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
    std::string *ip_icp, int *port_icp,
    std::string *ip_control, int *port_control_on_icp, int *port_control_on_camera,
    std::string *ip_camera, int *port_camera) {
    if (!ip_icp || !port_icp || !ip_control || !port_control_on_icp || !port_control_on_camera || !ip_camera || !port_camera)
        return false;

    rapidxml::xml_document<> doc;
    std::vector<char>        xml_copy;
    if (!loadXmlDoc(path, doc, xml_copy))
        return false;

    auto root = doc.first_node("udp");
    if (!root)
        return false;

    // udp_icp
    auto node_icp = root->first_node("udp_icp");
    if (node_icp) {
        *ip_icp   = node_icp->first_attribute("ip") ? node_icp->first_attribute("ip")->value() : "0.0.0.0";
        *port_icp = node_icp->first_attribute("port") ? std::stoi(node_icp->first_attribute("port")->value()) : 0;
    } else {
        *ip_icp   = "0.0.0.0";
        *port_icp = 0;
    }

    // udp_control
    auto node_ctrl = root->first_node("udp_control");
    if (node_ctrl) {
        *ip_control             = node_ctrl->first_attribute("ip") ? node_ctrl->first_attribute("ip")->value() : "0.0.0.0";
        *port_control_on_icp    = node_ctrl->first_attribute("port_on_icp") ? std::stoi(node_ctrl->first_attribute("port_on_icp")->value()) : 0;
        *port_control_on_camera = node_ctrl->first_attribute("port_on_camera") ? std::stoi(node_ctrl->first_attribute("port_on_camera")->value()) : 0;
    } else {
        *ip_control             = "0.0.0.0";
        *port_control_on_icp    = 0;
        *port_control_on_camera = 0;
    }

    // udp_camera
    auto node_cam = root->first_node("udp_camera");
    if (node_cam) {
        *ip_camera   = node_cam->first_attribute("ip") ? node_cam->first_attribute("ip")->value() : "0.0.0.0";
        *port_camera = node_cam->first_attribute("port") ? std::stoi(node_cam->first_attribute("port")->value()) : 0;
    } else {
        *ip_camera   = "0.0.0.0";
        *port_camera = 0;
    }

    return true;
}
