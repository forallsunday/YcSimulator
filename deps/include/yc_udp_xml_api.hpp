#pragma once

#include <fstream>
#include <iostream>
#include <rapidxml.hpp>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <rapidxml.hpp>
#include <sstream>
#include <string>
#include <vector>

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

// 合成函数：一次解析全部
inline bool parseXmlYcUdpConfig(
    const std::string &path,
    std::string       *ip_icp_server,
    std::string *ip_control, int *ctrl_port_recv_icp, int *ctrl_port_recv_camera,
    std::string *ip_camera, int *cam_port) {

    if (!ip_icp_server || !ip_control || !ctrl_port_recv_icp || !ctrl_port_recv_camera || !ip_camera || !cam_port)
        return false;

    rapidxml::xml_document<> doc;
    std::vector<char>        xml_copy;
    if (!loadXmlDoc(path, doc, xml_copy))
        return false;

    auto root = doc.first_node("udp");
    if (!root)
        return false;

    // === udp_icp_server ===
    if (auto node_icp = root->first_node("udp_icp_server")) {
        *ip_icp_server = node_icp->first_attribute("ip") ? node_icp->first_attribute("ip")->value() : "0.0.0.0";
    } else {
        *ip_icp_server = "0.0.0.0";
    }

    // === udp_control ===
    if (auto node_ctrl = root->first_node("udp_control")) {
        *ip_control            = node_ctrl->first_attribute("ip") ? node_ctrl->first_attribute("ip")->value() : "0.0.0.0";
        *ctrl_port_recv_icp    = node_ctrl->first_attribute("ctrl_port_recv_icp") ? std::stoi(node_ctrl->first_attribute("ctrl_port_recv_icp")->value()) : 0;
        *ctrl_port_recv_camera = node_ctrl->first_attribute("ctrl_port_recv_camera") ? std::stoi(node_ctrl->first_attribute("ctrl_port_recv_camera")->value()) : 0;
    } else {
        *ip_control            = "0.0.0.0";
        *ctrl_port_recv_icp    = 0;
        *ctrl_port_recv_camera = 0;
    }

    // === udp_camera ===
    if (auto node_cam = root->first_node("udp_camera")) {
        *ip_camera = node_cam->first_attribute("ip") ? node_cam->first_attribute("ip")->value() : "0.0.0.0";
        *cam_port  = node_cam->first_attribute("cam_port") ? std::stoi(node_cam->first_attribute("cam_port")->value()) : 0;
    } else {
        *ip_camera = "0.0.0.0";
        *cam_port  = 0;
    }

    return true;
}
