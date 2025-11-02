#include "udp_packet.h"
#include "udpconnect.h"
#include <atomic>
#include <camera_sim.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>
#include <udp_packet_log.h>
#include <yc_udp_xml_api.hpp>

int main() {

    while (true) {
        // 从自己写的xml配置文件获取ip和端口
        std::string ip_icp_server, ip_control, ip_camera;
        int         ctrl_port_recv_icp, ctrl_port_recv_camera, cam_port;
        if (parseXmlYcUdpConfig(
                "./yc_udp_config.xml", &ip_icp_server, &ip_control,
                &ctrl_port_recv_icp, &ctrl_port_recv_camera, &ip_camera, &cam_port)) {
        } else {
            printf("[ERR] failed to parse yc_udp_config.xml\n");
        }

        CameraSimulator cam_sim(cam_port, ip_control, ctrl_port_recv_camera);

        cam_sim.setPeriodicSendInterval(1000);

        cam_sim.init();

        // Note: 测试 时 直接上电
        cam_sim.powerOn(3);

        std::this_thread::sleep_for(std::chrono::seconds(15));
    }

    return 0;
}
