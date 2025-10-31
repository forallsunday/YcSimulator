#ifndef UDP_PACKET_H
#define UDP_PACKET_H

#include <cstdint>
#include <memory>

#pragma pack(1)

/* UDP-与ICP通信的包头  */
/// @brief 仿真 UDP 数据包头结构体
typedef struct {
    uint32_t source;         /* source function node ID */
    uint32_t dest;           /* destination function node address */
    uint32_t msgSpec;        /* msg transfer specification */
    uint32_t topicId;        // 会打上 0xd6 的发送标记
    uint64_t time_tag;       /* time tag when sending message */
    uint32_t uiQos;          /* quality of service */
    uint32_t payloadLen;     /* length of pPayload, UNIT: bytes */
    uint32_t uiBitMap[4];    /* network bitmap or function node bitmap 1–32; 33–64; 65–96; 97–128 */
    uint8_t  pPayload[2048]; /* payload data */
} UdpPacket;

#pragma pack()

using PtrUdpPacket = std::unique_ptr<UdpPacket>;

#endif