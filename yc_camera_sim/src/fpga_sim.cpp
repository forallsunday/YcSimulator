#include <fpga_sim.h>
#include <global_vars.h>
#include <YC_Controller_Computer.h>
#include <YC_Controller_globalVal_Ext.h>

#include <log_def.h>

using namespace std::chrono;

static std::atomic<int> speed_or_locate{1}; // 速度位置信号 (0=速度, 1=位置) 不工作时都是位置

int gpio0AIn(int code) {
    if (code == 4) {
        return speed_or_locate;
    } else {
        return -1;
    }
};

FpgaSimulator::FpgaSimulator() {}

FpgaSimulator::~FpgaSimulator() {
    stop();
}

bool FpgaSimulator::init() {
    using namespace std::chrono;
    // 5ms 周期定时器
    timer_5ms_.init(milliseconds(5), [this]() { onInterrupt(); });

    // 速度位置信号计时器
    timer_switch_.init(milliseconds(50), [this]() { onSwitchSpeedOrLocate(); });
    // 初始化默认温度值 (室温环境: 约20℃)
    setPrimaryMirrorTemp(200);   // 主镜温度 20.0℃
    setSecondaryMirrorTemp(200); // 次镜温度 20.0℃
    setTempID(1);                // 温度ID初始为1


    return true;
}

void FpgaSimulator::start() {
    timer_5ms_.start();
}

void FpgaSimulator::stop() {
    timer_5ms_.stop();
    timer_switch_.stop();
}

void FpgaSimulator::onInterrupt() {
    // Note: fpga 读写模拟

    // std::lock_guard<std::mutex> lock(mutex_fpga); // 上锁

    // 各分系统变量赋值
    this->simulatingDY();
    this->simulatingKJ();
    this->simulatingTJ();
    this->simulatingTG();
    this->simulatingTXCL();
    this->simulatingPCS();
    this->simulatingGCWK(); // 光窗温控模拟

    // 仿真曝光时刻flag=1
    this->simulatingExposure();
    // 仿真伺服运动
    this->simulatingMotionKJ();
    // 速度位置信号定时器是否启动 (顺序需要放在判断曝光时刻之后)
    simulatingTimerSpeedOrLocate();

    //------------设置标志位------------------------
    // 中断响应标志位
    flag_Fpga_Interrupt = 1;
    // fpga掉线次数清零
    flag_Fpga_down_times = 0;
}

void FpgaSimulator::onSwitchSpeedOrLocate() {
    // log_proc("当前是%s信号, 周期=%dms, elapsedTime=%dms",
    //          speed_or_locate == 0 ? "速度" : "位置", period_switcher_.count(), (int)timer_switch_.elapsedTimeMs());
}

void FpgaSimulator::simulatingTimerSpeedOrLocate() {
    // 如果是拍照命令且成像模式为广域成像或区域成像 则启动速度位置信号定时器
    if (mess_To_FPGA.cmd == FPGA_START_PHOTO &&
        (mess_To_FPGA.irst_form_mode == FPGA_GY_PHOTO || mess_To_FPGA.irst_form_mode == FPGA_QY_PHOTO)) {
        // 如果定时器没有running
        if (!timer_switch_.isRunning()) {
            speed_or_locate  = 1;
            period_switcher_ = milliseconds(666); // 等待一小段时间以正常计时
            timer_switch_.changePeriod(period_switcher_);
            timer_switch_.start();
            log_proc("开始速度位置信号计时器");
        }
    } else {
        // 停止定时器
        this->timer_switch_.stop();
    }

    // 如果定时器在运行
    if (timer_switch_.isRunning()) {
        std::lock_guard<std::mutex> lock(mutex_period_);
        // 处理速度位置信号切换请求
        if (timer_switch_.elapsedTimeMs() >= period_switcher_.count())
        // 如果走过的时间超过周期了
        {
            if (speed_or_locate == 0) {
                // 当前为速度信号
                period_switcher_ = milliseconds((int)param_Compute_Output.toFPGA_time_location);
                timer_switch_.changePeriod(period_switcher_);
                timer_switch_.start();
                speed_or_locate = 1;
                log_proc("切换到位置信号, 周期=%d ms", period_switcher_.count());
            } else {
                // 当前为位置信号
                period_switcher_ = milliseconds((int)param_Compute_Output.toFPGA_time_speed);
                timer_switch_.changePeriod(period_switcher_);
                timer_switch_.start();
                speed_or_locate = 0;
                log_proc("切换到速度信号, 周期=%d ms", period_switcher_.count());
            }
        }
    }
}

void FpgaSimulator::simulatingMotionKJ() {

    switch (mess_To_KJ.cmd) {
    case KJ_CMD_WAIT:
    case KJ_CMD_ZHNBEI:
    case KJ_CMD_STOP:
        return; // 不运动
        break;
    }

    static int count = 0; // 5ms计数 当变为位置信号即框架回程时清零

    if (speed_or_locate == 1) {
        count = 0;
    } else {
        count++;
    }

    // YC_Controller_Computer.cpp
    // KJAgl_pi.WKJ     = param_Compute_Input_Fromfpga.rtime_direction_frame * Agl_PI;       // 实时外框架角
    // KJAgl_pi.NKJ     = (param_Compute_Input_Fromfpga.rtime_pitch_frame + 90) * Agl_PI;    // 实时内框架角
    // KJAgl_exp_pi.WKJ = param_Compute_Input_Fromfpga.exposure_direction_frame * Agl_PI;    // 曝光时刻外框架角
    // KJAgl_exp_pi.NKJ = (param_Compute_Input_Fromfpga.exposure_pitch_frame + 90) * Agl_PI; // 曝光时刻内框架角

    // YC_Controller_Mess_Process.cpp
    // param_Compute_Input_Fromfpga.rtime_pitch_frame        = mess_From_KJ.rtime_pitch_frame * 0.0001;        // 框架实时俯仰角（LSB = 0.0001°)
    // param_Compute_Input_Fromfpga.rtime_direction_frame    = mess_From_KJ.rtime_direction_frame * 0.0001;    // 框架实时方位角（LSB = 0.0001°)
    // param_Compute_Input_Fromfpga.exposure_pitch_frame     = mess_From_KJ.exposure_pitch_frame * 0.0001;     // 框架曝光时刻俯仰角（LSB = 0.0001°)
    // param_Compute_Input_Fromfpga.exposure_direction_frame = mess_From_KJ.exposure_direction_frame * 0.0001; // 框架曝光时刻方位角（LSB = 0.0001°)
    // param_Compute_Input_Fromfpga.kfbgskfybcwz             = mess_From_KJ.kfbgskfybcwz * 0.0001;             // 快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
    // param_Compute_Input_Fromfpga.kfbgskfwbcwz             = mess_From_KJ.kfbgskfwbcwz * 0.0001;             // 快反曝光时刻方位补偿位置（LSB = 0.0001°)

    // param_Compute_Output.toKJ_pitch_start = KJ_start_pi.NKJ * PI_Agl - 90; // 框架俯仰指令   起始角 °

    float pitch_start     = param_Compute_Output.toKJ_pitch_start;
    float pitch_end       = param_Compute_Output.toKJ_pitch_end;
    float direction_start = param_Compute_Output.toKJ_direction_start;
    float direction_end   = param_Compute_Output.toKJ_direction_end;
    float pitch_speed     = param_Compute_Output.toKJ_pitch_speed;
    float direction_speed = param_Compute_Output.toKJ_direction_speed;

    constexpr float interval = 5e-3f; // 5ms

    // todo: 加随机数
    // 框架实时俯仰角（LSB = 0.0001°)
    mess_From_KJ.rtime_pitch_frame = 1e4 * (pitch_start + count * interval * pitch_speed);
    mess_From_KJ.rtime_pitch_frame = std::min(mess_From_KJ.rtime_pitch_frame, (int32_t)(1e4 * pitch_start));
    // 框架实时方位角（LSB = 0.0001°)
    mess_From_KJ.rtime_direction_frame = 1e4 * (direction_start + count * interval * direction_speed);
    mess_From_KJ.rtime_direction_frame = std::min(mess_From_KJ.rtime_direction_frame, (int32_t)(1e4 * direction_end));

    if (flag_Fpga_bg) {
        // 框架曝光时刻俯仰角（LSB = 0.0001°)
        mess_From_KJ.exposure_pitch_frame = mess_From_KJ.rtime_pitch_frame;
        // 框架曝光时刻方位角（LSB = 0.0001°)
        mess_From_KJ.exposure_direction_frame = mess_From_KJ.rtime_direction_frame;
    }

    // todo: 快反
}

void FpgaSimulator::simulatingPCS() {

    // // PCS惯导消息处理----------------------------------------------------------------------------
    // param_Compute_Input_Fromfpga.longitude    = mess_From_PCS_DATA.longitude * PI / pow(2, 31);    // 经度LSB=π/2^31---1
    // param_Compute_Input_Fromfpga.latitude     = mess_From_PCS_DATA.latitude * PI / pow(2, 31);     // 纬度LSB=π/2^31---1
    // param_Compute_Input_Fromfpga.altitude     = mess_From_PCS_DATA.altitude * 0.001;               // 高度 有符号数(-500m~25000m)， LSB=0.001m---1
    // param_Compute_Input_Fromfpga.true_heading = mess_From_PCS_DATA.true_heading * PI / pow(2, 31); // 真航向   有符号数(-π~+π)，LSB=π/2^31rad---1
    // param_Compute_Input_Fromfpga.pitch        = mess_From_PCS_DATA.pitch * PI / pow(2, 31);        // 俯仰角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    // param_Compute_Input_Fromfpga.roll         = mess_From_PCS_DATA.roll * PI / pow(2, 31);         // 横滚角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    // param_Compute_Input_Fromfpga.north_speed  = mess_From_PCS_DATA.north_speed * 0.001;            // 北向速度  有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    // param_Compute_Input_Fromfpga.east_speed   = mess_From_PCS_DATA.east_speed * 0.001;             // 东向速度	 有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    // param_Compute_Input_Fromfpga.ground_speed = mess_From_PCS_DATA.ground_speed * 0.001;           // 地向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1

    // ===== PCS 数据填充（直接来自 temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED）=====
    auto &fused = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED;

    uint32_t h, min, sec, ms;
    // 解析时间函数
    auto parseTime = [&h, &min, &sec, &ms](uint64_t calendartime) {
        constexpr uint64_t NS_PER_MS     = 1000000ULL;
        constexpr uint64_t NS_PER_SECOND = 1000000000ULL;
        constexpr uint64_t NS_PER_MINUTE = 60ULL * NS_PER_SECOND;
        constexpr uint64_t NS_PER_HOUR   = 3600ULL * NS_PER_SECOND;

        uint64_t ns = calendartime;

        h = ns / NS_PER_HOUR;
        ns %= NS_PER_HOUR;
        min = ns / NS_PER_MINUTE;
        ns %= NS_PER_MINUTE;
        sec = ns / NS_PER_SECOND;
        ms  = (ns % NS_PER_SECOND) / NS_PER_MS;
    };
    parseTime(fused.satellite_nav_data.time_gnss_calendartime);
    // 时间
    mess_From_PCS_DATA.time_year   = fused.satellite_nav_data.date_gnss_calendartime.date_year;
    mess_From_PCS_DATA.time_mounth = fused.satellite_nav_data.date_gnss_calendartime.date_month;
    mess_From_PCS_DATA.time_day    = fused.satellite_nav_data.date_gnss_calendartime.date_day;
    mess_From_PCS_DATA.time_hour   = h;
    mess_From_PCS_DATA.time_min    = min;
    mess_From_PCS_DATA.time_s      = sec;
    mess_From_PCS_DATA.time_ms     = ms;

    // 位置 (弧度)
    mess_From_PCS_DATA.longitude = fused.satellite_nav_data.ac_gnss_position_data._longitude * 0.00001 * 1e-3 / PI * pow(2, 31);
    mess_From_PCS_DATA.latitude  = fused.satellite_nav_data.ac_gnss_position_data._latitude * 0.00001 * 1e-3 / PI * pow(2, 31);
    mess_From_PCS_DATA.altitude  = fused.satellite_nav_data.ac_GNSS_alt._altitude * 0.01 / 0.001;
    // todo: 检查以上altitude单位

    // 姿态
    mess_From_PCS_DATA.true_heading = fused.ac_flight_vector.ac_true_heading._angle_mrad * 0.001 * 1e-3 / PI * pow(2, 31);
    mess_From_PCS_DATA.pitch        = fused.ac_flight_vector.ac_pitch._angle_mrad * 0.001 * 1e-3 / PI * pow(2, 31);
    mess_From_PCS_DATA.roll         = fused.ac_flight_vector.ac_roll._angle_mrad * 0.001 * 1e-3 / PI * pow(2, 31);

    // 速度
    mess_From_PCS_DATA.north_speed  = fused.ac_flight_vector.ac_plat_vel.Vel_North._velocity * 0.0001 / 0.001;
    mess_From_PCS_DATA.east_speed   = -1 * fused.ac_flight_vector.ac_plat_vel.Vel_West._velocity * 0.0001 / 0.001;
    mess_From_PCS_DATA.ground_speed = fused.satellite_nav_data.ac_GNSS_ground_speed._velocity * 0.0001 / 0.001;

    // 设置状态
    mess_From_PCS_DATA.status_sbzt   = 0; // 正常
    mess_From_PCS_DATA.status_gdgzms = 3; // 0：装订对准	1：地面静态对准	2：空中飞行对准	3：导航	4：自检中	判断数据可用：3
}

void FpgaSimulator::simulatingExposure() {
    static int cnt_i         = 0; // 中断次数计数
    static int num_in_stripe = 0; // 条带内曝光次数
    static bool focal_pos_initialized = false; // 焦面位置初始化标志

    // 计算帧间隔时间
    switch (mess_To_FPGA.irst_form_mode) {
    case FPGA_GY_PHOTO:
        frame_interval = 1000.0f / 15;
        break;
    case FPGA_QY_PHOTO: // 区域成像帧频 15hz
        frame_interval = 1000.0f / 15;
        break;
    case FPGA_QY_VIDEO: // 区域监视帧频 24hz
        frame_interval = 1000.0f / 24;
        break;
    case FPGA_JTJ_PHOTO:
        frame_interval = 1000.0f / 30;
        break;
    default:
        frame_interval = 1000.0f / 24;
    }

    switch (mess_To_FPGA.cmd) {
    case FPGA_START_PHOTO:
        // 首次拍照时设置焦面位置默认值
        if (!focal_pos_initialized) {
            setVisibleFocalPlanePosition(0);  // 可见光焦面位置默认0mm
            setInfraredFocalPlanePosition(0); // 红外焦面位置默认0mm
            focal_pos_initialized = true;
        }
        switch (mess_To_FPGA.irst_form_mode) {
        case FPGA_GY_PHOTO:
        case FPGA_QY_PHOTO: // 区域成像帧频 15hz
            // 广域 区域 成像
            if (speed_or_locate == 1) {
                // 位置信号时不触发曝光
                flag_Fpga_bg  = 0;
                cnt_i         = 0;
                num_in_stripe = 0; // 一个条带拍完了
            } else {
                // 速度信号时
                if (num_in_stripe < mess_To_FPGA.frames_Num) {
                    // 如果曝光次数小于条带内帧数
                    cnt_i++;
                    if (cnt_i * 5 >= frame_interval) {
                        // 到达间隔时间，触发一次曝光 (传到主控后 流程中会置0)
                        // log_proc("bg, num_interrupt=%d", cnt_i);
                        // log_proc("elapsed time after this exposure: %d ms", (int)this->timer_switch_.elapsedTimeMs());
                        flag_Fpga_bg = 1;
                        num_in_stripe++; // 条带内曝光次数+1
                        // 计数器清零
                        cnt_i = 0;
                    }
                }
            }
            break;
        case FPGA_QY_VIDEO:
            cnt_i++;
            if (cnt_i * 5 >= frame_interval) {
                // 到达间隔时间，触发一次曝光 (传到主控后 流程中会置0)
                flag_Fpga_bg = 1;
                // 计数器清零
                cnt_i = 0;
            }
            break;

        default:
            break;
        }

        break;

    case FPGA_STOP_PHOTO:
        cnt_i        = 0;
        flag_Fpga_bg = 0;
        break;

    default:
        break;
    }
}

void FpgaSimulator::simulatingDY() {
    // 电源
    // mess_To_DY.work_mode = work_mode; // 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
    // 电源开关字
    // mess_From_DY.state_szgd   = mess_To_DY.cmd_szgd;   // 数字供电0：关 1：开
    // mess_From_DY.state_glgd   = mess_To_DY.cmd_glgd;   // 功率供电0：关 1：开
    // mess_From_DY.state_rkbjgd = mess_To_DY.cmd_rkbjgd; // 热控供电本机：0：关 1：开
    // mess_From_DY.state_rkgcgd = mess_To_DY.cmd_rkgcgd; // 热控供电光窗：0：关 1：开
    switch (mess_To_DY.work_mode) {
    case 0:
        mess_From_DY.state_szgd   = 0;
        mess_From_DY.state_glgd   = 0;
        mess_From_DY.state_rkbjgd = 0;
        mess_From_DY.state_rkgcgd = 0;
        break;
    case 3:
        mess_From_DY.state_szgd   = 1;
        mess_From_DY.state_glgd   = 1;
        mess_From_DY.state_rkbjgd = 1;
        mess_From_DY.state_rkgcgd = 1;
        break;
    }
}

void FpgaSimulator::simulatingTXCL() {
    // 根据命令设置状态
    // 参考 make_Mess_To_TXCL_CMD 中设置的命令和参数
    switch (mess_To_TXCL_CMD.cmd) {
    case TX_CMD_EMPTY: // 空指令
        break;
    case TX_CMD_TRACK:                        // 跟踪
        mess_From_TXCL.state1_trackstate = 1; // 稳定跟踪
        // 填充跟踪目标像素坐标 - 从共享内存输入获取
        mess_From_TXCL.tg_valid = 1; // 跟踪有效
        mess_From_TXCL.tg_count = tracking_target_count_;
        // 目标1像素坐标
        mess_From_TXCL.tgt1_upleft_x    = target_pixel_coor_[0].up_left_x;
        mess_From_TXCL.tgt1_upleft_Y    = target_pixel_coor_[0].up_left_y;
        mess_From_TXCL.tgt1_downright_x = target_pixel_coor_[0].down_right_x;
        mess_From_TXCL.tgt1_downright_y = target_pixel_coor_[0].down_right_y;
        // 目标2像素坐标
        mess_From_TXCL.tgt2_upleft_x    = target_pixel_coor_[1].up_left_x;
        mess_From_TXCL.tgt2_upleft_Y    = target_pixel_coor_[1].up_left_y;
        mess_From_TXCL.tgt2_downright_x = target_pixel_coor_[1].down_right_x;
        mess_From_TXCL.tgt2_downright_y = target_pixel_coor_[1].down_right_y;
        // 目标3像素坐标
        mess_From_TXCL.tgt3_upleft_x    = target_pixel_coor_[2].up_left_x;
        mess_From_TXCL.tgt3_upleft_Y    = target_pixel_coor_[2].up_left_y;
        mess_From_TXCL.tgt3_downright_x = target_pixel_coor_[2].down_right_x;
        mess_From_TXCL.tgt3_downright_y = target_pixel_coor_[2].down_right_y;
        // 目标4像素坐标
        mess_From_TXCL.tgt4_upleft_x    = target_pixel_coor_[3].up_left_x;
        mess_From_TXCL.tgt4_upleft_Y    = target_pixel_coor_[3].up_left_y;
        mess_From_TXCL.tgt4_downright_x = target_pixel_coor_[3].down_right_x;
        mess_From_TXCL.tgt4_downright_y = target_pixel_coor_[3].down_right_y;
        // 目标5像素坐标
        mess_From_TXCL.tgt5_upleft_x    = target_pixel_coor_[4].up_left_x;
        mess_From_TXCL.tgt5_upleft_Y    = target_pixel_coor_[4].up_left_y;
        mess_From_TXCL.tgt5_downright_x = target_pixel_coor_[4].down_right_x;
        mess_From_TXCL.tgt5_downright_y = target_pixel_coor_[4].down_right_y;
        break;
    case TX_CMD_STOP_TRACK:                   // 停止跟踪
        mess_From_TXCL.state1_trackstate = 0; // 未跟踪
        // 清除跟踪目标像素坐标
        mess_From_TXCL.tg_valid         = 0;
        mess_From_TXCL.tg_count         = 0;
        mess_From_TXCL.tgt1_upleft_x    = 0;
        mess_From_TXCL.tgt1_upleft_Y    = 0;
        mess_From_TXCL.tgt1_downright_x = 0;
        mess_From_TXCL.tgt1_downright_y = 0;
        mess_From_TXCL.tgt2_upleft_x    = 0;
        mess_From_TXCL.tgt2_upleft_Y    = 0;
        mess_From_TXCL.tgt2_downright_x = 0;
        mess_From_TXCL.tgt2_downright_y = 0;
        mess_From_TXCL.tgt3_upleft_x    = 0;
        mess_From_TXCL.tgt3_upleft_Y    = 0;
        mess_From_TXCL.tgt3_downright_x = 0;
        mess_From_TXCL.tgt3_downright_y = 0;
        mess_From_TXCL.tgt4_upleft_x    = 0;
        mess_From_TXCL.tgt4_upleft_Y    = 0;
        mess_From_TXCL.tgt4_downright_x = 0;
        mess_From_TXCL.tgt4_downright_y = 0;
        mess_From_TXCL.tgt5_upleft_x    = 0;
        mess_From_TXCL.tgt5_upleft_Y    = 0;
        mess_From_TXCL.tgt5_downright_x = 0;
        mess_From_TXCL.tgt5_downright_y = 0;
        break;
    case TX_CMD_IMAGE_GY:                  // 广域成像
        mess_From_TXCL.state1_kjtxchs = 1; // 可见图像正在传输
        mess_From_TXCL.state1_hwtxchs = 1; // 红外图像正在传输
        break;
    case TX_CMD_IMAGE_VIEW: // 区域监视
        mess_From_TXCL.state1_kjtxchs = 1;
        mess_From_TXCL.state1_hwtxchs = 1;
        break;
    case TX_CMD_IMAGE_QY: // 区域成像
        mess_From_TXCL.state1_kjtxchs = 1;
        mess_From_TXCL.state1_hwtxchs = 1;
        break;
    case TX_CMD_IMAGE_TRANS:            // 传输图像/视频
        mess_From_TXCL.state3_kjsc = 1; // 可见输出
        mess_From_TXCL.state3_hwsc = 1; // 红外输出
        break;
    case TX_CMD_IMAGE_TRANS_STOP: // 停传图像/视频
        mess_From_TXCL.state3_kjsc = 0;
        mess_From_TXCL.state3_hwsc = 0;
        break;
    case TX_CMD_DJ: // 冻结
        break;
    case TX_CMD_SENSOR_SET: // 传感器设置
        // 根据 mess_To_TXCL_CMD.mode_IR_SENSOR 设置跟踪图像类型
        // 1=可见光，2=红外，3=可见+红外，4=红外+可见
        if (mess_To_TXCL_CMD.mode_IR_SENSOR == 1) {
            mess_From_TXCL.state1_trackvideo = 0; // 可见
        } else if (mess_To_TXCL_CMD.mode_IR_SENSOR == 2) {
            mess_From_TXCL.state1_trackvideo = 1; // 红外
        }
        break;
    case TX_CMD_VIDEO_BAND_SET: // 视频带宽设置
        // 视频带宽: 0=NA, 1=低(1.6M), 2=中(3.2M), 3=高(4.8M)
        // mess_To_TXCL_CMD.Video_BAND 由 cmd_From_FC.irst_cmd_param_IRST_Video_BAND 设置
        // 模拟：确认命令接收，回显命令字
        mess_From_TXCL.cmd = TX_CMD_VIDEO_BAND_SET;
        break;
    default:
        break;
    }

    // 设置故障状态 - 正常
    mess_From_TXCL.fault_bit0 = 0; // 图像处理模块内部电路正常
    mess_From_TXCL.fault_bit1 = 0; // 图像处理模块存储单元正常
    mess_From_TXCL.fault_bit2 = 0; // 输入可见图像信号正常
    mess_From_TXCL.fault_bit3 = 0; // 输入红外图像信号正常
    mess_From_TXCL.fault_bit4 = 0; // 存储单元未满
    mess_From_TXCL.fault_bit5 = 0; // 定位功能正常
    mess_From_TXCL.fault_bit6 = 0; // 识别功能正常

    // 设置剩余存储容量 - 未占用
    mess_From_TXCL.state3_txcckj = 0; // 存储空间未占用(余100%)
}

void FpgaSimulator::simulatingKJ() {
    // // 框架控制指令
    // #define KJ_CMD_WAIT 0x00   // 待机（空闲），停留在当前位置
    // #define KJ_CMD_CHECK 0x01  // 启动自检
    // #define KJ_CMD_ZHNBEI 0x02 // 准备，随动
    // #define KJ_CMD_STOP 0x03   // 停止工作，回零位
    // #define KJ_CMD_SCAN 0x04   // 摆扫
    // #define KJ_CMD_WATCH 0x05  // 凝视
    // #define KJ_CMD_TRACK 0x06  // 跟踪
    switch (mess_To_KJ.cmd) {
    case KJ_CMD_WAIT:
        mess_From_KJ.status_sub = 0; // 未开始
        break;
    case KJ_CMD_CHECK:
        mess_From_KJ.status_sub = 2; // 执行完成
        break;
    case KJ_CMD_ZHNBEI:
        mess_From_KJ.status_sub  = 2; // 正在执行
        mess_From_KJ.status_work = 0;
        break;
    case KJ_CMD_STOP:
        mess_From_KJ.status_sub  = 2; // 执行完成
        mess_From_KJ.status_work = 0;
        break;
    case KJ_CMD_SCAN:
        mess_From_KJ.status_sub  = 2;
        mess_From_KJ.status_work = KJ_WORK_STATE_SCAN; // 摆扫
        break;
    case KJ_CMD_WATCH:
        mess_From_KJ.status_sub  = 2;
        mess_From_KJ.status_work = KJ_WORK_STATE_WATCH; // 凝视
        break;
    case KJ_CMD_TRACK:
        // mess_From_KJ.status_sub  = 2;
        mess_From_KJ.status_work = KJ_WORK_STATE_TRACK; // 跟踪
        break;
    default:
        break;
    }

    // #define KJ_CMD_KF_MODE_EMPTY 0x00 // 0x00初始化值
    // #define KJ_CMD_KF_MODE_YZJ 0x05   // 0x05（快反从预置角补偿）广域成像、区域成像
    // #define KJ_CMD_KF_MODE_OWBC 0x0A  // 0x0A（快反从零位补偿）
    // #define KJ_CMD_KF_MODE_STOP 0xAA  // 0xAA（快反锁零）区域监视
}

void FpgaSimulator::simulatingTJ() {
    // 根据命令设置状态
    switch (mess_To_TJ.cmd) {
    case TJ_CMD_None:
        mess_From_TJ.state = 0; // 未开始
        break;
    case TJ_CMD_Collect:
        mess_From_TJ.state = 2;
        break;
    case TJ_CMD_CellBIT:
        mess_From_TJ.state        = 2;
        mess_From_TJ.status1_zjzt = 0;
        break;
    case TJ_CMD_HWJZ:
        mess_From_TJ.status2_jzb_dw = 1;
        break;
    case TJ_CMD_FlyFocus_Pre:
        mess_From_TJ.status1_djdw_kj = 1;
        mess_From_TJ.status2_bbj_dw  = 1;
        mess_From_TJ.status1_djdw_hw = 1;
        break;
    case TJ_CMD_FlyFocus:
        mess_From_TJ.status2_realtime_jj = 1;
        break;
    case TJ_CMD_Wait:
        mess_From_TJ.state = 2;
        break;

    default:
        mess_From_TJ.state = 0;
        break;
    }

    // 模拟大小视场切换反馈
    mess_From_TJ.state_bb = mess_To_TJ.control_bb; // 变倍状态跟随控制命令

    // 模拟调焦模式反馈
    mess_From_TJ.state_tjmode_kj = mess_To_TJ.control_tjmode_kj; // 可见调焦模式
    mess_From_TJ.state_tjmode_hw = mess_To_TJ.control_tjmode_hw; // 红外调焦模式
}

void FpgaSimulator::simulatingTG() {
    switch (mess_To_TG.Control_Cmd) {
    case TG_CMD_Light:
        switch (mess_To_FPGA.cmd) {
        case FPGA_STOP_PHOTO:
            mess_From_TG.JianGuang = 1;
            break;
        case FPGA_START_PHOTO:
            mess_From_TG.JianGuang = 2;
            // 直接赋值 调光完成 会使曝光时间没有计算 直接使用默认值
            // todo：是否需要在TG过程内所有变量均赋值让调光流程走通？
            break;
        }
        break;
    case TG_CMD_HWJZ:
        mess_From_TG.HWJiaoZheng    = 2; // 执行完校正
        mess_From_TJ.status2_jzb_dw = 0;
        break;
    case TG_CMD_FlyFocus:
        mess_From_TG.JianJiao_state = 1; // 调焦完成
        break;

    default:
        break;
    }
    // 模拟 可见光去雾、可见光增强、红外增强、红外极化
    // mess_To_TG.KJImg_ReMoveMist: 1=开,2=关 -> mess_From_TG.KJImg_ReMoveMist_back: 1=开,0=关
    mess_From_TG.KJImg_ReMoveMist_back = mess_To_TG.KJImg_ReMoveMist == 1 ? 1 : 0; // 可见光去雾
    mess_From_TG.KJImg_EnHance_back    = mess_To_TG.KJImg_EnHance == 1 ? 1 : 0;    // 可见光增强
    mess_From_TG.HWImg_EnHance_back    = mess_To_TG.HWImg_EnHance == 1 ? 1 : 0;    // 红外增强
    mess_From_TG.HWImg_Ply_back        = mess_To_TG.HWImg_Ply;                     // 红外极化(黑白热)
    // 模拟红外手动调光模式反馈
    // ICD: infrared_dim_mode: 1=自动, 2=手动, 0=NA -> HWTG_Mode_back: 0=自动, 1=手动
    // 仅当 infrared_dim_mode 不为 NA(0) 时才更新 HWTG_Mode_back，避免其他参数修改时误切换调光模式
    if (cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode != 0) {
        mess_From_TG.HWTG_Mode_back =
            cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode == 2 ? 1 : 0;
    }

    static uint64_t        cnt_cooling     = 0;
    static uint8_t         last_ref_switch = 0; // 上一次制冷开关状态
    static IRST_WORK_STATE last_irst_state = V_IRST_WORK_STATE_NA;
    static IRST_WORK_STATE current_irst_state;

    current_irst_state = main_Control_State_Param.irst_work_state;

    // 初始化状态
    if (V_IRST_WORK_STATE_INIT == current_irst_state) {
        // 仿真环境直接模拟配置完成 跳过配置流程
        tg_Param.KJTCQ_InitConfig = 1;
        tg_Param.HWTCQ_InitConfig = 1;
        // 初始化时直接启动制冷
        mess_To_TG.HWTCQ_Ref_Switch = 1;
    }

    // 检测状态变化: 从其他状态进入初始化状态时重置制冷计数
    if (V_IRST_WORK_STATE_INIT == current_irst_state &&
        V_IRST_WORK_STATE_INIT != last_irst_state) {
        cnt_cooling = 0; // 重新开始制冷计数
    }
    last_irst_state = current_irst_state;

    // 检测制冷开关状态变化: 从关闭变为开启时重置制冷计数
    uint8_t current_ref_switch = mess_To_TG.HWTCQ_Ref_Switch;
    if (current_ref_switch == 1 && last_ref_switch == 0) {
        cnt_cooling = 0; // 制冷机重新开启，重置计数
    }
    last_ref_switch = current_ref_switch;

    // 模拟红外制冷状态
    // HW_WorkState2 & 0x06: 0x04=正常制冷结束, 0x02=制冷未到位, 0x06=制冷故障
    mess_From_TG.HWRef_state_back = current_ref_switch; // 制冷机开关状态跟随命令

    constexpr uint64_t time_cooling = 3 * 1000 / 5; // 3s
    if (current_ref_switch == 1) {                  // 制冷机开启
        // 制冷计数累计
        cnt_cooling++;
        if (cnt_cooling < time_cooling) {
            mess_From_TG.HW_WorkState2 = 0x02; // 制冷中
            mess_From_TG.Cool_state    = 0;    // 0-正在制冷
        } else {
            mess_From_TG.HW_WorkState2 = 0x04; // 制冷正常结束
            mess_From_TG.Cool_state    = 1;    // 1-制冷到温
        }
    } else {
        // 制冷机关闭时不累计
        mess_From_TG.HW_WorkState2 = 0x00; // 制冷机关闭
        mess_From_TG.Cool_state    = 0;    // 未到温
    }
}

void FpgaSimulator::simulatingGCWK() {
    // 光窗去雾模拟：回显指令
    mess_From_GCWK.head      = 0x7E7E;
    mess_From_GCWK.cmd       = mess_To_GCWK.cmd; // 回显指令状态
    mess_From_GCWK.temp      = 250;              // 模拟温度 25.0℃
    mess_From_GCWK.tem_error = 0;                // 温度传感器正常
}

// ===== 跟踪目标像素坐标接口实现 =====
void FpgaSimulator::setTargetPixelCoor(int index, const TargetPixelCoor &coor) {
    if (index >= 0 && index < 5) {
        target_pixel_coor_[index] = coor;
    }
}

void FpgaSimulator::setTrackingTargetCount(uint8_t count) {
    tracking_target_count_ = count;
}

// ===== 曝光时间设置接口实现 =====
void FpgaSimulator::setElecOptiExposureTime(int32_t exp_time_ms) {
    // 范围限制: 5-150 ms
    
    if (exp_time_ms < KJEXPTIME_MIN) {
        exp_time_ms = KJEXPTIME_MIN;
        log_warn("可见光曝光时间过小,已限制为最小值 %d ms", KJEXPTIME_MIN);
    } else if (exp_time_ms > KJEXPTIME_MAX) {
        exp_time_ms = KJEXPTIME_MAX;
        log_warn("可见光曝光时间过大,已限制为最大值 %d ms", KJEXPTIME_MAX);
    }
    
    tg_Param.KJ_ExpTime = exp_time_ms;
    tg_Param.KJ_ExpTime_float = (float)exp_time_ms;
    // 拆分为高低8位
    tg_Param.KJ_ExpTimeH8 = ((uint16_t)exp_time_ms >> 8) & 0x00FF;
    tg_Param.KJ_ExpTimeL8 = (uint16_t)exp_time_ms & 0x00FF;
    
    log_info("设置可见光曝光时间: %d ms", exp_time_ms);
}

void FpgaSimulator::setInfraredExposureTime(uint16_t exp_time_us) {
    // 范围限制: 2000-16000 μs
    
    if (exp_time_us < HWEXPTIME_MIN) {
        exp_time_us = HWEXPTIME_MIN;
        log_warn("红外曝光时间过小,已限制为最小值 %d μs", HWEXPTIME_MIN);
    } else if (exp_time_us > HWEXPTIME_MAX) {
        exp_time_us = HWEXPTIME_MAX;
        log_warn("红外曝光时间过大,已限制为最大值 %d μs", HWEXPTIME_MAX);
    }
    
    tg_Param.HW_ExpTime = exp_time_us;
    tg_Param.HW_ExpTime_float = (float)exp_time_us;
    // 拆分为高低8位
    tg_Param.HW_ExpTimeH8 = (exp_time_us >> 8) & 0x00FF;
    tg_Param.HW_ExpTimeL8 = exp_time_us & 0x00FF;
    
    log_info("设置红外曝光时间: %d μs", exp_time_us);
}

int32_t FpgaSimulator::getVisibleExposureTime() const {
    return tg_Param.KJ_ExpTime;
}

uint16_t FpgaSimulator::getInfraredExposureTime() const {
    return tg_Param.HW_ExpTime;
}

// ===== 温度与焦面位置设置接口实现 =====
void FpgaSimulator::setPrimaryMirrorTemp(int16_t temp) {
    mess_From_QNSJ.zjwdxx = temp;
    log_info("设置主镜温度: %.1f℃", temp * 0.1f);
}

void FpgaSimulator::setSecondaryMirrorTemp(int16_t temp) {
    mess_From_QNSJ.cjwdxx = temp;
    log_info("设置次镜温度: %.1f℃", temp * 0.1f);
}

void FpgaSimulator::setTempID(uint8_t id) {
    if (id < 1 || id > 10) {
        log_warn("温度ID超出范围(1-10), 已限制为: %d", id < 1 ? 1 : 10);
        id = (id < 1) ? 1 : 10;
    }
    mess_From_QNSJ.tem_ID = id;
}

void FpgaSimulator::setVisibleFocalPlanePosition(int16_t pos_mm) {
    mess_From_TJ.jmwz_kj_real = pos_mm;
    log_info("设置可见光焦面位置: %.3f mm", pos_mm * 0.001f);
}

void FpgaSimulator::setInfraredFocalPlanePosition(int16_t pos_mm) {
    mess_From_TJ.jmwz_hw_real = pos_mm;
    log_info("设置红外焦面位置: %.3f mm", pos_mm * 0.001f);
}

int16_t FpgaSimulator::getPrimaryMirrorTemp() const {
    return mess_From_QNSJ.zjwdxx;
}

int16_t FpgaSimulator::getSecondaryMirrorTemp() const {
    return mess_From_QNSJ.cjwdxx;
}

uint8_t FpgaSimulator::getTempID() const {
    return mess_From_QNSJ.tem_ID;
}

int16_t FpgaSimulator::getVisibleFocalPlanePosition() const {
    return mess_From_TJ.jmwz_kj_real;
}

int16_t FpgaSimulator::getInfraredFocalPlanePosition() const {
    return mess_From_TJ.jmwz_hw_real;
}
