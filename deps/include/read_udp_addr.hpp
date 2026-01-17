#include <log.h>
#include <string>
#include <xml_api.h>

// 获取仿真模型和机载移植的ip和port
struct ReadUdpAddr {
    // icp、机载移植、相机仿真的ip
    std::string ip_icp_server, ip_control, ip_camera;
    // 机载移植监听icp消息的端口、机载移植监听相机仿真消息的端口、相机仿真监听消息的端口
    int ctrl_port_recv_icp, ctrl_port_recv_camera, cam_port;
};

void readUdpAddr(ReadUdpAddr &rua, const SOCKET_PARSE &socket_data) {
    // V_NODE_IRRM
    std::string node_id_str_0 = "0x076d";
    int         idx0          = find_node_d((char *)node_id_str_0.c_str());
    if (idx0 < 0) {
        log_warn("未找到在ControlSim上监听ICP消息的端口 Node = %s, idx = %d, no dest", node_id_str_0.c_str(), idx0);
    } else {
        log_info("在ControlSim上监听ICP消息的端口 Node = %s, ip = %s, port = %d",
                 node_id_str_0.c_str(), socket_data.all_ip[idx0], socket_data.all_port[idx0]);
        rua.ip_icp_server      = socket_data.all_ip[idx0];
        rua.ctrl_port_recv_icp = socket_data.all_port[idx0];
    }

    // ctrl_port_recv_camera
    std::string node_id_str_1 = "0x9301";
    int         idx1          = find_node_d((char *)node_id_str_1.c_str());
    if (idx1 < 0) {
        log_warn("未找到在ControlSim上监听CameraSim消息的端口 Node = %s, idx = %d, no dest", node_id_str_1.c_str(), idx1);
    } else {
        log_info("在ControlSim上监听CameraSim消息的端口 Node = %s, ip = %s, port = %d",
                 node_id_str_1.c_str(), socket_data.all_ip[idx1], socket_data.all_port[idx1]);
        rua.ip_control            = socket_data.all_ip[idx1];
        rua.ctrl_port_recv_camera = socket_data.all_port[idx1];
    }

    // cam_port
    std::string node_id_str_2 = "0x9401";
    int         idx2          = find_node_d((char *)node_id_str_2.c_str());
    if (idx2 < 0) {
        log_warn("未找到在CameraSim上监听消息的端口 Node = %s, idx = %d, no dest", node_id_str_2.c_str(), idx2);
    } else {
        log_info("在CameraSim上监听消息的端口 Node = %s, ip = %s, port = %d",
                 node_id_str_2.c_str(), socket_data.all_ip[idx2], socket_data.all_port[idx2]);
        rua.ip_camera = socket_data.all_ip[idx2];
        rua.cam_port  = socket_data.all_port[idx2];
    }
}