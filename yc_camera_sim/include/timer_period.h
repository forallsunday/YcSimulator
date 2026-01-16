#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class TimerPeriod {

  public:
    using Callback = std::function<void()>;
    using clock    = std::chrono::steady_clock;

    TimerPeriod();
    ~TimerPeriod();

    // 只允许初始化一次
    bool init(std::chrono::milliseconds period, Callback cb);

    // 开始 / 暂停计时（不创建 / 销毁线程）
    void start();
    void stop();

    // 修改周期 会停止当前计时
    void changePeriod(std::chrono::milliseconds period);

    bool isInitialized() const;
    bool isRunning() const;

    int   elapsedTimeUs() const;
    float elapsedTimeMs() const;

    // void resetElapsed();

  private:
    void run();

  private:
    std::chrono::milliseconds period_;
    Callback                  callback_;

    std::atomic<bool> initialized_;

    bool running_;
    bool exit_;

    std::thread worker_;

    mutable std::mutex      mtx_;
    std::condition_variable cv_;

    // ===== 计时相关 =====
    clock::time_point start_time_{};
};
