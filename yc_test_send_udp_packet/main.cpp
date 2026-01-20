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

void timerTest() {
    TimerPeriod timer_test;

    timer_test.init(std::chrono::milliseconds(1200), []() {
        printf("[callback] TimerPeriod callback executed\n");
    });

    std::atomic<bool> exit{false};

    // ===============================
    // 控制定时器 start / stop 的线程
    // ===============================
    std::thread controller([&] {
        while (!exit.load()) {

            printf(">>> controller: START timer\n");
            timer_test.start();

            std::this_thread::sleep_for(std::chrono::milliseconds(1200));

            printf(">>> controller: STOP timer\n");
            timer_test.stop();

            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    });

    // ===============================
    // 主线程：打印 elapsedTime
    // ===============================
    while (true) {
        auto elapsed_ms = timer_test.elapsedTimeMs();

        if (elapsed_ms >= 0) {
            printf("[main] elapsed = %.1f ms\n", elapsed_ms);
        } else {
            printf("[main] timer not running\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

    exit = true;
    controller.join();
}

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

    std::string win_ip = getWindowsVethIP_fromCmd();
    printf("Windows vEthernet IP: %s\n", win_ip.c_str());

    ReadUdpAddr rua;

    // !与检测仪互发
    // rua.ip_control = "172.20.160.1"; // 发送到windows检测仪的ip
    rua.ip_control            = win_ip; // 发送到windows检测仪的ip
    rua.cam_port              = 6000;   // 仿真模型的监听端口
    rua.ctrl_port_recv_camera = 7000;   // 检测仪的监听端口 (windows)

    CameraSimulator cam_sim(rua.cam_port, rua.ip_control, rua.ctrl_port_recv_camera);

    // 设置周期性发送线程中发送间隔
    cam_sim.setPeriodicInterval(1000);

    cam_sim.init();

    cam_sim.start();

    // Note: 测试直接拍照
    cam_sim.testPhotoing();

    SharedMemoryInput  shm_input;
    SharedMemoryOutput shm_output;

    auto *power_supply_status = &shm_input.m_FacilitiesPowerSupplyStatusParasMsg.St_FacilitiesPowerSupplyStatusData.ArrU1_FacilitiesPowerSupplyStatus[5];

    using namespace std::chrono_literals;

    int count = 0;
    while (true) {
        *power_supply_status = 2; // 快速上电
        cam_sim.step(&shm_input, &shm_output);
        std::this_thread::sleep_for(10ms);
        count++;
        if (count >= 1000) {
            count = 0;
            break;
        }
    }
    while (true) {
        *power_supply_status = 4; // 下电
        cam_sim.step(&shm_input, &shm_output);
        std::this_thread::sleep_for(10ms);
        count++;
        if (count >= 200) {
            count = 0;
            break;
        }
    }
    // todo: 这里再次上电后，相机无法拍照，怀疑是状态没有复位
    while (true) {
        *power_supply_status = 2; // 快速上电
        cam_sim.step(&shm_input, &shm_output);
        std::this_thread::sleep_for(10ms);
        count++;
        if (count >= 30000000) {
            count = 0;
            break;
        }
    }

    return 0;
}
