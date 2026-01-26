#ifndef READ_UDP_ADDR_HPP
#define READ_UDP_ADDR_HPP

#include <log.h>
#include <string>
#include <xml_api.h>

// 读取机载移植和相机仿真相互之间的UDP的ip和端口

struct ReadUdpAddr {
    // 机载移植、相机仿真的ip
    std::string ip_control, ip_camera;
    // 机载移植监听icp消息的端口、机载移植监听相机仿真消息的端口、相机仿真监听消息的端口
    int port_cam_listen_ctrl; // 相机仿真监听机载移植消息的端口
    int port_cam_send2_ctrl;  // 相机仿真向机载移植发送消息的端口
    int port_ctrl_listen_cam; // 机载移植监听相机仿真消息的端口
    int port_ctrl_send2_cam;  // 机载移植向相机仿真的发送端口
};

inline void readUdpAddr(ReadUdpAddr &rua, const SOCKET_PARSE &socket_data) {

    // 辅助函数：查找节点并直接赋值
    auto findAndAssign = [&](const char *node_id, const char *desc,
                             std::string &ip_ref, int &port_ref) {
        int idx = find_node_d(const_cast<char *>(node_id));
        if (idx < 0) {
            log_warn("%s Node = %s, idx = %d 未找到", desc, node_id, idx);
        } else {
            log_info("%s Node = %s, ip = %s, port = %d",
                     desc, node_id, socket_data.all_ip[idx], socket_data.all_port[idx]);
            ip_ref   = socket_data.all_ip[idx];
            port_ref = socket_data.all_port[idx];
        }
    };

    findAndAssign("0x9301", "相机仿真监听机载移植消息的端口",
                  rua.ip_camera, rua.port_cam_listen_ctrl);
    findAndAssign("0x9302", "相机仿真向机载移植发送消息的端口",
                  rua.ip_camera, rua.port_cam_send2_ctrl);
    findAndAssign("0x9303", "机载移植监听相机仿真消息的端口",
                  rua.ip_control, rua.port_ctrl_listen_cam);
    findAndAssign("0x9304", "机载移植向相机仿真的发送端口",
                  rua.ip_control, rua.port_ctrl_send2_cam);
}

#endif // READ_UDP_ADDR_HPP
