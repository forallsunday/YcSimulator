
#pragma once

#define PRINTF_UDP_PACKET_RECV 1 // 打印接收的udp包
#define PRINTF_UDP_PACKET_SEND 1 // 打印发送的udp包

#if PRINTF_UDP_PACKET_RECV
#define INFO_UDP_PACKET_RECV(packet)                                                                \
    do {                                                                                                       \
        printf("[RECV] | time_tag=%llu src=0x%08X dst=0x%08X topicId=0x%08X payloadLen=%u bytes\n", \
               static_cast<unsigned long long>((packet).time_tag),                                             \
               (packet).source,                                                                                \
               (packet).dest,                                                                                  \
               (packet).topicId,                                                                               \
               (packet).payloadLen);                                                                           \
    } while (0)
#else
#define PRINT_UDP_PACKET_RECV(where, ip, packet) \
    do {                                         \
    } while (0)
#endif

#if PRINTF_UDP_PACKET_SEND
#define INFO_UDP_PACKET_SEND(where, ip, port, packet)                                                             \
    do {                                                                                                          \
        printf("[SEND] to %s %s : %d | time_tag=%llu src=0x%08X dst=0x%08X topicId=0x%08X payloadLen=%u bytes\n", \
               where,                                                                                             \
               ip,                                                                                                \
               port,                                                                                              \
               static_cast<unsigned long long>((packet).time_tag),                                                \
               (packet).source,                                                                                   \
               (packet).dest,                                                                                     \
               (packet).topicId,                                                                                  \
               (packet).payloadLen);                                                                              \
    } while (0)
#else
#define INFO_UDP_PACKET_SEND(where, ip, port, packet) \
    do {                                              \
    } while (0)
#endif
