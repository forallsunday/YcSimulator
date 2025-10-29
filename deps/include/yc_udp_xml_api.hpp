#pragma once

#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief 解析 UDP XML 配置文件，获取指定节点的 IP 和端口
 *
 * @param path XML 文件路径
 * @param node_name 节点名称，例如 "udp_icp" / "udp_control" / "udp_camera"
 * @param ip 输出 IP 字符串
 * @param port 输出端口
 * @return true 成功解析
 * @return false 解析失败
 */
#pragma once

#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline bool parseYcUdpXml(
    const std::string &path, const std::string &node_name, std::string *ip, int *port) {
    if (!ip || !port)
        return false; // 防止空指针

    // 读取 XML 文件
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open xml file: " << path << "\n";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xml_content = buffer.str();

    std::vector<char> xml_copy(xml_content.begin(), xml_content.end());
    xml_copy.push_back('\0');

    rapidxml::xml_document<> doc;
    try {
        doc.parse<0>(&xml_copy[0]);
    } catch (const rapidxml::parse_error &e) {
        std::cerr << "XML parse error: " << e.what() << "\n";
        return false;
    }

    rapidxml::xml_node<> *root = doc.first_node("udp");
    if (!root) {
        std::cerr << "No <udp> root node found\n";
        return false;
    }

    rapidxml::xml_node<> *node = root->first_node(node_name.c_str());
    if (!node) {
        std::cerr << "No <" << node_name << "> node found\n";
        return false;
    }

    if (auto ip_attr = node->first_attribute("ip"))
        *ip = ip_attr->value();
    else
        *ip = "0.0.0.0";

    if (auto port_attr = node->first_attribute("port"))
        *port = std::stoi(port_attr->value());
    else
        *port = 0;

    return true;
}
