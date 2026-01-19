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

        // FPGA 模拟器 初始化
        fpga_sim_.init();

        this->already_initialized = true;
    }
}

void CameraSimulator::step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output) {
    // 是否需要上锁
    // std::lock_guard<std::mutex> lock(this->mtx_shm_);

    if (!already_initialized) {
        log_error("[CameraSimulator] Not initialized yet!");
        return;
    }
    if (shm_input == nullptr || shm_output == nullptr) {
        log_error("[CameraSimulator] Shared memory input or output is null!");
        return;
    }

    // 复制共享内存输入
    memcpy(&(this->shm_input_), shm_input, sizeof(SharedMemoryInput));

    // 更新共享内存变量输入
    this->updateSharedMemoryInput();

    // log_info("上电指令为: %d", *facility_power_supply_status_);

    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    switch (facility_power_supply_status_) {
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

    // 更新共享内存变量输出
    this->updateSharedMemoryOutput();

    // 复制共享内存输出
    memcpy(shm_output, &(this->shm_output_), sizeof(SharedMemoryOutput));
}

void CameraSimulator::updateSharedMemoryInput() {
    // // 设备供电状态参数
    // FacilitiesPowerSupplyStatusParasMsg m_FacilitiesPowerSupplyStatusParasMsg;
    // // 模拟器运行控制 - 场景控制指令
    // SecSimulatorControlMsg m_SecSimulatorControlMsg;
    // // 实体时空位置状态 - 实体目标信息（其他模拟器）
    // SecAllEntityTSPIMsg m_SecAllEntityTSPIMsg;
    // // 本机实体时空位置状态
    // SecEntityTSPIMsg m_SecEntityTSPIMsg;
    // // 虚拟兵力时空位置状态 - 虚拟目标信息（训练控制中设置的目标）
    // SecVFTSPIMsg m_SecVFTSPIMsg;
    // // 动目标像素坐标参数数据定义
    // SecTgtPositionParaMsg m_SecTgtPositionParaMsg; // 5个动目标像素坐标

    // 综合光电上电状态获取位置在5号索引
    constexpr int idx = 5;
    // // !!!!!调试时 供电暂时使用4
    // constexpr int idx = 4;

    // [5]综合光电系统 0-NA 1-上电 2-快速上电 3-降级 4-下电
    facility_power_supply_status_ = shm_input_.m_FacilitiesPowerSupplyStatusParasMsg.St_FacilitiesPowerSupplyStatusData.ArrU1_FacilitiesPowerSupplyStatus[idx];
    // 0-NA；1-初始化；2-快速启动；3-常规启动；4-冻结；5-停止
    operation_mode_ = shm_input_.m_SecSimulatorControlMsg.St_SimulatorStatusControl.U1_OperationMode;

    // 动目标像素坐标参数
    target_pixel_coor.up_left_x    = shm_input_.m_SecTgtPositionParaMsg.Arr_EOTgtPositionPara->U2_Tgt1UpleftX;
    target_pixel_coor.up_left_y    = shm_input_.m_SecTgtPositionParaMsg.Arr_EOTgtPositionPara->U2_Tgt1UpleftY;
    target_pixel_coor.down_right_x = shm_input_.m_SecTgtPositionParaMsg.Arr_EOTgtPositionPara->U2_Tgt1DownrightX;
    target_pixel_coor.down_right_y = shm_input_.m_SecTgtPositionParaMsg.Arr_EOTgtPositionPara->U2_Tgt1DownrightY;
}

void CameraSimulator::updateSharedMemoryOutput() {
    std::lock_guard<std::mutex> lock(mutex_shm);

    static SM_MessageHeader St_MessageHeader;
    St_MessageHeader.U4_Heartbeat       = this->heartbit_;
    St_MessageHeader.U2_EffectiveLength = sizeof(SM_MessageHeader);
    St_MessageHeader.St_GenerateTime    = getCurrentTimestamp();
    St_MessageHeader.St_PubTime         = getCurrentTimestamp();

    // FunctionalUnitStatusMsg 功能单元状态
    shm_output_.m_FunctionalUnitStatusMsg.St_MessageHeader                       = St_MessageHeader;
    shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.ArrI1_UnitID[0]      = 6;
    shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.ArrI1_UnitVersion[0] = 6; // ?
    shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U1_MemberStatus      = 1;
    shm_output_.m_FunctionalUnitStatusMsg.St_UnitStatusData.U4_UnitHeartbeat     = this->heartbit_;

    /// SecEOImageDriveMsg 综合光电成像驱动参数
    static EOImageState      St_EOImageState;      ///< @ID(1) 成像状态
    static EOImageShowArea   St_EOImageShowArea;   ///< @ID(2) 显示区域参数
    static EOImageParasIS    St_EOImageParasIS;    ///< @ID(3) 图像注释信息
    static EOImageModifyPara St_EOImageModifyPara; ///< @ID(4) 光电图像调节参数
    static EOTgtPara         Arr_EOTgtPara[5];     ///< @ID(5) 动目标检测成像参数[5] (最多包含5个目标)

    St_EOImageState.U1_IRSensor = mess_To_TXCL_CMD.mode_IR_SENSOR; // @ID(0) // 传感器状态 0-NA，1-可见光，2-红外，3-可见+红外，4-红外+可见

    // 视频状态 0-NA，1-图像，2-视频
    switch (mess_To_TXCL_ZSXX.tx_info[3]) {
    case 0: // 正常帧标记
        St_EOImageState.U1_TVState = 1;
        break;
    case 1: // 每秒1帧标记
    case 2: // 冻结标记
        St_EOImageState.U1_TVState = 2;
        break;
    default:
        St_EOImageState.U1_TVState = 0;
        break;
    }

    St_EOImageState.U1_ImageMode = main_Control_State_Param.irst_form_mode; // @ID(2) // 成像模式 0-NA，1-广域成像，2-区域成像，3-区域监视
    St_EOImageState.U1_Channel   = 1;                                       // todo: 确认通道填充规则

    // 指针以减少代码字数
    auto *image_paras_transit = &mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit; // 图像参数_下传
    auto *ac_ins_info         = &mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info;         // 飞机惯导信息

    // === EOImageShowArea 显示区域参数 ===
    St_EOImageShowArea.F4_AZLOS_deg_BODY      = image_paras_transit->fov_center_azimuth * 0.01f; // 视线方位角(deg)
    St_EOImageShowArea.F4_ELLOS_deg_BODY      = image_paras_transit->fov_center_el * 0.01f;      // 视线俯仰角(deg)
    St_EOImageShowArea.F4_horizontalCover_deg = image_paras_transit->fov_transverse * 0.01f;     // 水平范围(deg)
    St_EOImageShowArea.F4_verticalCover_deg   = image_paras_transit->fov_vertical * 0.01f;       // 垂直范围(deg)
    // === EOImageShowArea 显示区域参数 === End

    // === EOImageParasIS 图像注释信息 ===
    St_EOImageParasIS.St_ImageTime.U1_Year        = image_paras_transit->IMAGE_date_year;
    St_EOImageParasIS.St_ImageTime.U1_Month       = image_paras_transit->IMAGE_date_mounth;
    St_EOImageParasIS.St_ImageTime.U1_Day         = image_paras_transit->IMAGE_date_day;
    St_EOImageParasIS.St_ImageTime.U1_Hour        = image_paras_transit->IMAGE_time_hour;
    St_EOImageParasIS.St_ImageTime.U1_Minute      = image_paras_transit->IMAGE_time_minute;
    St_EOImageParasIS.St_ImageTime.U1_Second      = image_paras_transit->IMAGE_time_second;
    St_EOImageParasIS.St_ImageTime.U2_Millisecond = image_paras_transit->IMAGE_time_ms;
    St_EOImageParasIS.U4_ImgId                    = image_paras_transit->IMG_ID;                 // 图像帧编号
    St_EOImageParasIS.U2_EOCycleNo                = image_paras_transit->A818_CycleNo;           // 成像周期内序号
    St_EOImageParasIS.U2_LineNo                   = image_paras_transit->A818_LineNo;            // 条带序号
    St_EOImageParasIS.U2_EO_LineNo                = image_paras_transit->A818_EO_LineNo;         // 条带内序号
    St_EOImageParasIS.U4_WideCover                = image_paras_transit->A818_WideCover;         // 收容宽度(m)
    St_EOImageParasIS.F4_ELLOS_deg_BODY           = St_EOImageShowArea.F4_ELLOS_deg_BODY;        // 视场中心俯仰角(deg)
    St_EOImageParasIS.F4_AZLOS_deg_BODY           = St_EOImageShowArea.F4_AZLOS_deg_BODY;        // 视场中心方位角(deg)
    St_EOImageParasIS.F4_verticalCover_deg        = St_EOImageShowArea.F4_verticalCover_deg;     // 视场大小俯仰(deg)
    St_EOImageParasIS.F4_horizontalCover_deg      = St_EOImageShowArea.F4_horizontalCover_deg;   // 视场大小方位(deg)
    St_EOImageParasIS.U1_CouseTgtCover            = image_paras_transit->A818_Couse_tgt_cover;   // 航向重叠率 默认20%
    St_EOImageParasIS.U1_BesideTgtCover           = image_paras_transit->A818_Beside_tgt_cover;  // 傍向重叠率 默认20%
    St_EOImageParasIS.U2_CurResolution            = image_paras_transit->A818_CUR_RESOLUTION;    // 像元分辨率(m, LSB=0.01)
    St_EOImageParasIS.U2_GroundResolution         = image_paras_transit->A818_GROUND_RESOLUTION; // 地面摄影分辨率(m, LSB=0.01)
    // 图像中心经纬高 - 从注释信息获取
    // todo: 确认单位
    St_EOImageParasIS.St_ImgCenterPosition.D8_Longitude_deg_CGCS = image_paras_transit->image_center_longitude._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgCenterPosition.D8_Latitude_deg_CGCS  = image_paras_transit->image_center_latitude._latitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgCenterPosition.F4_AltitudeAsl_m_CGCS = image_paras_transit->A818_ImageCenterHeight;
    // 图像四角经纬度 - 从注释信息获取
    St_EOImageParasIS.St_ImgLeftUp.D8_Longitude_deg_CGCS    = image_paras_transit->upleft_longitude._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgLeftUp.D8_Latitude_deg_CGCS     = image_paras_transit->upleft_latitude._latitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgLeftDown.D8_Longitude_deg_CGCS  = image_paras_transit->downleft_longitude._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgLeftDown.D8_Latitude_deg_CGCS   = image_paras_transit->downleft_latitude._latitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgRightUp.D8_Longitude_deg_CGCS   = image_paras_transit->upright_longitude._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgRightUp.D8_Latitude_deg_CGCS    = image_paras_transit->upright_latitude._latitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgRightDown.D8_Longitude_deg_CGCS = image_paras_transit->downright_longitude._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgRightDown.D8_Latitude_deg_CGCS  = image_paras_transit->downright_latitude._latitude * 0.00001 * mrad_to_deg;

    St_EOImageParasIS.U2_TakeTimes    = image_paras_transit->A818_EO_TakeTimes;    // 照相次数
    St_EOImageParasIS.U2_FocalLength  = image_paras_transit->A818_EO_FocalLength;  // 相机焦距(mm)
    St_EOImageParasIS.U2_ExposureTime = image_paras_transit->A818_EO_ExposureTime; // 曝光时间(us)

    St_EOImageParasIS.U1_ImpotentTag = 2; // 重要目标标识 0-不重要 //todo: 确认填充规则

    St_EOImageParasIS.St_ImgCenter.D8_Longitude_deg_CGCS = image_paras_transit->REGION_CENTER_X._longitude * 0.00001 * mrad_to_deg;
    St_EOImageParasIS.St_ImgCenter.D8_Latitude_deg_CGCS  = image_paras_transit->REGION_CENTER_Y._latitude * 0.00001 * mrad_to_deg;

    // 载机信息
    static Position           St_EntityPosition;          // @ID(0)
    static LinearVelocity     St_EntityLinearVelocit;     // @ID(1)
    static LinearAcceleration St_EntityLinearAcceleratio; // @ID(2)
    static Attitude           St_EntityAttitude;          // @ID(3)
    // 载机位置
    St_EntityPosition.D8_Longitude_deg_CGCS = ac_ins_info->AC_data_start.ac_position_data._longitude * 0.00001 * mrad_to_deg;
    St_EntityPosition.D8_Latitude_deg_CGCS  = ac_ins_info->AC_data_start.ac_position_data._latitude * 0.00001 * mrad_to_deg;
    St_EntityPosition.F4_AltitudeAsl_m_CGCS = ac_ins_info->AC_data_start.ac_height._altitude * 0.01;
    // 载机速度
    St_EntityLinearVelocit.F4_VelocityNorth_mDs_NED = ac_ins_info->AC_data_start.Vel_North._velocity * 0.0001;
    St_EntityLinearVelocit.F4_VelocityEast_mDs_NED  = ac_ins_info->AC_data_start.Vel_East._velocity * 0.0001;
    St_EntityLinearVelocit.F4_VelocityUp_mDs_NED    = ac_ins_info->AC_data_start.Vel_Up._velocity * 0.0001;
    // 载机加速度
    St_EntityLinearAcceleratio.F4_AccelerationNorth_mDs2_NED = ac_ins_info->AC_data_start.ac_accel_North._acceleration * 0.0001;
    St_EntityLinearAcceleratio.F4_AccelerationEast_mDs2_NED  = ac_ins_info->AC_data_start.ac_accel_East._acceleration * 0.0001;
    St_EntityLinearAcceleratio.F4_AccelerationUp_mDs2_NED    = ac_ins_info->AC_data_start.ac_accel_Up._acceleration * 0.0001;
    // 载机姿态
    // todo:确认 航向、俯仰、横滚 对应共享内存中的哪个变量
    St_EntityAttitude.F4_Psi_deg   = ac_ins_info->AC_data_start.ac_true_heading._angle_mrad * 0.001 * mrad_to_deg; // 航向角
    St_EntityAttitude.F4_Theta_deg = ac_ins_info->AC_data_start.ac_pitch._angle_mrad * 0.001 * mrad_to_deg;        // 俯仰角
    St_EntityAttitude.F4_Phi_deg   = ac_ins_info->AC_data_start.ac_roll._angle_mrad * 0.001 * mrad_to_deg;         // 横滚角
    // 赋值载机信息
    St_EOImageParasIS.St_AcParas.St_EntityPosition          = St_EntityPosition;
    St_EOImageParasIS.St_AcParas.St_EntityLinearVelocit     = St_EntityLinearVelocit;
    St_EOImageParasIS.St_AcParas.St_EntityLinearAcceleratio = St_EntityLinearAcceleratio;
    St_EOImageParasIS.St_AcParas.St_EntityAttitude          = St_EntityAttitude;
    // 图像任务信息
    St_EOImageParasIS.Seq_Mission.resize(sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    memcpy(St_EOImageParasIS.Seq_Mission.data(), &mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras,
           sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    // === EOImageParasIS 图像注释信息 === End

    // === EOImageModifyPara 光电图像调节参数 ===
    // todo: 确认填充内容是否正确
    St_EOImageModifyPara.I1_LightValueLight     = static_cast<char>(cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_value); // 可见光调光值
    St_EOImageModifyPara.I1_FocusValueLight     = static_cast<char>(cmd_From_FC.irst_cmd_param_IR_image_paras_light.focus_value); // 可见光调焦值
    St_EOImageModifyPara.U1_LightMistEliminate  = mess_From_TG.KJImg_ReMoveMist_back == 0 ? 2 : 1;                                // 可见光去雾 0-NA，1-ON，2-OFF
    St_EOImageModifyPara.U1_LightEnhance_Mode   = mess_From_TG.KJImg_EnHance_back == 0 ? 2 : 1;                                   // 可见光增强 0-NA，1-ON，2-OFF
    St_EOImageModifyPara.I1_LightValueInfrared  = static_cast<char>(cmd_From_FC.irst_cmd_param_IR_image_paras_infra.light_value); // 红外调光值
    St_EOImageModifyPara.I1_FocusValueInfrared  = static_cast<char>(cmd_From_FC.irst_cmd_param_IR_image_paras_infra.focus_value); // 红外调焦值
    St_EOImageModifyPara.U1_VideoPolar          = mess_From_TG.HWImg_Ply_back == 1 ? 1 : 2;                                       // 极性 0-NA，1-白热，2-黑热
    St_EOImageModifyPara.U1_InfraredEnhanceMode = mess_From_TG.HWImg_EnHance_back == 0 ? 2 : 1;                                   // 红外增强 0-NA，1-ON，2-OFF
    // === EOImageModifyPara 光电图像调节参数 === END

    // === EOTgtPara 动目标检测成像参数 ===
    // 暂时填充默认值，后续可根据目标跟踪信息填充
    for (int i = 0; i < 5; i++) {
        EntityID St_EntityID;
        St_EntityID.U4_EntityID      = 0; // todo: 都是什么意义？
        St_EntityID.U2_GenID         = 0;
        Arr_EOTgtPara[i].St_EntityID = St_EntityID;
    }

    shm_output_.m_SecEOImageDriveMsg.St_SMMessageHeader   = St_MessageHeader;
    shm_output_.m_SecEOImageDriveMsg.St_EOImageState      = St_EOImageState;
    shm_output_.m_SecEOImageDriveMsg.St_EOImageShowArea   = St_EOImageShowArea;
    shm_output_.m_SecEOImageDriveMsg.St_EOImageParasIS    = St_EOImageParasIS;
    shm_output_.m_SecEOImageDriveMsg.St_EOImageModifyPara = St_EOImageModifyPara;
    memcpy(shm_output_.m_SecEOImageDriveMsg.Arr_EOTgtPara, Arr_EOTgtPara, sizeof(Arr_EOTgtPara));
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

            // 队列 初始化
            sq::sq_IRST_act_req.clearAndNotify();
            sq::sq_others.clearAndNotify();

            // 设备中的初始化参数
            param_Init();

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

        // 测试模式选择：广域成像=1, 区域成像=2, 区域监视=3
        // const int test_mode = 1;
        const int test_mode = 3;

        // 通用导航数据设置函数
        auto setNavData = [this]() {
            // ===================== temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED 数据填充 =====================
            // 反推填充 temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED
            // 参考 fpga_sim.cpp 中的转换公式进行反推

            // 时间数据（当前时间）
            auto now    = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto tm     = *std::localtime(&time_t);
            // 把 tm 改成今天 0 点
            tm.tm_hour = 0;
            tm.tm_min  = 0;
            tm.tm_sec  = 0;
            // 今天 0 点（system_clock::time_point）
            auto today_midnight = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            // 距离今天 0 点的纳秒数
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - today_midnight).count();

            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_year  = tm.tm_year + 1900;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_month = tm.tm_mon + 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_day   = tm.tm_mday;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.time_gnss_calendartime            = nanoseconds;

            // todo: 还是不太对
            temp_mess_FromFc_SYM_TIME_REPORT.time_calendartime            = nanoseconds;
            temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_year  = tm.tm_year + 1900;
            temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_month = tm.tm_mon + 1;
            temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_day   = tm.tm_mday;

            // 位置数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._longitude = 102.54 * deg_to_mrad / 0.00001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._latitude  = 30.05 * deg_to_mrad / 0.00001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_alt._altitude            = 17000.0 / 0.01;

            // 姿态数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_true_heading._angle_mrad = 90.0 * deg_to_mrad / 0.001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_pitch._angle_mrad        = 0.0 * deg_to_mrad / 0.001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_roll._angle_mrad         = 0.0 * deg_to_mrad / 0.001;

            // 速度数据反推
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_North._velocity  = 0.0 / 0.0001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_West._velocity   = -180.0 / 0.0001;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_ground_speed._velocity = 0.0 / 0.0001;

            // 设置数据有效性标志
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_position      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_GNSS_alt      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_north     = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_west      = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_ground_speed  = 1;
            temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_CNI_GNSS_time = 1;
        };

        // 广域成像参数设置
        auto setParamsWideImage = [this, &setNavData]() {
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

            // 设置导航数据
            setNavData();
        };

        // 区域监视参数设置
        auto setParamsAreaMonitor = [this, &setNavData]() {
            // 设置参数 - 参考 prepare_Model_WorkControl 流程
            // ===================== 成像模式参数 =====================
            // 成像模式：区域监视 (1=广域, 2=区域成像, 3=区域监视)
            cmd_From_FC.irst_cmd_param_irst_form_mode = V_IRST_FORM_MODE_AREA_MONI;
            main_Control_State_Param.irst_form_mode   = V_IRST_FORM_MODE_AREA_MONI;

            // 区域监视参数有效
            cmd_From_FC.irst_cmd_param_area_monitor_paras_validity = 1;

            const float lon = 102.54;
            const float lat = 31.0;
            const float alt = 300.0;

            // 区域监视参数设置 - 中心点经纬高 (ICD格式)
            // 目标中心点经度 (单位: 0.00001 mrad)
            cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude =
                static_cast<INT32>(lon * deg_to_mrad / 0.00001);
            // 目标中心点纬度 (单位: 0.00001 mrad)
            cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude =
                static_cast<INT32>(alt * deg_to_mrad / 0.00001);
            // 目标中心点高度 (单位: 0.01 m)
            cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._altitude =
                static_cast<INT32>(alt / 0.01);

            // 区域监视修改标识 - 标识所有参数都已修改
            cmd_From_FC.irst_cmd_param_area_monitor_paras.area_monitor_paras_mark.HEIGHT_CHG = 1;
            cmd_From_FC.irst_cmd_param_area_monitor_paras.area_monitor_paras_mark.LATI_CHG   = 1;
            cmd_From_FC.irst_cmd_param_area_monitor_paras.area_monitor_paras_mark.LONG_CHG   = 1;

            // 同步到计算参数结构体 (COMP格式, 单位: mrad/m)
            param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude = lon * deg_to_mrad;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude  = lat * deg_to_mrad;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude  = alt;

            // 设置导航数据
            setNavData();
        };

        // 准备
        log_once("[CameraSimulator] 设置准备");
        while (running_photoing_test) {
            // 根据测试模式设置参数
            switch (test_mode) {
            case 1:
                setParamsWideImage();
                break;
            case 3:
                setParamsAreaMonitor();
                break;
            }

            // act_req_IRST_Process();
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
            // 根据测试模式设置参数
            switch (test_mode) {
            case 1:
                setParamsWideImage();
                break;
            case 3:
                setParamsAreaMonitor();
                break;
            }

            // act_req_IRST_Process();
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
