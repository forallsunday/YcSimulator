#include <Def/AOXEAppDef.h>
#include <Def/AppTopicIdDef.h>

#include <camera_sim.h>
#include <udp_packet_log.h>

#include <chrono>
#include <cstring>

Timestamp getCurrentTimestamp() {
    using namespace std::chrono;

    // 获取当前时间点
    auto now = system_clock::now();

    // 转为 time_t（秒）
    std::time_t t = system_clock::to_time_t(now);
    std::tm     local_tm{};
#ifdef _WIN32
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif

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

CameraSimulator::CameraSimulator(int port, std::string ip_dst, int port_dst)
    : port_(port), ip_dst_(ip_dst), port_dst_(port_dst),
      heartbit_(0),
      updatting_heartbit_(false),
      is_powered_on_(false),
      running_act_req_(false),
      running_other_process_(false),
      running_periodic_send_(false),
      running_subsystem_timer_(false) {}

void CameraSimulator::init() {
    // 心跳线程
    startHeartbitting();

    // udp连接
    udp_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        "0.0.0.0", this->port_, -1,
        [this](char *data, int size) { this->dataReceive(data, size); }));

    // 开启udp连接 (子线程1启动)
    udp_->Init();

    // 其他子线程启动
    startActReq();
    startOtherProcess();
    startPeriodicSend();
    startSubsystemTiming();
}

void CameraSimulator::step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output) {
    // 上锁
    // std::lock_guard<std::mutex> lock(this->mtx_shm_);

    // TODO: 实现相机模拟器的步进逻辑
    // 复制共享内存输入
    memcpy(&(this->shm_input_), shm_input, sizeof(SharedMemoryInput));

    updateShmInputParams();

    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    switch (*facility_power_supply_status) {
    case 0:
        break;
    case 1:
        this->powerOn(50); // 上电 50s
        break;
    case 2:
        this->powerOn(10); // 快速上电 10s
        break;
    case 3:
        break;
    case 4:
        this->powerOff();
        break;
    default:
        break;
    }

    updateShmOutput();

    // 复制共享内存输出
    memcpy(shm_output, &(this->shm_output_), sizeof(SharedMemoryOutput));
}

void CameraSimulator::startHeartbitting() {
    if (updatting_heartbit_)
        return;
    // === 心跳线程 ===
    this->updatting_heartbit_ = true;
    heartbit_thread_          = std::thread([this]() {
        using namespace std::chrono;
        auto interval  = 1;
        auto time_step = seconds(interval);
        while (updatting_heartbit_) {
            ++heartbit_;

            // 构造心跳包
            // udpSend(0x0000BEEF, hb_payload, sizeof(hb_payload));
            std::this_thread::sleep_for(time_step);
        }
    });
}

void CameraSimulator::updateShmInputParams() {
    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    this->facility_power_supply_status = &shm_input_.facilities_power_supply_status_paras_msg.St_FacilitiesPowerSupplyStatusData
                                              .ArrU1_FacilitiesPowerSupplyStatus[5];
    // 0-NA；1-初始化；2-快速启动；3-常规启动；4-冻结；5-停止
    this->operation_mode = &shm_input_.sec_simulator_control_msg.St_SimulatorStatusControl.U1_OperationMode;
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
    this->shm_output_.functional_unit_status_msg.St_MessageHeader  = msg_header;
    this->shm_output_.functional_unit_status_msg.St_UnitStatusData = unit_status_data;
}

void CameraSimulator::udpSend(uint32_t topic_id, uint8_t *msg, uint32_t msg_len) {
    // // 加锁
    // std::lock_guard<std::mutex> lock(this->mtx_send_);

    // udp 发送数据包
    UdpPacket packet;

    // 获取当前时间戳
    using namespace std::chrono;
    auto time_stamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    // Note: 没有设置目标V_NODE_XXX 改逻辑放在 ControlSimulator 里实现
    packet.time_tag   = time_stamp;
    packet.source     = FUNCTION_NODE_TYPE::V_NODE_IRRM; // 我们发送的永远是这个
    packet.topicId    = topic_id;
    packet.payloadLen = msg_len;
    std::memcpy(packet.pPayload, msg, msg_len);

    this->udp_->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeof(UdpPacket),
        this->ip_dst_.c_str(), this->port_dst_);
}

void CameraSimulator::dataReceive(char *data, int size) {
    // todo: 解析数据 分类消息
    // Debug 检查数据大小
#ifndef NDEBUG
    if (size > sizeof(UdpPacket)) {
        printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }
#endif

    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV("Control", this->ip_dst_, *ptr_packet);

    // 收到后放入对应队列中
    // this->queue_act_req_.push(std::move(ptr_packet));
    // this->queue_others_.push(std::move(ptr_packet));
}

void CameraSimulator::startActReq() {
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
        const auto interval = milliseconds(5);

        while (running_periodic_send_) {
            auto start = steady_clock::now();

            // WORK_STATE_REPORT
            WORK_STATE_REPORT work_state_report;
            work_state_report.msg_publish_time.time_sys_RTC = getSysRTC();
            work_state_report.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
            work_state_report.start_remain_time             = this->remain_time;
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
    if (is_powered_on_)
        return; // 避免重复上电

    is_powered_on_ = true;
    printf("[CameraSimulator] Power ON sequence start (%d s)\n", delay);

    if (power_on_thread_.joinable())
        power_on_thread_.join();

    power_on_thread_ = std::thread([this, delay]() {
        using namespace std::chrono;
        this->remain_time = delay;
        int  interval     = 1; // 1秒间隔
        auto time_step    = seconds(interval);

        while (this->remain_time > 0 && is_powered_on_) {
            this->remain_time -= interval;
            std::this_thread::sleep_for(time_step);
        }

        if (is_powered_on_)
            printf("[CameraSimulator] Power ON complete\n");
    });
}
void CameraSimulator::powerOff() {
    if (!is_powered_on_) {
        printf("[CameraSimulator] Already powered off.\n");
        return;
    }

    // 上电线程退出
    is_powered_on_ = false;
    if (power_on_thread_.joinable())
        power_on_thread_.join();
    printf("[CameraSimulator] Power OFF start\n");

    // // 停止周期性任务
    // running_periodic_send_ = false;
    // if (thread_periodic_send_.joinable())
    //     thread_periodic_send_.join();

    // 更新共享内存状态
    this->shm_output_.functional_unit_status_msg.St_UnitStatusData.U1_MemberStatus = 0; // 0=下电
    // this->shm_output_.functional_unit_status_msg.St_UnitStatusData.U4_UnitHeartbeat = this->heartbit_;
    // this->shm_output_.functional_unit_status_msg.St_MessageHeader.St_PubTime        = getCurrentTimestamp();

    printf("[CameraSimulator] Power OFF complete\n");
}

CameraSimulator::~CameraSimulator() {
    // 停止心跳
    updatting_heartbit_ = false;
    if (heartbit_thread_.joinable())
        heartbit_thread_.join();

    // 停止上电线程
    is_powered_on_ = false;
    if (power_on_thread_.joinable())
        power_on_thread_.join();

    // 关闭udp连接
    if (udp_) {
        udp_->Close();
        udp_.reset();
    }

    running_act_req_         = false;
    running_other_process_   = false;
    running_periodic_send_   = false;
    running_subsystem_timer_ = false;

    queue_act_req_.notifyAll();
    queue_others_.notifyAll();

    if (thread_act_req_.joinable())
        thread_act_req_.join();
    if (thread_other_process_.joinable())
        thread_other_process_.join();
    if (thread_periodic_send_.joinable())
        thread_periodic_send_.join();
    if (thread_subsystem_timer_.joinable())
        thread_subsystem_timer_.join();

    printf("[CameraSimulator] All threads stopped\n");
}