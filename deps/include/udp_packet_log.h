
#pragma once

#include <udp_packet.h>

#include <atomic>
#include <chrono>

void printf_udp_packet_recv(const UdpPacket &packet);
void printf_udp_packet_send(const char *where, const char *ip, int port, const UdpPacket &packet);

#define PRINTF_UDP_PACKET_RECV 1 // 打印接收的udp包
#define PRINTF_UDP_PACKET_SEND 1 // 打印发送的udp包

#if PRINTF_UDP_PACKET_RECV
#define INFO_UDP_PACKET_RECV(packet)    \
    do {                                \
        printf_udp_packet_recv(packet); \
    } while (0)
#else
#define PRINT_UDP_PACKET_RECV(where, ip, packet) \
    do {                                         \
    } while (0)
#endif

#if PRINTF_UDP_PACKET_SEND
#define INFO_UDP_PACKET_SEND(where, ip, port, packet)    \
    do {                                                 \
        printf_udp_packet_send(where, ip, port, packet); \
    } while (0)
#else
#define INFO_UDP_PACKET_SEND(where, ip, port, packet) \
    do {                                              \
    } while (0)
#endif
