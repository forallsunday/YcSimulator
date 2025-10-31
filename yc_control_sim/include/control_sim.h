#ifndef CONTROL_SIM_H
#define CONTROL_SIM_H

#include <AOXEAppDef.h>
#include <thread_safe_queue.hpp>
#include <udp_packet.h>
#include <udpconnect.h>

#include <atomic>
#include <chrono>
#include <map>
#include <string>
#include <thread>

// udp地址 包含ip和端口
typedef struct UdpAddress {
    std::string ip;   // ip地址
    int         port; // 端口
} UdpAddress;

using MapNodeAddr   = std::map<FUNCTION_NODE_TYPE, UdpAddress>;       // ICP节点对应的地址
using MapTopicNodes = std::map<int, std::vector<FUNCTION_NODE_TYPE>>; // Topic要发送到nodes

// 机载主控模拟器
class ControlSimulator {

  public:
    ControlSimulator(
        int port_on_icp, int port_on_camera, UdpAddress addr_icp, UdpAddress addr_camera,
        MapNodeAddr map_icp_node);

    ~ControlSimulator();

    void init();

  private:
    // 处理ICP来的数据
    void dataHandlerICP(char *data, int size);
    // 处理相机仿真模型来的数据
    void dataHandlerCamera(char *data, int size);
    // 发送数据到ICP不同节点
    void startSend2IcpNodes();
    // 发送数据到相机仿真模型
    void startSend2Camera();

    // 数据监听端口
    int port_on_icp_, port_on_camera_;

    // udp地址 icp 和 相机仿真模型
    UdpAddress addr_icp_, addr_camera_;

    // udp 从ICP接收数据
    std::unique_ptr<UdpConnect> udp_icp_;

    // udp 从相机仿真模型接收数据
    std::unique_ptr<UdpConnect> udp_camera_;

    // ICP各个节点的地址
    MapNodeAddr   map_node_adrr_;    // ICP节点对应的地址
    MapTopicNodes map_topic_nodes_; // Topic要发送到nodes
    void          initMapTopicNodes();

    // 队列
    ThreadSafeQueue<PtrUdpPacket> q_from_icp_;    // 从ICP接收的数据
    ThreadSafeQueue<PtrUdpPacket> q_from_camera_; // 从相机仿真模型接收的数据

    // running
    std::atomic<bool> running_send2camera_;
    std::atomic<bool> running_send2nodes_;

    // threads
    std::thread thread_send2nodes_;
    std::thread thread_send2camera_;

    // 超时时间 (子线程阻塞时间)
    std::chrono::milliseconds timeout = std::chrono::milliseconds(100);
};

#endif