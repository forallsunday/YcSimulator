
#ifndef TIMER_PERIOD_H
#define TIMER_PERIOD_H

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

class TimerPeriod {
  public:
    using Callback = std::function<void()>;

    // 默认构造（不启动、不占资源）
    TimerPeriod();

    // 析构
    ~TimerPeriod();

    // 禁止拷贝
    TimerPeriod(const TimerPeriod &)            = delete;
    TimerPeriod &operator=(const TimerPeriod &) = delete;

    // ️初始化参数（只能调用一次）
    bool init(std::chrono::nanoseconds period, Callback cb);

    // 启动 / 停止
    void start();
    void stop();

    bool isInitialized() const;
    bool isRunning() const;

  private:
    void run();

  private:
    std::chrono::nanoseconds period_;
    Callback                 callback_;

    std::atomic<bool> initialized_;
    std::atomic<bool> running_;
    std::thread       worker_;
};

#endif // TIMER_PERIOD_H
