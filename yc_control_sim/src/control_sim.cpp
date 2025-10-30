#include <AppTopicIdDef.h>
#include <control_sim.h>
#include <cstring>
#include <udp_packet_log.h>

ControlSimulator::ControlSimulator(int port_on_icp, int port_on_camera, UdpAddress addr_icp, UdpAddress addr_camera, IcpNodeMap icp_node_map)
    : port_on_icp_(port_on_icp), port_on_camera_(port_on_camera),
      addr_icp_(addr_icp), addr_camera_(addr_camera),
      icp_node_map_(icp_node_map) {
}

ControlSimulator::~ControlSimulator() {
    // 关闭udp连接
    this->udp_icp_->Close();
    this->udp_camera_->Close();

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
    std::string ip_0 = "0.0.0.0";

    udp_icp_    = std::unique_ptr<UdpConnect>(new UdpConnect(
        ip_0, this->port_on_icp_, -1,
        [this](char *data, int size) { this->dataHandlerICP(data, size); }));
    udp_camera_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        ip_0, this->port_on_camera_, -1,
        [this](char *data, int size) { this->dataHandlerCamera(data, size); }));

    // udp连接 初始化
    if (udp_icp_->Init()) {
        printf("[Initilize] UDP ICP init, ip = %s, port = %d\n", ip_0.c_str(), this->port_on_icp_);
    } else {
        printf("[ERR] UDP ICP receive bind failed.\n");
        return;
    }
    if (udp_camera_->Init()) {
        printf("[Initilize] UDP Camera init, ip = %s, port = %d\n", ip_0.c_str(), this->port_on_camera_);
    } else {
        printf("[ERR] UDP Camera receive bind failed.\n");
        return;
    }

    // 开启发送线程
    startSend2Camera();
    startSend2IcpNodes();
}

void ControlSimulator::dataHandlerICP(char *data, int size) {
    if (size > sizeof(UdpPacket)) {
        printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }
    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV("ICP", this->addr_icp_.ip.c_str(), *ptr_packet);

    // 收到后放入队列icp中
    q_from_icp_.push(std::move(ptr_packet));
}

void ControlSimulator::dataHandlerCamera(char *data, int size) {
    if (size > sizeof(UdpPacket)) {
        printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }
    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV("Camera", this->addr_camera_.ip.c_str(), *ptr_packet);

    // 收到后放入队列中
    q_from_camera_.push(std::move(ptr_packet));
}

void ControlSimulator::startSend2Camera() {
    printf("start sending to camera.\n");
    running_send2camera_ = true;
    thread_send2camera_  = std::thread([this]() {
        while (running_send2camera_) {
            PtrUdpPacket ptr_packet;

            if (q_from_icp_.waitForAndPop(ptr_packet, this->timeout)) {
                // if (q_from_camera_.waitForAndPop(ptr_packet, this->timeout)) { // Note: 测试从Camera收
                // 没有竞争条件 不用加锁
                INFO_UDP_PACKET_SEND("Camera", this->addr_camera_.ip.c_str(), *ptr_packet);
                udp_camera_->SendData(
                    reinterpret_cast<const char *>(ptr_packet.get()),
                    sizeof(UdpPacket),
                    this->addr_camera_.ip.c_str(),
                    this->addr_camera_.port);
            }
        } // 这里 packet 超出作用域，它会自动 delete UdpPacket
    });
}

void ControlSimulator::startSend2IcpNodes() {
    printf("start sending to icp nodes.\n");
    // 消息分类 不同的节点
    running_send2nodes_ = true;
    thread_send2nodes_  = std::thread([this]() {
        while (running_send2nodes_) {
            PtrUdpPacket ptr_packet;
            if (q_from_camera_.waitForAndPop(ptr_packet, this->timeout)) {
                // 没有竞争条件 不用加锁
                // Note: 临时 发送到所有节点
                for (const auto &pair : icp_node_map_) {
                    const FUNCTION_NODE_TYPE &node = pair.first;
                    const UdpAddress         &addr = pair.second;
                    INFO_UDP_PACKET_SEND("ICP Node", addr.ip.c_str(), *ptr_packet);
                    udp_icp_->SendData(
                        reinterpret_cast<const char *>(ptr_packet.get()),
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
