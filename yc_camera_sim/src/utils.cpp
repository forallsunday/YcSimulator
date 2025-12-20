#include <utils.h>

Timestamp getCurrentTimestamp() {

    using namespace std::chrono;

    // 获取当前时间点
    auto now = system_clock::now();

    // 转为 time_t（秒）
    std::time_t t = system_clock::to_time_t(now);
    std::tm     local_tm{};

    localtime_r(&t, &local_tm);

    // 计算毫秒部分
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    Timestamp ts{};
    ts.U1_Year        = static_cast<unsigned char>((local_tm.tm_year + 1900) % 100); // 年份只取后两位
    ts.U1_Month       = static_cast<unsigned char>(local_tm.tm_mon + 1);
    ts.U1_Day         = static_cast<unsigned char>(local_tm.tm_mday);
    ts.U1_Hour        = static_cast<unsigned char>(local_tm.tm_hour);
    ts.U1_Minute      = static_cast<unsigned char>(local_tm.tm_min);
    ts.U1_Second      = static_cast<unsigned char>(local_tm.tm_sec);
    ts.U2_Millisecond = static_cast<unsigned short>(ms.count());

    return ts;
};

// 得到系统RTC TODO: How? 原来为fc函数
uint64_t getSysRTC() {
    // todo: 不对
    using namespace std::chrono;
    // 获取当前时间点（系统时钟）
    auto now = steady_clock::now();
    // 转换为毫秒数
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count();
    return static_cast<uint64_t>(ms);
};

void timespec_add_us(timespec &ts, long us) {
    // 每秒包含的微秒数：1e6 = 1,000,000
    // 显式 static_cast<long>，避免浮点参与运行期计算
    constexpr long USEC_PER_SEC = static_cast<long>(1e6);

    // 每秒包含的纳秒数：1e9 = 1,000,000,000
    constexpr long NSEC_PER_SEC = static_cast<long>(1e9);

    // 把“整秒部分”的微秒转换成秒，直接累加到 tv_sec
    // 例如 us = 2,000,010 → 增加 2 秒
    ts.tv_sec += us / USEC_PER_SEC;

    // 把“不足一秒的微秒部分”转换成纳秒，加到 tv_nsec
    // (us % USEC_PER_SEC) ∈ [0, 999999]
    // ×1000 → 微秒转纳秒
    ts.tv_nsec += (us % USEC_PER_SEC) * 1000L;

    // 如果纳秒数超过 1 秒（>= 1e9），需要进位
    if (ts.tv_nsec >= NSEC_PER_SEC) {
        // 减去 1 秒对应的纳秒数
        ts.tv_nsec -= NSEC_PER_SEC;
        // 秒数加 1
        ts.tv_sec++;
    }
}

void sleep_us(long us) {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    timespec_add_us(ts, us);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, nullptr);
}

void sleep_ms(long ms) {
    sleep_us(ms * 1000L);
}