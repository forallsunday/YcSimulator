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

    TimerPeriod();
    ~TimerPeriod();

    // 只允许初始化一次
    bool init(std::chrono::nanoseconds period, Callback cb);

    // 开始 / 暂停计时（不创建 / 销毁线程）
    void start();
    void stop();

    // 修改周期
    void changePeriod(std::chrono::nanoseconds period);

    bool isInitialized() const;
    bool isRunning() const;

  private:
    void run();

  private:
    std::chrono::nanoseconds period_;
    Callback                 callback_;

    std::atomic<bool> initialized_;
    std::atomic<bool> running_;
    std::atomic<bool> exit_;

    std::thread worker_;

    std::mutex              mtx_;
    std::condition_variable cv_;
};
