#include "timer_period.h"

TimerPeriod::TimerPeriod()
    : period_(0),
      initialized_(false),
      running_(false) {
}

TimerPeriod::~TimerPeriod() {
    stop();
}

bool TimerPeriod::init(std::chrono::nanoseconds period, Callback cb) {
    if (initialized_.exchange(true)) {
        return false; // 已初始化
    }

    period_   = period;
    callback_ = std::move(cb);
    return true;
}

void TimerPeriod::start() {
    if (!initialized_.load(std::memory_order_acquire)) {
        return; // 未 init，直接忽略或 assert
    }

    if (running_.exchange(true)) {
        return;
    }

    worker_ = std::thread(&TimerPeriod::run, this);
}

void TimerPeriod::stop() {
    if (!running_.exchange(false)) {
        return;
    }

    if (worker_.joinable()) {
        worker_.join();
    }
}

void TimerPeriod::run() {
    using clock = std::chrono::steady_clock;

    auto next = clock::now() + period_;

    while (running_.load(std::memory_order_acquire)) {

        std::this_thread::sleep_until(next);

        if (!running_.load(std::memory_order_acquire)) {
            break;
        }

        if (callback_) {
            callback_();
        }

        next += period_;
    }
}

bool TimerPeriod::isInitialized() const {
    return initialized_.load(std::memory_order_acquire);
}

bool TimerPeriod::isRunning() const {
    return running_.load(std::memory_order_acquire);
}