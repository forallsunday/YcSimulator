
#include <log.h>
#include <id_name.hpp>
#include <udp_packet_log.h>

void printf_udp_packet_recv(const UdpPacket &packet) {

    char src_buf[16];
    char dst_buf[16];
    char topic_buf[16];

    const char *src_name = lookupOrHex(
        packet.source, log_node_name_table, src_buf, sizeof(src_buf));
    const char *dst_name = lookupOrHex(
        packet.dest, log_node_name_table, dst_buf, sizeof(dst_buf));
    const char *topic_name = lookupOrHex(
        packet.topicId, log_topic_name_table, topic_buf, sizeof(topic_buf));

    log_info(
        "[接收RECV] | src=%s dst=%s topic=%s payloadLen=%u bytes time_tag=%llu",
        src_name,
        dst_name,
        topic_name,
        packet.payloadLen,
        static_cast<unsigned long long>(packet.time_tag));
}

void printf_udp_packet_send(const char *where, const char *ip, int port, const UdpPacket &packet) {
    char src_buf[16];
    char dst_buf[16];
    char topic_buf[16];

    const char *src_str = lookupOrHex(
        packet.source, log_node_name_table, src_buf, sizeof(src_buf));
    const char *dst_str = lookupOrHex(
        packet.dest, log_node_name_table, dst_buf, sizeof(dst_buf));
    const char *topic_str = lookupOrHex(
        packet.topicId, log_topic_name_table, topic_buf, sizeof(topic_buf));

    log_info(
        "[发送SEND] to %s %s:%d | src=%s dst=%s topic=%s payloadLen=%u bytes time_tag=%llu",
        where,
        ip,
        port,
        src_str,
        dst_str,
        topic_str,
        packet.payloadLen,
        static_cast<unsigned long long>(packet.time_tag));
};
