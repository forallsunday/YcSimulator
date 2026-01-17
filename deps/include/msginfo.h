/************************************************************************
*				成都飞机设计研究所 版权所有
* 	 Copyright (C) 2011 CADI Inc. All Rights Reserved.
***********************************************************************/

/*
 * 修改历史：
 * 2023-12-21    heting,wanghaojie，北京华智信科技发展有限公司
 *               创建该文件。
*/

/*
* @file： msginfo.h
* @brief：
*    <li>模型消息结构体定义</li>
* @implements: DK2.3
*/

#ifndef MSGINFO_H_
#define MSGINFO_H_

/************************头文件********************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/************************宏定义********************************/
#define CACHE_LINE_ALIGN(mark) unsigned char mark[0] __attribute__ ((aligned (64)))		/*对齐*/
#define NAMELENGTH 50		/*命名长度*/
#define MODELMAXNUM 100		/*模型最大数量*/
#define MAXHASHMSG 15000	/*hash最大数量*/

/************************类型定义******************************/
typedef struct							/*消息属性*/
{
	CACHE_LINE_ALIGN(cacheline0);
	unsigned int msg_len;
	unsigned int msg_type;
	unsigned int trans_type;
	unsigned int msg_offset;
	unsigned int hash_num;
//	unsigned int bit_idx;
	char struct_name[NAMELENGTH];
	char topic[NAMELENGTH];
	char topic_id[NAMELENGTH];
}T_MSGINFO;

typedef struct							/*模型属性*/
{
	CACHE_LINE_ALIGN(cacheline0);
	unsigned int model_rate;
	unsigned int sub_num;
	unsigned int pub_num;
	unsigned int msg_num;
	char model_name[NAMELENGTH];
	T_MSGINFO msg_info[MAXHASHMSG];

}T_MODELINFO;

typedef struct							/*xml解析结构体*/
{
	CACHE_LINE_ALIGN(cacheline0);
	int stacksize;
	int priority;
	int cpu;
	int thread_num;
	unsigned int shm_size;
	unsigned int model_num;
	unsigned int tickus;
	char shm_name[NAMELENGTH];
	T_MODELINFO model_info[MODELMAXNUM];
}T_XMLINFO;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* MSGINFO_H_ */
