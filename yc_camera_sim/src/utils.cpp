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