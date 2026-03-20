#pragma once

#include <YC_Controller_FPGA_Mess.h>
#include <atomic>
#include <timer_period.h>
#include <vector>

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
    // 设置所有跟踪目标像素坐标 (由camera_sim在共享内存更新时调用)
    void setFiveTargetPixelCoor(const std::vector<TargetPixelCoor> &coor_vec);
    // 设置跟踪目标数量
    void setTrackingTargetCount(uint8_t count);
    // 重置目标像素坐标
    void resetTargetPixelCoor();

    // ===== 曝光时间设置接口 =====
    // 设置可见光曝光时间 (单位: ms, 范围: 5-150)
    void setElecOptiExposureTime(int32_t exp_time_ms);
    // 设置红外曝光时间 (单位: μs, 范围: 2000-16000)
    void setInfraredExposureTime(uint16_t exp_time_us);
    // 获取可见光曝光时间 (单位: ms)
    int32_t getVisibleExposureTime() const;
    // 获取红外曝光时间 (单位: μs)
    uint16_t getInfraredExposureTime() const;

    // ===== 温度与焦面位置设置接口 =====
    // 设置主镜温度 (单位: 0.1℃, 例如: 250表示25.0℃)
    void setPrimaryMirrorTemp(int16_t temp);
    // 设置次镜温度 (单位: 0.1℃, 例如: 250表示25.0℃)
    void setSecondaryMirrorTemp(int16_t temp);
    // 设置温度ID (1-10循环)
    void setTempID(uint8_t id);
    // 设置可见光焦面位置 (单位: 0.001mm, 例如: 1000表示1.0mm)
    void setVisibleFocalPlanePosition(int16_t pos_mm);
    // 设置红外焦面位置 (单位: 0.001mm, 例如: 1000表示1.0mm)
    void setInfraredFocalPlanePosition(int16_t pos_mm);
    
    // 获取主镜温度 (单位: 0.1℃)
    int16_t getPrimaryMirrorTemp() const;
    // 获取次镜温度 (单位: 0.1℃)
    int16_t getSecondaryMirrorTemp() const;
    // 获取温度ID
    uint8_t getTempID() const;
    // 获取可见光焦面位置 (单位: 0.001mm)
    int16_t getVisibleFocalPlanePosition() const;
    // 获取红外焦面位置 (单位: 0.001mm)
    int16_t getInfraredFocalPlanePosition() const;

  private:
    TargetPixelCoor target_pixel_coor_[5]; // 5个跟踪目标像素坐标
    uint8_t         tracking_target_count_ = 0;
};
