#include <Def/AOXEAppDef.h>
#include <Def/AppTopicIdDef.h>
#include <Def/MyTopicIdDef.h>

#include <yc/YC_Controller_globalVal_Ext.h>

#include <global_vars.h>
#include <log.h>
#include <log_def.h>
#include <shm_interface.h>
#include <udp_packet.h>
#include <udp_trans.h>
#include <utils.h>

#include <cstring>

static std::unique_ptr<UdpConnect> udp0;
static int                         port_local;
static std::string                 ip_dst;
static int                         port_dst;

bool udpTransInit(int local_port, const char *dst_ip, int dst_port_) {

    // 已初始化则直接返回
    if (udp0) {
        return true;
    }

    port_local = local_port;
    ip_dst     = std::string(dst_ip);
    port_dst   = dst_port_;

    // udp0.reset(new UdpConnect("0.0.0.0", port_local, -1, recv_cb));
    // udp0 = std::make_unique<UdpConnect>("0.0.0.0", port_local, -1, recv_cb);
    udp0 = std::make_unique<UdpConnect>("0.0.0.0", port_local, -1, udpEventRecv);

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

void udpEventRecv(char *data, int size) {
    // // 如果没有上电 则不处理
    // if (power_status_ != POWER_ON)
    //     return;

    // 检查数据大小
    if (size > sizeof(UdpPacket)) {
        log_warn("Received data size (%d) > UdpPacket size (%zu)", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }

    auto ptr_packet = std::make_unique<UdpPacket>();
    std::memcpy(ptr_packet.get(), data, size);

    LOG_INFO_UDP_RECV(*ptr_packet);

    // 将收到的消息放入对应队列中
    auto topic_id = ptr_packet->topicId;
    switch (topic_id) {
        // 如果是IRST_ACT_REQ消息
    case V_TOPIC_IRST_ACT_REQ:
        sq::sq_IRST_act_req.push(std::move(ptr_packet));
        break;
        // 如果是需要处理和回复的消息
    case V_TOPIC_SYMM_SYM_OPERATIONAL_PARAS:
    case V_TOPIC_SYMD_DATA_LOAD_MSG_IRRM:
        sq::sq_others.push(std::move(ptr_packet));
        break;
        // 如果是参数信息，只需要保存，不需要回复和处理的信息,缓存下来
        // 系统管理时间信息报告
    case V_TOPIC_SYMM_SYM_TIME_REPORT:
        localUpdate(temp_mess_FromFc_SYM_TIME_REPORT, ptr_packet.get());
        break;
        // INS1工作参数报告
    case V_TOPIC_IN1M_INS1_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS1_OPERATIONAL_PARAS, ptr_packet.get());
        break;
        // INS2工作参数报告
    case V_TOPIC_IN2M_INS2_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS2_OPERATIONAL_PARAS, ptr_packet.get());
        break;
        // INS3工作参数报告
    case V_TOPIC_IN3M_INS3_OPERATIONAL_PARAS:
        localUpdate(temp_mess_FromFc_INS3_OPERATIONAL_PARAS, ptr_packet.get());
        break;
        // 绝对导航融合飞行参数
    case V_TOPIC_NAFM_ABSOLUTE_NAV_DATA_FUSED:
        localUpdate(temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED, ptr_packet.get());
        break;
        // 导航参数报告
    case V_TOPIC_NAV_PARAS:
        localUpdate(temp_mess_FromFc_NAV_PARAS, ptr_packet.get());
        break;
        // 战术任务事件报告（事件类，通常入队）
    case V_TOPIC_TMMM_MISSION_EVENT_REPORT:
        localUpdate(temp_mess_FromFc_MISSION_EVENT_REPORT, ptr_packet.get());
        break;
        // 内部存储消息（FLASH 相关）
    case V_TOPIC_NEIBU_MESS:
        localUpdate(nbMess_hwInfo_FLASH, ptr_packet.get());
        // my_flash_write(FLASH_ADDR, (void *)(aucRecvData + uiAppHeadLen), sizeof(MESS_FROMFC_HWINFO_FLASH)); // 写回flash
        break;
        // 静态成像使用消息
    case V_TOPIC_JT_PHOTO:
        localUpdate(nbMess_jt_Photo, ptr_packet.get());
        break;

    // ===================== 默认 =====================
    default:
        // 其他消息暂不处理
        break;
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

    LOG_INFO_UDP_SEND("机载移植", ip_dst.c_str(), port_dst, packet);

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

    // LOG_INFO_UDP_SEND("机载移植", ip_dst.c_str(), port_dst, packet);

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

    LOG_INFO_UDP_SEND("机载移植", "172.19.5.3", 9318, packet);

    udp0->SendData(
        reinterpret_cast<const char *>(&packet), sizeofPacket(&packet), "172.19.5.3", 9318);
}