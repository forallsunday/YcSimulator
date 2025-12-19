#ifndef BasicTypes_H
#define BasicTypes_H

#ifdef _AOXE_ACORES
#include <sysTypes.h>
#endif

#ifdef _AOXE_NT
typedef enum                                  
{
    NO_ERROR       =0,        /*  请求合法并且操作被执行         */
    NO_ACTION      =1,        /*  系统的操作状态未受到请求的影响 */
    NOT_AVAILABLE  =2,        /*  请求不能被立即执行             */
    INVALID_PARAM  =3,        /*  请求中有非法参数               */
    INVALID_CONFIG =4,        /*  请求中的参数与目前配置不匹配   */
    INVALID_MODE   =5,        /*  请求与目前的操作模式不匹配     */
    TIMED_OUT      =6         /*  超时请求所希望的时间           */
} RETURN_CODE_TYPE;
#endif

//## type UINT32
typedef unsigned int UINT32;

//## type INT32
typedef int INT32;

//## type UINT16
typedef unsigned short UINT16;

//## type INT16
typedef short INT16;

//#[ type INT8
typedef signed char INT8;
//#]

//## type UINT8
typedef unsigned char UINT8;

#ifdef _CPU_TYPE_64_
    #define ADDR_TYPE       UINT64
#else
    #define ADDR_TYPE       UINT32
#endif
#ifdef _AOXE_VX68
typedef int BOOL;
#endif

//#[ type BOOL
#ifdef _AOXE_NT
typedef int BOOL;
#endif

#ifdef _AOXE_LNX
typedef int BOOL;
#endif
#ifdef _AOXE_ACOREOS
typedef unsigned int BOOL;
#endif

#ifdef _AOXE_KV1
typedef unsigned int BOOL;
#endif

#if defined(_AOXE_KV3) || defined(_AOXE_KV3_653)
typedef unsigned int BOOL;
#endif

#ifdef _AOXE_HR2
typedef unsigned int BOOL;
#endif
#ifdef _AOXE_DMP
typedef unsigned int BOOL;
#endif
//#]

// lcy: 20251215 这么写要不然编译不过
typedef unsigned int BOOL;

//#[ type BIT
#define BIT( value,pos,len) (((UINT32)(value)<<((4-sizeof(value))*8 +(pos)))>>(32-(len)))
//#]

//## type UCHAR
typedef UINT8 UCHAR;

//#[ type __PACK_STRUCT__
#ifdef _AOXE_NT
#define __PACK_STRUCT__
#else
#define __PACK_STRUCT__
#endif
//#]

//#[ type UINT64
#ifdef _AOXE_NT
typedef unsigned __int64 UINT64;
#else
typedef unsigned long long UINT64;
#endif

//#[ type INT64
#ifdef _AOXE_NT
typedef signed __int64 INT64;
#else
typedef signed long long INT64;
#endif

#ifdef _AOXE_NT
#define NULL 0

#endif

typedef enum
{
	V_KV2_DEADLINE_MISSED = 1,
	V_KV2_APPLICATION_ERR = 2,
	V_KV2_NUMERIC_ERR = 3,
	V_KV2_ILLEGAL_REQ = 4,
	V_KV2_STACK_OVERFLOW = 5,
	V_KV2_MEMORY_VIOLATION = 6,
	V_KV2_STACK_OVER_PEAK = 7,
	V_KV2_HEAP_OVER_PEAK = 8,
	V_KV2_TASK_EXE_TIME_LOG = 9,
	V_KV2_MEMORY_MALOC_FAIL = 10,
	V_KV2_APP_RUN_UNNORMAL = 99,
	V_HM_ERR = 9999
}ERR_CODE_TY;
typedef struct
{
	UINT32 TaskId;
	char TaskName[32];
}TaskInfoType;

typedef enum
{
	V_M_TASK_STOP = 1,		//进程执行完毕
	V_M_TASK_NORMAL = 2,     //正常状态
	V_M_TASK_ERR = 3,        //异常挂起
	V_M_PARAM_INVALID = 99   //输入参数有误
}TASK_MONTIOR_STATUS_TY;

//故障记录类型
typedef enum
{
	V_ERR_PROCESS_EXP = 1,            //进程异常
	V_ERR_RUN_STATUS_MONITOR = 2,     //进程运行状态监控
	V_ERR_OS_RESOURCE_USAGE = 3,      //操作系统使用情况
	V_ERR_PROCESS_DEADLINE = 4,       //进程超时
}ERR_RECORD_TYPE;

typedef struct
{
	ERR_CODE_TY ErrorCode;
	UINT32      ErrorProcId;
	UINT32      ErrorAddress;	
	UINT32      ErrorLr;
	UINT32      ErrorDar;
}ERR_INFO_TYPE;

typedef struct
{
	ERR_RECORD_TYPE ErrorRecordType; //故障记录类型	  
	UINT32 ErrorProcId;              //进程ID 
	UINT32 ErrorStartTime;           //1、进程出现异常的首次发生时间
											             //2、进程监控的开始时间
											             //3、操作系统资源使用情况统计的开始时间
	UINT32 ErrorEndTime;             //1、进程异常结束时间
											             //2、进程监控结束时间
											             //3、操作系统资源使用情况统计的结束时间
	UINT32 ErrorCounter;						 //1、进程故障发生次数
																	 //2、操作系统资源超出门限值发生次数
	UINT32 FuncNodeId;               //应用节点号
	UINT32 ErrorCode;                //故障代码：	
	UINT32 ErrorAddress;             //进程地址
	UINT32 ErrorRecordData1;         //记录数据
	UINT32 ErrorRecordData2;         //记录数据
	//UINT32 ErrorRecordData3;         //记录数据
	//UINT32 ErrorRecordData4;         //记录数据
	UINT32 ErrorAcuYear;
	UINT32 ErrorAcuMonth;
	UINT32 ErrorAcuDay;
	UINT32 ErrorAcuHour;
	UINT32 ErrorAcuMinute;
	UINT32 ErrorAcuSecond;
	UINT32 ErrorAcuLr;
	UINT32 ErrorAcuDar;
}ERR_ITEM_TYPE;

typedef struct
{
	ERR_RECORD_TYPE ErrorRecordType; //故障记录类型	
	UINT32 ErrorProcId;              //进程ID
  /* 最大时间，纳秒,,上一个周期的统计数据  */
  UINT64 MaxTime;
	/* 最小时间，纳秒,上一个周期的统计数据  */
	UINT64 MinTime;
	/* 平均时间，纳秒,上一个周期的统计数据  */
	UINT64 AvgTime;   
	/* 累计运行的周期数,上一个周期的统计数据 */
	UINT32 TotalPeriodCnt;
	/* 应用节点ID*/
	UINT32 FuncNodeId;
	/* 累计时间，纳秒,包括当前周期的累计运行时间   */
	UINT64 TotalTime;
	UINT32 ErrorAcuYear;
	UINT32 ErrorAcuMonth;
	UINT32 ErrorAcuDay;
	UINT32 ErrorAcuHour;
	UINT32 ErrorAcuMinute;
	UINT32 ErrorAcuSecond;
}HM_TASK_EXE_TIME_TYPE;

typedef struct
{
	UINT32  PartErrorTableLen;
	UINT32  PartErrorTotalNum;
	ERR_ITEM_TYPE* ErrorTable; 	
}ERR_TABLE_TYPE;

typedef enum
{
	V_INT_NULL = 0,	
	V_INT_POWER_FAIL ,					//1  电源失效	
	V_INT_S2_RELEASE,						//2  S2开关按压释放
	V_INT_S4_FORWARD_RELEASE,		//3  S4开关前拨释放
	V_INT_S4_BACKWARD_RELEASE,	//4  S4开关后拨释放
	V_INT_S4_LEFT_RELEASE,			//5  S4开关左拨释放
	V_INT_S4_RIGHT_RELEASE,			//6  S4开关右拨释放
	V_INT_S4_MID_RELEASE,				//7  S4开关按压释放
	V_INT_T2_MID_RELEASE,				//8  T2开关按压释放
	V_INT_S7_FIRST_RELEASE,			//9  S7开关一级按压释放
	V_INT_S7_SECOND_RELEASE,		//10 S7开关二级按压释放
	V_INT_DISO10_UP,						//11
	V_INT_DISO11_UP,						//12
	V_INT_DISO12_UP,						//13
	V_INT_DISO13_UP,						//14
	V_INT_DISO14_UP,						//15
	V_INT_DISO15_UP,						//16
	V_INT_DISO16_UP,						//17
	V_INT_S2_PRESS,							//18  S2开关按压
	V_INT_S4_FORWARD,						//19  S4开关前拨
	V_INT_S4_BACKWARD,					//20  S4开关后拨
	V_INT_S4_LEFT,							//21  S4开关左拨
	V_INT_S4_RIGHT,							//22  S4开关右拨
	V_INT_S4_MID_PRESS,					//23  S4开关按压
	V_INT_T2_MID_RRESS,					//24  T2开关按压
	V_INT_S7_FIRST_PRESS,				//25  S7开关一级按压
	V_INT_S7_SECOND_PRESS,			//26  S7开关二级按压
	V_INT_DISO10_DOWN,					//27
	V_INT_DISO11_DOWN,					//28
	V_INT_DISO12_DOWN,					//29
	V_INT_DISO13_DOWN,					//30
	V_INT_DISO14_DOWN,					//31
	V_INT_DISO15_DOWN,					//32
	V_INT_DISO16_DOWN,					//33	
	
}INT_INDEX_TYPE;

typedef enum
{
	V_TM_SRC_DEFAULT = 0,
	V_TM_SRC_RTC = 1,
	V_TM_SRC_FC = 2,
	V_TM_SRC_1394 = 3,	
}TIME_SRC_TYPE;
#define HM_MAX_NAME_LEN1 (64)
#define HM_MAX_SIZE_EVENT_MSG1 (256)
typedef struct
{
	UINT32 uiYear;
	UINT32 uiMonth;
	UINT32 uiDate;
	UINT32 uiHour;
	UINT32 uiMinute;
	UINT32 uiSecond;
	UINT32 uiMillisecond;
}TIME_FicClkDate;
typedef enum
{
	HM_INVALID_LEVEL1 = -1,
	HM_PROCESS_LEVEL1 = 0,
	HM_PARTITION_LEVEL1,
	HM_MULTIPARTITION_LEVEL1,
	HM_MODULE_LEVEL1
}HM_LEVEL1;
typedef enum
{
    HME_DEADLINE_MISSED1 = 0,           /* 第一个ARINC故障代码必须为0 */
    HME_APPLICATION_ERROR1,
    HME_NUMERIC_ERROR1,
    HME_ILLEGAL_REQUEST1,
    HME_STACK_OVERFLOW1,
    HME_MEMORY_VIOLATION1,
    HME_HARDWARE_FAULT1,
    HME_POWER_FAIL1,
    HM_MAX_ARINC_CODES1,
    HME_KERNEL1 = HM_MAX_ARINC_CODES1,
    HME_CONFIG_ERROR1,                     /* 设置错误 */
    HME_INIT_ERROR1,                         /* 初始化错误  */
    HME_PARTITION_OVERFLOW1,          /* 超时 */
    HME_PARTITION_MODE_SET1,          /* 分区模式改变 */
    HME_APEX_INTERNAL_ERROR1,         /* APEX内部故障代码 */
    HME_HM_INTERNAL_ERROR1,            /* 健康监控内部故障代码 */
    HME_PORT_INTERNAL_ERROR1,         /* 核心系统端口内部故障代码 */
    HME_LOST_TICKS1,                        /* 系统时钟tick丢失 */
    HME_OTHER1,                                /* 其他错误 */
    HM_MSG1,                                    /* 健康健康信息 */
    HM_MAX_INJECTABLE_CODES1,        /* 可注入的故障代码最大值 */
    HME_HM_ERROR1 = HM_MAX_INJECTABLE_CODES1,  /* 健康监控错误 */
    HME_HMQ_OVERFLOW1,                  /* 健康监控队列溢出 */
    HME_DATA_LOSS1,                        /* 数据丢失错误 */
    HME_HM_DEADLINE_MISSED1,
    HME_DEFAULT1,
    HME_UNKNOWN1,                           /* 保持配置表兼容性而保留 */
    HM_MAX_CODES1,
    HM_CODE_DEFAULT1 = 0xffffffff
} HM_CODE1;
typedef struct
{
    UINT32 evtTag;
    int core;
    int partNumber;
    HM_LEVEL1 level;
    UINT64 timeStamp;
    UINT32 sysStatus;
    int historicalCode;
    HM_CODE1 code;
    int subCode;
    int addInfo;
    void *addr;
    unsigned long injectorId;
    char injectorName[HM_MAX_NAME_LEN1];
    UINT32 lineNumber;
    char fileName[HM_MAX_NAME_LEN1];
    int msgLen;
    char msg[HM_MAX_SIZE_EVENT_MSG1];
}HM_EVENT1;
typedef struct
{
	TIME_FicClkDate mFicClkDate;
	HM_EVENT1 mhmEvtId;
}HmLogType1;
#define AOXE_ROUTER_AGENT_RELAY_ID 0xD9
#define NORM_APP_MSG_KNOWN_ID 0xD6
#define STRM_APP_MSG_KNOWN_ID 0xD7
#define AOXE_ROUTER_MSG_KNOWN_ID 0xD8
#define AOXE_NODEMNG_MSG_KNOWN_ID 0xDA
#define AOXE_MONITOR_MSG_KNOWN_ID 0xD5
#define NDB_TOPIC 0xFF
#define NDB_RECORD_TOPIC 0xd5ff
#endif
