#pragma once

#include <fstream>
#include <iostream>
#include <rapidxml.hpp>
#include <sstream>
#include <string>
#include <vector>

struct UDPSimInfo {
    std::string SIMROLE; // SRMM
    std::string Addr;    // IP
    int         Recv_port;
    int         Send_port;
    std::string NodeName; // V_NODE_SRMM
    int         NodeID;   // 1001
};

inline bool loadXmlDoc(const std::string &path, rapidxml::xml_document<> &doc, std::vector<char> &xml_copy) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open xml file: " << path << "\n";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xml_content = buffer.str();

    xml_copy.assign(xml_content.begin(), xml_content.end());
    xml_copy.push_back('\0');

    try {
        doc.parse<0>(&xml_copy[0]);
    } catch (const rapidxml::parse_error &e) {
        std::cerr << "XML parse error: " << e.what() << "\n";
        return false;
    }
    return true;
}

inline bool parseUdpCommFile(const std::string &path, std::vector<UDPSimInfo> &out_list) {
    rapidxml::xml_document<> doc;
    std::vector<char>        xml_copy;
    if (!loadXmlDoc(path, doc, xml_copy))
        return false;

    auto root = doc.first_node("UdpCommFile");
    if (!root)
        return false;

    auto nodeList = root->first_node("UDPNodeList");
    if (!nodeList)
        return false;

    for (auto nodeSim = nodeList->first_node("UDPSIMInfo"); nodeSim; nodeSim = nodeSim->next_sibling("UDPSIMInfo")) {
        UDPSimInfo info;

        // 读取 UDPSIMInfo 属性
        info.SIMROLE   = nodeSim->first_attribute("SIMROLE") ? nodeSim->first_attribute("SIMROLE")->value() : "";
        info.Addr      = nodeSim->first_attribute("Addr") ? nodeSim->first_attribute("Addr")->value() : "";
        info.Recv_port = nodeSim->first_attribute("Recv_port") ? std::stoi(nodeSim->first_attribute("Recv_port")->value()) : 0;
        info.Send_port = nodeSim->first_attribute("Send_port") ? std::stoi(nodeSim->first_attribute("Send_port")->value()) : 0;

        // 读取 SIMROLE 子节点
        auto nodeRole = nodeSim->first_node("SIMROLE");
        if (nodeRole) {
            info.NodeName = nodeRole->first_attribute("NodeName") ? nodeRole->first_attribute("NodeName")->value() : "";
            info.NodeID   = nodeRole->first_attribute("NodeID") ? std::stoi(nodeRole->first_attribute("NodeID")->value()) : 0;
        }

        out_list.push_back(info);
    }

    return true;
}
