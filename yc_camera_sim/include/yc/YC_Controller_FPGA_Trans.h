///*
// * YC_Controller_FPGA_Communicate.h
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *      
// *      描述：与FPGA通信的底层收发函数定义
// */

#ifndef YC_CONTROLLER_FPGA_TRANS_H_
#define YC_CONTROLLER_FPGA_TRANS_H_
#ifdef __cplusplus
extern "C" {
#endif

//FPGA读函数
void fpga_Recv(void* recv_data, int offset, int datalen);
//FPGA写函数
void fpga_Send(void* send_data, int offset, int datalen);



//FPGA接收消息处理函数

#ifdef __cplusplus
}
#endif
#endif /* YC_CONTROLLER_FPGA_TRANS_H_ */
