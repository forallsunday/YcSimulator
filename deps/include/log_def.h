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
// log ICP发送给IRRM的包
void log_udp_packet_recv_icp_to_irrm(const UdpPacket &packet);

#define LOG_UDP_PACKET_RECV 1 // log接收的udp包
#define LOG_UDP_PACKET_SEND 1 // log发送的udp包

#if LOG_UDP_PACKET_RECV
#define INFO_UDP_PACKET_RECV(packet) \
    do {                             \
        log_udp_packet_recv(packet); \
    } while (0)
#else
#define PRINT_UDP_PACKET_RECV(packet) \
    do {                              \
    } while (0)
#endif

#if LOG_UDP_PACKET_SEND
#define INFO_UDP_PACKET_SEND(where, ip, port, packet) \
    do {                                              \
        log_udp_packet_send(where, ip, port, packet); \
    } while (0)
#else
#define INFO_UDP_PACKET_SEND(where, ip, port, packet) \
    do {                                              \
    } while (0)
#endif

#define LOG_IN_FUNC 1 // 在进入函数后 是否打印log 用于调试
#if LOG_IN_FUNC
#define INFO_LOG_IN_FUNC(...)                               \
    do {                                                    \
        log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__); \
    } while (0)
#else
#define INFO_LOG_IN_FUNC(...) \
    do {                      \
    } while (0)
#endif
