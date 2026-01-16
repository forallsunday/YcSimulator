#include "timer_period.h"
#include <log.h>

using namespace std::chrono;

TimerPeriod::TimerPeriod()
    : period_(0),
      initialized_(false),
      running_(false),
      exit_(false) {
    // 线程常驻
    worker_ = std::thread(&TimerPeriod::run, this);
}

TimerPeriod::~TimerPeriod() {
    {
        std::lock_guard<std::mutex> lk(mtx_);
        exit_    = true;
        running_ = false;
    }
    cv_.notify_one();

    if (worker_.joinable()) {
        worker_.join();
    }
}

bool TimerPeriod::init(std::chrono::milliseconds period, Callback cb) {
    if (initialized_.exchange(true)) {
        return false;
    }

    period_   = period;
    callback_ = std::move(cb);
    return true;
}

void TimerPeriod::start() {
    if (!initialized_)
        return;

    std::lock_guard<std::mutex> lk(mtx_);
    start_time_ = clock::now();
    running_    = true;
    cv_.notify_one();
}

void TimerPeriod::stop() {
    std::lock_guard<std::mutex> lk(mtx_);
    running_ = false;
    cv_.notify_one();
}

void TimerPeriod::changePeriod(std::chrono::milliseconds period) {
    std::lock_guard<std::mutex> lk(mtx_);
    running_ = false;
    period_  = period;
    cv_.notify_one();
}

bool TimerPeriod::isInitialized() const {
    return initialized_.load(std::memory_order_acquire);
}

bool TimerPeriod::isRunning() const {
    std::lock_guard<std::mutex> lk(mtx_);
    return running_;
}

int TimerPeriod::elapsedTimeUs() const {
    std::lock_guard<std::mutex> lk(mtx_);

    if (!running_) {
        return -1; // 从未 start
    }

    return duration_cast<std::chrono::microseconds>(clock::now() - start_time_).count();
}

float TimerPeriod::elapsedTimeMs() const {
    auto us = elapsedTimeUs();
    if (us < 0)
        return -1;
    return static_cast<int>(us / 1000.f); // 自己控制精度
}

void TimerPeriod::run() {
    using clock = std::chrono::steady_clock;

    std::unique_lock<std::mutex> lk(mtx_);

    while (!exit_) {

        // === 等待 start() 或 析构 ===
        cv_.wait(lk, [&] { return running_ || exit_; });

        if (exit_) {
            break;
        }

        // === 防护：period 不合法 ===
        if (period_.count() <= 0) {
            // 无效周期，等待下一次 start / changePeriod
            cv_.wait(lk, [&] { return !running_ || exit_; });
            continue; // 跳过本次循环
        }

        // start 后重新对齐周期起点
        auto next = clock::now() + period_;

        // === 周期运行态 ===
        while (running_ && !exit_) {

            lk.unlock();
            std::this_thread::sleep_until(next);
            lk.lock();

            // cv_.wait_until(lk, next, [&] { return !running_ || exit_; });

            if (!running_ || exit_) {
                break;
            }

            if (callback_) {
                lk.unlock();
                callback_();
                lk.lock();
            }

            // next += period_;

            auto now = clock::now();
            if (next <= now) {
                auto missed = duration_cast<milliseconds>(now - next).count() / period_.count() + 1;
                next += period_ * missed;
            } else {
                next += period_;
            }
        }
    }
}
