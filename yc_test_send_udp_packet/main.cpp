#include "udp_packet.h"
#include "udpconnect.h"
#include <camera_sim.h>
#include <read_udp_addr.hpp>
#include <timer_period.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include <log_def.h>
#include <log_init.h>

int main() {
    log_init(nullptr);

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

    // 获取 Windows 主机的 IP 地址
    auto getWindowsVethIP_fromCmd = []() -> std::string {
        std::array<char, 128> buffer;
        std::string           result;
        FILE                 *pipe = popen("ip route | grep default | awk '{print $3}'", "r");
        if (!pipe)
            return {};
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        pclose(pipe);
        if (!result.empty() && result.back() == '\n')
            result.pop_back();
        return result;
    };

    // Note: 与检测仪互发 检测仪在win中 仿真模型载wsl中
    std::string win_ip = getWindowsVethIP_fromCmd();
    printf("Windows vEthernet IP: %s\n", win_ip.c_str());
    int port      = 6000; // 仿真模型的监听端口
    int port_send = 6001; // 仿真模型发送端口
    int port_dst  = 7000; // 检测仪的监听端口 (windows)

    using namespace std::chrono_literals;

    CameraSimulator cam_sim(port, port_send, win_ip, port_dst);

    // 设置周期性发送线程中发送间隔
    // cam_sim.setPeriodicInterval(1000);

    cam_sim.init();

    cam_sim.setConnectToJCY(true);

    std::this_thread::sleep_for(3s);

    cam_sim.start();

    // Note: 测试直接拍照
    // cam_sim.testPhotoing();

    SharedMemoryInput  shm_input;
    SharedMemoryOutput shm_output;

    auto *power_supply_status = &shm_input.m_FacilitiesPowerSupplyStatusParasMsg.St_FacilitiesPowerSupplyStatusData.ArrU1_FacilitiesPowerSupplyStatus[5];

    int64_t count = 0;
    while (true) {
        *power_supply_status = 2; // 快速上电
        // *power_supply_status = 0; // NA
        cam_sim.step(&shm_input, &shm_output);
        std::this_thread::sleep_for(10ms);
        count++;
        if (count >= 1e9) {
            count = 0;
            break;
        }
    }

    return 0;
}
