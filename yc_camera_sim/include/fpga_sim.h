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

  private:
    // 5ms中断处理函数
    void onInterrupt();
    // 模拟电源
    void simulatingDY();
    // 模拟图像处理
    void simulatingTXCL();
    // 模拟框架
    void simulatingKJ();
    // 模拟调焦
    void simulatingTJ();
    // 模拟调光
    void simulatingTG();
    // 模拟PCS
    void simulatingPCS();
    // 模拟光窗温控
    void simulatingGCWK();
    // 模拟曝光时刻flag 根据帧频
    void simulatingExposure();

    // 模拟框架运动
    void simulatingMotionKJ();
    // 速度位置信号 计时切换
    void onSwitchSpeedOrLocate();

    // 速度位置信号 切换处理函数
    void simulatingTimerSpeedOrLocate();

  private:
    TimerPeriod timer_5ms_; // 5ms中断 计时器

    TimerPeriod timer_switch_; // 速度位置信号切换 计时器

    std::chrono::milliseconds period_switcher_{100}; // 速度位置信号周期

    std::mutex mutex_period_;
    // 图像帧之间的时间间隔
    float frame_interval;

  public:
    // ===== 跟踪目标像素坐标接口 =====
    // 目标像素坐标结构体
    struct TargetPixelCoor {
        uint16_t up_left_x    = 0;
        uint16_t up_left_y    = 0;
        uint16_t down_right_x = 0;
        uint16_t down_right_y = 0;
    };

    // 设置跟踪目标像素坐标 (由camera_sim在共享内存更新时调用)
    void setTargetPixelCoor(int index, const TargetPixelCoor &coor);
    // 设置跟踪目标数量
    void setTrackingTargetCount(uint8_t count);

  private:
    TargetPixelCoor target_pixel_coor_[5]; // 5个跟踪目标像素坐标
    uint8_t         tracking_target_count_ = 0;
};
