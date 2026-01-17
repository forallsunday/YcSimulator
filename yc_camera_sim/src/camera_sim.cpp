#include <Def/AOXEAppDef.h>
#include <Def/AppTopicIdDef.h>
#include <Def/MyTopicIdDef.h>

#include <camera_sim.h>
#include <log_def.h>
#include <utils.h>

#include <yc/YC_Controller_Main_Process.h>
#include <yc/YC_Controller_init.h>

#include <chrono>
#include <cstring>
#include <log.h>
#include <udp_trans.h>

CameraSimulator::CameraSimulator(int port, std::string ip_control, int port_dst)
    : port_(port), ip_contrl_(ip_control), port_dst_(port_dst),
      running_hearbit(false),
      running_subsystem_timer_(false),
      power_status_(POWER_UNKNOWN) {}

void CameraSimulator::init() {

    if (!already_initialized) {

        // 设置周期性发送间隔
        ps::periodic_interval = PERIOD_TASK_TIME;

        // UDP线程
        startUdpConnect();
        // 心跳线程
        startHeartbitting();
        // 共享内存输入参数 指针映射
        pointShmInputParams();

        // FPGA 模拟器 初始化
        fpga_sim_.init();

        this->already_initialized = true;
    }
}

void CameraSimulator::step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output) {
    // todo: 是否需要上锁
    // std::lock_guard<std::mutex> lock(this->mtx_shm_);

    // TODO: 实现相机模拟器的步进逻辑
    // 复制共享内存输入
    memcpy(&(this->shm_input_), shm_input, sizeof(SharedMemoryInput));

    // log_info("上电指令为: %d", *facility_power_supply_status_);

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
            sendOkMsg();

            std::this_thread::sleep_for(time_step);
        }
    });
}

void CameraSimulator::startUdpConnect() {
    // 初始化udp连接 设置接受函数
    // udpTransInit(port_, ip_contrl_.c_str(), port_dst_, [this](char *data, int size) { this->udpEventRecv(data, size); });
    udpTransInit(port_, ip_contrl_.c_str(), port_dst_);
}

void CameraSimulator::startMainControl() {
    if (running_main_ctrl)
        return;

    // fpga 启动
    fpga_sim_.start();

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

    // 避免重复上电
    if (power_status_ == POWER_ON || power_status_ == POWER_CHECKING) {
        return;
    }

    log_info("[CameraSimulator] Power ON start with (%d s)", delay);

    // 如果还没退出 上电线程退出
    if (thread_power_on_.joinable())
        thread_power_on_.join();

    this->thread_power_on_ = std::thread([this, delay]() {
        using namespace std::chrono;
        this->remain_time = delay;
        int  interval     = 1; // 1秒间隔
        auto time_step    = seconds(interval);

        this->power_status_ = POWER_CHECKING;

        while (remain_time > 0 && power_status_ == POWER_CHECKING) {
            log_info("[CameraSimulator] Power ON remain %d seconds...", this->remain_time.load());
            // 上电自检中
            // msg
            this->remain_time -= interval;

            std::this_thread::sleep_for(time_step);
        }

        if (power_status_ == POWER_FREEZE || power_status_ == POWER_OFF) {
            log_info("[CameraSimulator] Power ON terminated");

        } else {
            // 上电成功
            this->remain_time   = 0;
            this->power_status_ = POWER_ON;
            // 初始化参数
            param_Init();
            // 队列 初始化
            sq::sq_IRST_act_req.clearAndNotify();
            sq::sq_others.clearAndNotify();

            log_info("[CameraSimulator] Power ON complete");

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

    // 再清空并通知，确保等待的线程能醒来并检查到退出标志
    sq::sq_IRST_act_req.clearAndNotify();
    sq::sq_others.clearAndNotify();

    // 停止定时器
    timer_5ms_.stop();

    // 停止fpga
    fpga_sim_.stop();

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

    // 等待线程退出
    if (thread_main_ctrl_.joinable())
        thread_main_ctrl_.join();
    if (thread_other_process_.joinable())
        thread_other_process_.join();
    if (thread_periodic_send_.joinable())
        thread_periodic_send_.join();
    if (thread_subsystem_timer_.joinable())
        thread_subsystem_timer_.join();

    // 更新共享内存状态
    this->shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U1_MemberStatus  = 4; // 4=下电?
    this->shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U4_UnitHeartbeat = this->heartbit_;
    // this->shm_output_.m_FunctionalUnitStatusMsg.St_MessageHeader.St_PubTime        = getCurrentTimestamp();

    this->power_status_ = POWER_OFF;

    log_info("[CameraSimulator] Power OFF complete");
}

void CameraSimulator::close() {
    this->powerOff();

    // 停止心跳
    running_hearbit = false;

    if (thread_heartbit_.joinable())
        thread_heartbit_.join();

    // 停止拍照测试
    running_photoing_test = false;
    if (thread_photoing_test_.joinable())
        thread_photoing_test_.join();

    udpTransClose();

    this->already_initialized = false;

    log_info("[CameraSimulator] All threads stopped");
}

CameraSimulator::~CameraSimulator() {
    this->close();
}

void CameraSimulator::testPhotoing() {
    if (running_photoing_test)
        return;

    running_photoing_test = true;
    thread_photoing_test_ = std::thread([this]() {
        using namespace std::chrono;
        using namespace std::this_thread;

        auto setParams = []() {
            // 设置参数 - 参考 prepare_Model_WorkControl 流程
            // ===================== 成像模式参数 =====================
            // 成像模式：广域成像 (1=广域, 2=区域成像, 3=区域监视)
            cmd_From_FC.irst_cmd_param_irst_form_mode = V_IRST_FORM_MODE_WIDE_IMAG;
            main_Control_State_Param.irst_form_mode   = V_IRST_FORM_MODE_WIDE_IMAG;
            // 广域成像参数有效
            cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity = 1;
            // 由于没有udp包 不能处理act_req的参数传递 只能直接修改全局参数
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = V_IR_WIDE_IMAGE_DIRECTION_RIGHT;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = V_IR_WIDE_IMAGE_MODE_DIS_PRIO;
            // 距离优先参数
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_lowline = 40;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_upline  = 80;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude  = 123;
            // 方位优先参数
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE      = 0;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_start_angle = 0;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_end_angle   = 0;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.AZ_area_altitude    = 123;

            // ===================== temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED 数据填充 =====================
            // 反推填充 temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED
            // 参考 fpga_sim.cpp 中的转换公式进行反推

            // 时间数据（当前时间）
            auto now         = std::chrono::system_clock::now();
            auto time_t      = std::chrono::system_clock::to_time_t(now);
            auto tm          = *std::localtime(&time_t);
            auto duration    = now.time_since_epoch();
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_year  = tm.tm_year + 1900;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_month = tm.tm_mon + 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_day   = tm.tm_mday;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.time_gnss_calendartime            = nanoseconds;

            // 位置数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._longitude = 102.54f * PI / 180 / 0.00001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._latitude  = 30.05f * PI / 180 / 0.00001;

            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_alt._altitude = 17000.0f / 0.01;

            // 姿态数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_true_heading._angle_mrad = 90.0f * PI / 180 / 0.001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_pitch._angle_mrad        = 2.0f * PI / 180 / 0.001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_roll._angle_mrad         = 3.0f * PI / 180 / 0.001;

            // 速度数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_North._velocity  = 0.0f / 0.0001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_West._velocity   = -180.0f / 0.0001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_ground_speed._velocity = 0.0f / 0.0001;

            // 设置数据有效性标志
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_position      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_GNSS_alt      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_north     = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_west      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_ground_speed  = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_CNI_GNSS_time = 1;
        };

        // 准备
        log_once("[CameraSimulator] 设置准备");
        while (running_photoing_test) {
            setParams();
            cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_PREPARE;
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_PREPARE) {
                cmd_From_FC.irst_cmd_STATE_SET = 0;
            } else {
                cmd_From_FC.irst_cmd_STATE_SET = 1;
            }
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
                break;
            }
            sleep_for(10ms);
        }

        log_once("[CameraSimulator] 开始拍照");
        while (running_photoing_test) {
            setParams();
            cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_TAKE_PIC;
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
                cmd_From_FC.irst_cmd_STATE_SET = 0;
            } else {
                cmd_From_FC.irst_cmd_STATE_SET = 1;
            }
            // main_Control_State_Param.irst_work_state   = V_IRST_WORK_STATE_TAKE_PIC;
            sleep_for(10ms);
        }
    });
}
