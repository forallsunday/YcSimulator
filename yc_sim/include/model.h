/**
 * @Author: Chongyang Liu
 * @Date:   2025-09-06 20:50:29
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-09-24 15:50:44
 */
/************************************************************************
*				成都飞机设计研究所 版权所有
* 	 Copyright (C) 2011 CADI Inc. All Rights Reserved.
***********************************************************************/


/*
* @file： moudule.h
* @brief：
*    <li>模型通用接口</li>
* @implements: DK2.3.3
*/

#ifndef MODULE_H_
#define MODULE_H_
#define  uword  unsigned char
#define BITS(x)         (sizeof(x)*4)

#define UDPBITMAP_SIZE  20

/************************头文件********************************/
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
/************************接口声明******************************/

int usrmode_wait();

void usrmode_freeze();

void usrmode_report();

void usrmode_init();
		
void usrmode_scheduler(int status_flag);

void usrmode_close();

	
void step_calculate();

void step_freeze();


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
