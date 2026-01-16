#ifndef INIT_UDP_HPP
#define INIT_UDP_HPP

// #include <string>
#include <udpconnect.h>

// 初始化udp连接 udp包的接收逻辑在udpEventRecv中实现
bool udpTransInit(int local_port, const char *dst_ip, int dst_port_);

void udpTransSend(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

// 发送消息 名为FC 实际在仿真中为UDP
void fc_Send_Message(uint32_t topic_id, const uint8_t *msg, uint32_t size_msg);

// 向机载移植发送 okmsg
void sendOkMsg();

/// @brief 接收数据 分类消息 放入队列 (对应原 fc_EventRecv_task )
/// @param data udp包的指针
/// @param size udp包的数据长度
void udpEventRecv(char *data, int size);

// 关闭udp连接
void udpTransClose();

// test
void testSendToYcControl();

#endif // INIT_UDP_HPP
