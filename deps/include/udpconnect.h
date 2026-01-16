#ifndef UDPCONNECT_H
#define UDPCONNECT_H

//todo: 修改以适应windows能收发

#include "SocketWrapper.h"

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <thread>

class UdpConnect {
  public:
    using DataHandlFunc = std::function<void(char *, int)>;
    /// @brief 构造函数
    /// @param ip 地址
    /// @param port 接收端口
    /// @param port_send 发送端口 (<1 时为系统分配端口)
    /// @param dataHandlFunc 数据处理函数
    ///
    /// 使用示例：
    /// ```cpp
    /// void data_receive_handle(char* pData, int nSize) {
    ///     msg_log(INFO, "recv buf size is %d", nSize);
    ///     msg_log(INFO, "recv buf content is %s", pData);
    /// }
    ///
    /// UdpConnect udp_connect("153.15.2.21", 10086, 10087, &data_receive_handle);
    /// ```
    UdpConnect(std::string ip, int port, int port_send, DataHandlFunc dataFunc);

    ~UdpConnect();

    bool Init(); // 初始化链接, 建立接收udp

    // 参数：数据缓冲区，数据长度，目标ip，目标端口
    int SendData(const char *buf, size_t size, const char *ip_dst, int port_dst);

    // int recvfrom(SocketWrapperHandle s, char* buf, size_t len, unsigned int* farAddr, unsigned short* farPort);
    //    int RecvData( char* buf, size_t len, unsigned int* farAddr);

    void Close(); // 关闭链接

  private:
    std::string ip_;

    int port_;
    int port_send;

    DataHandlFunc dataHandlFunc_; // 数据处理

    std::atomic<bool> start_receive{false}; // 是否开启接收数据

    int            epfd_ = -1;
    std::thread    recv_thread_;
    SocketWrapper *pSocketWrapper_          = nullptr;
    void          *socketWrapperHandle_     = nullptr;
    void          *socketWrapperHandle_send = nullptr;
};

#endif
