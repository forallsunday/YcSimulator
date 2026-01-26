
#include <id_name.hpp>
#include <log_def.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const char file_udp[] = "UDP ";

void log_udp_packet_recv(const UdpPacket &packet) {

    char src_buf[16];
    char dst_buf[16];
    char topic_buf[16];

    const char *src_name = lookupOrHex(
        packet.source, log_node_name_table, src_buf, sizeof(src_buf));
    const char *dst_name = lookupOrHex(
        packet.dest, log_node_name_table, dst_buf, sizeof(dst_buf));
    const char *topic_name = lookupOrHex(
        packet.topicId, log_topic_name_table, topic_buf, sizeof(topic_buf));

    // log_info(
    log_log(LOG_INFO, file_udp, 0,
            "[接收RECV] | src=<%s>, dst=<%s>, topic=<%s>, payloadLen=%u bytes, time_tag=%llu",
            src_name,
            dst_name,
            topic_name,
            packet.payloadLen,
            static_cast<unsigned long long>(packet.time_tag));
}

void log_udp_packet_send(const char *where, const char *ip, int port, const UdpPacket &packet) {

    char src_buf[16];
    char dst_buf[16];
    char topic_buf[16];

    const char *src_str = lookupOrHex(
        packet.source, log_node_name_table, src_buf, sizeof(src_buf));
    const char *dst_str = lookupOrHex(
        packet.dest, log_node_name_table, dst_buf, sizeof(dst_buf));
    const char *topic_str = lookupOrHex(
        packet.topicId, log_topic_name_table, topic_buf, sizeof(topic_buf));

    // log_info(
    log_log(LOG_INFO, file_udp, 0,
            "[发送SEND] to %s %s:%d | src=<%s>, dst=<%s>, topic=<%s>, payloadLen=%u bytes, time_tag=%llu",
            where,
            ip,
            port,
            src_str,
            dst_str,
            topic_str,
            packet.payloadLen,
            static_cast<unsigned long long>(packet.time_tag));
}

void log_once_func(const char *fmt, ...) {
    static char last_msg[1024] = {0}; // 上一次打印的内容
    char        curr_msg[1024];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(curr_msg, sizeof(curr_msg), fmt, ap);
    va_end(ap);

    // 完全一样 → 不打印
    if (strcmp(curr_msg, last_msg) == 0) {
        return;
    }

    // 不一样 → 打印并更新 last_msg
    strncpy(last_msg, curr_msg, sizeof(last_msg) - 1);
    last_msg[sizeof(last_msg) - 1] = '\0';

    log_log(LOG_INFO, "once", 0, "%s", curr_msg);
}