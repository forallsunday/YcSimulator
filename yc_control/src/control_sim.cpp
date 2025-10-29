#include <AppTopicIdDef.h>
#include <control_sim.h>
#include <cstring>

#define TEST_MODE_CONTROL_SIM

ControlSimulator::ControlSimulator(
    UdpAddress addr_icp, UdpAddress addr_camera, IcpNodeMap icp_node_map)
    : addr_icp_(addr_icp), addr_camera_(addr_camera), icp_node_map_(icp_node_map) {
}

ControlSimulator::~ControlSimulator() {
    // 关闭线程
    running_send2camera_ = false;
    q_from_icp_.notifyAll(); // 唤醒如果阻塞
    running_send2nodes_ = false;
    q_from_camera_.notifyAll();

    if (thread_send2camera_.joinable())
        thread_send2camera_.join();

    if (thread_send2nodes_.joinable())
        thread_send2nodes_.join();
}

void ControlSimulator::init() {
    // udp连接 设置参数
    udp_icp_    = std::unique_ptr<UdpConnect>(new UdpConnect(
        this->addr_icp_.ip, this->addr_icp_.port, -1,
        [this](char *data, int size) { this->dataHandlerICP(data, size); }));
    udp_camera_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        this->addr_camera_.ip, this->addr_camera_.port, -1,
        [this](char *data, int size) { this->dataHandlerCamera(data, size); }));

    // udp连接 初始化
    if (udp_icp_->Init()) {
        printf("[Initilize] UDP ICP init,   ip:%s, port:%d\n",
               this->addr_icp_.ip.c_str(), this->addr_icp_.port);
    } else {
        printf("Connect UDP ICP ERROR\n");

        return;
    }
    if (udp_camera_->Init()) {
        printf("[Initilize] UDP Camera init, ip:%s, port:%d\n",
               this->addr_camera_.ip.c_str(), this->addr_camera_.port);
    } else {
        printf("Connect UDP Camera ERROR\n");
    }

    // 开启发送线程
    startSend2Camera();
    startSend2IcpNodes();
}

void ControlSimulator::dataHandlerICP(char *data, int size) {
    // if (size > sizeof(UdpPacket)) {
    //     printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
    //     size = sizeof(UdpPacket); // 避免越界
    // }
    // 收到后放入队列icp中
    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    // if (size > sizeof(UdpPacket))
    //     size = sizeof(UdpPacket);
    std::memcpy(ptr_packet.get(), data, size);
    q_from_icp_.push(std::move(ptr_packet));

#ifdef TEST_MODE_CONTROL_SIM
    printf("[Recv] From ICP %s:%d | src=0x%08X dst=0x%08X topicId=0x%08X payloadLen=%u bytes\n",
           this->addr_icp_.ip.c_str(),
           this->addr_icp_.port,
           ptr_packet->source,
           ptr_packet->dest,
           ptr_packet->topicId,
           ptr_packet->payloadLen);
#endif
}

void ControlSimulator::dataHandlerCamera(char *data, int size) {
    // 收到后放入队列camera中
    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    // if (size > sizeof(UdpPacket))
    //     size = sizeof(UdpPacket);
    std::memcpy(ptr_packet.get(), data, size);
    q_from_camera_.push(std::move(ptr_packet));

#ifdef TEST_MODE_CONTROL_SIM
    printf("[Recv] From Camera %s:%d | src=0x%08X dst=0x%08X topicId=0x%08X payloadLen=%u bytes\n",
           this->addr_camera_.ip.c_str(),
           this->addr_camera_.port,
           ptr_packet->source,
           ptr_packet->dest,
           ptr_packet->topicId,
           ptr_packet->payloadLen);
#endif
}

void ControlSimulator::startSend2IcpNodes() {
    // 消息分类 不同的节点
    running_send2nodes_ = true;
    thread_send2nodes_  = std::thread([this]() {
        while (running_send2nodes_) {
            PtrUdpPacket packet;
            if (q_from_camera_.waitForAndPop(packet, this->timeout)) {
                // 没有竞争条件 不用加锁
                // Note: 临时 发送到所有节点
                for (const auto &pair : icp_node_map_) {
                    const FUNCTION_NODE_TYPE &node = pair.first;
                    const UdpAddress         &addr = pair.second;
                    udp_icp_->SendData(
                        reinterpret_cast<const char *>(packet.get()),
                        sizeof(UdpPacket),
                        addr.ip.c_str(),
                        addr.port);
                }
                // // todo: 根据topic 发送到不同的节点
                // auto       &topic = packet->topicId;
                // std::string ip;
                // int         port;
                // switch (topic) {
                // case V_TOPIC_IRRM_IRST_LOS:
                //     ip   = this->icp_node_map_[V_NODE_IRRM].ip.c_str();
                //     port = this->icp_node_map_[V_NODE_IRRM].port;
                //     break;
                // }
                // udp_icp_->SendData(reinterpret_cast<const char *>(packet.get()), sizeof(UdpPacket), ip.c_str(), port);
            }
        } // 这里 packet 超出作用域，它会自动 delete UdpPacket
    });
}
void ControlSimulator::startSend2Camera() {
    running_send2camera_ = true;
    thread_send2camera_  = std::thread([this]() {
        while (running_send2camera_) {
            PtrUdpPacket packet;
            if (q_from_icp_.waitForAndPop(packet, this->timeout)) {
                // 没有竞争条件 不用加锁
                udp_camera_->SendData(
                    reinterpret_cast<const char *>(packet.get()),
                    sizeof(UdpPacket),
                    this->addr_camera_.ip.c_str(),
                    this->addr_camera_.port);
            }
        } // 这里 packet 超出作用域，它会自动 delete UdpPacket
    });
}