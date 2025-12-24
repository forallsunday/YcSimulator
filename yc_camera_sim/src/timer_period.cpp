#include "timer_period.h"

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

bool TimerPeriod::init(std::chrono::nanoseconds period, Callback cb) {
    if (initialized_.exchange(true)) {
        return false;
    }

    period_   = period;
    callback_ = std::move(cb);
    return true;
}

void TimerPeriod::start() {
    if (!initialized_.load(std::memory_order_acquire)) {
        return;
    }

    {
        std::lock_guard<std::mutex> lk(mtx_);
        running_ = true;
    }
    cv_.notify_one();
}

void TimerPeriod::stop() {
    std::lock_guard<std::mutex> lk(mtx_);
    running_ = false;
}

void TimerPeriod::changePeriod(std::chrono::nanoseconds period) {
    std::lock_guard<std::mutex> lk(mtx_);
    period_ = period;
}

bool TimerPeriod::isInitialized() const {
    return initialized_.load(std::memory_order_acquire);
}

bool TimerPeriod::isRunning() const {
    return running_.load(std::memory_order_acquire);
}

void TimerPeriod::run() {
    using clock = std::chrono::steady_clock;

    std::unique_lock<std::mutex> lk(mtx_);

    while (!exit_) {

        // === 等待 start() 或 析构 ===
        cv_.wait(lk, [&] {
            return running_ || exit_;
        });

        if (exit_) {
            break;
        }

        // start 后重新对齐周期起点
        auto next = clock::now() + period_;

        // === 周期运行态 ===
        while (running_ && !exit_) {

            // sleep_until 不需要持锁
            lk.unlock();
            std::this_thread::sleep_until(next);
            lk.lock();

            if (!running_ || exit_) {
                break;
            }

            if (callback_) {
                callback_();
            }

            next += period_;
        }
    }
}
