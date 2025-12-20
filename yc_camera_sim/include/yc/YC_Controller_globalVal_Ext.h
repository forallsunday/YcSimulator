///*
// * YC_Controller_globalVal_Ext.h
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *
// *      描述：在该文件中定义所有全局变量的extern
// */
#ifndef YC_CONTROLLER_GLOBALVAL_EXT_H_
#define YC_CONTROLLER_GLOBALVAL_EXT_H_
// #ifdef __cplusplus
// extern "C" {
// #endif
#include <sysTypes.h>
// #include <tasks.h>
// #include <attribute.h>
#include <stdio.h>
#include <stdlib.h>
// #include <printk.h>
// #include <mosErrno.h>
// #include <config_appcfg.h>
// #include <logLib.h>
// #include <acSmp.h>
// #include <lstLib.h>
#include <stdio.h>
#include <stdlib.h>
// #include "ioFcApi.h"
#include "ICDB_ENUM_STRUCT_IRRM.H"
#include "ICDB_TOPIC_DESCRIPTION_IRRM.H"
#include "ICDB_TOPIC_STRUCT_IRRM.H"
#include "YC_Controller_Computer.h"
#include "YC_Controller_Constant_Define.h"
#include "YC_Controller_FPGA_Mess.h"
// #include "YC_Controller_Main_Process.h"
#include "YC_Controller_TG_Process.h"

#include <atomic>
//-----------------------------------------主控线及定时器程控制用参数--------------------------------------------
// // 线程id定义
// extern Task_ID YC_FC_Recv;          // 接收FC消息线程，放入list缓冲区
// extern Task_ID YC_Main_Control;     // 主流程控制线程
// extern Task_ID YC_Others_Porcess;   // 其他消息处理线程
// extern Task_ID YC_Period_Send_Mess; // 周期发送线程
// // 定时器定义
// extern ACoreOs_id timer_id_5ms; // 5ms周期定义
// // 消息缓冲区
// extern LIST list_Mess_FromFc_IRST_act_req; // FC接收消息缓冲区-IRST_ACT_REQ
// extern LIST list_Mess_FromFc_Others;       // FC接收消息缓冲区-其他消息
// // 信号量
// extern ACoreOs_id   bSemId_list_Mess_FromFc_IRST_act_req;   // FC接收消息缓冲区互斥锁id-IRST_ACT_REQ
// extern ACoreOs_name bSemName_list_Mess_FromFc_IRST_act_req; // FC接收消息缓冲区互斥锁name-IRST_ACT_REQ
// extern ACoreOs_id   bSemId_list_Mess_FromFc_Others;         // FC接收消息缓冲区互斥锁id-其他消息
// extern ACoreOs_name bSemName_list_Mess_FromFc_Others;       // FC接收消息缓冲区互斥锁name-其他消息
// // 主控用标志位
extern UINT8            flag_Fpga_Interrupt;  // fpga中断，0为未收到中断，1为已收到中断
// extern int              flag_Fpga_down_times; // 统计fpga未触发次数//fpga掉线次数
extern std::atomic<int> flag_Fpga_down_times; // 统计fpga未触发次数//fpga掉线次数
extern UINT8            flag_Fpga_bg;         // 曝光信号到达
//-----------------------------------------主控线及定时器程控制用参数------------------END--------------------------

//-----------------------------------------主控状态控制及参数计算用参数--------------------------------------------
extern MAIN_CONTROL_STATE_PARAM main_Control_State_Param; // 主控从状态、控制数据记录等
// 主控收到指令寄存器
extern CMD_FROM_FC cmd_From_FC; // 用于缓存从fc来的IRST_ACT_REQ消息，和能执行的指令
// 主控flash存储持久化信息
extern MESS_FROMFC_HWINFO_FLASH nbMess_hwInfo_FLASH;
// 静态成像ICD
extern MESS_FROMFC_JT_PHOTO nbMess_jt_Photo;
// 记录各功能单元的应用状态结构体
extern V_NODE_APP_STATE vnode_APP_STATE;

// 主控计算用参数，主要包含两类，（一）计算输入参数和（二）计算输出参数
// 一、计算输入参数包括两类：
// 1.来自FC上端接收，需要定义相关变量进行缓存,主要包括各种工作模式使用的参数,以及其他控制参数
extern PARAM_COMPUTE_INPUT_FROMFC param_Compute_Input_Fromfc;
// 2.来自内部fpga各分系统,也要定义一个结构体，用mess_From_Fpga中的相关参数乘以LSB后进行缓存
extern PARAM_COMPUTE_INPUT_FROMFPGA param_Compute_Input_Fromfpga;
// 二、计算输出参数：
extern PARAM_COMPUTE_OUTPUT param_Compute_Output; // 主控计算输出参数结构体

// 调光用相关参数
extern TG_PARAM     tg_Param;     // 调光用参数结构体
extern MESS_TO_TG   mess_To_TG;   // 向调光发送
extern MESS_FROM_TG mess_From_TG; // 从调光接收
//-----------------------------------------主控状态控制及参数计算用参数---------------END-----------------------------

//---------------------------------外部FC消息定义----------------------------------------
// 从FC接收的消息，需要使用其参数
extern SYM_OPERATIONAL_PARAS   temp_mess_FromFc_SYM_OPERATIONAL_PARAS;   // 系统管理工作参数报告
extern SYM_TIME_REPORT         temp_mess_FromFc_SYM_TIME_REPORT;         // 系统管理时间信息报告
extern INS1_OPERATIONAL_PARAS  temp_mess_FromFc_INS1_OPERATIONAL_PARAS;  // INS1工作参数报告
extern INS2_OPERATIONAL_PARAS  temp_mess_FromFc_INS2_OPERATIONAL_PARAS;  // INS2工作参数报告
extern INS3_OPERATIONAL_PARAS  temp_mess_FromFc_INS3_OPERATIONAL_PARAS;  // INS3工作参数报告
extern INS1_NAV_DATA           temp_mess_FromFc_INS1_NAV_DATA;           // INS1导航数据
extern INS2_NAV_DATA           temp_mess_FromFc_INS2_NAV_DATA;           // INS2导航数据
extern INS3_NAV_DATA           temp_mess_FromFc_INS3_NAV_DATA;           // INS3导航数据
extern ABSOLUTE_NAV_DATA_FUSED temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED; // 绝对导航融合飞行参数
extern NAV_PARAS               temp_mess_FromFc_NAV_PARAS;               // 导航参数报告
extern MISSION_EVENT_REPORT    temp_mess_FromFc_MISSION_EVENT_REPORT;    // 战术任务事件报告
// 向FC发送的消息
extern IRST_ACT_REQ_REPORT            mess_ToFC_IRST_ACT_REQ_REPORT;            // IRST_活动请求通告
extern WORK_STATE_REPORT              mess_ToFC_WORK_STATE_REPORT;              // 工作状态报告
extern IRST_OPERATIONAL_PARAS         mess_ToFC_IRST_OPERATIONAL_PARAS;         // IRST工作参数报告
extern IRST_OPERATIONAL_PARAS         temp_mess_ToFC_IRST_OPERATIONAL_PARAS;    // IRST工作参数报告6——用于比较与上一次是否一致，不一致则上报
extern HW_CONFIG_INFO_REPORT          mess_ToFC_HW_CONFIG_INFO_REPORT;          // 硬件配置信息报告
extern SW_CONFIG_INFO_REPORT          mess_ToFC_SW_CONFIG_INFO_REPORT;          // 软件配置信息报告
extern PHM_DATA_RAW_IRST              mess_ToFC_PHM_DATA_RAW_IRST;              // 健康管理_Raw数据_IRST
extern PHM_DATA_EVENT_MS_SUB          mess_ToFC_PHM_DATA_EVENT_MS_SUB;          // 健康管理_Event数据_MS_SUB
extern PHM_DATA_HMC_MS_SUB            mess_ToFC_PHM_DATA_HMC_MS_SUB;            // 健康管理_HMC数据_MS_SUB
extern DATABASEINFO                   mess_ToFC_DATABASEINFO;                   // 数据库信息
extern IRST_PIXEL_PARAS               mess_ToFC_IRST_PIXEL_PARAS;               // IRST像元参数10
extern IRST_LOS                       mess_ToFC_IRST_LOS;                       // 上报los数据
extern IR_NAV_DATA                    mess_ToFC_IR_NAV_DATA;                    // 光电IMU导航数据
extern RECONNAISED_AREA_IR_2GCS_EVENT mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT; // 侦察覆盖区域参数_IR,红外注释信息
extern RECONNAISED_AREA_TV_2GCS_EVENT mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT; // 侦察覆盖区域参数_TV,可见注释信息
extern ID_DATA_TRANSMIT_STATE         mess_ToFC_ID_DATA_TRANSMIT_STATE;         // 情报数据传输状态
//---------------------------------外部FC消息定义------------------END----------------------

//---------------------------------内部系统读写数据定义----------------------------------------
// 向fpga写的消息数据
extern Mess_To_TJ         mess_To_TJ;         // 向调焦发
extern Mess_To_KJ         mess_To_KJ;         // 向框架发
extern Mess_To_TXCL_CMD   mess_To_TXCL_CMD;   // 向图像处理指令
extern Mess_To_TXCL_ZSXX  mess_To_TXCL_ZSXX;  // 图像处理-注释信息
extern Mess_To_DY         mess_To_DY;         // 向电源发
extern MESS_To_GCWK       mess_To_GCWK;       // 向光窗温控发
extern Mess_TO_PCS_DATA   mess_TO_PCS_DATA;   // 向惯导发数据包
extern MESS_To_PCS_Update mess_To_PCS_Update; // 向惯导发
extern MESS_To_JLY        mess_To_JLY;        // 向记录仪发
extern MESS_To_QNSJ       mess_To_QNSJ;       // 向球内数据发
extern MESS_To_FPGA       mess_To_FPGA;       // 向FPGA发
// 从fpga读的消息数据
extern Mess_From_TJ       mess_From_TJ;        // 从调焦收
extern Mess_From_KJ       mess_From_KJ;        // 从框架收
extern Mess_From_TXCL     mess_From_TXCL;      // 从图像处理收
extern Mess_From_TXCL     temp_mess_From_TXCL; // 从图像处理收——给fpga兜底
extern Mess_From_DY       mess_From_DY;        // 从电源收
extern Mess_From_PCS_DATA mess_From_PCS_DATA;  // 从PCS收
extern MESS_From_GCWK     mess_From_GCWK;      // 从光窗温控收
extern MESS_From_JLY      mess_From_JLY;       // 向记录仪发
extern MESS_From_QNSJ     mess_From_QNSJ;      // 向球内数据发
extern MESS_From_FPGA     mess_From_FPGA;      // 向FPGA发
//---------------------------------内部系统读写数据定义-------------END---------------------------

// 外部函数引用
extern STATUS pcieInit(void); // PICE初始化函数外部引用
// 写flash
// extern int my_flash_write(ADDRESS flashStart, char *buf, ULONG nbytes);

// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_GLOBALVAL_EXT_H_ */
