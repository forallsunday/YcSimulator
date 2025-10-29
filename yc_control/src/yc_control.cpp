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

    UdpAddress addr_icp;    // icp server 地址
    UdpAddress addr_camera; // 相机仿真 地址

    // 从xml配置文件获取ICP和机载主控模拟器的地
    if (parseYcUdpXml("yc_udp_config.xml", "udp_icp", &addr_icp.ip, &addr_icp.port)) {
        printf("ERR: parse yc_udp_config.xml for udp_icp failed\n");
        return 0;
    }

    if (parseYcUdpXml("yc_udp_config.xml", "udp_camera", &addr_camera.ip, &addr_camera.port)) {
        printf("ERR: parse yc_udp_config.xml failed for udp_camera\n");
        return 0;
    }

    // // Note: 调试时手动指定ip和端口 (假定)
    // addr_icp.ip      = "192.168.1.111";
    // addr_icp.port    = 10000;
    // addr_camera.ip   = "192.168.1.222";
    // addr_camera.port = 10001;

    // 解析xml文件 获取icp节点(V_NODE_XXX)对应的所有地址
    SOCKET_PARSE data; // xml解析的数据
    tcp_udp_parse_d("./ModuleConfig.xml", &data);

    IcpNodeMap icp_node_map; // icp节点对应的端口

    // 需要解析的icp节点
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
            printf("icp uiDest = %s idx = %d no dest\n", node_str.c_str(), idx);
        } else {
            printf(" addr is %s, port is %d \n", data.all_ip[idx], data.all_port[idx]);
            // 放入map中
            icp_node_map[node] = {data.all_ip[idx], data.all_port[idx]};
        }
    }

    // 机载主控模拟器
    ControlSimulator ctrl_sim(addr_icp, addr_camera, icp_node_map);
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