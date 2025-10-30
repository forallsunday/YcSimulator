#include <AOXEAppDef.h>
#include <control_sim.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <xml_api.h>
#include <yc_udp_xml_api.hpp>

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

    // 从自己写的xml配置文件获取ip和端口
    // ip: ICP、机载主控模拟器、相机仿真模型
    std::string ip_icp, ip_control, ip_camera;
    // port: ICP、机载主控接收ICP、机载主控接收相机、相机仿真模型
    int port_icp, port_control_on_icp, port_control_on_camera, port_camera;

    // if (parseXmlYcUdpConfig("./yc_udp_config.xml",
    if (parseXmlYcUdpConfig("/mnt/d/Documents/C-Project/YcSimulator/yc_udp_config.xml",
                            &ip_icp, &port_icp,
                            &ip_control, &port_control_on_icp, &port_control_on_camera,
                            &ip_camera, &port_camera)) {
    } else {
        printf("[ERR] failed to parse yc_udp_config.xml\n");
    }

    // 解析xml文件 获取icp节点(V_NODE_XXX)对应的所有地址
    SOCKET_PARSE data; // xml解析的数据
    // Note: 没有文件时需要注释掉下面这行
    // tcp_udp_parse_d("./ModuleConfig.xml", &data);

    IcpNodeMap icp_node_map; // icp节点对应的端口

    // 需要发送的icp节点
    std::vector<FUNCTION_NODE_TYPE> node_vec = {
        V_NODE_SYMM,
        V_NODE_IRRM,
    };

    for (const auto &node : node_vec) {
        // 将node转换为16进制字符串(xml中的形式)
        std::string node_str = hexString(node);
        // 查询node对应的idx
        int idx = find_node_d((char *)node_str.c_str());
        if (idx < 0) {
            printf("[WARN] ICP Node = %s, idx = %d, no dest\n", node_str.c_str(), idx);
        } else {
            printf("[INFO] ICP Node = %s, ip = %s, port = %d \n",
                   node_str.c_str(), data.all_ip[idx], data.all_port[idx]);
            // 放入map中
            icp_node_map[node] = {data.all_ip[idx], data.all_port[idx]};
        }
    }

    UdpAddress addr_icp    = {ip_icp, port_icp};       // icp server 地址
    UdpAddress addr_camera = {ip_camera, port_camera}; // 相机仿真 地址

    // 机载主控模拟器
    ControlSimulator ctrl_sim(
        port_control_on_icp, port_control_on_camera, addr_icp, addr_camera, icp_node_map);
    // 初始化 建立udp连接 接收从icp和相机仿真发来的数据
    ctrl_sim.init();

    // 心跳计数器
    uint32_t heartbit = 0;
    //
    bool running = true;
    while (running) {
        ++heartbit;

        // printf("HeartBit: %llu\n", heartbit); // for uint64_t
        printf("HeartBit: %u\n", heartbit);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}