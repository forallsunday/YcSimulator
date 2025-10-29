#include "xml_api.h"
#include "xml_printf.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <vector>

/*udp发送node_id*/
std::map<std::string, node> g_udp_ndd;

typedef std::map<std::string, node>::iterator NODE_ITR;

void udp_node_insert_d(char *topic, const int idx) {
    std::string tmp(topic);
    g_udp_ndd[tmp].idx = idx;
}

int find_node_d(char *topic) {
    int         res = -1;
    NODE_ITR    itr;
    std::string tmp(topic);
    itr = g_udp_ndd.find(tmp);
    if (itr == g_udp_ndd.end()) {
        return -1;
    } else {
        res = g_udp_ndd[tmp].idx;
    }
    return res;
}

/*udp事件消息映射共享内存和位消息*/
std::map<std::string, entry>                   g_udp_tp_d;
typedef std::map<std::string, entry>::iterator UDP_ITR_D;

void udp_topic_insert_d(char *topic, const int offset, const int len /*, const int udp_idx*/) {
    std::string tmp(topic);
    g_udp_tp_d[tmp].offset = offset;
    g_udp_tp_d[tmp].len    = len;
    //	g_udp_tp_d[tmp].udp_idx = udp_idx;
}

entry *find_udp_d(char *topic) {
    entry      *res = NULL;
    UDP_ITR_D   itr;
    std::string tmp(topic);
    itr = g_udp_tp_d.find(tmp);
    if (itr == g_udp_tp_d.end()) {
        return NULL;
    } else {
        res = &g_udp_tp_d[tmp];
    }
    return res;
}

void tcp_udp_parse_d(char *file_path, SOCKET_PARSE *socket_data) {
    int  temp_num     = 1;
    int  icp_num      = 0;
    int  sim_num      = 0;
    int  icp_node_num = 0;
    int  sim_node_num = 0;
    char app_name[50] = {0};

    xml_doc_type  p_doc;
    xml_node_type root_node    = get_root_node(file_path, &p_doc);
    xml_node_type tcp_udp_node = get_first_child_node(root_node, "tcp_udp");

    xml_node_type icp_node = get_first_child_node(tcp_udp_node, "udp_icp");
    memcpy(socket_data->server_ip[1], get_first_attribute_value(icp_node, "server_ip"), strlen(get_first_attribute_value(icp_node, "server_ip")));
    socket_data->port[1] = atoi(get_first_attribute_value(icp_node, "recv_port"));
    socket_data->port[2] = atoi(get_first_attribute_value(icp_node, "send_port"));

    xml_node_type sim_node = get_first_child_node(tcp_udp_node, "udp_sim");
    memcpy(socket_data->server_ip[2], get_first_attribute_value(sim_node, "server_ip"), strlen(get_first_attribute_value(sim_node, "server_ip")));
    socket_data->port[3] = atoi(get_first_attribute_value(sim_node, "recv_port"));
    socket_data->port[4] = atoi(get_first_attribute_value(sim_node, "send_port"));

    xml_node_type monitor_node = get_first_child_node(tcp_udp_node, "udp_monitor");
    memcpy(socket_data->server_ip[3], get_first_attribute_value(monitor_node, "server_ip"), strlen(get_first_attribute_value(monitor_node, "server_ip")));
    socket_data->port[5] = atoi(get_first_attribute_value(monitor_node, "icp_port"));
    socket_data->port[6] = atoi(get_first_attribute_value(monitor_node, "sim_port"));

    xml_node_type simulator_node = get_first_child_node(root_node, "simulator_0");
    //	xml_node_type shm_node = get_first_child_node(simulator_node,"SharedMemoryName");
    //	memcpy(socket_data->shm_name,get_first_attribute_value(shm_node,"SharedMemoryName"),strlen(get_first_attribute_value(shm_node,"SharedMemoryName")));
    memcpy(socket_data->shm_name, "cadi_15b", strlen("cadi_15b"));
    if (socket_data->shm_name == NULL) {
        printf("SharedMemoryName is NULL");
    }
    xml_node_type ShMS_node = get_first_child_node(simulator_node, "SharedMemorySize");
    socket_data->shm_size   = atoi(get_first_attribute_value(ShMS_node, "SharedMemorySize"));
    if (socket_data->shm_size <= 0) {
        printf("SharedMemorySize is error");
    }

    int           ip_idx          = 0;
    xml_node_type icp_client_node = get_first_child_node(tcp_udp_node, "ICP");
    icp_num                       = get_child_node_count(icp_client_node, "client_ip");
    socket_data->icp_num          = icp_num;
    xml_node_type icp_c_ip_node   = get_first_child_node(icp_client_node, "client_ip");
    for (int i = 0; i < icp_num; i++) {

        memcpy(socket_data->all_ip[ip_idx], get_first_attribute_value(icp_c_ip_node, "ip"), strlen(get_first_attribute_value(icp_c_ip_node, "ip")));
        socket_data->all_port[ip_idx] = atoi(get_first_attribute_value(icp_c_ip_node, "port"));
        icp_node_num                  = get_child_node_count(icp_c_ip_node, "SIMROLE");

        xml_node_type icp_SIMROLE_node = get_first_child_node(icp_c_ip_node, "SIMROLE");
        for (int j = 0; j < icp_node_num; j++) {
            udp_node_insert_d(get_first_attribute_value(icp_SIMROLE_node, "NodeID"), ip_idx);
            xml_node_type Tmp0_node = get_next_sibling_node(icp_SIMROLE_node, "SIMROLE");
            icp_SIMROLE_node        = Tmp0_node;
        }
        xml_node_type Tmp1_node = get_next_sibling_node(icp_c_ip_node, "client_ip");
        icp_c_ip_node           = Tmp1_node;
        ip_idx++;
    }

    xml_node_type sim_client_node = get_first_child_node(tcp_udp_node, "SIM");
    sim_num                       = get_child_node_count(sim_client_node, "client_ip");
    socket_data->sim_num          = sim_num;
    xml_node_type sim_c_ip_node   = get_first_child_node(sim_client_node, "client_ip");
    for (int i = 0; i < sim_num; i++) {
        memcpy(socket_data->all_ip[ip_idx], get_first_attribute_value(sim_c_ip_node, "ip"), strlen(get_first_attribute_value(sim_c_ip_node, "ip")));
        socket_data->all_port[ip_idx] = atoi(get_first_attribute_value(sim_c_ip_node, "port"));
        sim_node_num                  = get_child_node_count(sim_c_ip_node, "SIMROLE");

        xml_node_type sim_SIMROLE_node = get_first_child_node(sim_c_ip_node, "SIMROLE");
        for (int j = 0; j < sim_node_num; j++) {
            udp_node_insert_d(get_first_attribute_value(sim_SIMROLE_node, "NodeID"), i);
            xml_node_type Tmp2_node = get_next_sibling_node(sim_SIMROLE_node, "SIMROLE");
            sim_SIMROLE_node        = Tmp2_node;
        }
        xml_node_type Tmp3_node = get_next_sibling_node(sim_c_ip_node, "client_ip");
        sim_c_ip_node           = Tmp3_node;
        ip_idx++;
    }

    int   len            = 0;
    int   offset         = 0;
    char  Module_sel[50] = {0};
    char *msg_type;
    int   count_sub = 0;
    int   count_pub = 0;

    xml_node_type MNum_node = get_first_child_node(simulator_node, "ModelNum");
    int           model_num = atoi(get_first_attribute_value(MNum_node, "ModelNum"));
    for (int i = 0; i < model_num; i++) {
        int sub_num_count = 0;
        sprintf(Module_sel, "Module%d", i);
        xml_node_type Moudle_i_node = get_first_child_node(simulator_node, Module_sel);

        xml_node_type MsgInfo_node = get_first_child_node(Moudle_i_node, "MsgInfo");

        xml_node_type sub_node  = get_first_child_node(MsgInfo_node, "sub");
        int           count_sub = get_child_node_count(sub_node, "MsgID");

        xml_node_type MsgID_sub_node = get_first_child_node(sub_node, "MsgID");
        for (int m = 0; m < count_sub; m++) {
            msg_type = get_first_attribute_value(MsgID_sub_node, "MsgType");
            len      = atoi(get_first_attribute_value(MsgID_sub_node, "MsgLen"));
            offset   = atoi(get_first_attribute_value(MsgID_sub_node, "MsgOffset"));
            if (strcmp(msg_type, "UDP_ICP") == 0 || strcmp(msg_type, "UDP_SIM") == 0) {
                udp_topic_insert_d(get_first_attribute_value(MsgID_sub_node, "TOPIC_ID"), offset, len);
            }

            xml_node_type Tmp_node = get_next_sibling_node(MsgID_sub_node, "MsgID");
            MsgID_sub_node         = Tmp_node;
        }
    }

    xml_node_type application_node = get_first_child_node(simulator_node, "application");
    int           app_num          = get_child_node_count(application_node, "app");

    xml_node_type app_node = get_first_child_node(application_node, "app");
    for (int i = 0; i < app_num; i++) {
        memset(app_name, 0, sizeof app_name);
        memcpy(app_name, get_first_attribute_value(app_node, "name"), strlen(get_first_attribute_value(app_node, "name")));

        // printf("app_name %s\n",app_name);
        // printf("find app_name = %s success\n",app_name);
        xml_node_type MsgInfo_node = get_first_child_node(app_node, "MsgInfo");
        xml_node_type sub_node     = get_first_child_node(MsgInfo_node, "sub");
        xml_node_type pub_node     = get_first_child_node(MsgInfo_node, "pub");
        count_sub                  = get_child_node_count(sub_node, "MsgID");
        count_pub                  = get_child_node_count(pub_node, "MsgID");

        xml_node_type MsgID_sub_node = get_first_child_node(sub_node, "MsgID");
        for (int m = 0; m < count_sub; m++) {
            msg_type = get_first_attribute_value(MsgID_sub_node, "MsgType");
            len      = atoi(get_first_attribute_value(MsgID_sub_node, "MsgLen"));
            offset   = atoi(get_first_attribute_value(MsgID_sub_node, "MsgOffset"));
            if (strcmp(msg_type, "UDP_ICP") == 0 || strcmp(msg_type, "UDP_SIM") == 0) {
                udp_topic_insert_d(get_first_attribute_value(MsgID_sub_node, "TOPIC_ID"), offset, len);
            }

            xml_node_type Tmp_node = get_next_sibling_node(MsgID_sub_node, "MsgID");
            MsgID_sub_node         = Tmp_node;
        }

        xml_node_type Tmp_node = get_next_sibling_node(app_node, "app");
        app_node               = Tmp_node;
    }
}
