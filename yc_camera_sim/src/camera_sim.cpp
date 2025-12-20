#include <Def/AOXEAppDef.h>
#include <Def/AppTopicIdDef.h>
#include <Def/MyTopicIdDef.h>

#include <camera_sim.h>
#include <udp_packet_log.h>
#include <utils.h>

#include <yc/YC_Controller_Main_Process.h>
#include <yc/YC_Controller_init.h>

#include <chrono>
#include <cstring>

CameraSimulator::CameraSimulator(int port, std::string ip_control, int port_dst)
    : port_(port), ip_contrl_(ip_control), port_dst_(port_dst),
      running_hearbit(false),
      running_subsystem_timer_(false),
      power_status_(POWER_UNKNOWN) {}

void CameraSimulator::init() {

    // UDP线程
    startUdpConnect();
    // 心跳线程
    startHeartbitting();
    // 共享内存输入参数 指针映射
    pointShmInputParams();

    // FPGA 模拟器 启动
    fpga_sim.start();
}

void CameraSimulator::step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output) {
    // todo: 是否需要上锁
    // std::lock_guard<std::mutex> lock(this->mtx_shm_);

    // TODO: 实现相机模拟器的步进逻辑
    // 复制共享内存输入
    memcpy(&(this->shm_input_), shm_input, sizeof(SharedMemoryInput));

    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    switch (*facility_power_supply_status_) {
    case 0:
        break;
    case 1:
        this->powerOn(30); // 上电 50s
        break;
    case 2:
        this->powerOn(2); // 快速上电 10s
        break;
    case 3:
        // 降级
        break;
    case 4:
        this->powerOff();
        break;
    default:
        break;
    }

    // 计算逻辑
    // this->compute();

    updateShmOutput();

    // 复制共享内存输出
    memcpy(shm_output, &(this->shm_output_), sizeof(SharedMemoryOutput));
}

void CameraSimulator::pointShmInputParams() {
    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    this->facility_power_supply_status_ = &shm_input_.m_FacilitiesPowerSupplyStatusParasMsg.St_FacilitiesPowerSupplyStatusData
                                               .ArrU1_FacilitiesPowerSupplyStatus[5];

    // // !!!!!调试时 供电暂时使用4
    // this->facility_power_supply_status_ = &shm_input_.m_FacilitiesPowerSupplyStatusParasMsg.St_FacilitiesPowerSupplyStatusData
    //                                            .ArrU1_FacilitiesPowerSupplyStatus[4];

    // 0-NA；1-初始化；2-快速启动；3-常规启动；4-冻结；5-停止
    this->operation_mode_ = &shm_input_.m_SecSimulatorControlMsg.St_SimulatorStatusControl.U1_OperationMode;
}

void CameraSimulator::updateShmOutput() {
    // std::lock_guard<std::mutex> lock(this->mtx_send_); // 不用加锁吧?
    SM_MessageHeader msg_header;
    msg_header.U4_Heartbeat       = this->heartbit_;
    msg_header.U2_EffectiveLength = sizeof(SM_MessageHeader);
    msg_header.St_GenerateTime    = getCurrentTimestamp();
    msg_header.St_PubTime         = getCurrentTimestamp();

    UnitStatusData unit_status_data;
    unit_status_data.ArrI1_UnitID[0]  = 6;
    unit_status_data.U1_MemberStatus  = 1;
    unit_status_data.U4_UnitHeartbeat = this->heartbit_;

    // update...
    this->shm_output_.m_FunctionalUnitStatusMsg.St_MessageHeader  = msg_header;
    this->shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData = unit_status_data;
}

int CameraSimulator::sendPacket(const UdpPacket *ptr_packet) {
    return udp_->SendData(
        reinterpret_cast<const char *>(ptr_packet),
        sizeofPacket(ptr_packet), ip_contrl_.c_str(), port_dst_);
}

void CameraSimulator::udpSendMsg(uint32_t topic_id, uint8_t *msg, uint32_t size_msg) {
    // udp 发送数据包
    UdpPacket packet;

    // Note: 没有设置目标V_NODE_XXX 改逻辑放在 ControlSimulator 里实现
    packet.time_tag   = getSysRTC();
    packet.source     = FUNCTION_NODE_TYPE::V_NODE_IRRM; // 我们发送的永远是这个
    packet.topicId    = topic_id;
    size_msg          = size_msg < 2048 ? size_msg : 2048;
    packet.payloadLen = size_msg;
    std::memcpy(packet.pPayload, msg, size_msg);

    INFO_UDP_PACKET_SEND("机载移植 Control", ip_contrl_.c_str(), port_dst_, packet);
    this->sendPacket(&packet);
}

void CameraSimulator::udpEventRecv(char *data, int size) {
    // 如果没有上电 则不处理
    if (power_status_ != POWER_ON)
        return;

    // 检查数据大小
    if (size > sizeof(UdpPacket)) {
        printf("[WARN] received data size (%d) > UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }

    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV(*ptr_packet);

    // 将收到的消息放入对应队列中
    auto topic_id = ptr_packet->topicId;
    switch (topic_id) {
    case V_TOPIC_IRST_ACT_REQ:
        sq::sq_IRST_act_req.push(std::move(ptr_packet));
        break;
    case V_TOPIC_SYMM_SYM_OPERATIONAL_PARAS:
    case V_TOPIC_SYMD_DATA_LOAD_MSG_IRRM:
        sq::sq_others.push(std::move(ptr_packet));
        break;
        // Note: 缓存参数信息
        // 系统管理时间信息报告
    case V_TOPIC_SYMM_SYM_TIME_REPORT:
        localUpdate(temp_mess_FromFc_SYM_TIME_REPORT, ptr_packet.get());
        break;
        // INS1工作参数报告
    case V_TOPIC_IN1M_INS1_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS1_OPERATIONAL_PARAS, ptr_packet.get());
        break;
        // INS2工作参数报告
    case V_TOPIC_IN2M_INS2_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS2_OPERATIONAL_PARAS, ptr_packet.get());
        break;
        // INS3工作参数报告
    case V_TOPIC_IN3M_INS3_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS3_OPERATIONAL_PARAS, ptr_packet.get());
        break;
    // 绝对导航融合飞行参数
    case V_TOPIC_NAFM_ABSOLUTE_NAV_DATA_FUSED:
        localUpdate(temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED, ptr_packet.get());
        break;
    // 导航参数报告
    case V_TOPIC_NAV_PARAS:
        localUpdate(temp_mess_FromFc_NAV_PARAS, ptr_packet.get());
        break;
    // 战术任务事件报告（事件类，通常入队）
    case V_TOPIC_TMMM_MISSION_EVENT_REPORT:
        localUpdate(temp_mess_FromFc_MISSION_EVENT_REPORT, ptr_packet.get());
        break;

    // // 内部存储消息（FLASH 相关）
    // case V_TOPIC_NEIBU_MESS:
    //     msgUpdate(msg_recv.m_HWINFO_FLASH, ptr_packet.get());
    //     // 如需要同步写 flash，可在 msgUpdate 内或此处处理
    //     break;
    // // 静态成像使用消息
    // case V_TOPIC_JT_PHOTO:
    //     msgUpdate(msg_recv.m_JT_PHOTO, ptr_packet.get());
    //     break;

    // ===================== 默认 =====================
    default:
        // 其他消息暂不处理
        break;
    }
    // todo: 5微秒延时？
}

void CameraSimulator::startTaskThreads() {
    // 任务线程启动
    startMainControl();
    startOtherProcess();
    startPeriodicSend();
    startTimer5ms();
    // startSubsystemTiming();
}

void CameraSimulator::startHeartbitting() {
    if (running_hearbit)
        return;
    // === 心跳线程 ===
    this->running_hearbit = true;
    thread_heartbit_      = std::thread([this]() {
        using namespace std::chrono;
        // auto time_step = seconds(1);
        auto time_step = milliseconds(180);

        while (running_hearbit) {
            ++heartbit_;

            // 向Control发送OKMSG
            uint8_t data[1] = {1};
            this->udpSendMsg(V_TOPIC_OKMSG, data);

            std::this_thread::sleep_for(time_step);
        }
    });
}

void CameraSimulator::startUdpConnect() {
    // 初始化udp连接 设置接受函数
    initUdpTrans(port_, ip_contrl_.c_str(), port_dst_,
                 [this](char *data, int size) { this->udpEventRecv(data, size); });
}

void CameraSimulator::startMainControl() {
    if (running_main_ctrl)
        return;

    running_main_ctrl = true;
    thread_main_ctrl_ = std::thread([this]() {
        main_Control_And_Mess_Process_Act_req_task();
    });
    //
}

void CameraSimulator::startOtherProcess() {
    if (running_other_process)
        return;

    running_other_process = true;
    thread_other_process_ = std::thread([this]() {
        fc_Mess_Process_Others_task();
    });
}

void CameraSimulator::startPeriodicSend() {
    if (running_periodic_send)
        return;

    running_periodic_send = true;
    thread_periodic_send_ = std::thread([this]() {
        fc_Mess_Send_Period_task();
    });
}

void CameraSimulator::startTimer5ms() {
    timer_5ms_.init(std::chrono::milliseconds(5), timer_service_func_5ms);
    timer_5ms_.start();
}

void CameraSimulator::startSubsystemTiming() {
}

void CameraSimulator::powerOn(int delay) {
    // 初始化参数
    param_Init();

    // 避免重复上电
    if (power_status_ == POWER_ON || power_status_ == POWER_CHECKING) {
        return;
    }

    printf("[CameraSimulator] Power ON start with (%d s)\n", delay);

    // 如果还没退出 上电线程退出
    if (thread_power_on_.joinable())
        thread_power_on_.join();

    this->thread_power_on_ = std::thread([this, delay]() {
        using namespace std::chrono;
        this->remain_time = delay;
        int  interval     = 1; // 1秒间隔
        auto time_step    = seconds(interval);

        this->power_status_ == POWER_CHECKING;

        while (remain_time > 0 && power_status_ == POWER_CHECKING) {
            printf("[CameraSimulator] Power ON remain %d seconds... \n", this->remain_time.load());
            // 上电自检中
            // msg
            this->remain_time -= interval;

            std::this_thread::sleep_for(time_step);
        }

        if (power_status_ == POWER_FREEZE || power_status_ == POWER_OFF) {
            printf("[CameraSimulator] Power ON terminated\n");

        } else {
            // 上电成功
            this->remain_time   = 0;
            this->power_status_ = POWER_ON;

            printf("[CameraSimulator] Power ON complete\n");

            // !!!启动任务线程
            this->startTaskThreads();
        }
    });
}

void CameraSimulator::freeze() {
    if (power_status_ == POWER_FREEZE) {
        return;
    }

    // 退出除了周期发送以外的其他线程
    // 先设置退出标志
    running_main_ctrl     = false;
    running_other_process = false;
    running_periodic_send = false;
    // ?
    this->running_subsystem_timer_ = false;

    // 再清空并通知，确保等待的线程能醒来并检查到退出标志
    sq::sq_IRST_act_req.clearAndNotify();
    sq::sq_others.clearAndNotify();

    // 等待线程退出
    if (thread_main_ctrl_.joinable())
        thread_main_ctrl_.join();
    if (thread_other_process_.joinable())
        thread_other_process_.join();
    if (thread_periodic_send_.joinable())
        thread_periodic_send_.join();
    if (thread_subsystem_timer_.joinable())
        thread_subsystem_timer_.join();

    // 停止定时器
    timer_5ms_.stop();

    this->power_status_ = POWER_FREEZE;

    // 停止上电线程
    if (thread_power_on_.joinable())
        thread_power_on_.join();
}

void CameraSimulator::powerOff() {
    if (power_status_ == POWER_OFF) {
        return;
    }

    this->freeze();

    // 更新共享内存状态
    this->shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U1_MemberStatus  = 4; // 4=下电?
    this->shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U4_UnitHeartbeat = this->heartbit_;
    // this->shm_output_.m_FunctionalUnitStatusMsg.St_MessageHeader.St_PubTime        = getCurrentTimestamp();

    // todo: 下电自检测流程

    // this->udpSend(V_TOPIC_IRRM_WORK_STATE_REPORT, (UINT8 *)&msg_send.m_WORK_STATE_REPORT, sizeof(WORK_STATE_REPORT));
    // this->udpSend(V_TOPIC_IRRM_IRST_OPERATIONAL_PARAS, (UINT8 *)&msg_send.m_IRST_OPERATIONAL_PARAS, sizeof(IRST_OPERATIONAL_PARAS));

    this->power_status_ = POWER_OFF;

    printf("[CameraSimulator] Power OFF complete\n");
    // // msg
    // msg_send.m_WORK_STATE_REPORT.bit_process_percent = 0;
    // msg_send.m_WORK_STATE_REPORT.start_remain_time   = 0;
    // msg_send.m_WORK_STATE_REPORT.subsys_work_state   = SUBSYS_WORK_STATE::V_SUBSYS_WORK_STATE_STOP;
    // msg_send.m_WORK_STATE_REPORT.subsys_main_mode    = SUBSYS_MAIN_MODE::V_SUBSYS_MAIN_MODE_STOP;
}

CameraSimulator::~CameraSimulator() {

    this->powerOff();

    // 关闭udp连接
    if (udp_) {
        udp_->Close();
        udp_.reset();
    }

    // 停止心跳
    running_hearbit = false;
    if (thread_heartbit_.joinable())
        thread_heartbit_.join();

    printf("[CameraSimulator] All threads stopped\n");
}