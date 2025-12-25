#include "udp_packet.h"
#include "udpconnect.h"
#include <camera_sim.h>
#include <read_udp_addr.hpp>

#include <atomic>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>

#include <log_def.h>
#include <log_init.h>

int main() {
    log_init("test_.log");

    // 解析xml文件 获取icp节点(V_NODE_XXX)对应的所有地址
    SOCKET_PARSE socket_data; // xml解析的数据
    // 要检查的文件路径
    const std::string config_file = "./ModuleConfig.xml";
    // 尝试以输入模式打开文件
    std::ifstream file(config_file);

    if (file.is_open()) {
        // 文件存在并且可以成功打开
        file.close(); // 及时关闭，让 tcp_udp_parse_d 函数可以自行打开
        // 现在可以安全地调用你的解析函数
        tcp_udp_parse_d(config_file.c_str(), &socket_data); // 注意：传入 c_str()
    } else {
        // 打开文件失败
        std::cerr << "Error: Configuration file not found or cannot be opened: " << config_file << std::endl;
    }

    ReadUdpAddr rua;
    readUdpAddr(rua, socket_data);

    CameraSimulator cam_sim(rua.cam_port, rua.ip_control, rua.ctrl_port_recv_camera);

    // 设置周期性发送线程中发送间隔
    cam_sim.setPeriodicInterval(1000);

    cam_sim.powerOff();

    while (true) {

        cam_sim.init();

        // Note: 测试 时 直接上电
        cam_sim.powerOn(3);

        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
