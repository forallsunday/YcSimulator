/*
 * YC_Controller_ToolsFunc.h
 *
 *  Created on: 2025年5月16日
 *      Author: wangx
 */

#ifndef YC_CONTROLLER_MESS_PROCESS_H_
#define YC_CONTROLLER_MESS_PROCESS_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <ICDB_ENUM_STRUCT_IRRM.H>
#include <sysTypes.h>

//******************************发送消息包***************************
// !!! update_ 原为send_ 改为只更新全局变量
// 发送IRST_活动请求通告
void send_Mess_IRST_ACT_REQ_REPORT(UINT8 activity_state, UINT8 act_refused_reason);
// 工作状态报告,参数为bit百分比
void send_Mess_WORK_STATE_REPORT(UINT32 start_remain_time, UINT32 bitpercent);
// IRST工作参数报告-构造
void make_Mess_IRST_OPERATIONAL_PARAS();
// IRST工作参数报告-发送
void send_Mess_IRST_OPERATIONAL_PARAS();
// 硬件配置信息报告
void send_Mess_HW_CONFIG_INFO_REPORT();
// 软件配置信息报告
void send_Mess_SW_CONFIG_INFO_REPORT();
// 健康管理_Raw数据_IRST
void send_Mess_PHM_DATA_RAW_IRST();
// 健康管理_Event数据_MS_SUB
void send_Mess_PHM_DATA_EVENT_MS_SUB();
// 健康管理_HMC数据_MS_SUB,i代表需要发的是第几包数据,从1开始
void send_Mess_PHM_DATA_HMC_MS_SUB(int pack_num);
// 数据库信息
void send_Mess_DATABASEINFO();
// IRST像元参数
void send_Mess_IRST_PIXEL_PARAS();
// 上报los数据
void send_Mess_IRST_LOS(UINT8 data_valid);
// 上报光电IMU导航数据
void send_Mess_IR_NAV_DATA();
// 上报红外注释信息——通用
void send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT();
// 上报可见注释信息——通用
void send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT();
// 上报红外注释信息——监视单帧
void send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT_VIEW();
// 上报可见注释信息——监视单帧
void send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT_VIEW();
// 情报数据传输状态
void send_Mess_ToFC_ID_DATA_TRANSMIT_STATE(ID_DATA_TRANS_FLAG trans_State);
//******************************构建内部消息包***************************
// 调焦消息构建1
void make_Mess_To_TJ(UINT8 cmd, INT8 view_cmd);
// 框架消息构建1
void make_Mess_To_KJ(UINT8 cmd, UINT8 kf_mode);
// 图像处理指令消息1
void make_Mess_To_TXCL_CMD(UINT8 cmd);
// 光窗温控1
void make_Mess_To_GCWK();
// 电源分系统消息构建1
void make_Mess_To_DY(UINT8 work_mode, UINT8 cmd_szgd, UINT8 cmd_glgd, UINT8 cmd_rkbjgd, UINT8 cmd_rkgcgd);
// 惯导导航数据包1
void make_Mess_To_PCS_DATA(UINT8 cmd);
// 向记录仪发1
void make_Mess_To_JLY(UINT8 cmd);
// 向球内数据发--可见探测器1
void make_Mess_To_QNSJ_KJTCQ(UINT8 cmd, UINT8 data1, UINT8 data2);
// 向球内数据发--红外探测器1
void make_Mess_To_QNSJ_HWTCQ(UINT8 cmd, UINT8 data1, UINT8 data2);
// 向球内数据发--温控探测器1
void make_Mess_To_QNSJ_WK(UINT8 cmd);
// 向FPGA发1
void make_Mess_To_FPGA(UINT8 cmd, UINT8 irst_form_mode, UINT8 zsxx_valid);
// 向调光发（写结构体）
void make_Mess_To_TG(UINT8 cmd, UINT8 jg_mode);

// 图像处理注释信息消息1
void make_Mess_To_TXCL_ZSXX();
// 图像处理注释信息消息-时间信息、pos信息获取
void make_Mess_To_TXCL_ZSXX_Time_Pos();

// 在线升级
void make_Mess_To_PCS_Update(); // 惯导升级数据包

// 处理从fpga接收到的所有消息
void fpga_Mess_Process();

// FC系统RTC时间获取
UINT64 fcSysRtcGet();

void test_forFpga();      // fpga测试函数
void test_forTXCL_ZZXX(); // 注释信息测试

#ifdef __cplusplus
}
#endif

#endif /* YC_CONTROLLER_MESS_PROCESS_H_ */
