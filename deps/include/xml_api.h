/************************************************************************
 *				成都飞机设计研究所 版权所有
 * 	 Copyright (C) 2011 CADI Inc. All Rights Reserved.
 ***********************************************************************/

/*
 * 修改历史：
 * 2023-12-21    heting，wanghaojie，北京华智信科技发展有限公司
 *               创建该文件。
 */

/*
 * @file： xml_api.h
 * @brief：
 *    <li>xml解析头文件</li>
 * @implements: DK2.3
 */

#ifndef _XML_API_H_
#define _XML_API_H_

/************************头文件********************************/
#include "msginfo.h"
#include "sysTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************宏定义********************************/
#define TOPICNUM 100 /*主题最大数量*/

/************************类型定义******************************/
typedef void *xml_node_type;

typedef struct {
    xml_node_type doc_node;
    char         *text;

} xml_doc_type;

typedef struct /*dds解析参数*/
{
    int  Stacksize;
    int  Priority;
    int  CPU;
    int  domain;
    int  subnum;
    int  pubnum;
    char subtopic[TOPICNUM][NAMELENGTH];
    char pubtopic[TOPICNUM][NAMELENGTH];
    char Addr[NAMELENGTH];
} DDS_PARSE;

typedef struct /*sync解析参数*/
{
    int Stacksize;
    int Priority;
    int CPU;
    int Simulator_Num;
} SYNC_PARSE;

typedef struct /* tcp_udp 解析后的参数结构体 */
{
    unsigned int shm_size;                 // 共享内存大小，从 <SharedMemorySize> 节点读取
    char         shm_name[NAMELENGTH];     // 共享内存名称，从 <SharedMemoryName> 节点读取（函数中固定为 "cadi_15b"）
    char         server_ip[4][NAMELENGTH]; // 主要服务端 IP
                                           // [1] udp_icp 的 server_ip
                                           // [2] udp_sim 的 server_ip
                                           // [3] udp_monitor 的 server_ip
                                           // [0] 未使用
    char all_ip[100][NAMELENGTH];          // 所有客户端 IP
                                           // 先存 ICP 客户端 IP，再存 SIM 客户端 IP
                                           // 对应函数中循环获取 <ICP>/<SIM> 节点下的 <client_ip> 属性 "ip"
    // char icp_ip[100][NAMELENGTH];
    // char sim_ip[100][NAMELENGTH];
    int port[7];       // 常用端口号
                       // [1] udp_icp recv_port
                       // [2] udp_icp send_port
                       // [3] udp_sim recv_port
                       // [4] udp_sim send_port
                       // [5] udp_monitor icp_port
                       // [6] udp_monitor sim_port
                       // [0] 未使用
    int icp_num;       // ICP 客户端数量，从 <ICP> 节点下 <client_ip> 个数获取
    int sim_num;       // SIM 客户端数量，从 <SIM> 节点下 <client_ip> 个数获取
    int all_port[100]; // 对应 all_ip 的端口号
                       // 从 <client_ip> 节点属性 "port" 获取
                       // 索引顺序与 all_ip 一致
    // int icp_port[100];
    // int sim_port[100];
} SOCKET_PARSE;

typedef struct /*tcp_udp解析参数*/
{
    unsigned int shm_size;
    char         shm_name[NAMELENGTH];
    char         server_ip[NAMELENGTH];
    char         client_ip[NAMELENGTH];
    int          server_port;
    int          client_port;
    int          msg_num;
    int          bmsg_num;
    int          offset[10000][2];
    int          len[10000][2];
    int          rate[10000][2];
} SNAPSHOT_PARSE;

typedef struct
{
    int idx;
} node;

typedef struct
{
    int offset;
    int len;
} entry;

typedef void *xml_attribute_type;

/************************接口声明******************************/
int open_xml_file(char *file_name, xml_doc_type *p_doc);

void close_xml_file(xml_doc_type *doc);

char *get_node_value(xml_node_type node);

xml_node_type get_next_sibling_node(xml_node_type node, char *name);

xml_node_type get_first_child_node(xml_node_type node, char *name);

xml_attribute_type get_first_attribute(xml_node_type node, char *name);

xml_attribute_type get_next_attribute(xml_attribute_type attribute, char *name);

char *get_attribute_value(xml_attribute_type attribute);

long int get_attribute_int_value(xml_attribute_type attribute, int base);

bool get_first_attribute_bool_value(xml_node_type node, char *name);

long int get_first_attribute_str_or_int_value(xml_node_type, char *, char *, int, int);

int get_child_node_count(xml_node_type node, char *name);

char *get_first_attribute_value(xml_node_type node, char *name);

long int get_first_attribute_int_value(xml_node_type node, char *name, int base);

double get_first_attribute_double_value(xml_node_type node, char *name);

xml_node_type get_root_node(char *cfg_file, xml_doc_type *p_doc);

char *malloc_by_child_node(xml_node_type node, char *name, int node_size, int *p_node_count);

void hzx_parse_xml(char *file_path, T_XMLINFO *data, char *user_name);

void hzx_dds_parse(char *file_path, DDS_PARSE *dds_data);

void hzx_sync_parse(char *file_path, SYNC_PARSE *sync_data);

void tcp_udp_parse_d(char *file_path, SOCKET_PARSE *socket_data);

void snapshot_parse(char *file_path, SNAPSHOT_PARSE *snapshot);

void udp_node_insert_d(char *topic, const int idx);

int find_node_d(char *topic);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _XML_API_H_ */
