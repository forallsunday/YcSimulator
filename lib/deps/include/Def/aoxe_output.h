
#ifndef AOXE_OUTPUT_H
#define AOXE_OUTPUT_H


#include "BasicTypes.h"
#include "aoxe_errorCode.h"

#ifdef __cplusplus
extern "C"{
#endif
/*****************************OSS MODULE*************************************************************/


//#]

//#[ type FACE_OSS_MAX_NAME_LENGTH
#define FACE_OSS_MAX_NAME_LENGTH (30)
//#]

//#[ type FACE_OSS_RETURN_CODE_TYPE
typedef INT32 FACE_OSS_RETURN_CODE_TYPE;
//#]

//#[ type FACE_OSS_ERROR_CODE
/* 路由返回值 */
#define AOXE_OSS_SUCC                             (0)

#define AOXE_OSS_ERR_CODE_BASE                    (-800)
#define AOXE_OSS_NULL_INSTANCE_ERR				  (AOXE_OSS_ERR_CODE_BASE - 1)

//#]

//#[ type FACE_OSS_SYSTEM_TIME_TYPE
typedef INT64 FACE_OSS_SYSTEM_TIME_TYPE;
//#]

//#[ type FACE_OSS_NAME_TYPE
typedef  char   FACE_OSS_NAME_TYPE[FACE_OSS_MAX_NAME_LENGTH];
//#]

//#[ type FACE_OSS_PROCESS_DEF
typedef UINT32	 FACE_OSS_AFFINITY_TYPE;
typedef ADDR_TYPE	 FACE_OSS_PROCESS_ID;
typedef UINT32	 FACE_OSS_STACK_SIZE_TYPE;
typedef INT32	 FACE_OSS_PRIORITY_TYPE;

//#[ type FACE_OSS_PARTITION_DEF
typedef UINT32	 FACE_OSS_PARTITION_ID_TYPE;
//#]

//#[ type FACE_OSS_MUTEX_DEF
typedef ADDR_TYPE FACE_OSS_MUTEX_ID;
//#]

//#[ type FACE_OSS_SEMAPHORE_DEF
typedef ADDR_TYPE FACE_OSS_SEMAPHORE_ID;
//#]

//#[ type FACE_OSS_MESSAGE_QUEUE_DEF
typedef ADDR_TYPE FACE_OSS_MESSAGE_QUEUE_ID;
typedef enum
{
	FACE_OSS_SOFT = 0,
	FACE_OSS_HARD = 1,
	FACE_OSS_DEADLINE_DEFAULT = 0xffffffff,
}FACE_OSS_DEADLINE_TYPE;

typedef enum
{
	FACE_OSS_DORMANT = 0,
	FACE_OSS_READY = 1,
	FACE_OSS_RUNNING = 2,
	FACE_OSS_WAITING = 3,
	FACE_OSS_PROCESS_STATE_DEFAULT = 0xffffffff
}FACE_OSS_PROCESS_STATE_TYPE;


//#]

//#[ type FACE_OSS_SYSTEM_ADDRESS_TYPE
typedef  void           (*FACE_OSS_SYSTEM_ADDRESS_TYPE);     /* 系统地址类型定义 */
//#]

//#[ type FACE_OSS_PROCESS_ATTRIBUTE_TYPE
typedef struct
{
	FACE_OSS_NAME_TYPE		 			pcName; /* 进程名 */
    void*			 					pvEntryPoint; /* 进程入口点 */
    void*								pvParam; /* 进程参数 */
    FACE_OSS_STACK_SIZE_TYPE 			uiStackSize; /* 进程栈大小 */
    FACE_OSS_PRIORITY_TYPE 				uiBasePriority; /* 进程基础优先级 */
    FACE_OSS_SYSTEM_TIME_TYPE 			ulPeriod; /* 进程周期 */
    FACE_OSS_SYSTEM_TIME_TYPE 			ulTimeCapacity; /* 进程时间容量 */
  //  FACE_OSS_DEADLINE_TYPE				uiDeadline; /* 进程截止期类型 */
    FACE_OSS_AFFINITY_TYPE				uiAffinity; /* 进程运行核 */
}FACE_OSS_PROCESS_ATTRIBUTE_TYPE;
//#]

//#[ type FACE_OSS_PROCESS_STATUS_TYPE
typedef struct
{
 	FACE_OSS_PROCESS_ATTRIBUTE_TYPE 	tAttributes; /* 进程属性 */
    FACE_OSS_PRIORITY_TYPE 				uiCurrentPriority; /* 进程当前优先级 */
    FACE_OSS_SYSTEM_TIME_TYPE 			ulDeadline; /* 进程截止期 */
    FACE_OSS_PROCESS_STATE_TYPE 		tProcessStatus; /* 进程状态 */
}FACE_OSS_PROCESS_STATUS_TYPE;
//#]
//#]
/******************获取OSS版本接口***********************/
/* 获取 OSS版本号 */
void OSS_Get_Version(char* pcVersion);
/* 设置OSS版本号 */
void OSS_Set_Version();

//## operation FACE_OSS_Create_Task(FACE_OSS_PROCESS_ATTRIBUTE_TYPE*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Create_Task(FACE_OSS_PROCESS_ATTRIBUTE_TYPE* ptTaskAttrib, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

//## operation FACE_OSS_Get_Current_Process_ID(FACE_OSS_PROCESS_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Get_Current_Process_ID(FACE_OSS_PROCESS_ID* piProcessId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

//## operation FACE_OSS_Get_Partition_ID(FACE_OSS_PARTITION_ID_TYPE*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Get_Partition_ID(FACE_OSS_PARTITION_ID_TYPE* piPartitionId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

//## operation FACE_OSS_Get_Process_Name(FACE_OSS_PROCESS_ID,char*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Get_Process_Name(FACE_OSS_PROCESS_ID iProcessId, char* pcProcessName, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);
// @函数名：FACE_OSS_Message_Queue_Create
// @功能：创建消息队列
// @输入参数:
//             UINT32 maxMsgLen  队列消息最大长度
//             UINT32 maxQueSize 队列最大深度
// @输入输出参数：
//             FACE_OSS_Message_Queue_ID pQueid 队列ID
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
//## operation FACE_OSS_MessageQueue_Create(UINT32,UINT32,FACE_OSS_MESSAGE_QUEUE_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_MessageQueue_Create(UINT32 maxMsgLen, UINT32 maxQueSize, FACE_OSS_MESSAGE_QUEUE_ID* pQueid, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名：FACE_OSS_Message_Queue_Get
// @功能：获取消息队列中的消息
// @输入参数:
//             queueId 队列ID
//             timeout 等待时间
// @输入输出参数：
//             pMsg 消息负载
// @返回值：消息长度：成功；<0:失败
// @修改记录：
// 
// 
//## operation FACE_OSS_MessageQueue_Get(FACE_OSS_MESSAGE_QUEUE_ID,void *,INT32)
UINT32 FACE_OSS_MessageQueue_Get(FACE_OSS_MESSAGE_QUEUE_ID queueId, void * pMsg, INT32 timeout);

// @函数名：FACE_OSS_Message_Queue_GetNum
// @功能：获取消息队列中的消息个数
// @输入参数:
//             queueId 队列ID
// @返回值：消息个数
// @修改记录：
// 
// 
//## operation FACE_OSS_MessageQueue_GetNum(FACE_OSS_MESSAGE_QUEUE_ID)
UINT32 FACE_OSS_MessageQueue_GetNum(FACE_OSS_MESSAGE_QUEUE_ID queueId);

// @函数名：FACE_OSS_Message_Queue_IsEmpty
// @功能：判断消息队列是否为空
// @输入参数:
//             queid 队列ID
// @返回值：0：其他；1：空
// @修改记录：
//## operation FACE_OSS_MessageQueue_IsEmpty(FACE_OSS_MESSAGE_QUEUE_ID)
BOOL FACE_OSS_MessageQueue_IsEmpty(FACE_OSS_MESSAGE_QUEUE_ID queueId);

// @函数名：FACE_OSS_Message_Queue_IsFull
// @功能：判断消息队列是否满
// @输入参数:
//             queid 队列ID
// @返回值：0：其他；1：满
// @修改记录：
// 
//## operation FACE_OSS_MessageQueue_IsFull(FACE_OSS_MESSAGE_QUEUE_ID)
BOOL FACE_OSS_MessageQueue_IsFull(FACE_OSS_MESSAGE_QUEUE_ID queueId);

// @函数名：FACE_OSS_Message_Queue_Put
// @功能：向消息队列里面放入消息
// @输入参数:
//            queueId  队列ID
//            pMsg  消息负载
//            msgLen 消息长度
//            timeout 等待时间
// @返回值：0：其他；1：放入成功
// @修改记录：
//## operation FACE_OSS_MessageQueue_Put(FACE_OSS_MESSAGE_QUEUE_ID,void *,UINT32,INT32)
BOOL FACE_OSS_MessageQueue_Put(FACE_OSS_MESSAGE_QUEUE_ID queueId, void * pMsg, UINT32 msgLen, INT32 timeout);

// 功能：创建多值信号量
// 输入参数：
//     semFlag：阻塞方式，semFlag 等于0x0（SEM_FIFO）或者0x1（SEM_PRIORITY）；
//     name：信号量名称；
//     initialCount：信号量初始值；
//     maxCount：信号量最大值； 
//     说明：由于在AOXE_Mutex类中，Lock（）接口没有提供timeout参数，当获取不到信号灯时会一直阻塞直至获取信号灯；
//     为方便灵活处理，可用AOXE_Semphore类的Wait（const long timeout）来代替，
//      在创建信号量时，输入参数：initialCount = 0或者1；maxCount = 1;此时，与互斥信号灯功能相同。
// Argument char* name :
// 信号量名称；
//## operation FACE_OSS_Mutex_Create(char*,FACE_OSS_MUTEX_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Mutex_Create(char* name, FACE_OSS_MUTEX_ID* pMutexId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名： FACE_OSS_Mutex_Lock
// @功能：锁信号量
// @输入参数:
//              mutexId 信号量ID
// @返回值：
// @修改记录：
// 
//## operation FACE_OSS_Mutex_Lock(FACE_OSS_MUTEX_ID)
void FACE_OSS_Mutex_Lock(FACE_OSS_MUTEX_ID mutexId);

// @函数名： FACE_OSS_Mutex_Unlock
// @功能：释放信号量
// @输入参数:
//              mutexId 信号量ID
// @返回值：
// @修改记录：
// 
// 
//## operation FACE_OSS_Mutex_Unlock(FACE_OSS_MUTEX_ID)
void FACE_OSS_Mutex_Unlock(FACE_OSS_MUTEX_ID mutexId);

//## operation FACE_OSS_PARTITION_Get_Id(FACE_OSS_PARTITION_ID_TYPE*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_PARTITION_Get_Id(FACE_OSS_PARTITION_ID_TYPE* piPartitionId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// 功能：创建多值信号量
// 输入参数：
//     semFlag：阻塞方式，semFlag 等于0x0（SEM_FIFO）或者0x1（SEM_PRIORITY）；
//     name：信号量名称；
//     initialCount：信号量初始值；
//     maxCount：信号量最大值； 
//     说明：由于在AOXE_Mutex类中，Lock（）接口没有提供timeout参数，当获取不到信号灯时会一直阻塞直至获取信号灯；
//     为方便灵活处理，可用AOXE_Semphore类的Wait（const long timeout）来代替，
//      在创建信号量时，输入参数：initialCount = 0或者1；maxCount = 1;此时，与互斥信号灯功能相同。
// Argument UINT32 semFlag :
// 阻塞方式，semFlag 等于0x0（SEM_FIFO）或者0x1（SEM_PRIORITY）；
// Argument char* name :
// 信号量名称；
// Argument UINT32 initialCount :
// 信号量初始值；
// Argument UINT32 maxCount :
// 信号量最大值； 
//## operation FACE_OSS_Semaphore_Create(UINT32,char*,UINT32,UINT32,FACE_OSS_SEMAPHORE_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Semaphore_Create(UINT32 semFlag, char* name, UINT32 initialCount, UINT32 maxCount, FACE_OSS_SEMAPHORE_ID* pSemId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名：  FACE_OSS_Semaphore_Signal
// @功能：释放信号灯
// @输入参数:
//              semId 信号灯ID
// @返回值：
// @修改记录：
// 20221001 zyh创建
// 
// 
//## operation FACE_OSS_Semaphore_Signal(FACE_OSS_SEMAPHORE_ID)
void FACE_OSS_Semaphore_Signal(FACE_OSS_SEMAPHORE_ID semId);

// @函数名：  FACE_OSS_Semaphore_Signal
// @功能：等待信号灯
// @输入参数:
//              semId 信号灯ID
//                       timeout：超时时间，单位：微秒
// 
// @返回值：
// @修改记录：
// 20221001 zyh创建
// 
// 
// 
//## operation FACE_OSS_Semaphore_Wait(FACE_OSS_SEMAPHORE_ID,INT32)
void FACE_OSS_Semaphore_Wait(FACE_OSS_SEMAPHORE_ID semId, INT32 timeout);

// @函数名：FACE_OSS_Task_Create
// @功能：创建任务
// @输入参数:
//             ptTaskAttrib  任务属性
// @输入输出参数：
//             pid 任务ID
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
// 
//## operation FACE_OSS_Task_Create(FACE_OSS_PROCESS_ATTRIBUTE_TYPE*,FACE_OSS_PROCESS_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Create(FACE_OSS_PROCESS_ATTRIBUTE_TYPE* ptTaskAttrib, FACE_OSS_PROCESS_ID* pid, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

//## operation FACE_OSS_Task_Delay(UINT32)
void FACE_OSS_Task_Delay(UINT32 time);

// @函数名：FACE_OSS_Task_Get_Current_ID
// @功能：获取当前正在运行的任务ID
// 
// @输入输出参数：
//             piProcessId 任务ID
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
// 
// 
//## operation FACE_OSS_Task_Get_Current_ID(FACE_OSS_PROCESS_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Get_Current_ID(FACE_OSS_PROCESS_ID* piProcessId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名：FACE_OSS_Task_Get_Name
// @功能：获取指定任务ID的任务名
// @输入参数
//             iProcessId 任务ID
// @输入输出参数：
//             pcProcessName 任务名
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
// 
// 
// 
//## operation FACE_OSS_Task_Get_Name(FACE_OSS_PROCESS_ID,char*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Get_Name(FACE_OSS_PROCESS_ID iProcessId, char* pcProcessName, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

//## operation FACE_OSS_Task_Get_Status(FACE_OSS_PROCESS_ID,FACE_OSS_PROCESS_STATUS_TYPE*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Get_Status(FACE_OSS_PROCESS_ID iProcessId, FACE_OSS_PROCESS_STATUS_TYPE* ptProcStatus, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名：FACE_OSS_Task_Get_ID
// @功能：获取指定任务名的任务ID
// @输入参数
//            pcProcessName 任务名           
// @输入输出参数：
//             piProcessId 任务ID 
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
// 
// 
// 
//## operation FACE_OSS_Task_Get_Task_ID(char*,FACE_OSS_PROCESS_ID*,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Get_Task_ID(char* pcProcessName, FACE_OSS_PROCESS_ID* piProcessId, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

// @函数名：FACE_OSS_Start
// @功能：启动任务
// @输入参数:
//              pid 任务ID 
// @输入输出参数：
//             FACE_OSS_RETURN_CODE_TYPE* piRtnCode 返回值
// @返回值：0：成功；其他：失败
// @修改记录：
// 
// 
// 
//## operation FACE_OSS_Task_Start(FACE_OSS_PROCESS_ID,FACE_OSS_RETURN_CODE_TYPE*)
void FACE_OSS_Task_Start(FACE_OSS_PROCESS_ID pid, FACE_OSS_RETURN_CODE_TYPE* piRtnCode);

/*****************************END OF OSS MODULE*************************************************************/
//#[ type IOSS_ADAPTOR_HANDLE_TYPE
typedef UINT32 IOSS_ADAPTOR_HANDLE_TYPE;
//#]

//#[ type IOSS_ADAPTOR_RETURN_CODE_TYPE
typedef INT32 IOSS_ADAPTOR_RETURN_CODE_TYPE;

/********************各总线加载接口**************************/
//加载FC总线
void IOSS_Adaptor_Launch_NetFc(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载PCIE总线
void IOSS_Adaptor_Launch_NetPcie(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载NDB
void IOSS_Adaptor_Launch_NetNdb(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载TIC
void IOSS_Adaptor_Launch_NetTic(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载显示触屏422
 void IOSS_Adaptor_Launch_Net422(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载机载软总线
 void IOSS_Adaptor_Launch_NetTm(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
 //加载点对点FC
 void IOSS_Adaptor_Launch_NetFcP2P(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
 //加载分区网
 void IOSS_Adaptor_Launch_NetPN(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
  //加载分区网
 void IOSS_Adaptor_Launch_NetUdp(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
 //加载分区网
void IOSS_Adaptor_Launch_Net485(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载Rio
void IOSS_Adaptor_Launch_NetRio(IOSS_ADAPTOR_RETURN_CODE_TYPE*);
/****************************************************/


/********************TSS加载接口**************************/

//#[ type TSS_ADAPTOR_HANDLE_TYPE
typedef UINT32 TSS_ADAPTOR_HANDLE_TYPE;
//#]

//#[ type TSS_ADAPTOR_RETURN_CODE_TYPE
typedef INT32 TSS_ADAPTOR_RETURN_CODE_TYPE;

//加载时间服务
void TSS_Adaptor_Launch_TimeServ(TSS_ADAPTOR_RETURN_CODE_TYPE*);
//加载路由服务
void TSS_Adaptor_Launch_Router(TSS_ADAPTOR_RETURN_CODE_TYPE*);
void TSS_Adaptor_Launch_NodeMngServ(TSS_ADAPTOR_RETURN_CODE_TYPE*);
// 监控初始化
void LaunchMonitor(TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
/****************************************************/
/*********执行环境组件版本号*********************/
typedef struct
{

	char acOSVer[25];  	    //操作系统版本
	char acFileSystemVer[25]; //文件系统版本号
	/*****执行环境版本号****/
	char acAoxeOssVer[25];  //oss适配层版本

	char acAoxeNetFcVer[25];  //FC适配层版本
	char acAoxeNet422Ver[25];  //422适配层版本
	char acAoxeNetNdbVer[25];  //飞管1394适配层版本
	char acAoxeNetPcieVer[25]; //PCIE适配层版本
	char acAoxeNetPnVer[25];  //分区网适配层版本
	char acAoxeNetTicVer[25]; //任务1394适配层版本
	char acAoxeNetTmVer[25];  //天脉软总线适配层版本
	char acAoxeNetFcP2PVer[25];  //点对点FC适配层版本
	char acAoxeNetUdpVer[25]; //UDP适配层版本
	char acAoxeNetRioVer[25]; //RIO网适配层版本
	char acAoxeBusMngVer[25]; //总线服务版本

	char acAoxeRouterVer[25]; //路由服务版本
	char acAoxeTimeServVer[25]; //时间服务版本
	char acAoxeNodeMngVer[25]; //节点管理服务版本
	char acAoxeMonitorVer[25]; //监控服务版本
	char acAoxeErrHandlerVer[25]; //故障监控服务版本
	char acAoxeTssAdaptorVer[25];//Tss适配层版本

	char acAoxeAppFrameVer[25]; //应用框架版本
	char acAoxeQosVer[25]; //QOS版本号
	char acAoxeFileSystemVer[25]; //网络文件系统版本号
	char acAoxeFaceIossVer[25]; //FACE层版本号
	char acAoxeTotalVer[25]; //执行环境总版本号
	/*************************/
}AOXE_VERSION_TYPE;

//#[ ignore


/*****************************IOSS ADAPTOR(IA) MODULE*************************************************************/

//#[ type CONST_TYPE_DEF
#define MAX_BOX_NUM 4
#define MAX_LOG_LENTH0 100
#define MAX_LOG_SIZE0 5
#define MAX_VER_LENTH0 25
/* msgLen Def */
#define SHORT_MSG_MAX_LEN 2096
#define STREAM_MSG_MAX_LEN 0x1000000
//must divided by 4
#define READ_BUF_SIZE (15000/4)
//TIME_UNIT_TRANS
#define HNS_TO_NS  100
#define NS_TO_HNS  0.01

#define ICP_MAX_ITEM_NUM 32

#define IOSS_ADAPTOR_VERSION_LEN 24
#define IOSS_ADAPTOR_DRV_VER_LEN 50
// #[ type NET_DATA_PACKET_HEAD
// 网络数据包头
//#[ type NET_DATA_PACKET_HEAD
typedef struct {
	UINT32 uiSource		; /* source function node ID 		*/
	UINT32 uiDest			; /* destination function node address */
	UINT32 uiMsgSpec		; /* msg transfer specification*/
	UINT32 uiTopicId		; /* topicId */
	UINT64 ulTimeTag		; /* time tag when send message 	*/
	UINT32 uiQos			; /* Qos property*/
	UINT32 uiPayloadLen	; /* length of pData, UNIT: bytes */
	UINT32 uiBitMap[4];
}NET_DATA_PACKET_HEAD;
//#]

// #[ type NET_DATA_PACKET_TYPE
// 节点之间传输的数据类型，实际数据为：Head＋Data
//#[ type NET_DATA_PACKET_TYPE
typedef struct {
	UINT32 uiSource		; /* source function node ID 		*/
	UINT32 uiDest			; /* destination function node address */
	UINT32 uiMsgSpec		; /* msg transfer specification*/
	UINT32 uiTopicId		; /* topicId */
	UINT64 ulTimeTag		; /* time tag when send message 	*/
	UINT32 uiQos			; /* Qos Property*/
	UINT32 uiPayloadLen	; 	  /* length of pData, UNIT: bytes */
	UINT32 uiBitMap[4];
	UINT8* pucPayload		; /* payload data */
}NET_DATA_PACKET_TYPE;

typedef struct
{
 	UINT32 uiQueryCmd;
 	UINT32 uiBoxId;
 	void* pvInPara;
 	void* pvOutPara;
}IOSS_ADAPTOR_PARAM_TYPE;

typedef enum
{
 	V_GET_NP_BIT = 1,   //FC节点BIT
 	V_GET_SW_BIT_1 = 2,  //交换机1BIT
 	V_GET_SW_BIT_2 = 3,  //交换机2BIT
}IOSS_ADAPTOR_FC_BIT_TYPE;

typedef struct
{
	UINT32 uiNodeId;
	UINT32 uiBoxId;
	UINT32 uiHandle;
	void*  pvIOServ;
}IOSS_ADAPTOR_CONFIG_RESOURCE;

typedef struct
{
	UINT32 uiNodeId;
	UINT32 uiStatus;
}IOSS_ADAPTOR_NODE_STATUS_CONTROL_TYPE;
//#]
// 总线连接状态类型
//#[ type IOSS_ADAPTOR_CONNECTION_STATUS_CMD
typedef enum
{
 	V_BUS_GET_NET_TOP = 0,
 	V_BUS_GET_READY_STATUS,
	V_BUS_SET_NODE_STATUS,
}IOSS_ADAPTOR_CONNECTION_STATUS_CMD;

typedef enum
{
    V_BUS_LOAD_STATUS = 0,  //总线加载状态
    V_BUS_SET_BEHAVIOR_START, //启动各总线状态图
    V_BUS_SET_TASK_START,
    V_GET_PERIOD_BIT_RESULT, //获取周期BIT结果
    V_CLK_CHECK_SERVER_ALIVE_STATUS, //获取时钟服务器存活状态
    V_GET_POWERUP_BIT_RESULT, // 获取上电BIT结果
} IOSS_ADAPTOR_STATUS_CMD;

//#[ type IOSS_ADAPTOR_CONNECTION_CONFIGURATION_CMD
typedef enum
{
    V_DYNAMIC_REGISTER_TOPIC = 0,
    V_DYNAMIC_REGISTER_WELLKNOWN_TOPIC,
    V_BUS_METRIC_QUERY,
    V_BUS_NODE_TO_DEVICE_QUERY,
}IOSS_ADAPTOR_CONNECTION_CONFIGURATION_CMD;
typedef struct
{
 	UINT32 uiCallbackCmd;
 	UINT32 uiNotificationId;
 	void* pvCallback;
}IOSS_ADAPTOR_CALLBACK;

typedef enum
{
	V_APP_MSG_CALLBACK,    //应用回调注册
	V_MIDWARE_MSG_CALLBACK,  //中间件回调注册
	V_NODE_ONOFF_CALLBACK,	//上下网回调注册
	V_SPECIAL_MONITOR_MSG_CALLBACK, //特殊监控回调(飞管)
	V_MONITOR_MSG_CALLBACK, //监控回调注册
}IOSS_ADAPTOR_CALLBACK_CMD;

//#[ type IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE
typedef struct
{
	UINT32 uiTopicId;  
	UINT32 uiNetId; 
	UINT32 uiMsgType;
	UINT8* pucPayload;
	UINT32 uiPayloadLen; 
	INT32* piRtnCode;
}IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE;   

// IOSS
//#[ type IOSS_ADAPTOR_STORAGE_PAYLOAD
typedef struct
{
	UINT32 uiAddr;				//NVRAM/FLASH 写/读 地址
	UINT32 uiPayloadLen; 	    //负载长度
	void* pvPayload;			//负载
}IOSS_ADAPTOR_STORAGE_PAYLOAD;
//#]

//#[ type IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE
typedef struct
{
 	UINT32 uiTopicId;
 	UINT32 uiMsgProperty;
 	UINT32 uiMsgLen;
}IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE;
//#]
// 总线参数配置类型
//#[ type IOSS_ADAPTOR_PARAMETER_CONFIGURATION_CMD
// 总线参数配置类型
//#[ type IOSS_ADAPTOR_PARAMETER_CONFIGURATION_CMD
typedef enum
{
    /** Time Relevant**/
    V_CLK_SET_ROLE_SERVER = 0, // set clock role to time server
    V_CLK_SET_ROLE_CLIENT, // set clock role to time client
    V_CLK_SET_DATE, // set date
    V_CLK_GET_DATE, // get date  
    V_CLK_GET_LOCAL_RTC, // get local rtc
    V_CLK_SET_SYS_RTC, // set system rtc 
    V_CLK_GET_SYS_RTC, // get system rtc   
    V_CLK_GET_MISSION_DELTA_RTC, //get mission delta rtc
    
    
    V_STRM_RELEASE_BUF, // release stream buf
    
    V_GET_NORMAL_MSG_NUM,
    V_GET_STREAM_MSG_NUM, 
       
    V_GET_BM_MSG_NUM, 
    
    V_GET_EVENT_MSG_NUM,
    V_GET_STOF_MSG_NUM,
    V_GET_PERIOD_MSG_NUM,   

    V_GET_CPU_ID, 				//天脉软总线获取CPUID   
    V_GET_VERSION,				//天脉软总线获取版本信息
    V_GET_SYS_ID,				//天脉软总线ICP:获取ICP ID
    V_GET_MODULE_ID,			//天脉软总线ICP:获取
    V_GET_MODULE_TEMP, 			//天脉软总线获取模块温度
    V_GET_CPU_TEMP, 			//天脉软总线获取CPU温度  
    V_GET_TIMEBASE_TIME,		//天脉软总线获取timebase时间 
    
    /*天脉软总线 NVRAM, FLASH相关*/
    V_GET_NVRAM_ADDR,
    V_GET_FLASH_ADDR, 
    
    V_GET_BM_READ_PTR, //获取TIC BM读指针
    V_UPDATE_BM_READ_PTR, //释放TIC BM读指针  
    
    V_GET_NDB_MONITOR_BIT, //获取NDB故障监控位 
    V_GET_NODE_NET_STATUS, //获取节点网络状态       
    V_GET_IOSS_ADAPTOR_VERSION, //获取执行环境版本号       
    
     /*BIT相关*/
    V_BIT_SET_ITEM,
    V_GET_CBIT, 
    V_GET_PBIT,
    V_GET_MBIT,
    V_GET_IBIT, 
    V_BIT_MODULE_GET_ITEM,  
    V_GET_CFM_INFO,       
    
        /*电源模块相关*/
    V_GPIO_SET_PUBIT_CMD,   
    V_GPIO_Search_PSM_STATUS_CMD,  
    V_GPIO_SET_GET_SWITCH_STATUS_CMD,  
    V_GPIO_SET_CMD_SWITCH_CURRENT, 
    V_GPIO_SET_CMD_SWITCH_OUTPUT,
    V_SET_SWITCH_STATUS_CMD,   
    V_SEND_VERSION_CMD  ,
    V_SET_SWITCH_TABLE_CMD,
    V_SET_CMD_LOAD_SWITCH_TABLE,
    V_SET_SWITCH_CONFIG_TABLE_CMD, 
    V_SET_POWER_STATUS_CMD,  
    V_GPIO_GET_MSG_NUM,        
    V_GET_NET485ENABLE_FLAG,
    V_PARTITION_REBOOT,//重启分区

     /* NVRAM相关,每个记录区的初始化状态、起始地址、大小 */
    V_GET_TOTAL_NVRAM_SIZE_INFO, //获取总NVRAM区域大小
    V_GET_NVRAM_REGION_INFO, //获取NVRAM各区域的信息，包括AOXE、APP等全部区域划分信息
    V_GET_AOXE_CORE_ERR_NVRAM_INFO, //执行环境异常记录区
    V_GET_AOXE_RUNSTATUS_NVRAM_INFO,  //执行环境初始化、任务状态及异常信息记录区
    V_GET_AOXE_MSGSTATUS_NVRAM_INFO, //执行环境消息队列灯其他信息记录区
    V_GET_APP_NVRAM_INFO, //应用软件记录区
    V_GET_PLATFORM_NVRAM_INFO,//底层故障信息记录区


    V_CHECK_AOXE_CORE_ERR_NVRAM_INFO,  //检查地址是否合法
    V_CHECK_AOXE_RUNSTATUS_NVRAM_INFO,//检查地址是否合法
    V_CHECK_AOXE_MSGSTATUS_NVRAM_INFO, //检查地址是否合法
    V_CHECK_APP_NVRAM_INFO,    //检查地址是否合法
    V_CHECK_PLATFORM_NVRAM_INFO,   //检查地址是否合法


    V_GET_DEV_TEMPERATURE, //获取设备温度
    V_GET_NSM_VERSION,
    V_GET_DRV_VER_INFO, //获取版本信息2（目前适用于DMP硬件）
    V_GET_BCODE_TIME, //获取B码时间
    V_GET_BCODE_TIME_VALIDITY,//获取B码时间有效性
    V_VIDEO_STREAM_OVERLAP, //视频叠加接口

    V_GET_INT_MEM_OFFSET, //获取中断偏移地址
    V_SET_WDT_ENABLE, // 设置喂狗使能
    V_SET_WDT_FEED, //喂狗
    V_SET_NODE_STATUS, //设置节点状态
    V_GET_LINK_STATUS, //获取网络物理链路状态
    
}IOSS_ADAPTOR_PARAMETER_CONFIGURATION_CMD;


typedef enum
{
    V_GET_DRIVER_VERSION_NA = 0,
    V_GET_DRIVER_VERSION_DMP,  //获取DMP底层版本信息

}IOSS_ADAPTOR_DRIVER_VERSION_CMD;
//#[ type IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE_TYPE
typedef struct
{
 	UINT32 uiSubNum;
 	UINT32 uiPubNum;
 	IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE* ptSubTopicTable;
 	IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE* ptPubTopicTable;
}IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE_TYPE;

//#[ type IOSS_ADAPTOR_VER_LEN
#define IOSS_ADAPTOR_DRV_VER_LEN 50
//#]

typedef struct
{
	char acSoftVer[IOSS_ADAPTOR_DRV_VER_LEN];    /* 驱动软件版本 */
	char acCfgVer[IOSS_ADAPTOR_DRV_VER_LEN];    /* 配置数据版本 */
	char acLogicVer[IOSS_ADAPTOR_DRV_VER_LEN]; /* 逻辑版本 */
	char acMcuVer[IOSS_ADAPTOR_DRV_VER_LEN];    /* FC接口MUC辅助测试软件版本 */
}IOSS_ADAPTOR_VERSION_TYPE;

typedef struct
{
	char  drvName[IOSS_ADAPTOR_DRV_VER_LEN];		/*驱动名称*/
	char  drvVersion[IOSS_ADAPTOR_DRV_VER_LEN];		/*驱动版本号*/
	char  chkCode[IOSS_ADAPTOR_DRV_VER_LEN];   		/*驱动校验码，时分秒*/

}IOSS_ADAPTOR_DRV_VER_ITEM;

typedef struct
{
	IOSS_ADAPTOR_DRV_VER_ITEM* ptDrvVerItem;
	UINT32* puiDrvNum;
}IOSS_ADATOR_DRV_VERSION_INFO;
//#]
//FC节点BIT
/* 节点机上电BIT: PBIT */
typedef struct
{
    UINT8 ucHost;             /* 主机接口检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaHeart;        /* FPAG心跳检测: 0, 成功；非0，失败。*/
    UINT8 ucCfgFlash;         /* 配置FLASH检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaFlash;        /* FPAG FLASH检测: 0, 成功；非0，失败。*/

    UINT8 ucNvram;            /* NVRAM FLASH检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaVol;          /* FPAG电压检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaTemp;         /* FPAG温度检测: 0, 成功；非0，失败。*/
    UINT8 ucMcu;              /* MCU心跳检测: 0, 成功；非0，失败。*/

    UINT8 ucOpticalVol;       /* 光模块电压检测: 0, 成功；非0，失败。*/
    UINT8 ucOpticalTemp;      /* 光模块温度检测: 0, 成功；非0，失败。*/

    UINT8 ucSyncValid;
    UINT8 ucCommValid;

    UINT8 aucReserved1[4];

    UINT8 aaucMacPower[8][2]; /* MAC0-MAC7发射/接收功率检测: [0], 发射功率；[1], 接收功率；0, 成功；非0，失败。*/

    UINT8 aucAdcVccVtt[16];
    UINT8 aucMacLink[8];

    UINT8 aucReserved2[8];
}IOSS_ADAPTOR_FC_NP_BIT;
/* 交换机PBIT */
typedef struct
{
    UINT8 ucHost;             /* 主机接口检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaHeart;        /* FPAG心跳检测: 0, 成功；非0，失败。*/
    UINT8 ucCfgFlash;         /* 配置FLASH检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaFlash;        /* FPAG FLASH检测: 0, 成功；非0，失败。*/

    UINT8 ucNvram;            /* NVRAM FLASH检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaVol;          /* FPAG电压检测: 0, 成功；非0，失败。*/
    UINT8 ucFpgaTemp;         /* FPAG温度检测: 0, 成功；非0，失败。*/
    UINT8 ucMcu;              /* MCU心跳检测: 0, 成功；非0，失败。*/

    UINT8 ucSysFlash;         /* 系统FLASH检测: 0, 成功；非0，失败。*/
    UINT8 ucCpu;              /* CPU检测: 0, 成功；非0，失败。*/
    UINT8 ucSdram;            /* SDRAM检测: 0, 成功；非0，失败。*/
    UINT8 ucCpld;             /* CPLD检测: 0, 成功；非0，失败。*/

    UINT8 ucMid;              /* MID检测: 0, 成功；非0，失败。*/
    UINT8 ucSsmg;             /* 系统离散量检测: 0, 成功；非0，失败。*/
    UINT8 ucPfail;            /* PFAIL故障检测: 0, 成功；非0，失败。*/

    UINT8 isl_bit;

    UINT8 ucCpuTemp1;
    UINT8 ucCpuTemp2;
    UINT8 aucEthLink[11];

    UINT8 aucRsvd1[35];

    UINT8 aucOptVol[8];
    UINT8 aucOptTemp[8];
    UINT8 aucPortLink[48];

    UINT8 aaucOptPower[48][2]; /* 光模块功率检测: [0]，发射功率；[1]，接收功率；0, 成功；非0，失败。*/
	UINT8 aucRsvd2[32];

}IOSS_ADAPTOR_FC_SW_BIT;

typedef struct
{
	UINT8 aucLinkStatus[3]; //飞管端口通信故障检测：0，正确；1，错误。
	UINT8 ucCfg; //飞管配置加载检测：0，成功；1，错误。
}IOSS_ADAPTOR_NDB_BIT;

//#[ type IOSS_ADAPTOR_NDB_MONITOR_BIT
typedef struct
{
	UINT32	uiIllegalMode;   //VMS1394_非法模式监控故障, 0表示合法模式
	UINT32  uiUNConfirmCOM;  //VMS1394_未确认通信连接监控故障, 0表示无故障
	UINT32	uiCHError;  //VMS1394_连接通道错误监控故障, 0表示无故障
	UINT32	uiCRCError; //VMS1394_配置表CRC校验错误监控故障, 0表示无故障
	UINT32	uiSTOFStop;  //VMS1394_STOF包未刷新监控故障, 0表示无故障
	UINT32	uiPBITTimeout; //VMS1394_PBIT模式超时监控故障, 0表示无故障
	UINT32  uiHOTASHeart; //VMS1394_HOTAS包心跳监控故障, 0表示无故障
	UINT32	uiCLAWHeart;   //VMS1394_CLAW包心跳监控故障, 0表示无故障
	UINT32	uiFCRMHeart;  //VMS1394_FCRM包心跳监控故障, 0表示无故障
	UINT32	uiHOTASSVPC;  //VMS1394_HOTAS包SVPC监控故障, 0表示无故障
	UINT32  uiCLAWSVPC; //VMS1394_CLAW包SVPC监控故障, 0表示无故障
	UINT32	uiFCRMSVPC; //VMS1394_FCRM包SVPC监控故障, 0表示无故障
	UINT32  uiSTOFCHV; //VMS1394_STOF包CHV监控故障 , 0表示无故障
	UINT32	uiSTOFVPC;  //VMS1394_STOF包VPC监控故障, 0表示无故障
	UINT32	uiSTOFCycle;  //VMS1394_STOF包周期监控故障 , 0表示无故障
}IOSS_ADAPTOR_NDB_MONITOR_BIT;


//#]

//#[ type IOSS_ADAPTOR_ICP_BIT
typedef enum
{
    IOSS_PBIT    = 0,
    IOSS_CBIT    = 1,    /*CBIT测试*/
    IOSS_IBIT    = 2,    /*IBIT测试*/
    IOSS_MBIT    = 3,    /*MBIT测试*/     
    
}IOSS_ADAPTOR_BIT_TYPE; 
    
typedef struct
{
	IOSS_ADAPTOR_BIT_TYPE  bitType;
	UINT64 item;
}IOSS_ADAPTOR_BIT_SET_TYPE; 
  
typedef enum
{
    V_GET_CBIT_CMD,    /*CBIT测试*/
    V_GET_PBIT_CMD,    /*IBIT测试*/
    V_GET_IBIT_CMD,    /*MBIT测试*/     
    V_GET_MBIT_CMD,
}IOSS_ADAPTOR_BIT_TYPE_CMD;   


typedef enum
{
    IOSS_BIT_OK   = 0,   /*BIT测试正确*/
    IOSS_BIT_FAIL = 1    /*BIT测试有错*/
}IOSS_ADAPTOR_ICP_BIT_FINAL_RESULT;  

typedef struct
{
     UINT64    item;     /*测试项目号*/
     UINT32    result;   /*对应该项目的测试结果*/
     UINT32    arg1;     /*测试结果附加参数*/
     UINT32    arg2;     /*测试结果附加参数*/
}IOSS_ADAPTOR_ICP_BIT_ITEM_DETAIL_RESULT; 
#define ICP_MAX_ITEM_NUM 32  
typedef struct
{
    unsigned int nItem;  /*BIT的结果项数*/
    IOSS_ADAPTOR_ICP_BIT_ITEM_DETAIL_RESULT bitItemDetailResult[ICP_MAX_ITEM_NUM];/*BIT测试详细结果*/
}IOSS_ADAPTOR_ICP_BIT_DETAIL_RESULT; 

typedef struct
{
	IOSS_ADAPTOR_ICP_BIT_FINAL_RESULT  bitFinalResult;/*BIT最终结果*/
	IOSS_ADAPTOR_ICP_BIT_DETAIL_RESULT bitDetailResult;/*BIT详细结果*/
}IOSS_ADAPTOR_ICP_BIT_RESULT;          

typedef struct
{
	UINT64 IBitIterm;
	UINT64 CBitIterm;
	UINT64 MBitIterm;
}IOSS_ICP_BIT_ITEM;

//#[ type IOSS_ADAPTOR_READ_PAYLOAD_TYPE
typedef struct
{
 	UINT32	uiQueryCmd;                  //命令码
 	UINT32  uiBoxId;					 //子卡Id
 	UINT64* pulReceivedTime;      //获取时间
 	void*	pvReadData;           //读消息结构体
}IOSS_ADAPTOR_READ_PAYLOAD_TYPE;  

typedef struct
{
 	UINT32 uiQueryCmd;
 	UINT32 uiBoxId;					 //子卡Id
 	UINT32 uiMsgType; 		//0:urgent, 1:normal, 2:stream
 	void* pvWriteData;
}IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE;

typedef struct
{
	UINT32 uiNextHop;				 //下一跳节点号
	NET_DATA_PACKET_HEAD* pMsgHead;  //执行环境网络数据包
	void* pvPayload;			     //负载
}IOSS_ADAPTOR_WRITE_PAYLOAD;

typedef enum
{
	/* IOSS msg type */
	IOSS_URGENT_MESSAGE = 0,
	IOSS_NORMAL_MESSAGE,
	IOSS_STREAM_MESSAGE,

	IOSS_NORMAL_WELLKNOWN_MESSAGE,
	IOSS_STREAM_WELLKNOWN_MESSAGE,

	/********SPECIAL DEF********/

	/* TIC BM */
	IOSS_BM_MESSAGE,

	/* NDB */
	IOSS_EVENT_MESSAGE,
	IOSS_STOF_MESSAGE,
	IOSS_PERIOD_MESSAGE,

	/*FLASH, NVRAM*/
	IOSS_FLASH_MESSAGE,
	IOSS_NVRAM_MESSAGE,

}IOSS_ADAPTOR_MESSAGE_TYPE;

//#[ type IOSS_ADAPTOR_TOPOLOGY_TYPE
#define MAX_NEIGHBOR_NUM 4

typedef struct
{
	UINT32 uiNodeId; // 节点ID
	UINT32 uiStatus;  //连接状态
}IOSS_ADAPTOR_TOPOLOGY_CONNECTION_TYPE;

typedef struct
{
 	UINT32 uiNodeId;   
 	UINT32 uiDeviceId;
 	IOSS_ADAPTOR_TOPOLOGY_CONNECTION_TYPE tAdjacentConnection[MAX_NEIGHBOR_NUM];
}IOSS_ADAPTOR_TOPOLOGY_ITEM;

//#[ type IOSS_ADAPTOR_MODULE_INFO
typedef struct{

    UINT32   uifirstPowerUpFlag;     /*初次上电标志 位，若此值为FIRST_POWER_UP，则为已设置过数值，否则showModuleInfo执行时不予显示*/
        UINT32   uifirstPowerUpFlag_log;     /*初次上电标志 位，若此值为FIRST_POWER_UP，则为已设置过数值，否则showModuleInfo执行时不予显示*/
        UINT8    uilogNum;
        UINT8	 uipCnt;
        UINT8	 uires[15];

        UINT8    uimanufacturerID[MAX_VER_LENTH0];  /*制造商ID号*/
        UINT8    uimoduleType[MAX_VER_LENTH0];      /*模块类型*/
        UINT8    uisoldTime[MAX_VER_LENTH0];      /*模块出厂日期*/
        UINT8    uicarapaceNum[MAX_VER_LENTH0];   /*模块壳体号*/
        UINT8    uipcbFunc[MAX_VER_LENTH0];             /*PCB功能*/
        UINT8    uipcbFuncHardVer[MAX_VER_LENTH0];       /*PCB功能硬件版本*/
        UINT8    uipcbItf[MAX_VER_LENTH0];             /*PCB接口号*/
        UINT8    uipcbItfHardVer[MAX_VER_LENTH0];             /*PCB接口硬件版本*/


        UINT8    uilogicVerCpu1[MAX_VER_LENTH0];             /*逻辑版本cpu1*/
        UINT8    uilogicVerCpu2[MAX_VER_LENTH0];            /*逻辑版本cpu2*/
        UINT8    uilogicVerCpu3[MAX_VER_LENTH0];            /*逻辑版本cpu3*/

        UINT8    uibootSwVer[MAX_VER_LENTH0];            /*操作系统版本，在BOOT写入*/
        UINT8    uiresSwVer[MAX_VER_LENTH0];             /*驻留软件版本，在MSL写入*/
        UINT8    uisupSwVer[MAX_VER_LENTH0];            /*平台软件版本*/

        UINT8    uiallFcDrvSwVer[MAX_VER_LENTH0];            /*全状态FC 驱动软件版本*/
        UINT8    uiallFcDrvMcuVer[MAX_VER_LENTH0];            /*全状态FC 固件版本*/
        UINT8    uiallFcLogicVer[MAX_VER_LENTH0];            /*全状态FC 逻辑版本*/
        UINT8    uiallFcCfgtblVer[MAX_VER_LENTH0];            /*全状态FC 配置表版本*/

        UINT8    uinsm1BootVer[MAX_VER_LENTH0];             /*NSM软件版本*/
        UINT8    uinsm1MslVer[MAX_VER_LENTH0];            /*NSM板级软件版本*/
        UINT8    uinsm1SoftVer[MAX_VER_LENTH0];            /*NSM管理软件版本*/
        UINT8    uinsm1CfgVer[MAX_VER_LENTH0];            /*NSM配置表版本*/
        UINT8    uinsm1LogicVer[MAX_VER_LENTH0];            /*NSM逻辑版本1*/
        UINT8    uinsm1CpldVer[MAX_VER_LENTH0];            /*NSM逻辑版本2*/
        UINT8    uinsm1McuVer[MAX_VER_LENTH0];            /*NSM辅助测试软件版本*/
        UINT8    uinsm1LoadVer[MAX_VER_LENTH0];            /*NSM加载器软件版本*/


        UINT8    uipsm1SwVer[MAX_VER_LENTH0];               /*PSM软件版本*/
        //UINT8    uipsmLogicVer[MAX_VER_LENTH0];            /*PSM逻辑版本*/
        //UINT8    uipsmCfgtblVer[MAX_VER_LENTH0];           /*PSM配置表版本*/

        UINT8    uinsm2BootVer[MAX_VER_LENTH0];             /*NSM软件版本*/
        UINT8    uinsm2MslVer[MAX_VER_LENTH0];            /*NSM板级软件版本*/
        UINT8    uinsm2SoftVer[MAX_VER_LENTH0];            /*NSM管理软件版本*/
        UINT8    uinsm2CfgVer[MAX_VER_LENTH0];            /*NSM配置表版本*/
        UINT8    uinsm2LogicVer[MAX_VER_LENTH0];            /*NSM逻辑版本1*/
        UINT8    uinsm2CpldVer[MAX_VER_LENTH0];            /*NSM逻辑版本2*/
        UINT8    uinsm2McuVer[MAX_VER_LENTH0];            /*NSM辅助测试软件版本*/
        UINT8    uinsm2LoadVer[MAX_VER_LENTH0];            /*NSM加载器软件版本*/


        UINT8    uipsm2SwVer[MAX_VER_LENTH0];               /*PSM软件版本*/

        UINT8    uindbSwVer[MAX_VER_LENTH0];               /*NDB软件版本*/
        UINT8    uindbCfgtblVer[MAX_VER_LENTH0];           /*NDB配置表版本*/

        UINT8    uimcuSwVer[MAX_VER_LENTH0];            /*MCU软件版本*/
        UINT8    uiloaderSwVer[MAX_VER_LENTH0];            /*加载器软件版本*/
        UINT8    uibootVer[MAX_VER_LENTH0];             /*模块支持层编译时间*/
        UINT8    uimslVer[MAX_VER_LENTH0];             /*模块支持层编译时间*/
        UINT8    uiosVer[MAX_VER_LENTH0];            /*操作系统编译时间*/

        UINT8    uimaintenanceLog[MAX_LOG_SIZE0][MAX_LOG_LENTH0];       /*维护日志5条*/
}IOSS_ADAPTOR_MODULE_INFO;


typedef struct
{
	UINT32 spare[484];
	UINT32 uiSource;
	UINT32 uiFlightId;
	UINT64 ulSysRtc;
	UINT32 uiYear;
	UINT32 uiMonth;
	UINT32 uiDay;
	UINT32 uiHour;
	UINT32 uiMinute;
	UINT32 uiSecond;
	UINT32 uiMsecond;
	UINT32 uiCounter;
}AOXE_TEST_PAYLOAD_TYPE;


//#[ type IOSS_ADAPTOR_SWITCH_CMD
typedef struct{
	INT32 dstid ;
	UINT8 ctrlTableNO ;
}IOSS_SET_SWITCH_TABLE;    


typedef struct{
	INT32 dstid;
	UINT8 channel;  /*通道号（0~17）*/
	UINT8 switchStatus;   /*开关状态（0关1开）*/
}IOSS_SET_SWITCH_STATUS;    

typedef struct{
	INT32 dstid;
	INT32 modid;
}IOSS_GET_SWITCH_CURRENT; 

typedef struct
{
 	UINT8 dstid;
 	UINT32 modid;
}IOSS_GET_SWITCH_VOLTAGE;    

typedef struct
{
 	INT32 dstid;
 	INT8 channelStatus0;
 	INT8 channelStatus1;
 	INT8 channelStatus2;
}IOSS_SET_PSM_POWER_STATUS;

//## type MON_ACQ_ATTR_TYPE
enum MON_ACQ_ATTR_TYPE {
    V_ATTR_ACQUIRE_ONLY = 0x40000000,
    V_ATTR_MONITOR_ONLY = 0x80000000,
    V_ATTR_BOTH_ACQUIRE_AND_MONITOR = 0xc0000000,
    V_ATTR_CLEAR_MONITOR_BIT = 0xffffffff
};

//#[ type IOSS_ADAPTOR_REST_PARTITION
typedef struct
{
 	char *pName;
 	UINT32 operatingMode;
 	UINT32 startCondition;
} IOSS_ADAPTOR_REST_PARTITION;
//#]
//## type NVRAM_ADDR_TYPE
enum NVRAM_ADDR_TYPE {
    TOTAL_NVRAM_RECORD_INFO = 0,
    AOXE_CORE_ERR_NVRAM_INFO,
    AOXE_RUNSTATUS_NVRAM_INFO,
    AOXE_MSGSTATUS_NVRAM_INFO,
    APP_NVRAM_INFO,
    NVRAM_MAX_INFO,
    PLATFORM_NVRAM_INFO
};

//#[ type NVRAM_INFO_TYPE
typedef struct
{
  BOOL m_enableFlag;
  UINT32 m_nodeID; //本地功能节点ID
  UINT32 m_partitionNum; //当前CPU配置的最大分区数
  UINT32 m_partID; //本节点分区号，仅分区网络有效，其它均为0
  UINT32 m_indexID;//本节点分区号的索引
  UINT32 m_nvramAddr;//由于双座底层提供的NVRAM地址从0开始，故此处的地址值为一个相对偏移量
  UINT32 m_nvramSize;

}NVRAM_INFO_TYPE;

typedef  NVRAM_INFO_TYPE NVRAM_INFO_TABLE_TYPE[16];
//#[ type IOSS_ADAPTOR_ICP_BIT_ITEM_CMD

#define    IOSS_ICP_BIT_ITEM_PSM_CERCUIT    				    (0x000000000400000ull) //电流检测电路故障
#define    IOSS_ICP_BIT_ITEM_PSM_OC     						(0x000000000800000ull) //输出电流过流
#define    IOSS_ICP_BIT_ITEM_PSM_OUT_28V     			    (0x000000001000000ull) //28V输出故障
#define    IOSS_ICP_BIT_ITEM_PSM_TEM_GET     			    (0x000000002000000ull) //获取温度错误
#define    IOSS_ICP_BIT_ITEM_PSM_MOD_OVER_TEMP_CUT	        (0x000000008000000ull) //模块超温断电
#define    IOSS_ICP_BIT_ITEM_PSM_KEEP_DATA_CUT		        (0x000000010000000ull) //无法掉电保持数据
#define    IOSS_ICP_BIT_ITEM_PSM_SW_EMER_POWER               (0x000000000400000ull) //无法切换紧急用电
#define    IOSS_ICP_BIT_ITEM_PSM_NVRAM     				    (0x000000000400000ull) //NVRAM故障
#define    IOSS_ICP_BIT_ITEM_SPM_MOD_OVER_TEMP               (0x000000000004000ull) //模块超温
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_ETHER     		        (0x000000000002000ull) //DSP检测故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_GET_TEMP     	        (0x000000000008000ull) //DSP温度错误
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_OVER_TEMP               (0x000000000010000ull) //DSP超温
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_RIO_COM     	        (0x000000000020000ull) //DSP节点RIO通信故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_ID     				    (0x000000000002000ull) //DSP模块标识号错误
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_ETHER     		        (0x000000000002000ull) //DSP以太网故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_SERIAL     		        (0x000000000002000ull) //DSP串口检测故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_NVRAM     		        (0x000000000002000ull) //DSPNVRAM故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_BOOT_WORK               (0x000000000002000ull) //DSP启动模式错误
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_FLASH     		        (0x000000000002000ull) //DSPFLASH出错
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_DDR     			    (0x000000000002000ull) //DSPDDR检测故障
#define    IOSS_ICP_BIT_ITEM_SPM_DSP_RIO_ITF     	        (0x000000000002000ull) //DSPRIO接口故障
#define    IOSS_ICP_BIT_ITEM_SPM_CPU_RIO_ITF   		        (0x000000000002000ull) //处理器RIO接口故障
#define    IOSS_ICP_BIT_ITEM_SPM_OUT_RIO_ITF   		        (0x000000000002000ull) //对外RIO接口错误
#define    IOSS_ICP_BIT_ITEM_SPM_HRDSP_FLASH    		        (0x000000000040000ull) //HRDSP_FLASH出错
#define    IOSS_ICP_BIT_ITEM_SPM_HRDSP_NVRAM     	        (0x000000000080000ull) //HRDSP_NvRAM检测故障
#define    IOSS_ICP_BIT_ITEM_SPM_HRDSP_DDR     		        (0x000000000100000ull) //HRDSP_DDR检测故障
#define    IOSS_ICP_BIT_ITEM_SPM_HRDSP_RIO     		        (0x000000000200000ull) //HRDSP_RIO通信故障
#define    IOSS_ICP_BIT_ITEM_SPM_FPGA     				    (0x000000000400000ull) //预处理FPGA故障
#define    IOSS_ICP_BIT_ITEM_SPM_FPGA_DDR     				(0x000000000800000ull) //预处理FPGA的DDR故障
#define    IOSS_ICP_BIT_ITEM_SPM_FPGA_QDR     				(0x000000001000000ull) //预处理FPGA的QDR故障
#define    IOSS_ICP_BIT_ITEM_SPM_FPGA_RIO_COM     			(0x000000002000000ull) //预处理FPGA的RIO通信故障
#define    IOSS_ICP_BIT_ITEM_SPM_RIO_COM     				(0x000000004000000ull) //RIO通信故障
#define    IOSS_ICP_BIT_ITEM_SPM_CPU_ID     					(0x000000000002000ull) //处理器模块标识号错误
#define    IOSS_ICP_BIT_ITEM_SPM_CPU_RIO_COM      	 		(0x000000000002000ull) //处理器间RIO通信错误
#define    IOSS_ICP_BIT_ITEM_NSM_FPGA     					(0x000000000400000ull) //FPGA故障
#define    IOSS_ICP_BIT_ITEM_NSM_NET_CASC_CFG     			(0x000000000400000ull) //网络级联配置错误
#define    IOSS_ICP_BIT_ITEM_NSM_SW_PORT_COM     			(0x000000000400000ull) //交换端口不能通信
#define    IOSS_ICP_BIT_ITEM_NSM_ETHER_SW_PORT_COM 			(0x000000000400000ull) //以太网交换端口不能通信

/********************************NodeMNG ADAPTOR API***********************************************/

//#[ type V_NODEMNG_APP_OK
#define V_NODEMNG_APP_OK 0x3000fb01
//#]

//#[ type V_NODEMNG_SET_SYMM
#define V_NODEMNG_SET_SYMM 0x3000fb03
//#]

//#[ type V_NODEMNG_CUSTOMIZE_SCC_REPORT
#define V_NODEMNG_CUSTOMIZE_SCC_REPORT  0x3000fb02
//#]

//#[ type V_NODEMNG_REGISTER
#define V_NODEMNG_REGISTER  0x3000fa01
//#]

//#[ type V_NODEMNG_GET_CHILD_NUM
#define V_NODEMNG_GET_CHILD_NUM 0x3000fc01
//#]

//#[ type V_NODEMNG_GET_CHILD
#define V_NODEMNG_GET_CHILD 0x3000fc02
//#]

//#[ type V_NODEMNG_GET_FATHER
#define V_NODEMNG_GET_FATHER 0x3000fc03
//#]

//#[ type V_NODEMNG_GET_LOCAL_ID
#define V_NODEMNG_GET_LOCAL_ID 0x3000fc04
//#]

//#[ type V_NDOEMNG_IS_CHILD
#define V_NDOEMNG_IS_CHILD 0x3000fc05
//#]

//#[ type V_NODEMNG_GET_SCC_SRATUS
#define V_NODEMNG_GET_SCC_SRATUS 0x3000fc06
//#]

//#[ type V_NODEMNG_SET_MAINMODE
#define V_NODEMNG_SET_MAINMODE  0x3000fb16
//#]
//#]
/********************************NodeMNG ADAPTOR API***********************************************/
/********************************IOSS ADAPTOR API***********************************************/

// @IOSS Adaptor(IA) API
//
// @Function:
// use to Initialize busmng module. *This should be invoke before any bus modules launched.*
//
// @Param
// IN IOSS_ADAPTOR_CONFIG_RESOURCE* ptConfigResource: init param, now only use Function node Id
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_CONFIG_RESOURCE tConfigResource = {0};
// tConfigResource.uiNodeId = V_NODE_SYMM;
// IOSS_Adaptor_Initialize(&tConfigResource, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Initialize(IOSS_ADAPTOR_CONFIG_RESOURCE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Initialize(IOSS_ADAPTOR_CONFIG_RESOURCE* ptConfigResource,IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to get bus connection status.
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_CONNECTION_STATUS_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvOutPara type for different CMD)
// 	IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// 	IOSS_ADAPTOR_HANDLE_TYPE uiNetId = V_NET_FC;
// 	IOSS_ADAPTOR_PARAM_TYPE tIossParam = {0};
// 	UINT32 uiStatus = 0;
// 	tIossParam.uiQueryCmd = V_BUS_GET_READY_STATUS;
// 	tIossParam.uiBoxId = 1; //指定子卡，有效值从1开始。必填
// 	tIossParam.pvOutPara = (void*)&uiStatus;
// 	IOSS_Adaptor_Get_Connection_Status(uiNetId, &tIossParam, &rtnCode);
// 	printf("get Status for card 1 %d \n", uiStatus);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Get_Connection_Status(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Get_Connection_Status(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to set Bus Status
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_STATUS_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvInPara type for different CMD)
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_PARAM_TYPE tIossParam = {0};
// tIossParam.uiQueryCmd = V_BUS_SET_TASK_START;
// IOSS_Adaptor_Set_Status(0, &tIossParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
void IOSS_Adaptor_Set_Status(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
//## operation IOSS_Adaptor_Set_Status(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Set_Connection_Status(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to register callback function.
// Now we offer 2 kinds of callback, which is of IOSS_ADAPTOR_CB_ON_OFF_PAYLOAD_TYPE type or  IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE
// IOSS_ADAPTOR_CB_ON_OFF_PAYLOAD_TYPE is used to get online information of other function nodes;
// IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE is used to recv msg. which is aoxe headers + payload
//
// @Param
// IN IOSS_ADAPTOR_CALLBACK* ptCallback: callback type
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// How to Register callback:
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_CALLBACK callback;
// callback.uiCallbackCmd = V_APP_MSG_CALLBACK;   //register recv msg callback if app needs
// callback.pvCallback = (void*)&AppReceiveMessage;
// IOSS_Adaptor_Register_Callback(&callback, &rtnCode);
//
// How to use Callback parameter:
// void AppReceiveMessage(void* ptReadParam)
//  {
//      IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE* ptMsgParam = (IOSS_ADAPTOR_CB_MSG_HANDLER_PAYLOAD_TYPE*)ptReadParam;
//     if(pMsgParam)
//     {
//      	UINT32 uiNetId = ptMsgParam ->uiNetId;
//      	UINT8* pucPayload = ptMsgParam->pucPayload;
//      	switch(pMsgParam->uiMsgType)
//      	{
//      	 	case TOPIC_TYPE_NORMAL:
//      	 		handleDatagram(uiNetId, *((NET_DATA_PACKET_TYPE*)pucPayload));
//      	 		break;
//
//      	 	case TOPIC_TYPE_DATASTREAM:
//      	 		handleStreamDatagram(uiNetId, *((NET_DATA_PACKET_TYPE*)pucPayload));
//      	 		break;
//
//      	 	default:
//      	 		break;
//      	}
//     }
// }
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Register_Callback(IOSS_ADAPTOR_CALLBACK*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Register_Callback(IOSS_ADAPTOR_CALLBACK* ptCallback, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);


// @IOSS Adaptor(IA) API
//
// @Function:
// use to Set bus connection configuration.
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_CONNECTION_CONFIGURATION_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvInPara type for different CMD)
// 	IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// 	IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE tSubTopicTable[] = {
// 	{0x30, 1, 2096},
// 	};//topicId, type(0:urg,1:norm; 2:strm), len(norm:2096, strm:16*1024*1024)
//
// 	IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE tPubTopicTable[] = {
// 	{0x40, 1, 2096},
// 	};
//
// 	IOSS_ADAPTOR_DYNAMIC_TOPIC_TABLE_TYPE tTopicTable = {0};
// 	tTopicTable.uiSubNum = 1;
// 	tTopicTable.uiPubNum = 1;
// 	tTopicTable.ptSubTopicTable = tSubTopicTable;
// 	tTopicTable.ptPubTopicTable = tPubTopicTable;
//
// 	IOSS_ADAPTOR_PARAM_TYPE iossParam = {0};
// 	iossParam.pvInPara = (void*)&tTopicTable;
// 	iossParam.uiQueryCmd = V_DYNAMIC_REGISTER_TOPIC;  //
// 	IOSS_Adaptor_Set_Connection_Configuration(V_NET_FC, &iossParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Set_Connection_Configuration(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Set_Connection_Configuration(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to get bus parameter configuration.
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_PARAMETER_CONFIGURATION_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvInPara type for different CMD)
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// UINT64 ulSysRtc = RtcDate;
// IOSS_ADAPTOR_PARAM_TYPE tIossParam = {0};
// tIossParam.uiQueryCmd = V_CLK_SET_SYS_RTC;
// tIossParam.pvInPara = (void*)&ulSysRtc;
// IOSS_Adaptor_Get_Parameter_Configuration(V_NET_FC, &tIossParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Set_Parameter_Configuration(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Set_Parameter_Configuration(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
// @IOSS Adaptor(IA) API
//
// @Function:
// use to get bus parameter configuration.
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_PARAMETER_CONFIGURATION_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvOutPara type for different CMD)
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_DATE_TYPE timeOfDate = {0};
// IOSS_ADAPTOR_PARAM_TYPE tIossParam = {0};
// tIossParam.uiQueryCmd = V_CLK_GET_DATE;
// tIossParam.pvOutPara = (void*)&timeOfDate;
// IOSS_Adaptor_Get_Parameter_Configuration(V_NET_FC, &tIossParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Get_Parameter_Configuration(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Get_Parameter_Configuration(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to get bus status.
// valid queryCmd can be checked in AOXE_BUSMNG_PARA.h, BUS_STATUS_CMD
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// INOUT IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam : includes cmd, in/out para struct
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage (different pvOutPara type for different CMD)
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IINT32 netAccess = 0;
// IOSS_ADAPTOR_PARAM_TYPE tIossParam = {0};
// tIossParam.uiQueryCmd = V_BUS_LOAD_STATUS;
// tIossParam.pvOutPara = (void*)&netAccess;
// IOSS_Adaptor_Get_Status(V_NET_FC, &tIossParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation IOSS_Adaptor_Get_Status(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_PARAM_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Get_Status(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_PARAM_TYPE* ptConfigParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

//## operation IOSS_Adaptor_Read(UINT32,IOSS_ADAPTOR_READ_PAYLOAD_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Read(UINT32 uiHandle, IOSS_ADAPTOR_READ_PAYLOAD_TYPE* ptReadParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @IOSS Adaptor(IA) API
//
// @Function:
// use to set write message to different buses.
// Now we offer unicast/broadcast/pubsub mode.
// valid queryCmd can be checked in AOXE_IOSERV_PARA.h,IOSS_ADAPTOR_MEESAGE_TYPE
// IOSS_NORMAL_MESSAGE indicates pubsub mode message
// IOSS_NORMAL_WELLKNOWN_MESSAGE indicates unicast mode message (needs to fill uiNextHop).
// BROADCAST_ADDRESS indicates broadcast mode
//
// @Param
// IN  IOSS_ADAPTOR_HANDLE_TYPE uiHandle : netId, like V_NET_FC, defined in netAccessCfgDef.h
// IN IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE* writePayloadType: write payload type
// INOUT IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
//
// @PUBSUB
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE iossWritePayload = {0};
// IOSS_ADAPTOR_WRITE_PAYLOAD writePayload = {0};
// writePayload.uiDataLen = ptMsgHead->uiPayloadLen;
// writePayload.pvPayload = (void*)pucPayload;
// writePayload.uiTopicId = uiTopicId;
// writePayload.pMsgHead = ptMsgHead;
// iossWritePayload.uiQueryCmd = IOSS_NORMAL_MESSAGE;   //pubsubMode
// iossWritePayload.pvWriteData = &writePayload;
// IOSS_Adaptor_Write(V_NET_FC, &iossWritePayload, &rtnCode);
//
// @UNICAST/ BROADCAST
// IOSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE iossWritePayload = {0};
// IOSS_ADAPTOR_WRITE_PAYLOAD writePayload = {0};
// writePayload.uiDataLen = ptMsgHead->uiPayloadLen;
// writePayload.uiNextHop = V_NODE_SYMM/ BROADCAST_ADDRESS;
// writePayload.pvPayload = (void*)pucPayload;
// writePayload.pMsgHead = ptMsgHead;
// iossWritePayload.uiQueryCmd = IOSS_NORMAL_WELLKNOWN_MESSAGE;
// iossWritePayload.pvWriteData = &writePayload;
// IOSS_Adaptor_Write(V_NET_FC, &iossWritePayload, piRtnCode);
//
//
// @Return code
// Successful : return 0
// Fail : return code < 0
// Argument IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode :
// 返回值
//## operation IOSS_Adaptor_Write(IOSS_ADAPTOR_HANDLE_TYPE,IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE*,IOSS_ADAPTOR_RETURN_CODE_TYPE*)
void IOSS_Adaptor_Write(IOSS_ADAPTOR_HANDLE_TYPE uiHandle, IOSS_ADAPTOR_WRITE_PAYLOAD_TYPE* ptWriteParam, IOSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

/****************************************************/


/****************************TSS ADAPTOR(TA) Module*************************************************/

/********************************Common**********************************/
//#[ type TSS_ADAPTOR_MODULE_HANDLE_DEF
typedef enum
{
 	V_TSS_NA = 0,
 	V_TSS_ROUTER_MODULE,
 	V_TSS_TIMESERV_MODULE,
 	V_TSS_MONITOR_MODULE,
 	V_TSS_NODEMNG_MODULE,
 	V_TSS_ADAPTOR_MODULE,
 	V_TOTAL_AOXE_MODULE,
}TSS_ADAPTOR_MODULE_HANDLE_DEF;

typedef struct
{
	UINT32	uiNodeId;
	UINT32	uiHandle;
	void*	pvInitConfig;
	void*   pvTAServ;
}TSS_ADAPTOR_CONFIG_RESOURCE;

typedef struct
{
 	UINT32 uiQueryCmd;
 	UINT32 uiHandle;
 	void* pvInPara;
 	void* pvOutPara;
}TSS_ADAPTOR_PARAM_TYPE;

//#[ type TSS_ADAPTOR_WRITE_PAYLOAD_TYPE
typedef struct
{
 	UINT32 uiQueryCmd;
 	UINT32 uiMsgType;
 	UINT32 uiHandle;
 	void* pvWriteData;
}TSS_ADAPTOR_WRITE_PAYLOAD_TYPE;


typedef struct
{
 	UINT32 uiCallbackCmd;
 	UINT32 uiNotificationId;
 	void* pvCallback;
}TSS_ADAPTOR_CALLBACK;

//#[ type AOXE_VERSION_TYPE
typedef enum
{
 	V_TA_STATUS_NA = 0,
 	V_TA_SET_BEHAVIOR_START, 
 	V_TA_GET_VERSION, 
   	/* TimerChip */
 	V_TIMESERV_GET_DATE, //get year, month, day, hour, minute,second, msecond 
 	V_TIMESERV_GET_LOCAL_RTC,// get local RTC
 	V_TIMESERV_GET_SYS_RTC, // get System RTC   
 	V_TIMESERV_SET_CLIENT,
  	V_TIMESERV_SET_SERVER,
 	V_TIMESERV_SET_DATE, //set year, month, day, hour, minute, second, msecond
  	V_TIMESERV_SET_SYS_RTC,// set System RTC   
  	V_TIMESERV_GET_MISSION_DELTA_RTC,
  	
  	/* High Accuracy Timer*/
  	V_TIMESERV_GET_HIGH_ACCURATE_COUNTER, //high accuracy timer, now valid for dmp/icp
 	V_TIMESERV_GET_HIGH_ACCURATE_FREQUENCY, // high accuracy frequency, now valid for dmp/icp
 	          
 	/* TimeOut Serv */
  	V_TIMESERV_SET_TIMER,
  	V_TIMESERV_CANCEL_TIMER, 
  	
  	V_TIMESERV_CHECK_SERVER, //check if exists time server 
  	
  	/* ROUTER */
	V_ROUTER_CLASSIFICATION_GET,		//get flight classification
	V_ROUTER_CLASSIFICATION_SET,		//set flight classification   
	V_ROUTER_GET_PUBLISH_TOPIC_ITEM,
	V_ROUTER_GET_ROUTER_ITEM,   
	V_ROUTER_GET_ROUTER_STATUS,
	V_ROUTER_GET_NODE_LINK_STATUS, //获取节点链路状态
	V_ROUTER_SET_NODE_LINK_STATUS, //设置节点链路状态

}TSS_ADAPTOR_STATUS_CMD;

/***************************************************************************/
/******************************TIMESERV*************************************/


// IOSS日期定义
//#[ type IOSS_ADAPTOR_DATE_TYPE
typedef struct
{
	UINT32	uiYear;
	UINT32	uiMonth;
	UINT32	uiDay;
	UINT32	uiHour;
	UINT32	uiMinute;
	UINT32	uiSecond;
	UINT32	uiMsecond;
}IOSS_ADAPTOR_DATE_TYPE;
/***************************************************************************/
/******************************ROUTER***************************************/
typedef enum
{
	V_MODE_NA = 0,
	V_MODE_PUBSUB,
	V_MODE_UNICAST,
	V_MODE_MONITOR,
	V_MODE_ROUTER_REPLY,
	V_MODE_BROADCAST,
	V_MODE_BROADCAST_TO_ALL,
	V_MODE_BROADCAST_TO_GROUP,
}ROUTER_DELIVERY_MODE;

//#[ type TSS_ROUTER_CALLBACK_CMD
typedef enum
{
 	V_ROUTER_CALLBACK_NA = 0,
 	/* midware Callback */
 	V_ROUTER_MIDWARE_CALLBACK,
 	/* TssMsg Callback, normal and stream */
 	V_ROUTER_TSS_CALLBACK,
 	/* AppMsg Callback, normal and stream */
 	V_ROUTER_APP_CALLBACK,
}TSS_ROUTER_CALLBACK_CMD;

//callback parameter def
//#[ type TSS_ROUTER_CB_PAYLOAD_TYPE
typedef struct
{
	UINT32 uiTopicId;
	UINT32 uiMsgType;
	UINT8* pucPayload;
	UINT32 uiPayloadLen;
}TSS_ROUTER_CB_PAYLOAD_TYPE;


//#[ type TSS_ADAPTOR_ROUTER_WRITE_PAYLOAD
typedef struct
{
	UINT32 uiSource		; /* source function node ID 		*/
	UINT32 uiDest			; /* destination function node address */
	UINT32 uiMsgSpec		; /* msg transfer specification*/
	UINT32 uiTopicId		; /* normally,   first byte: phscial block, second byte: logcial block */
	UINT64 ulTimeTag		; /* time tag when send message 	*/
	UINT32 uiQos			; /* qos parameter*/
	UINT32 uiPayloadLen	; /* length of pData, UNIT: bytes */
	UINT8* pucPayload		; /* payload data */
	void* pvExtPayload;

}TSS_ADAPTOR_ROUTER_WRITE_PAYLOAD;

#define MAX_LINK_NUM 8
//链路状态结构体
typedef struct
{
	UINT32 uiLinkId;
	UINT32 uiLinkStatus;
}TSS_ROUTER_LINK_STATUS_TYPE;
     
//链路更新结构体
typedef struct
{
	UINT32 uiNodeId;
	UINT32 uiNetId;
	TSS_ROUTER_LINK_STATUS_TYPE tLinkStatus;
}TSS_ROUTER_LINK_STATUS_UPDATE_TYPE;  

//链路报告消息定义
typedef struct
{
   UINT32 uiNodeId;
   UINT32 uiNetId;
   UINT32 uiLinkNum;
   TSS_ROUTER_LINK_STATUS_TYPE tLinkStatus[MAX_LINK_NUM];
}TSS_ROUTER_LINK_STATUS_REPORT_TYPE;      

//节点链路查询信息
typedef struct
{
	UINT32 uiNodeId;
	UINT32 uiNetId;
}TSS_ROUTER_NODE_LINK_QUERY_ITEM;
/***************************************************************************/

/***********************************TSS Adaptor(TA) API********************************************************/

// @TSS Adaptor(TA) API
//
// @Function:
// use to Initialize Tss Adaptor module. *This should be invoked before any tss module launched.*
//
// @Param
// IN TSS_ADAPTOR_CONFIG_RESOURCE* ptConfigResource: init param, now only use Function node Id
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_CONFIG_RESOURCE tTssConfigResource = {0};
// tTssConfigResource.uiNodeId = V_NODE_SYMM;
// TSS_Adaptor_Initialize(&tTssConfigResource, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation TSS_Adaptor_Initialize(TSS_ADAPTOR_CONFIG_RESOURCE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Initialize(TSS_ADAPTOR_CONFIG_RESOURCE* ptConfigResource, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
// @TSS Adaptor(TA) API
//
// @Function:
// use to get status parameter.
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
// INOUT TSS_ADAPTOR_PARAM_TYPE  ptConfigParam: includes cmd, in/out para struct. Cmd can be found in TSS_ADAPTOR_STATUS_CMD
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// TSS_ADAPTOR_RETURN_CODE_TYPE iRet = 0;
// TSS_ADAPTOR_PARAM_TYPE tTssParam = {0};
// UINT32 uiQueryCmd = V_TA_GET_VERSION;
// UINT32 uiLen = 25;
// tTssParam.uiQueryCmd = uiQueryCmd;
// tTssParam.pvInPara = &uiLen;
// /* get Router Version */
// tTssParam.pvOutPara = ptAoxeVersion->acAoxeRouterVer;
// TSS_Adaptor_Get_Status_Parameter(V_TSS_ROUTER_MODULE, &tTssParam, &iRet);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//
//
//## operation TSS_Adaptor_Get_Status_Parameter(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_PARAM_TYPE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Get_Status_Parameter(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_PARAM_TYPE* ptConfigParam, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @TSS Adaptor(TA) API
//
// @Function:
// use to get time relevant parameter. *This is only used in module V_TSS_TIMESERV_MODULE.*
//
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
//
// INOUT TSS_ADAPTOR_PARAM_TYPE  ptConfigParam: includes cmd, in/out para struct
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_HANDLE_TYPE uiHandle = V_TSS_TIMESERV_MODULE;
// TSS_ADAPTOR_PARAM_TYPE tConfigParam = {0};
// UINT64 ulLocalRtc = 0;
// tTssParam.uiQueryCmd = V_TIMESERV_GET_LOCAL_RTC;
// tTssParam.pvOutPara = (void*)&ulLocalRtc;
// TSS_Adaptor_Get_Time_Parameter(V_TSS_TIMESERV_MODULE, &tTssParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation TSS_Adaptor_Get_Time_Parameter(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_PARAM_TYPE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Get_Time_Parameter(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_PARAM_TYPE* ptConfigParam, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @TSS Adaptor(TA) API
//
// @Function:
// use to set time relevant parameter. *This is only used in module V_TSS_TIMESERV_MODULE.*
//
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
//
// INOUT TSS_ADAPTOR_PARAM_TYPE  ptConfigParam: includes cmd, in/out para struct
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_HANDLE_TYPE uiHandle = V_TSS_TIMESERV_MODULE;
// TSS_ADAPTOR_PARAM_TYPE tConfigParam = {0};
// UINT64 ulSysRtc = 123456789;
// tTssParam.uiQueryCmd = V_TIMESERV_SET_SYS_RTC;
// tTssParam.pvInPara = (void*)&ulSysRtc;
// TSS_Adaptor_Set_Time_Parameter(V_TSS_TIMESERV_MODULE, &tTssParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//
//## operation TSS_Adaptor_Set_Time_Parameter(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_PARAM_TYPE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Set_Time_Parameter(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_PARAM_TYPE* ptConfigParam, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

// @TSS Adaptor(TA) API
//
// @Function:
// use to set status parameter.
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
// INOUT TSS_ADAPTOR_PARAM_TYPE  ptConfigParam: includes cmd, in/out para struct. Cmd can be found in TSS_ADAPTOR_STATUS_CMD
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_PARAM_TYPE tConfigParam = {0};
// tTssParam.uiQueryCmd = V_TA_SET_BEHAVIOR_START;
// TSS_Adaptor_Set_Status_Parameter(0, &tTssParam, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//
//
//## operation TSS_Adaptor_Set_Status_Parameter(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_PARAM_TYPE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Set_Status_Parameter(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_PARAM_TYPE* ptConfigParam, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
// @TSS Adaptor(TA) API
//
// @Function:
// use to write message. *now only used in ROUTER module*
//
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
//
// INOUT TSS_ADAPTOR_WRITE_PAYLOAD_TYPE*  ptWriteParam: includes cmd, message type and payload.
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
//
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_HANDLE_TYPE uiHandle = V_TSS_ROUTER_MODULE;
// TSS_ADAPTOR_WRITE_PAYLOAD_TYPE tWriteParam = {0};
// TSS_ADAPTOR_ROUTER_WRITE_PAYLOAD tPayload = {0};
// UINT32 payload[5] = {0,0,1,1,1};
// tPayload.uiSource = V_NODE_SYMM;
// tPayload.uiDest = V_NODE_CNIM;  //publish mode fill with 0.
// tPayload.uiMsgSpec = 0x20000000; //normal send.
// tPayload.uiTopicId = V_TOPIC_XXXX;
// tPayload.ulTimeTag = 0;
// tPayload.uiQos = 0;
// tPayload.uiPayloadLen = 0x123;
// tPayload.pucPayload = (UINT8*)payload;
//
// tWriteParam.uiQueryCmd = V_MODE_UNICAST;  // or V_MODE_PUBSUB
// tWriteParam.uiMsgType = TOPIC_TYPE_NORMAL; // or TOPIC_TYPE_STREAM;   0: urgent, 1:normal, 2:stream
// tWriteParam.pvWriteData = (void*)&tPayload;
// TSS_Adaptor_Write(&tWriteParam, &rtnCode);
//
// @Return code
// Successful : return payload length
// Fail : return code < 0
//
//
//## operation TSS_Adaptor_Write(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_WRITE_PAYLOAD_TYPE*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Write(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_WRITE_PAYLOAD_TYPE* ptWriteParam, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);
// @TSS Adaptor(TA) API
//
// @Function:
// use to register Callback function of tss adaptor modules.
// @Param
// IN TSS_ADAPTOR_HANDLE_TYPE uiHandle.  In Param, use to choose Tss Modules, which can be found in TSS_ADAPTOR_MODULE_HANDLE_DEF
// IN TSS_ADAPTOR_CALLBACK  ptConfigParam: includes cmd, notification Id and callback
// INOUT TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode: return code
//
// @Usage
//
// void onRecvUnicastMsg(void* pvParam)
// {
// 	TSS_ROUTER_CB_PAYLOAD_TYPE* pMsgParam = (TSS_ROUTER_CB_PAYLOAD_TYPE*)pvParam;
// 	if(pMsgParam)
// 	{
// 		UINT32 topicId = pMsgParam->uiTopicId;
// 		UINT32 msgType = pMsgParam->uiMsgType;
// 		UINT8* payload = pMsgParam->pucPayload;
// 		printf("rcv msg 0x%x\n", topicId);
// 	}
// }
//
// TSS_ADAPTOR_RETURN_CODE_TYPE rtnCode = 0;
// TSS_ADAPTOR_CALLBACK tTssCallback = {0};
// tTssCallback.uiCallbackCmd = V_ROUTER_MIDWARE_CALLBACK;
// tTssCallback.pvCallback = (void*)&onRecvUnicastMsg;
// TSS_Adaptor_Register_Callback(V_TSS_ROUTER_MODULE, &tTssCallback, &rtnCode);
//
// @Return code
// Successful : return 0
// Fail : return code < 0
//## operation TSS_Adaptor_Register_Callback(TSS_ADAPTOR_HANDLE_TYPE,TSS_ADAPTOR_CALLBACK*,TSS_ADAPTOR_RETURN_CODE_TYPE*)
void TSS_Adaptor_Register_Callback(TSS_ADAPTOR_HANDLE_TYPE uiHandle, TSS_ADAPTOR_CALLBACK* ptCallback, TSS_ADAPTOR_RETURN_CODE_TYPE* piRtnCode);

/*************************************************************************************************************************/


//#[ ignore
#ifdef __cplusplus
};
#endif

//#]


#endif
