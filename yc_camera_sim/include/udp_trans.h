#ifndef INIT_UDP_HPP
#define INIT_UDP_HPP

// #include <string>
#include <udpconnect.h>

bool udpTransInit(
    int                       local_port,
    const char               *dst_ip,
    int                       dst_port_,
    UdpConnect::DataHandlFunc recv_cb);

void udpTransSend(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

// 发送消息 名为FC 实际在仿真中为UDP
void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

// 向机载移植发送 okmsg
void sendOkMsg();

// 关闭udp连接
void udpTransClose();

// test
void testSendToYcControl();

#endif // INIT_UDP_HPP
