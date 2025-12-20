#include <fpga_sim.h>
#include <yc/YC_Controller_globalVal_Ext.h>

FpgaSimulator::FpgaSimulator() {}

FpgaSimulator::~FpgaSimulator() {
    stop();
}

bool FpgaSimulator::init() {
    // 5ms 周期定时器
    return timer_5ms_.init(
        std::chrono::milliseconds(5),
        [this]() { on5msTick(); });
}

void FpgaSimulator::start() {
    timer_5ms_.start();
}

void FpgaSimulator::stop() {
    timer_5ms_.stop();
}
void FpgaSimulator::on5msTick() {
    // todo: fpga 读写模拟
    // mess_From_KJ = xxx
    // mess_From_TJ = xxx
    // 具体见 void fpga_Mess_Process() { // 处理从fpga接收到的所有消息

    // 电源
    // mess_To_DY.work_mode = work_mode; // 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
    // 电源开关字
    mess_From_DY.state_szgd   = mess_To_DY.cmd_szgd;   // 数字供电0：关 1：开
    mess_From_DY.state_glgd   = mess_To_DY.cmd_glgd;   // 功率供电0：关 1：开
    mess_From_DY.state_rkbjgd = mess_To_DY.cmd_rkbjgd; // 热控供电本机：0：关 1：开
    mess_From_DY.state_rkgcgd = mess_To_DY.cmd_rkgcgd; // 热控供电光窗：0：关 1：开

    //------------设置标志位------------------------
    // 中断响应标志位
    flag_Fpga_Interrupt = 1;
    // fpga掉线次数清零
    flag_Fpga_down_times = 0;
}

void FpgaSimulator::triggerExposure() {
    // ==============================
    // 等价 isr_Fpga_Mess() 中 0A3
    // ==============================

    // flag_Fpga_bg.store(1, std::memory_order_relaxed);
    // TG_NBCJInterrupt();
}
