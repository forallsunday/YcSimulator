#include <fpga_sim.h>
#include <yc/YC_Controller_Computer.h>
#include <yc/YC_Controller_globalVal_Ext.h>

static std::atomic<int> speed_or_locate{1}; // 速度位置信号；1：位置；0：速度；不工作时都是位置

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
    timer_5ms_.init(milliseconds(5), [this]() { on5msTick(); });

    // 速度位置信号计时器
    timer_switch_.init(milliseconds(50), [this]() { onSwitchSpeedOrLocate(); });

    return true;
}

void FpgaSimulator::start() {
    timer_5ms_.start();
}

void FpgaSimulator::stop() {
    timer_5ms_.stop();
    timer_switch_.stop();
}

void FpgaSimulator::on5msTick() {
    // todo: fpga 读写模拟
    // mess_From_KJ = xxx
    // mess_From_TJ = xxx
    // 具体见 void fpga_Mess_Process() { // 处理从fpga接收到的所有消息

    this->simulatingDY();
    this->simulatingPCS();
    this->simulatingTXCL();

    // 查看KJ命令字 如果是SCAN 则开始速度位置信号定时器
    checkingKjCmd();

    // 仿真伺服运动
    switch (mess_To_KJ.cmd) {
    case KJ_CMD_ZHNBEI:
    case KJ_CMD_SCAN:
    case KJ_CMD_WATCH:
    case KJ_CMD_TRACK:
        this->simulatingMotionKJ();
        break;
    default:
        break;
    }

    //------------设置标志位------------------------
    // 中断响应标志位
    flag_Fpga_Interrupt = 1;
    // fpga掉线次数清零
    flag_Fpga_down_times = 0;
}

void FpgaSimulator::checkingKjCmd() {
    switch (mess_To_KJ.cmd) {
    case KJ_CMD_SCAN:
        // 如果定时器没有running
        if (!timer_switch_.isRunning()) {
            speed_or_locate = 1; // 初始状态为位置信号
            timer_switch_.changePeriod(
                std::chrono::microseconds((int)(1000 * param_Compute_Output.toFPGA_time_location)));
            timer_switch_.start(); // 启动定时器
        } else {
            // 如果框架还是SCAN 且定时器已经启动 继续定时
        }
        break;
    default:
        timer_switch_.stop(); // 框架的其他命令停止定时器
        break;
    }
}

void FpgaSimulator::onSwitchSpeedOrLocate() {
    using namespace std::chrono;

    if (speed_or_locate == 1) {
        // 当前位置 → 切到速度
        speed_or_locate = 0;
        timer_switch_.changePeriod(
            microseconds((int)(1000 * param_Compute_Output.toFPGA_time_speed)));
    } else {
        // 当前速度 → 切到位置
        speed_or_locate = 1;
        timer_switch_.changePeriod(
            microseconds((int)(1000 * param_Compute_Output.toFPGA_time_location)));
    }
}

void FpgaSimulator::simulatingMotionKJ() {
    float pitch_start     = mess_To_KJ.toKJ_pitch_start * 0.0001f;
    float pitch_end       = mess_To_KJ.toKJ_pitch_end * 0.0001f;
    float pitch_speed     = mess_To_KJ.toKJ_pitch_speed * 0.01f;
    float direction_start = mess_To_KJ.toKJ_direction_start * 0.0001f;
    float direction_end   = mess_To_KJ.toKJ_direction_end * 0.0001f;
    float direction_speed = mess_To_KJ.toKJ_direction_speed * 0.01f;

    // 判断成像模式 根据帧频
    float tpf; // time per frame
    switch (cmd_From_FC.irst_cmd_param_irst_form_mode) {
    case V_IRST_FORM_MODE_WIDE_IMAG:
        tpf = GYCX_pfs;
        break;
    case V_IRST_FORM_MODE_AREA_IMAG:
        tpf = QYCX_pfs;
        break;
    case V_IRST_FORM_MODE_AREA_MONI:
        tpf = 1 / 25;
        break;
    default:
        break;
    }

    // 框架实时俯仰角（LSB = 0.0001°)
    mess_From_KJ.rtime_pitch_frame = pitch_start + 5 * 1e-3f * pitch_speed;
    // 框架实时方位角（LSB = 0.0001°)
    mess_From_KJ.rtime_direction_frame = direction_start + 5 * 1e-3f * direction_speed;
    // 根据帧频计算的
    // 框架曝光时刻俯仰角（LSB = 0.0001°)
    mess_From_KJ.exposure_pitch_frame = pitch_start + tpf * pitch_speed;
    // 框架曝光时刻方位角（LSB = 0.0001°)
    mess_From_KJ.exposure_direction_frame = direction_start + tpf * direction_speed;
    // // 框架曝光时刻俯仰指令角（LSB = 0.0001°)
    // mess_From_KJ.exposure_order_pitch_frame;
    // // 框架曝光时刻方位指令角（LSB = 0.0001°)
    // mess_From_KJ.exposure_order_direction_frame;
    // // 框架实时俯仰陀螺速度（LSB = 0.01°/s)
    // mess_From_KJ.rtime_pitch_frame_top_v;
    // // 框架实时方位陀螺速度（LSB = 0.01°/s)
    // mess_From_KJ.rtime_direction_frame_top_v;
    // // 框架曝光时刻俯仰陀螺速度（LSB = 0.01°/s)
    // mess_From_KJ.exposure_pitch_frame_top_v;
    // // 框架曝光时刻方位陀螺速度（LSB = 0.01°/s)
    // mess_From_KJ.exposure_direction_frame_top_v;
    // // 快反实时俯仰补偿位置（LSB = 0.0001°)
    // mess_From_KJ.kfssfybcwz;
    // // 快反实时方位补偿位置（LSB = 0.0001°)
    // mess_From_KJ.kfssfwbcwz;
    // // 快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
    // mess_From_KJ.kfbgskfybcwz;
    // // 快反曝光时刻方位补偿位置（LSB = 0.0001°)
    // mess_From_KJ.kfbgskfwbcwz;
    // todo: 快反
}

void FpgaSimulator::simulatingPCS() {
    // todo: 需要后续仔细对照
    // 时间1
    // mess_From_PCS_DATA.time_hour   = mess_TO_PCS_DATA.time_gnss_calendartime; // 时
    mess_From_PCS_DATA.time_day    = mess_TO_PCS_DATA.date_day;   // 日
    mess_From_PCS_DATA.time_mounth = mess_TO_PCS_DATA.date_month; // 月
    mess_From_PCS_DATA.time_year   = mess_TO_PCS_DATA.date_year;  // 年

    // 时间2
    // mess_From_PCS_DATA.time_ms;  // 毫秒
    // mess_From_PCS_DATA.time_s;   // 秒
    // mess_From_PCS_DATA.time_min; // 分

    mess_From_PCS_DATA.longitude = mess_TO_PCS_DATA.pt_longitude; // 经度LSB=π/2^31---1
    mess_From_PCS_DATA.latitude  = mess_TO_PCS_DATA.pt_latitude;  // 纬度LSB=π/2^31---1
    // mess_From_PCS_DATA.altitude             = mess_TO_PCS_DATA.ac_height; // 高度 有符号数(-500m~25000m)， LSB=0.001m---1
    // mess_From_PCS_DATA.true_heading         = mess_TO_PCS_DATA; // 真航向   有符号数(-π~+π)，LSB=π/2^31rad---1
    // mess_From_PCS_DATA.pitch                = mess_TO_PCS_DATA; // 俯仰角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    // mess_From_PCS_DATA.roll                 = mess_TO_PCS_DATA; // 横滚角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    // mess_From_PCS_DATA.heading_v            = mess_TO_PCS_DATA; // 航向角速度  有符号数 (-π~+π)rad/s，LSB=π/ (2^15)rad/s
    // mess_From_PCS_DATA.pitch_v              = mess_TO_PCS_DATA; // 俯仰角速度  有符号数 (-π~+π)rad/s，LSB =π/ (2^15)rad/s
    // mess_From_PCS_DATA.roll_v               = mess_TO_PCS_DATA; // 横滚角速度  有符号数 (-π~+π)rad/s，LSB =π/ (2^15)rads
    // mess_From_PCS_DATA.north_speed          = mess_TO_PCS_DATA; // 北向速度  有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    // mess_From_PCS_DATA.east_speed           = mess_TO_PCS_DATA; // 东向速度	 有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    // mess_From_PCS_DATA.ground_speed         = mess_TO_PCS_DATA; // 地向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    // mess_From_PCS_DATA.forward_acceleration = mess_TO_PCS_DATA; // 前向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，顺航向向前为正
    // mess_From_PCS_DATA.normal_acceleration  = mess_TO_PCS_DATA; // 法向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，飞机法向向上为正
    // mess_From_PCS_DATA.lateral_acceleration = mess_TO_PCS_DATA; // 侧向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，顺航向向右为正
}

void FpgaSimulator::simulatingDY() {
    // 电源
    // mess_To_DY.work_mode = work_mode; // 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
    // 电源开关字
    mess_From_DY.state_szgd   = mess_To_DY.cmd_szgd;   // 数字供电0：关 1：开
    mess_From_DY.state_glgd   = mess_To_DY.cmd_glgd;   // 功率供电0：关 1：开
    mess_From_DY.state_rkbjgd = mess_To_DY.cmd_rkbjgd; // 热控供电本机：0：关 1：开
    mess_From_DY.state_rkgcgd = mess_To_DY.cmd_rkgcgd; // 热控供电光窗：0：关 1：开
}

void FpgaSimulator::simulatingTXCL() {
}

void FpgaSimulator::triggerExposure() {
    // ==============================
    // 等价 isr_Fpga_Mess() 中 0A3
    // ==============================

    // flag_Fpga_bg.store(1, std::memory_order_relaxed);
    // TG_NBCJInterrupt();
}
