#pragma once

#include <YC_Controller_FPGA_Mess.h>
#include <atomic>
#include <timer_period.h>

// 中断模拟
int gpio0AIn(int code);

class FpgaSimulator {
  public:
    ;
    FpgaSimulator();
    ~FpgaSimulator();

    bool init();
    void start();
    void stop();

    // 模拟框架运动
    void simulatingMotionKJ();
    // 模拟PCS
    void simulatingPCS();
    // 模拟电源
    void simulatingDY();
    // 模拟图像处理
    void simulatingTXCL();

    // 模拟曝光同步信号（0A3）
    void triggerExposure();

  private:
    // 等价于 isr_Fpga_Mess 中 0A2 分支
    void on5msTick();
    // 速度位置信号 计时切换
    void onSwitchSpeedOrLocate();

    // 监控KJ命令字
    void checkingKjCmd();

  private:
    TimerPeriod timer_5ms_;    // 5ms中断 计时器
    TimerPeriod timer_switch_; // 速度位置信号切换 计时器
};
