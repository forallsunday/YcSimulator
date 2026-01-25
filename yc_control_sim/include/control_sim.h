#ifndef CONTROL_SIM_H
#define CONTROL_SIM_H

#include <atomic>
#include <chrono>
#include <map>
#include <string>
#include <thread>

#include <Def/AOXEAppDef.h>
#include <MyTopicIdDef.h>
#include <id_name.hpp>
#include <thread_safe_queue.hpp>
#include <udp_packet.h>
#include <udpconnect.h>
#include <read_udp_addr.hpp>

// udp地址 包含ip和端口
typedef struct UdpAddress {
    std::string ip;        // 功能节点的ip地址
    int         port;      // 监听端口
    int         port_send; // 发送端口
} UdpAddress;

using MapNodeAddr   = std::map<FUNCTION_NODE_TYPE, UdpAddress>;       // ICP节点对应的地址
using MapTopicNodes = std::map<int, std::vector<FUNCTION_NODE_TYPE>>; // Topic要发送到nodes

// 机载主控模拟器
class ControlSimulator {

  public:
    ControlSimulator(ReadUdpAddr read_udp_addr, MapNodeAddr map_node_addr);

    ~ControlSimulator();

    void init();

  private:
    // 处理ICP来的数据
    void dataHandlerICP(char *data, int size);
    // 处理相机仿真模型来的数据
    void dataHandlerCamera(char *data, int size);
    // 发送OK_MSG
    void startSendOkMsg();
    // 发送数据到ICP不同节点
    void startSend2IcpNodes();
    // 发送数据到相机仿真模型
    void startSend2Camera();

    // 是否要发送
    bool is_send2camera_   = true;
    bool is_send2icpnodes_ = true;

    // 读取机载移植和相机仿真相互之间的UDP的ip和端口
    ReadUdpAddr read_udp_addr_;

    // udp 从ICP接收数据
    std::unique_ptr<UdpConnect> udp_icp_;

    // udp 从相机仿真模型接收数据
    std::unique_ptr<UdpConnect> udp_camera_;

    int sendPkt2Camera(const UdpPacket *ptr_packet);
    int sendPkt2IcpNodes(const UdpPacket *ptr_packet, std::string ip, int port);

    // ICP各个节点的地址
    MapNodeAddr   map_node_addr_;   // ICP节点对应的地址
    MapTopicNodes map_topic_nodes_; // Topic要发送到nodes
    void          initMapTopicNodes();

    // ok msg 发送的数量
    int num_okmsg_ = 0;

    // 队列
    ThreadSafeQueue<int>          queue_okmsg_;       // 从相机仿真模型接收的okmsg的信号
    ThreadSafeQueue<PtrUdpPacket> queue_from_icp_;    // 从ICP接收的数据
    ThreadSafeQueue<PtrUdpPacket> queue_from_camera_; // 从相机仿真模型接收的数据

    // running
    std::atomic<bool> running_send_okmsg_{false};
    std::atomic<bool> running_send2camera_{false};
    std::atomic<bool> running_send2nodes_{false};

    // threads
    std::thread thread_send_okmsg_;
    std::thread thread_send2nodes_;
    std::thread thread_send2camera_;

    // 超时时间 (子线程阻塞时间)
    std::chrono::milliseconds timeout = std::chrono::milliseconds(100);
};

#endif