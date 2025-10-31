#include <AppTopicIdDef.h>
#include <control_sim.h>
#include <cstring>
#include <udp_packet_log.h>

#define SEND_TOPIC (0xd6 << 24)

ControlSimulator::ControlSimulator(
    int port_on_icp, int port_on_camera,
    UdpAddress addr_icp, UdpAddress addr_camera,
    MapNodeAddr map_node_adrr)
    : port_on_icp_(port_on_icp), port_on_camera_(port_on_camera), addr_icp_(addr_icp), addr_camera_(addr_camera), map_node_adrr_(map_node_adrr) {
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

    // 初始化主题节点映射
    initMapTopicNodes();

    // 开启发送线程
    startSend2Camera();
    startSend2IcpNodes();
}

void ControlSimulator::dataHandlerICP(char *data, int size) {

    // Debug 检查数据大小
#ifndef NDEBUG
    if (size > sizeof(UdpPacket)) {
        printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }
#endif

    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV("ICP", this->addr_icp_.ip.c_str(), *ptr_packet);

    // 收到后放入队列icp中
    q_from_icp_.push(std::move(ptr_packet));
}

void ControlSimulator::dataHandlerCamera(char *data, int size) {

#ifndef NDEBUG
    if (size > sizeof(UdpPacket)) {
        printf("Warning: received data size (%d) exceeds UdpPacket size (%zu)\n", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }
#endif

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

void ControlSimulator::initMapTopicNodes() {
    // 初始化ICP节点映射

    this->map_topic_nodes_[V_TOPIC_IRRM_WORK_STATE_REPORT] = {
        V_NODE_MPHL,
        V_NODE_SYMM,
        V_NODE_MPHR,
    };

    this->map_topic_nodes_[V_TOPIC_IRRM_IRST_OPERATIONAL_PARAS] = {
        V_NODE_IIPM,
        V_NODE_DCLD,
        V_NODE_TMMM,
        V_NODE_DCRM,
        V_NODE_DCLM,
        V_NODE_DCRD,
        V_NODE_SRMM,
    };

    // 可以根据需要添加更多节点
}

void ControlSimulator::startSend2IcpNodes() {
    printf("start sending to icp nodes.\n");
    // 消息分类 不同的节点
    running_send2nodes_ = true;
    thread_send2nodes_  = std::thread([this]() {
        while (running_send2nodes_) {
            PtrUdpPacket ptr_packet;
            if (q_from_camera_.waitForAndPop(ptr_packet, this->timeout)) {
                // 只发送camera 发送过来的包
                if (ptr_packet->source != V_NODE_IRRM)
                    continue;

                // Note: 根据topic 发送到不同的节点
                // uint32_t topic_id   = ptr_packet->topicId & 0x00FFFFFF; // 打上发送标记的情况: 保留低 24 位
                // 现在camera 发送过来的包没有发送标记了, 在这里打发送标记
                uint32_t topic_id   = ptr_packet->topicId;
                auto     iter_topic = map_topic_nodes_.find(topic_id);
                if (iter_topic == map_topic_nodes_.end())
                    continue; // topic 未注册

                for (const FUNCTION_NODE_TYPE node : iter_topic->second) {
                    auto iter_node = map_node_adrr_.find(node);
                    if (iter_node == map_node_adrr_.end())
                        continue; // 节点地址未注册

                    const std::string &ip   = iter_node->second.ip;
                    int                port = iter_node->second.port;

                    // 修改 packet
                    ptr_packet->topicId = SEND_TOPIC | topic_id;
                    ptr_packet->dest    = node;

                    INFO_UDP_PACKET_SEND("ICP Nodes", ip.c_str(), *ptr_packet);

                    udp_icp_->SendData(
                        reinterpret_cast<const char *>(ptr_packet.get()),
                        sizeof(UdpPacket),
                        ip.c_str(), port);
                }
            }
        } // 这里 packet 超出作用域，它会自动 delete UdpPacket
    });
}
