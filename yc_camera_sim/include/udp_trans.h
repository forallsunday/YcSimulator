#ifndef INIT_UDP_HPP
#define INIT_UDP_HPP

// #include <string>
#include <udpconnect.h>

bool initUdpTrans(
    int                       local_port,
    const char               *dst_ip,
    int                       dst_port_,
    UdpConnect::DataHandlFunc recv_cb);

// 发送消息 名为FC 实际在仿真中为UDP
void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

#endif // INIT_UDP_HPP
