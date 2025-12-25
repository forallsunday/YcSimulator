/*******************************************************************************
        2024-4-3, 10:58:30, 4361, 功能节点定义表, 配置工具生成，请勿修改
*******************************************************************************/
#ifndef AOXEAPPDEF_H
#define AOXEAPPDEF_H
// #include	"BasicTypes.h"

/*	域定义	*/
typedef enum {
    V_DOMAIN_NULL = -1,
    V_TS          = 0x0, /*	智能情报处理域	*/
    V_AM          = 0x1, /*	系统管理域	*/
    V_PM          = 0x2, /*	健康管理域	*/
    V_SR          = 0x3, /*	传感器域	*/
    V_MI          = 0x4, /*	维护接口	*/
    V_WF          = 0x5, /*	武器火控域	*/
    V_VMS         = 0x6, /*	飞管系统	*/
    V_MS          = 0x7, /*	任务域	*/
    V_NAS         = 0x8, /*	导航系统	*/
    V_PV          = 0x9, /*	指控接口域	*/
    V_DC          = 0xa, /*	数据采集域	*/
    V_DL          = 0xb, /*	测控系统域	*/
    V_DOMAIN_MAX  = 998,
} DOMAIN_TYPE;

/*	功能子域定义	*/
typedef enum {
    V_SUBSYS_NULL     = -1,
    V_AIP             = 0x0,  /*	情报处理	*/
    V_JAS             = 0x1,  /*	危险评估	*/
    V_TGF             = 0x2,  /*	目标融合	*/
    V_LAS             = 0x3,  /*	杀伤力评估	*/
    V_NAF             = 0x4,  /*	导航融合	*/
    V_SYM             = 0x5,  /*	系统管理	*/
    V_AOXE            = 0x6,  /*	执行环境	*/
    V_GSM             = 0x7,  /*	核心处理	*/
    V_PHM             = 0x8,  /*	健康管理	*/
    V_IRR             = 0x9,  /*	综合光电	*/
    V_CRS             = 0xa,  /*	通信侦察	*/
    V_CNI             = 0xb,  /*	通讯导航	*/
    V_EWJ             = 0xc,  /*	电子战干扰	*/
    V_ERD             = 0xd,  /*	预警雷达	*/
    V_EWS             = 0xe,  /*	电子战侦察告警	*/
    V_SRM             = 0xf,  /*	传感器管理	*/
    V_RDR             = 0x10, /*	侦察监视雷达	*/
    V_PMA             = 0x11, /*	便携维护接口设备	*/
    V_GMP             = 0x12, /*	地面维护接口板	*/
    V_SMS             = 0x13, /*	悬挂物管理	*/
    V_FCC             = 0x14, /*	火控解算	*/
    V_VCA             = 0x15, /*	飞管计算机A	*/
    V_VCB             = 0x16, /*	飞管计算机B	*/
    V_TMM             = 0x17, /*	战术管理	*/
    V_NAC             = 0x18, /*	导航管理	*/
    V_TRP             = 0x19, /*	威胁响应	*/
    V_IN3             = 0x1a, /*	惯导3	*/
    V_IN1             = 0x1b, /*	惯导1	*/
    V_IN2             = 0x1c, /*	惯导2	*/
    V_DCR             = 0x1d, /*	右混合接口	*/
    V_DCL             = 0x1e, /*	左混合接口	*/
    V_MDC             = 0x1f, /*	任务数据采集	*/
    V_MDE             = 0x20, /*	维护数据记录	*/
    V_DM              = 0x21, /*	数据管理	*/
    V_DLS             = 0x22, /*	测控系统	*/
    V_SUB_DOMAIN_TYPE = 9998,
} SUB_DOMAIN_TYPE;

/*	功能节点定义	*/
typedef enum {
    V_NODE_JASM = 0x0961, /*	危险评估单元	*/
    V_NODE_TGFI = 0x0901, /*	综合识别	*/
    V_NODE_TGFS = 0x08FF, /*	空面目标融合	*/
    V_NODE_TGFA = 0x08FE, /*	空空目标融合	*/
    V_NODE_CPEG = 0x0900, /*	协同作战	*/
    V_NODE_NAFM = 0x0835, /*	导航融合处理单元	*/
    V_NODE_SYMM = 0x17D5, /*	系统管理单元	*/
    V_NODE_SYMD = 0x17D6, /*	系统数据库单元	*/
    V_NODE_APHM = 0x1BBE, /*	飞机系统健康管理单元	*/
    V_NODE_MPHL = 0x1BBD, /*	任务系统左健康管理单元	*/
    V_NODE_MPHR = 0x1BC1, /*	任务系统右健康管理单元	*/
    V_NODE_IRRM = 0x076D, /*	光雷管理单元	*/
    V_NODE_CRSM = 0x0A8D, /*	通信侦察管理	*/
    V_NODE_CNLA = 0x0644, /*	数据链代理	*/
    V_NODE_CNIM = 0x0641, /*	CNI系统控制管理	*/
    V_NODE_EWJM = 0x07D1, /*	电子战干扰管理	*/
    // V_NODE_ERDM	=	0x0A29,	/*	预警雷达管理	*/
    V_NODE_EDRM = 0x0A29, /*	预警雷达管理	*/
    V_NODE_EWSM = 0x0709, /*	电子战管理控制	*/
    V_NODE_SRMM = 0x03E9, /*	传感器任务管理单元	*/
    V_NODE_RDRM = 0x06A5, /*	雷达管理单元	*/
    V_NODE_PMAM = 0x23F1, /*	便携维护接口单元	*/
    V_NODE_GMPM = 0x23F2, /*	地面维护接口单元	*/
    V_NODE_VCAM = 0x1FA5, /*	飞控单元A	*/
    V_NODE_VCBM = 0x1FA6, /*	飞控单元B	*/
    V_NODE_VCCM = 0x1FA7, /*	飞控单元C（仅与惯导直连）	*/
    V_NODE_IFRP = 0x0C1F, /*	任务重规划单元	*/
    V_NODE_TMMM = 0x0C1D, /*	战术管理处理单元	*/
    V_NODE_NACL = 0x0C81, /*	左导航管理单元	*/
    V_NODE_NACR = 0x0C82, /*	右导航管理单元	*/
    V_NODE_TRPM = 0x0CE5, /*	威胁响应单元	*/
    V_NODE_IN1M = 0x0515, /*	惯导1单元	*/
    V_NODE_IN2M = 0x0579, /*	惯导2单元	*/
    V_NODE_IN3M = 0x05DD, /*	惯导3单元	*/
    V_NODE_DCRM = 0x1451, /*	右混合接口单元	*/
    V_NODE_DCLM = 0x13ED, /*	左混合接口单元	*/
    V_NODE_DCRD = 0x1452, /*	右数管单元	*/
    V_NODE_DCLD = 0x13EE, /*	左数管单元	*/

    V_NODE_EIPM = 0x0903, /*	电磁情报处理（可能后续会分为多个子应用）	*/
    V_NODE_IIPM = 0x0902, /*	图像情报处理（可能后续会分为多个子应用）	*/

    V_NODE_LASM = 0x09C5, /*	杀伤评估单元	*/
    V_NODE_SMET = 0x1008, /*	嵌训弹道解算	*/
    V_NODE_SMSM = 0x1005, /*	悬挂物系统管理	*/
    V_NODE_FCAS = 0x106A, /*	空面火控单元	*/
    V_NODE_FCCM = 0x1069, /*	火控解算单元	*/

    V_NODE_SMU1 = 0x1006, /*	FRIU1接口单元	*/
    V_NODE_SMU2 = 0x010A, /*	FRIU2接口单元	*/
    V_NODE_DCLP = 0x00F1, /*	左地图单元	*/
    V_NODE_MNTR = 0x113E, /*	系统数据库单元	*/
    V_NODE_ADAS = 0x213E, /*	系统数据库单元	*/
    V_NODE_ICPM = 0x313E, /*	系统数据库单元	*/

    V_NODE_CDLM = 0x2009, /*	C链路端机（宽带遥测）	*/
    V_NODE_KDLM = 0x200A, /*	K链路端机（宽带遥测）	*/

    // 执行环境节点id无意义
    V_NODE_AOXE_D = 0x17DB, /*	执行环境_目的	*/
    V_NODE_AOXE_S = 0x17DA, /*	执行环境_源	*/

    // cpum节点id为纯手动定义
    V_NODE_CPDM = 0x17D8, /*	核心管理单元	*/
    V_NODE_CPUM = 0x17D9, /*	CPU管理单元	*/

    // IPM1（AIMP1、AIMP2）
    V_NODE_CPUMGP11 = 0x6110, // V_NODE_CPUM_AIMP1_IPM1_1（D2000/8）
    V_NODE_CPUMGP12 = 0x6111, // V_NODE_CPUM_AIMP2_IPM1_1（D2000/8）
    V_NODE_CPUMGP13 = 0x6112, // AIMP1_IPM1_2（FT2000/4）
    V_NODE_CPUMGP14 = 0x6113, // AIMP2_IPM1_2（FT2000/4）

    // IPM2（AIMP1、AIMP2）
    V_NODE_CPUMGP21 = 0x6114, // V_NODE_CPUM_AIMP1_IPM2_1（D2000/8）
    V_NODE_CPUMGP22 = 0x6115, // V_NODE_CPUM_AIMP2_IPM2_1（D2000/8）
    V_NODE_CPUMGP23 = 0x6116, // AIMP1_IPM2_2（FT2000/4）
    V_NODE_CPUMGP24 = 0x6117, // AIMP2_IPM2_2（FT2000/4）

    // IPM3（AIMP1、AIMP2）
    V_NODE_CPUMGP31 = 0x6118, // V_NODE_CPUM_AIMP1_IPM3_1（D2000/8）
    V_NODE_CPUMGP32 = 0x6119, // V_NODE_CPUM_AIMP2_IPM3_1（D2000/8）
    V_NODE_CPUMGP33 = 0x6120, // AIMP1_IPM3_2（FT2000/4）
    V_NODE_CPUMGP34 = 0x6121, // AIMP2_IPM3_2（FT2000/4）

    // IPM4（AIMP1、AIMP2）
    V_NODE_CPUMGP41 = 0x6122, // V_NODE_CPUM_AIMP1_IPM4_1（D2000/8）
    V_NODE_CPUMGP42 = 0x6123, // V_NODE_CPUM_AIMP2_IPM4_1（D2000/8）
    V_NODE_CPUMGP43 = 0x6124, // AIMP1_IPM4_2（FT2000/4）
    V_NODE_CPUMGP44 = 0x6125, // AIMP2_IPM4_2（FT2000/4）

    // IOM（AIMP1、AIMP2）
    V_NODE_CPUMGI11 = 0x6126, // V_NODE_CPUM_AIMP1_IOM11
    V_NODE_CPUMGI12 = 0x6127,
    V_NODE_CPUMGI21 = 0x6128, // V_NODE_CPUM_AIMP2_IOM11
    V_NODE_CPUMGI22 = 0x6129,

    V_NODE_CPUMSP11 = 0x6130,
    V_NODE_CPUMSP21 = 0x6131,
    V_NODE_CPUMSP31 = 0x6132,
    V_NODE_CPUMSP41 = 0x6133,

    V_NODE_CPUMPS11 = 0x6134,
    V_NODE_CPUMPS21 = 0x6135,

    V_NODE_CPUMNS11 = 0x6136,
    V_NODE_CPUMNS21 = 0x6137,

} FUNCTION_NODE_TYPE;

/*	优先级定义	*/
typedef enum {
    AOXETASK_HIGH_PRIORITY = 0,
    AOXETASK_ABOVE_NORMAL,
    AOXETASK_NOMAL,
    AOXETASK_BELOW_NORMAL,
    AOXETASK_IDLE,
    APPTASK_HIGH_PRIORITY,
    APPTASK_ABOVE_NORMAL,
    APPTASK_NOMAL,
    APPTASK_BELOW_NORMAL,
    APPTASK_IDLE,
    AOXETASK_ABOVE_NORMAL_1,
    AOXETASK_ABOVE_NORMAL_2,
    AOXETASK_ABOVE_NORMAL_3,
    AOXETASK_ABOVE_NORMAL_4,
    AOXETASK_ABOVE_NORMAL_5,
    AOXETASK_ABOVE_NORMAL_6,
    AOXETASK_NOMAL_1,
    AOXETASK_NOMAL_2,
    AOXETASK_NOMAL_3,
    AOXETASK_NOMAL_4,
    AOXETASK_NOMAL_5,
    AOXETASK_NOMAL_6,
    AOXETASK_NOMAL_7,
    AOXETASK_NOMAL_8,
    AOXETASK_NOMAL_9,
} PRIORITY_TYPE_DEF;

typedef struct
{
    FUNCTION_NODE_TYPE function_node_no;   /*	功能节点号	*/
    char              *function_node_name; /*	功能节点名	*/
} FUNCTION_NODE_TABLE;

#endif /*	AOXEAPPDEF_H	*/
