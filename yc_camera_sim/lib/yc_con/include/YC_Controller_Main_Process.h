/*
 * YC_Controller_Process.h
 *
 *  Created on: 2025年5月16日
 *      Author: wangx
 */

#ifndef YC_CONTROLLER_MAIN_PROCESS_H_
#define YC_CONTROLLER_MAIN_PROCESS_H_
// #ifdef __cplusplus
// extern "C" {
// #endif
#include "ICDB_ENUM_STRUCT_IRRM.H"
#include "ICDB_TOPIC_STRUCT_IRRM.H"
#include "sysTypes.h"

#include <chrono>

void main_Control_And_Mess_Process_Act_req_task();            // 主流程控制，处理act_req消息
void fc_Mess_Process_Others_task();                           // 其他消息处理
void fc_Mess_Send_Period_task();                              // 周期消息发送处理
void timer_service_func_5ms();                                // 5ms定时器响应函数，用于统计fpga掉线次数
void isr_Fpga_Mess(UINT32 vector, void *context, LONG param); // 接收到fpage中断的响应函数0A2

void act_req_mess_Process(); // 处理活动请求指令
void act_req_IRST_Process(); // 特殊活动请求指令处理

void wide_Image_Paras_Set();             // 广域成像参数获取及设置
void area_Image_Paras_Set(int AREA_num); // 区域成像参数获取及设置

// 更新系统工作模式、状态相关
void update_Work_State(INT8 state);                 // 更新相机工作状态
void update_Main_Mode(SUBSYS_MAIN_MODE mode);       // 更新相机工作模式
void update_Irst_State(IRST_WORK_STATE irst_state); // 更新IRST工作状态
void update_Irst_Mode(IRST_FORM_MODE irst_mode);    // 更新IRST成像模式

// 工作流程控制----------------
void Work_Control();              // 工作流程控制1
void init_Model_WorkControl();    // 工作流程控制----初始化1
void collect_Model_WorkControl(); // 工作流程控制----收藏1
void prepare_Model_WorkControl(); // 工作流程控制----准备中1
void wait_Model_WorkControl();    // 工作流程控制----待机1
void photo_Model_WorkControl();   // 工作流程控制----拍照1
void check_Model_WorkControl();   // 工作流程控制----自检测1
void na_down_WorkControl();       // 工作流程控制----下电
void nb_jtphoto_WorkControl();    // 工作流程控制----静态成像-内部使用

void param_Over_Range_Judge(); // 参数超限判断

UINT8 jiaozheng_WorkControl(UINT8 rst_n); // 红外校正子函数1

// 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
// 参数1：是否需要给图像处理发送注释信息，返回参数
// 参数2：是否需要向fc发送注释信息，判断参数
// 参数3：是否需要累加条带号、帧号等信息
void photoing_Control(UINT8 *toTxcl_zzxx_valid, UINT8 fcSend_Flag, UINT8 numup_Flag);

void clean_cmd_From_FC();       // 重置指令缓存
void clean_cmd_ImageInfo_Num(); // 重置图像序号

// Note:lcy 增加
extern bool running_main_ctrl;
extern bool running_other_process;
extern bool running_periodic_send;

// 子系统工作模式切换函数 可由外部调用(读取共享内存后切换)
void switchSubsysOperMode(SUBSYS_MAIN_OPER_MODE mode);

// 子系统是否处于初始化中
bool ycInitializing();

// 子系统是否处于正常工作状态
bool ycAlreadyNormal();

// 子系统是否处于下电
bool ycAlreadyStop();

// 重置上电次数
void resetElectrifyAmount();

// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_MAIN_PROCESS_H_ */
