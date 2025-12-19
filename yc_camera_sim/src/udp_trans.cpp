#include <AOXEAppDef.h>
#include <cstring>
#include <shm_interface.h>
#include <udp_packet.h>
#include <udp_packet_log.h>
#include <udp_trans.h>
#include <utils.h>

static std::unique_ptr<UdpConnect> udp0;
static int                         port_local;
static std::string                 ip_dst;
static int                         port_dst;

bool initUdpTrans(
    int                       local_port,
    const char               *dst_ip,
    int                       dst_port_,
    UdpConnect::DataHandlFunc recv_cb) {

    // 已初始化则直接返回
    if (udp0) {
        return true;
    }

    port_local = local_port;
    ip_dst     = std::string(dst_ip);
    port_dst   = dst_port_;

    udp0.reset(new UdpConnect(
        "0.0.0.0", port_local, -1, recv_cb));

    if (!udp0) {
        return false;
    }

    udp0->Init();

    return true;
}

void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg) {

    if (!udp0 || !msg || size_msg == 0) {
        return;
    }

    UdpPacket packet{};
    packet.time_tag = getSysRTC();
    packet.source   = FUNCTION_NODE_TYPE::V_NODE_IRRM;
    packet.topicId  = topic_id;

    size_msg          = std::min(size_msg, static_cast<uint32_t>(2048));
    packet.payloadLen = size_msg;
    std::memcpy(packet.pPayload, msg, size_msg);

    INFO_UDP_PACKET_SEND("机载移植 Control", ip_dst.c_str(), port_dst, packet);

    udp0->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeofPacket(&packet), ip_dst.c_str(), port_dst);
}