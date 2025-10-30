#include <Def/AOXEAppDef.h>
#include <camera_sim.h>
#include <chrono>
#include <cstring>

#define SEND_TOPIC (0xd6 << 24)

CameraSimulator::CameraSimulator(int port_, std::string ip_send2, int port_send2)
    : port_(port_), ip_dst_(ip_send2), port_dst_(port_send2) {
}

CameraSimulator::~CameraSimulator() {
    // 关闭udp连接 (子线程1停止)
    udp_->Close();
    udp_.reset();

    // 子线程内不循环
    running_act_req_       = false;
    running_other_process_ = false;

    // 队列不wait
    queue_act_req_.notifyAll();
    queue_others_.notifyAll();

    // 子线程退出
    if (thread_act_req_.joinable()) {
        thread_act_req_.join();
    }
    if (thread_other_process_.joinable()) {
        thread_other_process_.join();
    }
}

void CameraSimulator::init() {
    // udp连接
    udp_ = std::unique_ptr<UdpConnect>(new UdpConnect(
        "0.0.0.0", this->port_, -1,
        [this](char *data, int size) { this->dataHandlerReceive(data, size); }));

    // 开启udp连接 (子线程1启动)
    udp_->Init();

    // 子线程3 启动
    this->running_other_process_ = true;
    thread_other_process_        = std::thread(&CameraSimulator::otherProcess, this);
}

void CameraSimulator::udpSend(uint32_t topic_id, uint8_t *msg, uint32_t msg_len) {

    // 加锁
    std::lock_guard<std::mutex> lock(this->mtx_send_);

    // udp 发送数据包
    UdpPacket packet;

    // 获取当前时间戳
    using namespace std::chrono;
    auto time_stamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    // Note: 没有设置目标V_NODE_XXX 改逻辑放在 ControlSimulator 里实现
    packet.time_tag   = time_stamp;
    packet.source     = FUNCTION_NODE_TYPE::V_NODE_IRRM; // 我们发送的永远是这个
    packet.topicId    = SEND_TOPIC | topic_id;           // 在topic_id前加上发送标记
    packet.payloadLen = msg_len;
    std::memcpy(packet.pPayload, msg, msg_len);

    this->udp_->SendData(
        reinterpret_cast<const char *>(&packet),
        sizeof(UdpPacket),
        this->ip_dst_.c_str(), this->port_dst_);
}

void CameraSimulator::dataHandlerReceive(char *data, int size) {
    // 解析数据 分类消息
}

void CameraSimulator::actReq() {
    // 如果队列不为空
    // if (this->queue_other_msg_.tryPop(packet)) {
    //     // 处理其他消息
    // }
}

void CameraSimulator::otherProcess() {
    while (this->running_other_process_) {
        // UDP数据包
        UdpPacket packet;
        // 等待队列有数据并取出，如果超时，则进行下一次循环
        if (this->queue_others_.waitForAndPop(packet, this->timeout)) {
            // 处理others消息
        }
    }
}

void CameraSimulator::periodicSend() {
}
void CameraSimulator::subsystemTimer() {
}
