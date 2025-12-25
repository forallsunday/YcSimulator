#ifndef COMMINTERFACE_H_
#define COMMINTERFACE_H_
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <time.h>
#include <sys/time.h>
#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "ZRInterface_c++.h"
#include "./icd_include/AOXEAppDef.h"
#include "./icd_include/AoxeTopicIdDef.h"
#include "./icd_include/AppTopicIdDef_EWSM.h"

#if 1	//HA

//#include "ICDB_ENUM_STRUCT_EWSM.H"
//#include "ICDB_TOPIC_DESCRIPTION_EWSM.H"
//#include "ICDB_TOPIC_STRUCT.H"

//#include "./common_include_HXX/ICDB_ENUM_STRUCT.H"
//#include "./common_include_HXX/ICDB_TOPIC_DESCRIPTION.H"
//#include "./common_include_HXX/ICDB_TOPIC_STRUCT.H"

#else	//SE

#include "./common_include_SXX/ICDB_ENUM_STRUCT_EWSM.H"
#include "./common_include_SXX/ICDB_TOPIC_DESCRIPTION_EWSM.H"
#include "./common_include_SXX/ICDB_TOPIC_STRUCT_EWSM.H"

#endif

//如果定义了这个宏，那么进行本地测试
//#define USETEST

using namespace std;

//仿真周期 单位ms	10ms
#define Simu_Circle 40

typedef int(*UDPSEND)(int, const char*, size_t);

/**********宏定义信息区域:Begin***********/
/**********宏定义信息区域:End***********/



//int step_calculate();
//void step_freeze();
/**********框架动态库定义信息区域:End***********/
//#ifdef __cplusplus
//}
//#endif  /* __cplusplus */


/**********结构体定义信息区域:Begin***********/
#pragma pack(1)
typedef struct {
	UINT32 source; /* source function node ID 		*/
	UINT32 dest; /* destination function node address */
	UINT32 msgSpec; /* msg transfer specification*/
	UINT32 topicId; /* normally,   first byte: phscial block, second byte: logcial block */
	UINT64 time_tag; /* time tag when send message 	*/
	UINT32 uiQos;
	UINT32 payloadLen; /* length of pData, UNIT: bytes */
	UINT32 uiBitMap[4]; /* network bitmap or function node bitmap 1-32;33-64;65-96;97-128 */
	UINT8  pPayload[2048]; /* payload data */
} NET_DATA_PACKET_TYPE;   //仿真UDP头


typedef struct {
	UINT32 block_id;
	UINT32 msg_src;
	UINT32 sysctrl_node;
	UINT32 appcfg;
	UINT32 app_ok;
	UINT32 flag;
}OK_MSG;

#pragma pack()
/**********结构体定义信息区域:End***********/



#endif
