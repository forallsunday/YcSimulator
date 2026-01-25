// 定义log的相关函数
#pragma once

#include <atomic>
#include <chrono>
#include <log.h>
#include <udp_packet.h>

// log接受的udp包
void log_udp_packet_recv(const UdpPacket &packet);
// log发送的udp包
void log_udp_packet_send(const char *where, const char *ip, int port, const UdpPacket &packet);

// 多次刷新只打印一次
void log_once_func(const char *fmt, ...);

#define PRINT_LOG_UDP_RECV 1 // log接收的udp包
#define PRINT_LOG_UDP_SEND 1 // log发送的udp包

#if PRINT_LOG_UDP_RECV
#define LOG_INFO_UDP_RECV(packet)    \
    do {                             \
        log_udp_packet_recv(packet); \
    } while (0)
#else
#define LOG_INFO_UDP_RECV(packet) \
    do {                          \
    } while (0)
#endif

#if PRINT_LOG_UDP_SEND
#define LOG_INFO_UDP_SEND(where, ip, port, packet)    \
    do {                                              \
        log_udp_packet_send(where, ip, port, packet); \
    } while (0)
#else
#define LOG_INFO_UDP_SEND(where, ip, port, packet) \
    do {                                           \
    } while (0)
#endif

#define PRINT_LOG_PROC 1 // 打印函数内的过程日志
#if PRINT_LOG_PROC
#define log_proc(...)                              \
    do {                                           \
        log_log(LOG_INFO, "proc", 0, __VA_ARGS__); \
    } while (0)
#define log_once(...)               \
    do {                            \
        log_once_func(__VA_ARGS__); \
    } while (0)
#else
#define log_proc(...) \
    do {              \
    } while (0)
#define log_once(...) \
    do {              \
    } while (0)
#endif
