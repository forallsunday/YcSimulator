#pragma once

#include <atomic>
#include <timer_period.h>
#include <YC_Controller_FPGA_Mess.h>

class FpgaSimulator {
  public:
    FpgaSimulator();
    ~FpgaSimulator();

    bool init();
    void start();
    void stop();

    // void setPowerOn();

    // 模拟曝光同步信号（0A3）
    void triggerExposure();

  private:
    // 等价于 isr_Fpga_Mess 中 0A2 分支
    void on5msTick();

  private:
    TimerPeriod timer_5ms_;
};
