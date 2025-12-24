///*
// * YC_Controller_Mess_FromFPGA.h
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *
// *      描述：定义从fpga接收的所有分系统的数据结构体
// */

#ifndef YC_CONTROLLER_FPGA_MESS_H_
#define YC_CONTROLLER_FPGA_MESS_H_
// #ifdef __cplusplus
// extern "C" {
// #endif
#include "ICDB_ENUM_STRUCT_IRRM.H"
#include "ICDB_TOPIC_STRUCT_IRRM.H"
// #include "YC_Controller_Main_Process.h"
// #include "YC_Controller_TG_Process.h"

#pragma pack(1)
//*******************1****框架分系统ICD定义**********（包括框架+快反）****************************************
// 框架控制指令
#define KJ_CMD_WAIT 0x00   // 待机（空闲），停留在当前位置
#define KJ_CMD_CHECK 0x01  // 启动自检
#define KJ_CMD_ZHNBEI 0x02 // 准备，随动
#define KJ_CMD_STOP 0x03   // 停止工作，回零位
#define KJ_CMD_SCAN 0x04   // 摆扫
#define KJ_CMD_WATCH 0x05  // 凝视
#define KJ_CMD_TRACK 0x06  // 跟踪
#define KJ_CMD_UPDATE 0x07 // 在线升级

#define KJ_CMD_KF_MODE_EMPTY 0x00 // 0x00初始化值
#define KJ_CMD_KF_MODE_YZJ 0x05   // 0x05（快反从预置角补偿）广域成像、区域成像
#define KJ_CMD_KF_MODE_OWBC 0x0A  // 0x0A（快反从零位补偿）
#define KJ_CMD_KF_MODE_STOP 0xAA  // 0xAA（快反锁零）区域监视

// 框架工作状态
#define KJ_WORK_STATE_NA 0x00    // 未开始
#define KJ_WORK_STATE_SCAN 0x04  // 摆扫
#define KJ_WORK_STATE_WATCH 0x05 // 凝视
#define KJ_WORK_STATE_TRACK 0x06 // 跟踪

#define KJ_WORK_MODE_NA 0x00      // 未开始
#define KJ_WORK_MODE_WORKING 0x01 // 正在执行
#define KJ_WORK_MODE_DONE 0x02    // 执行完成

// 向框架分系统发送的报文------------40字节
typedef struct Struct_Mess_To_KJ {
    UINT8 head1; // 帧头1   0xEB
    UINT8 head2; // 帧头2   0x90
    UINT8 cmd;   // 控制字

    INT32 toKJ_pitch_start;     // 框架俯仰指令   起始角（LSB=0.0001°）
    INT32 toKJ_pitch_end;       // 框架俯仰指令   结束角（LSB=0.0001°）
    INT32 toKJ_direction_start; // 框架方位指令   起始角（LSB=0.0001°）
    INT32 toKJ_direction_end;   // 框架方位指令   结束角（LSB=0.0001°）

    INT16 toKJ_pitch_speed;     // 框架俯仰扫描速度指令（LSB=0.01°/s）
    INT16 toKJ_direction_speed; // 框架方位扫描速度指令（LSB=0.01°/s）

    UINT16 kj_f; // 可见焦距值（LSB = 1mm）
    UINT16 hw_f; // 红外焦距值（LSB = 1mm）

    INT16 pitch_tracking_speed;     // 俯仰单根跟踪（速度）（LSB=0.01°/s）
    INT16 direction_tracking_speed; // 方位单根跟踪（速度）（LSB=0.01°/s）

    UINT8 trackvideo; // 视频跟踪模式：0x00初始化值；0x01可见跟踪；0x02红外跟踪

    UINT8 speed_hight; // 速高比（LSB=0.001）

    INT16 pitch_image_motion_velocity;     // 给定快反俯仰前向像移速度（LSB=0.001°/s)
    INT16 direction_image_motion_velocity; // 给定快反方位前向像移速度（LSB=0.001°/s)

    UINT8 kf_working_mode; /*快反工作模式
                                                                               (0x00初始化值,0x05-广域搜索、区域搜索（快反从预置角补偿）,
                                                                               0x0A-数引模式、手动搜索（快反从零位补偿）,0xAA-地理跟踪、激光照射、自动跟踪（快反锁零）
                                                                              （注：准备命令和搜索/跟踪/照射指令下均需要发送此项内容，补偿镜据此信息进行准备角度）
                                                                               )*/
    UINT8 yuliu;           // 伺服上下电：0xAA下电；0x00上电，默认上
    UINT8 checkSum;        // 校验和
} Mess_To_KJ;

// 从框架分系统接收的报文-----------52字节
typedef struct Struct_Mess_FROM_KJ {
    UINT8 head1; // 帧头1   0xEB
    UINT8 head2; // 帧头2   0x90

    // 工作状态字
    UINT8 status_sub : 4; // 待机/自检/调光/调焦/非均匀校正/准备状态：

    // 0000 未开始0
    // 0001 正在执行1
    // 0010 执行完成2

    UINT8 status_work : 4; // 工作状态： 	0000未开始   0x04摆扫    0x05凝视  0x06跟踪

    // 框架故障字
    UINT16 error_kj_kjfytlyc : 1;  // Bit0  框架俯仰陀螺异常    0：正常1：故障-内框架
    UINT16 error_kj_kjfwtlyc : 1;  // Bit1  框架方位陀螺异常    0：正常1：故障-外框架
    UINT16 error_kj_kjfybmqyc : 1; // Bit2  框架俯仰编码器异常   0：正常1：故障
    UINT16 error_kj_fwbmqyc : 1;   // Bit3  方位编码器异常      0：正常1：故障
    UINT16 error_kj_kjfywzcc : 1;  // Bit4  框架俯仰位置超差    0：正常1：故障
    UINT16 error_kj_kjfwwzcc : 1;  // Bit5  框架方位位置超差    0：正常1：故障
    UINT16 error_kj_kjfysdcc : 1;  // Bit6  框架俯仰速度超差    0：正常1：故障
    UINT16 error_kj_kjfwsdcc : 1;  // Bit7  框架方位速度超差    0：正常1：故障
    UINT16 error_bgxhyc : 1;       // Bit8  曝光信号异常		0：正常1：故障
    UINT16 error_tbl422sjyc : 1;   // Bit9  脱靶量422数据异常	0：正常1：故障
    UINT16 error_possjyc : 1;      // Bit10 POS数据异常			0：正常1：故障
    UINT16 error_kj_fykjcx : 1;    // Bit11  俯仰框架超限		0：正常1：故障
    UINT16 error_kj_fwkjcx : 1;    // Bit12  方位框架超限		0：正常1：故障
    UINT16 error_ADcyyc : 1;       // Bit13  AD采样异常			0：正常1：故障
    UINT16 error_wzsdtbxh : 1;     // Bit14  位置/速度同步信号	0：正常1：故障
    UINT16 error_baoliu0 : 1;      // Bit15  保留				0：正常1：故障

    // 快反故障字
    UINT16 error_kjfytlyc : 1;   // Bit0  俯仰陀螺异常
    UINT16 error_kjfwtlyc : 1;   // Bit1  方位陀螺异常
    UINT16 error_kf422txyc : 1;  // Bit2  快反422通讯异常
    UINT16 error_kfADcyyc : 1;   // Bit3  快反AD采样异常 ——方位、俯仰
    UINT16 error_xybczqxhyc : 1; // Bit4  相移补偿周期信号异常
    UINT16 error_baoliu1 : 3;    // Bit5-7  保留
    UINT16 error_fywzcc : 1;     // Bit8  俯仰位置超差、快反俯仰电机状态异常
    UINT16 error_fwwzcc : 1;     // Bit9  方位位置超差、快反方位电机状态异常
    UINT16 error_fybcsdcc : 1;   // Bit10 俯仰补偿速度超差
    UINT16 error_fwbcsdcc : 1;   // Bit11 方位补偿速度超差
    UINT16 error_fywzcx : 1;     // Bit12  俯仰位置超限
    UINT16 error_fwwzcx : 1;     // Bit13  方位位置超限
    UINT16 error_baoliu2 : 2;    // Bit14-15  保留

    INT32 rtime_pitch_frame;              // 框架实时俯仰角（LSB = 0.0001°)
    INT32 rtime_direction_frame;          // 框架实时方位角（LSB = 0.0001°)
    INT32 exposure_pitch_frame;           // 框架曝光时刻俯仰角（LSB = 0.0001°)
    INT32 exposure_direction_frame;       // 框架曝光时刻方位角（LSB = 0.0001°)
    INT32 exposure_order_pitch_frame;     // 框架曝光时刻俯仰指令角（LSB = 0.0001°)
    INT32 exposure_order_direction_frame; // 框架曝光时刻方位指令角（LSB = 0.0001°)
    INT16 rtime_pitch_frame_top_v;        // 框架实时俯仰陀螺速度（LSB = 0.01°/s)
    INT16 rtime_direction_frame_top_v;    // 框架实时方位陀螺速度（LSB = 0.01°/s)
    INT16 exposure_pitch_frame_top_v;     // 框架曝光时刻俯仰陀螺速度（LSB = 0.01°/s)
    INT16 exposure_direction_frame_top_v; // 框架曝光时刻方位陀螺速度（LSB = 0.01°/s)
    INT16 kfssfybcwz;                     // 快反实时俯仰补偿位置（LSB = 0.0001°)
    INT16 kfssfwbcwz;                     // 快反实时方位补偿位置（LSB = 0.0001°)
    INT16 kfbgskfybcwz;                   // 快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
    INT16 kfbgskfwbcwz;                   // 快反曝光时刻方位补偿位置（LSB = 0.0001°)

    UINT32 yuliu;    // 预留
    UINT8  checkSum; // 校验和

} Mess_From_KJ;
//***********************框架分系统ICD定义**********（包括框架+快反）****END************************************

//************3***********电源分系统ICD定义**************************************************
// 电源子系统工作帧——12字节
typedef struct Struct_Power_Operation_Frame {
    UINT16 head;      // 帧头:0x7E7E
    UINT8  work_mode; // 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
    // 电源开关字
    UINT8 cmd_szgd : 1;   // 数字供电0：关 1：开
    UINT8 cmd_glgd : 1;   // 功率供电0：关 1：开
    UINT8 cmd_rkbjgd : 1; // 热控供电本机：0：关 1：开
    UINT8 cmd_rkgcgd : 1; // 热控供电光窗：0：关 1：开
    UINT8 cmd_baoliu : 4; // 保留

    UINT8 baoliu[7]; // 备用
    UINT8 checkSum;  // 校验和
} Mess_To_DY;

// 电源子系统工作应答帧
typedef struct Struct_Power_Operation_require_Frame {
    UINT16 head;                          // 帧头:0x7E7E
    UINT16 head_number;                   // 帧序号
    UINT16 input_operating_voltage;       // 输入工作电压LSB = 0. 1
    UINT16 input_operating_current;       // 输入工作电流LSB = 0. 1
    UINT16 frame_control_voltage;         // 框架控制电压LSB = 0. 1
    UINT16 frame_control_current;         // 框架控制电流LSB = 0. 1
    UINT16 interface_conversion_voltage;  // 接口转换电压LSB = 0. 1
    UINT16 interface_conversion_current;  // 接口转换电流LSB = 0. 1
    UINT16 image_processing_voltage;      // 图像处理电压LSB = 0. 1
    UINT16 image_processing_current;      // 图像处理电流LSB = 0. 1
    UINT16 PCS_voltage;                   // PCS电压LSB = 0. 1
    UINT16 PCS_current;                   // PCS电流LSB = 0. 1
    UINT16 data_recording_voltage;        // 数据记录电压LSB = 0. 1
    UINT16 data_recording_current;        // 数据记录电流LSB = 0. 1
    UINT16 frame_driving_voltage;         // 框架驱动电压LSB = 0. 1
    UINT16 frame_driving_current;         // 框架驱动电流LSB = 0. 1
    UINT16 variable_driving_voltage;      // 变倍驱动电压LSB = 0. 1
    UINT16 variable_driving_current;      // 变倍驱动电流LSB = 0. 1
    UINT16 high_speed_driving_voltage;    // 高速机驱动电压LSB = 0. 1
    UINT16 high_speed_driving_current;    // 高速机驱动电流LSB = 0. 1
    UINT16 local_thermal_control_voltage; // 本机热控电压LSB = 0. 1
    UINT16 local_thermal_control_current; // 本机热控电流LSB = 0. 1
    UINT16 gc_thermal_control_voltage;    // 光窗热控电压LSB = 0. 1
    UINT16 gc_thermal_control_current;    // 光窗热控电流LSB = 0. 1
    UINT16 working_duration;              // 开机工作时长LSB = 10s

    // 电源子系统状态字1
    UINT8 state_szgd : 1;   // 数字供电0：关 1：开
    UINT8 state_glgd : 1;   // 功率供电0：关 1：开
    UINT8 state_rkbjgd : 1; // 热控供电本机：0：关 1：开
    UINT8 state_rkgcgd : 1; // 热控供电光窗：0：关 1：开
    UINT8 state_baoliu : 4; // 保留

    // 电源子系统故障字1:故障位“1”表示存在，“0”表示不存在或消失
    UINT8 error1_kj : 1;   // 框架控制供电
    UINT8 error1_jk : 1;   // 接口供电
    UINT8 error1_txcl : 1; // 图像处理供电
    UINT8 error1_pcs : 1;  // pcs供电
    UINT8 error1_sjjl : 1; // 数据记录供电
    UINT8 error1_kjqd : 1; // 框架驱动供电
    UINT8 error1_tjqd : 1; // 调焦驱动供电
    UINT8 error1_bbqd : 1; // 变倍驱动供电

    // 电源子系统故障字2:故障位“1”表示存在，“0”表示不存在或消失
    UINT8 error2_gsjqd : 1;   // 高速机驱动供电
    UINT8 error2_baoliu1 : 1; // 保留
    UINT8 error2_rkbj : 1;    // 热控供电本机
    UINT8 error2_rkgc : 1;    // 热控供电光窗
    UINT8 error2_baoliu2 : 1; // 保留
    UINT8 error2_tem : 1;     // 温度传感器
    UINT8 error2_baoliu3 : 2; // 保留

    UINT8 power_tem; // 电源子系统温度LSB = 1
    UINT8 checkSum;  // 校验和
} Mess_From_DY;
//***********************电源分系统ICD定义*****************END*********************************

//**************4*********调焦分系统ICD定义**************************************************
#define TJ_CMD_None 0x00             // 空指令
#define TJ_CMD_Collect 0x76          // 收藏
#define TJ_CMD_CellBIT 0xC2          // 单元自检
#define TJ_CMD_KJselfFocus 0x8B      // 可见自准值检焦
#define TJ_CMD_KJImgFocus 0x33       // 可见自准值检焦
#define TJ_CMD_HWselfFocus 0x4C      // 红外图像检焦
#define TJ_CMD_Light 0x17            // 检光
#define TJ_CMD_HWJZ 0x35             // 红外非均匀校正
#define TJ_CMD_Wait 0xAF             // 待机
#define TJ_CMD_GYCX 0xA0             // 广域成像
#define TJ_CMD_QYCX 0xA4             // 区域成像
#define TJ_CMD_QYJS 0xA6             // 区域监视
#define TJ_CMD_PicLinkTestBegin 0x2B // 图像链路测试开始
#define TJ_CMD_PicLinkTestEnd 0x2C   // 图像链路测试结束
#define TJ_CMD_FlyFocus_Pre 0x6C     // 航空实景检焦-准备
#define TJ_CMD_FlyFocus 0x6D         // 航空实景检焦
#define TJ_CMD_StaticPhoto 0xAA      // 静态成像
#define TJ_CMD_Update 0xCC           // 程序在线升级

#define TJ_CMD_VIEW_BIG 1      // 1：短焦（大视场）
#define TJ_CMD_VIEW_SMALL 0    // 0：长焦（小视场）
#define TJ_CMD_VIEW_DEFAULT -1 // 根据指令

// 调焦子系统工作帧-------24字节
typedef struct Struct_focus_Operation_Frame {
    UINT16 head_number;           // 帧编号
    UINT8  cmd;                   // 命令字
    UINT8  control_tjmode_kj : 1; // 可见手动/自动调焦标志 1：手动；0：自动
    UINT8  control_tjmode_hw : 1; // 红外手动/自动调焦标志 1：手动；0：自动
    UINT8  control_dmzj : 1;      // 是否地面自检状态标志位 1：是；0：否
    UINT8  control_sjss : 1;      // 进行实景搜索标志位；1:进行；0：完成——暂时不用
    UINT8  control_bb : 1;        // 变倍开关，0：长焦（小视场）1：短焦（大视场）
    UINT8  control_tgjzzt : 1;    // 调光反馈的校正状态：0：未完成；1：已完成
    UINT8  control_lzstate : 1;   // 轮载状态，1：地面；0：空中
    UINT8  control_baoliu : 1;    // 保留

    UINT32 distance;   // 照相距离
    INT16  zjwdxx;     // 主镜温度信息，来自温控
    INT16  cjwdxx;     // 次镜温度信息，来自温控
    INT8   sdtjjzl_kj; // 手动调焦校准量-可见
    INT8   sdtjjzl_hw; // 手动调焦校准量-红外
    UINT16 ylz;        // 压力值，来自温控

    UINT8 baoliu[8]; // 备用

} Mess_To_TJ;

// 检调焦子系统工作应答帧--------32字节
typedef struct Struct_focus_Operation_require_Frame {
    UINT16 head_number; // 帧编号:收到主控的帧编号
    UINT8  cmd;         // 收到的命令字

    UINT8 state : 2;           // 状态：0:未开始；1：正在执行；2：执行完成
    UINT8 state_tjmode_kj : 1; // 可见手动/自动调焦标志 1：手动；0：自动
    UINT8 state_tjmode_hw : 1; // 红外手动/自动调焦标志 1：手动；0：自动
    UINT8 state_bb : 1;        // 变倍状态，0：长焦（小视场）1：短焦（大视场）
    UINT8 state_baoliu : 3;    // 保留

    // 工作状态1
    UINT8 status1_zjzt : 1;            // 1：单元自检   	0：单元自检结束
    UINT8 status1_realtime_baoliu : 1; // 1：正在航空实景检焦   0：结束
    UINT8 status1_jmyd : 1;            // 1：正在移动焦面   0：结束
    UINT8 status1_djdw_kj : 1;         // 1：可见检焦步进电机到位  	0：可见检焦步进电机未到位
    UINT8 status1_djdw_hw : 1;         // 1：红外检焦步进电机到位  	0：红外检焦步进电机未到位
    UINT8 status1_bjdj : 1;            // 1：步进电机到位	0：步进电机未到位
    UINT8 status1_sjss : 2;            // 航空实景检焦状态：	00:0状态 01：1状态 10：2状态

    // 工作状态2——保留
    UINT8 status2_bbj_move : 1;    // 1：正在移动变倍镜	0：结束
    UINT8 status2_bbj_dw : 1;      // 1．动变倍镜到位  	0:未到位
    UINT8 status2_jzb_move : 1;    // 1：正在移动校正板	0：结束
    UINT8 status2_jzb_dw : 1;      // 1．校正位置	0:非校正位置
    UINT8 status2_realtime_jj : 1; // 1．实景检校完成	0:实景检校未完成
    UINT8 status2_baoliu : 3;      // 保留

    // 故障字1
    UINT8 error1_kj_wzcc : 1;     // 可见调焦位置超差 1:故障 0：正常
    UINT8 error1_kj_jjcs : 1;     // 可见检焦超时 1:故障 0：正常
    UINT8 error1_kj_tjbmq : 1;    // 可见调焦编码器异常 1:故障 0：正常
    UINT8 error1_hw_wzcc : 1;     // 红外调焦位置超差 1:故障 0：正常
    UINT8 error1_hw_timeout : 1;  // 红外检焦超时 1:故障 0：正常
    UINT8 error1_hw_tjbmq : 1;    // 红外调焦编码器异常 1:故障 0：正常
    UINT8 error1_bbj_dw : 1;      // 变倍镜到位信号异常 1:故障 0：正常
    UINT8 error1_bbj_timeout : 1; // 变倍镜超时 1:故障 0：正常

    // 故障字2
    UINT8 error2_jzb_dw : 1;      // 校正板到位信号异常 1:故障 0：正常
    UINT8 error2_jzb_timeout : 1; // 校正板超时 1:故障 0：正常
    UINT8 error2_ylcgq : 1;       // 压力传感器异常 1:故障 0：正常
    UINT8 error2_bgxh : 1;        // 检调焦曝光信号异常 1:故障 0：正常
    UINT8 error2_txcl : 1;        // 图像处理器通讯异常 1:故障 0：正常
    UINT8 error2_zkmy : 1;        // 主控密钥失效 1:故障 0：正常
    UINT8 error2_fpgamy : 1;      // Fpga密钥失效 1:故障 0：正常
    UINT8 error2_baoliu : 1;      // 保留

    // 故障字3——保留
    UINT8 error3_jjdw_kj : 1; // 可见检焦到位信号异常
    UINT8 error3_jjdw_hw : 1; // 红外检焦到位信号异常
    UINT8 error3_baoliu : 6;  // 保留

    UINT8  baoliu1;                 // 备用
    UINT16 pressure_used_for_focus; // 调焦使用的压力LSB=0.1mbar#
    UINT16 tem_used_for_focus;      // 调焦使用的温度LSB=0. 1℃ #
    INT16  jmwz_kj;                 // 曝光时刻可见焦面位置,下发的-127-127
    INT16  jmwz_hw;                 // 曝光时刻红外焦面位置，下发的-127-127
    UINT16 qxd_hw;                  // 红外检焦用清晰度值
    UINT16 qxd_kj;                  // 可见检焦用清晰度值
    INT16  jmwz_kj_real;            // 曝光时刻可见焦面位置LSB=0.001mm#
    INT16  jmwz_hw_real;            // 曝光时刻红外焦面位置LSB=0.001mm#
    UINT16 baoliu2[5];              // 保留

} Mess_From_TJ;
//***********************调焦分系统ICD定义***************END***********************************

//*************5**********惯导分系统ICD定义**************************************************
// 向PCS发送的机载导航信息
typedef struct Struct_TO_PCS_Data {
    UINT16 head_number; // 帧编号0xAA55

    UINT8  num_of_satellite; // 定位卫星数目
    UINT16 HDOP;             // 水平精度因子

    UINT8 validity_GNSS_alt : 1;           // 有效性-卫星高度
    UINT8 validity_position_wx : 1;        // 有效性-位置
    UINT8 validity_vel_up : 1;             // 有效性-速度天向
    UINT8 validity_vel_west : 1;           // 有效性-速度西向
    UINT8 validity_vel_north : 1;          // 有效性-速度北向
    UINT8 validity_CNI_GNSS_time : 1;      // 有效性-卫星时间
    UINT8 validity_ground_speed : 1;       // 有效性-地速
    UINT8 validity_ground_track_angle : 1; // 有效性-航迹角

    UINT8 validity_pressure_alt : 1;      // 有效性-气压高度
    UINT8 validity_pressure_alt_rate : 1; // 有效性-气压高度变化率
    UINT8 validity_baoliu : 6;            // 保留

    UINT16               date_year;              // 卫星时间_日历日期_日期_年
    UINT8                date_month;             // 卫星时间_日历日期_日期_月
    UINT8                date_day;               // 卫星时间_日历日期_日期_日
    UINT64               time_gnss_calendartime; // 卫星时间_日历时间
    INT32                wx_latitude;            // 载机卫星位置数据-纬度
    INT32                wx_longitude;           // 载机卫星位置数据-经度
    AC_GNSS_ALT_TYPE_DEF ac_GNSS_alt;            // 载机卫星高度-高度
    VEL_NORTH_TYPE_DEF   Vel_North_wx;           // 载机卫星平台系速度-北向速度
    VEL_WEST_TYPE_DEF    Vel_West_wx;            // 载机卫星平台系速度-西向速度
    VEL_UP_TYPE_DEF      Vel_Up_wx;              // 载机卫星平台系速度-天向速度
    INT32                _angle_mrad;            // 载机卫星航迹角_角度_毫弧度
    INT32                _velocity;              // 载机卫星地速

    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate; // 载机气压高度变化率
    AC_PRESSURE_ALT_TYPE_DEF      AC_pressure_alt;      // 载机气压高度

    DATA_GENERATED_TIME_TYPE_DEF data_generated_time; // 数据生成时间_时间_任务时间
    AC_PITCH_TYPE_DEF            ac_pitch;            // 载机俯仰角_角度_毫弧度
    AC_ROLL_TYPE_DEF             ac_roll;             // 载机横滚角_角度_毫弧度
    AC_TRUE_HEADING_TYPE_DEF     ac_true_heading;     // 载机真航向_角度_毫弧度
    VEL_NORTH_TYPE_DEF           Vel_North_pt;        // 载机平台系速度-速度_北向
    VEL_WEST_TYPE_DEF            Vel_West_pt;         // 载机平台系速度-速度_西向
    VEL_UP_TYPE_DEF              Vel_Up_pt;           // 载机平台系速度-速度_天向
    INT32                        pt_latitude;         // 载机位置数据_纬度
    INT32                        pt_longitude;        // 载机位置数据__经度

    AC_HEIGHT_TYPE_DEF                ac_height;                // 载机海拔高度
    AC_GNSS_INERTIAL_ADS_ALT_TYPE_DEF AC_GNSS_inertial_ADS_alt; // 载机惯性卫星大气高度_高度

    UINT8 validity_zt_angle : 1;              // 有效性-姿态角（俯仰、横滚、真航向）
    UINT8 validity_vel : 1;                   // 有效性-速度（北向、西向、天向）
    UINT8 validity_position_pt : 1;           // 有效性_位置
    UINT8 validity_height : 1;                // 有效性_载机海拔高度
    UINT8 validity_GNSS_inertial_ADS_alt : 1; // 有效性_惯性卫星大气高度
    UINT8 validity_baoliu1 : 3;

    UINT8 cmd;      // 给惯导的指令，重对准
    UINT8 baoliu;   // 保留
    UINT8 checksum; // 校验字：（字节序号）2~105字节和校验，溢出不计
    UINT8 end;      // 消息尾 0xBB
} Mess_TO_PCS_DATA;

// 从PCS接收的数据协议
typedef struct Struct_PCS_Data {
    UINT16 sync_word; // 同步字:0xAA，0xBB

    // 时间1
    UINT32 time_hour : 8;   // 时
    UINT32 time_day : 8;    // 日
    UINT32 time_mounth : 8; // 月
    UINT32 time_year : 8;   // 年

    // 时间2
    UINT32 time_ms : 16; // 毫秒
    UINT32 time_s : 8;   // 秒
    UINT32 time_min : 8; // 分

    INT32 longitude;            // 经度LSB=π/2^31---1
    INT32 latitude;             // 纬度LSB=π/2^31---1
    INT32 altitude;             // 高度 有符号数(-500m~25000m)， LSB=0.001m---1
    INT32 true_heading;         // 真航向   有符号数(-π~+π)，LSB=π/2^31rad---1
    INT32 pitch;                // 俯仰角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    INT32 roll;                 // 横滚角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    INT16 heading_v;            // 航向角速度  有符号数 (-π~+π)rad/s，LSB=π/ (2^15)rad/s
    INT16 pitch_v;              // 俯仰角速度  有符号数 (-π~+π)rad/s，LSB =π/ (2^15)rad/s
    INT16 roll_v;               // 横滚角速度  有符号数 (-π~+π)rad/s，LSB =π/ (2^15)rads
    INT32 north_speed;          // 北向速度  有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    INT32 east_speed;           // 东向速度	 有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    INT32 ground_speed;         // 地向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    INT16 forward_acceleration; // 前向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，顺航向向前为正
    INT16 normal_acceleration;  // 法向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，飞机法向向上为正
    INT16 lateral_acceleration; // 侧向加速度   有符号数(-10~+10g)，LSB =10/ (2^15)g，顺航向向右为正

    // 状态字
    UINT32 status_wx_count : 8; // bit0-7:卫星数量
    UINT32 status_baoliu : 8;   // bit8-15:保留
    UINT32 status_spxh : 1;     // bit16:射频信号	0：正常	1：异常
    UINT32 status_jjsj : 1;     // bit17:加计数据	0：正常	1：异常
    UINT32 status_tlsj : 1;     // bit18:陀螺数据	0：正常	1：异常
    UINT32 status_wxdjyxx : 1;  // bit19:卫星定位有效性	0：正常	1：异常	判断数据可用：0
    UINT32 status_baoliu1 : 1;  // bit20:保留
    UINT32 status_gb3 : 1;      // bit21:杆臂3	0：收到	1：未收到
    UINT32 status_gb2 : 1;      // bit22:杆臂2	0：收到	1：未收到
    UINT32 status_gb1 : 1;      // bit23:杆臂1	0：收到	1：未收到
    UINT32 status_wx_type : 2;  // bit24-25:卫星类型	0：BD	1：GPS	2：BG
    UINT32 status_zgddata : 1;  // bit26:主惯导数据状态	0：主惯导位置速度有效	1：主惯导位置速度无效
    UINT32 status_gdgzms : 3;   // bit27-29:惯导工作模式	0：装订对准	1：地面静态对准	2：空中飞行对准	3：导航	4：自检中	判断数据可用：3
    UINT32 status_zjjg : 1;     // bit30:自检结果	0：正常	1：异常
    UINT32 status_sbzt : 1;     // bit31:设备状态0：正常	1：异常

    UINT8 frame_count; // 帧计数
    UINT8 baoliu[4];   // 预留
    UINT8 check;       // 校验
} Mess_From_PCS_DATA;

// 向PCS发送的升级帧
typedef struct Struct_PCS_Update {
    UINT8 head1; //'H' 0x48
    UINT8 head2; //'E' 0x45
    UINT8 head3; //'A' 0x41
    UINT8 head4; //'D' 0x44

    UINT8 cmd;       // 0x01：准备升级，惯导执行初始化工作
                     // 0x02：升级过程中，发送拆分的固件包内容
                     // 0x03：升级结束
                     // 0x10：肯定应答（备用）
    UINT8 file_type; // 标识所升级文件的类型：
                     // 0x02：core2的升级固件（预处理）
                     // 0x03：core3的升级固件（导航解算）

    UINT32 file_size;         // 文件大小
    UINT32 package_total_num; // 文件总包数
    UINT32 package_num;       // 当前传输包数

    UINT16 youxiao_size; // 当前包中的有效内容长度

    UINT8 data[512]; // 字符内容	操作类型为0x01时，内容为文件名称；操作类型为0x02时，拷贝内容为对应升级固件字符内容。

    UINT8 check_sum; // 校验和：5-536字节取和校验

    UINT8 end1; //'E' 0x45
    UINT8 end2; //'N' 0x4E
    UINT8 end3; //'D' 0x44

} MESS_To_PCS_Update;
//***********************惯导分系统ICD定义**********END****************************************

//*************6**********窗口温控系统ICD定义**************************************************
#define GCWK_CMD_None 0x00  // 空指令
#define GCWK_CMD_OPEN 0xAA  // 打开风机
#define GCWK_CMD_CLOSE 0x55 // 关闭风机

// 光窗温控指令-------4字节
typedef struct Struct_To_GCWK {
    UINT16 head; // 0x7E7E
    UINT8  cmd;  // 指令0xAA:打开风机	0x55:关风机

    UINT8 check_sum; // 校验和
} MESS_To_GCWK;

// 光窗温控回报-------8字节
typedef struct Struct_From_GCWK {
    UINT16 head; // 0x7E7E
    UINT8  cmd;  // 指令0xAA:打开风机	0x55:关风机

    UINT8 tem_ID; // 温度信息ID-1-10循环发送
    INT16 temp;   // 温度值，LSB=0.1℃

    UINT8 tem_error; // 温度传感器异常0：正常；1：异常

    UINT8 check_sum; // 校验和
} MESS_From_GCWK;
//***********************窗口温控系统ICD定义*******END*******************************************

//*************7**********记录仪分系统ICD定义**************************************************
#define JLY_CMD_None 0xFF  // 空指令
#define JLY_CMD_OPEN 0x01  // 开始存储
#define JLY_CMD_CLOSE 0x02 // 停止存储

// 向记录仪发
typedef struct Struct_To_JLY {
    UINT16 head; // 0xEB90
    UINT8  cmd;  // 指令

    UINT8 param_channel1 : 1; // 通道1
    UINT8 param_channel2 : 1; // 通道2
    UINT8 param_channel3 : 1; // 通道3
    UINT8 param_channel4 : 1; // 通道4
    UINT8 param_baoliu : 4;

    UINT8 baoliu[3];

    UINT8 check_sum; // 校验和
} MESS_To_JLY;

// 从记录仪收
typedef struct Struct_From_JLY {
    UINT16 head; // 0xEB90
    UINT8  cmd;  // 指令

    UINT8 param_channel1_link : 1; // 通道1链接状态
    UINT8 param_channel2_link : 1; // 通道2链接状态
    UINT8 param_channel3_link : 1; // 通道3链接状态
    UINT8 param_channel4_link : 1; // 通道4链接状态
    UINT8 param_channel1_save : 1; // 通道1存储状态
    UINT8 param_channel2_save : 1; // 通道2存储状态
    UINT8 param_channel3_save : 1; // 通道3存储状态
    UINT8 param_channel4_save : 1; // 通道4存储状态

    UINT8 channel1_space; // 通道1剩余空间百分比  %
    UINT8 channel2_space; // 通道2剩余空间百分比  %
    UINT8 channel3_space; // 通道3剩余空间百分比  %
    UINT8 channel4_space; // 通道4剩余空间百分比  %

    UINT8 baoliu[3];

    UINT8 check_sum; // 校验和

} MESS_From_JLY;

//***********************记录仪分系统ICD定义*******END*******************************************

//---------------------调光用ICD定义--------------------------------------------------------
#define TG_CMD_None 0x00             // 空指令
#define TG_CMD_Collect 0x76          // 收藏
#define TG_CMD_CellBIT 0xC2          // 单元自检
#define TG_CMD_KJselfFocus 0x8B      // 可见自准值检焦
#define TG_CMD_KJImgFocus 0x33       // 可见图像检焦
#define TG_CMD_HWselfFocus 0x4C      // 红外图像检焦
#define TG_CMD_Light 0x17            // 检光
#define TG_CMD_HWJZ 0x35             // 红外非均匀校正
#define TG_CMD_Wait 0xAF             // 待机
#define TG_CMD_GYCX 0xA0             // 广域成像
#define TG_CMD_QYCX 0xA4             // 区域成像
#define TG_CMD_QYJS 0xA6             // 区域监视
#define TG_CMD_PicLinkTestBegin 0x2B // 图像链路测试开始
#define TG_CMD_PicLinkTestEnd 0x2C   // 图像链路测试结束
#define TG_CMD_FlyFocus 0x6D         // 航空实景检焦
#define TG_CMD_StaticPhoto 0xAA      // 静态成像

//---------------------调光用ICD END----------------------------------------------------

//*************8**********球内数据ICD定义**************************************************
// 球内分系统结构体，包括可见探测器、红外探测器、球内温控
// 向可见探测器发送的报文————6字节
typedef struct Struct_To_TCQ_KJ {
    UINT8 KJSendHeader1; // 可见探测器发送帧头1	0xB1
    UINT8 KJSendHeader2; // 可见探测器发送帧头2	0x4C
    UINT8 KJCmd;         // 可见探测器命令字
    UINT8 KJSendDat1;    // 可见探测器数据字1
    UINT8 KJSendDat2;    // 可见探测器数据字2
    UINT8 CheckSum;      // 校验和
} MESS_To_TCQ_KJ;
//--------------可见探测器-------END--------------------------

// 向红外探测器发送的报文-----6字节
typedef struct Struct_To_TCQ_HW {
    UINT8 HWSendHeader1; // 红外探测器发送帧头1
    UINT8 HWSendHeader2; // 红外探测器发送帧头2
    UINT8 HWCmd;         // 红外探测器命令字
    UINT8 HWSendDat1;    // 红外探测器数据字1
    UINT8 HWSendDat2;    // 红外探测器数据字2
    UINT8 CheckSum;      // 校验和

} MESS_To_TCQ_HW;
//--------------红外探测器-------END--------------------------

//--------------球内温控---------------------------------
// 此处定义球内温控的指令、状态等宏定义
#define QNWK_CMD_None 0x00  // 空指令
#define QNWK_CMD_OPEN 0xAA  // 温控开
#define QNWK_CMD_CLOSE 0x55 // 温控关

// 向球内温控发送的报文-----8字节
typedef struct Struct_To_QNWK {
    UINT16 head;     // 0x7E7E
    UINT8  cmd;      // 指令
    UINT8  cmd_mode; // 手动/自动温控   0：自动 1：手动

    UINT8 baoliu[3]; // 保留
    UINT8 checksum;  // 校验和

} MESS_To_QNWK;
//--------------球内温控-------END--------------------------

// 向球内数据发————20字节
typedef struct Struct_To_QNSJ {
    MESS_To_TCQ_KJ mess_To_TCQ_KJ; // 给可见探测器 	6字节
    MESS_To_TCQ_HW mess_To_TCQ_HW; // 给红外探测器 	6字节
    MESS_To_QNWK   mess_To_QNWK;   // 给球内温控 		8字节

} MESS_To_QNSJ;

// 从球内数据收——————56字节
typedef struct Struct_From_QNSJ {
    UINT16 head; // 0x7E7E
    UINT8  baoliu1[6];
    UINT8  kjtcq_data[4]; // 可见探测器返回数据 	——调光用
    UINT8  hwtcq_data[4]; // 红外探测器返回数据 	——调光用
    UINT8  kj_cmd_back;   // 可见应答字 			——调光用
    UINT8  hw_cmd_back;   // 红外应答字 			——调光用
    UINT8  baoliu2[2];

    INT32 rtime_direction_frame_top_v; // 框架实时方位陀螺速度（LSB = 1.0/1100000°/s)--高精度
    INT32 rtime_pitch_frame_top_v;     // 框架实时俯仰陀螺速度（LSB = 1.0/1100000°/s)--高精度
    UINT8 rtime_pitch_frame[3];        // 框架实时俯仰角（LSB = 360/2^24°)----内框架编码器

    UINT8 qnwk_cmd;      // 指令
    UINT8 qnwk_cmd_mode; // 手动/自动温控   0：自动 1：手动
    UINT8 baoliu3[3];    // 保留(加热区控制)

    INT16 zjwdxx; // 主镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    INT16 cjwdxx; // 次镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦

    UINT8 tem_ID; // 温度信息ID-1-10循环发送
    INT16 temp;   // 温度值，LSB=0.1℃

    UINT8 error1; // 温控传感器故障字1:Bit0-bit7：代表8个区域传感器故障
    UINT8 error2; // 温控传感器故障字2:Bit0-bit5：代表6个区域传感器故障

    UINT8  baoliu4; // 版本号A
    UINT16 ylz;     // 压力值，来自温控
    UINT8  baoliu5; // 版本号B、C

    UINT8 year;       // 年
    UINT8 month;      // 月
    UINT8 day;        // 日
    UINT8 baoliu6[3]; // 保留
    UINT8 checksum;   // 校验和
} MESS_From_QNSJ;
//***********************球内数据ICD定义*******END*******************************************

//*************9**********主控与FPGA   ICD定义**************************************************
#define FPGA_START_PHOTO 0x01  // 拍照
#define FPGA_STOP_PHOTO 0x00   // 停拍
#define FPGA_GY_PHOTO 0x01     // 广域成像
#define FPGA_QY_PHOTO 0x02     // 区域成像
#define FPGA_QY_VIDEO 0x03     // 区域监视
#define FPGA_JT_PHOTO 0x04     // 静态成像
#define FPGA_JTJ_PHOTO 0x05    // 检调焦30Hz
#define FPGA_ZSXX_VALID 0x01   // 注释信息有效
#define FPGA_ZSXX_INVALID 0x00 // 注释信息无效

// 向FPGA发
typedef struct Struct_To_FPGA {
    UINT8 cmd;            // 指令：0x01:拍照,0x00停拍
    UINT8 irst_form_mode; // IRST成像模式:0不工作、1广域成像、2区域成像、3区域监视、4静态成像
    UINT8 frames_Num;     // 条带张数
    UINT8 zsxx_valid;     // 当前注释信息有效标识，1：有效，0：无效

    UINT32 time_speed;    // 速度信号时间LSB=0.1ms,赋值的时候*30000
    UINT32 time_location; // 位置信号时间LSB=0.1ms,赋值的时候*30000

    UINT32 time_kj; // 可见曝光时间LSB=0.1ms,赋值的时候*30000
    UINT32 time_hw; // 红外曝光时间LSB=0.1ms,赋值的时候*30000

} MESS_To_FPGA;

// 从FPGA收
// 从fpga接收的422通信故障
struct Struct_Fpga_422Err {
    // 0:正常；1：故障；

    UINT8 error_data_qn : 1;    // 球内数据内容故障
    UINT8 error_commu_qn : 1;   // 球内通信故障
    UINT8 error_data_kj : 1;    // 框架数据内容故障
    UINT8 error_commu_kj : 1;   // 框架通信故障
    UINT8 error_data_qnwk : 1;  // 球内温控数据内容故障
    UINT8 error_commu_qnwk : 1; // 球内温控控通信故障
    UINT8 error_data_gc : 1;    // 光窗温控数据内容故障
    UINT8 error_commu_gc : 1;   // 光窗温控通信故障

    UINT8 error_data_bettery : 1;  // 电源数据内容故障
    UINT8 error_commu_bettery : 1; // 电源通信故障
    UINT8 error_data_pos : 1;      // POS数据内容故障
    UINT8 error_commu_pos : 1;     // POS通信故障
    UINT8 error_data_tx : 1;       // 图像数据内容故障
    UINT8 error_commu_tx : 1;      // 图像通信故障
    UINT8 error_data_tj : 1;       // 调焦数据内容故障
    UINT8 error_commu_tj : 1;      // 调焦通信故障
};
typedef union Union_Fpga_422Err {
    UINT16                    all;
    struct Struct_Fpga_422Err fpag_422Err;
} FPGA_422ERR;

typedef struct Struct_From_FPGA {
    // 各种故障  Uint16
    FPGA_422ERR fpga_422ERR;
    UINT8       cmd;            // 指令：0x01:拍照,0x00停拍
    UINT8       irst_form_mode; // IRST成像模式:0不工作、1广域成像、2区域成像、3区域监视、4静态成像

} MESS_From_FPGA;
//***********************主控与FPGA   ICD定义*******END*******************************************

//****************2*******图像处理分系统ICD定义**************************************************
#define TX_CMD_EMPTY 0xFF            // 空指令
#define TX_CMD_TRACK 0x1B            // 跟踪
#define TX_CMD_STOP_TRACK 0x01       // 停止跟踪
#define TX_CMD_IMAGE_GY 0x06         // 广域成像，输入图像设置1   可见：5120*4096 15Hz    红外：1280*1024 15Hz
#define TX_CMD_IMAGE_VIEW 0x07       // 区域监视，输入图像设置2   可见：5120*4096 24Hz   红外：1280*1024 24Hz
#define TX_CMD_IMAGE_QY 0x08         // 区域成像，输入图像设置2   可见：5120*4096 15Hz   红外：1280*1024 15Hz
#define TX_CMD_SHOW_KJ_BBUP 0x37     // 可见电子变倍+
#define TX_CMD_SHOW_KJ_BBDOWN 0x38   // 可见电子变倍-
#define TX_CMD_SHOW_HW_BBUP 0x39     // 红外电子变倍+
#define TX_CMD_SHOW_HW_BBDOWN 0x3A   // 红外电子变倍-
#define TX_CMD_SHOW_MBSB_OPEN 0x44   // 目标识别开
#define TX_CMD_SHOW_MBSB_CLOSE 0x45  // 目标识别关
#define TX_CMD_SHOW_BZF 0x47         // 白字符
#define TX_CMD_SHOW_HZF 0x48         // 黑字符
#define TX_CMD_SHOW_ZFXY_PP 0x49     // 字符消隐,乒乓
#define TX_CMD_IMAGE_TRANS 0x53      // 传输图像/视频
#define TX_CMD_IMAGE_TRANS_STOP 0x54 // 停传图像/视频
#define TX_CMD_JZDWJD 0x23           // 校准定位精度（安装角修正）
#define TX_CMD_DJ 0x56               // 冻结
#define TX_CMD_SHOW_JJMS 0x4D        // 检焦模式使能
#define TX_CMD_SENSOR_SET 0x6A       // 传感器设置
#define TX_CMD_VIDEO_BAND_SET 0x6B   // 视频带宽设置

// #define TX_CMD_TRACK_HW       		0x1C        //红外跟踪
// #define TX_CMD_STOP_TRANS_KJ    	0x02        //可见不输出
// #define TX_CMD_START_TRANS_KJ   	0x03        //可见输出
// #define TX_CMD_STOP_TRANS_HW    	0x04        //红外不输出
// #define TX_CMD_START_TRANS_HW   	0x05        //红外输出
// #define TX_CMD_IMAGE_MODEL3     	0x08        //输入图像设置3   保留
// #define TX_CMD_SHOW_KJ_TXZQ_PP   	0x32   //可见图像增强,乒乓
// #define TX_CMD_SHOW_KJ_LDUP      	0x33       //可见亮度+
// #define TX_CMD_SHOW_KJ_LDDOWN    	0x34   //可见亮度-
// #define TX_CMD_SHOW_HW_TXZQ_PP   	0x3B   //红外图像增强,乒乓
// #define TX_CMD_SHOW_HW_LDUP      	0x3C   //红外亮度+
// #define TX_CMD_SHOW_HW_LDDOWN    	0x3D   //红外亮度-
// #define TX_CMD_SHOW_HW_DBDUP     	0x3F   //红外对比度+
// #define TX_CMD_SHOW_HW_DBDDOWN      0x40   //红外对比度-
// #define TX_CMD_SHOW_KJ_QW_PP        0x41   //可见去雾,乒乓
// #define TX_CMD_SHOW_DZDZQ_PP        0x42   //低照度增强,乒乓
// #define TX_CMD_SHOW_TXQZ_PP        	0x43   //图像去噪处理
// #define TX_CMD_SHOW_PRNU        	0x4C   //可见图像PRNU校正功能使能
// #define TX_CMD_SHOW_HWJX_PP         0x46   //红外极性,乒乓
// #define TX_CMD_SHOW_KJ_HZH_PP       0x4A   //可见画中画开/关,乒乓
// #define TX_CMD_SHOW_HW_HZH_PP       0x4B   //红外画中画开/关,乒乓
// #define TX_CMD_IMAGE_SAVE           0x51   //存储图像
// #define TX_CMD_IMAGE_SAVE_STOP      0x52   //停止存储图像
// #define TX_CMD_IMAGE_CLEAR          0x55   //清空图像

// 向图像处理发送的指令报文 12字节
typedef struct Struct_Mess_To_TXCL_CMD {
    UINT8 head1; // 帧头1   0xEB
    UINT8 head2; // 帧头2   0x90

    UINT8 cmd; // 命令字

    INT16 diff_pitch; // 俯仰偏差角 LSB 0.01,x方向脱靶量
    INT16 diff_roll;  // 俯仰偏差角 LSB 0.01，y方向脱靶量

    UINT8 mode_IR_SENSOR; // 图像传感器模式：1可见光；2红外；3可见+红外；4红外+可见（在视频模式下代表画中画）
    UINT8 Video_BAND;     // 视频带宽设置
    UINT8 baoliu[2];      // 保留

    UINT8 checkSum; // 校验字节
} Mess_To_TXCL_CMD;

// 从图像处理接收的报文  64字节
typedef struct Struct_Mess_From_TXCL {
    UINT8 head1; // 帧头1   0xEB
    UINT8 head2; // 帧头2   0x90

    UINT8 cmd; // 命令字

    // 工作状态1
    UINT8 state1_trackstate : 2; // Bit0-1        跟踪状态:0：未跟踪；    1：稳定跟踪；    2：一般跟踪；    3：即将丢失；
    UINT8 state1_trackvideo : 1; // Bit2          跟踪图像:0：可见    1：红外
    UINT8 state1_kjtxchs : 1;    // Bit3          可见图像传输状态0：未传输    1：正在传输——使用
    UINT8 state1_hwtxchs : 1;    // Bit4          红外图像传输状态0：未传输    1：正在传输——使用
    UINT8 state1_baoliu : 3;     // 保留
    //    UINT8           state1_kjtxzq:1 ;               //Bit3          可见图像增强    1：开启 0：关闭
    //    UINT8           state1_hwtxzq:1 ;               //Bit4          红外图像增强     1：开启 0：关闭
    //    UINT8           state1_kjtw:1 ;                 //Bit5          可见透雾       1：开启 0：关闭
    //    UINT8           state1_txcc:1;                  //Bit6          图像存储状态0：未存储    1：存储

    // 工作状态2
    //    UINT8           state2_kjdzdzq:1 ;               //Bit0          可见低照度增强  1：开启 0：关闭
    //    UINT8           state2_mbdw:1 ;                  //Bit1          目标定位               0:关闭 1：开启
    //    UINT8           state2_mbsb:1 ;                  //Bit2          目标识别               0:关闭 1：开启
    //    UINT8           state2_hwjx:1;                   //Bit3          红外极性:0:白热 1:黑热
    UINT8 state2_baoliu : 4; // 保留
    UINT8 state2_zfys : 1;   // Bit4          字符颜色:0：白字符 1：黑字符
    UINT8 state2_zfxy : 1;   // Bit5          字符消隐:0：显示 1：消隐
    UINT8 state2_kjhzh : 1;  // Bit6          可见画中画             0:关闭 1：开启
    UINT8 state2_hwhzh : 1;  // Bit7          红外画中画             0:关闭 1：开启

    // 工作状态3剩余存储容量
    UINT8 state3_txcckj : 2; /*Bit0-Bit1 剩余存储容量  0：存储空间未占用（余100%）;
                                                                                 1：存储空间充足（余10~99%）2：存储空间告警（余<10%）
                                                                                 3：存储空间已满*/
    UINT8 state3_kjsc : 1;   // Bit2 可见输出状态
    UINT8 state3_hwsc : 1;   // Bit3 红外输出状态   0：未输出；1：输出
    UINT8 state3_rsvd : 4;   // Bit4-7 保留

    INT32 target_longitude; // 中心点定位经度180/2147483647
    INT32 target_latitude;  // 中心点定位纬度90/2147483647
    INT16 target_altitude;  // 中心点定位高度
    UINT8 kj_dzbb;          // 可见电子变倍
    UINT8 hw_dzbb;          // 红外电子变倍

    UINT8 tg_valid; // 有效标识
    UINT8 tg_count; // 动目标数目

    // 名  称:动目标1框左上角横向像素坐标
    UINT16 tgt1_upleft_x;
    // 名  称:动目标1框左上角纵向像素坐标
    UINT16 tgt1_upleft_Y;
    // 名  称:动目标1框右下角横向像素坐标
    UINT16 tgt1_downright_x;
    // 名  称:动目标1框右下角纵向像素坐标
    UINT16 tgt1_downright_y;
    // 名  称:动目标2框左上角横向像素坐标
    UINT16 tgt2_upleft_x;
    // 名  称:动目标2框左上角纵向像素坐标
    UINT16 tgt2_upleft_Y;
    // 名  称:动目标2框右下角横向像素坐标
    UINT16 tgt2_downright_x;
    // 名  称:动目标2框右下角纵向像素坐标
    UINT16 tgt2_downright_y;
    // 名  称:动目标3框左上角横向像素坐标
    UINT16 tgt3_upleft_x;
    // 名  称:动目标3框左上角纵向像素坐标
    UINT16 tgt3_upleft_Y;
    // 名  称:动目标3框右下角横向像素坐标
    UINT16 tgt3_downright_x;
    // 名  称:动目标3框右下角纵向像素坐标
    UINT16 tgt3_downright_y;
    // 名  称:动目标4框左上角横向像素坐标
    UINT16 tgt4_upleft_x;
    // 名  称:动目标4框左上角纵向像素坐标
    UINT16 tgt4_upleft_Y;
    // 名  称:动目标4框右下角横向像素坐标
    UINT16 tgt4_downright_x;
    // 名  称:动目标4框右下角纵向像素坐标
    UINT16 tgt4_downright_y;
    // 名  称:动目标5框左上角横向像素坐标
    UINT16 tgt5_upleft_x;
    // 名  称:动目标5框左上角纵向像素坐标
    UINT16 tgt5_upleft_Y;
    // 名  称:动目标5框右下角横向像素坐标
    UINT16 tgt5_downright_x;
    // 名  称:动目标5框右下角纵向像素坐标
    UINT16 tgt5_downright_y;

    UINT8 baoiu2[2]; // 保留

    // 故障位
    UINT8 fault_bit0 : 1; // Bit0:图像处理模块内部电路，1：故障	0：正常
    UINT8 fault_bit1 : 1; // Bit1:图像处理模块存储单元，1：故障	0：正常
    UINT8 fault_bit2 : 1; // Bit2:图像处理模块输入可见图像信号，1：故障	0：正常——使用
    UINT8 fault_bit3 : 1; // Bit3:图像处理模块输入红外图像信号，1：故障	0：正常——使用
    UINT8 fault_bit4 : 1; // Bit4:图像处理模块存储单元满，1：故障	0：正常
    UINT8 fault_bit5 : 1; // Bit5:定位功能
    UINT8 fault_bit6 : 1; // Bit6:识别功能 0=正常 1：异常
    UINT8 fault_rsvd : 1; // Bit7 保留

    // 校验和
    UINT8 checkSum;

} Mess_From_TXCL;

// 向图像处理发送的注释信息报文
typedef struct Struct_Mess_To_TXCL_ZSXX {
    // 名  称:图像任务信息
    A818_IMAGE_COMMON_PARAS_TYPE_DEF to_Txcl_A818_Image_common_paras;
    SPARE32                          spare1[1]; // 保留字段
    // 名  称:图像参数_下传
    IMAGE_PARAS_TRANSIT_TYPE_DEF to_Txcl_image_paras_transit;
    // 名  称:飞机惯导信息
    AC_INS_INFO_TYPE_DEF to_Txcl_AC_ins_info;

    // 后面定义自己需要的注释信息内容(108字节)
    UINT16 fpga_info;   // fpga2字节
    UINT8  kj_info[44]; // 框架44字节
    UINT8  tj_info[20]; // 调焦20字节
    UINT8  tg_info[30]; // 调光30字节

    // 球内数据8字节
    INT16  zjwdxx; // 主镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    INT16  cjwdxx; // 次镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    UINT8  error1; // 温控传感器故障字1:Bit0-bit7：代表8个区域传感器故障
    UINT8  error2; // 温控传感器故障字2:Bit0-bit5：代表6个区域传感器故障
    UINT16 ylz;    // 压力值，来自温控

    UINT8 tx_info[4]; // 图像处理4字节

    // 主控需要保存的注释信息
    UINT32 distance;             // 照相距离
    INT32  toKJ_pitch_start;     // 框架俯仰指令   起始角（LSB=0.0001°）
    INT32  toKJ_pitch_end;       // 框架俯仰指令   结束角（LSB=0.0001°）
    INT32  toKJ_direction_start; // 框架方位指令   起始角（LSB=0.0001°）
    INT32  toKJ_direction_end;   // 框架方位指令   结束角（LSB=0.0001°）

    INT16 toKJ_pitch_speed;     // 框架俯仰扫描速度指令（LSB=0.01°/s）
    INT16 toKJ_direction_speed; // 框架方位扫描速度指令（LSB=0.01°/s）

    INT16 pitch_image_motion_velocity;     // 给定快反俯仰前向像移速度（LSB=0.001°/s)
    INT16 direction_image_motion_velocity; // 给定快反方位前向像移速度（LSB=0.001°/s)

    // 载荷惯导时间
    UINT8  pos_time_year;   // 年
    UINT8  pos_time_mounth; // 月
    UINT8  pos_time_day;    // 日
    UINT8  pos_time_hour;   // 时
    UINT8  pos_time_min;    // 分
    UINT8  pos_time_s;      // 秒
    UINT16 pos_time_ms;     // 毫秒

} Mess_To_TXCL_ZSXX;
//***********************图像处理分系统ICD定义******END********************************************

#pragma pack()

// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_FPGA_MESS_H_ */
