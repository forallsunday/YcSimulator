/************************************************************************
*				成都飞机设计研究所 版权所有
* 	 Copyright (C) 2011 CADI Inc. All Rights Reserved.
***********************************************************************/

/*
 * 修改历史：
 * 2023-12-21    成都飞机设计研究所-15部
 *               创建该文件。
*/

/*
* @file： cadi_user.h
* @brief：
*    <li>中间件接口</li>
* @implements: DK2.3.3
*/

#ifndef CADI_USER_H_
#define CADI_USER_H_


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
/************************接口声明******************************/

/*
 * module_name:模型名或app名
 * xml_name：xml文件名
 * */
int topic_init(char *module_name,char *xml_name);

/*
 * topic:读取的topic
 * ptr：读取数据存放的结构体
 * flag：打印标志位，0关闭，1打开
 * */
int topic_read(char *topic,void *ptr, int flag);

/*
 * topic:写入的topic
 * ptr：写入的结构体
 * flag：打印标志位，0关闭，1打开
 * */
int topic_write(char *topic,void *ptr,int flag);

void shm_clear(int clear_num);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif

