#include "HeartBeat.h"

// udp所用到的头文件
#include "udpconnect.h"
#include "xml_api.h"

// 引用model中定义的对象
extern SOCKET_PARSE socket_data;
extern UdpConnect   udp_connect;

HeartBeat::HeartBeat(chrono::milliseconds inTime)
    : m_secInterval(inTime), m_stopFlag(false) {
    // 现在可以start-stop-start-stop
}

HeartBeat::~HeartBeat() {
    // 停止线程发送数据
    Stop();
}

void HeartBeat::Start() {
    // 如果已经有该线程了则退出
    if (m_threadWorker.joinable()) {
        return;
    }
    m_stopFlag     = false;
    m_threadWorker = thread([this] {
        unique_lock<mutex> lock(m_mTex);
        while (!m_stopFlag) {
            // 发送心跳的处理函数
            Send();
            // 这个是等待m_secInterval时间然后进行触发执行
            m_conVar.wait_for(lock, m_secInterval, [this] {
                return m_stopFlag.load();
            });
        }
    });
}

void HeartBeat::Stop() {
    {
        lock_guard<mutex> lock(m_mTex);
        m_stopFlag = true;
    }
    m_conVar.notify_all();
    if (m_threadWorker.joinable()) {
        m_threadWorker.join();
    }
}

void HeartBeat::Send() {
    m_stUdpHeader.uiQos = 0x10000000; // 最高位置1，机载有qos判断
    struct timeval tv;
    struct tm      tm_info;
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_info);
    UINT64 timeNow = (UINT64)((((tm_info.tm_hour * 60 + tm_info.tm_min) * 60 + tm_info.tm_sec) * 1e6) + tv.tv_usec) * 1e3;

    /************************握手消息******************/
    // EWSM的心跳==============================================注意：EWFT是EWSM只要上线了，EWFT就上线了
    memset(&m_stUdpHeader, 0, sizeof(m_stUdpHeader));
    // m_stUdpHeader.dest = V_NODE_SYMM;
    // msgSend.dest = V_NODE_SYMD;
    m_stUdpHeader.msgSpec    = 0;
    m_stUdpHeader.topicId    = (0x80001234); // 握手消息
    m_stUdpHeader.time_tag   = 0;
    m_stUdpHeader.payloadLen = sizeof(OK_MSG);

    OK_MSG ok_msg;
    memset(&ok_msg, 0, sizeof(OK_MSG));
    ok_msg.block_id = 0x80001234; // 握手消息
    ok_msg.app_ok   = 1;          // 握手成功

    stringstream ss1;
    ss1 << hex << V_NODE_SYMM;

    string hexStr;

    if (strlen(ss1.str().c_str()) % 2 != 0) {
        hexStr = "0x0" + ss1.str();
    } else {
        hexStr = "0x" + ss1.str();
    }

    int idx1 = find_node_d((char *)hexStr.c_str());

    if (idx1 < 0) {
        printf("icp uiDest = %s idx = %d no dest  心跳\n", hexStr.c_str(), idx1);
    }
    //	else
    //	{
    //		printf(" addr is %s, port is %d 心跳 %d \n",
    //			socket_data.all_ip[idx1],
    //			socket_data.all_port[idx1],
    //			idx1);
    //	}

    //		udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx], socket_data.all_port[idx]); //SYMM UDP发送

    m_stUdpHeader.source = V_NODE_EWSM;
    ok_msg.msg_src       = V_NODE_EWSM; // 注册EWSM-自己
    m_stUdpHeader.dest   = V_NODE_SYMM; // 向SYMM-发的
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx1], socket_data.all_port[idx1]); // SYMM UDP发送

    m_stUdpHeader.topicId = (0x8400fff0); // 握手消息
    ok_msg.block_id       = 0x8400fff0;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx1], socket_data.all_port[idx1]); // SYMM UDP发送

    m_stUdpHeader.topicId = (0xda00ff06); // 握手消息
    ok_msg.block_id       = 0xda00ff06;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx1], socket_data.all_port[idx1]); // SYMM UDP发送

    // 发送MPHL 心跳 健康管理
    stringstream ss2;
    ss2 << hex << V_NODE_MPHL;

    if (strlen(ss2.str().c_str()) % 2 != 0) {
        hexStr = "0x0" + ss2.str();
    } else {
        hexStr = "0x" + ss2.str();
    }

    int idx2 = find_node_d((char *)hexStr.c_str());

    if (idx2 < 0) {
        printf("icp uiDest = %s idx = %d no dest  心跳\n", hexStr.c_str(), idx2);
    }
    //	else
    //	{
    //		printf(" addr is %s, port is %d 心跳 %d\n",
    //			socket_data.all_ip[idx2],
    //			socket_data.all_port[idx2],
    //			idx2);
    //	}

    m_stUdpHeader.source = V_NODE_EWSM;
    ok_msg.msg_src       = V_NODE_EWSM;
    m_stUdpHeader.dest   = V_NODE_MPHL; // 注册MPHL 健康管理

    m_stUdpHeader.topicId = (0x80001234); // 握手消息
    ok_msg.block_id       = 0x80001234;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx2], socket_data.all_port[idx2]); // MPHL UDP发送

    m_stUdpHeader.topicId = (0x8400fff0); // 握手消息
    ok_msg.block_id       = 0x8400fff0;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx2], socket_data.all_port[idx2]); // MPHL UDP发送

    m_stUdpHeader.topicId = (0xda00ff06); // 握手消息
    ok_msg.block_id       = 0xda00ff06;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx2], socket_data.all_port[idx2]); // MPHL UDP发送

    // 发送SRMM 心跳 健康管理
    stringstream ss3;
    ss3 << hex << V_NODE_SRMM;

    if (strlen(ss3.str().c_str()) % 2 != 0) {
        hexStr = "0x0" + ss3.str();
    } else {
        hexStr = "0x" + ss3.str();
    }

    int idx3 = find_node_d((char *)hexStr.c_str());

    if (idx3 < 0) {
        printf("icp uiDest = %s idx = %d no dest  心跳\n", hexStr.c_str(), idx3);
    }
    //		else
    //		{
    //			printf(" addr is %s, port is %d 心跳 %d\n",
    //				socket_data.all_ip[idx3],
    //				socket_data.all_port[idx3],
    //				idx3);
    //		}
    m_stUdpHeader.source  = V_NODE_EWSM;
    ok_msg.msg_src        = V_NODE_EWSM;
    m_stUdpHeader.dest    = V_NODE_SRMM;  // 注册SRMM 健康管理
    m_stUdpHeader.topicId = (0x80001234); // 握手消息
    ok_msg.block_id       = 0x80001234;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx3], socket_data.all_port[idx3]); // SRMM UDP发送

    m_stUdpHeader.topicId = (0x8400fff0); // 握手消息
    ok_msg.block_id       = 0x8400fff0;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx3], socket_data.all_port[idx3]); // SRMM UDP发送

    m_stUdpHeader.topicId = (0xda00ff06); // 握手消息
    ok_msg.block_id       = 0xda00ff06;   // 握手消息
    memcpy(m_stUdpHeader.pPayload, &ok_msg, sizeof(ok_msg));
    udp_connect.SendData((char *)&m_stUdpHeader, 48 + sizeof(OK_MSG), (char *)socket_data.all_ip[idx3], socket_data.all_port[idx3]); // SRMM UDP发送
}
