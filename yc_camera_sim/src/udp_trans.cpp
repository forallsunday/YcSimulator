#include <Def/AOXEAppDef.h>
#include <Def/MyTopicIdDef.h>
#include <cstring>
#include <log.h>
#include <log_def.h>
#include <shm_interface.h>
#include <udp_packet.h>
#include <udp_trans.h>
#include <utils.h>

static std::unique_ptr<UdpConnect> udp0;
static int                         port_local;
static std::string                 ip_dst;
static int                         port_dst;

bool udpTransInit(
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

    udp0.reset(new UdpConnect("0.0.0.0", port_local, -1, recv_cb));

    if (!udp0) {
        return false;
    }

    if (udp0->Init()) {
        log_info("udp初始化成功 监听端口%d", port_local);
        return true;
    } else {
        log_warn("udp初始化失败");
        return false;
    }
}

void udpTransSend(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg) {
    if (!udp0 || !msg || size_msg == 0) {
        log_error("udp发送失败!");
        return;
    }

    UdpPacket packet{};
    packet.time_tag = getSysRTC();
    packet.source   = FUNCTION_NODE_TYPE::V_NODE_IRRM;
    packet.topicId  = topic_id;

    size_msg          = std::min(size_msg, static_cast<uint32_t>(2048));
    packet.payloadLen = size_msg;
    std::memcpy(packet.pPayload, msg, size_msg);

    INFO_UDP_PACKET_SEND("机载移植", ip_dst.c_str(), port_dst, packet);

    udp0->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeofPacket(&packet), ip_dst.c_str(), port_dst);
}

void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg) {
    udpTransSend(topic_id, msg, size_msg);
}

// 定义okmsg
static const uint8_t c_ok_msg = 1;
// 发送okmsg
void sendOkMsg() {
    //    udpTransSend(MY_TOPIC_OKMSG, &c_ok_msg, 1);
    if (!udp0) {
        log_error("udp发送失败!");
        return;
    }

    UdpPacket packet{};
    packet.time_tag = getSysRTC();
    packet.source   = FUNCTION_NODE_TYPE::V_NODE_IRRM;
    packet.topicId  = MY_TOPIC_OKMSG;

    packet.payloadLen = 1;
    std::memcpy(packet.pPayload, &c_ok_msg, 1);

    // INFO_UDP_PACKET_SEND("机载移植", ip_dst.c_str(), port_dst, packet);

    udp0->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeofPacket(&packet), ip_dst.c_str(), port_dst);
}

void udpTransClose() {
    if (udp0) {
        udp0->Close();
        udp0.reset();
    }
}

void testSendToYcControl() {
    uint8_t   msg = 1;
    UdpPacket packet{};
    packet.time_tag = getSysRTC();
    packet.source   = FUNCTION_NODE_TYPE::V_NODE_IRRM;
    packet.topicId  = MY_TOPIC_OKMSG;

    int size_msg      = 1;
    packet.payloadLen = 1;
    memcpy(packet.pPayload, &msg, size_msg);

    INFO_UDP_PACKET_SEND("机载移植", "172.19.5.3", 9318, packet);

    udp0->SendData(
        reinterpret_cast<const char *>(&packet), sizeofPacket(&packet), "172.19.5.3", 9318);
}