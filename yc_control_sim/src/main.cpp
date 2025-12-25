#include <AOXEAppDef.h>
#include <control_sim.h>
#include <id_name.hpp>
#include <read_udp_addr.hpp>
#include <xml_api.h>

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

    // 解析xml文件 获取icp节点(V_NODE_XXX)对应的所有地址
    SOCKET_PARSE socket_data; // xml解析的数据
    // 要检查的文件路径
    // const std::string config_file = "./ModuleConfig.xml";
    const std::string config_file = "/mnt/d/Documents/C-Project/YcSimulator/ModuleConfig.xml";
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

    MapNodeAddr icp_node_map; // icp节点对应的端口

    // todo: 让node_vec变为set
    // 需要发送的icp节点
    std::set<FUNCTION_NODE_TYPE> node_set = {
        // 监控
        V_NODE_ADAS,
        // ok_msg
        V_NODE_SYMM, V_NODE_MPHL, V_NODE_MPHR, V_NODE_SRMM,
        // V_TOPIC_IRRM_WORK_STATE_REPORT 对应:
        V_NODE_MPHL, V_NODE_SYMM, V_NODE_MPHR,
        // V_TOPIC_IRRM_IRST_OPERATIONAL_PARAS 对应:
        V_NODE_IIPM, V_NODE_DCLD, V_NODE_TMMM, V_NODE_DCRM, V_NODE_DCLM, V_NODE_DCRD, V_NODE_SRMM};

    for (const auto &node : node_set) {
        // 将node转换为16进制字符串(xml中的形式)
        std::string code_str  = hexString(node);
        const char* node_name = lookupNode(node);
        // 查询node对应的idx
        int idx = find_node_d((char *)code_str.c_str());
        if (idx < 0) {
            // printf("[WARN] ICP Node = %s, idx = %d, no dest\n", node_str.c_str(), idx);
            log_warn("查找ICP Node=<%s>, hex=%s, 未找到, idx = %d", node_name, code_str.c_str(), idx);
        } else {
            log_info("查找ICP Node=<%s>, hex=%s, ip = %s, port = %d", node_name, code_str.c_str(), socket_data.all_ip[idx], socket_data.all_port[idx]);
            // 放入map中
            icp_node_map[node] = {socket_data.all_ip[idx], socket_data.all_port[idx]};
        }
    }

    // // 查看所有node
    // printf_all_node();

    ReadUdpAddr rua;
    readUdpAddr(rua, socket_data);

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