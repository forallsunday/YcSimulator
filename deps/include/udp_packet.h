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
    uint32_t topicId;        // 发送到icp nodes时 会打上 0xd6 的发送标记
    uint64_t time_tag;       /* time tag when sending message */
    uint32_t uiQos;          /* quality of service */
    uint32_t payloadLen;     /* length of pPayload, UNIT: bytes */
    uint32_t uiBitMap[4];    /* network bitmap or function node bitmap 1–32; 33–64; 65–96; 97–128 */
    uint8_t  pPayload[2048]; /* payload data */
} UdpPacket;

typedef struct {
    uint32_t block_id;
    uint32_t msg_src;
    uint32_t sysctrl_node;
    uint32_t appcfg;
    uint32_t app_ok;
    uint32_t flag;
} OK_MSG;

#pragma pack()

using PtrUdpPacket = std::unique_ptr<UdpPacket>;

inline size_t sizeofPacket(const UdpPacket *ptr_packet) {
    return 64 + ptr_packet->payloadLen; // 应该是48个字节 多发几个字节 确保不会少字节
};

#endif