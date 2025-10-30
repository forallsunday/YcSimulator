#include "udp_packet.h"
#include "udpconnect.h"
#include <atomic>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>
#include <udp_packet_log.h>

// 回调函数（接收数据）
void onRecv(char *data, int size) {
    if (size > sizeof(UdpPacket)) {
        size = sizeof(UdpPacket);
    }
    UdpPacket packet;
    std::memcpy(&packet, data, sizeof(UdpPacket));

    INFO_UDP_PACKET_RECV("Control", "?", packet);
}

int main() {
    // 目标地址（局域网机器）
    // std::string dst_ip   = "192.168.1.10";
    std::string dst_ip   = "127.0.0.1";
    int         dst_port = 3002;

    // WSL 内监听端口
    int local_port = 4001;

    // 初始化 UDP 连接
    UdpConnect udp("127.0.0.1", local_port, -1, onRecv);
    if (!udp.Init()) {
        std::cerr << "Failed to init UDP\n";
        return -1;
    }

    std::atomic<uint32_t> seq{0}; // payload 序号

    // 循环发送
    while (true) {
        UdpPacket packet{};
        packet.source   = 0x1234;
        packet.dest     = 0x5678;
        packet.topicId  = (0xd6 << 24) | 0x01;
        packet.time_tag = std::chrono::duration_cast<std::chrono::milliseconds>(
                              std::chrono::system_clock::now().time_since_epoch())
                              .count();

        // payload 内容 = "Hello UDP XXX"
        std::string msg   = "Hello UDP " + std::to_string(seq++);
        packet.payloadLen = static_cast<uint32_t>(msg.size());
        std::memcpy(packet.pPayload, msg.data(), packet.payloadLen);

        int sent = udp.SendData(reinterpret_cast<const char *>(&packet),
                                sizeof(UdpPacket),
                                dst_ip.c_str(),
                                dst_port);
        if (sent < 0) {
            std::cerr << "Failed to send UDP packet\n";
        } else {
            std::cout << "[SEND] payload=" << msg
                      << " time_tag=" << packet.time_tag << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
    }

    return 0;
}
