#include <Def/AOXEAppDef.h>
#include <Def/AppTopicIdDef.h>

#include <camera_sim.h>
#include <udp_packet_log.h>

#include <chrono>
#include <cstring>

CameraSimulator::CameraSimulator(int port, std::string ip_control, int port_dst)
    : port_(port), ip_contrl_(ip_control), port_dst_(port_dst),
      running_hearbit(false),
      during_powered_on_(false),
      running_act_req_(false),
      running_other_process_(false),
      running_periodic_send_(false),
      running_subsystem_timer_(false),
      power_status_(POWER_UNKNOWN) {}

void CameraSimulator::init() {
    // 心跳线程
    startHeartbitting();
    // UDP线程
    startUdpConnect();
    // 共享内存输入参数 指针映射
    pointShmInputParams();
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
        this->powerOn(5); // 快速上电 10s
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

void CameraSimulator::udpSend(uint32_t topic_id, uint8_t *msg, uint32_t size_msg) {
    // // 加锁
    // std::lock_guard<std::mutex> lock(this->mtx_send_);

    // udp 发送数据包
    UdpPacket packet;

    // Note: 没有设置目标V_NODE_XXX 改逻辑放在 ControlSimulator 里实现
    packet.time_tag   = getSysRTC();
    packet.source     = FUNCTION_NODE_TYPE::V_NODE_IRRM; // 我们发送的永远是这个
    packet.topicId    = topic_id;
    size_msg          = size_msg < 2048 ? size_msg : 2048;
    packet.payloadLen = size_msg;

    std::memcpy(packet.pPayload, msg, size_msg);

    INFO_UDP_PACKET_SEND("Control", this->ip_contrl_.c_str(), this->port_dst_, packet);

    this->udp_->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeof(UdpPacket),
        this->ip_contrl_.c_str(), this->port_dst_);
}

void CameraSimulator::udpRecv(char *data, int size) {
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

    // todo: 解析数据 分类消息
    // 将收到的消息放入对应队列中
    auto topic_id = ptr_packet->topicId;
    switch (topic_id) {
    case V_TOPIC_IRST_ACT_REQ:
        this->queue_act_req_.push(std::move(ptr_packet));
        break;
    case V_TOPIC_SYMM_SYM_OPERATIONAL_PARAS:
    case V_TOPIC_SYMD_DATA_LOAD_MSG_IRRM:
        this->queue_others_.push(std::move(ptr_packet));
        break;
        // Note: 缓存参数信息
        // 系统管理时间信息报告
    case V_TOPIC_SYMM_SYM_TIME_REPORT:
        copyMsgFromPacket(msg_recv.m_SYM_TIME_REPORT, ptr_packet.get());
        break;
        // INS1工作参数报告
    case V_TOPIC_IN1M_INS1_OPERATIONAL_PARAS:
        copyMsgFromPacket(msg_recv.m_INS1_OPERATIONAL_PARAS, ptr_packet.get());
        break;
    // ...
    default:
        break;
    }
}

void CameraSimulator::startTaskThreads() {
    // 任务线程启动
    startActReq();
    startOtherProcess();
    startPeriodicSend();
    startSubsystemTiming();
}

void CameraSimulator::startHeartbitting() {
    if (running_hearbit)
        return;
    // === 心跳线程 ===
    this->running_hearbit = true;
    thread_heartbit_      = std::thread([this]() {
        using namespace std::chrono;
        auto interval  = 1;
        auto time_step = seconds(interval);
        while (running_hearbit) {
            ++heartbit_;
            std::this_thread::sleep_for(time_step);
        }
    });
}

void CameraSimulator::startUdpConnect() {
    // udp连接
    udp_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        "0.0.0.0", this->port_, -1,
        [this](char *data, int size) { this->udpRecv(data, size); }));

    printf("[CameraSimulator] UdpConnect bind port: %d\n", this->port_);

    // 开启udp连接 (子线程1启动)
    udp_->Init();
}

void CameraSimulator::startActReq() {
    //
}

void CameraSimulator::startOtherProcess() {
    if (running_other_process_)
        return;

    running_other_process_ = true;
    thread_other_process_  = std::thread([this]() {
        using namespace std::chrono;

        while (running_other_process_) {

            PtrUdpPacket ptr_packet;

            // 等待队列有数据并取出，如果超时，则进行下一次循环
            if (queue_others_.waitForAndPop(ptr_packet, timeout)) {
                // === 处理UDP消息 ===
            }
        }
    });
}

void CameraSimulator::startPeriodicSend() {
    if (running_periodic_send_)
        return;

    running_periodic_send_ = true;
    thread_periodic_send_  = std::thread([this]() {
        using namespace std::chrono;
        const auto interval = milliseconds(this->periodic_send_interval);

        while (running_periodic_send_) {
            auto start = steady_clock::now();

            // WORK_STATE_REPORT
            WORK_STATE_REPORT work_state_report;
            work_state_report.msg_publish_time.time_sys_RTC = getSysRTC();
            work_state_report.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
            work_state_report.start_remain_time             = this->remain_time; // remain_time.load()?
            work_state_report.subsys_work_state             = SUBSYS_WORK_STATE::V_SUBSYS_WORK_STATE_NA;
            work_state_report.subsys_main_mode              = SUBSYS_MAIN_MODE::V_SUBSYS_MAIN_MODE_NA;
            // work_state_report.AC_ID =
            work_state_report.security_level          = V_SECURITY_LEVEL_SECRET;
            work_state_report.bit_process_percent     = 678;
            work_state_report.subsys_electrify_amount = 123;

            this->udpSend(V_TOPIC_IRRM_WORK_STATE_REPORT,
                           (UINT8 *)&work_state_report, sizeof(WORK_STATE_REPORT));
            printf("[CameraSimulator] Sent periodic UDP packet: WORK_STATE_REPORT\n");

            // IRST_OPERATIONAL_PARAMS
            IRST_OPERATIONAL_PARAS irst_operational_paras;
            irst_operational_paras.msg_publish_time.time_sys_RTC = getSysRTC();
            irst_operational_paras.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
            irst_operational_paras.security_level                = V_SECURITY_LEVEL_SECRET;
            irst_operational_paras.paras_validity                = 1; // 有效

            this->udpSend(V_TOPIC_IRRM_IRST_OPERATIONAL_PARAS,
                           (UINT8 *)&irst_operational_paras, sizeof(IRST_OPERATIONAL_PARAS));
            printf("[CameraSimulator] Sent periodic UDP packet: IRST_OPERATIONAL_PARAS\n");

            // 定时
            std::this_thread::sleep_until(start + interval);
        }
    });
}

void CameraSimulator::startSubsystemTiming() {
}

Timestamp CameraSimulator::getCurrentTimestamp() {
    using namespace std::chrono;

    // 获取当前时间点
    auto now = system_clock::now();

    // 转为 time_t（秒）
    std::time_t t = system_clock::to_time_t(now);
    std::tm     local_tm{};

    localtime_r(&t, &local_tm);

    // 计算毫秒部分
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    Timestamp ts{};
    ts.U1_Year        = static_cast<unsigned char>((local_tm.tm_year + 1900) % 100); // 年份只取后两位
    ts.U1_Month       = static_cast<unsigned char>(local_tm.tm_mon + 1);
    ts.U1_Day         = static_cast<unsigned char>(local_tm.tm_mday);
    ts.U1_Hour        = static_cast<unsigned char>(local_tm.tm_hour);
    ts.U1_Minute      = static_cast<unsigned char>(local_tm.tm_min);
    ts.U1_Second      = static_cast<unsigned char>(local_tm.tm_sec);
    ts.U2_Millisecond = static_cast<unsigned short>(ms.count());

    return ts;
}

uint64_t CameraSimulator::getSysRTC() {
    // todo: 不对
    using namespace std::chrono;
    // 获取当前时间点（系统时钟）
    auto now = steady_clock::now();
    // 转换为毫秒数
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count();
    return static_cast<uint64_t>(ms);
}

void CameraSimulator::powerOn(int delay) {
    // 避免重复上电
    if (power_status_ == POWER_ON) {
        return;
    }

    printf("[CameraSimulator] Power ON start with (%d s)\n", delay);

    this->during_powered_on_ = true;

    // 如果还没退出 上电线程退出
    if (thread_power_on_.joinable())
        thread_power_on_.join();

    this->thread_power_on_ = std::thread([this, delay]() {
        using namespace std::chrono;
        this->remain_time = delay;
        int  interval     = 1; // 1秒间隔
        auto time_step    = seconds(interval);

        while (this->remain_time > 0 && during_powered_on_) {
            printf("[CameraSimulator] Power ON remain %d seconds... \n", this->remain_time.load());
            this->remain_time -= interval;
            std::this_thread::sleep_for(time_step);
        }

        if (power_status_ == POWER_FREEZE || power_status_ == POWER_OFF) {
            printf("[CameraSimulator] Power ON terminated\n");

        } else {
            this->remain_time        = 0;
            this->during_powered_on_ = false;
            this->power_status_      = POWER_ON;

            printf("[CameraSimulator] Power ON complete\n");

            // 启动任务线程
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
    this->running_act_req_         = false;
    this->running_other_process_   = false;
    this->running_subsystem_timer_ = false;

    // 再清空并通知，确保等待的线程能醒来并检查到退出标志
    this->queue_act_req_.clearAndNotify();
    this->queue_others_.clearAndNotify();

    // 等待线程退出
    if (thread_act_req_.joinable())
        thread_act_req_.join();
    if (thread_other_process_.joinable())
        thread_other_process_.join();
    if (thread_subsystem_timer_.joinable())
        thread_subsystem_timer_.join();

    this->power_status_ = POWER_FREEZE;

    // 停止上电线程
    during_powered_on_ = false;
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

    this->power_status_ = POWER_OFF;

    printf("[CameraSimulator] Power OFF complete\n");
}

CameraSimulator::~CameraSimulator() {

    this->powerOff();

    // 关闭周期性发送
    running_periodic_send_ = false;
    if (thread_periodic_send_.joinable())
        thread_periodic_send_.join();

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