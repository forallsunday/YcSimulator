
#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <shm_interface.h>
#include <time.h>
#include <udp_packet.h>

// 获取当前时间戳 (共享内存格式)
Timestamp getCurrentTimestamp();

// 获取系统RTC (待实现怎么与FC中一致)
uint64_t getSysRTC();

// 从UdpPacket中更新消息数据
template <typename T>
void localUpdate(T &msg, UdpPacket *ptr_packet) {
    // if (ptr_packet->pPayload == nullptr) {
    // if (ptr_packet->pPayloadLen != sizeof(T) {
    memcpy(&msg, ptr_packet->pPayload, sizeof(T));
}

// timespec加微秒 用于定时
void timespec_add_us(timespec &ts, long us);

// sleep 微秒
void sleep_us(long us);
// sleep 毫秒
void sleep_ms(long ms);

#endif // UTILS_HPP
