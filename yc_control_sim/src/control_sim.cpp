#include <AppTopicIdDef.h>
#include <chrono>
#include <control_sim.h>
#include <cstring>
#include <log.h>
#include <udp_packet_log.h>

#define SEND_TOPIC (0xd6 << 24)

ControlSimulator::ControlSimulator(std::string ip_icp_server, std::string ip_camera, int ctrl_port_recv_icp, int ctrl_port_recv_camera, int cam_port, MapNodeAddr map_node_addr)
    : ip_icp_server_(ip_icp_server), ip_camera_(ip_camera),
      ctrl_port_recv_icp_(ctrl_port_recv_icp), ctrl_port_recv_camera_(ctrl_port_recv_camera),
      cam_port_(cam_port), map_node_addr_(map_node_addr) {
}

ControlSimulator::~ControlSimulator() {
    // 关闭udp连接
    this->udp_icp_->Close();
    this->udp_camera_->Close();

    // 关闭线程
    running_send_okmsg_  = false;
    running_send2camera_ = false;
    running_send2nodes_  = false;
    queue_okmsg_.notifyAll();
    queue_from_icp_.notifyAll(); // 唤醒如果阻塞
    queue_from_camera_.notifyAll();

    if (thread_send_okmsg_.joinable())
        thread_send_okmsg_.join();

    if (thread_send2camera_.joinable())
        thread_send2camera_.join();

    if (thread_send2nodes_.joinable())
        thread_send2nodes_.join();
}

void ControlSimulator::init() {
    // udp连接 设置参数
    std::string ip_0 = "0.0.0.0";

    udp_icp_    = std::unique_ptr<UdpConnect>(new UdpConnect(
        ip_0, ctrl_port_recv_icp_, -1,
        [this](char *data, int size) { this->dataHandlerICP(data, size); }));
    udp_camera_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        ip_0, ctrl_port_recv_camera_, -1,
        [this](char *data, int size) { this->dataHandlerCamera(data, size); }));

    // udp连接 初始化
    if (udp_icp_->Init()) {
        log_info("udp初始化成功 监听端口%d", ctrl_port_recv_icp_);
    } else {
        log_warn("udp初始化失败");
    }

    if (udp_camera_->Init()) {
        log_info("udp初始化成功 监听端口%d", ctrl_port_recv_camera_);
    } else {
        log_warn("udp初始化失败");
    }

    // 初始化 主题要发送到的节点
    initMapTopicNodes();

    // 开启发送线程
    startSendOkMsg();
    startSend2Camera();
    startSend2IcpNodes();
}

int ControlSimulator::sendPkt2Camera(const UdpPacket *ptr_packet) {
    return udp_camera_->SendData(
        reinterpret_cast<const char *>(ptr_packet),
        sizeofPacket(ptr_packet), ip_camera_.c_str(), cam_port_);
}

int ControlSimulator::sendPkt2IcpNodes(const UdpPacket *ptr_packet, std::string ip, int port) {
    return udp_icp_->SendData(
        reinterpret_cast<const char *>(ptr_packet),
        sizeofPacket(ptr_packet), ip.c_str(), port);
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

void ControlSimulator::dataHandlerICP(char *data, int size) {

    if (size > sizeof(UdpPacket)) {
        log_warn("Received data size (%d) > UdpPacket size (%zu)", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }

    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV(*ptr_packet);

    // 收到后放入队列icp中
    queue_from_icp_.push(std::move(ptr_packet));
}

void ControlSimulator::dataHandlerCamera(char *data, int size) {

    if (size > sizeof(UdpPacket)) {
        log_warn("Received data size (%d) > UdpPacket size (%zu)", size, sizeof(UdpPacket));
        size = sizeof(UdpPacket); // 避免越界
    }

    auto ptr_packet = PtrUdpPacket(new UdpPacket());
    std::memcpy(ptr_packet.get(), data, size);

    INFO_UDP_PACKET_RECV(*ptr_packet);

    // 收到后放入队列中
    if (ptr_packet->topicId == MY_TOPIC_OKMSG) {
        ++this->num_okmsg_;
        queue_okmsg_.push(this->num_okmsg_);
    } else {
        queue_from_camera_.push(std::move(ptr_packet));
    }
}

void ControlSimulator::startSendOkMsg() {
    log_info("start sending ok msg.");
    running_send_okmsg_ = true;
    thread_send_okmsg_  = std::thread([this]() {
        using namespace std::chrono;
        // 获取当前时间点（系统时钟）毫秒
        auto     now      = steady_clock::now();
        auto     ms       = duration_cast<milliseconds>(now.time_since_epoch()).count();
        uint64_t time_tag = static_cast<uint64_t>(ms);

        auto make_ok_packet = [&](uint32_t topic_id, uint32_t block_id) {
            OK_MSG ok{};
            ok.app_ok   = 1; // 握手成功
            ok.msg_src  = V_NODE_IRRM;
            ok.block_id = block_id;

            UdpPacket pkt{};
            pkt.uiQos      = 0x10000000;
            pkt.msgSpec    = 0;
            pkt.time_tag   = time_tag;
            pkt.payloadLen = sizeof(OK_MSG);
            pkt.source     = V_NODE_IRRM;
            pkt.topicId    = topic_id;
            memcpy(&pkt.pPayload, &ok, sizeof(OK_MSG));

            return pkt;
        };

        //  三个包
        std::vector<UdpPacket> packets = {
            make_ok_packet(0x80001234, 0x80001234),
            make_ok_packet(0x8400fff0, 0x8400fff0),
            make_ok_packet(0xda00ff06, 0xda00ff06)};

        auto send_to_node = [&](FUNCTION_NODE_TYPE node, const std::string &node_name) {
            auto iter = map_node_addr_.find(node);
            if (iter != map_node_addr_.end()) {
                const auto &ip   = iter->second.ip;
                auto        port = iter->second.port;

                for (auto &pkt : packets) {
                    pkt.dest = node;
                    // INFO_UDP_PACKET_SEND(node_name, ip.c_str(), port, pkt);
                    this->sendPkt2IcpNodes(&pkt, ip.c_str(), port);
                }
            } else {
                log_info("%s ip and port not found.", node_name.c_str());
            }
        };

        while (running_send_okmsg_) {
            // if (true) {
            //     std::this_thread::sleep_for(std::chrono::milliseconds(180)); // 测试时直接发 ok_msg
            int num_okmsg;
            if (queue_okmsg_.waitForAndPop(num_okmsg, this->timeout)) {
                //  发送到各节点
                send_to_node(V_NODE_ADAS, "V_NODE_ADAS"); // 监控
                send_to_node(V_NODE_SYMM, "V_NODE_SYMM");
                send_to_node(V_NODE_MPHL, "V_NODE_MPHL");
                send_to_node(V_NODE_MPHR, "V_NODE_MPHR");
                send_to_node(V_NODE_SRMM, "V_NODE_SRMM");
            }
        }
    });
}

void ControlSimulator::startSend2Camera() {
    log_info("start sending to camera.");
    running_send2camera_ = true;
    thread_send2camera_  = std::thread([this]() {
        while (running_send2camera_) {
            PtrUdpPacket ptr_packet;

            if (queue_from_icp_.waitForAndPop(ptr_packet, this->timeout)) {
                // if (queue_from_camera_.waitForAndPop(ptr_packet, this->timeout)) { // Note: 测试从Camera收
                // 没有竞争条件 不用加锁
                INFO_UDP_PACKET_SEND("相机仿真 Camera", ip_camera_.c_str(), cam_port_, *ptr_packet);
                this->sendPkt2Camera(ptr_packet.get());
            }
        } // 这里 packet 超出作用域，它会自动 delete UdpPacket
    });
}

void ControlSimulator::startSend2IcpNodes() {
    log_info("start sending to icp nodes.");
    // 消息分类 不同的节点
    running_send2nodes_ = true;
    thread_send2nodes_  = std::thread([this]() {
        while (running_send2nodes_) {
            PtrUdpPacket ptr_packet;
            if (queue_from_camera_.waitForAndPop(ptr_packet, this->timeout)) {
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
                    auto iter_node = map_node_addr_.find(node);
                    if (iter_node == map_node_addr_.end())
                        continue; // 节点地址未注册

                    const std::string &ip   = iter_node->second.ip;
                    int                port = iter_node->second.port;

                    // 修改 packet
                    ptr_packet->dest    = node;
                    INFO_UDP_PACKET_SEND("ICP Nodes 节点", ip.c_str(), port, *ptr_packet);
                    ptr_packet->topicId = SEND_TOPIC | topic_id;

                    this->sendPkt2IcpNodes(ptr_packet.get(), ip, port);
                }

                // Note: 测试 同时发送一份给监控
                auto iter_2 = map_node_addr_.find(V_NODE_ADAS);
                if (iter_2 != map_node_addr_.end()) {
                    const std::string &ip_adas   = iter_2->second.ip;
                    int                port_adas = iter_2->second.port;
                    INFO_UDP_PACKET_SEND("V_NODE_ADAS 监控", ip_adas.c_str(), port_adas, *ptr_packet);
                    this->sendPkt2IcpNodes(ptr_packet.get(), ip_adas, port_adas);
                }
            }
        }
    });
}
