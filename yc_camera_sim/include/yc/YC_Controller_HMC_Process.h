/*
 * YC_Controller_HMC_Process.h
 *
 *  Created on: 2025年9月8日
 *      Author: wangx
 */

#ifndef YC_CONTROLLER_HMC_PROCESS_H_
#define YC_CONTROLLER_HMC_PROCESS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "ICDB_TOPIC_STRUCT_IRRM.H"
#define TOTAL_HMC_NUM 56

#pragma pack(1)
// 内部HMC信息记录结构体
typedef struct Struct_HMC_IRST_NB {
    UINT8 flag_LAST_HMC[TOTAL_HMC_NUM];    // 上一次HMC状态，1：产生故障，0：取消故障。发生1、消失0
    UINT8 flag_CURRENT_HMC[TOTAL_HMC_NUM]; // 当前HMC状态，1：产生故障，0：取消故障。发生1、消失0

    HMC_DATA_ITEM_MS_SUB_TYPE_DEF HMC_Data_Item_MS_Sub[TOTAL_HMC_NUM]; // HMC数据项_任务子系统,一共57个故障

    int                           hmc_count_upload;                           // 需要上报的HMC个数
    int                           pack_count;                                 // 需要上报的HMC包数
    HMC_DATA_ITEM_MS_SUB_TYPE_DEF HMC_Data_Item_MS_Sub_upload[TOTAL_HMC_NUM]; // 需要上报的HMC

} HMC_IRST_NB;
#pragma pack()

extern HMC_IRST_NB nb_HMC_DATA;
// 内部HMC数据初始化，主要是编号
void nb_HMC_DATA_INIT();

// HMC信息获取函数,上电、维护、启动后调用，周期调用，记录当前故障______外部调用
void nb_HMC_DATA_SET();

// 记录需要上报的故障信息：包括个数和内容
void nb_HMC_DATA_UPLOAD();

// 清除HMC信息函数，收到指令后调用______外部调用
void nb_HMC_DATA_CLEAR();

#ifdef __cplusplus
}
#endif
#endif /* YC_CONTROLLER_HMC_PROCESS_H_ */
