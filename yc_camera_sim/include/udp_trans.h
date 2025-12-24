#ifndef INIT_UDP_HPP
#define INIT_UDP_HPP

// #include <string>
#include <udpconnect.h>

bool udpTransInit(
    int                       local_port,
    const char               *dst_ip,
    int                       dst_port_,
    UdpConnect::DataHandlFunc recv_cb);

// 发送消息 名为FC 实际在仿真中为UDP
void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

void udpTransSend(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

// 发送udp消息到机载移植
template <typename T>
void udpTransSend(uint32_t topic_id, T *msg) {
    udpTransSend(topic_id, (uint8_t *)msg, sizeof(T));
};

// 关闭udp连接
void udpTransClose();

#endif // INIT_UDP_HPP
