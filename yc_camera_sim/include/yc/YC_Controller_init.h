/*
 * YC_Controller_init.h
 *
 *  Created on: 2025年4月30日
 *      Author: wangx
 *      初始化系统变量函数声明
 */

#ifndef YC_CONTROLLER_INIT_H_
#define YC_CONTROLLER_INIT_H_
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "sysTypes.h"
// #include <tasks.h>
// #include <attribute.h>
// #include <periodtasks.h>
// //**************************创建线程**************************
// //**UINT32 affinity:处理器核号
// //**ACoreOs_task_priority priority：优先级
// //**ULONG stack_size：任务栈大小
// //**ACoreOs_name name：任务名称
// //**Task_ID task_id：任务id
// //**ACoreOs_task_entry entryPoint：任务入口函数
// //**************************创建线程**************************
// void yc_Create_Task(UINT32 affinity, ACoreOs_task_priority priority,  ULONG stack_size, ACoreOs_name name,Task_ID task_id, ACoreOs_task_entry entryPoint );

// //**************************创建周期线程**************************
// //**UINT32 affinity:处理器核号
// //**ACoreOs_task_priority priority：优先级
// //**ULONG stack_size：任务栈大小
// //**ACoreOs_name name：任务名称
// //**Task_ID task_id：任务id
// //**ACoreOs_task_entry entryPoint：任务入口函数
// //**************************创建线程**************************
// void yc_Create_Period_Task(UINT32 affinity,ACoreOs_task_priority priority, ULONG stack_size, ACoreOs_name name, Task_ID * task_id, ACoreOs_task_entry entryPoint,ACoreOs_interval periodLength);

extern void param_Init(); // 参数初始化
extern void mess_Init();  // 消息初始化
// extern void flash_Data_Init();//持久化存储信息初始化
// extern void interrupt_Init();//中断初始化

// void mess_Init();

// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_INIT_H_ */
