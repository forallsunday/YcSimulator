// #include <AOXEAppDef.h>
#include <control_sim.h>
#include <id_name.hpp>
#include <read_udp_addr.hpp>
#include <xml_api.h>
#include <yc_udp_xml_api.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <log.h>
#include <log_init.h>

// 转换为16进制字符串
std::string hexString(int value) {
    std::stringstream ss;
    ss << "0x"
       << std::hex
       << std::nouppercase  // 不转换为大写
       << std::setw(4)      // 最少 4 位
       << std::setfill('0') // 前面补 0
       << value;
    return ss.str();
};

int main() {

    log_init("control_sim.log");

    // Note: 读取所有icp节点的ip和端口
    MapNodeAddr icp_node_map; // icp节点对应的端口

    const std::string path_UDPNodeConfig = "./UDPNodeConfig_A.xml";

    std::vector<UDPSimInfo> sim_list;
    if (!parseUdpCommFile(path_UDPNodeConfig, sim_list)) {
        log_warn("Failed to parse UDP XML: %s", path_UDPNodeConfig.c_str());
        return -1;
    }

    for (const auto &s : sim_list) {
        // NodeID 作为 key，Addr + Recv_port 作为 value
        icp_node_map[(FUNCTION_NODE_TYPE)s.NodeID] = {s.Addr, s.Recv_port};

        // 输出日志，模拟你原来的格式
        log_info("查找ICP Node=<%s>, hex=%s, ip = %s, port = %d",
                 s.NodeName.c_str(),
                 hexString(s.NodeID).c_str(),
                 s.Addr.c_str(),
                 s.Recv_port);
    }

    // 解析xml文件 获取相机仿真、机载一直的ip port
    SOCKET_PARSE socket_data; // xml解析的数据
    // 要检查的文件路径
    const std::string config_file = "./ModuleConfig.xml";
    // const std::string config_file = "/mnt/d/Documents/C-Project/YcSimulator/ModuleConfig.xml";
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
    // // 查看所有node
    // printf_all_node();

    ReadUdpAddr rua;
    readUdpAddr(rua, socket_data);

    // 节点以UDPNodeConfig.xml为准
    // 监听icp发来消息的端口
    rua.ctrl_port_recv_icp = icp_node_map[V_NODE_IRRM].port;
    log_info("监听icp发来消息的端口为 %d", rua.ctrl_port_recv_icp);

    // 机载移植
    ControlSimulator ctrl_sim(
        rua.ip_icp_server, rua.ip_camera,
        rua.ctrl_port_recv_icp, rua.ctrl_port_recv_camera, rua.cam_port,
        icp_node_map);

    // 初始化 建立udp连接 接收从icp和相机仿真发来的数据
    ctrl_sim.init();

    // 心跳计数器
    uint32_t heartbit = 0;
    //
    bool running = true;
    while (running) {
        ++heartbit;

        log_info("HeartBit: %u", heartbit);

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}