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

typedef struct /*tcp_udp解析参数*/
{
    unsigned int shm_size;
    char         shm_name[NAMELENGTH];
    char         server_ip[4][NAMELENGTH];
    char         all_ip[100][NAMELENGTH];
    // char icp_ip[100][NAMELENGTH];
    // char sim_ip[100][NAMELENGTH];
    int port[7];
    int icp_num;
    int sim_num;
    int all_port[100];
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
int open_xml_file(const char *file_name, xml_doc_type *p_doc);

void close_xml_file(xml_doc_type *doc);

char *get_node_value(xml_node_type node);

xml_node_type get_next_sibling_node(xml_node_type node, const char *name);

xml_node_type get_first_child_node(xml_node_type node, const char *name);

xml_attribute_type get_first_attribute(xml_node_type node, const char *name);

xml_attribute_type get_next_attribute(xml_attribute_type attribute, const char *name);

char *get_attribute_value(xml_attribute_type attribute);

long int get_attribute_int_value(xml_attribute_type attribute, int base);

bool get_first_attribute_bool_value(xml_node_type node, const char *name);

long int get_first_attribute_str_or_int_value(xml_node_type, const char *, const char *, int, int);

int get_child_node_count(xml_node_type node, const char *name);

char *get_first_attribute_value(xml_node_type node, const char *name);

long int get_first_attribute_int_value(xml_node_type node, const char *name, int base);

double get_first_attribute_double_value(xml_node_type node, const char**name);

xml_node_type get_root_node(const char *cfg_file, xml_doc_type *p_doc);

char *malloc_by_child_node(xml_node_type node, const char *name, int node_size, int *p_node_count);

void hzx_parse_xml(char *file_path, T_XMLINFO *data, char *user_name);

void hzx_dds_parse(char *file_path, DDS_PARSE *dds_data);

void hzx_sync_parse(char *file_path, SYNC_PARSE *sync_data);

void tcp_udp_parse_d(const char *file_path, SOCKET_PARSE *socket_data);

void snapshot_parse(char *file_path, SNAPSHOT_PARSE *snapshot);

void udp_node_insert_d(const char *topic, const int idx);

int find_node_d(const char *topic);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _XML_API_H_ */
