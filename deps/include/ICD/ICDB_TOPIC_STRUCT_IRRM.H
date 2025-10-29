/**
 * @Author: Chongyang Liu
 * @Date:   2025-10-14 11:18:22
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-10-25 22:02:23
 */
//////////////////////////版本信息/////////////////////////
// 软件版本：ICDB3.32
// 数据版本：SE_A1.1.0版
// CPU类型：X86

#ifndef ICDB_TOPIC_STRUCT_IRRM_H
#define ICDB_TOPIC_STRUCT_IRRM_H

///////////////////////////////////基本结构////////////////////////////////////
#pragma pack(1)
typedef void* VIDEO;
typedef void* AUDIO;
typedef void* IMAGE;
typedef void* STREAM;
typedef float float1750;
typedef unsigned char BCD_8;
typedef unsigned short int BCD_16;
typedef unsigned int BCD_32;
typedef unsigned char BOOL_8;
typedef unsigned int BOOL_32;
typedef char char_8;
typedef unsigned short int char_16;
typedef unsigned int char_32;
typedef unsigned int SPARE32;
typedef unsigned char SPARE8;
typedef signed char INT8, *PINT8;
typedef signed short INT16, *PINT16;
typedef signed int INT32, *PINT32;
typedef signed long long INT64, *PINT64;
typedef unsigned char UINT8, *PUINT8;
typedef unsigned short UINT16, *PUINT16;
typedef unsigned int UINT32, *PUINT32;
typedef unsigned long long UINT64, *PUINT64;

////////////////////////////////////////////分时信号数据区非信号组类型信号结构定义///////////////////////////////////////////

// 信号标 识 符: VMS1394_ATC_AC_code
// 信号名    称: VMS1394_航管_A/C码
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: 航管应答A/C模式码，4位数字组成
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 VMS1394_ATC_AC_code;
} VMS1394_ATC_AC_CODE_TSTYPE_DEF;

// 信号标 识 符: VMS1394_YK_ATC_crisis_code
// 信号名    称: VMS1394_遥控_航管_危急码
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明: W0：正常情况，对应的A模式识别码(飞机批号)为当前A模式识别码；
//         W1：劫机，对应的A模式识别码为7500；
//         W2：无线电通信故障，对应的A模式识别码为7600；
//         W3：机械故障，对应的A模式识别码为7700。
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 VMS1394_YK_ATC_crisis_code;
} VMS1394_YK_ATC_CRISIS_CODE_TSTYPE_DEF;

// 信号标 识 符: VMS1394_ATC_S_code
// 信号名    称: VMS1394_航管_地址码
// 信号长    度: 32
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: bit8~bit31，共24bit
//         数据范围[000000,FFFFFF]
typedef struct
{
    UINT32 VMS1394_ATC_S_code;
} VMS1394_ATC_S_CODE_TSTYPE_DEF;

// 信号标 识 符: sat_antenna_work_mode_GCS
// 信号名    称: 遥控卫导天线工作模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 sat_antenna_work_mode_GCS;
} SAT_ANTENNA_WORK_MODE_GCS_TSTYPE_DEF;

// 信号标 识 符: IFFI_batch_mode
// 信号名    称: 敌我识别_编批询问模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IFFI_batch_mode;
} IFFI_BATCH_MODE_TSTYPE_DEF;

// 信号标 识 符: IFFR_batch_mode
// 信号名    称: 敌我识别_编批应答模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IFFR_batch_mode;
} IFFR_BATCH_MODE_TSTYPE_DEF;

// 信号标 识 符: IFFR_special_mode
// 信号名    称: 敌我识别_特殊应答模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IFFR_special_mode;
} IFFR_SPECIAL_MODE_TSTYPE_DEF;

// 信号标 识 符: IFFIdCode
// 信号名    称: 识别码
// 信号长    度: 32
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    UINT32 IFFIdCode;
} IFFIDCODE_TSTYPE_DEF;

// 信号标 识 符: BDS_address
// 信号名    称: 北斗短报文_接收地址
// 信号长    度: 32
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: 有效地址[1,16777215]
//         0表示无效地址，
typedef struct
{
    UINT32 BDS_address;
} BDS_ADDRESS_TSTYPE_DEF;

// 信号标 识 符: pilot_no
// 信号名    称: 飞行员代码
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 pilot_no;
} PILOT_NO_TSTYPE_DEF;

// 信号标 识 符: select_flag
// 信号名    称: 是否选择
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: BOOL
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    BOOL_8 select_flag;
} SELECT_FLAG_TSTYPE_DEF;

// 信号标 识 符: net_id
// 信号名    称: 网络规划
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 net_id;
} NET_ID_TSTYPE_DEF;

// 信号标 识 符: plane_id
// 信号名    称: 网络成员身份
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 plane_id;
} PLANE_ID_TSTYPE_DEF;

// 信号标 识 符: master_control
// 信号名    称: 时间基准标识
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: BOOL
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    BOOL_8 master_control;
} MASTER_CONTROL_TSTYPE_DEF;

// 信号标 识 符: transmit_antenna
// 信号名    称: 发射天线
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 transmit_antenna;
} TRANSMIT_ANTENNA_TSTYPE_DEF;

// 信号标 识 符: local_train
// 信号名    称: 本场训练
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: BOOL
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    BOOL_8 local_train;
} LOCAL_TRAIN_TSTYPE_DEF;

// 信号标 识 符: hop_database_no
// 信号名    称: 跳频库号
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: 训练模式：[0,92]
//         正常模式：[1,12]
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 hop_database_no;
} HOP_DATABASE_NO_TSTYPE_DEF;

// 信号标 识 符: hop_serial_no
// 信号名    称: 跳频序列号
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: [1,14]
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 hop_serial_no;
} HOP_SERIAL_NO_TSTYPE_DEF;

// 信号标 识 符: urgent_encrypt_req
// 信号名    称: 应急加密请求
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 urgent_encrypt_req;
} URGENT_ENCRYPT_REQ_TSTYPE_DEF;

// 信号标 识 符: FREQ_SELECT
// 信号名    称: 频率规划
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 FREQ_SELECT;
} FREQ_SELECT_TSTYPE_DEF;

// 信号标 识 符: J_CHANNEL_no
// 信号名    称: J_波道号
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明: 1-255
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 J_CHANNEL_no;
} J_CHANNEL_NO_TSTYPE_DEF;

// 信号标 识 符: JMODE
// 信号名    称: J_工作模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 JMODE;
} JMODE_TSTYPE_DEF;

// 信号标 识 符: fused_tgt_ID_of_ownship
// 信号名    称: 本机的融合目标编号
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 fused_tgt_ID_of_ownship;
} FUSED_TGT_ID_OF_OWNSHIP_TSTYPE_DEF;

// 信号标 识 符: target_class
// 信号名    称: 目标类型
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明: 注：ALL 普查，仅图像情报使用
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 target_class;
} TARGET_CLASS_TSTYPE_DEF;

// 信号标 识 符: IMG_Section_Compression_Level
// 信号名    称: 图像切片压缩档位设置
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明: 自动：机上根据图像目标的重要度自动设置压缩比；
//         手动压缩档位：从1-4，对应的图像切片质量逐渐降低。相同档位针对不同类型的切片压缩比不同
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IMG_Section_Compression_Level;
} IMG_SECTION_COMPRESSION_LEVEL_TSTYPE_DEF;

// 信号标 识 符: irst_form_mode
// 信号名    称: IRST成像模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 irst_form_mode;
} IRST_FORM_MODE_TSTYPE_DEF;

// 信号标 识 符: IR_SENSOR
// 信号名    称: 光电传感器状态
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IR_SENSOR;
} IR_SENSOR_TSTYPE_DEF;

// 信号标 识 符: environmnet_type
// 信号名    称: 环境类型
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 environmnet_type;
} ENVIRONMNET_TYPE_TSTYPE_DEF;

// 信号标 识 符: rdr_freq_type
// 信号名    称: 雷达频率类型
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 rdr_freq_type;
} RDR_FREQ_TYPE_TSTYPE_DEF;

// 信号标 识 符: rdr_freq_sel
// 信号名    称: 雷达工作频率选择
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 rdr_freq_sel;
} RDR_FREQ_SEL_TSTYPE_DEF;

// 信号标 识 符: rdr_gain_mode
// 信号名    称: 雷达增益模式
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 rdr_gain_mode;
} RDR_GAIN_MODE_TSTYPE_DEF;

// 信号标 识 符: rdr_env_height
// 信号名    称: 雷达目标区高度
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    INT16 rdr_env_height;
} RDR_ENV_HEIGHT_TSTYPE_DEF;

// 信号标 识 符: spotsar_res_reSet
// 信号名    称: 聚束SAR预设分辨率
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 spotsar_res_reSet;
} SPOTSAR_RES_RESET_TSTYPE_DEF;

// 信号标 识 符: rdr_LPI_strategy
// 信号名    称: 雷达LPI策略
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 rdr_LPI_strategy;
} RDR_LPI_STRATEGY_TSTYPE_DEF;

// 信号标 识 符: EM_level
// 信号名    称: 辐射等级
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明: 辐射级别控制参数。等级1配置为全静默等级，等级5配置为无限制辐射等级，中间级别可根据任务配置。
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 EM_level;
} EM_LEVEL_TSTYPE_DEF;

// 信号标 识 符: CRSM_CMD_Work_band
// 信号名    称: 通侦侦察频段控制
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 CRSM_CMD_Work_band;
} CRSM_CMD_WORK_BAND_TSTYPE_DEF;

// 信号标 识 符: CRSM_CMD_dwell_time
// 信号名    称: 侦察驻留时间控制
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 CRSM_CMD_dwell_time;
} CRSM_CMD_DWELL_TIME_TSTYPE_DEF;

// 信号标 识 符: CRSM_CMD_delete_datum_No
// 信号名    称: 删除基准点编号控制
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 CRSM_CMD_delete_datum_No;
} CRSM_CMD_DELETE_DATUM_NO_TSTYPE_DEF;

// 信号标 识 符: CRSM_Monitor_Tgt_No
// 信号名    称: 监听音频目标批号
// 信号长    度: 16
// 信号数组长度: 1
// 信号类    型: INT
// 信号说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段
    UINT16 CRSM_Monitor_Tgt_No;
} CRSM_MONITOR_TGT_NO_TSTYPE_DEF;

// 信号标 识 符: IRST_Video_BAND
// 信号名    称: IRST_区域监视视频带宽
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 IRST_Video_BAND;
} IRST_VIDEO_BAND_TSTYPE_DEF;

// 信号标 识 符: network_plan_select_seq
// 信号名    称: 网络规划选用序号
// 信号长    度: 8
// 信号数组长度: 1
// 信号类    型: ENUM
// 信号说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段
    UINT8 network_plan_select_seq;
} NETWORK_PLAN_SELECT_SEQ_TSTYPE_DEF;

////////////////////////////////////////////信号组结构定义///////////////////////////////////////////

// 信 号 组 标 识 符: date_calendartime
// 信 号 组 名    称: 时间_日历日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} DATE_CALENDARTIME_TYPE_DEF;

// 信 号 组 标 识 符: Time_Load
// 信 号 组 名    称: 加载时间
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 加载软件、数据的日历时间，
//                    格式为：XXXX年XX月XX日  XX时XX分XX秒
typedef struct
{
    // 标识符:date_calendartime
    // 名  称:时间_日历日期
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATE_CALENDARTIME_TYPE_DEF date_calendartime;

    // 标识符:time_calendartime
    // 名  称:时间_日历时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT64 time_calendartime;

} TIME_LOAD_TYPE_DEF;

// 信 号 组 标 识 符: msg_publisher_ID
// 信 号 组 名    称: 消息发布者ID
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

} MSG_PUBLISHER_ID_TYPE_DEF;

// 信 号 组 标 识 符: msg_publish_time
// 信 号 组 名    称: 消息发布时间
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
typedef struct
{
    // 标识符:time_sys_RTC
    // 名  称:时间_系统RTC
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT64 time_sys_RTC;

} MSG_PUBLISH_TIME_TYPE_DEF;

// 信 号 组 标 识 符: flight_status
// 信 号 组 名    称: IRST载机姿态信息
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:irst_fly_pitch
    // 名  称:IRST载机俯仰姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:0
    // 起始位:16
    INT16 irst_fly_pitch;

    // 标识符:irst_fly_course
    // 名  称:IRST载机航向姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT16 irst_fly_course;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:irst_fly_roll
    // 名  称:IRST载机横滚姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    INT16 irst_fly_roll;

} FLIGHT_STATUS_TYPE_DEF;

// 信 号 组 标 识 符: IR_IMU_data
// 信 号 组 名    称: 光电IMU数据
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:irst_INS_valid
    // 名  称:IRST载机姿态有效标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 irst_INS_valid : 8;

    // 标识符:A818_INS_NOW
    // 名  称:当前使用惯导
    // 说  明:飞机惯导
    //        03H-载荷惯导
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 A818_INS_NOW : 8;

    // 标识符:flight_status
    // 名  称:IRST载机姿态信息
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    FLIGHT_STATUS_TYPE_DEF flight_status;

} IR_IMU_DATA_TYPE_DEF;

// 信 号 组 标 识 符: sel_true_course
// 信 号 组 名    称: 选择真航线
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)
//                    选择航线相对于真北的夹角，顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SEL_TRUE_COURSE_TYPE_DEF;

// 信 号 组 标 识 符: sel_mag_course
// 信 号 组 名    称: 选择磁航线
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)
//                    选择磁航线相对于磁北顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SEL_MAG_COURSE_TYPE_DEF;

// 信 号 组 标 识 符: route_point_name
// 信 号 组 名    称: 航线点名称
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:wayppoint_name
    // 名  称:航路点名称
    // 说  明:航路点的中文名称，最长5个汉字
    // 单  位:
    // 起始字:0
    // 起始位:0
    char_8 wayppoint_name[12];

} ROUTE_POINT_NAME_TYPE_DEF;

// 信 号 组 标 识 符: fast_climb_state
// 信 号 组 名    称: 最速爬升状态
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_fast_climb_alt
    // 名  称:有效性_最速爬升高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 validity_fast_climb_alt : 8;

    // 标识符:validity_fast_climb_mach
    // 名  称:有效性_最速爬升马赫
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 validity_fast_climb_mach : 8;

    // 标识符:fast_climb_strategy
    // 名  称:最速爬升策略
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 fast_climb_strategy : 8;

    // 标识符:fast_climb_mode
    // 名  称:最速爬升模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 fast_climb_mode : 8;

    // 标识符:fast_climb_alt
    // 名  称:最速爬升高度
    // 说  明:[0,15000]米
    // 单  位:m
    // LSB  :1
    // 起始字:1
    // 起始位:16
    INT16 fast_climb_alt;

    // 标识符:fast_climb_mach
    // 名  称:最速爬升马赫
    // 说  明:[0,2.5]
    // 单  位:Mach
    // LSB  :0.01
    // 起始字:1
    // 起始位:0
    UINT16 fast_climb_mach;

} FAST_CLIMB_STATE_TYPE_DEF;

// 信 号 组 标 识 符: RWY_sel_mag_course
// 信 号 组 名    称: 进场选择磁航线
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360]度
//                    表示进入该机场点所在机场设定的选择磁航线。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} RWY_SEL_MAG_COURSE_TYPE_DEF;

// 信 号 组 标 识 符: bingo_tgt_set_fuel
// 信 号 组 名    称: bingo目标预置燃油
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_mass
    // 名  称:_质量
    // 说  明:用于表示质量重量等信号值，带符号位是为了计算过程中可能会产生负值。
    //        表示精度为0.001kg，表示范围约+/-1000吨
    // 单  位:kg
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _mass;

} BINGO_TGT_SET_FUEL_TYPE_DEF;

// 信 号 组 标 识 符: bingo_tgt_para
// 信 号 组 名    称: bingo目标参数
// 信 号 组 字    数: 8
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:bingo_alt
    // 名  称:bingo高度
    // 说  明:【0,15000】米
    // 单  位:m
    // LSB  :1
    // 起始字:0
    // 起始位:16
    INT32 bingo_alt : 16;

    // 标识符:bingo_envlope_set_type
    // 名  称:bingo剖面设置方式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 bingo_envlope_set_type : 8;

    // 标识符:fly_plan
    // 名  称:飞行计划号
    // 说  明:飞行计划，包括A~K（I除外）计划、标记点、波塞点、标定点、初始位置、最近机场、机场
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 fly_plan : 8;

    // 标识符:airport_num
    // 名  称:机场号
    // 说  明:机场号表示范围为0~999
    //        当前航线点类型或当前航路点类型不为机场时，则机场号=0；
    //        当前航线点类型或当前航路点类型为机场时，则根据机场号赋相应值，范围为1~999
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 airport_num;

    // 标识符:sp_number
    // 名  称:操纵点编号
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 sp_number;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:reverse_airport_num
    // 名  称:反向机场编号
    // 说  明:在信号组"航线点（route_point）"中表示：该机场点对应的反向着陆机场在本计划中的航线点编号。取值范围0~99，0表示没有对应的反向着陆机场。
    //        在信号组"航路点（waypoint）"中表示：该机场点对应的反向着陆机场在航路点库中的航路点编号。取值范围0~999，0表示没有对应的反向着陆机场。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT16 reverse_airport_num;

    // 标识符:RWY_sel_mag_course
    // 名  称:进场选择磁航线
    // 说  明:[0,360]度
    //        表示进入该机场点所在机场设定的选择磁航线。
    // 单  位:
    // 起始字:3
    // 起始位:0
    RWY_SEL_MAG_COURSE_TYPE_DEF RWY_sel_mag_course;

    // 标识符:route_point_name
    // 名  称:航线点名称
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    ROUTE_POINT_NAME_TYPE_DEF route_point_name;

    // 标识符:bingo_tgt_set_fuel
    // 名  称:bingo目标预置燃油
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    BINGO_TGT_SET_FUEL_TYPE_DEF bingo_tgt_set_fuel;

} BINGO_TGT_PARA_TYPE_DEF;

// 信 号 组 标 识 符: IR_pixel_elevation
// 信 号 组 名    称: IR点迹俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} IR_PIXEL_ELEVATION_TYPE_DEF;

// 信 号 组 标 识 符: IR_pixel_azimuth
// 信 号 组 名    称: IR点迹方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} IR_PIXEL_AZIMUTH_TYPE_DEF;

// 信 号 组 标 识 符: ir_aa_search
// 信 号 组 名    称: IR空空点迹参数
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 50
// 信 号 组 说    明:
typedef struct
{
    // 标识符:dot_confidence
    // 名  称:点迹置信度
    // 说  明:
    // 单  位:%
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 dot_confidence;

    // 标识符:dot_id
    // 名  称:点迹编号
    // 说  明:点迹编号。为了与目标编号取值不重合，光了上报点迹编号从1001开始编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT16 dot_id;

    // 标识符:IR_search_validity
    // 名  称:IR点迹有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 IR_search_validity;

    // 标识符:IR_pixel_azimuth
    // 名  称:IR点迹方位
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    IR_PIXEL_AZIMUTH_TYPE_DEF IR_pixel_azimuth;

    // 标识符:IR_pixel_elevation
    // 名  称:IR点迹俯仰
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    IR_PIXEL_ELEVATION_TYPE_DEF IR_pixel_elevation;

} IR_AA_SEARCH_TYPE_DEF;

// 信 号 组 标 识 符: MD5_current
// 信 号 组 名    称: MD5校验码_机内
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:MD5_a
    // 名  称:MD5_a
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 MD5_a;

    // 标识符:MD5_b
    // 名  称:MD5_b
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 MD5_b;

    // 标识符:MD5_c
    // 名  称:MD5_c
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 MD5_c;

    // 标识符:MD5_d
    // 名  称:MD5_d
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 MD5_d;

} MD5_CURRENT_TYPE_DEF;

// 信 号 组 标 识 符: DataBaseCfgInfo
// 信 号 组 名    称: 数据库配置信息
// 信 号 组 字    数: 18
// 信 号 组 数组长度: 5
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:is_online_loading
    // 名  称:在线统一加载标识
    // 说  明:当加载类型为软件加载时，该信号有意义；
    //        表示某个子系统该配置项当前是否可执行统一加载标志，
    //        子系统启动后，由其主控功能单元（RDRM、CNIM、EWSM、DASM等）统一上报给SYMD。
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 is_online_loading : 8;

    // 标识符:loading_type
    // 名  称:加载类型
    // 说  明:描述文件/数据在的场景类型：
    //        1=在任务系统正常模式下进行的战术任务数据加载；
    //        2=在任务系统维护模式下进行的维护配置数据加载；
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 loading_type : 8;

    // 标识符:array_element_valid
    // 名  称:数组元素有效性
    // 说  明:如果信号组信号为一个数组，则应包含该信号，表征该数组元素是否有效，当信息不需占用全部的数组元素时，未占用的元素该信号置无效。
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 array_element_valid : 8;

    // 标识符:PBS_Code
    // 名  称:PBS编码
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    char_8 PBS_Code[8];

    // 标识符:load_terminal_ID
    // 名  称:加载终端ID
    // 说  明:功能单元ID
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 load_terminal_ID;

    // 标识符:file_volume_byte
    // 名  称:文件体积
    // 说  明:描述文件体积大小，单位Byte。最大可表示不超过约4GB的文件。
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 file_volume_byte;

    // 标识符:Time_Load
    // 名  称:加载时间
    // 说  明:加载软件、数据的日历时间，
    //        格式为：XXXX年XX月XX日  XX时XX分XX秒
    // 单  位:
    // 起始字:5
    // 起始位:0
    TIME_LOAD_TYPE_DEF Time_Load;

    // 标识符:MD5_current
    // 名  称:MD5校验码_机内
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    MD5_CURRENT_TYPE_DEF MD5_current;

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //        软件版本号包括：
    //            1-2：机型识别码;
    //          3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //             11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //             12：字母“V”
    //        13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //        19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:12
    // 起始位:0
    char_8 ver_number[24];

} DATABASECFGINFO_TYPE_DEF;

// 信 号 组 标 识 符: data_block_trans_mark
// 信 号 组 名    称: 数据包传输标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_block_serial_number
    // 名  称:数据包_当前包序号
    // 说  明:从1开始编号
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 data_block_serial_number;

    // 标识符:data_block_total_count
    // 名  称:数据包_总包数
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 data_block_total_count;

} DATA_BLOCK_TRANS_MARK_TYPE_DEF;

// 信 号 组 标 识 符: satellite_nav_data_validity
// 信 号 组 名    称: 卫星导航数据_有效性
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1;  // 保留字段

    // 标识符:validity_baro_GNSS_alt
    // 名  称:有效性_卫星参考高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_baro_GNSS_alt;

    // 标识符:validity_GNSS_alt
    // 名  称:有效性_卫星高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_GNSS_alt;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_position;

    SPARE8 spare2;  // 保留字段

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_vel_north;

    SPARE8 spare3;  // 保留字段

    // 标识符:validity_CNI_GNSS_time
    // 名  称:有效性_卫星时间
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_CNI_GNSS_time;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_ground_speed;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_ground_track_angle;

} SATELLITE_NAV_DATA_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: date_gnss_calendartime
// 信 号 组 名    称: 卫星时间_日历日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: UTC0
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} DATE_GNSS_CALENDARTIME_TYPE_DEF;

// 信 号 组 标 识 符: data_generated_time
// 信 号 组 名    称: 数据生成时间
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
typedef struct
{
    // 标识符:time_missiontime
    // 名  称:时间_任务时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT64 time_missiontime;

} DATA_GENERATED_TIME_TYPE_DEF;

// 信 号 组 标 识 符: ac_gnss_position_data
// 信 号 组 名    称: 载机卫星位置数据
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    (-180,180]deg
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _longitude;

} AC_GNSS_POSITION_DATA_TYPE_DEF;

// 信 号 组 标 识 符: Vel_West
// 信 号 组 名    称: 速度_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_WEST_TYPE_DEF;

// 信 号 组 标 识 符: Vel_Up
// 信 号 组 名    称: 速度_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_UP_TYPE_DEF;

// 信 号 组 标 识 符: Vel_North
// 信 号 组 名    称: 速度_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: ac_gnss_plat_vel
// 信 号 组 名    称: 载机卫星平台系速度
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m;
//                    [-1000,1000]m;
//                    [-1000,1000]m;
typedef struct
{
    // 标识符:Vel_North
    // 名  称:速度_北向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VEL_NORTH_TYPE_DEF Vel_North;

    // 标识符:Vel_West
    // 名  称:速度_西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VEL_WEST_TYPE_DEF Vel_West;

    // 标识符:Vel_Up
    // 名  称:速度_天向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    VEL_UP_TYPE_DEF Vel_Up;

} AC_GNSS_PLAT_VEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_GNSS_ground_track_angle
// 信 号 组 名    称: 载机卫星航迹角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)deg
//                    相对于真北顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_GNSS_GROUND_TRACK_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: ac_GNSS_ground_speed
// 信 号 组 名    称: 载机卫星地速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_GNSS_GROUND_SPEED_TYPE_DEF;

// 信 号 组 标 识 符: ac_GNSS_alt
// 信 号 组 名    称: 载机卫星高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-2500,30000]m
//                    卫星接收机输出的高度（绝对的，84座标）
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_GNSS_ALT_TYPE_DEF;

// 信 号 组 标 识 符: ac_baro_GNSS_alt
// 信 号 组 名    称: 载机卫星参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-7500,30000]m
//                    卫星高度－场高
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_BARO_GNSS_ALT_TYPE_DEF;

// 信 号 组 标 识 符: satellite_nav_data
// 信 号 组 名    称: 卫星导航数据
// 信 号 组 字    数: 18
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:sat_anti_cheat_identify
    // 名  称:卫星防欺骗识别状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    UINT32 sat_anti_cheat_identify : 8;

    // 标识符:HDOP
    // 名  称:水平精度因子
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.01
    // 起始字:2
    // 起始位:8
    UINT32 HDOP : 16;

    // 标识符:num_of_satellite
    // 名  称:定位卫星数目
    // 说  明:从卫星报文的GGA语句中解析得到
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 num_of_satellite : 8;

    // 标识符:satellite_nav_data_validity
    // 名  称:卫星导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SATELLITE_NAV_DATA_VALIDITY_TYPE_DEF satellite_nav_data_validity;

    // 标识符:ac_gnss_position_data
    // 名  称:载机卫星位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:6
    // 起始位:0
    AC_GNSS_POSITION_DATA_TYPE_DEF ac_gnss_position_data;

    // 标识符:ac_GNSS_alt
    // 名  称:载机卫星高度
    // 说  明:[-2500,30000]m
    //        卫星接收机输出的高度（绝对的，84座标）
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_GNSS_ALT_TYPE_DEF ac_GNSS_alt;

    // 标识符:ac_baro_GNSS_alt
    // 名  称:载机卫星参考高度
    // 说  明:[-7500,30000]m
    //        卫星高度－场高
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_BARO_GNSS_ALT_TYPE_DEF ac_baro_GNSS_alt;

    // 标识符:ac_gnss_plat_vel
    // 名  称:载机卫星平台系速度
    // 说  明:[-1000,1000]m;
    //        [-1000,1000]m;
    //        [-1000,1000]m;
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_GNSS_PLAT_VEL_TYPE_DEF ac_gnss_plat_vel;

    // 标识符:ac_GNSS_ground_track_angle
    // 名  称:载机卫星航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_GNSS_GROUND_TRACK_ANGLE_TYPE_DEF ac_GNSS_ground_track_angle;

    // 标识符:ac_GNSS_ground_speed
    // 名  称:载机卫星地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_GNSS_GROUND_SPEED_TYPE_DEF ac_GNSS_ground_speed;

    // 标识符:date_gnss_calendartime
    // 名  称:卫星时间_日历日期
    // 说  明:UTC0
    // 单  位:
    // 起始字:15
    // 起始位:0
    DATE_GNSS_CALENDARTIME_TYPE_DEF date_gnss_calendartime;

    // 标识符:time_gnss_calendartime
    // 名  称:卫星时间_日历时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:16
    // 起始位:0
    UINT64 time_gnss_calendartime;

} SATELLITE_NAV_DATA_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_zz
// 信 号 组 名    称: 系数zz
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_ZZ_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_zy
// 信 号 组 名    称: 系数zy
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_ZY_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_zx
// 信 号 组 名    称: 系数zx
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_ZX_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_yz
// 信 号 组 名    称: 系数yz
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_YZ_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_yy
// 信 号 组 名    称: 系数yy
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_YY_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_yx
// 信 号 组 名    称: 系数yx
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_YX_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_xz
// 信 号 组 名    称: 系数xz
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_XZ_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_xy
// 信 号 组 名    称: 系数xy
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_XY_TYPE_DEF;

// 信 号 组 标 识 符: coefficent_xx
// 信 号 组 名    称: 系数xx
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_unitary_number
    // 名  称:_归一化数值
    // 说  明:[-1,1];
    //        归一化数值。
    // 单  位:
    // LSB  :1/1073741824
    // 起始字:0
    // 起始位:0
    INT32 _unitary_number;

} COEFFICENT_XX_TYPE_DEF;

// 信 号 组 标 识 符: plat_to_body_matrix
// 信 号 组 名    称: 平台系到机体转换矩阵
// 信 号 组 字    数: 9
// 信 号 组 数组长度: 1
// 信 号 组 说    明: _系数xx =  COS(φ) * COS(θ).
//                    _系数xy = -SIN(φ) * COS(θ).
//                    _系数xz = SIN(θ)
//                    _系数yx = COS(φ) * SIN(θ) * SIN(ξ) - SIN(φ) * COS(ξ)
//                    _系数yy = -COS(φ) * COS(ξ) - SIN(φ) * SIN(θ) * SIN(ξ)
//                    _系数yz = -COS(θ) * SIN(ξ)
//                    _系数zx = SIN(φ) * SIN(ξ) + COS(φ) * SIN(θ) * COS(ξ)
//                    _系数zy = COS(φ) * SIN(ξ) - SIN(φ) * SIN(θ) * COS(ξ)
//                    _系数zz = -COS(θ) * COS(ξ)
//                    φ=AC_Ture_Heading
//                    θ=AC_Pitch
//                    ξ=AC_Roll
typedef struct
{
    // 标识符:coefficent_xx
    // 名  称:系数xx
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    COEFFICENT_XX_TYPE_DEF coefficent_xx;

    // 标识符:coefficent_xy
    // 名  称:系数xy
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    COEFFICENT_XY_TYPE_DEF coefficent_xy;

    // 标识符:coefficent_xz
    // 名  称:系数xz
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    COEFFICENT_XZ_TYPE_DEF coefficent_xz;

    // 标识符:coefficent_yx
    // 名  称:系数yx
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    COEFFICENT_YX_TYPE_DEF coefficent_yx;

    // 标识符:coefficent_yy
    // 名  称:系数yy
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    COEFFICENT_YY_TYPE_DEF coefficent_yy;

    // 标识符:coefficent_yz
    // 名  称:系数yz
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    COEFFICENT_YZ_TYPE_DEF coefficent_yz;

    // 标识符:coefficent_zx
    // 名  称:系数zx
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    COEFFICENT_ZX_TYPE_DEF coefficent_zx;

    // 标识符:coefficent_zy
    // 名  称:系数zy
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    COEFFICENT_ZY_TYPE_DEF coefficent_zy;

    // 标识符:coefficent_zz
    // 名  称:系数zz
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    COEFFICENT_ZZ_TYPE_DEF coefficent_zz;

} PLAT_TO_BODY_MATRIX_TYPE_DEF;

// 信 号 组 标 识 符: INS_pure_inertial_nav_data_A_validity
// 信 号 组 名    称: INS纯惯导航数据A_有效性
// 信 号 组 字    数: 8
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_pitch_rate;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    // 标识符:validity_angle_rate_Y
    // 名  称:有效性_角速率Y轴
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_angle_rate_Y;

    // 标识符:validity_angle_rate_X
    // 名  称:有效性_角速率X轴
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_angle_rate_X;

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_roll_rate;

    // 标识符:validity_accel_Z
    // 名  称:有效性_加速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    BOOL_8 validity_accel_Z;

    // 标识符:validity_accel_Y
    // 名  称:有效性_加速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_accel_Y;

    // 标识符:validity_accel_X
    // 名  称:有效性_加速度X轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_accel_X;

    // 标识符:validity_angle_rate_Z
    // 名  称:有效性_角速率Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_angle_rate_Z;

    // 标识符:validity_vel_X
    // 名  称:有效性_速度X轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:24
    BOOL_8 validity_vel_X;

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_accel_north;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:24
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    BOOL_8 validity_vel_north;

    // 标识符:validity_vel_Z
    // 名  称:有效性_速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    BOOL_8 validity_vel_Z;

    // 标识符:validity_vel_Y
    // 名  称:有效性_速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    BOOL_8 validity_vel_Y;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:16
    BOOL_8 validity_ground_speed;

    // 标识符:validity_total_vel
    // 名  称:有效性_总速
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    BOOL_8 validity_total_vel;

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    BOOL_8 validity_vel_up;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:24
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:8
    BOOL_8 validity_inertial_AOA;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    BOOL_8 validity_climbing_angle;

    SPARE8 spare1;  // 保留字段

    // 标识符:validity_plat_to_body_matrix
    // 名  称:有效性_平台系到机体转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:16
    BOOL_8 validity_plat_to_body_matrix;

    // 标识符:validity_earth_to_plat_matrix
    // 名  称:有效性_地球系到地理系转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:8
    BOOL_8 validity_earth_to_plat_matrix;

    // 标识符:validity_G_force
    // 名  称:有效性_法向过载
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    BOOL_8 validity_G_force;

} INS_PURE_INERTIAL_NAV_DATA_A_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: ac_true_heading
// 信 号 组 名    称: 载机真航向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)deg
//                    相对于真北顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_TRUE_HEADING_TYPE_DEF;

// 信 号 组 标 识 符: ac_total_vel
// 信 号 组 名    称: 载机总速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_TOTAL_VEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_sl_angle
// 信 号 组 名    称: 载机偏流角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-45,45]deg
//                    速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_SL_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: ac_roll_rate
// 信 号 组 名    称: 载机横滚角速率
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} AC_ROLL_RATE_TYPE_DEF;

// 信 号 组 标 识 符: ac_roll
// 信 号 组 名    称: 载机横滚角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: (-180,180]deg
//                    右倾为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_ROLL_TYPE_DEF;

// 信 号 组 标 识 符: ac_plat_vel
// 信 号 组 名    称: 载机平台系速度
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
typedef struct
{
    // 标识符:Vel_North
    // 名  称:速度_北向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VEL_NORTH_TYPE_DEF Vel_North;

    // 标识符:Vel_West
    // 名  称:速度_西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VEL_WEST_TYPE_DEF Vel_West;

    // 标识符:Vel_Up
    // 名  称:速度_天向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    VEL_UP_TYPE_DEF Vel_Up;

} AC_PLAT_VEL_TYPE_DEF;

// 信 号 组 标 识 符: Accel_West
// 信 号 组 名    称: 加速度_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_WEST_TYPE_DEF;

// 信 号 组 标 识 符: Accel_Up
// 信 号 组 名    称: 加速度_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_UP_TYPE_DEF;

// 信 号 组 标 识 符: Accel_North
// 信 号 组 名    称: 加速度_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: ac_plat_accel
// 信 号 组 名    称: 载机平台系加速度
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
typedef struct
{
    // 标识符:Accel_North
    // 名  称:加速度_北向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    ACCEL_NORTH_TYPE_DEF Accel_North;

    // 标识符:Accel_West
    // 名  称:加速度_西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    ACCEL_WEST_TYPE_DEF Accel_West;

    // 标识符:Accel_Up
    // 名  称:加速度_天向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    ACCEL_UP_TYPE_DEF Accel_Up;

} AC_PLAT_ACCEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_pitch_rate
// 信 号 组 名    称: 载机俯仰角速率
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} AC_PITCH_RATE_TYPE_DEF;

// 信 号 组 标 识 符: ac_pitch
// 信 号 组 名    称: 载机俯仰角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    仰角为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_PITCH_TYPE_DEF;

// 信 号 组 标 识 符: ac_inertial_AOS
// 信 号 组 名    称: 载机惯性侧滑角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-45,45]deg
//                    速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_INERTIAL_AOS_TYPE_DEF;

// 信 号 组 标 识 符: ac_inertial_AOA
// 信 号 组 名    称: 载机惯性攻角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_INERTIAL_AOA_TYPE_DEF;

// 信 号 组 标 识 符: ac_heading_rate
// 信 号 组 名    称: 载机航向角速率
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} AC_HEADING_RATE_TYPE_DEF;

// 信 号 组 标 识 符: ac_ground_track_angle
// 信 号 组 名    称: 载机航迹角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)deg
//                    相对于真北顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_GROUND_TRACK_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: ac_ground_speed
// 信 号 组 名    称: 载机地速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_GROUND_SPEED_TYPE_DEF;

// 信 号 组 标 识 符: ac_G_force
// 信 号 组 名    称: 载机法向过载
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-9.9,9.9]g
typedef struct
{
    // 标识符:_G_force
    // 名  称:_过载
    // 说  明:
    // 单  位:g
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _G_force;

} AC_G_FORCE_TYPE_DEF;

// 信 号 组 标 识 符: ac_climbing_angle
// 信 号 组 名    称: 载机爬升角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    爬升为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_CLIMBING_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: Vel_Z
// 信 号 组 名    称: 速度_Z轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_Z_TYPE_DEF;

// 信 号 组 标 识 符: Vel_Y
// 信 号 组 名    称: 速度_Y轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_Y_TYPE_DEF;

// 信 号 组 标 识 符: Vel_X
// 信 号 组 名    称: 速度_X轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_X_TYPE_DEF;

// 信 号 组 标 识 符: ac_body_vel
// 信 号 组 名    称: 机体系速度
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s
typedef struct
{
    // 标识符:Vel_X
    // 名  称:速度_X轴
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VEL_X_TYPE_DEF Vel_X;

    // 标识符:Vel_Y
    // 名  称:速度_Y轴
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VEL_Y_TYPE_DEF Vel_Y;

    // 标识符:Vel_Z
    // 名  称:速度_Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    VEL_Z_TYPE_DEF Vel_Z;

} AC_BODY_VEL_TYPE_DEF;

// 信 号 组 标 识 符: anglerate_Z
// 信 号 组 名    称: 角速率_Z轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} ANGLERATE_Z_TYPE_DEF;

// 信 号 组 标 识 符: anglerate_Y
// 信 号 组 名    称: 角速率_Y轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} ANGLERATE_Y_TYPE_DEF;

// 信 号 组 标 识 符: anglerate_X
// 信 号 组 名    称: 角速率_X轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} ANGLERATE_X_TYPE_DEF;

// 信 号 组 标 识 符: ac_body_axis_rate
// 信 号 组 名    称: 机体系角速率
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s;[-720,720]deg/s;[-720,720]deg/s
//                    飞机相对于惯性系的转动角速率在机体系的投影，即陀螺测量到的角速率。
typedef struct
{
    // 标识符:anglerate_X
    // 名  称:角速率_X轴
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    ANGLERATE_X_TYPE_DEF anglerate_X;

    // 标识符:anglerate_Y
    // 名  称:角速率_Y轴
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    ANGLERATE_Y_TYPE_DEF anglerate_Y;

    // 标识符:anglerate_Z
    // 名  称:角速率_Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    ANGLERATE_Z_TYPE_DEF anglerate_Z;

} AC_BODY_AXIS_RATE_TYPE_DEF;

// 信 号 组 标 识 符: Accel_Z
// 信 号 组 名    称: 加速度_Z轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_Z_TYPE_DEF;

// 信 号 组 标 识 符: Accel_Y
// 信 号 组 名    称: 加速度_Y轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_Y_TYPE_DEF;

// 信 号 组 标 识 符: Accel_X
// 信 号 组 名    称: 加速度_X轴
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} ACCEL_X_TYPE_DEF;

// 信 号 组 标 识 符: ac_body_accel
// 信 号 组 名    称: 机体系加速度
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
//                    注：该加速度包含重力加速度。
typedef struct
{
    // 标识符:Accel_X
    // 名  称:加速度_X轴
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    ACCEL_X_TYPE_DEF Accel_X;

    // 标识符:Accel_Y
    // 名  称:加速度_Y轴
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    ACCEL_Y_TYPE_DEF Accel_Y;

    // 标识符:Accel_Z
    // 名  称:加速度_Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    ACCEL_Z_TYPE_DEF Accel_Z;

} AC_BODY_ACCEL_TYPE_DEF;

// 信 号 组 标 识 符: _earth_to_plat_matrix
// 信 号 组 名    称: 地球系到地理系转换矩阵
// 信 号 组 字    数: 9
// 信 号 组 数组长度: 1
// 信 号 组 说    明: _系数xx = cos(AC_LAT)
//                    _系数xy = 0
//                    _系数xz = -sin(AC_LAT)
typedef struct
{
    // 标识符:coefficent_xx
    // 名  称:系数xx
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    COEFFICENT_XX_TYPE_DEF coefficent_xx;

    // 标识符:coefficent_xy
    // 名  称:系数xy
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    COEFFICENT_XY_TYPE_DEF coefficent_xy;

    // 标识符:coefficent_xz
    // 名  称:系数xz
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    COEFFICENT_XZ_TYPE_DEF coefficent_xz;

    // 标识符:coefficent_yx
    // 名  称:系数yx
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    COEFFICENT_YX_TYPE_DEF coefficent_yx;

    // 标识符:coefficent_yy
    // 名  称:系数yy
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    COEFFICENT_YY_TYPE_DEF coefficent_yy;

    // 标识符:coefficent_yz
    // 名  称:系数yz
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    COEFFICENT_YZ_TYPE_DEF coefficent_yz;

    // 标识符:coefficent_zx
    // 名  称:系数zx
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    COEFFICENT_ZX_TYPE_DEF coefficent_zx;

    // 标识符:coefficent_zy
    // 名  称:系数zy
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    COEFFICENT_ZY_TYPE_DEF coefficent_zy;

    // 标识符:coefficent_zz
    // 名  称:系数zz
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    COEFFICENT_ZZ_TYPE_DEF coefficent_zz;

} _EARTH_TO_PLAT_MATRIX_TYPE_DEF;

// 信 号 组 标 识 符: pure_inertial_nav_data_A
// 信 号 组 名    称: 纯惯导航数据A
// 信 号 组 字    数: 57
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:INS_pure_inertial_nav_data_A_validity
    // 名  称:INS纯惯导航数据A_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    INS_PURE_INERTIAL_NAV_DATA_A_VALIDITY_TYPE_DEF INS_pure_inertial_nav_data_A_validity;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:15
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_body_axis_rate
    // 名  称:机体系角速率
    // 说  明:[-720,720]deg/s;[-720,720]deg/s;[-720,720]deg/s
    //        飞机相对于惯性系的转动角速率在机体系的投影，即陀螺测量到的角速率。
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_BODY_AXIS_RATE_TYPE_DEF ac_body_axis_rate;

    // 标识符:ac_body_accel
    // 名  称:机体系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    //        注：该加速度包含重力加速度。
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_BODY_ACCEL_TYPE_DEF ac_body_accel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_body_vel
    // 名  称:机体系速度
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:25
    // 起始位:0
    AC_BODY_VEL_TYPE_DEF ac_body_vel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:28
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_total_vel
    // 名  称:载机总速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:31
    // 起始位:0
    AC_TOTAL_VEL_TYPE_DEF ac_total_vel;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:32
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //        爬升为正
    // 单  位:
    // 起始字:34
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //        速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:35
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //        速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //        速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:37
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_G_force
    // 名  称:载机法向过载
    // 说  明:[-9.9,9.9]g
    // 单  位:
    // 起始字:38
    // 起始位:0
    AC_G_FORCE_TYPE_DEF ac_G_force;

    // 标识符:_earth_to_plat_matrix
    // 名  称:地球系到地理系转换矩阵
    // 说  明:_系数xx = cos(AC_LAT)
    //        _系数xy = 0
    //        _系数xz = -sin(AC_LAT)
    // 单  位:
    // 起始字:39
    // 起始位:0
    _EARTH_TO_PLAT_MATRIX_TYPE_DEF _earth_to_plat_matrix;

    // 标识符:plat_to_body_matrix
    // 名  称:平台系到机体转换矩阵
    // 说  明:_系数xx =  COS(φ) * COS(θ).
    //        _系数xy = -SIN(φ) * COS(θ).
    //        _系数xz = SIN(θ)
    //        _系数yx = COS(φ) * SIN(θ) * SIN(ξ) - SIN(φ) * COS(ξ)
    //        _系数yy = -COS(φ) * COS(ξ) - SIN(φ) * SIN(θ) * SIN(ξ)
    //        _系数yz = -COS(θ) * SIN(ξ)
    //        _系数zx = SIN(φ) * SIN(ξ) + COS(φ) * SIN(θ) * COS(ξ)
    //        _系数zy = COS(φ) * SIN(ξ) - SIN(φ) * SIN(θ) * COS(ξ)
    //        _系数zz = -COS(θ) * COS(ξ)
    //        φ=AC_Ture_Heading
    //        θ=AC_Pitch
    //        ξ=AC_Roll
    // 单  位:
    // 起始字:48
    // 起始位:0
    PLAT_TO_BODY_MATRIX_TYPE_DEF plat_to_body_matrix;

} PURE_INERTIAL_NAV_DATA_A_TYPE_DEF;

// 信 号 组 标 识 符: INS_pure_inertia_nav_data_B_validity
// 信 号 组 名    称: INS纯惯导航数据B_有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_pure_inertial_alt
    // 名  称:有效性_纯惯性高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_pure_inertial_alt;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_position;

} INS_PURE_INERTIA_NAV_DATA_B_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: ac_pure_inertial_alt
// 信 号 组 名    称: 载机纯惯性高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
//                    INS无气压高度阻尼的纯惯性高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_PURE_INERTIAL_ALT_TYPE_DEF;

// 信 号 组 标 识 符: ac_position_data
// 信 号 组 名    称: 载机位置数据
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    (-180,180]deg
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _longitude;

} AC_POSITION_DATA_TYPE_DEF;

// 信 号 组 标 识 符: pure_inertia_nav_data_B
// 信 号 组 名    称: 纯惯导航数据B
// 信 号 组 字    数: 6
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:INS_pure_inertia_nav_data_B_validity
    // 名  称:INS纯惯导航数据B_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    INS_PURE_INERTIA_NAV_DATA_B_VALIDITY_TYPE_DEF INS_pure_inertia_nav_data_B_validity;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:3
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:ac_pure_inertial_alt
    // 名  称:载机纯惯性高度
    // 说  明:[-500,30000]m
    //        INS无气压高度阻尼的纯惯性高度
    // 单  位:
    // 起始字:5
    // 起始位:0
    AC_PURE_INERTIAL_ALT_TYPE_DEF ac_pure_inertial_alt;

} PURE_INERTIA_NAV_DATA_B_TYPE_DEF;

// 信 号 组 标 识 符: roz
// 信 号 组 名    称: ROZ
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-0.1,0.1]mrad/s
//                    由于飞机在地球上运动而产生的航向变化率
//                    Roz = -(VEL_WEST*tan(LAT))/(R*(1+sin^2(LAT)*e)+ ALT)
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} ROZ_TYPE_DEF;

// 信 号 组 标 识 符: location_error_covariance_4
// 信 号 组 名    称: 位置误差方差4
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance_long
    // 名  称:_长距
    // 说  明:用于距离、长度等信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT64 _distance_long;

} LOCATION_ERROR_COVARIANCE_4_TYPE_DEF;

// 信 号 组 标 识 符: location_error_covariance_3
// 信 号 组 名    称: 位置误差方差3
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance_long
    // 名  称:_长距
    // 说  明:用于距离、长度等信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT64 _distance_long;

} LOCATION_ERROR_COVARIANCE_3_TYPE_DEF;

// 信 号 组 标 识 符: location_error_covariance_2
// 信 号 组 名    称: 位置误差方差2
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance_long
    // 名  称:_长距
    // 说  明:用于距离、长度等信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT64 _distance_long;

} LOCATION_ERROR_COVARIANCE_2_TYPE_DEF;

// 信 号 组 标 识 符: location_error_covariance_1
// 信 号 组 名    称: 位置误差方差1
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance_long
    // 名  称:_长距
    // 说  明:用于距离、长度等信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT64 _distance_long;

} LOCATION_ERROR_COVARIANCE_1_TYPE_DEF;

// 信 号 组 标 识 符: location_error_covariance_matrix
// 信 号 组 名    称: 位置误差方差矩阵
// 信 号 组 字    数: 8
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:location_error_covariance_1
    // 名  称:位置误差方差1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    LOCATION_ERROR_COVARIANCE_1_TYPE_DEF location_error_covariance_1;

    // 标识符:location_error_covariance_2
    // 名  称:位置误差方差2
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    LOCATION_ERROR_COVARIANCE_2_TYPE_DEF location_error_covariance_2;

    // 标识符:location_error_covariance_3
    // 名  称:位置误差方差3
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    LOCATION_ERROR_COVARIANCE_3_TYPE_DEF location_error_covariance_3;

    // 标识符:location_error_covariance_4
    // 名  称:位置误差方差4
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    LOCATION_ERROR_COVARIANCE_4_TYPE_DEF location_error_covariance_4;

} LOCATION_ERROR_COVARIANCE_MATRIX_TYPE_DEF;

// 信 号 组 标 识 符: mag_var
// 信 号 组 名    称: 磁差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    磁北相对于真北之间的角度差，顺时针为正。
//                    注：磁航向=真航向-磁差
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} MAG_VAR_TYPE_DEF;

// 信 号 组 标 识 符: local_magnetic_variation
// 信 号 组 名    称: 本地磁差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    飞机所在位置的磁差
typedef struct
{
    // 标识符:mag_var
    // 名  称:磁差
    // 说  明:[-90,90]deg
    //        磁北相对于真北之间的角度差，顺时针为正。
    //        注：磁航向=真航向-磁差
    // 单  位:
    // 起始字:0
    // 起始位:0
    MAG_VAR_TYPE_DEF mag_var;

} LOCAL_MAGNETIC_VARIATION_TYPE_DEF;

// 信 号 组 标 识 符: local_gravity
// 信 号 组 名    称: 本地重力加速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [9.5,10]m/s/s
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} LOCAL_GRAVITY_TYPE_DEF;

// 信 号 组 标 识 符: INS_hybrid_nav_data_B_validity
// 信 号 组 名    称: INS组合导航数据B_有效性
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_position;

    // 标识符:validity_baro_GNSS_inertial_ADS_alt
    // 名  称:有效性_惯性卫星大气参考高度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_baro_GNSS_inertial_ADS_alt;

    // 标识符:validity_GNSS_inertial_ADS_alt
    // 名  称:有效性_惯性卫星大气高度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_GNSS_inertial_ADS_alt;

    // 标识符:validity_baro_pressure_inertial_alt
    // 名  称:有效性_惯性气压参考高度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_baro_pressure_inertial_alt;

    // 标识符:validity_pressure_inertial_alt
    // 名  称:有效性_惯性气压高度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_pressure_inertial_alt;

    // 标识符:validity_location_error_covariance_matrix
    // 名  称:有效性_位置误差方差矩阵
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    BOOL_8 validity_location_error_covariance_matrix;

    // 标识符:validity_roz
    // 名  称:有效性_ROZ
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_roz;

    // 标识符:validity_local_gravity
    // 名  称:有效性_本地重力加速度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_local_gravity;

    // 标识符:validity_local_magnetic_variation
    // 名  称:有效性_本地磁差
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_local_magnetic_variation;

} INS_HYBRID_NAV_DATA_B_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: AC_pressure_inertial_alt
// 信 号 组 名    称: 载机惯性气压高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
//                    INS阻尼后的气压高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_PRESSURE_INERTIAL_ALT_TYPE_DEF;

// 信 号 组 标 识 符: AC_GNSS_inertial_ADS_alt
// 信 号 组 名    称: 载机惯性卫星大气高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-2500,30000]m
//                    INS/卫星/ADS组合高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_GNSS_INERTIAL_ADS_ALT_TYPE_DEF;

// 信 号 组 标 识 符: AC_baro_pressure_inertial_alt
// 信 号 组 名    称: 载机惯性气压参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-5500,30000]m
//                    =惯性气压高度－场压装订高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_BARO_PRESSURE_INERTIAL_ALT_TYPE_DEF;

// 信 号 组 标 识 符: AC_baro_GNSS_inertial_ADS_alt
// 信 号 组 名    称: 载机惯性卫星大气参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-7500,30000]m
//                    惯性卫星大气高度－场压装订高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_BARO_GNSS_INERTIAL_ADS_ALT_TYPE_DEF;

// 信 号 组 标 识 符: hybrid_nav_data_B
// 信 号 组 名    称: 组合导航数据B
// 信 号 组 字    数: 22
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:INS_hybrid_nav_data_B_validity
    // 名  称:INS组合导航数据B_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    INS_HYBRID_NAV_DATA_B_VALIDITY_TYPE_DEF INS_hybrid_nav_data_B_validity;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:5
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:AC_pressure_inertial_alt
    // 名  称:载机惯性气压高度
    // 说  明:[-500,30000]m
    //        INS阻尼后的气压高度
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_pressure_inertial_alt;

    // 标识符:AC_baro_pressure_inertial_alt
    // 名  称:载机惯性气压参考高度
    // 说  明:[-5500,30000]m
    //        =惯性气压高度－场压装订高度
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_BARO_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_baro_pressure_inertial_alt;

    // 标识符:AC_GNSS_inertial_ADS_alt
    // 名  称:载机惯性卫星大气高度
    // 说  明:[-2500,30000]m
    //        INS/卫星/ADS组合高度
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_GNSS_INERTIAL_ADS_ALT_TYPE_DEF AC_GNSS_inertial_ADS_alt;

    // 标识符:AC_baro_GNSS_inertial_ADS_alt
    // 名  称:载机惯性卫星大气参考高度
    // 说  明:[-7500,30000]m
    //        惯性卫星大气高度－场压装订高度
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_BARO_GNSS_INERTIAL_ADS_ALT_TYPE_DEF AC_baro_GNSS_inertial_ADS_alt;

    // 标识符:local_magnetic_variation
    // 名  称:本地磁差
    // 说  明:[-90,90]deg
    //        飞机所在位置的磁差
    // 单  位:
    // 起始字:11
    // 起始位:0
    LOCAL_MAGNETIC_VARIATION_TYPE_DEF local_magnetic_variation;

    // 标识符:local_gravity
    // 名  称:本地重力加速度
    // 说  明:[9.5,10]m/s/s
    // 单  位:
    // 起始字:12
    // 起始位:0
    LOCAL_GRAVITY_TYPE_DEF local_gravity;

    // 标识符:roz
    // 名  称:ROZ
    // 说  明:[-0.1,0.1]mrad/s
    //        由于飞机在地球上运动而产生的航向变化率
    //        Roz = -(VEL_WEST*tan(LAT))/(R*(1+sin^2(LAT)*e)+ ALT)
    // 单  位:
    // 起始字:13
    // 起始位:0
    ROZ_TYPE_DEF roz;

    // 标识符:location_error_covariance_matrix
    // 名  称:位置误差方差矩阵
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    LOCATION_ERROR_COVARIANCE_MATRIX_TYPE_DEF location_error_covariance_matrix;

} HYBRID_NAV_DATA_B_TYPE_DEF;

// 信 号 组 标 识 符: INS_hybrid_nav_data_A_validity
// 信 号 组 名    称: INS组合导航数据A_有效性
// 信 号 组 字    数: 12
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_mag_heading
    // 名  称:有效性_磁航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_mag_heading;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    SPARE8 spare1;  // 保留字段

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_roll_rate;

    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_pitch_rate;

    SPARE8 spare2;  // 保留字段

    // 标识符:validity_angle_rate_Z
    // 名  称:有效性_角速率Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_angle_rate_Z;

    // 标识符:validity_angle_rate_Y
    // 名  称:有效性_角速率Y轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_angle_rate_Y;

    // 标识符:validity_angle_rate_X
    // 名  称:有效性_角速率X轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_angle_rate_X;

    SPARE8 spare3;  // 保留字段

    // 标识符:validity_accel_Z
    // 名  称:有效性_加速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    BOOL_8 validity_accel_Z;

    // 标识符:validity_accel_Y
    // 名  称:有效性_加速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_accel_Y;

    // 标识符:validity_accel_X
    // 名  称:有效性_加速度X轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_accel_X;

    SPARE8 spare4;  // 保留字段

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    BOOL_8 validity_accel_north;

    SPARE8 spare5;  // 保留字段

    // 标识符:validity_vel_Z
    // 名  称:有效性_速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:16
    BOOL_8 validity_vel_Z;

    // 标识符:validity_vel_Y
    // 名  称:有效性_速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    BOOL_8 validity_vel_Y;

    // 标识符:validity_vel_X
    // 名  称:有效性_速度X轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    BOOL_8 validity_vel_X;

    SPARE8 spare6;  // 保留字段

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:8
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    BOOL_8 validity_vel_north;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:24
    BOOL_8 validity_climbing_angle;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:16
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:8
    BOOL_8 validity_ground_speed;

    // 标识符:validity_total_vel
    // 名  称:有效性_总速
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    BOOL_8 validity_total_vel;

    // 标识符:validity_G_force
    // 名  称:有效性_法向过载
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_G_force;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_inertial_AOA;

    SPARE8 spare7[2];  // 保留字段

    // 标识符:validity_plat_to_body_matrix
    // 名  称:有效性_平台系到机体转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_plat_to_body_matrix;

    // 标识符:validity_earth_to_plat_matrix
    // 名  称:有效性_地球系到地理系转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_earth_to_plat_matrix;

    SPARE8 spare8;  // 保留字段

    // 标识符:validity_wind_up
    // 名  称:有效性_风速天向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:16
    BOOL_8 validity_wind_up;

    // 标识符:validity_wind_west
    // 名  称:有效性_风速西向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:8
    BOOL_8 validity_wind_west;

    // 标识符:validity_wind_north
    // 名  称:有效性_风速北向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    BOOL_8 validity_wind_north;

    // 标识符:validity_flight_path_acc
    // 名  称:有效性_飞行加速度
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:24
    BOOL_8 validity_flight_path_acc;

    // 标识符:validity_vel_up_adjusted
    // 名  称:有效性_修正天向速度
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:16
    BOOL_8 validity_vel_up_adjusted;

    // 标识符:validity_wind_vel_level
    // 名  称:有效性_风速水平
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    BOOL_8 validity_wind_vel_level;

    // 标识符:validity_wind_direction_level
    // 名  称:有效性_风向水平
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    BOOL_8 validity_wind_direction_level;

} INS_HYBRID_NAV_DATA_A_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: wind_vel_level
// 信 号 组 名    称: 风速_水平
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,150]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_VEL_LEVEL_TYPE_DEF;

// 信 号 组 标 识 符: wind_direction_level
// 信 号 组 名    称: 风向_水平
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0，360)deg
//                    风的来向与真北的夹角
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} WIND_DIRECTION_LEVEL_TYPE_DEF;

// 信 号 组 标 识 符: INS_horizontal_wind_vel_dir
// 信 号 组 名    称: 惯导水平风速风向
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,150]m/s;
//                    [0,360)deg;
//                    与真北的夹角顺时针为正。
typedef struct
{
    // 标识符:wind_direction_level
    // 名  称:风向_水平
    // 说  明:[0，360)deg
    //        风的来向与真北的夹角
    // 单  位:
    // 起始字:0
    // 起始位:0
    WIND_DIRECTION_LEVEL_TYPE_DEF wind_direction_level;

    // 标识符:wind_vel_level
    // 名  称:风速_水平
    // 说  明:[0,150]m/s
    // 单  位:
    // 起始字:1
    // 起始位:0
    WIND_VEL_LEVEL_TYPE_DEF wind_vel_level;

} INS_HORIZONTAL_WIND_VEL_DIR_TYPE_DEF;

// 信 号 组 标 识 符: flight_path_acc
// 信 号 组 名    称: 载机飞行加速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-4,4]g
//                    表示载机飞行轨迹（速度矢量）方向上的加速度，延飞行轨迹（速度矢量）方向加速为正。
//                    当轮载在地面且地速小于150km/h时，强制输出为0；否则按计算值输出。
typedef struct
{
    // 标识符:_Accel_g
    // 名  称:_加速度_g
    // 说  明:以g为单位的加速度
    // 单  位:g
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _Accel_g;

} FLIGHT_PATH_ACC_TYPE_DEF;

// 信 号 组 标 识 符: wind_west
// 信 号 组 名    称: 风速_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_WEST_TYPE_DEF;

// 信 号 组 标 识 符: wind_up
// 信 号 组 名    称: 风速_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_UP_TYPE_DEF;

// 信 号 组 标 识 符: wind_north
// 信 号 组 名    称: 风速_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: ac_wind_vel
// 信 号 组 名    称: 载机风速矢量
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-100,100]m/s
//                    [-100,100]m/s
//                    [-100,100]m/s
typedef struct
{
    // 标识符:wind_north
    // 名  称:风速_北向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    WIND_NORTH_TYPE_DEF wind_north;

    // 标识符:wind_west
    // 名  称:风速_西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    WIND_WEST_TYPE_DEF wind_west;

    // 标识符:wind_up
    // 名  称:风速_天向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    WIND_UP_TYPE_DEF wind_up;

} AC_WIND_VEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_Vel_Up_adjusted
// 信 号 组 名    称: 修正天向速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]m/s
//                    惯性/大气/卫星组合的天向速度
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_VEL_UP_ADJUSTED_TYPE_DEF;

// 信 号 组 标 识 符: AC_mag_heading
// 信 号 组 名    称: 载机磁航向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)deg
//                    相对于磁北顺时针为正
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_MAG_HEADING_TYPE_DEF;

// 信 号 组 标 识 符: hybrid_nav_data_A
// 信 号 组 名    称: 组合导航数据A
// 信 号 组 字    数: 69
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:INS_hybrid_nav_data_A_validity
    // 名  称:INS组合导航数据A_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    INS_HYBRID_NAV_DATA_A_VALIDITY_TYPE_DEF INS_hybrid_nav_data_A_validity;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:15
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:AC_mag_heading
    // 名  称:载机磁航向
    // 说  明:[0,360)deg
    //        相对于磁北顺时针为正
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_MAG_HEADING_TYPE_DEF AC_mag_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_body_axis_rate
    // 名  称:机体系角速率
    // 说  明:[-720,720]deg/s;[-720,720]deg/s;[-720,720]deg/s
    //        飞机相对于惯性系的转动角速率在机体系的投影，即陀螺测量到的角速率。
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_BODY_AXIS_RATE_TYPE_DEF ac_body_axis_rate;

    // 标识符:ac_body_accel
    // 名  称:机体系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    //        注：该加速度包含重力加速度。
    // 单  位:
    // 起始字:24
    // 起始位:0
    AC_BODY_ACCEL_TYPE_DEF ac_body_accel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:27
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_body_vel
    // 名  称:机体系速度
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:30
    // 起始位:0
    AC_BODY_VEL_TYPE_DEF ac_body_vel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_total_vel
    // 名  称:载机总速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_TOTAL_VEL_TYPE_DEF ac_total_vel;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:37
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:38
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //        爬升为正
    // 单  位:
    // 起始字:39
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //        速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:40
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //        速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:41
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //        速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:42
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_G_force
    // 名  称:载机法向过载
    // 说  明:[-9.9,9.9]g
    // 单  位:
    // 起始字:43
    // 起始位:0
    AC_G_FORCE_TYPE_DEF ac_G_force;

    // 标识符:_earth_to_plat_matrix
    // 名  称:地球系到地理系转换矩阵
    // 说  明:_系数xx = cos(AC_LAT)
    //        _系数xy = 0
    //        _系数xz = -sin(AC_LAT)
    // 单  位:
    // 起始字:44
    // 起始位:0
    _EARTH_TO_PLAT_MATRIX_TYPE_DEF _earth_to_plat_matrix;

    // 标识符:plat_to_body_matrix
    // 名  称:平台系到机体转换矩阵
    // 说  明:_系数xx =  COS(φ) * COS(θ).
    //        _系数xy = -SIN(φ) * COS(θ).
    //        _系数xz = SIN(θ)
    //        _系数yx = COS(φ) * SIN(θ) * SIN(ξ) - SIN(φ) * COS(ξ)
    //        _系数yy = -COS(φ) * COS(ξ) - SIN(φ) * SIN(θ) * SIN(ξ)
    //        _系数yz = -COS(θ) * SIN(ξ)
    //        _系数zx = SIN(φ) * SIN(ξ) + COS(φ) * SIN(θ) * COS(ξ)
    //        _系数zy = COS(φ) * SIN(ξ) - SIN(φ) * SIN(θ) * COS(ξ)
    //        _系数zz = -COS(θ) * COS(ξ)
    //        φ=AC_Ture_Heading
    //        θ=AC_Pitch
    //        ξ=AC_Roll
    // 单  位:
    // 起始字:53
    // 起始位:0
    PLAT_TO_BODY_MATRIX_TYPE_DEF plat_to_body_matrix;

    // 标识符:ac_wind_vel
    // 名  称:载机风速矢量
    // 说  明:[-100,100]m/s
    //        [-100,100]m/s
    //        [-100,100]m/s
    // 单  位:
    // 起始字:62
    // 起始位:0
    AC_WIND_VEL_TYPE_DEF ac_wind_vel;

    // 标识符:INS_horizontal_wind_vel_dir
    // 名  称:惯导水平风速风向
    // 说  明:[0,150]m/s;
    //        [0,360)deg;
    //        与真北的夹角顺时针为正。
    // 单  位:
    // 起始字:65
    // 起始位:0
    INS_HORIZONTAL_WIND_VEL_DIR_TYPE_DEF INS_horizontal_wind_vel_dir;

    // 标识符:ac_Vel_Up_adjusted
    // 名  称:修正天向速度
    // 说  明:[-1000,1000]m/s
    //        惯性/大气/卫星组合的天向速度
    // 单  位:
    // 起始字:67
    // 起始位:0
    AC_VEL_UP_ADJUSTED_TYPE_DEF ac_Vel_Up_adjusted;

    // 标识符:flight_path_acc
    // 名  称:载机飞行加速度
    // 说  明:[-4,4]g
    //        表示载机飞行轨迹（速度矢量）方向上的加速度，延飞行轨迹（速度矢量）方向加速为正。
    //        当轮载在地面且地速小于150km/h时，强制输出为0；否则按计算值输出。
    // 单  位:
    // 起始字:68
    // 起始位:0
    FLIGHT_PATH_ACC_TYPE_DEF flight_path_acc;

} HYBRID_NAV_DATA_A_TYPE_DEF;

// 信 号 组 标 识 符: VMS_DataBlock_Valid_4
// 信 号 组 名    称: 飞管数据包有效性4
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:yes_no
    // 名  称:YES_NO
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 yes_no;

} VMS_DATABLOCK_VALID_4_TYPE_DEF;

// 信 号 组 标 识 符: VMS_Chn_Valid
// 信 号 组 名    称: 飞管通道有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:yes_no
    // 名  称:YES_NO
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 yes_no;

} VMS_CHN_VALID_TYPE_DEF;

// 信 号 组 标 识 符: true_static_pressure
// 信 号 组 名    称: 真实静压
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [1.7,108.4]kPa
typedef struct
{
    // 标识符:_pressure_pa
    // 名  称:_压强_帕
    // 说  明:
    // 单  位:Pa
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT32 _pressure_pa;

} TRUE_STATIC_PRESSURE_TYPE_DEF;

// 信 号 组 标 识 符: cokpit_differential_pressure
// 信 号 组 名    称: 座舱压力差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-8,80]kPa
typedef struct
{
    // 标识符:_pressure_pa
    // 名  称:_压强_帕
    // 说  明:
    // 单  位:Pa
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT32 _pressure_pa;

} COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF;

// 信 号 组 标 识 符: cokpit_alt
// 信 号 组 名    称: 座舱高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-2000,20567]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} COKPIT_ALT_TYPE_DEF;

// 信 号 组 标 识 符: baro_setting_alt
// 信 号 组 名    称: 场压装订高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,5000]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} BARO_SETTING_ALT_TYPE_DEF;

// 信 号 组 标 识 符: baro_setting
// 信 号 组 名    称: 场压装订
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [54,107.5]kPa
typedef struct
{
    // 标识符:_pressure_pa
    // 名  称:_压强_帕
    // 说  明:
    // 单  位:Pa
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT32 _pressure_pa;

} BARO_SETTING_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data_validity
// 信 号 组 名    称: 大气导航数据_有效性
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_cal_air_speed
    // 名  称:有效性_校准空速
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_cal_air_speed;

    // 标识符:validity_true_airspeed
    // 名  称:有效性_真空速
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_true_airspeed;

    // 标识符:validity_true_side_slip_angle
    // 名  称:有效性_真侧滑角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_true_side_slip_angle;

    // 标识符:validity_true_aoa
    // 名  称:有效性_真攻角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_true_aoa;

    // 标识符:validity_baro_setting_alt
    // 名  称:有效性_场压装订高度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_baro_setting_alt;

    // 标识符:validity_baro_setting
    // 名  称:有效性_场压装订
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_baro_setting;

    // 标识符:validity_pressure_alt_rate
    // 名  称:有效性_气压高度变化率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_pressure_alt_rate;

    // 标识符:validity_mach
    // 名  称:有效性_马赫数
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_mach;

    // 标识符:validity_free_airtemp
    // 名  称:有效性_大气静温
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    BOOL_8 validity_free_airtemp;

    // 标识符:validity_total_temperature
    // 名  称:有效性_大气总温
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_total_temperature;

    // 标识符:validity_baro_alt
    // 名  称:有效性_气压参考高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_baro_alt;

    // 标识符:validity_pressure_alt
    // 名  称:有效性_气压高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_pressure_alt;

    SPARE8 spare1;  // 保留字段

    // 标识符:validity_true_static_pressure
    // 名  称:有效性_真实静压
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    BOOL_8 validity_true_static_pressure;

    // 标识符:validity_air_density_ratio
    // 名  称:有效性_大气密度比
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_air_density_ratio;

    // 标识符:validity_pressure_ratio
    // 名  称:有效性_大气压力比
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_pressure_ratio;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:validity_cokpit_alt
    // 名  称:有效性_座舱高度
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    BOOL_8 validity_cokpit_alt;

    // 标识符:validity_cokpit_differential_pressure
    // 名  称:有效性_座舱压力差
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    BOOL_8 validity_cokpit_differential_pressure;

} AIR_NAV_DATA_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: ac_true_side_slip_angle
// 信 号 组 名    称: 载机真侧滑角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-20,20]deg
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: ac_true_aoa
// 信 号 组 名    称: 载机真攻角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-20,60]deg
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_TRUE_AOA_TYPE_DEF;

// 信 号 组 标 识 符: ac_true_airspeed
// 信 号 组 名    称: 载机真空速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,2500]km/h
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_TRUE_AIRSPEED_TYPE_DEF;

// 信 号 组 标 识 符: ac_total_temperature
// 信 号 组 名    称: 载机大气总温
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-70,350])Cel 即[203.15,623.15]Kel
typedef struct
{
    // 标识符:_temperature
    // 名  称:_温度
    // 说  明:
    // 单  位:Kel
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _temperature;

} AC_TOTAL_TEMPERATURE_TYPE_DEF;

// 信 号 组 标 识 符: ac_pressure_ratio
// 信 号 组 名    称: 载机大气压力比
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0.033,1.1]
typedef struct
{
    // 标识符:_float4dig_value
    // 名  称:_浮点数值_万分之一
    // 说  明:最低位万分之一，可表示约+/-10万。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _float4dig_value;

} AC_PRESSURE_RATIO_TYPE_DEF;

// 信 号 组 标 识 符: ac_pressure_alt_rate
// 信 号 组 名    称: 载机气压高度变化率
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-300,300]m/s
//                    即爬升率
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_PRESSURE_ALT_RATE_TYPE_DEF;

// 信 号 组 标 识 符: AC_pressure_alt
// 信 号 组 名    称: 载机气压高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,22800]m
//                    转发的大气高度
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_PRESSURE_ALT_TYPE_DEF;

// 信 号 组 标 识 符: ac_mach
// 信 号 组 名    称: 载机马赫数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,2.5]mach
typedef struct
{
    // 标识符:_mach
    // 名  称:_马赫数
    // 说  明:用于马赫数相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        表示精度0.0001MACH。
    // 单  位:Mach
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _mach;

} AC_MACH_TYPE_DEF;

// 信 号 组 标 识 符: ac_free_airtemp
// 信 号 组 名    称: 载机大气静温
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [173.15,373.15]kel
typedef struct
{
    // 标识符:_temperature
    // 名  称:_温度
    // 说  明:
    // 单  位:Kel
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _temperature;

} AC_FREE_AIRTEMP_TYPE_DEF;

// 信 号 组 标 识 符: ac_cal_air_speed
// 信 号 组 名    称: 载机校准空速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_CAL_AIR_SPEED_TYPE_DEF;

// 信 号 组 标 识 符: ac_baro_alt
// 信 号 组 名    称: 载机气压参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-5500,23300]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_BARO_ALT_TYPE_DEF;

// 信 号 组 标 识 符: ac_air_density_ratio
// 信 号 组 名    称: 载机大气密度比
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0.0355,1.045]
typedef struct
{
    // 标识符:_float4dig_value
    // 名  称:_浮点数值_万分之一
    // 说  明:最低位万分之一，可表示约+/-10万。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _float4dig_value;

} AC_AIR_DENSITY_RATIO_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data_D
// 信 号 组 名    称: 大气导航数据_D
// 信 号 组 字    数: 26
// 信 号 组 数组长度: 1
// 信 号 组 说    明: “飞管数据包有效性”根据SVPC、心跳原则判断。
//                    “飞管通道有效性”根据CHV判断。
typedef struct
{
    // 标识符:VMS_Chn_Valid
    // 名  称:飞管通道有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VMS_CHN_VALID_TYPE_DEF VMS_Chn_Valid;

    // 标识符:VMS_DataBlock_Valid_4
    // 名  称:飞管数据包有效性4
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VMS_DATABLOCK_VALID_4_TYPE_DEF VMS_DataBlock_Valid_4;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:2
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:air_nav_data_validity
    // 名  称:大气导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AIR_NAV_DATA_VALIDITY_TYPE_DEF air_nav_data_validity;

    // 标识符:ac_true_aoa
    // 名  称:载机真攻角
    // 说  明:[-20,60]deg
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AOA_TYPE_DEF ac_true_aoa;

    // 标识符:ac_true_side_slip_angle
    // 名  称:载机真侧滑角
    // 说  明:[-20,20]deg
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF ac_true_side_slip_angle;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_cal_air_speed
    // 名  称:载机校准空速
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_CAL_AIR_SPEED_TYPE_DEF ac_cal_air_speed;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

    // 标识符:ac_pressure_alt_rate
    // 名  称:载机气压高度变化率
    // 说  明:[-300,300]m/s
    //        即爬升率
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate;

    // 标识符:baro_setting
    // 名  称:场压装订
    // 说  明:[54,107.5]kPa
    // 单  位:
    // 起始字:15
    // 起始位:0
    BARO_SETTING_TYPE_DEF baro_setting;

    // 标识符:baro_setting_alt
    // 名  称:场压装订高度
    // 说  明:[-500,5000]m
    // 单  位:
    // 起始字:16
    // 起始位:0
    BARO_SETTING_ALT_TYPE_DEF baro_setting_alt;

    // 标识符:AC_pressure_alt
    // 名  称:载机气压高度
    // 说  明:[-500,22800]m
    //        转发的大气高度
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_PRESSURE_ALT_TYPE_DEF AC_pressure_alt;

    // 标识符:ac_baro_alt
    // 名  称:载机气压参考高度
    // 说  明:[-5500,23300]m
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_BARO_ALT_TYPE_DEF ac_baro_alt;

    // 标识符:ac_total_temperature
    // 名  称:载机大气总温
    // 说  明:[-70,350])Cel 即[203.15,623.15]Kel
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_TOTAL_TEMPERATURE_TYPE_DEF ac_total_temperature;

    // 标识符:ac_free_airtemp
    // 名  称:载机大气静温
    // 说  明:[173.15,373.15]kel
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_FREE_AIRTEMP_TYPE_DEF ac_free_airtemp;

    // 标识符:ac_pressure_ratio
    // 名  称:载机大气压力比
    // 说  明:[0.033,1.1]
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_PRESSURE_RATIO_TYPE_DEF ac_pressure_ratio;

    // 标识符:ac_air_density_ratio
    // 名  称:载机大气密度比
    // 说  明:[0.0355,1.045]
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_AIR_DENSITY_RATIO_TYPE_DEF ac_air_density_ratio;

    // 标识符:true_static_pressure
    // 名  称:真实静压
    // 说  明:[1.7,108.4]kPa
    // 单  位:
    // 起始字:23
    // 起始位:0
    TRUE_STATIC_PRESSURE_TYPE_DEF true_static_pressure;

    // 标识符:cokpit_differential_pressure
    // 名  称:座舱压力差
    // 说  明:[-8,80]kPa
    // 单  位:
    // 起始字:24
    // 起始位:0
    COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF cokpit_differential_pressure;

    // 标识符:cokpit_alt
    // 名  称:座舱高度
    // 说  明:[-2000,20567]m
    // 单  位:
    // 起始字:25
    // 起始位:0
    COKPIT_ALT_TYPE_DEF cokpit_alt;

} AIR_NAV_DATA_D_TYPE_DEF;

// 信 号 组 标 识 符: VMS_DataBlock_Valid_2
// 信 号 组 名    称: 飞管数据包有效性2
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:yes_no
    // 名  称:YES_NO
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 yes_no;

} VMS_DATABLOCK_VALID_2_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data_B
// 信 号 组 名    称: 大气导航数据_B
// 信 号 组 字    数: 26
// 信 号 组 数组长度: 1
// 信 号 组 说    明: “飞管数据包有效性”根据SVPC、心跳原则判断。
//                    “飞管通道有效性”根据CHV判断。
typedef struct
{
    // 标识符:VMS_Chn_Valid
    // 名  称:飞管通道有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VMS_CHN_VALID_TYPE_DEF VMS_Chn_Valid;

    // 标识符:VMS_DataBlock_Valid_2
    // 名  称:飞管数据包有效性2
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VMS_DATABLOCK_VALID_2_TYPE_DEF VMS_DataBlock_Valid_2;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:2
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:air_nav_data_validity
    // 名  称:大气导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AIR_NAV_DATA_VALIDITY_TYPE_DEF air_nav_data_validity;

    // 标识符:ac_true_aoa
    // 名  称:载机真攻角
    // 说  明:[-20,60]deg
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AOA_TYPE_DEF ac_true_aoa;

    // 标识符:ac_true_side_slip_angle
    // 名  称:载机真侧滑角
    // 说  明:[-20,20]deg
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF ac_true_side_slip_angle;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_cal_air_speed
    // 名  称:载机校准空速
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_CAL_AIR_SPEED_TYPE_DEF ac_cal_air_speed;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

    // 标识符:ac_pressure_alt_rate
    // 名  称:载机气压高度变化率
    // 说  明:[-300,300]m/s
    //        即爬升率
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate;

    // 标识符:baro_setting
    // 名  称:场压装订
    // 说  明:[54,107.5]kPa
    // 单  位:
    // 起始字:15
    // 起始位:0
    BARO_SETTING_TYPE_DEF baro_setting;

    // 标识符:baro_setting_alt
    // 名  称:场压装订高度
    // 说  明:[-500,5000]m
    // 单  位:
    // 起始字:16
    // 起始位:0
    BARO_SETTING_ALT_TYPE_DEF baro_setting_alt;

    // 标识符:AC_pressure_alt
    // 名  称:载机气压高度
    // 说  明:[-500,22800]m
    //        转发的大气高度
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_PRESSURE_ALT_TYPE_DEF AC_pressure_alt;

    // 标识符:ac_baro_alt
    // 名  称:载机气压参考高度
    // 说  明:[-5500,23300]m
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_BARO_ALT_TYPE_DEF ac_baro_alt;

    // 标识符:ac_total_temperature
    // 名  称:载机大气总温
    // 说  明:[-70,350])Cel 即[203.15,623.15]Kel
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_TOTAL_TEMPERATURE_TYPE_DEF ac_total_temperature;

    // 标识符:ac_free_airtemp
    // 名  称:载机大气静温
    // 说  明:[173.15,373.15]kel
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_FREE_AIRTEMP_TYPE_DEF ac_free_airtemp;

    // 标识符:ac_pressure_ratio
    // 名  称:载机大气压力比
    // 说  明:[0.033,1.1]
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_PRESSURE_RATIO_TYPE_DEF ac_pressure_ratio;

    // 标识符:ac_air_density_ratio
    // 名  称:载机大气密度比
    // 说  明:[0.0355,1.045]
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_AIR_DENSITY_RATIO_TYPE_DEF ac_air_density_ratio;

    // 标识符:true_static_pressure
    // 名  称:真实静压
    // 说  明:[1.7,108.4]kPa
    // 单  位:
    // 起始字:23
    // 起始位:0
    TRUE_STATIC_PRESSURE_TYPE_DEF true_static_pressure;

    // 标识符:cokpit_differential_pressure
    // 名  称:座舱压力差
    // 说  明:[-8,80]kPa
    // 单  位:
    // 起始字:24
    // 起始位:0
    COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF cokpit_differential_pressure;

    // 标识符:cokpit_alt
    // 名  称:座舱高度
    // 说  明:[-2000,20567]m
    // 单  位:
    // 起始字:25
    // 起始位:0
    COKPIT_ALT_TYPE_DEF cokpit_alt;

} AIR_NAV_DATA_B_TYPE_DEF;

// 信 号 组 标 识 符: VU_track_number
// 信 号 组 名    称: VU链目标编号
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 8
// 信 号 组 说    明: 编号及编识号为0时，表示链上无该目标。
typedef struct
{
    // 标识符:member_no
    // 名  称:成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 member_no;

    // 标识符:tgt_id
    // 名  称:目标编识号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 tgt_id;

} VU_TRACK_NUMBER_TYPE_DEF;

// 信 号 组 标 识 符: JIDS_track_number
// 信 号 组 名    称: JIDS链目标编号
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 8
// 信 号 组 说    明: 编号及编识号为0时，表示链上无该目标。
typedef struct
{
    // 标识符:member_no
    // 名  称:成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 member_no;

    // 标识符:tgt_id
    // 名  称:目标编识号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 tgt_id;

} JIDS_TRACK_NUMBER_TYPE_DEF;

// 信 号 组 标 识 符: IFDL_track_number
// 信 号 组 名    称: IFDL链目标编号
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 10
// 信 号 组 说    明: 编号及编识号为0时，表示链上无该目标。
typedef struct
{
    // 标识符:I_member_no
    // 名  称:I链成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 I_member_no;

    // 标识符:I_team_no
    // 名  称:I链编队号
    // 说  明:编队号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 I_team_no;

    // 标识符:tgt_id
    // 名  称:目标编识号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 tgt_id;

} IFDL_TRACK_NUMBER_TYPE_DEF;

// 信 号 组 标 识 符: TGFX_target_correlation
// 信 号 组 名    称: 融合目标关联矩阵
// 信 号 组 字    数: 66
// 信 号 组 数组长度: 5
// 信 号 组 说    明: 目标关联矩阵
typedef struct
{
    // 标识符:formation_fused_tgt_ID
    // 名  称:编队融合目标编号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 formation_fused_tgt_ID;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 platform_fused_tgt_ID;

    // 标识符:tgt_dis_ID
    // 名  称:目标显示编号
    // 说  明:融合输出的目标显示编号，用两位表示。
    //        显示使用数字1~9、字母a~z组合表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 tgt_dis_ID;

    // 标识符:RDR_track_number
    // 名  称:RDR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT16 RDR_track_number;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 IR_track_number;

    // 标识符:EW_tgt_no
    // 名  称:EW目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 EW_tgt_no;

    // 标识符:ADS_B_IN_target_id
    // 名  称:ADS_B_IN目标编号
    // 说  明:即S模式地址码,全球唯一编码
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 ADS_B_IN_target_id;

    // 标识符:SAT_link_tgt_id
    // 名  称:卫通链目标编识号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 SAT_link_tgt_id;

    // 标识符:VU_track_number
    // 名  称:VU链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:6
    // 起始位:0
    VU_TRACK_NUMBER_TYPE_DEF VU_track_number[8];

    // 标识符:JIDS_track_number
    // 名  称:JIDS链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:22
    // 起始位:0
    JIDS_TRACK_NUMBER_TYPE_DEF JIDS_track_number[8];

    // 标识符:IFDL_track_number
    // 名  称:IFDL链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:38
    // 起始位:0
    IFDL_TRACK_NUMBER_TYPE_DEF IFDL_track_number[10];

    SPARE8 spare2[2];  // 保留字段

    // 标识符:IBS_tgt_ID
    // 名  称:IBS目标编号
    // 说  明:0:NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:58
    // 起始位:0
    UINT16 IBS_tgt_ID;

    // 标识符:ADI_ID
    // 名  称:ADI标识号
    // 说  明:[0-524287]
    // 单  位:
    // LSB  :1
    // 起始字:59
    // 起始位:0
    UINT32 ADI_ID;

    SPARE8 spare3[2];  // 保留字段

    // 标识符:CRSM_tgt_ID
    // 名  称:通侦目标编号
    // 说  明:0：NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:60
    // 起始位:0
    UINT16 CRSM_tgt_ID;

    SPARE8 spare5[2];  // 保留字段

    // 标识符:DAS_tgt_no
    // 名  称:DAS目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:61
    // 起始位:8
    UINT8 DAS_tgt_no;

    SPARE8 spare4;  // 保留字段

    SPARE8 spare6[2];  // 保留字段

    // 标识符:EWS2_tgt_no
    // 名  称:选装电子战目标编号
    // 说  明:EW2M对选装电子战目标分配的统一编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:62
    // 起始位:0
    UINT16 EWS2_tgt_no;

    // 标识符:IIPM_tgt_no
    // 名  称:图像情报目标编号
    // 说  明:IIPM对图像情报目标分配的统一编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:63
    // 起始位:16
    UINT16 IIPM_tgt_no;

    SPARE8 spare7[2];  // 保留字段

    // 标识符:ais_target_id
    // 名  称:AIS目标编号
    // 说  明:MMSI编码，全球唯一编码。0～999999999
    // 单  位:
    // LSB  :1
    // 起始字:64
    // 起始位:0
    UINT32 ais_target_id;

    SPARE8 spare8[2];  // 保留字段

    // 标识符:LOADING_tgt_ID
    // 名  称:加载目标编号
    // 说  明:0：NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:65
    // 起始位:0
    UINT16 LOADING_tgt_ID;

} TGFX_TARGET_CORRELATION_TYPE_DEF;

// 信 号 组 标 识 符: upright_longitude
// 信 号 组 名    称: 右上角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 东向为正，几何校正后经度
//                    LSB= 0.00001
//
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} UPRIGHT_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: upright_latitude
// 信 号 组 名    称: 右上角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} UPRIGHT_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: upleft_longitude
// 信 号 组 名    称: 左上角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 东向为正，几何校正后经度
//                    LSB= 0.00001
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} UPLEFT_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: upleft_latitude
// 信 号 组 名    称: 左上角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 北向为正，几何校正后纬度
//                    LSB= 0.00001
//
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} UPLEFT_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: REGION_CENTER_Y
// 信 号 组 名    称: 区域中心位置Y
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} REGION_CENTER_Y_TYPE_DEF;

// 信 号 组 标 识 符: REGION_CENTER_X
// 信 号 组 名    称: 区域中心位置X
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} REGION_CENTER_X_TYPE_DEF;

// 信 号 组 标 识 符: image_center_longitude
// 信 号 组 名    称: 图像中心经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGE_CENTER_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: image_center_latitude
// 信 号 组 名    称: 图像中心纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGE_CENTER_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: downright_longitude
// 信 号 组 名    称: 右下角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 东向为正，几何校正后经度
//                    LSB= 0.00001
//
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} DOWNRIGHT_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: downright_latitude
// 信 号 组 名    称: 右下角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} DOWNRIGHT_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: downleft_longitude
// 信 号 组 名    称: 左下角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 东向为正，几何校正后经度
//                    LSB= 0.00001
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} DOWNLEFT_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: downleft_latitude
// 信 号 组 名    称: 左下角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} DOWNLEFT_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: image_paras_transit
// 信 号 组 名    称: 图像参数_下传
// 信 号 组 字    数: 56
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IMAGE_time_hour
    // 名  称:图像时间_时
    // 说  明:0～23
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 IMAGE_time_hour;

    // 标识符:IMAGE_date_day
    // 名  称:图像时间_日期_日
    // 说  明:01～31
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 IMAGE_date_day;

    // 标识符:IMAGE_date_mounth
    // 名  称:图像时间_日期_月
    // 说  明:01～12
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT8 IMAGE_date_mounth;

    // 标识符:IMAGE_date_year
    // 名  称:图像时间_日期_年
    // 说  明:2000年开始为0
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 IMAGE_date_year;

    // 标识符:IMAGE_time_ms
    // 名  称:图像时间_毫秒
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 IMAGE_time_ms;

    // 标识符:IMAGE_time_second
    // 名  称:图像时间_秒
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 IMAGE_time_second;

    // 标识符:IMAGE_time_minute
    // 名  称:图像时间_分
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 IMAGE_time_minute;

    // 标识符:IMG_ID
    // 名  称:图像帧序号
    // 说  明:共用。
    //        光电：图像总序号（可见光/红外分开计数）。
    //        雷达：即图像帧编号（即方位向图像编号），用于拼接及叠加：条带256K（距离）*2K（方位）为1帧分块；聚束为8K*8K为1帧分块，按照逐行从左到右（距离近到远），从下到上（航向方向）。
    //        帧号下电存在前端传感器，上电后按照上次的继续编号，满了从1开始编号（不同架次连续编）。雷达帧号不区分不同模式，连续编号。光电区分可见光和红外分别编。
    //
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 IMG_ID;

    // 标识符:A818_LineNo
    // 名  称:条带号
    // 说  明:1～65535，共用。
    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
    //        雷达：与帧序号定义相同，但是每个周期从1开始编号。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 A818_LineNo;

    // 标识符:A818_CycleNo
    // 名  称:周期号
    // 说  明:00000～65535，共用。
    //        光电定义：完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
    //        雷达定义：一张完整的聚束SAR的图像，作为一个周期；或者一副完整的条带SAR图像作为一个周期。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 A818_CycleNo;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:A818_EO_LineNo
    // 名  称:条带内序号
    // 说  明:1～65535，光电专用。
    //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 A818_EO_LineNo;

    // 标识符:A818_WideCover
    // 名  称:收容宽度
    // 说  明:单位：米。
    //        对于光电：广域模式和区域成像模式下垂直航向的实际宽度，区域监视模式下为一帧图像的实际宽度。
    //        对于侦察雷达：表示条带的幅宽、或聚束SAR的幅宽
    // 单  位:m
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 A818_WideCover;

    // 标识符:fov_vertical
    // 名  称:相机纵向视场
    // 说  明:共用。
    //        对于雷达表示当前成像时波束俯仰向的波束宽度
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:6
    // 起始位:16
    UINT16 fov_vertical;

    // 标识符:fov_transverse
    // 名  称:相机横向视场
    // 说  明:共用。
    //        对于雷达：表示当前成像时波束方位向的波束宽度
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:6
    // 起始位:0
    UINT16 fov_transverse;

    // 标识符:fov_center_el
    // 名  称:视场中心俯仰角
    // 说  明:共用，LSB=0.01
    //        对于光电：采用机体系；
    //        对于雷达：像时波束俯仰向中心线与水平面之间的夹角（东北天坐标系），向天为正，向地为负，取决于工作模式，属于雷达系统参数
    //
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:7
    // 起始位:16
    INT16 fov_center_el;

    // 标识符:fov_center_azimuth
    // 名  称:视场中心方位角
    // 说  明:共用，LSB=0.01
    //        对于光电：采用机体系；
    //        对于雷达：波束中心指向在水平面投影与正北方向夹角（东北天坐标系），从上往下看，顺时针为正。
    //
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:7
    // 起始位:0
    INT16 fov_center_azimuth;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:A818_Beside_tgt_cover
    // 名  称:傍向重叠率
    // 说  明:00~99,百分比,垂直飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:8
    // 起始位:8
    UINT8 A818_Beside_tgt_cover;

    // 标识符:A818_Couse_tgt_cover
    // 名  称:航向重叠率
    // 说  明:00~99,像素百分比,平行飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:8
    // 起始位:0
    UINT8 A818_Couse_tgt_cover;

    // 标识符:A818_GROUND_RESOLUTION
    // 名  称:地面摄影分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置地面摄影分辨率。像元投影到地面后的分辨率。精度与飞机姿态参数精度、相对高度参数精度等相关
    // 单  位:m
    // LSB  :0.01
    // 起始字:9
    // 起始位:16
    UINT16 A818_GROUND_RESOLUTION;

    // 标识符:A818_CUR_RESOLUTION
    // 名  称:像元分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置分辨率（计算值，精度与飞机姿态参数精度、相对高度参数精度等相关）
    //        对于雷达表示图像斜距距离向的像元尺寸。
    // 单  位:m
    // LSB  :0.01
    // 起始字:9
    // 起始位:0
    UINT16 A818_CUR_RESOLUTION;

    SPARE8 spare3[2];  // 保留字段

    // 标识符:A818_ImageCenterHeight
    // 名  称:图像中心高度
    // 说  明:图像中心对应的地面海拔值（成像区域的海拔平均值）
    // 单  位:m
    // LSB  :1
    // 起始字:10
    // 起始位:0
    INT16 A818_ImageCenterHeight;

    // 标识符:image_center_longitude
    // 名  称:图像中心经度
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    IMAGE_CENTER_LONGITUDE_TYPE_DEF image_center_longitude;

    // 标识符:image_center_latitude
    // 名  称:图像中心纬度
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    IMAGE_CENTER_LATITUDE_TYPE_DEF image_center_latitude;

    // 标识符:upleft_longitude
    // 名  称:左上角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    // 单  位:
    // 起始字:13
    // 起始位:0
    UPLEFT_LONGITUDE_TYPE_DEF upleft_longitude;

    // 标识符:upleft_latitude
    // 名  称:左上角纬度
    // 说  明:北向为正，几何校正后纬度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:14
    // 起始位:0
    UPLEFT_LATITUDE_TYPE_DEF upleft_latitude;

    // 标识符:downleft_longitude
    // 名  称:左下角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    // 单  位:
    // 起始字:15
    // 起始位:0
    DOWNLEFT_LONGITUDE_TYPE_DEF downleft_longitude;

    // 标识符:downleft_latitude
    // 名  称:左下角纬度
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    DOWNLEFT_LATITUDE_TYPE_DEF downleft_latitude;

    // 标识符:upright_longitude
    // 名  称:右上角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:17
    // 起始位:0
    UPRIGHT_LONGITUDE_TYPE_DEF upright_longitude;

    // 标识符:upright_latitude
    // 名  称:右上角纬度
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    UPRIGHT_LATITUDE_TYPE_DEF upright_latitude;

    // 标识符:downright_longitude
    // 名  称:右下角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:19
    // 起始位:0
    DOWNRIGHT_LONGITUDE_TYPE_DEF downright_longitude;

    // 标识符:downright_latitude
    // 名  称:右下角纬度
    // 说  明:
    // 单  位:
    // 起始字:20
    // 起始位:0
    DOWNRIGHT_LATITUDE_TYPE_DEF downright_latitude;

    SPARE8 spare4[2];  // 保留字段

    // 标识符:A818_FrequencyNo
    // 名  称:工作频点号
    // 说  明:雷达独有，由于频点保密要求，输出频点号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:21
    // 起始位:0
    UINT16 A818_FrequencyNo;

    // 标识符:A818_SlantRange
    // 名  称:场景中心斜距
    // 说  明:雷达独有，雷达到场景中心点的斜距，2位小数
    // 单  位:m
    // LSB  :0.01
    // 起始字:22
    // 起始位:0
    UINT32 A818_SlantRange;

    // 标识符:A818_AZPixelsNo
    // 名  称:图像方位向像元个数
    // 说  明:0~256K，一帧图像（块）方位向的像素个数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:23
    // 起始位:0
    UINT32 A818_AZPixelsNo;

    // 标识符:A818_RGPixelsNo
    // 名  称:图像距离向像元个数
    // 说  明:0~256K，一帧图像（块）距离向的像素个数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:24
    // 起始位:0
    UINT32 A818_RGPixelsNo;

    // 标识符:A818_AZpixelSize
    // 名  称:图像地距方位向像元尺寸
    // 说  明:000.0~999.99，2位小数。方位相两个像素的间隔（投影到地距上），雷达独有。
    // 单  位:m
    // LSB  :0.01
    // 起始字:25
    // 起始位:0
    UINT32 A818_AZpixelSize;

    // 标识符:A818_SlantRangeAZpixelSize
    // 名  称:图像斜距方位向像元尺寸
    // 说  明:000.0~999.99，2位小数.方位相两个像素的间隔（投影到斜距上）。雷达独有
    // 单  位:m
    // LSB  :0.01
    // 起始字:26
    // 起始位:0
    UINT32 A818_SlantRangeAZpixelSize;

    // 标识符:A818_EO_TakeTimes
    // 名  称:照相次数
    // 说  明:000~999，共用。
    //        光电：每次接收拍照指令或模式变换时+1，对应数据记录时，建立新模式的文件夹
    //        雷达：对SAR雷达，一次飞行过程中开机的序号，每切换一次工作模式，开机次数需递增。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:27
    // 起始位:16
    UINT16 A818_EO_TakeTimes;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:27
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:A818_EO_ExposureTime
    // 名  称:曝光时间
    // 说  明:000~999，图像曝光时间，分辨率为1微秒，光电独有
    // 单  位:Mic
    // LSB  :1
    // 起始字:28
    // 起始位:16
    UINT16 A818_EO_ExposureTime;

    // 标识符:A818_EO_FocalLength
    // 名  称:相机焦距
    // 说  明:0~65535，毫米,相机焦距参数，光电独有
    // 单  位:mm
    // LSB  :1
    // 起始字:28
    // 起始位:0
    UINT16 A818_EO_FocalLength;

    SPARE8 spare5[3];  // 保留字段

    // 标识符:move_tgt_acount
    // 名  称:动目标数目
    // 说  明:动目标检测标识，表示该图上最大动目标个数，最大设置为五个。光电独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:29
    // 起始位:0
    UINT8 move_tgt_acount;

    // 标识符:tgt1_upleft_Y
    // 名  称:动目标1框左上角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:30
    // 起始位:16
    UINT16 tgt1_upleft_Y;

    // 标识符:tgt1_upleft_x
    // 名  称:动目标1框左上角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:30
    // 起始位:0
    UINT16 tgt1_upleft_x;

    // 标识符:tgt1_downright_y
    // 名  称:动目标1框右下角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:31
    // 起始位:16
    UINT16 tgt1_downright_y;

    // 标识符:tgt1_downright_x
    // 名  称:动目标1框右下角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:31
    // 起始位:0
    UINT16 tgt1_downright_x;

    // 标识符:tgt2_upleft_Y
    // 名  称:动目标2框左上角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:32
    // 起始位:16
    UINT16 tgt2_upleft_Y;

    // 标识符:tgt2_upleft_x
    // 名  称:动目标2框左上角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:32
    // 起始位:0
    UINT16 tgt2_upleft_x;

    // 标识符:tgt2_downright_y
    // 名  称:动目标2框右下角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:33
    // 起始位:16
    UINT16 tgt2_downright_y;

    // 标识符:tgt2_downright_x
    // 名  称:动目标2框右下角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:33
    // 起始位:0
    UINT16 tgt2_downright_x;

    // 标识符:tgt3_upleft_Y
    // 名  称:动目标3框左上角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:34
    // 起始位:16
    UINT16 tgt3_upleft_Y;

    // 标识符:tgt3_upleft_x
    // 名  称:动目标3框左上角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:34
    // 起始位:0
    UINT16 tgt3_upleft_x;

    // 标识符:tgt3_downright_y
    // 名  称:动目标3框右下角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:35
    // 起始位:16
    UINT16 tgt3_downright_y;

    // 标识符:tgt3_downright_x
    // 名  称:动目标3框右下角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:35
    // 起始位:0
    UINT16 tgt3_downright_x;

    // 标识符:tgt4_upleft_Y
    // 名  称:动目标4框左上角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:36
    // 起始位:16
    UINT16 tgt4_upleft_Y;

    // 标识符:tgt4_upleft_x
    // 名  称:动目标4框左上角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:36
    // 起始位:0
    UINT16 tgt4_upleft_x;

    // 标识符:tgt4_downright_y
    // 名  称:动目标4框右下角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:37
    // 起始位:16
    UINT16 tgt4_downright_y;

    // 标识符:tgt4_downright_x
    // 名  称:动目标4框右下角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:37
    // 起始位:0
    UINT16 tgt4_downright_x;

    // 标识符:tgt5_upleft_Y
    // 名  称:动目标5框左上角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:38
    // 起始位:16
    UINT16 tgt5_upleft_Y;

    // 标识符:tgt5_upleft_x
    // 名  称:动目标5框左上角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:38
    // 起始位:0
    UINT16 tgt5_upleft_x;

    // 标识符:tgt5_downright_y
    // 名  称:动目标5框右下角纵向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:39
    // 起始位:16
    UINT16 tgt5_downright_y;

    // 标识符:tgt5_downright_x
    // 名  称:动目标5框右下角横向像素坐标
    // 说  明:动目标的四角坐标像素定义，以图像左下角为原点。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:39
    // 起始位:0
    UINT16 tgt5_downright_x;

    // 标识符:REGION_CENTER_X
    // 名  称:区域中心位置X
    // 说  明:用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
    // 单  位:
    // 起始字:40
    // 起始位:0
    REGION_CENTER_X_TYPE_DEF REGION_CENTER_X;

    // 标识符:REGION_CENTER_Y
    // 名  称:区域中心位置Y
    // 说  明:用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
    // 单  位:
    // 起始字:41
    // 起始位:0
    REGION_CENTER_Y_TYPE_DEF REGION_CENTER_Y;

    // 标识符:A818_NearestSlantRange
    // 名  称:最近斜距
    // 说  明:该图像帧的近边到平台的斜距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:42
    // 起始位:0
    UINT32 A818_NearestSlantRange;

    // 标识符:A818_FarthestSlantRange
    // 名  称:最远斜距
    // 说  明:该图像帧的远边到平台的斜距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:43
    // 起始位:0
    UINT32 A818_FarthestSlantRange;

    // 标识符:A818_NearestFloorDistance
    // 名  称:最近地距
    // 说  明:该图像帧的近边到平台的地距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:44
    // 起始位:0
    UINT32 A818_NearestFloorDistance;

    // 标识符:A818_FarthestFloorDistance
    // 名  称:最远地距
    // 说  明:该图像帧的远边到平台的地距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:45
    // 起始位:0
    UINT32 A818_FarthestFloorDistance;

    // 标识符:A818_ACRelativeAltitude
    // 名  称:飞机相对高度
    // 说  明:飞机与场景中心点相对高度（载机高度-场景中心高度），雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:46
    // 起始位:0
    UINT32 A818_ACRelativeAltitude;

    SPARE8 spare6[2];  // 保留字段

    // 标识符:A818_ViewNum
    // 名  称:视数
    // 说  明:方位向和距离向分辨率的比例，作为雷达内部参数使用。LSB=0.01，雷达独有
    // 单  位:No_Unit
    // LSB  :0.01
    // 起始字:47
    // 起始位:0
    UINT16 A818_ViewNum;

    // 标识符:A818_SATime
    // 名  称:合成孔径时间
    // 说  明:一个点的积累回波时间。与分辨率、作用距离、飞行速度等有关。3位小数，雷达独有
    // 单  位:Sec
    // LSB  :0.01
    // 起始字:48
    // 起始位:0
    UINT32 A818_SATime;

    // 标识符:A818_PRF
    // 名  称:脉冲重复频率
    // 说  明:发射重频，雷达独有
    // 单  位:Hz
    // LSB  :0.01
    // 起始字:49
    // 起始位:0
    UINT32 A818_PRF;

    // 标识符:A818_PRFCount
    // 名  称:PRF计数值
    // 说  明:当前图像对应回波数据起始PRF计数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:50
    // 起始位:0
    UINT64 A818_PRFCount;

    // 标识符:A818_DCF
    // 名  称:多普勒中心频率
    // 说  明:多普勒中心频率，雷达独有
    // 单  位:Hz
    // LSB  :1
    // 起始字:52
    // 起始位:0
    UINT32 A818_DCF;

    // 标识符:BeamStrabismusAngle
    // 名  称:波束斜视角
    // 说  明:-90~+90，雷达波束指向与航迹的夹角，前为正，后为负，雷达独有
    // 单  位:Deg
    // LSB  :0.0001
    // 起始字:53
    // 起始位:0
    INT32 BeamStrabismusAngle;

    // 标识符:BeamLevelWidth
    // 名  称:波束水平宽度
    // 说  明:[-45,45]度，波束水平面投影角度，雷达独有
    // 单  位:Deg
    // LSB  :0.00001
    // 起始字:54
    // 起始位:0
    INT32 BeamLevelWidth;

    // 标识符:A818_DataRate
    // 名  称:数据率
    // 说  明:兆比特/秒，传输峰值数据率
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:55
    // 起始位:0
    UINT32 A818_DataRate;

} IMAGE_PARAS_TRANSIT_TYPE_DEF;

// 信 号 组 标 识 符: Vel_East
// 信 号 组 名    称: 速度_东向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} VEL_EAST_TYPE_DEF;

// 信 号 组 标 识 符: ac_indicate_airspeed
// 信 号 组 名    称: 指示空速
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,2500]km/h
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} AC_INDICATE_AIRSPEED_TYPE_DEF;

// 信 号 组 标 识 符: ac_height
// 信 号 组 名    称: 载机海拔高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
//                    融合后载机海拔高度。
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_HEIGHT_TYPE_DEF;

// 信 号 组 标 识 符: ac_CDI_angle
// 信 号 组 名    称: 载机偏航角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 飞机纵轴与预定航线的夹角，相对预定航线左偏为正，
//                    LSB=0.001
//
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_CDI_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: ac_accel_Up
// 信 号 组 名    称: 飞机天向加速度_
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: -16.38～+16.38m/s2
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} AC_ACCEL_UP_TYPE_DEF;

// 信 号 组 标 识 符: ac_accel_North
// 信 号 组 名    称: 飞机北向加速度_
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: -16.38～+16.38m/s2
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} AC_ACCEL_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: ac_accel_East
// 信 号 组 名    称: 飞机东向加速度_
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: -16.38～+16.38m/s2
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} AC_ACCEL_EAST_TYPE_DEF;

// 信 号 组 标 识 符: AC_data_start
// 信 号 组 名    称: 成像开始时刻载机数据
// 信 号 组 字    数: 17
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 共有
//                    对于雷达是开始成像录取回波时刻的载机信息；对于光电是该帧图像拍照时的位置信息。
//
typedef struct
{
    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:0
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:ac_height
    // 名  称:载机海拔高度
    // 说  明:[-500,30000]m
    //        融合后载机海拔高度。
    // 单  位:
    // 起始字:2
    // 起始位:0
    AC_HEIGHT_TYPE_DEF ac_height;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:3
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:4
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:5
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_CDI_angle
    // 名  称:载机偏航角
    // 说  明:飞机纵轴与预定航线的夹角，相对预定航线左偏为正，
    //        LSB=0.001
    //
    // 单  位:
    // 起始字:6
    // 起始位:0
    AC_CDI_ANGLE_TYPE_DEF ac_CDI_angle;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //        速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_indicate_airspeed
    // 名  称:指示空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_INDICATE_AIRSPEED_TYPE_DEF ac_indicate_airspeed;

    // 标识符:Vel_East
    // 名  称:速度_东向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    VEL_EAST_TYPE_DEF Vel_East;

    // 标识符:Vel_North
    // 名  称:速度_北向
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    VEL_NORTH_TYPE_DEF Vel_North;

    // 标识符:Vel_Up
    // 名  称:速度_天向
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    VEL_UP_TYPE_DEF Vel_Up;

    // 标识符:ac_accel_East
    // 名  称:飞机东向加速度_
    // 说  明:-16.38～+16.38m/s2
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_ACCEL_EAST_TYPE_DEF ac_accel_East;

    // 标识符:ac_accel_North
    // 名  称:飞机北向加速度_
    // 说  明:-16.38～+16.38m/s2
    // 单  位:
    // 起始字:15
    // 起始位:0
    AC_ACCEL_NORTH_TYPE_DEF ac_accel_North;

    // 标识符:ac_accel_Up
    // 名  称:飞机天向加速度_
    // 说  明:-16.38～+16.38m/s2
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_ACCEL_UP_TYPE_DEF ac_accel_Up;

} AC_DATA_START_TYPE_DEF;

// 信 号 组 标 识 符: ac_roll_accel
// 信 号 组 名    称: 载机横滚角加速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]deg/s2
typedef struct
{
    // 标识符:_angular_accel
    // 名  称:_角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_accel;

} AC_ROLL_ACCEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_pitch_accel
// 信 号 组 名    称: 载机俯仰角加速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]deg/s2
typedef struct
{
    // 标识符:_angular_accel
    // 名  称:_角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_accel;

} AC_PITCH_ACCEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_heading_accel
// 信 号 组 名    称: 载机航向角加速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-1000,1000]deg/s2
typedef struct
{
    // 标识符:_angular_accel
    // 名  称:_角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_accel;

} AC_HEADING_ACCEL_TYPE_DEF;

// 信 号 组 标 识 符: AC_data_end
// 信 号 组 名    称: 成像结束时刻载机数据
// 信 号 组 字    数: 11
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 雷达独有，雷达增加了成像回波录取结束时的载机惯导信息
typedef struct
{
    // 标识符:A818_INS_No
    // 名  称:惯导序号
    // 说  明:标识该组惯导参数在当前图像中对应的列号，由载荷提供，从00001开始计数
    //        雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 A818_INS_No;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:1
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:ac_height
    // 名  称:载机海拔高度
    // 说  明:[-500,30000]m
    //        融合后载机海拔高度。
    // 单  位:
    // 起始字:3
    // 起始位:0
    AC_HEIGHT_TYPE_DEF ac_height;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:4
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_heading_accel
    // 名  称:载机航向角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:5
    // 起始位:0
    AC_HEADING_ACCEL_TYPE_DEF ac_heading_accel;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:6
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_pitch_accel
    // 名  称:载机俯仰角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_PITCH_ACCEL_TYPE_DEF ac_pitch_accel;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_roll_accel
    // 名  称:载机横滚角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_ROLL_ACCEL_TYPE_DEF ac_roll_accel;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

} AC_DATA_END_TYPE_DEF;

// 信 号 组 标 识 符: AC_ins_info
// 信 号 组 名    称: 飞机惯导信息
// 信 号 组 字    数: 30
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:A818_INS_NOW
    // 名  称:当前使用惯导
    // 说  明:飞机惯导
    //        03H-载荷惯导
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 A818_INS_NOW;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:A818_INS_GroupStatus
    // 名  称:惯导组合状态
    // 说  明:0~3位：惯导1组合状态
    //        4~7位：惯导2组合状态
    //        8~11位：惯导3组合状态
    //
    //        0=无效（默认）
    //        1=惯性/RTK BDS组合
    //        2=惯性/RTD BDS组合
    //        3=惯性/单点BDS组合
    //        4=惯性/RTD GPS组合
    //        5=惯性/单点 GPS组合
    //        6=惯性/ VMC综合卫星组合
    //        7=惯性/毫米波组合
    //        8=惯性/飞行辅助引导设备组合
    //        9=惯性/SBAS BDS组合
    //        10=惯性/天文组合
    //        11=惯性/地景组合
    //        12=惯性/精定修正
    //        13=惯性/大气组合
    //        14=纯惯性（断开修正）
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 A818_INS_GroupStatus;

    // 标识符:AC_data_start
    // 名  称:成像开始时刻载机数据
    // 说  明:共有
    //        对于雷达是开始成像录取回波时刻的载机信息；对于光电是该帧图像拍照时的位置信息。
    //
    // 单  位:
    // 起始字:2
    // 起始位:0
    AC_DATA_START_TYPE_DEF AC_data_start;

    // 标识符:AC_data_end
    // 名  称:成像结束时刻载机数据
    // 说  明:雷达独有，雷达增加了成像回波录取结束时的载机惯导信息
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_DATA_END_TYPE_DEF AC_data_end;

} AC_INS_INFO_TYPE_DEF;

// 信 号 组 标 识 符: A818_Image_common_paras
// 信 号 组 名    称: 图像任务信息
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:A818_MissionCode
    // 名  称:任务代号
    // 说  明:0000～9999，任务规划系统规划任务时确定。取自任务规划加载，用于区分哪个架次、哪次任务。后续数据分类整理可能用到，机上图像处理不用。该信号雷达和光电共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 A818_MissionCode;

    // 标识符:message_header
    // 名  称:图像信息包头
    // 说  明:该信号表示注释信息包头。雷达和光电系统共有,用于区分是来自哪个载荷的图像。
    //        光电：7E7E
    //        雷达：7E7F
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 message_header;

    // 标识符:A818_AC_No
    // 名  称:飞机号
    // 说  明:0000～9999，飞机编号，缺省值00，与测控联网后从测控链获取。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 A818_AC_No;

    // 标识符:A818_AC_BatchNo
    // 名  称:飞机批号
    // 说  明:保留，默认取00。该信号非必须，共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 A818_AC_BatchNo;

    // 标识符:A818_AC_TYPE
    // 名  称:飞行器类型
    // 说  明:暂定缺省置0X4B(侦察型)，预警型待定。与测控联网后从测控取。
    //        该信号雷达与光电共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 A818_AC_TYPE;

    UINT32 spare2 : 10;  // 保留字段
    // 标识符:A818_SideViewDirection
    // 名  称:雷达侧视方向
    // 说  明:雷达专用，表示雷达侧视方向。条带SAR模式或SAR-GMTI模式下：1=左侧视、2=右侧视；其它模式填0
    // 单  位:No_Unit
    // 起始字:2
    // 起始位:20
    UINT32 A818_SideViewDirection : 2;

    // 标识符:location_presise
    // 名  称:定位精度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:17
    UINT32 location_presise : 3;

    // 标识符:IR_pole_type
    // 名  称:极化类型
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 IR_pole_type : 1;

    // 标识符:scan_direct_tag
    // 名  称:扫描方向标志
    // 说  明:顺航向从左到右为正扫，反之为反扫。光电专用
    // 单  位:
    // 起始字:2
    // 起始位:15
    UINT32 scan_direct_tag : 1;

    // 标识符:A818_ImageBitDepth
    // 名  称:图像位深
    // 说  明:1、8、12、16、32等
    // 单  位:No_Unit
    // 起始字:2
    // 起始位:12
    UINT32 A818_ImageBitDepth : 3;

    // 标识符:Payload_Factory
    // 名  称:载荷厂家
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 Payload_Factory : 4;

    UINT32 spare1 : 1;  // 保留字段
    // 标识符:Payload_type
    // 名  称:载荷类型
    // 说  明:载荷类型（雷达置3，光电按照枚举值定义分类填写）
    // 单  位:
    // 起始字:2
    // 起始位:3
    UINT32 Payload_type : 4;

    // 标识符:transitmit_type
    // 名  称:传输方式_3bit
    // 说  明:载荷默认填0, AIMP根据实时传输模式填1或2（例如：用于地面图像实时显示或对于断网后指定图像的传输）
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 transitmit_type : 3;

    // 标识符:A818_MissionStageNo
    // 名  称:任务段号
    // 说  明:00~255，第几段任务，需要任务机下发，共用。来自于系统获取的任务阶段、航段、任务区
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:24
    UINT32 A818_MissionStageNo : 8;

    // 标识符:device_work_mode
    // 名  称:设备工作模式
    // 说  明:共用，对于侦察雷达表示雷达成像模式；对于综合光电表示相机工作模式。
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 device_work_mode : 8;

    // 标识符:A818_ImageCompressionRatio
    // 名  称:图像压缩比
    // 说  明:000～9999，载荷默认填0，由AIMP下传时填写
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 A818_ImageCompressionRatio : 16;

} A818_IMAGE_COMMON_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: VMS_DataBlock_Valid_3
// 信 号 组 名    称: 飞管数据包有效性3
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:yes_no
    // 名  称:YES_NO
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 yes_no;

} VMS_DATABLOCK_VALID_3_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data_C
// 信 号 组 名    称: 大气导航数据_C
// 信 号 组 字    数: 26
// 信 号 组 数组长度: 1
// 信 号 组 说    明: “飞管数据包有效性”根据SVPC、心跳原则判断。
//                    “飞管通道有效性”根据CHV判断。
typedef struct
{
    // 标识符:VMS_Chn_Valid
    // 名  称:飞管通道有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VMS_CHN_VALID_TYPE_DEF VMS_Chn_Valid;

    // 标识符:VMS_DataBlock_Valid_3
    // 名  称:飞管数据包有效性3
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VMS_DATABLOCK_VALID_3_TYPE_DEF VMS_DataBlock_Valid_3;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:2
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:air_nav_data_validity
    // 名  称:大气导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AIR_NAV_DATA_VALIDITY_TYPE_DEF air_nav_data_validity;

    // 标识符:ac_true_aoa
    // 名  称:载机真攻角
    // 说  明:[-20,60]deg
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AOA_TYPE_DEF ac_true_aoa;

    // 标识符:ac_true_side_slip_angle
    // 名  称:载机真侧滑角
    // 说  明:[-20,20]deg
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF ac_true_side_slip_angle;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_cal_air_speed
    // 名  称:载机校准空速
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_CAL_AIR_SPEED_TYPE_DEF ac_cal_air_speed;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

    // 标识符:ac_pressure_alt_rate
    // 名  称:载机气压高度变化率
    // 说  明:[-300,300]m/s
    //        即爬升率
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate;

    // 标识符:baro_setting
    // 名  称:场压装订
    // 说  明:[54,107.5]kPa
    // 单  位:
    // 起始字:15
    // 起始位:0
    BARO_SETTING_TYPE_DEF baro_setting;

    // 标识符:baro_setting_alt
    // 名  称:场压装订高度
    // 说  明:[-500,5000]m
    // 单  位:
    // 起始字:16
    // 起始位:0
    BARO_SETTING_ALT_TYPE_DEF baro_setting_alt;

    // 标识符:AC_pressure_alt
    // 名  称:载机气压高度
    // 说  明:[-500,22800]m
    //        转发的大气高度
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_PRESSURE_ALT_TYPE_DEF AC_pressure_alt;

    // 标识符:ac_baro_alt
    // 名  称:载机气压参考高度
    // 说  明:[-5500,23300]m
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_BARO_ALT_TYPE_DEF ac_baro_alt;

    // 标识符:ac_total_temperature
    // 名  称:载机大气总温
    // 说  明:[-70,350])Cel 即[203.15,623.15]Kel
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_TOTAL_TEMPERATURE_TYPE_DEF ac_total_temperature;

    // 标识符:ac_free_airtemp
    // 名  称:载机大气静温
    // 说  明:[173.15,373.15]kel
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_FREE_AIRTEMP_TYPE_DEF ac_free_airtemp;

    // 标识符:ac_pressure_ratio
    // 名  称:载机大气压力比
    // 说  明:[0.033,1.1]
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_PRESSURE_RATIO_TYPE_DEF ac_pressure_ratio;

    // 标识符:ac_air_density_ratio
    // 名  称:载机大气密度比
    // 说  明:[0.0355,1.045]
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_AIR_DENSITY_RATIO_TYPE_DEF ac_air_density_ratio;

    // 标识符:true_static_pressure
    // 名  称:真实静压
    // 说  明:[1.7,108.4]kPa
    // 单  位:
    // 起始字:23
    // 起始位:0
    TRUE_STATIC_PRESSURE_TYPE_DEF true_static_pressure;

    // 标识符:cokpit_differential_pressure
    // 名  称:座舱压力差
    // 说  明:[-8,80]kPa
    // 单  位:
    // 起始字:24
    // 起始位:0
    COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF cokpit_differential_pressure;

    // 标识符:cokpit_alt
    // 名  称:座舱高度
    // 说  明:[-2000,20567]m
    // 单  位:
    // 起始字:25
    // 起始位:0
    COKPIT_ALT_TYPE_DEF cokpit_alt;

} AIR_NAV_DATA_C_TYPE_DEF;

// 信 号 组 标 识 符: VMS_DataBlock_Valid_1
// 信 号 组 名    称: 飞管数据包有效性1
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:yes_no
    // 名  称:YES_NO
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 yes_no;

} VMS_DATABLOCK_VALID_1_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data_A
// 信 号 组 名    称: 大气导航数据_A
// 信 号 组 字    数: 26
// 信 号 组 数组长度: 1
// 信 号 组 说    明: “飞管数据包有效性”根据SVPC、心跳原则判断。
//                    “飞管通道有效性”根据CHV判断。
typedef struct
{
    // 标识符:VMS_Chn_Valid
    // 名  称:飞管通道有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VMS_CHN_VALID_TYPE_DEF VMS_Chn_Valid;

    // 标识符:VMS_DataBlock_Valid_1
    // 名  称:飞管数据包有效性1
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VMS_DATABLOCK_VALID_1_TYPE_DEF VMS_DataBlock_Valid_1;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:2
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:air_nav_data_validity
    // 名  称:大气导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AIR_NAV_DATA_VALIDITY_TYPE_DEF air_nav_data_validity;

    // 标识符:ac_true_aoa
    // 名  称:载机真攻角
    // 说  明:[-20,60]deg
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AOA_TYPE_DEF ac_true_aoa;

    // 标识符:ac_true_side_slip_angle
    // 名  称:载机真侧滑角
    // 说  明:[-20,20]deg
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF ac_true_side_slip_angle;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_cal_air_speed
    // 名  称:载机校准空速
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_CAL_AIR_SPEED_TYPE_DEF ac_cal_air_speed;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

    // 标识符:ac_pressure_alt_rate
    // 名  称:载机气压高度变化率
    // 说  明:[-300,300]m/s
    //        即爬升率
    // 单  位:
    // 起始字:14
    // 起始位:0
    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate;

    // 标识符:baro_setting
    // 名  称:场压装订
    // 说  明:[54,107.5]kPa
    // 单  位:
    // 起始字:15
    // 起始位:0
    BARO_SETTING_TYPE_DEF baro_setting;

    // 标识符:baro_setting_alt
    // 名  称:场压装订高度
    // 说  明:[-500,5000]m
    // 单  位:
    // 起始字:16
    // 起始位:0
    BARO_SETTING_ALT_TYPE_DEF baro_setting_alt;

    // 标识符:AC_pressure_alt
    // 名  称:载机气压高度
    // 说  明:[-500,22800]m
    //        转发的大气高度
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_PRESSURE_ALT_TYPE_DEF AC_pressure_alt;

    // 标识符:ac_baro_alt
    // 名  称:载机气压参考高度
    // 说  明:[-5500,23300]m
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_BARO_ALT_TYPE_DEF ac_baro_alt;

    // 标识符:ac_total_temperature
    // 名  称:载机大气总温
    // 说  明:[-70,350])Cel 即[203.15,623.15]Kel
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_TOTAL_TEMPERATURE_TYPE_DEF ac_total_temperature;

    // 标识符:ac_free_airtemp
    // 名  称:载机大气静温
    // 说  明:[173.15,373.15]kel
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_FREE_AIRTEMP_TYPE_DEF ac_free_airtemp;

    // 标识符:ac_pressure_ratio
    // 名  称:载机大气压力比
    // 说  明:[0.033,1.1]
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_PRESSURE_RATIO_TYPE_DEF ac_pressure_ratio;

    // 标识符:ac_air_density_ratio
    // 名  称:载机大气密度比
    // 说  明:[0.0355,1.045]
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_AIR_DENSITY_RATIO_TYPE_DEF ac_air_density_ratio;

    // 标识符:true_static_pressure
    // 名  称:真实静压
    // 说  明:[1.7,108.4]kPa
    // 单  位:
    // 起始字:23
    // 起始位:0
    TRUE_STATIC_PRESSURE_TYPE_DEF true_static_pressure;

    // 标识符:cokpit_differential_pressure
    // 名  称:座舱压力差
    // 说  明:[-8,80]kPa
    // 单  位:
    // 起始字:24
    // 起始位:0
    COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF cokpit_differential_pressure;

    // 标识符:cokpit_alt
    // 名  称:座舱高度
    // 说  明:[-2000,20567]m
    // 单  位:
    // 起始字:25
    // 起始位:0
    COKPIT_ALT_TYPE_DEF cokpit_alt;

} AIR_NAV_DATA_A_TYPE_DEF;

// 信 号 组 标 识 符: SL_correlate_matrix
// 信 号 组 名    称: 射击列表目标关联矩阵
// 信 号 组 字    数: 81
// 信 号 组 数组长度: 5
// 信 号 组 说    明: 目标关联矩阵
typedef struct
{
    // 标识符:formation_fused_tgt_ID
    // 名  称:编队融合目标编号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 formation_fused_tgt_ID;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 platform_fused_tgt_ID;

    // 标识符:tgt_dis_ID
    // 名  称:目标显示编号
    // 说  明:融合输出的目标显示编号，用两位表示。
    //        显示使用数字1~9、字母a~z组合表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 tgt_dis_ID;

    // 标识符:RDR_track_number
    // 名  称:RDR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT16 RDR_track_number;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 IR_track_number;

    // 标识符:EW_tgt_no
    // 名  称:EW目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 EW_tgt_no;

    // 标识符:ADS_B_IN_target_id
    // 名  称:ADS_B_IN目标编号
    // 说  明:即S模式地址码,全球唯一编码
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 ADS_B_IN_target_id;

    // 标识符:SAT_link_tgt_id
    // 名  称:卫通链目标编识号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 SAT_link_tgt_id;

    // 标识符:VU_track_number
    // 名  称:VU链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:6
    // 起始位:0
    VU_TRACK_NUMBER_TYPE_DEF VU_track_number[8];

    // 标识符:JIDS_track_number
    // 名  称:JIDS链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:22
    // 起始位:0
    JIDS_TRACK_NUMBER_TYPE_DEF JIDS_track_number[8];

    // 标识符:IFDL_track_number
    // 名  称:IFDL链目标编号
    // 说  明:编号及编识号为0时，表示链上无该目标。
    // 单  位:
    // 起始字:38
    // 起始位:0
    IFDL_TRACK_NUMBER_TYPE_DEF IFDL_track_number[10];

    SPARE8 spare2[2];  // 保留字段

    // 标识符:IBS_tgt_ID
    // 名  称:IBS目标编号
    // 说  明:0:NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:58
    // 起始位:0
    UINT16 IBS_tgt_ID;

    // 标识符:ADI_ID
    // 名  称:ADI标识号
    // 说  明:[0-524287]
    // 单  位:
    // LSB  :1
    // 起始字:59
    // 起始位:0
    UINT32 ADI_ID;

    SPARE8 spare3[2];  // 保留字段

    // 标识符:CRSM_tgt_ID
    // 名  称:通侦目标编号
    // 说  明:0：NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:60
    // 起始位:0
    UINT16 CRSM_tgt_ID;

    SPARE8 spare5[2];  // 保留字段

    // 标识符:DAS_tgt_no
    // 名  称:DAS目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:61
    // 起始位:8
    UINT8 DAS_tgt_no;

    SPARE8 spare4;  // 保留字段

    SPARE8 spare6[2];  // 保留字段

    // 标识符:EWS2_tgt_no
    // 名  称:选装电子战目标编号
    // 说  明:EW2M对选装电子战目标分配的统一编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:62
    // 起始位:0
    UINT16 EWS2_tgt_no;

    // 标识符:IIPM_tgt_no
    // 名  称:图像情报目标编号
    // 说  明:IIPM对图像情报目标分配的统一编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:63
    // 起始位:16
    UINT16 IIPM_tgt_no;

    SPARE8 spare7[2];  // 保留字段

    // 标识符:ais_target_id
    // 名  称:AIS目标编号
    // 说  明:MMSI编码，全球唯一编码。0～999999999
    // 单  位:
    // LSB  :1
    // 起始字:64
    // 起始位:0
    UINT32 ais_target_id;

    SPARE8 spare8[2];  // 保留字段

    // 标识符:LOADING_tgt_ID
    // 名  称:加载目标编号
    // 说  明:0：NA
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:65
    // 起始位:0
    UINT16 LOADING_tgt_ID;

    SPARE32 spare9[13];  // 保留字段

    UINT32 spare10 : 24;  // 保留字段
    // 标识符:datalink_contribute_flag
    // 名  称:链路贡献标识
    // 说  明:按位定义各链路对射击列表目标的贡献，如：
    //        VU有贡献，值=1；
    //        VU和IFDL都有三维目标贡献，值=1+4。
    // 单  位:
    // 起始字:79
    // 起始位:0
    UINT32 datalink_contribute_flag : 8;

    SPARE8 spare11[3];  // 保留字段

    // 标识符:New_Target_ID
    // 名  称:新目标标识
    // 说  明:用于TGFA向TGFI传输目标信息时，针对每个目标是否新目标的计数器，当次发送的目标为新目标，则计数器+1。计数到255后再从1开始。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:80
    // 起始位:0
    UINT8 New_Target_ID;

} SL_CORRELATE_MATRIX_TYPE_DEF;

// 信 号 组 标 识 符: tgt_TOA
// 信 号 组 名    称: 目标TOA
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 本机测量目标的TOA
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} TGT_TOA_TYPE_DEF;

// 信 号 组 标 识 符: tgt_el
// 信 号 组 名    称: 目标俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 范围：[-180,180]
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_EL_TYPE_DEF;

// 信 号 组 标 识 符: tgt_az
// 信 号 组 名    称: 目标方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 范围：[-180,180]
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: rnav_measure_paras_validity
// 信 号 组 名    称: 相对导航测量参数有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1;  // 保留字段

    // 标识符:validity_tgt_el
    // 名  称:有效性_目标俯仰
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_tgt_el;

    // 标识符:validity_tgt_az
    // 名  称:有效性_目标方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_tgt_az;

    // 标识符:validity_tgt_TOA
    // 名  称:有效性_目标TOA
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_tgt_TOA;

} RNAV_MEASURE_PARAS_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: AC_IFDL_slant_distance
// 信 号 组 名    称: 载机IFDL斜距
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 范围：[-180,180]
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} AC_IFDL_SLANT_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: rnav_measure_paras
// 信 号 组 名    称: 相对导航测量参数
// 信 号 组 字    数: 8
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 本机测量目标的TOA、相对方位角、相对俯仰角
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:rnav_measure_paras_validity
    // 名  称:相对导航测量参数有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    RNAV_MEASURE_PARAS_VALIDITY_TYPE_DEF rnav_measure_paras_validity;

    // 标识符:tgt_TOA
    // 名  称:目标TOA
    // 说  明:本机测量目标的TOA
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_TOA_TYPE_DEF tgt_TOA;

    // 标识符:tgt_az
    // 名  称:目标方位
    // 说  明:范围：[-180,180]
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_AZ_TYPE_DEF tgt_az;

    // 标识符:tgt_el
    // 名  称:目标俯仰
    // 说  明:范围：[-180,180]
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_EL_TYPE_DEF tgt_el;

    // 标识符:AC_IFDL_slant_distance
    // 名  称:载机IFDL斜距
    // 说  明:范围：[-180,180]
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_IFDL_SLANT_DISTANCE_TYPE_DEF AC_IFDL_slant_distance;

} RNAV_MEASURE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: link_member_nav_paras_validity_iFDL
// 信 号 组 名    称: 成员导航参数有效性_IFDL
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_roll_angle;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_height
    // 名  称:有效性_海拔高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_height;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_position;

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_vel_north;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    // 标识符:validity_GNSS_inertial_ADS_alt
    // 名  称:有效性_惯性卫星大气高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    BOOL_8 validity_GNSS_inertial_ADS_alt;

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_accel_north;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_mach
    // 名  称:有效性_马赫数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_mach;

    // 标识符:validity_above_ground_height
    // 名  称:有效性_地形相对高度
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_above_ground_height;

} LINK_MEMBER_NAV_PARAS_VALIDITY_IFDL_TYPE_DEF;

// 信 号 组 标 识 符: above_ground_height
// 信 号 组 名    称: 地形相对高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
//                    相对地形高度。
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} ABOVE_GROUND_HEIGHT_TYPE_DEF;

// 信 号 组 标 识 符: member_nav_paras_IFDL
// 信 号 组 名    称: 成员导航参数_IFDL
// 信 号 组 字    数: 19
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:link_member_nav_paras_validity_iFDL
    // 名  称:成员导航参数有效性_IFDL
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    LINK_MEMBER_NAV_PARAS_VALIDITY_IFDL_TYPE_DEF link_member_nav_paras_validity_iFDL;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:4
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:ac_height
    // 名  称:载机海拔高度
    // 说  明:[-500,30000]m
    //        融合后载机海拔高度。
    // 单  位:
    // 起始字:6
    // 起始位:0
    AC_HEIGHT_TYPE_DEF ac_height;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:13
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:AC_GNSS_inertial_ADS_alt
    // 名  称:载机惯性卫星大气高度
    // 说  明:[-2500,30000]m
    //        INS/卫星/ADS组合高度
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_GNSS_INERTIAL_ADS_ALT_TYPE_DEF AC_GNSS_inertial_ADS_alt;

    // 标识符:above_ground_height
    // 名  称:地形相对高度
    // 说  明:[-500,30000]m
    //        相对地形高度。
    // 单  位:
    // 起始字:17
    // 起始位:0
    ABOVE_GROUND_HEIGHT_TYPE_DEF above_ground_height;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

} MEMBER_NAV_PARAS_IFDL_TYPE_DEF;

// 信 号 组 标 识 符: member_PPLI_info_IFDL
// 信 号 组 名    称: 成员精确定位与识别信息_IFDL
// 信 号 组 字    数: 24
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:tgt_type
    // 名  称:平台类型
    // 说  明:各类型的定义在ICD文件中用表格形式明确。
    //        根据平台环境类别确定平台类型定义
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 tgt_type : 8;

    // 标识符:pilot_no
    // 名  称:飞行员代码
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 pilot_no : 16;

    // 标识符:location_quality
    // 名  称:地理位置质量
    // 说  明:[0,15]
    //        0：大于5510m
    //        1：不大于5510m
    //        2：不大于2755m
    //        3：不大于1378m
    //        4：不大于689m
    //        5：不大于488m
    //        6：不大于344m
    //        7：不大于244m
    //        8：不大于172m
    //        9：不大于122m
    //        10：不大于86m
    //        11：不大于61m
    //        12：不大于43m
    //        13：不大于30m
    //        14：不大于22m
    //        15：不大于15m
    //        16：不大于10.5m
    //        17：不大于7.3m
    //        18：不大于5.1m
    //        19：不大于3.6m
    //        20：不大于2.5m
    //        21：不大于1.7m
    //        22：不大于1.2m
    //        23：不大于0.9m
    //        24：不大于0.6m
    //        25：不大于0.4m
    //        26：不大于0.3m
    //        27：不大于0.2m
    //        28：不大于0.15m
    //        29：不大于0.1m
    //        30：不大于0.07m
    //        31：无报告
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:24
    UINT32 location_quality : 8;

    // 标识符:location_source
    // 名  称:位置来源
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 location_source : 8;

    // 标识符:tgt_model
    // 名  称:平台型号
    // 说  明:各型号的定义在ICD文件中用表格形式明确。
    //        定义如下：
    //        95-J20
    //        121-歼20ISC
    //        122-J20A
    //        150-攻-11
    //
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 tgt_model : 16;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:altitude_quality
    // 名  称:高度质量
    // 说  明:[0,15]
    //        0：大于5510m
    //        1：不大于5510m
    //        2：不大于2755m
    //        3：不大于1378m
    //        4：不大于689m
    //        5：不大于488m
    //        6：不大于344m
    //        7：不大于244m
    //        8：不大于172m
    //        9：不大于122m
    //        10：不大于86m
    //        11：不大于61m
    //        12：不大于43m
    //        13：不大于30m
    //        14：不大于22m
    //        15：不大于15m
    //        16：不大于10.5m
    //        17：不大于7.3m
    //        18：不大于5.1m
    //        19：不大于3.6m
    //        20：不大于2.5m
    //        21：不大于1.7m
    //        22：不大于1.2m
    //        23：不大于0.9m
    //        24：不大于0.6m
    //        25：不大于0.4m
    //        26：不大于0.3m
    //        27：不大于0.2m
    //        28：不大于0.15m
    //        29：不大于0.1m
    //        30：不大于0.07m
    //        31：无报告
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT8 altitude_quality;

    // 标识符:member_nav_paras_IFDL
    // 名  称:成员导航参数_IFDL
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    MEMBER_NAV_PARAS_IFDL_TYPE_DEF member_nav_paras_IFDL;

} MEMBER_PPLI_INFO_IFDL_TYPE_DEF;

// 信 号 组 标 识 符: link_message_tr_time
// 信 号 组 名    称: 消息收发时间
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
typedef struct
{
    // 标识符:time_link
    // 名  称:时间_链路时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT64 time_link;

    // 标识符:time_missiontime
    // 名  称:时间_任务时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT64 time_missiontime;

} LINK_MESSAGE_TR_TIME_TYPE_DEF;

// 信 号 组 标 识 符: link_message_source_destination
// 信 号 组 名    称: 消息源目的端
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
typedef struct
{
    // 标识符:member_no
    // 名  称:成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 member_no;

} LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF;

// 信 号 组 标 识 符: req_publisher_ID
// 信 号 组 名    称: 请求发布者ID
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 发布活动请求者的ID号。
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

} REQ_PUBLISHER_ID_TYPE_DEF;

// 信 号 组 标 识 符: longitude
// 信 号 组 名    称: 经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: (-180,180]deg
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: latitude
// 信 号 组 名    称: 纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: altitude
// 信 号 组 名    称: 高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} ALTITUDE_TYPE_DEF;

// 信 号 组 标 识 符: spi_location
// 信 号 组 名    称: SPI点位置
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:validity_location
    // 名  称:位置有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_location;

    // 标识符:longitude
    // 名  称:经度
    // 说  明:(-180,180]deg
    // 单  位:
    // 起始字:1
    // 起始位:0
    LONGITUDE_TYPE_DEF longitude;

    // 标识符:latitude
    // 名  称:纬度
    // 说  明:[-90,90]deg
    // 单  位:
    // 起始字:2
    // 起始位:0
    LATITUDE_TYPE_DEF latitude;

    // 标识符:altitude
    // 名  称:高度
    // 说  明:[-500,30000]m
    // 单  位:
    // 起始字:3
    // 起始位:0
    ALTITUDE_TYPE_DEF altitude;

} SPI_LOCATION_TYPE_DEF;

// 信 号 组 标 识 符: Servo_Search_Range
// 信 号 组 名    称: IRST搜索宽度范围
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:RollPosAngle
    // 名  称:消旋角度
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    INT16 RollPosAngle;

    // 标识符:SchWidthEl
    // 名  称:搜索俯仰宽度
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT8 SchWidthEl;

    // 标识符:SchWidthAz
    // 名  称:搜索方位宽度
    // 说  明:
    // 单  位:Deg
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 SchWidthAz;

} SERVO_SEARCH_RANGE_TYPE_DEF;

// 信 号 组 标 识 符: sensor_LOS_el
// 信 号 组 名    称: 传感器LOS俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SENSOR_LOS_EL_TYPE_DEF;

// 信 号 组 标 识 符: sensor_LOS_az
// 信 号 组 名    称: 传感器LOS方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SENSOR_LOS_AZ_TYPE_DEF;

// 信 号 组 标 识 符: sensor_los_geo
// 信 号 组 名    称: 地理系_传感器LOS
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:data_valid
    // 名  称:数据有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 data_valid;

    // 标识符:sensor_LOS_az
    // 名  称:传感器LOS方位
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    SENSOR_LOS_AZ_TYPE_DEF sensor_LOS_az;

    // 标识符:sensor_LOS_el
    // 名  称:传感器LOS俯仰
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    SENSOR_LOS_EL_TYPE_DEF sensor_LOS_el;

} SENSOR_LOS_GEO_TYPE_DEF;

// 信 号 组 标 识 符: irst_tgt_det_paras
// 信 号 组 名    称: 光雷目标探测参数
// 信 号 组 字    数: 8
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:irst_tgt_acq_mode
    // 名  称:IRST目标获取方式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 irst_tgt_acq_mode : 8;

    // 标识符:Servo_Search_Range
    // 名  称:IRST搜索宽度范围
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    SERVO_SEARCH_RANGE_TYPE_DEF Servo_Search_Range;

    // 标识符:servo_elevation
    // 名  称:IRST搜索/指示中心俯仰
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:2
    // 起始位:16
    INT16 servo_elevation;

    // 标识符:servo_azimuth
    // 名  称:IRST搜索/指示中心方位
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:2
    // 起始位:0
    INT16 servo_azimuth;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:frame_end
    // 名  称:IRST场结束有效位
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 frame_end;

    // 标识符:frame_bgn
    // 名  称:IRST场开始有效位
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 frame_bgn;

    // 标识符:sensor_los_geo
    // 名  称:地理系_传感器LOS
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    SENSOR_LOS_GEO_TYPE_DEF sensor_los_geo;

    // 标识符:SPARE
    // 名  称:SPARE
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:7
    // 起始位:0
    UINT32 SPARE;

} IRST_TGT_DET_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_slant_distance
// 信 号 组 名    称: 目标斜距
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_SLANT_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_pitch_measured
// 信 号 组 名    称: IR目标测量俯仰_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_PITCH_MEASURED_TYPE_DEF;

// 信 号 组 标 识 符: tgt_bearing_measured
// 信 号 组 名    称: IR目标测量方位_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_BEARING_MEASURED_TYPE_DEF;

// 信 号 组 标 识 符: tgt_bearing_average
// 信 号 组 名    称: IR目标方位均值_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_BEARING_AVERAGE_TYPE_DEF;

// 信 号 组 标 识 符: member_no_and_irst_tgt_ID
// 信 号 组 名    称: 协同成员编号及光雷目标编号
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 IR_track_number;

    // 标识符:I_member_no
    // 名  称:I链成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 I_member_no;

} MEMBER_NO_AND_IRST_TGT_ID_TYPE_DEF;

// 信 号 组 标 识 符: ir_tgt_pitch_average
// 信 号 组 名    称: IR目标俯仰均值_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} IR_TGT_PITCH_AVERAGE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_pitch
// 信 号 组 名    称: 目标俯仰_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_PITCH_TYPE_DEF;

// 信 号 组 标 识 符: tgt_elevation
// 信 号 组 名    称: 目标俯仰_机体系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_ELEVATION_TYPE_DEF;

// 信 号 组 标 识 符: tgt_bearing
// 信 号 组 名    称: 目标方位_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_BEARING_TYPE_DEF;

// 信 号 组 标 识 符: tgt_azimuth
// 信 号 组 名    称: 目标方位_机体系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_AZIMUTH_TYPE_DEF;

// 信 号 组 标 识 符: IR_angular_paras
// 信 号 组 名    称: IR目标角度信息
// 信 号 组 字    数: 9
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_tgt_el
    // 名  称:有效性_目标俯仰
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_tgt_el;

    // 标识符:validity_tgt_az
    // 名  称:有效性_目标方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_tgt_az;

    // 标识符:tgt_azimuth
    // 名  称:目标方位_机体系
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_AZIMUTH_TYPE_DEF tgt_azimuth;

    // 标识符:tgt_elevation
    // 名  称:目标俯仰_机体系
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_ELEVATION_TYPE_DEF tgt_elevation;

    // 标识符:tgt_bearing
    // 名  称:目标方位_地理系
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_BEARING_TYPE_DEF tgt_bearing;

    // 标识符:tgt_pitch
    // 名  称:目标俯仰_地理系
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_PITCH_TYPE_DEF tgt_pitch;

    // 标识符:IR_track_AZ_angularvelocity
    // 名  称:目标方位角速度
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.0001
    // 起始字:5
    // 起始位:0
    INT32 IR_track_AZ_angularvelocity;

    // 标识符:IR_track_EL_angularvelocity
    // 名  称:目标俯仰角速度
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.0001
    // 起始字:6
    // 起始位:0
    INT32 IR_track_EL_angularvelocity;

    // 标识符:IR_track_AZ_angaccel
    // 名  称:目标方位角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.0001
    // 起始字:7
    // 起始位:0
    INT32 IR_track_AZ_angaccel;

    // 标识符:IR_track_EL_angaccel
    // 名  称:目标俯仰角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.0001
    // 起始字:8
    // 起始位:0
    INT32 IR_track_EL_angaccel;

} IR_ANGULAR_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: irst_cooperation_track_paras
// 信 号 组 名    称: 光雷协同航迹目标参数
// 信 号 组 字    数: 32
// 信 号 组 数组长度: 10
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:ir_tgt_track_flag
    // 名  称:IR目标航迹标识
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 ir_tgt_track_flag : 8;

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 IR_track_number : 16;

    // 标识符:member_no_and_irst_tgt_ID
    // 名  称:协同成员编号及光雷目标编号
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    MEMBER_NO_AND_IRST_TGT_ID_TYPE_DEF member_no_and_irst_tgt_ID;

    // 标识符:tgt_bearing_measured
    // 名  称:IR目标测量方位_地理系
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_BEARING_MEASURED_TYPE_DEF tgt_bearing_measured;

    // 标识符:tgt_pitch_measured
    // 名  称:IR目标测量俯仰_地理系
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_PITCH_MEASURED_TYPE_DEF tgt_pitch_measured;

    // 标识符:tgt_bearing_average
    // 名  称:IR目标方位均值_地理系
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_BEARING_AVERAGE_TYPE_DEF tgt_bearing_average;

    // 标识符:ir_tgt_pitch_average
    // 名  称:IR目标俯仰均值_地理系
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    IR_TGT_PITCH_AVERAGE_TYPE_DEF ir_tgt_pitch_average;

    // 标识符:IR_angular_paras
    // 名  称:IR目标角度信息
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    IR_ANGULAR_PARAS_TYPE_DEF IR_angular_paras;

    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:17
    // 起始位:16
    UINT16 platform_fused_tgt_ID;

    SPARE8 spare2;  // 保留字段

    // 标识符:validity_tgt_distance
    // 名  称:有效性_目标距离
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    BOOL_8 validity_tgt_distance;

    // 标识符:tgt_slant_distance
    // 名  称:目标斜距
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    TGT_SLANT_DISTANCE_TYPE_DEF tgt_slant_distance;

    // 标识符:Target_Size
    // 名  称:像素尺寸
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:19
    // 起始位:16
    UINT16 Target_Size;

    // 标识符:Target_GrayValue
    // 名  称:目标灰度/信噪比
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:19
    // 起始位:0
    UINT16 Target_GrayValue;

    // 标识符:ir_tgt_miss_count
    // 名  称:IR目标量测丢失次数
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:16
    UINT16 ir_tgt_miss_count;

    // 标识符:ir_target_confidence
    // 名  称:IR航迹置信度
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:0
    UINT16 ir_target_confidence;

    // 标识符:ir_inviable_paras
    // 名  称:IR不变量
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:21
    // 起始位:16
    UINT16 ir_inviable_paras;

    // 标识符:ir_dihedral_angle
    // 名  称:IR二面角
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:21
    // 起始位:0
    UINT16 ir_dihedral_angle;

    // 标识符:test_data1
    // 名  称:测试数据1
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:22
    // 起始位:0
    INT32 test_data1;

    // 标识符:test_data2
    // 名  称:测试数据2
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:23
    // 起始位:0
    INT32 test_data2;

    // 标识符:test_data3
    // 名  称:测试数据3
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:24
    // 起始位:0
    INT32 test_data3;

    // 标识符:test_data4
    // 名  称:测试数据4
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:25
    // 起始位:0
    INT32 test_data4;

    // 标识符:test_data5
    // 名  称:测试数据5
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:26
    // 起始位:0
    INT32 test_data5;

    // 标识符:test_data6
    // 名  称:测试数据6
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:27
    // 起始位:0
    INT32 test_data6;

    // 标识符:test_data7
    // 名  称:测试数据7
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:28
    // 起始位:0
    INT32 test_data7;

    // 标识符:test_data8
    // 名  称:测试数据8
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:29
    // 起始位:0
    INT32 test_data8;

    // 标识符:test_data9
    // 名  称:测试数据9
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:30
    // 起始位:0
    INT32 test_data9;

    // 标识符:test_data10
    // 名  称:测试数据10
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:31
    // 起始位:0
    INT32 test_data10;

} IRST_COOPERATION_TRACK_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: reproduce_date
// 信 号 组 名    称: 返修生产日期
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:HWConfig_PD_Year
    // 名  称:生产日期-年
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 HWConfig_PD_Year;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:HWConfig_PD_Day
    // 名  称:生产日期-日
    // 说  明:取值范围：1~31
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 HWConfig_PD_Day;

    // 标识符:HWConfig_PD_Mon
    // 名  称:生产日期-月
    // 说  明:取值范围：1~12
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 HWConfig_PD_Mon;

} REPRODUCE_DATE_TYPE_DEF;

// 信 号 组 标 识 符: produce_date
// 信 号 组 名    称: 生产日期
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:HWConfig_PD_Year
    // 名  称:生产日期-年
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 HWConfig_PD_Year;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:HWConfig_PD_Day
    // 名  称:生产日期-日
    // 说  明:取值范围：1~31
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 HWConfig_PD_Day;

    // 标识符:HWConfig_PD_Mon
    // 名  称:生产日期-月
    // 说  明:取值范围：1~12
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 HWConfig_PD_Mon;

} PRODUCE_DATE_TYPE_DEF;

// 信 号 组 标 识 符: HW_config_info
// 信 号 组 名    称: 硬件配置信息
// 信 号 组 字    数: 43
// 信 号 组 数组长度: 6
// 信 号 组 说    明: 硬件配置信息应包括每个设备或模块的详细配置信息，包括设备或模块的LCN编码(用于后勤保障和定货等)、名称、序列号、累计工作时间、硬件的版本、以及硬件的描述信息。
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:array_element_valid
    // 名  称:数组元素有效性
    // 说  明:如果信号组信号为一个数组，则应包含该信号，表征该数组元素是否有效，当信息不需占用全部的数组元素时，未占用的元素该信号置无效。
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 array_element_valid;

    // 标识符:equipment_LCN_code
    // 名  称:设备LCN编码
    // 说  明:CCGD900-003 歼-20信息支援控制飞机编码管理要求
    //        第1～3位为系统码，用3位阿拉伯数字表示，系统码由标准专业根据产品分解结构统一规定，歼-20信息支援控制飞机产品分解结构系统码见附录A，对于3级以下系统，原则上其系统码应与3级系统的系统码保持一致；
    //        第4～5位为子系统码，用2位阿拉伯数字表示，子系统码仅用于对系统按功能进行拆分时使用：
    //        1)当系统无下级子系统时，子系统码默认为00；
    //        2)当系统下仅拆分2级子系统以内且每级子系统数量不超过9个时，第1位子系统码用来拆分第1级子系统，第2位子系统码用来拆分第2级子系统（若无第2级子系统，则第2位子系统码默认为0）；
    //        3)当系统下有超过2级子系统或每级子系统数量超过9个时，应从01开始连续顺序编排，不体现其层级关系；
    //        第6～9位为组件码，组件应是按模块化方法进行产品结构分解得到的最小模块或独立功能单元，组件码由4位阿拉伯数字表示，不得使用英文字母，一般不体现层级关系，若需体现层级关系编码时应评估分析，确保编码容量满足当前及后续发展机型的组件编码需求；
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 equipment_LCN_code;

    SPARE32 spare2[1];  // 保留字段

    // 标识符:hardware_serial_ID
    // 名  称:硬件序列号
    // 说  明:序号用以区分同型号产品或零部件的不同个体或批次，由产品承制单位按企业内标准自行编码，由数字、字符、字母或其组合组成，长度一般不超过15位。标识应唯一；标识应可追溯到产品或产品零部件的检验者、生产日期、批次号或顺序号等信息。
    // 单  位:
    // 起始字:3
    // 起始位:0
    char_8 hardware_serial_ID[16];

    // 标识符:hardware_name
    // 名  称:硬件名称
    // 说  明:硬件名称，不超过20个字符（汉字、数字、字母、符号）
    // 单  位:
    // 起始字:7
    // 起始位:0
    char_8 hardware_name[40];

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //        软件版本号包括：
    //            1-2：机型识别码;
    //          3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //             11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //             12：字母“V”
    //        13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //        19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:17
    // 起始位:0
    char_8 ver_number[24];

    // 标识符:total_run_time
    // 名  称:时间_累计工作时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:23
    // 起始位:0
    UINT64 total_run_time;

    // 标识符:HWConfig_RunTime_LastTime
    // 名  称:上次工作时长
    // 说  明:取值范围：0~99999
    // 单  位:h
    // LSB  :0.1
    // 起始字:25
    // 起始位:0
    UINT32 HWConfig_RunTime_LastTime;

    // 标识符:HWConfig_Manufacturer
    // 名  称:生产单位
    // 说  明:GBK编码字符
    //        最多16个半角字符或8个全角字符
    // 单  位:
    // 起始字:26
    // 起始位:0
    char_8 HWConfig_Manufacturer[32];

    // 标识符:produce_date
    // 名  称:生产日期
    // 说  明:
    // 单  位:
    // 起始字:34
    // 起始位:0
    PRODUCE_DATE_TYPE_DEF produce_date;

    // 标识符:reproduce_date
    // 名  称:返修生产日期
    // 说  明:
    // 单  位:
    // 起始字:36
    // 起始位:0
    REPRODUCE_DATE_TYPE_DEF reproduce_date;

    // 标识符:HWConfig_MaxTemp_LastTime_IsValid
    // 名  称:上次上电最高温-有效性
    // 说  明:
    // 单  位:
    // 起始字:38
    // 起始位:0
    BOOL_32 HWConfig_MaxTemp_LastTime_IsValid;

    // 标识符:last_power_on_highest_temp
    // 名  称:上次上电历史最高温度
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:39
    // 起始位:0
    INT32 last_power_on_highest_temp;

    // 标识符:HWConfig_MaxTemp_Total_IsValid
    // 名  称:历史最高温度-有效性
    // 说  明:
    // 单  位:
    // 起始字:40
    // 起始位:0
    BOOL_32 HWConfig_MaxTemp_Total_IsValid;

    // 标识符:history_highest_temp
    // 名  称:历史最高温度
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:41
    // 起始位:0
    INT32 history_highest_temp;

    // 标识符:repair_times
    // 名  称:返修次数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:42
    // 起始位:0
    INT32 repair_times;

} HW_CONFIG_INFO_TYPE_DEF;

// 信 号 组 标 识 符: data_generated_time1
// 信 号 组 名    称: 数据生成时间1
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
typedef struct
{
    // 标识符:time_missiontime
    // 名  称:时间_任务时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT64 time_missiontime;

} DATA_GENERATED_TIME1_TYPE_DEF;

// 信 号 组 标 识 符: tgt_radial_velocity_covariance
// 信 号 组 名    称: 目标径向速度方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_RADIAL_VELOCITY_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_radial_velocity
// 信 号 组 名    称: 目标径向速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_RADIAL_VELOCITY_TYPE_DEF;

// 信 号 组 标 识 符: tgt_paras_validity
// 信 号 组 名    称: 目标数据有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_tgt_velocity
    // 名  称:有效性_目标速度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_tgt_velocity;

    // 标识符:validity_tgt_el
    // 名  称:有效性_目标俯仰
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_tgt_el;

    // 标识符:validity_tgt_az
    // 名  称:有效性_目标方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_tgt_az;

    // 标识符:validity_tgt_distance
    // 名  称:有效性_目标距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_tgt_distance;

} TGT_PARAS_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance_covariance
// 信 号 组 名    称: 目标距离方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance
// 信 号 组 名    称: 目标距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: slave_tgt_paras
// 信 号 组 名    称: 随动目标参数
// 信 号 组 字    数: 10
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 以目标为中心的随动参数。
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:tgt_paras_validity
    // 名  称:目标数据有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_PARAS_VALIDITY_TYPE_DEF tgt_paras_validity;

    // 标识符:target_azimuth
    // 名  称:目标方位角_机体系
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:2
    // 起始位:0
    INT32 target_azimuth;

    // 标识符:variance_of_tgt_azimuth
    // 名  称:目标方位角方差_机体系
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:3
    // 起始位:0
    INT32 variance_of_tgt_azimuth;

    // 标识符:target_elevation
    // 名  称:目标俯仰角_机体系
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:4
    // 起始位:0
    INT32 target_elevation;

    // 标识符:variance_of_tgt_elevation
    // 名  称:目标俯仰角方差_机体系
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:5
    // 起始位:0
    INT32 variance_of_tgt_elevation;

    // 标识符:tgt_distance
    // 名  称:目标距离
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_DISTANCE_TYPE_DEF tgt_distance;

    // 标识符:tgt_distance_covariance
    // 名  称:目标距离方差
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_DISTANCE_COVARIANCE_TYPE_DEF tgt_distance_covariance;

    // 标识符:tgt_radial_velocity
    // 名  称:目标径向速度
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_RADIAL_VELOCITY_TYPE_DEF tgt_radial_velocity;

    // 标识符:tgt_radial_velocity_covariance
    // 名  称:目标径向速度方差
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    TGT_RADIAL_VELOCITY_COVARIANCE_TYPE_DEF tgt_radial_velocity_covariance;

} SLAVE_TGT_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: slave_pitch_angle
// 信 号 组 名    称: 随动俯仰角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 是指头显或平显的视场中心在机体系下的俯仰大小表示
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SLAVE_PITCH_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: slave_azimuth_angle
// 信 号 组 名    称: 随动方位角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 是指头显或平显的视场中心在机体系下的方位大小表示
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SLAVE_AZIMUTH_ANGLE_TYPE_DEF;

// 信 号 组 标 识 符: slave_los_paras
// 信 号 组 名    称: 随动LOS参数
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 随动于LOS的方位和俯仰角
typedef struct
{
    // 标识符:slave_azimuth_angle
    // 名  称:随动方位角
    // 说  明:是指头显或平显的视场中心在机体系下的方位大小表示
    // 单  位:
    // 起始字:0
    // 起始位:0
    SLAVE_AZIMUTH_ANGLE_TYPE_DEF slave_azimuth_angle;

    // 标识符:slave_pitch_angle
    // 名  称:随动俯仰角
    // 说  明:是指头显或平显的视场中心在机体系下的俯仰大小表示
    // 单  位:
    // 起始字:1
    // 起始位:0
    SLAVE_PITCH_ANGLE_TYPE_DEF slave_pitch_angle;

} SLAVE_LOS_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: sys_network_state
// 信 号 组 名    称: 系统网络状态
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 150
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    // 标识符:off_state_YES_NO
    // 名  称:关机状态_是_否
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    UINT32 off_state_YES_NO : 8;

    // 标识符:VS1394_net_state
    // 名  称:飞管1394网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 VS1394_net_state : 8;

    // 标识符:AV1394_net_state
    // 名  称:航电1394网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 AV1394_net_state : 8;

    // 标识符:FC_net_state
    // 名  称:FC网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 FC_net_state : 8;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:PowOff_CMD_State
    // 名  称:下电指令状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 PowOff_CMD_State : 8;

    // 标识符:app_state
    // 名  称:应用软件状态
    // 说  明:正常运行时，应用软件状态仅为正常工作或非正常工作；
    //        仅在飞管系统进入OFP加载模式后，SYMM将所有功能单元的应用软件状态置为SW_LOAD，触发各子系统进入维护加载态。
    //        若任务系统处于正常运行态时，但某子系统或子系统某模块运行在软件加载态，则对应子系统状态置为SW_load。
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 app_state : 8;

} SYS_NETWORK_STATE_TYPE_DEF;

// 信 号 组 标 识 符: AA_TOI_list_paras
// 信 号 组 名    称: 关注目标列表参数
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 4
// 信 号 组 说    明:
typedef struct
{
    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 platform_fused_tgt_ID;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:EW_tgt_no
    // 名  称:EW目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 EW_tgt_no;

    // 标识符:RDR_track_number
    // 名  称:RDR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 RDR_track_number;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT16 IR_track_number;

    // 标识符:suitor_member_no
    // 名  称:请求者成员编号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT8 suitor_member_no[4];

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:TOI_rank
    // 名  称:目标关注等级
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 TOI_rank : 8;

} AA_TOI_LIST_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: block_pixel_paras
// 信 号 组 名    称: 探测器分块像元参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 9
// 信 号 组 说    明: 该信号组描述探测器阵面各区域的坏元情况。
//                    各探测器阵面按照9方格划分为9块。按照数组元素0--8的顺序，分别表示上左、上、上右、中左、中、中右、下左、下、下右各块的参数。
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:block_id
    // 名  称:分块ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 block_id : 8;

    // 标识符:block_pixel_num
    // 名  称:分块像元数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 block_pixel_num;

    // 标识符:block_damage_pixel_num
    // 名  称:分块坏元数
    // 说  明:
    // 单  位:%
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 block_damage_pixel_num;

    // 标识符:ratio
    // 名  称:坏元率
    // 说  明:
    // 单  位:%
    // LSB  :0.000001
    // 起始字:3
    // 起始位:0
    UINT32 ratio;

} BLOCK_PIXEL_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: member_PPLI_info_team_IFDL
// 信 号 组 名    称: 成员精确定位与识别信息编队间_IFDL
// 信 号 组 字    数: 25
// 信 号 组 数组长度: 16
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:altitude_quality
    // 名  称:高度质量
    // 说  明:[0,15]
    //        0：大于5510m
    //        1：不大于5510m
    //        2：不大于2755m
    //        3：不大于1378m
    //        4：不大于689m
    //        5：不大于488m
    //        6：不大于344m
    //        7：不大于244m
    //        8：不大于172m
    //        9：不大于122m
    //        10：不大于86m
    //        11：不大于61m
    //        12：不大于43m
    //        13：不大于30m
    //        14：不大于22m
    //        15：不大于15m
    //        16：不大于10.5m
    //        17：不大于7.3m
    //        18：不大于5.1m
    //        19：不大于3.6m
    //        20：不大于2.5m
    //        21：不大于1.7m
    //        22：不大于1.2m
    //        23：不大于0.9m
    //        24：不大于0.6m
    //        25：不大于0.4m
    //        26：不大于0.3m
    //        27：不大于0.2m
    //        28：不大于0.15m
    //        29：不大于0.1m
    //        30：不大于0.07m
    //        31：无报告
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT32 altitude_quality : 8;

    // 标识符:location_quality
    // 名  称:地理位置质量
    // 说  明:[0,15]
    //        0：大于5510m
    //        1：不大于5510m
    //        2：不大于2755m
    //        3：不大于1378m
    //        4：不大于689m
    //        5：不大于488m
    //        6：不大于344m
    //        7：不大于244m
    //        8：不大于172m
    //        9：不大于122m
    //        10：不大于86m
    //        11：不大于61m
    //        12：不大于43m
    //        13：不大于30m
    //        14：不大于22m
    //        15：不大于15m
    //        16：不大于10.5m
    //        17：不大于7.3m
    //        18：不大于5.1m
    //        19：不大于3.6m
    //        20：不大于2.5m
    //        21：不大于1.7m
    //        22：不大于1.2m
    //        23：不大于0.9m
    //        24：不大于0.6m
    //        25：不大于0.4m
    //        26：不大于0.3m
    //        27：不大于0.2m
    //        28：不大于0.15m
    //        29：不大于0.1m
    //        30：不大于0.07m
    //        31：无报告
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:8
    UINT32 location_quality : 8;

    // 标识符:location_source
    // 名  称:位置来源
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 location_source : 8;

    // 标识符:member_nav_paras_IFDL
    // 名  称:成员导航参数_IFDL
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    MEMBER_NAV_PARAS_IFDL_TYPE_DEF member_nav_paras_IFDL;

    // 标识符:I_team_no
    // 名  称:I链编队号
    // 说  明:编队号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:22
    // 起始位:16
    UINT16 I_team_no;

    // 标识符:public_net_id
    // 名  称:公网序号
    // 说  明:公网序号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:22
    // 起始位:0
    UINT16 public_net_id;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:I_member_no
    // 名  称:I链成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:23
    // 起始位:0
    UINT16 I_member_no;

    // 标识符:member_net_id
    // 名  称:成员编识号
    // 说  明:网络ID
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:24
    // 起始位:0
    UINT32 member_net_id;

} MEMBER_PPLI_INFO_TEAM_IFDL_TYPE_DEF;

// 信 号 组 标 识 符: TDC_EL
// 信 号 组 名    称: TDC光标俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TDC_EL_TYPE_DEF;

// 信 号 组 标 识 符: TDC_AZ
// 信 号 组 名    称: TDC光标方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TDC_AZ_TYPE_DEF;

// 信 号 组 标 识 符: EventData_Data_Item_MS_SUB
// 信 号 组 名    称: EventData数据项_MS_SUB
// 信 号 组 字    数: 15
// 信 号 组 数组长度: 6
// 信 号 组 说    明:
typedef struct
{
    // 标识符:HMC_LCN
    // 名  称:HMC_LCN
    // 说  明:LCN码，双座由8位改为9位
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 HMC_LCN;

    // 标识符:HMC_State
    // 名  称:HMC_State
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 HMC_State;

    // 标识符:HMC_HASC
    // 名  称:HMC_HASC
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT8 HMC_HASC;

    // 标识符:HMC_HSC
    // 名  称:HMC_HSC
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 HMC_HSC;

    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT16 date_year;

    // 标识符:time_calendartime_ms
    // 名  称:时间_日历时间_ms
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    // 单  位:M_sc
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 time_calendartime_ms;

    // 标识符:HMC_EventDataLen
    // 名  称:HMC伴随数据长度
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 HMC_EventDataLen;

    // 标识符:HMC_EventData_MS_Sub
    // 名  称:HMC伴随数据_任务子系统
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    INT32 HMC_EventData_MS_Sub[10];

} EVENTDATA_DATA_ITEM_MS_SUB_TYPE_DEF;

// 信 号 组 标 识 符: mission_sequence
// 信 号 组 名    称: 任务序列
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:mission_sequence_no
    // 名  称:任务序列号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT8 mission_sequence_no;

    // 标识符:mission_sequence_name
    // 名  称:任务序列名称
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    char_8 mission_sequence_name[12];

} MISSION_SEQUENCE_TYPE_DEF;

// 信 号 组 标 识 符: system_status
// 信 号 组 名    称: 系统状态
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:EM_level
    // 名  称:辐射等级
    // 说  明:辐射级别控制参数。等级1配置为全静默等级，等级5配置为无限制辐射等级，中间级别可根据任务配置。
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 EM_level : 8;

    // 标识符:mission_sequence_no
    // 名  称:任务序列号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    INT32 mission_sequence_no : 8;

    // 标识符:mission_main_mode
    // 名  称:任务主模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 mission_main_mode : 8;

} SYSTEM_STATUS_TYPE_DEF;

// 信 号 组 标 识 符: time_event_para_2
// 信 号 组 名    称: 时间事件参数2
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:system_status
    // 名  称:系统状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    SYSTEM_STATUS_TYPE_DEF system_status;

} TIME_EVENT_PARA_2_TYPE_DEF;

// 信 号 组 标 识 符: time_event_para_1
// 信 号 组 名    称: 时间事件参数1
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time_nounit
    // 名  称:_时间_无符号
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT64 _time_nounit;

} TIME_EVENT_PARA_1_TYPE_DEF;

// 信 号 组 标 识 符: event_para_validity
// 信 号 组 名    称: 事件参数_有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_event_para_2
    // 名  称:有效性_事件参数2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_event_para_2;

    // 标识符:validity_event_para_1
    // 名  称:有效性_事件参数1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_event_para_1;

} EVENT_PARA_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: time_event
// 信 号 组 名    称: 时间事件
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 当时间事件类型为“到达某时刻”时，时间事件参数1填写到达时刻，时间事件参数2无效。
//                    当导航事件类型为“状态持续时间”时，时间事件参数1填写持续时间，时间事件参数2填写对应的系统状态。不关注的系统状态置为NA。
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:time_event_type
    // 名  称:时间事件类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 time_event_type : 8;

    // 标识符:mission_event_serial_no
    // 名  称:任务事件序号
    // 说  明:本次任务规划的所有任务事件的统一编号，以规划中事件可能发生的先后顺序从1一次编号。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT32 mission_event_serial_no : 8;

    // 标识符:time_event_serial_no
    // 名  称:时间事件序号
    // 说  明:任务事件中所包含的时间事件的序号，从1开始依次定义。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 time_event_serial_no : 8;

    // 标识符:event_para_validity
    // 名  称:事件参数_有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    EVENT_PARA_VALIDITY_TYPE_DEF event_para_validity;

    // 标识符:time_event_para_1
    // 名  称:时间事件参数1
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TIME_EVENT_PARA_1_TYPE_DEF time_event_para_1;

    // 标识符:time_event_para_2
    // 名  称:时间事件参数2
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TIME_EVENT_PARA_2_TYPE_DEF time_event_para_2;

} TIME_EVENT_TYPE_DEF;

// 信 号 组 标 识 符: state_change_event_para_2
// 信 号 组 名    称: 状态转换事件参数2
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:system_status
    // 名  称:系统状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    SYSTEM_STATUS_TYPE_DEF system_status;

} STATE_CHANGE_EVENT_PARA_2_TYPE_DEF;

// 信 号 组 标 识 符: state_change_event_para_1
// 信 号 组 名    称: 状态转换事件参数1
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:system_status
    // 名  称:系统状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    SYSTEM_STATUS_TYPE_DEF system_status;

} STATE_CHANGE_EVENT_PARA_1_TYPE_DEF;

// 信 号 组 标 识 符: state_change_event
// 信 号 组 名    称: 状态转换事件
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 状态转换事件参数1为前一状态，状态转换事件参数2为后一状态。
//                    若不关注前一状态，则参数1无效；不关注的系统状态置NA。
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:state_change_event_type
    // 名  称:状态转换事件类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 state_change_event_type : 8;

    // 标识符:mission_event_serial_no
    // 名  称:任务事件序号
    // 说  明:本次任务规划的所有任务事件的统一编号，以规划中事件可能发生的先后顺序从1一次编号。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT32 mission_event_serial_no : 8;

    // 标识符:state_change_event_serial_no
    // 名  称:状态转换事件序号
    // 说  明:任务事件中所包含的状态转换事件的序号，从1开始依次定义。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 state_change_event_serial_no : 8;

    // 标识符:event_para_validity
    // 名  称:事件参数_有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    EVENT_PARA_VALIDITY_TYPE_DEF event_para_validity;

    // 标识符:state_change_event_para_1
    // 名  称:状态转换事件参数1
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    STATE_CHANGE_EVENT_PARA_1_TYPE_DEF state_change_event_para_1;

    // 标识符:state_change_event_para_2
    // 名  称:状态转换事件参数2
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    STATE_CHANGE_EVENT_PARA_2_TYPE_DEF state_change_event_para_2;

} STATE_CHANGE_EVENT_TYPE_DEF;

// 信 号 组 标 识 符: situation_event_para_2
// 信 号 组 名    称: 态势事件参数2
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:tgt_source
    // 名  称:目标来源
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 tgt_source : 8;

} SITUATION_EVENT_PARA_2_TYPE_DEF;

// 信 号 组 标 识 符: situation_event_para_1
// 信 号 组 名    称: 态势事件参数1
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:target_class
    // 名  称:目标类型
    // 说  明:注：ALL 普查，仅图像情报使用
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 target_class : 8;

} SITUATION_EVENT_PARA_1_TYPE_DEF;

// 信 号 组 标 识 符: situation_event
// 信 号 组 名    称: 态势事件
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:situation_event_type
    // 名  称:态势事件类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 situation_event_type : 8;

    // 标识符:mission_event_serial_no
    // 名  称:任务事件序号
    // 说  明:本次任务规划的所有任务事件的统一编号，以规划中事件可能发生的先后顺序从1一次编号。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT32 mission_event_serial_no : 8;

    // 标识符:situation_event_serial_no
    // 名  称:态势事件序号
    // 说  明:任务事件中所包含的态势事件的序号，从1开始依次定义。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 situation_event_serial_no : 8;

    // 标识符:event_para_validity
    // 名  称:事件参数_有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    EVENT_PARA_VALIDITY_TYPE_DEF event_para_validity;

    // 标识符:situation_event_para_1
    // 名  称:态势事件参数1
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    SITUATION_EVENT_PARA_1_TYPE_DEF situation_event_para_1;

    // 标识符:situation_event_para_2
    // 名  称:态势事件参数2
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SITUATION_EVENT_PARA_2_TYPE_DEF situation_event_para_2;

} SITUATION_EVENT_TYPE_DEF;

// 信 号 组 标 识 符: nav_event_para_2
// 信 号 组 名    称: 导航事件参数2
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    INT32 _velocity;

} NAV_EVENT_PARA_2_TYPE_DEF;

// 信 号 组 标 识 符: nav_event_para_1
// 信 号 组 名    称: 导航事件参数1
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_monitor_above_below
    // 名  称:数据监控数值范围
    // 说  明:数据监控数值范围
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 data_monitor_above_below : 8;

    // 标识符:data_monitor_type
    // 名  称:数据监控类型
    // 说  明:导航事件：数据监控类型
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 data_monitor_type : 8;

    // 标识符:route_point_area_no
    // 名  称:航线点或区域编号
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT32 route_point_area_no : 8;

    // 标识符:fly_plan
    // 名  称:飞行计划号
    // 说  明:飞行计划，包括A~K（I除外）计划、标记点、波塞点、标定点、初始位置、最近机场、机场
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 fly_plan : 8;

} NAV_EVENT_PARA_1_TYPE_DEF;

// 信 号 组 标 识 符: nav_event
// 信 号 组 名    称: 导航事件
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 当导航事件类型为“到达某点”时，导航事件参数1填写飞行计划号和航线点号，导航事件参数2填写进入门限。
//                    当导航事件类型为“到达某区”或“退出某区”时，导航事件参数1填写区域号，导航事件参数2无效。
//                    当导航事件类型为“偏离航线”时，导航事件参数1填写飞行计划号，导航事件参数2填写偏离门限。
//                    当导航事件类型为“数据监测”时，导航事件参数1填写数据监控类型和范围，导航事件参数2填写速度或距离。
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:nav_event_type
    // 名  称:导航事件类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 nav_event_type : 8;

    // 标识符:mission_event_serial_no
    // 名  称:任务事件序号
    // 说  明:本次任务规划的所有任务事件的统一编号，以规划中事件可能发生的先后顺序从1一次编号。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT32 mission_event_serial_no : 8;

    // 标识符:nav_event_serial_no
    // 名  称:导航事件序号
    // 说  明:任务事件中所包含的导航事件的序号，从1开始依次定义。
    //        0表示无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 nav_event_serial_no : 8;

    // 标识符:event_para_validity
    // 名  称:事件参数_有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    EVENT_PARA_VALIDITY_TYPE_DEF event_para_validity;

    // 标识符:nav_event_para_1
    // 名  称:导航事件参数1
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    NAV_EVENT_PARA_1_TYPE_DEF nav_event_para_1;

    // 标识符:nav_event_para_2
    // 名  称:导航事件参数2
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    NAV_EVENT_PARA_2_TYPE_DEF nav_event_para_2;

} NAV_EVENT_TYPE_DEF;

// 信 号 组 标 识 符: mission_event
// 信 号 组 名    称: 任务事件
// 信 号 组 字    数: 20
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:mission_event_type
    // 名  称:任务事件类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 mission_event_type : 8;

    // 标识符:nav_event
    // 名  称:导航事件
    // 说  明:当导航事件类型为“到达某点”时，导航事件参数1填写飞行计划号和航线点号，导航事件参数2填写进入门限。
    //        当导航事件类型为“到达某区”或“退出某区”时，导航事件参数1填写区域号，导航事件参数2无效。
    //        当导航事件类型为“偏离航线”时，导航事件参数1填写飞行计划号，导航事件参数2填写偏离门限。
    //        当导航事件类型为“数据监测”时，导航事件参数1填写数据监控类型和范围，导航事件参数2填写速度或距离。
    // 单  位:
    // 起始字:1
    // 起始位:0
    NAV_EVENT_TYPE_DEF nav_event;

    // 标识符:situation_event
    // 名  称:态势事件
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    SITUATION_EVENT_TYPE_DEF situation_event;

    // 标识符:time_event
    // 名  称:时间事件
    // 说  明:当时间事件类型为“到达某时刻”时，时间事件参数1填写到达时刻，时间事件参数2无效。
    //        当导航事件类型为“状态持续时间”时，时间事件参数1填写持续时间，时间事件参数2填写对应的系统状态。不关注的系统状态置为NA。
    // 单  位:
    // 起始字:10
    // 起始位:0
    TIME_EVENT_TYPE_DEF time_event;

    // 标识符:state_change_event
    // 名  称:状态转换事件
    // 说  明:状态转换事件参数1为前一状态，状态转换事件参数2为后一状态。
    //        若不关注前一状态，则参数1无效；不关注的系统状态置NA。
    // 单  位:
    // 起始字:15
    // 起始位:0
    STATE_CHANGE_EVENT_TYPE_DEF state_change_event;

    UINT32 spare2 : 16;  // 保留字段
    // 标识符:member_mission_event
    // 名  称:编队成员任务事件
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:8
    UINT32 member_mission_event : 8;

    // 标识符:onboard_mission_event
    // 名  称:本机任务事件
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT32 onboard_mission_event : 8;

} MISSION_EVENT_TYPE_DEF;

// 信 号 组 标 识 符: turn_point_ground_distance
// 信 号 组 名    称: 转弯点地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 转弯点与载机位置的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TURN_POINT_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: turn_point_az
// 信 号 组 名    称: 转弯点方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 转弯点到载机位置的连线与真北的夹角
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TURN_POINT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: TTG
// 信 号 组 名    称: 预计到达所需时间
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} TTG_TYPE_DEF;

// 信 号 组 标 识 符: TACAN_type_course_offset
// 信 号 组 名    称: 塔康航线偏差距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机位置相对于塔康类型航线的距离。飞机在选择航线正向的左边为正。
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TACAN_TYPE_COURSE_OFFSET_TYPE_DEF;

// 信 号 组 标 识 符: stpt_position
// 信 号 组 名    称: 操纵点位置
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:validity_location
    // 名  称:位置有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_location;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _longitude;

    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:2
    // 起始位:0
    INT32 _latitude;

    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:3
    // 起始位:0
    INT32 _altitude;

} STPT_POSITION_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_slant_distance
// 信 号 组 名    称: 操纵点斜距
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的斜距
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} STEERING_POINT_SLANT_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: up_Range
// 信 号 组 名    称: 天向距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} UP_RANGE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_plat_up_distance
// 信 号 组 名    称: 操纵点平台系天向距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的距离在平台系的天向分量
typedef struct
{
    // 标识符:up_Range
    // 名  称:天向距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UP_RANGE_TYPE_DEF up_Range;

} STEERING_POINT_PLAT_UP_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: west_Range
// 信 号 组 名    称: 西向距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} WEST_RANGE_TYPE_DEF;

// 信 号 组 标 识 符: north_distance
// 信 号 组 名    称: 北向距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} NORTH_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_plat_NW_distance
// 信 号 组 名    称: 操纵点平台系北西距离
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的距离在平台系的北西向分量
typedef struct
{
    // 标识符:north_distance
    // 名  称:北向距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    NORTH_DISTANCE_TYPE_DEF north_distance;

    // 标识符:west_Range
    // 名  称:西向距离
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    WEST_RANGE_TYPE_DEF west_Range;

} STEERING_POINT_PLAT_NW_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: pitch
// 信 号 组 名    称: 俯仰角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} PITCH_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_plat_el
// 信 号 组 名    称: 操纵点平台系俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点相对于载机的俯仰在平台系的投影。
typedef struct
{
    // 标识符:pitch
    // 名  称:俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    PITCH_TYPE_DEF pitch;

} STEERING_POINT_PLAT_EL_TYPE_DEF;

// 信 号 组 标 识 符: azimuth
// 信 号 组 名    称: 方位角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AZIMUTH_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_plat_az
// 信 号 组 名    称: 操纵点平台系方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点相对于载机的方位在平台系的投影。
typedef struct
{
    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} STEERING_POINT_PLAT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_slant_distance
// 信 号 组 名    称: 操纵点OAP斜距
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的OAP的斜距
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} STEERING_POINT_OAP_SLANT_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_plat_up_distance
// 信 号 组 名    称: 操纵点OAP平台系天向距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的OAP的距离在平台系的天向分量
typedef struct
{
    // 标识符:up_Range
    // 名  称:天向距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UP_RANGE_TYPE_DEF up_Range;

} STEERING_POINT_OAP_PLAT_UP_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_plat_NW_distance
// 信 号 组 名    称: 操纵点OAP平台系北西距离
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的OAP的距离在平台系的北西分量
typedef struct
{
    // 标识符:north_distance
    // 名  称:北向距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    NORTH_DISTANCE_TYPE_DEF north_distance;

    // 标识符:west_Range
    // 名  称:西向距离
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    WEST_RANGE_TYPE_DEF west_Range;

} STEERING_POINT_OAP_PLAT_NW_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_plat_el
// 信 号 组 名    称: 操纵点OAP平台系俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点的OAP相对于载机的俯仰在平台系的投影。
typedef struct
{
    // 标识符:pitch
    // 名  称:俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    PITCH_TYPE_DEF pitch;

} STEERING_POINT_OAP_PLAT_EL_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_plat_az
// 信 号 组 名    称: 操纵点OAP平台系方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点的OAP相对于载机的方位在平台系的投影。
typedef struct
{
    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} STEERING_POINT_OAP_PLAT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_ground_distance
// 信 号 组 名    称: 操纵点OAP地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的OAP的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} STEERING_POINT_OAP_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_OAP_body_azel
// 信 号 组 名    称: 操纵点OAP机体系方位俯仰
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点的OAP相对于载机的方位俯仰在机体系的投影。
typedef struct
{
    // 标识符:pitch
    // 名  称:俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    PITCH_TYPE_DEF pitch;

    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} STEERING_POINT_OAP_BODY_AZEL_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_localizer_dev
// 信 号 组 名    称: 操纵点方位偏差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机位置的相对于操纵点类型选择航线的方位偏差。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} STEERING_POINT_LOCALIZER_DEV_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_ground_distance
// 信 号 组 名    称: 操纵点地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与操纵点的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} STEERING_POINT_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: steering_point_body_azel
// 信 号 组 名    称: 操纵点机体系方位俯仰
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 操纵点相对于载机的方位俯仰在机体系的投影。
typedef struct
{
    // 标识符:pitch
    // 名  称:俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    PITCH_TYPE_DEF pitch;

    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} STEERING_POINT_BODY_AZEL_TYPE_DEF;

// 信 号 组 标 识 符: steer_direct_desired_vel
// 信 号 组 名    称: 期望速度指引
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:desired_command_types
    // 名  称:期望指令类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 desired_command_types : 8;

    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    INT32 _velocity;

} STEER_DIRECT_DESIRED_VEL_TYPE_DEF;

// 信 号 组 标 识 符: steer_direct_desired_track
// 信 号 组 名    称: 期望航迹指引
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:CDI_types
    // 名  称:航线偏差指引类型
    // 说  明:航线偏差指引类型，表示航线偏差指示符根据何种传感器数据指示。
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 CDI_types : 8;

    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:1
    // 起始位:0
    INT32 _angle_mrad;

} STEER_DIRECT_DESIRED_TRACK_TYPE_DEF;

// 信 号 组 标 识 符: steer_direct_desired_heading
// 信 号 组 名    称: 期望航向指引
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} STEER_DIRECT_DESIRED_HEADING_TYPE_DEF;

// 信 号 组 标 识 符: desired_refer_alt
// 信 号 组 名    称: 期望参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-5500,30000]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} DESIRED_REFER_ALT_TYPE_DEF;

// 信 号 组 标 识 符: desired_height
// 信 号 组 名    称: 期望海高高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,30000]m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} DESIRED_HEIGHT_TYPE_DEF;

// 信 号 组 标 识 符: steer_direct_desired_alt
// 信 号 组 名    称: 期望高度指引
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:desired_command_types
    // 名  称:期望指令类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 desired_command_types : 8;

    // 标识符:desired_height
    // 名  称:期望海高高度
    // 说  明:[-500,30000]m
    // 单  位:
    // 起始字:1
    // 起始位:0
    DESIRED_HEIGHT_TYPE_DEF desired_height;

    // 标识符:desired_refer_alt
    // 名  称:期望参考高度
    // 说  明:[-5500,30000]m
    // 单  位:
    // 起始字:2
    // 起始位:0
    DESIRED_REFER_ALT_TYPE_DEF desired_refer_alt;

} STEER_DIRECT_DESIRED_ALT_TYPE_DEF;

// 信 号 组 标 识 符: SPOI_nav_info_validity
// 信 号 组 名    称: 关注操纵点导航信息_有效性
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_ERF
    // 名  称:有效性_预计剩余燃油
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_ERF;

    // 标识符:validity_deltaTOT
    // 名  称:有效性_预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_deltaTOT;

    // 标识符:validity_ETA
    // 名  称:有效性_预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_ETA;

    // 标识符:validity_TTG
    // 名  称:有效性_预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_TTG;

    // 标识符:validity_routeERF
    // 名  称:有效性_航线_预计剩余燃油
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_routeERF;

    // 标识符:validity_route_deltaTOT
    // 名  称:有效性_航线_预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_route_deltaTOT;

    // 标识符:validity_route_ETA
    // 名  称:有效性_航线_预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_route_ETA;

    // 标识符:validity_route_TTG
    // 名  称:有效性_航线_预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_route_TTG;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_steering_point_ground_distance
    // 名  称:有效性_操纵点地面距离
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_steering_point_ground_distance;

    // 标识符:validity_steering_point_plat_az
    // 名  称:有效性_操纵点平台系方位
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_steering_point_plat_az;

} SPOI_NAV_INFO_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: route_TTG
// 信 号 组 名    称: 航线_预计到达所需时间
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} ROUTE_TTG_TYPE_DEF;

// 信 号 组 标 识 符: route_ETA
// 信 号 组 名    称: 航线_预计到达时刻
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} ROUTE_ETA_TYPE_DEF;

// 信 号 组 标 识 符: route_ERF
// 信 号 组 名    称: 航线_预计剩余油量
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_mass
    // 名  称:_质量
    // 说  明:用于表示质量重量等信号值，带符号位是为了计算过程中可能会产生负值。
    //        表示精度为0.001kg，表示范围约+/-1000吨
    // 单  位:kg
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _mass;

} ROUTE_ERF_TYPE_DEF;

// 信 号 组 标 识 符: route_deltaTOT
// 信 号 组 名    称: 航线_预计到达时刻差
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} ROUTE_DELTATOT_TYPE_DEF;

// 信 号 组 标 识 符: ETA
// 信 号 组 名    称: 预计到达时刻
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} ETA_TYPE_DEF;

// 信 号 组 标 识 符: ERF
// 信 号 组 名    称: 预计剩余油量
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_mass
    // 名  称:_质量
    // 说  明:用于表示质量重量等信号值，带符号位是为了计算过程中可能会产生负值。
    //        表示精度为0.001kg，表示范围约+/-1000吨
    // 单  位:kg
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _mass;

} ERF_TYPE_DEF;

// 信 号 组 标 识 符: deltaTOT
// 信 号 组 名    称: 预计到达时刻差
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} DELTATOT_TYPE_DEF;

// 信 号 组 标 识 符: SPOI_nav_info
// 信 号 组 名    称: 关注操纵点导航信息
// 信 号 组 字    数: 20
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:SPOI_nav_info_validity
    // 名  称:关注操纵点导航信息_有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    SPOI_NAV_INFO_VALIDITY_TYPE_DEF SPOI_nav_info_validity;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:sp_number
    // 名  称:操纵点编号
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:8
    UINT32 sp_number : 16;

    // 标识符:fly_plan
    // 名  称:飞行计划号
    // 说  明:飞行计划，包括A~K（I除外）计划、标记点、波塞点、标定点、初始位置、最近机场、机场
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 fly_plan : 8;

    // 标识符:steering_point_plat_az
    // 名  称:操纵点平台系方位
    // 说  明:操纵点相对于载机的方位在平台系的投影。
    // 单  位:
    // 起始字:4
    // 起始位:0
    STEERING_POINT_PLAT_AZ_TYPE_DEF steering_point_plat_az;

    // 标识符:steering_point_ground_distance
    // 名  称:操纵点地面距离
    // 说  明:载机与操纵点的地面距离
    // 单  位:
    // 起始字:5
    // 起始位:0
    STEERING_POINT_GROUND_DISTANCE_TYPE_DEF steering_point_ground_distance;

    // 标识符:TTG
    // 名  称:预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TTG_TYPE_DEF TTG;

    // 标识符:ETA
    // 名  称:预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    ETA_TYPE_DEF ETA;

    // 标识符:deltaTOT
    // 名  称:预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    DELTATOT_TYPE_DEF deltaTOT;

    // 标识符:ERF
    // 名  称:预计剩余油量
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    ERF_TYPE_DEF ERF;

    // 标识符:route_TTG
    // 名  称:航线_预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    ROUTE_TTG_TYPE_DEF route_TTG;

    // 标识符:route_ETA
    // 名  称:航线_预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    ROUTE_ETA_TYPE_DEF route_ETA;

    // 标识符:route_deltaTOT
    // 名  称:航线_预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    ROUTE_DELTATOT_TYPE_DEF route_deltaTOT;

    // 标识符:route_ERF
    // 名  称:航线_预计剩余油量
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    ROUTE_ERF_TYPE_DEF route_ERF;

} SPOI_NAV_INFO_TYPE_DEF;

// 信 号 组 标 识 符: SP_type_course_offset
// 信 号 组 名    称: 操纵点航线偏差距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机位置相对于操纵点类型航线的距离。飞机在选择航线正向的左边为正。
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} SP_TYPE_COURSE_OFFSET_TYPE_DEF;

// 信 号 组 标 识 符: SCA_gls_dev
// 信 号 组 名    称: 自主着陆下滑道偏差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SCA_GLS_DEV_TYPE_DEF;

// 信 号 组 标 识 符: nav_point_plat_el
// 信 号 组 名    称: 导航点平台系俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 导航点相对于载机的俯仰在平台系的投影。
typedef struct
{
    // 标识符:pitch
    // 名  称:俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    PITCH_TYPE_DEF pitch;

} NAV_POINT_PLAT_EL_TYPE_DEF;

// 信 号 组 标 识 符: nav_point_plat_az
// 信 号 组 名    称: 导航点平台系方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 导航点相对于载机的方位在平台系的投影。
typedef struct
{
    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} NAV_POINT_PLAT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: nav_point_ground_distance
// 信 号 组 名    称: 导航点地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 当前导航点的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} NAV_POINT_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: NAV_paras_validity
// 信 号 组 名    称: 导航参数_有效性
// 信 号 组 字    数: 10
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_FAF_point_az
    // 名  称:有效性_FAF点方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_FAF_point_az;

    // 标识符:validity_FAF_point_ground_distance
    // 名  称:有效性_FAF地面距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_FAF_point_ground_distance;

    // 标识符:validity_ILS_station_az
    // 名  称:有效性_仪表站方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_ILS_station_az;

    // 标识符:validity_MLS_station_az
    // 名  称:有效性_微波站方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_MLS_station_az;

    // 标识符:validity_steering_point_slant_distance
    // 名  称:有效性_操纵点斜距
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 validity_steering_point_slant_distance;

    // 标识符:validity_steering_point_ground_distance
    // 名  称:有效性_操纵点地面距离
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_steering_point_ground_distance;

    // 标识符:validity_turn_point_az
    // 名  称:有效性_转弯点方位
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_turn_point_az;

    // 标识符:validity_turn_point_ground_range
    // 名  称:有效性_转弯点地面距离
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_turn_point_ground_range;

    // 标识符:validity_steering_point_plat_el
    // 名  称:有效性_操纵点平台系俯仰
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    BOOL_8 validity_steering_point_plat_el;

    // 标识符:validity_steering_point_body_azel
    // 名  称:有效性_操纵点机体系方位俯仰
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_steering_point_body_azel;

    // 标识符:validity_steering_point_plat_up_distance
    // 名  称:有效性_操纵点平台系天向距离
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_steering_point_plat_up_distance;

    // 标识符:validity_steering_point_plat_NW_distance
    // 名  称:有效性_操纵点平台系北西距离
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_steering_point_plat_NW_distance;

    // 标识符:validity_steering_point_OAP_plat_NW_distance
    // 名  称:有效性_操纵点OAP平台系北西距离
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:24
    BOOL_8 validity_steering_point_OAP_plat_NW_distance;

    // 标识符:validity_steering_point_OAP_slant_distance
    // 名  称:有效性_操纵点OAP斜距
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    BOOL_8 validity_steering_point_OAP_slant_distance;

    // 标识符:validity_steering_point_OAP_ground_distance
    // 名  称:有效性_操纵点OAP地面距离
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_steering_point_OAP_ground_distance;

    // 标识符:validity_steering_point_plat_az
    // 名  称:有效性_操纵点平台系方位
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_steering_point_plat_az;

    // 标识符:validity_steering_point_OAP_plat_el
    // 名  称:有效性_操纵点OAP平台系俯仰
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:24
    BOOL_8 validity_steering_point_OAP_plat_el;

    // 标识符:validity_steering_point_OAP_plat_az
    // 名  称:有效性_操纵点OAP平台系方位
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    BOOL_8 validity_steering_point_OAP_plat_az;

    // 标识符:validity_steering_point_OAP_body_azel
    // 名  称:有效性_操纵点OAP机体系方位俯仰
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    BOOL_8 validity_steering_point_OAP_body_azel;

    // 标识符:validity_steering_point_OAP_plat_up_distance
    // 名  称:有效性_操纵点OAP平台系天向距离
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    BOOL_8 validity_steering_point_OAP_plat_up_distance;

    // 标识符:validity_SP_type_course_offset
    // 名  称:有效性_操纵点航线偏差距离
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    BOOL_8 validity_SP_type_course_offset;

    // 标识符:validity_deltaTOT
    // 名  称:有效性_预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:16
    BOOL_8 validity_deltaTOT;

    // 标识符:validity_ETA
    // 名  称:有效性_预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    BOOL_8 validity_ETA;

    // 标识符:validity_TTG
    // 名  称:有效性_预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    BOOL_8 validity_TTG;

    // 标识符:validity_desired_height
    // 名  称:有效性_期望海高高度
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:24
    BOOL_8 validity_desired_height;

    // 标识符:validity_SCA_gls_dev
    // 名  称:有效性_自主着陆下滑道偏差
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    BOOL_8 validity_SCA_gls_dev;

    // 标识符:validity_steering_point_localizer_dev
    // 名  称:有效性_操纵点方位偏差
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:8
    BOOL_8 validity_steering_point_localizer_dev;

    // 标识符:validity_TACAN_type_course_offset
    // 名  称:有效性_塔康航线偏差距离
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    BOOL_8 validity_TACAN_type_course_offset;

    // 标识符:validity_desired_track
    // 名  称:有效性_期望航迹
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:24
    BOOL_8 validity_desired_track;

    // 标识符:validity_desired_heading
    // 名  称:有效性_期望航向
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:16
    BOOL_8 validity_desired_heading;

    // 标识符:validity_desired_vel
    // 名  称:有效性_期望速度
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:8
    BOOL_8 validity_desired_vel;

    // 标识符:validity_desired_refer_alt
    // 名  称:有效性_期望参考高度
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    BOOL_8 validity_desired_refer_alt;

    // 标识符:validity_bullseye_point_plat_az
    // 名  称:有效性_波塞点平台系方位
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_bullseye_point_plat_az;

    // 标识符:validity_flight_director_cue_el
    // 名  称:有效性_飞行操纵指引符俯仰
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_flight_director_cue_el;

    // 标识符:validity_flight_director_cue_az
    // 名  称:有效性_飞行操纵指引符方位
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_flight_director_cue_az;

    // 标识符:validity_heading_steer_direct_loc_dev
    // 名  称:有效性_航向操纵指引杆方位偏差
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_heading_steer_direct_loc_dev;

    SPARE8 spare1;  // 保留字段

    // 标识符:validity_ERF
    // 名  称:有效性_预计剩余燃油
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:16
    BOOL_8 validity_ERF;

    // 标识符:validity_bingo_fuel
    // 名  称:有效性_bingo油量
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_bingo_fuel;

    // 标识符:validity_bullseye_point_ground_distance
    // 名  称:有效性_波塞点地面距离
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_bullseye_point_ground_distance;

} NAV_PARAS_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: heading_steer_direct_loc_dev
// 信 号 组 名    称: 航向操纵指引杆方位偏差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} HEADING_STEER_DIRECT_LOC_DEV_TYPE_DEF;

// 信 号 组 标 识 符: nav_heading_steer_direct
// 信 号 组 名    称: 航向操纵指引杆
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:heading_steer_direct_loc_dev
    // 名  称:航向操纵指引杆方位偏差
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    HEADING_STEER_DIRECT_LOC_DEV_TYPE_DEF heading_steer_direct_loc_dev;

} NAV_HEADING_STEER_DIRECT_TYPE_DEF;

// 信 号 组 标 识 符: MLS_station_az
// 信 号 组 名    称: 微波站方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} MLS_STATION_AZ_TYPE_DEF;

// 信 号 组 标 识 符: ILS_station_az
// 信 号 组 名    称: 仪表站方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} ILS_STATION_AZ_TYPE_DEF;

// 信 号 组 标 识 符: flight_director_cue_el
// 信 号 组 名    称: 飞行操纵指引符俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} FLIGHT_DIRECTOR_CUE_EL_TYPE_DEF;

// 信 号 组 标 识 符: flight_director_cue_az
// 信 号 组 名    称: 飞行操纵指引符方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} FLIGHT_DIRECTOR_CUE_AZ_TYPE_DEF;

// 信 号 组 标 识 符: flight_director_cue
// 信 号 组 名    称: 飞行操纵指引符
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:flight_director_cue_az
    // 名  称:飞行操纵指引符方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    FLIGHT_DIRECTOR_CUE_AZ_TYPE_DEF flight_director_cue_az;

    // 标识符:flight_director_cue_el
    // 名  称:飞行操纵指引符俯仰
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    FLIGHT_DIRECTOR_CUE_EL_TYPE_DEF flight_director_cue_el;

} FLIGHT_DIRECTOR_CUE_TYPE_DEF;

// 信 号 组 标 识 符: ac_fast_climb_angle_increment
// 信 号 组 名    称: 载机最速爬升角增量
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_FAST_CLIMB_ANGLE_INCREMENT_TYPE_DEF;

// 信 号 组 标 识 符: fast_climb_paras
// 信 号 组 名    称: 最速爬升参数
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1;  // 保留字段

    // 标识符:validity_fast_climb_alt
    // 名  称:有效性_最速爬升高度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_fast_climb_alt;

    // 标识符:validity_fast_climb_mach
    // 名  称:有效性_最速爬升马赫
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_fast_climb_mach;

    // 标识符:validity_ac_fast_climb_angle_increment
    // 名  称:有效性_载机最速爬升角增量
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_ac_fast_climb_angle_increment;

    // 标识符:ac_fast_climb_angle_increment
    // 名  称:载机最速爬升角增量
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    AC_FAST_CLIMB_ANGLE_INCREMENT_TYPE_DEF ac_fast_climb_angle_increment;

    // 标识符:fast_climb_alt
    // 名  称:最速爬升高度
    // 说  明:[0,15000]米
    // 单  位:m
    // LSB  :1
    // 起始字:2
    // 起始位:16
    INT16 fast_climb_alt;

    // 标识符:fast_climb_mach
    // 名  称:最速爬升马赫
    // 说  明:[0,2.5]
    // 单  位:Mach
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    UINT16 fast_climb_mach;

} FAST_CLIMB_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: FAF_point_ground_distance
// 信 号 组 名    称: FAF地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机与FAF点的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} FAF_POINT_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: FAF_point_az
// 信 号 组 名    称: FAF点方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: FAF点到载机位置的连线与真北的夹角
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} FAF_POINT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: bullseye_point_plat_az
// 信 号 组 名    称: 波塞点平台系方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 载机相对于当前选择的波塞点的方位在平台系的投影。（即以波塞点为原点，从波塞点到载机位置的连线与真北的夹角）
typedef struct
{
    // 标识符:azimuth
    // 名  称:方位角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AZIMUTH_TYPE_DEF azimuth;

} BULLSEYE_POINT_PLAT_AZ_TYPE_DEF;

// 信 号 组 标 识 符: bullseye_point_ground_distance
// 信 号 组 名    称: 波塞点地面距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 当前选择波塞点与载机间的地面距离
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} BULLSEYE_POINT_GROUND_DISTANCE_TYPE_DEF;

// 信 号 组 标 识 符: bingo_fuel
// 信 号 组 名    称: bingo燃油量
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_mass
    // 名  称:_质量
    // 说  明:用于表示质量重量等信号值，带符号位是为了计算过程中可能会产生负值。
    //        表示精度为0.001kg，表示范围约+/-1000吨
    // 单  位:kg
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _mass;

} BINGO_FUEL_TYPE_DEF;

// 信 号 组 标 识 符: PRM_invalid_time
// 信 号 组 名    称: PRM失效时间
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} PRM_INVALID_TIME_TYPE_DEF;

// 信 号 组 标 识 符: initial_location
// 信 号 组 名    称: 初始位置
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-90,90]deg
//                    (-180,180]deg
//                    [-500,30000]m
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _latitude;

    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    INT32 _altitude;

} INITIAL_LOCATION_TYPE_DEF;

// 信 号 组 标 识 符: fast_align_heading
// 信 号 组 名    称: 快对航向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,360)deg
//                    在做存储航向对准时，快对航向=存储航向，做输入航向对准时，快对航向=输入航向。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} FAST_ALIGN_HEADING_TYPE_DEF;

// 信 号 组 标 识 符: INS_align_param
// 信 号 组 名    称: 惯导对准参数信息
// 信 号 组 字    数: 6
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:init_location_ctrl_type
    // 名  称:初始位置控制方式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 init_location_ctrl_type : 8;

    // 标识符:initial_location
    // 名  称:初始位置
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    //        [-500,30000]m
    // 单  位:
    // 起始字:1
    // 起始位:0
    INITIAL_LOCATION_TYPE_DEF initial_location;

    // 标识符:fast_align_heading
    // 名  称:快对航向
    // 说  明:[0,360)deg
    //        在做存储航向对准时，快对航向=存储航向，做输入航向对准时，快对航向=输入航向。
    // 单  位:
    // 起始字:4
    // 起始位:0
    FAST_ALIGN_HEADING_TYPE_DEF fast_align_heading;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:align_remain_time
    // 名  称:时间_对准倒计时
    // 说  明:[0,600]sec
    // 单  位:Sec
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 align_remain_time;

} INS_ALIGN_PARAM_TYPE_DEF;

// 信 号 组 标 识 符: IC_invalid_time
// 信 号 组 名    称: IC失效时间
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} IC_INVALID_TIME_TYPE_DEF;

// 信 号 组 标 识 符: position_los_cross
// 信 号 组 名    称: LOS交点位置
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _latitude;

} POSITION_LOS_CROSS_TYPE_DEF;

// 信 号 组 标 识 符: ground_height
// 信 号 组 名    称: 地形高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-500,10000]m
//                    地形高度。
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} GROUND_HEIGHT_TYPE_DEF;

// 信 号 组 标 识 符: file_reciever_IDs
// 信 号 组 名    称: 文件接收者ID
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 20
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

} FILE_RECIEVER_IDS_TYPE_DEF;

// 信 号 组 标 识 符: config_info_generated_time
// 信 号 组 名    称: 配置信息生成时间
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 软件、硬件、数据库配置信息收集的时间
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

    // 标识符:time_calendartime
    // 名  称:时间_日历时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT64 time_calendartime;

} CONFIG_INFO_GENERATED_TIME_TYPE_DEF;

// 信 号 组 标 识 符: stream_info_file
// 信 号 组 名    称: 文件流信息
// 信 号 组 字    数: 43
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 描述当前传输的流数据文件信息
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:loading_type
    // 名  称:加载类型
    // 说  明:描述文件/数据在的场景类型：
    //        1=在任务系统正常模式下进行的战术任务数据加载；
    //        2=在任务系统维护模式下进行的维护配置数据加载；
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 loading_type : 8;

    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 folder_id;

    // 标识符:folder_name
    // 名  称:文件夹名称
    // 说  明:加载文件名称，不大于5个字符
    // 单  位:
    // 起始字:2
    // 起始位:0
    char_8 folder_name[12];

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 file_id;

    // 标识符:file_name
    // 名  称:文件名称
    // 说  明:加载文件名称，不大于5个字符
    // 单  位:
    // 起始字:6
    // 起始位:0
    char_8 file_name[12];

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:secret_level
    // 名  称:密级
    // 说  明:目前只有非密/秘密两种密级，后续可能会增加更多的密级
    // 单  位:
    // 起始字:9
    // 起始位:0
    UINT32 secret_level : 8;

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //        软件版本号包括：
    //            1-2：机型识别码;
    //          3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //             11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //             12：字母“V”
    //        13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //        19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:10
    // 起始位:0
    char_8 ver_number[24];

    // 标识符:config_info_generated_time
    // 名  称:配置信息生成时间
    // 说  明:软件、硬件、数据库配置信息收集的时间
    // 单  位:
    // 起始字:16
    // 起始位:0
    CONFIG_INFO_GENERATED_TIME_TYPE_DEF config_info_generated_time;

    // 标识符:file_volume_byte
    // 名  称:文件体积
    // 说  明:描述文件体积大小，单位Byte。最大可表示不超过约4GB的文件。
    // 单  位:
    // LSB  :1
    // 起始字:19
    // 起始位:0
    UINT32 file_volume_byte;

    // 标识符:check_word
    // 名  称:校验字
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:0
    UINT32 check_word;

    // 标识符:file_reciever_IDs
    // 名  称:文件接收者ID
    // 说  明:
    // 单  位:
    // 起始字:21
    // 起始位:0
    FILE_RECIEVER_IDS_TYPE_DEF file_reciever_IDs[20];

    // 标识符:packet_total_number
    // 名  称:分包总数
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:41
    // 起始位:0
    UINT32 packet_total_number;

    // 标识符:packet_current_number
    // 名  称:当前包数
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:42
    // 起始位:0
    UINT32 packet_current_number;

} STREAM_INFO_FILE_TYPE_DEF;

// 信 号 组 标 识 符: HMC_Data_Item_MS_Sub
// 信 号 组 名    称: HMC数据项_任务子系统
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 10
// 信 号 组 说    明:
typedef struct
{
    // 标识符:HMC_LCN
    // 名  称:HMC_LCN
    // 说  明:LCN码，双座由8位改为9位
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 HMC_LCN;

    // 标识符:HMC_State
    // 名  称:HMC_State，发生1、消失0
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    BOOL_8 HMC_State;

    // 标识符:HMC_HASC
    // 名  称:HMC_HASC
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT8 HMC_HASC;

    // 标识符:HMC_HSC
    // 名  称:HMC_HSC
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 HMC_HSC;

    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT16 date_year;

    // 标识符:time_calendartime
    // 名  称:时间_日历时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT64 time_calendartime;

} HMC_DATA_ITEM_MS_SUB_TYPE_DEF;

// 信 号 组 标 识 符: MD5_check
// 信 号 组 名    称: MD5校验
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:MD5_a
    // 名  称:MD5_a
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 MD5_a;

    // 标识符:MD5_b
    // 名  称:MD5_b
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 MD5_b;

    // 标识符:MD5_c
    // 名  称:MD5_c
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 MD5_c;

    // 标识符:MD5_d
    // 名  称:MD5_d
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 MD5_d;

} MD5_CHECK_TYPE_DEF;

// 信 号 组 标 识 符: sys_network_state_OMP
// 信 号 组 名    称: 系统网络状态_OMP
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 128
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    // 标识符:off_state_YES_NO
    // 名  称:关机状态_是_否
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    UINT32 off_state_YES_NO : 8;

    // 标识符:VS1394_net_state
    // 名  称:飞管1394网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 VS1394_net_state : 8;

    // 标识符:AV1394_net_state
    // 名  称:航电1394网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 AV1394_net_state : 8;

    // 标识符:FC_net_state
    // 名  称:FC网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 FC_net_state : 8;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:PowOff_CMD_State
    // 名  称:下电指令状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 PowOff_CMD_State : 8;

    // 标识符:app_state
    // 名  称:应用软件状态
    // 说  明:正常运行时，应用软件状态仅为正常工作或非正常工作；
    //        仅在飞管系统进入OFP加载模式后，SYMM将所有功能单元的应用软件状态置为SW_LOAD，触发各子系统进入维护加载态。
    //        若任务系统处于正常运行态时，但某子系统或子系统某模块运行在软件加载态，则对应子系统状态置为SW_load。
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 app_state : 8;

} SYS_NETWORK_STATE_OMP_TYPE_DEF;

// 信 号 组 标 识 符: subsys_state_info
// 信 号 组 名    称: 子系统状态信息
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 60
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:subsys_work_state
    // 名  称:工作状态
    // 说  明:子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    //        20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
    //        20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
    //        20250515，增加应急状态，表示ICP处于28V供电的一个工作状态。
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 subsys_work_state : 8;

    // 标识符:subsys_main_mode
    // 名  称:工作模式
    // 说  明:描述系统的工作模式；
    //        初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 subsys_main_mode : 8;

    // 标识符:MFL_exist
    // 名  称:维护故障信息是否存在
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 MFL_exist : 8;

    // 标识符:start_remain_time
    // 名  称:时间_启动倒计时
    // 说  明:
    // 单  位:Sec
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT16 start_remain_time;

    // 标识符:bit_process_percent
    // 名  称:自检测进度
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    UINT16 bit_process_percent;

    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    // 说  明:表征子系统上电次数
    //        不能上报的功能单元将该信号置0
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 subsys_electrify_amount;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:subsys_HMC_total_list_number
    // 名  称:子系统HMC_总条数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 subsys_HMC_total_list_number;

} SUBSYS_STATE_INFO_TYPE_DEF;

// 信 号 组 标 识 符: SW_config_info
// 信 号 组 名    称: 软件配置信息
// 信 号 组 字    数: 26
// 信 号 组 数组长度: 7
// 信 号 组 说    明: 数据库信息以软件配置信息的格式一同发送，发送时软件CSCI信息，再发送数据库配置信息。
//                    软件版本信息，包含以下信息：
//                    1、数组元素有效性：表征该数组元素是否有效，当不需占用全部的数组元素时，未占用的元素该信号置无效。
//                    2、软件配置项代码：8位ASCII数字字母。
//                    3、软件名称：按标准发布的软件名称填写，不超过20个字符。
//                    4、版本号：软件当前版本信息，按统一格式编码。
//                    5、校验码：软件在地面生成时用于校验软件正确性的编码。
//                    6、加载时间：软件加载到机上的日历时间的年月日和时间。
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:version_type
    // 名  称:版本类型
    // 说  明:描述各子系统上报的软件版本的类型
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 version_type : 8;

    // 标识符:array_element_valid
    // 名  称:数组元素有效性
    // 说  明:如果信号组信号为一个数组，则应包含该信号，表征该数组元素是否有效，当信息不需占用全部的数组元素时，未占用的元素该信号置无效。
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 array_element_valid : 8;

    // 标识符:SW_CSCI_code
    // 名  称:软件配置项代码
    // 说  明:软件部件的工作单元代码，ASCII字符。
    // 单  位:
    // 起始字:1
    // 起始位:0
    char_8 SW_CSCI_code[8];

    // 标识符:software_name
    // 名  称:软件名称
    // 说  明:软件名称，不超过20个字符（汉字、数字、字母、符号）
    // 单  位:
    // 起始字:3
    // 起始位:0
    char_8 software_name[40];

    // 标识符:check_code
    // 名  称:软件校验码
    // 说  明:由6个字母数字组成,软件编译时间的时分秒：HHMMSS。ASCII字符
    // 单  位:
    // 起始字:13
    // 起始位:0
    char_8 check_code[8];

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //        软件版本号包括：
    //            1-2：机型识别码;
    //          3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //             11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //             12：字母“V”
    //        13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //        19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:15
    // 起始位:0
    char_8 ver_number[24];

    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:21
    // 起始位:0
    UINT32 folder_id;

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:22
    // 起始位:0
    UINT32 file_id;

    // 标识符:Time_Load
    // 名  称:加载时间
    // 说  明:加载软件、数据的日历时间，
    //        格式为：XXXX年XX月XX日  XX时XX分XX秒
    // 单  位:
    // 起始字:23
    // 起始位:0
    TIME_LOAD_TYPE_DEF Time_Load;

} SW_CONFIG_INFO_TYPE_DEF;

// 信 号 组 标 识 符: integrity_information_validity
// 信 号 组 名    称: 完好性信息_有效性
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_vertical_integrity_protect_threshold
    // 名  称:有效性_垂直完好性保护门限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_vertical_integrity_protect_threshold;

    // 标识符:validity_horizontial_integrity_protect_threshold
    // 名  称:有效性_水平完好性保护门限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_horizontial_integrity_protect_threshold;

} INTEGRITY_INFORMATION_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: integrity_information
// 信 号 组 名    称: 完好性信息
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:integrity_information_validity
    // 名  称:完好性信息_有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    INTEGRITY_INFORMATION_VALIDITY_TYPE_DEF integrity_information_validity;

    // 标识符:horizontial_integrity_protect_threshold
    // 名  称:水平完好性保护门限
    // 说  明:
    // 单  位:m
    // LSB  :1
    // 起始字:1
    // 起始位:0
    INT32 horizontial_integrity_protect_threshold;

    // 标识符:vertical_integrity_protect_threshold
    // 名  称:垂直完好性保护门限
    // 说  明:
    // 单  位:m
    // LSB  :1
    // 起始字:2
    // 起始位:0
    INT32 vertical_integrity_protect_threshold;

} INTEGRITY_INFORMATION_TYPE_DEF;

// 信 号 组 标 识 符: horizontal_position_accuracy
// 信 号 组 名    称: 水平位置精度
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: CEP（95%）
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:valid_invalid
    // 名  称:有效_无效
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 valid_invalid;

    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:1
    // 起始位:0
    INT32 _distance;

} HORIZONTAL_POSITION_ACCURACY_TYPE_DEF;

// 信 号 组 标 识 符: air_nav_data
// 信 号 组 名    称: 大气导航数据
// 信 号 组 字    数: 24
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:air_nav_data_validity
    // 名  称:大气导航数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    AIR_NAV_DATA_VALIDITY_TYPE_DEF air_nav_data_validity;

    // 标识符:ac_true_aoa
    // 名  称:载机真攻角
    // 说  明:[-20,60]deg
    // 单  位:
    // 起始字:7
    // 起始位:0
    AC_TRUE_AOA_TYPE_DEF ac_true_aoa;

    // 标识符:ac_true_side_slip_angle
    // 名  称:载机真侧滑角
    // 说  明:[-20,20]deg
    // 单  位:
    // 起始字:8
    // 起始位:0
    AC_TRUE_SIDE_SLIP_ANGLE_TYPE_DEF ac_true_side_slip_angle;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:9
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_cal_air_speed
    // 名  称:载机校准空速
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    AC_CAL_AIR_SPEED_TYPE_DEF ac_cal_air_speed;

    // 标识符:ac_mach
    // 名  称:载机马赫数
    // 说  明:[0,2.5]mach
    // 单  位:
    // 起始字:11
    // 起始位:0
    AC_MACH_TYPE_DEF ac_mach;

    // 标识符:ac_pressure_alt_rate
    // 名  称:载机气压高度变化率
    // 说  明:[-300,300]m/s
    //        即爬升率
    // 单  位:
    // 起始字:12
    // 起始位:0
    AC_PRESSURE_ALT_RATE_TYPE_DEF ac_pressure_alt_rate;

    // 标识符:baro_setting
    // 名  称:场压装订
    // 说  明:[54,107.5]kPa
    // 单  位:
    // 起始字:13
    // 起始位:0
    BARO_SETTING_TYPE_DEF baro_setting;

    // 标识符:baro_setting_alt
    // 名  称:场压装订高度
    // 说  明:[-500,5000]m
    // 单  位:
    // 起始字:14
    // 起始位:0
    BARO_SETTING_ALT_TYPE_DEF baro_setting_alt;

    // 标识符:AC_pressure_alt
    // 名  称:载机气压高度
    // 说  明:[-500,22800]m
    //        转发的大气高度
    // 单  位:
    // 起始字:15
    // 起始位:0
    AC_PRESSURE_ALT_TYPE_DEF AC_pressure_alt;

    // 标识符:ac_baro_alt
    // 名  称:载机气压参考高度
    // 说  明:[-5500,23300]m
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_BARO_ALT_TYPE_DEF ac_baro_alt;

    // 标识符:ac_total_temperature
    // 名  称:载机大气总温
    // 说  明:[-70,350])Cel 即[203.15,623.15]Kel
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_TOTAL_TEMPERATURE_TYPE_DEF ac_total_temperature;

    // 标识符:ac_free_airtemp
    // 名  称:载机大气静温
    // 说  明:[173.15,373.15]kel
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_FREE_AIRTEMP_TYPE_DEF ac_free_airtemp;

    // 标识符:ac_pressure_ratio
    // 名  称:载机大气压力比
    // 说  明:[0.033,1.1]
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_PRESSURE_RATIO_TYPE_DEF ac_pressure_ratio;

    // 标识符:ac_air_density_ratio
    // 名  称:载机大气密度比
    // 说  明:[0.0355,1.045]
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_AIR_DENSITY_RATIO_TYPE_DEF ac_air_density_ratio;

    // 标识符:true_static_pressure
    // 名  称:真实静压
    // 说  明:[1.7,108.4]kPa
    // 单  位:
    // 起始字:21
    // 起始位:0
    TRUE_STATIC_PRESSURE_TYPE_DEF true_static_pressure;

    // 标识符:cokpit_differential_pressure
    // 名  称:座舱压力差
    // 说  明:[-8,80]kPa
    // 单  位:
    // 起始字:22
    // 起始位:0
    COKPIT_DIFFERENTIAL_PRESSURE_TYPE_DEF cokpit_differential_pressure;

    // 标识符:cokpit_alt
    // 名  称:座舱高度
    // 说  明:[-2000,20567]m
    // 单  位:
    // 起始字:23
    // 起始位:0
    COKPIT_ALT_TYPE_DEF cokpit_alt;

} AIR_NAV_DATA_TYPE_DEF;

// 信 号 组 标 识 符: wind_vel_left_right
// 信 号 组 名    称: 风速_左侧_右侧
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,150]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_VEL_LEFT_RIGHT_TYPE_DEF;

// 信 号 组 标 识 符: wind_vel_head_tail
// 信 号 组 名    称: 风速_迎头_尾后
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,150]m/s
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} WIND_VEL_HEAD_TAIL_TYPE_DEF;

// 信 号 组 标 识 符: forward_side_wind_vel
// 信 号 组 名    称: 正侧向风速
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:left_right
    // 名  称:左侧右侧
    // 说  明:描述风速的相对机身左右方向：
    //        =LEFT，表示左侧风向
    //        =RIGHT，表右侧风向
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 left_right : 8;

    // 标识符:head_tail
    // 名  称:迎头尾后
    // 说  明:描述风速的迎头尾后方向：
    //        =Head，表示迎头风向
    //        =Tail，表尾后风向
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 head_tail : 8;

    // 标识符:validity_wind_forward_side
    // 名  称:有效性_正侧风速
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 validity_wind_forward_side : 8;

    // 标识符:wind_vel_head_tail
    // 名  称:风速_迎头_尾后
    // 说  明:[0,150]m/s
    // 单  位:
    // 起始字:1
    // 起始位:0
    WIND_VEL_HEAD_TAIL_TYPE_DEF wind_vel_head_tail;

    // 标识符:wind_vel_left_right
    // 名  称:风速_左侧_右侧
    // 说  明:[0,150]m/s
    // 单  位:
    // 起始字:2
    // 起始位:0
    WIND_VEL_LEFT_RIGHT_TYPE_DEF wind_vel_left_right;

} FORWARD_SIDE_WIND_VEL_TYPE_DEF;

// 信 号 组 标 识 符: ac_climbing_angle_predicted_increment
// 信 号 组 名    称: 载机预测爬升角增量
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 系统根据载机当前运动加速度及大气参数预测爬升角增量，用于表征载机的当前剩余功率。
//                    （载机预测爬升角+载机当前爬升角）的取值范围[-90,90]deg
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} AC_CLIMBING_ANGLE_PREDICTED_INCREMENT_TYPE_DEF;

// 信 号 组 标 识 符: ac_climbing_angle_predicted
// 信 号 组 名    称: 载机预测爬升角
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:validity_ac_climbing_angle_predicted_increment
    // 名  称:有效性_载机预测爬升角增量
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_ac_climbing_angle_predicted_increment;

    // 标识符:ac_climbing_angle_predicted_increment
    // 名  称:载机预测爬升角增量
    // 说  明:系统根据载机当前运动加速度及大气参数预测爬升角增量，用于表征载机的当前剩余功率。
    //        （载机预测爬升角+载机当前爬升角）的取值范围[-90,90]deg
    // 单  位:
    // 起始字:1
    // 起始位:0
    AC_CLIMBING_ANGLE_PREDICTED_INCREMENT_TYPE_DEF ac_climbing_angle_predicted_increment;

} AC_CLIMBING_ANGLE_PREDICTED_TYPE_DEF;

// 信 号 组 标 识 符: ac_flight_vector_C
// 信 号 组 名    称: 载机飞行矢量数据C
// 信 号 组 字    数: 7
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:forward_side_wind_vel
    // 名  称:正侧向风速
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    FORWARD_SIDE_WIND_VEL_TYPE_DEF forward_side_wind_vel;

    // 标识符:ac_climbing_angle_predicted
    // 名  称:载机预测爬升角
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    AC_CLIMBING_ANGLE_PREDICTED_TYPE_DEF ac_climbing_angle_predicted;

} AC_FLIGHT_VECTOR_C_TYPE_DEF;

// 信 号 组 标 识 符: ac_flight_vector_B
// 信 号 组 名    称: 载机飞行矢量数据B
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:above_ground_height_type
    // 名  称:地形相对高度类型
    // 说  明:0：表示地形高度采用DTED来源；
    //        1：表示无线电测相对地形高度；
    //        2：表示采用装订气压高度作为地形高度。
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 above_ground_height_type : 8;

    // 标识符:validity_ground_height
    // 名  称:有效性_地形高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 validity_ground_height : 8;

    // 标识符:validity_above_ground_height
    // 名  称:有效性_地形相对高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 validity_above_ground_height : 8;

    // 标识符:above_ground_height
    // 名  称:地形相对高度
    // 说  明:[-500,30000]m
    //        相对地形高度。
    // 单  位:
    // 起始字:3
    // 起始位:0
    ABOVE_GROUND_HEIGHT_TYPE_DEF above_ground_height;

    // 标识符:ground_height
    // 名  称:地形高度
    // 说  明:[-500,10000]m
    //        地形高度。
    // 单  位:
    // 起始字:4
    // 起始位:0
    GROUND_HEIGHT_TYPE_DEF ground_height;

} AC_FLIGHT_VECTOR_B_TYPE_DEF;

// 信 号 组 标 识 符: horizontal_wind_vel_dir
// 信 号 组 名    称: 水平风速风向
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [0,150]m/s;
//                    [0,360)deg;
//                    与真北的夹角顺时针为正。
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:wind_data_source
    // 名  称:风速风向数据源
    // 说  明:描述风速风向的数据来源：
    //        =INS，表示风速风向来自于惯导；
    //        =DCS，表述风速风向来自于与人工通过显控修改。
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 wind_data_source : 8;

    // 标识符:wind_direction_level
    // 名  称:风向_水平
    // 说  明:[0，360)deg
    //        风的来向与真北的夹角
    // 单  位:
    // 起始字:1
    // 起始位:0
    WIND_DIRECTION_LEVEL_TYPE_DEF wind_direction_level;

    // 标识符:wind_vel_level
    // 名  称:风速_水平
    // 说  明:[0,150]m/s
    // 单  位:
    // 起始字:2
    // 起始位:0
    WIND_VEL_LEVEL_TYPE_DEF wind_vel_level;

} HORIZONTAL_WIND_VEL_DIR_TYPE_DEF;

// 信 号 组 标 识 符: ac_flight_vector_validity
// 信 号 组 名    称: 载机飞行矢量数据_有效性
// 信 号 组 字    数: 15
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_mag_heading
    // 名  称:有效性_磁航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_mag_heading;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    SPARE8 spare1;  // 保留字段

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    BOOL_8 validity_roll_rate;

    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    BOOL_8 validity_pitch_rate;

    SPARE8 spare2;  // 保留字段

    // 标识符:validity_angle_rate_Z
    // 名  称:有效性_角速率Z轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    BOOL_8 validity_angle_rate_Z;

    // 标识符:validity_angle_rate_Y
    // 名  称:有效性_角速率Y轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    BOOL_8 validity_angle_rate_Y;

    // 标识符:validity_angle_rate_X
    // 名  称:有效性_角速率X轴
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    BOOL_8 validity_angle_rate_X;

    SPARE8 spare3;  // 保留字段

    // 标识符:validity_accel_Z
    // 名  称:有效性_加速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    BOOL_8 validity_accel_Z;

    // 标识符:validity_accel_Y
    // 名  称:有效性_加速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    BOOL_8 validity_accel_Y;

    // 标识符:validity_accel_X
    // 名  称:有效性_加速度X轴
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    BOOL_8 validity_accel_X;

    SPARE8 spare4;  // 保留字段

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    BOOL_8 validity_accel_north;

    SPARE8 spare5;  // 保留字段

    // 标识符:validity_vel_Z
    // 名  称:有效性_速度Z轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:16
    BOOL_8 validity_vel_Z;

    // 标识符:validity_vel_Y
    // 名  称:有效性_速度Y轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    BOOL_8 validity_vel_Y;

    // 标识符:validity_vel_X
    // 名  称:有效性_速度X轴
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    BOOL_8 validity_vel_X;

    SPARE8 spare6;  // 保留字段

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:8
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    BOOL_8 validity_vel_north;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:24
    BOOL_8 validity_climbing_angle;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:16
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:8
    BOOL_8 validity_ground_speed;

    // 标识符:validity_total_vel
    // 名  称:有效性_总速
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    BOOL_8 validity_total_vel;

    // 标识符:validity_G_force
    // 名  称:有效性_法向过载
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_G_force;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_inertial_AOA;

    SPARE8 spare7[2];  // 保留字段

    // 标识符:validity_plat_to_body_matrix
    // 名  称:有效性_平台系到机体转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_plat_to_body_matrix;

    // 标识符:validity_earth_to_plat_matrix
    // 名  称:有效性_地球系到地理系转换矩阵
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_earth_to_plat_matrix;

    SPARE8 spare8;  // 保留字段

    // 标识符:validity_wind_up
    // 名  称:有效性_风速天向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:16
    BOOL_8 validity_wind_up;

    // 标识符:validity_wind_west
    // 名  称:有效性_风速西向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:8
    BOOL_8 validity_wind_west;

    // 标识符:validity_wind_north
    // 名  称:有效性_风速北向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    BOOL_8 validity_wind_north;

    // 标识符:validity_GNSS_inertial_ADS_alt
    // 名  称:有效性_惯性卫星大气高度
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:24
    BOOL_8 validity_GNSS_inertial_ADS_alt;

    // 标识符:validity_vel_up_adjusted
    // 名  称:有效性_修正天向速度
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:16
    BOOL_8 validity_vel_up_adjusted;

    // 标识符:validity_wind_vel_level
    // 名  称:有效性_风速水平
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    BOOL_8 validity_wind_vel_level;

    // 标识符:validity_wind_direction_level
    // 名  称:有效性_风向水平
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    BOOL_8 validity_wind_direction_level;

    SPARE8 spare9;  // 保留字段

    // 标识符:validity_baro_reference_alt
    // 名  称:有效性_参考高度
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:16
    BOOL_8 validity_baro_reference_alt;

    // 标识符:validity_height
    // 名  称:有效性_海拔高度
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:8
    BOOL_8 validity_height;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    BOOL_8 validity_position;

    SPARE8 spare10;  // 保留字段

    // 标识符:validity_roz
    // 名  称:有效性_ROZ
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:16
    BOOL_8 validity_roz;

    // 标识符:validity_local_gravity
    // 名  称:有效性_本地重力加速度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    BOOL_8 validity_local_gravity;

    // 标识符:validity_local_magnetic_variation
    // 名  称:有效性_本地磁差
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    BOOL_8 validity_local_magnetic_variation;

    SPARE8 spare11[3];  // 保留字段

    // 标识符:validity_flight_path_acc
    // 名  称:有效性_飞行加速度
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    BOOL_8 validity_flight_path_acc;

} AC_FLIGHT_VECTOR_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: ac_baro_reference_alt
// 信 号 组 名    称: 载机参考高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-5500,30000]m
//                    相对场高高度。
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_BARO_REFERENCE_ALT_TYPE_DEF;

// 信 号 组 标 识 符: ac_flight_vector
// 信 号 组 名    称: 载机飞行矢量数据
// 信 号 组 字    数: 81
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:ac_flight_vector_validity
    // 名  称:载机飞行矢量数据_有效性
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    AC_FLIGHT_VECTOR_VALIDITY_TYPE_DEF ac_flight_vector_validity;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:AC_mag_heading
    // 名  称:载机磁航向
    // 说  明:[0,360)deg
    //        相对于磁北顺时针为正
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_MAG_HEADING_TYPE_DEF AC_mag_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:23
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_body_axis_rate
    // 名  称:机体系角速率
    // 说  明:[-720,720]deg/s;[-720,720]deg/s;[-720,720]deg/s
    //        飞机相对于惯性系的转动角速率在机体系的投影，即陀螺测量到的角速率。
    // 单  位:
    // 起始字:24
    // 起始位:0
    AC_BODY_AXIS_RATE_TYPE_DEF ac_body_axis_rate;

    // 标识符:ac_body_accel
    // 名  称:机体系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    //        注：该加速度包含重力加速度。
    // 单  位:
    // 起始字:27
    // 起始位:0
    AC_BODY_ACCEL_TYPE_DEF ac_body_accel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:30
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_body_vel
    // 名  称:机体系速度
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_BODY_VEL_TYPE_DEF ac_body_vel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_total_vel
    // 名  称:载机总速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:39
    // 起始位:0
    AC_TOTAL_VEL_TYPE_DEF ac_total_vel;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:40
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:41
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //        爬升为正
    // 单  位:
    // 起始字:42
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //        速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:43
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //        速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:44
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //        速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:45
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_G_force
    // 名  称:载机法向过载
    // 说  明:[-9.9,9.9]g
    // 单  位:
    // 起始字:46
    // 起始位:0
    AC_G_FORCE_TYPE_DEF ac_G_force;

    // 标识符:_earth_to_plat_matrix
    // 名  称:地球系到地理系转换矩阵
    // 说  明:_系数xx = cos(AC_LAT)
    //        _系数xy = 0
    //        _系数xz = -sin(AC_LAT)
    // 单  位:
    // 起始字:47
    // 起始位:0
    _EARTH_TO_PLAT_MATRIX_TYPE_DEF _earth_to_plat_matrix;

    // 标识符:plat_to_body_matrix
    // 名  称:平台系到机体转换矩阵
    // 说  明:_系数xx =  COS(φ) * COS(θ).
    //        _系数xy = -SIN(φ) * COS(θ).
    //        _系数xz = SIN(θ)
    //        _系数yx = COS(φ) * SIN(θ) * SIN(ξ) - SIN(φ) * COS(ξ)
    //        _系数yy = -COS(φ) * COS(ξ) - SIN(φ) * SIN(θ) * SIN(ξ)
    //        _系数yz = -COS(θ) * SIN(ξ)
    //        _系数zx = SIN(φ) * SIN(ξ) + COS(φ) * SIN(θ) * COS(ξ)
    //        _系数zy = COS(φ) * SIN(ξ) - SIN(φ) * SIN(θ) * COS(ξ)
    //        _系数zz = -COS(θ) * COS(ξ)
    //        φ=AC_Ture_Heading
    //        θ=AC_Pitch
    //        ξ=AC_Roll
    // 单  位:
    // 起始字:56
    // 起始位:0
    PLAT_TO_BODY_MATRIX_TYPE_DEF plat_to_body_matrix;

    // 标识符:ac_wind_vel
    // 名  称:载机风速矢量
    // 说  明:[-100,100]m/s
    //        [-100,100]m/s
    //        [-100,100]m/s
    // 单  位:
    // 起始字:65
    // 起始位:0
    AC_WIND_VEL_TYPE_DEF ac_wind_vel;

    // 标识符:horizontal_wind_vel_dir
    // 名  称:水平风速风向
    // 说  明:[0,150]m/s;
    //        [0,360)deg;
    //        与真北的夹角顺时针为正。
    // 单  位:
    // 起始字:68
    // 起始位:0
    HORIZONTAL_WIND_VEL_DIR_TYPE_DEF horizontal_wind_vel_dir;

    // 标识符:ac_Vel_Up_adjusted
    // 名  称:修正天向速度
    // 说  明:[-1000,1000]m/s
    //        惯性/大气/卫星组合的天向速度
    // 单  位:
    // 起始字:71
    // 起始位:0
    AC_VEL_UP_ADJUSTED_TYPE_DEF ac_Vel_Up_adjusted;

    // 标识符:AC_GNSS_inertial_ADS_alt
    // 名  称:载机惯性卫星大气高度
    // 说  明:[-2500,30000]m
    //        INS/卫星/ADS组合高度
    // 单  位:
    // 起始字:72
    // 起始位:0
    AC_GNSS_INERTIAL_ADS_ALT_TYPE_DEF AC_GNSS_inertial_ADS_alt;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //        (-180,180]deg
    // 单  位:
    // 起始字:73
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:ac_height
    // 名  称:载机海拔高度
    // 说  明:[-500,30000]m
    //        融合后载机海拔高度。
    // 单  位:
    // 起始字:75
    // 起始位:0
    AC_HEIGHT_TYPE_DEF ac_height;

    // 标识符:ac_baro_reference_alt
    // 名  称:载机参考高度
    // 说  明:[-5500,30000]m
    //        相对场高高度。
    // 单  位:
    // 起始字:76
    // 起始位:0
    AC_BARO_REFERENCE_ALT_TYPE_DEF ac_baro_reference_alt;

    // 标识符:local_magnetic_variation
    // 名  称:本地磁差
    // 说  明:[-90,90]deg
    //        飞机所在位置的磁差
    // 单  位:
    // 起始字:77
    // 起始位:0
    LOCAL_MAGNETIC_VARIATION_TYPE_DEF local_magnetic_variation;

    // 标识符:local_gravity
    // 名  称:本地重力加速度
    // 说  明:[9.5,10]m/s/s
    // 单  位:
    // 起始字:78
    // 起始位:0
    LOCAL_GRAVITY_TYPE_DEF local_gravity;

    // 标识符:roz
    // 名  称:ROZ
    // 说  明:[-0.1,0.1]mrad/s
    //        由于飞机在地球上运动而产生的航向变化率
    //        Roz = -(VEL_WEST*tan(LAT))/(R*(1+sin^2(LAT)*e)+ ALT)
    // 单  位:
    // 起始字:79
    // 起始位:0
    ROZ_TYPE_DEF roz;

    // 标识符:flight_path_acc
    // 名  称:载机飞行加速度
    // 说  明:[-4,4]g
    //        表示载机飞行轨迹（速度矢量）方向上的加速度，延飞行轨迹（速度矢量）方向加速为正。
    //        当轮载在地面且地速小于150km/h时，强制输出为0；否则按计算值输出。
    // 单  位:
    // 起始字:80
    // 起始位:0
    FLIGHT_PATH_ACC_TYPE_DEF flight_path_acc;

} AC_FLIGHT_VECTOR_TYPE_DEF;

// 信 号 组 标 识 符: time_calendar_config
// 信 号 组 名    称: 时间_日历时间配置
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:time_zone
    // 名  称:时间_时区
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    INT32 time_zone : 8;

    // 标识符:time_calendar_sync_type
    // 名  称:时间_日历时间授时同步方式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 time_calendar_sync_type : 8;

} TIME_CALENDAR_CONFIG_TYPE_DEF;

// 信 号 组 标 识 符: wide_image_paras_mark
// 信 号 组 名    称: 广域成像修改标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 23;  // 保留字段
    // 标识符:RNG_DIRECTION_CHG
    // 名  称:扫描方向修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 RNG_DIRECTION_CHG : 1;

    // 标识符:D_HEIGHT_CHG
    // 名  称:距离优先高度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:7
    UINT32 D_HEIGHT_CHG : 1;

    // 标识符:AZ_HEIGHT_CHG
    // 名  称:方位优先高度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:6
    UINT32 AZ_HEIGHT_CHG : 1;

    // 标识符:END_ANGLE_CHG
    // 名  称:结束角度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:5
    UINT32 END_ANGLE_CHG : 1;

    // 标识符:START_ANGLE_CHG
    // 名  称:起始角度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:4
    UINT32 START_ANGLE_CHG : 1;

    // 标识符:RNG_CHG
    // 名  称:量程修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 RNG_CHG : 1;

    // 标识符:RNG_UP_CHG
    // 名  称:远界距离修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 RNG_UP_CHG : 1;

    // 标识符:RNG_LOW_CHG
    // 名  称:近界距离修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 RNG_LOW_CHG : 1;

    // 标识符:SUB_MODE_CHG
    // 名  称:广域成像子模式修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 SUB_MODE_CHG : 1;

} WIDE_IMAGE_PARAS_MARK_TYPE_DEF;

// 信 号 组 标 识 符: IR_wide_image_paras_req
// 信 号 组 名    称: IR广域成像范围参数_请求
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:wide_image_paras_mark
    // 名  称:广域成像修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    WIDE_IMAGE_PARAS_MARK_TYPE_DEF wide_image_paras_mark;

    // 标识符:IR_range_lowline
    // 名  称:IR距离近界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:1
    // 起始位:16
    UINT32 IR_range_lowline : 16;

    UINT32 spare1 : 10;  // 保留字段
    // 标识符:IR_WIDE_IMAGE_DIRECTION
    // 名  称:光电广域成像扫描方向
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:3
    UINT32 IR_WIDE_IMAGE_DIRECTION : 3;

    // 标识符:IR_WIDE_IMAGE_MODE
    // 名  称:光电广域成像子模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 IR_WIDE_IMAGE_MODE : 3;

    // 标识符:IR_IMAGE_RANGE
    // 名  称:量程
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:2
    // 起始位:16
    UINT16 IR_IMAGE_RANGE;

    // 标识符:IR_range_upline
    // 名  称:IR距离远界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    UINT16 IR_range_upline;

    // 标识符:IR_scan_end_angle
    // 名  称:光电扫描结束角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.01
    // 起始字:3
    // 起始位:16
    INT16 IR_scan_end_angle;

    // 标识符:IR_scan_start_angle
    // 名  称:光电扫描起始角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.01
    // 起始字:3
    // 起始位:0
    INT16 IR_scan_start_angle;

    // 标识符:D_area_altitude
    // 名  称:距离优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:4
    // 起始位:16
    INT16 D_area_altitude;

    // 标识符:AZ_area_altitude
    // 名  称:方位优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:4
    // 起始位:0
    INT16 AZ_area_altitude;

} IR_WIDE_IMAGE_PARAS_REQ_TYPE_DEF;

// 信 号 组 标 识 符: vertical_deviation
// 信 号 组 名    称: 垂直方向偏差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} VERTICAL_DEVIATION_TYPE_DEF;

// 信 号 组 标 识 符: origin_pixle_Y
// 信 号 组 名    称: 图像原点坐标Y
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} ORIGIN_PIXLE_Y_TYPE_DEF;

// 信 号 组 标 识 符: origin_pixle_X
// 信 号 组 名    称: 图像原点坐标X
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} ORIGIN_PIXLE_X_TYPE_DEF;

// 信 号 组 标 识 符: horizontal_deviation
// 信 号 组 名    称: 水平方向偏差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} HORIZONTAL_DEVIATION_TYPE_DEF;

// 信 号 组 标 识 符: IR_TGT_TRACK_INFO
// 信 号 组 名    称: 图像跟踪信息
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 20;  // 保留字段
    // 标识符:TGT_TRACK_ID
    // 名  称:动目标ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 TGT_TRACK_ID : 4;

    // 标识符:data_valid
    // 名  称:数据有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 data_valid : 8;

    // 标识符:origin_pixle_X
    // 名  称:图像原点坐标X
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    ORIGIN_PIXLE_X_TYPE_DEF origin_pixle_X;

    // 标识符:origin_pixle_Y
    // 名  称:图像原点坐标Y
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    ORIGIN_PIXLE_Y_TYPE_DEF origin_pixle_Y;

    // 标识符:horizontal_deviation
    // 名  称:水平方向偏差
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    HORIZONTAL_DEVIATION_TYPE_DEF horizontal_deviation;

    // 标识符:vertical_deviation
    // 名  称:垂直方向偏差
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    VERTICAL_DEVIATION_TYPE_DEF vertical_deviation;

} IR_TGT_TRACK_INFO_TYPE_DEF;

// 信 号 组 标 识 符: image_paras_mark
// 信 号 组 名    称: 可见光修改标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 28;  // 保留字段
    // 标识符:ENHANCE_CHG
    // 名  称:增强修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 ENHANCE_CHG : 1;

    // 标识符:mist_eliminate_CHG
    // 名  称:可见光去雾修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 mist_eliminate_CHG : 1;

    // 标识符:focus_CHG
    // 名  称:调焦修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 focus_CHG : 1;

    // 标识符:dim_CHG
    // 名  称:调光修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 dim_CHG : 1;

} IMAGE_PARAS_MARK_TYPE_DEF;

// 信 号 组 标 识 符: IR_image_paras_light
// 信 号 组 名    称: IR可见光图像参数
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:image_paras_mark
    // 名  称:可见光修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    IMAGE_PARAS_MARK_TYPE_DEF image_paras_mark;

    // 标识符:light_value
    // 名  称:调光值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:24
    INT32 light_value : 8;

    // 标识符:light_focus_mode
    // 名  称:可见光调焦模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 light_focus_mode : 8;

    // 标识符:light_dim_mode
    // 名  称:可见光调光模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 light_dim_mode : 8;

    UINT32 spare1 : 8;  // 保留字段

    // 标识符:light_enhance_mode
    // 名  称:可见光增强状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    UINT32 light_enhance_mode : 8;

    // 标识符:light_mist_eliminate_state
    // 名  称:可见光去雾状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 light_mist_eliminate_state : 8;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:focus_value
    // 名  称:调焦值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    INT32 focus_value : 8;

} IR_IMAGE_PARAS_LIGHT_TYPE_DEF;

// 信 号 组 标 识 符: image_infra_mark
// 信 号 组 名    称: 红外修改标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 28;  // 保留字段
    // 标识符:video_polar_CHG
    // 名  称:视频极化修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 video_polar_CHG : 1;

    // 标识符:ENHANCE_CHG
    // 名  称:增强修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 ENHANCE_CHG : 1;

    // 标识符:focus_CHG
    // 名  称:调焦修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 focus_CHG : 1;

    // 标识符:dim_CHG
    // 名  称:调光修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 dim_CHG : 1;

} IMAGE_INFRA_MARK_TYPE_DEF;

// 信 号 组 标 识 符: IR_image_paras_infra
// 信 号 组 名    称: IR红外图像参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:image_infra_mark
    // 名  称:红外修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    IMAGE_INFRA_MARK_TYPE_DEF image_infra_mark;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:infrared_focus_mode
    // 名  称:红外调焦模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 infrared_focus_mode : 8;

    // 标识符:infrared_dim_mode
    // 名  称:红外调光模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 infrared_dim_mode : 8;

    UINT32 spare1 : 8;  // 保留字段

    SPARE8 spare3[2];  // 保留字段

    // 标识符:light_value
    // 名  称:调光值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:8
    INT8 light_value;

    // 标识符:focus_value
    // 名  称:调焦值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    INT8 focus_value;

    UINT32 spare4 : 16;  // 保留字段
    // 标识符:infrared_enhance_mode
    // 名  称:红外增强状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 infrared_enhance_mode : 8;

    // 标识符:video_polar
    // 名  称:视频极化
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 video_polar : 8;

} IR_IMAGE_PARAS_INFRA_TYPE_DEF;

// 信 号 组 标 识 符: center_point_pos
// 信 号 组 名    称: 中心点位置
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    INT32 _longitude;

    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    INT32 _altitude;

} CENTER_POINT_POS_TYPE_DEF;

// 信 号 组 标 识 符: area_monitor_paras_mark
// 信 号 组 名    称: 区域监视修改标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 29;  // 保留字段
    // 标识符:HEIGHT_CHG
    // 名  称:高度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 HEIGHT_CHG : 1;

    // 标识符:LATI_CHG
    // 名  称:纬度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 LATI_CHG : 1;

    // 标识符:LONG_CHG
    // 名  称:经度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 LONG_CHG : 1;

} AREA_MONITOR_PARAS_MARK_TYPE_DEF;

// 信 号 组 标 识 符: area_monitor_paras
// 信 号 组 名    称: IR区域监视范围参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:area_monitor_paras_mark
    // 名  称:区域监视修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AREA_MONITOR_PARAS_MARK_TYPE_DEF area_monitor_paras_mark;

    // 标识符:center_point_pos
    // 名  称:中心点位置
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    CENTER_POINT_POS_TYPE_DEF center_point_pos;

} AREA_MONITOR_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: area_image_paras_mark
// 信 号 组 名    称: 区域成像修改标识
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 21;  // 保留字段
    // 标识符:IMG_MODE_CHG
    // 名  称:成像方式修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:10
    UINT32 IMG_MODE_CHG : 1;

    // 标识符:LENGTH_CHG
    // 名  称:区域边长修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:9
    UINT32 LENGTH_CHG : 1;

    // 标识符:HEIGHT_CHG
    // 名  称:高度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 HEIGHT_CHG : 1;

    // 标识符:LATI_CHG
    // 名  称:纬度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:7
    UINT32 LATI_CHG : 1;

    // 标识符:LONG_CHG
    // 名  称:经度修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:6
    UINT32 LONG_CHG : 1;

    // 标识符:AREA3_CHG
    // 名  称:区域3修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:4
    UINT32 AREA3_CHG : 2;

    // 标识符:AREA2_CHG
    // 名  称:区域2修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 AREA2_CHG : 2;

    // 标识符:AREA1_CHG
    // 名  称:区域1修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 AREA1_CHG : 2;

} AREA_IMAGE_PARAS_MARK_TYPE_DEF;

// 信 号 组 标 识 符: area_image_paras_req
// 信 号 组 名    称: IR区域成像范围参数_请求
// 信 号 组 字    数: 6
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:area_image_paras_mark
    // 名  称:区域成像修改标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    AREA_IMAGE_PARAS_MARK_TYPE_DEF area_image_paras_mark;

    // 标识符:center_point_pos
    // 名  称:中心点位置
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    CENTER_POINT_POS_TYPE_DEF center_point_pos;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:AREA_num
    // 名  称:区域编号
    // 说  明:表征区域编号数值
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:8
    UINT8 AREA_num;

    // 标识符:IR_AREA_LENGTH
    // 名  称:光电区域边长
    // 说  明:
    // 单  位:km
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT8 IR_AREA_LENGTH;

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:IR_IMG_MODE
    // 名  称:光电成像方式
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 IR_IMG_MODE : 8;

} AREA_IMAGE_PARAS_REQ_TYPE_DEF;

// 信 号 组 标 识 符: unique_act_req_paras_IRST
// 信 号 组 名    称: 特殊活动请求附加参数_IRST
// 信 号 组 字    数: 33
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:irst_work_state
    // 名  称:IRST工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 irst_work_state : 8;

    // 标识符:IR_image_paras_light
    // 名  称:IR可见光图像参数
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    IR_IMAGE_PARAS_LIGHT_TYPE_DEF IR_image_paras_light;

    // 标识符:IR_image_paras_infra
    // 名  称:IR红外图像参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    IR_IMAGE_PARAS_INFRA_TYPE_DEF IR_image_paras_infra;

    UINT32 spare2 : 16;  // 保留字段
    // 标识符:irst_form_mode
    // 名  称:IRST成像模式
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    UINT32 irst_form_mode : 8;

    // 标识符:Transom_mist_eliminate_state
    // 名  称:光窗去雾状态
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    UINT32 Transom_mist_eliminate_state : 8;

    // 标识符:IR_wide_image_paras_req
    // 名  称:IR广域成像范围参数_请求
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    IR_WIDE_IMAGE_PARAS_REQ_TYPE_DEF IR_wide_image_paras_req;

    SPARE32 spare3[1];  // 保留字段

    // 标识符:area_image_paras_req
    // 名  称:IR区域成像范围参数_请求
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    AREA_IMAGE_PARAS_REQ_TYPE_DEF area_image_paras_req;

    SPARE32 spare4[1];  // 保留字段

    UINT32 spare5 : 24;  // 保留字段
    // 标识符:IRST_Video_BAND
    // 名  称:IRST_区域监视视频带宽
    // 说  明:
    // 单  位:
    // 起始字:22
    // 起始位:0
    UINT32 IRST_Video_BAND : 8;

    // 标识符:area_monitor_paras
    // 名  称:IR区域监视范围参数
    // 说  明:
    // 单  位:
    // 起始字:23
    // 起始位:0
    AREA_MONITOR_PARAS_TYPE_DEF area_monitor_paras;

    // 标识符:IR_TGT_TRACK_INFO
    // 名  称:图像跟踪信息
    // 说  明:
    // 单  位:
    // 起始字:27
    // 起始位:0
    IR_TGT_TRACK_INFO_TYPE_DEF IR_TGT_TRACK_INFO;

    UINT32 spare7 : 8;  // 保留字段
    // 标识符:environmnet_type
    // 名  称:环境类型
    // 说  明:
    // 单  位:
    // 起始字:32
    // 起始位:16
    UINT32 environmnet_type : 8;

    UINT32 spare6 : 8;  // 保留字段
    // 标识符:IR_SENSOR
    // 名  称:光电传感器状态
    // 说  明:
    // 单  位:
    // 起始字:32
    // 起始位:0
    UINT32 IR_SENSOR : 8;

} UNIQUE_ACT_REQ_PARAS_IRST_TYPE_DEF;

// 信 号 组 标 识 符: general_act_req_paras
// 信 号 组 名    称: 通用活动请求附加参数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 该信号仅在“通用活动请求”枚举值不为“NA”或“特殊活动请求”时有效
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:MFL_operation
    // 名  称:MFL操作类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 MFL_operation : 8;

    // 标识符:bit_mode
    // 名  称:自检测模式
    // 说  明:只有IBIT和MBIT可以作为命令下发
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 bit_mode : 8;

    // 标识符:subsys_main_oper_mode
    // 名  称:子系统工作模式
    // 说  明:描述系统的工作模式；
    //        初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subsys_main_oper_mode : 8;

} GENERAL_ACT_REQ_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: calibirate_paras_test
// 信 号 组 名    称: 光轴偏差参数_测试值
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:TrackMdfY
    // 名  称:跟踪修正偏差Y
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    INT32 TrackMdfY : 8;

    // 标识符:TrackMdfX
    // 名  称:跟踪修正偏差X
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    INT32 TrackMdfX : 8;

    // 标识符:calibrate_data_validity
    // 名  称:光轴偏差参数有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 calibrate_data_validity : 8;

} CALIBIRATE_PARAS_TEST_TYPE_DEF;

// 信 号 组 标 识 符: calibirate_paras_cureent
// 信 号 组 名    称: 光轴偏差参数_当前值
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:TrackMdfY
    // 名  称:跟踪修正偏差Y
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    INT32 TrackMdfY : 8;

    // 标识符:TrackMdfX
    // 名  称:跟踪修正偏差X
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    INT32 TrackMdfX : 8;

    // 标识符:calibrate_data_validity
    // 名  称:光轴偏差参数有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 calibrate_data_validity : 8;

} CALIBIRATE_PARAS_CUREENT_TYPE_DEF;

// 信 号 组 标 识 符: VMS1394_VMC_State
// 信 号 组 名    称: VMS1394_VMC_状态字
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:VMS1394_VMC_A_CHV
    // 名  称:VMS1394_有效性_A通道
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:31
    UINT32 VMS1394_VMC_A_CHV : 1;

    // 标识符:VMS1394_VMC_B_CHV
    // 名  称:VMS1394_有效性_B通道
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:30
    UINT32 VMS1394_VMC_B_CHV : 1;

    // 标识符:VMS1394_VMC_C_CHV
    // 名  称:VMS1394_有效性_C通道
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:29
    UINT32 VMS1394_VMC_C_CHV : 1;

    // 标识符:VMS1394_SCO
    // 名  称:VMS1394_单通道工作标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:28
    UINT32 VMS1394_SCO : 1;

    UINT32 spare3 : 1;  // 保留字段
    // 标识符:VMS1394_VMC_DPV
    // 名  称:VMS1394_本通道CPU_DPV
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:26
    UINT32 VMS1394_VMC_DPV : 1;

    UINT32 spare2 : 1;  // 保留字段
    // 标识符:VMS1394_CPU1_LCV
    // 名  称:VMS1394_有效性_本通道CPU1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 VMS1394_CPU1_LCV : 1;

    // 标识符:VMS1394_CPU2_LCV
    // 名  称:VMS1394_有效性_本通道CPU2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:23
    UINT32 VMS1394_CPU2_LCV : 1;

    // 标识符:VMS1394_CPU3_LCV
    // 名  称:VMS1394_有效性_本通道CPU3
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:22
    UINT32 VMS1394_CPU3_LCV : 1;

    // 标识符:VMS1394_CPU4_LCV
    // 名  称:VMS1394_有效性_本通道CPU4
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:21
    UINT32 VMS1394_CPU4_LCV : 1;

    // 标识符:VMS1394_CPU2_MON
    // 名  称:VMS1394_通道内监控_CPU2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:20
    UINT32 VMS1394_CPU2_MON : 1;

    UINT32 spare1 : 20;  // 保留字段

} VMS1394_VMC_STATE_TYPE_DEF;

// 信 号 组 标 识 符: VMS1394_VMC_Branch_State
// 信 号 组 名    称: VMS1394_VMC分支状态字
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:VMS1394_AC_CFG_ID
    // 名  称:VMS1394_飞机构型识别ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:29
    UINT32 VMS1394_AC_CFG_ID : 3;

    UINT32 spare3 : 1;  // 保留字段
    // 标识符:VMS1394_LRU_ID
    // 名  称:VMS1394_LRU_ID
    // 说  明:A通道：bit26~bit27  1 0
    //        B通道：bit26~bit27  0 1
    //        C通道：bit26~bit27  1 0
    // 单  位:
    // 起始字:0
    // 起始位:26
    UINT32 VMS1394_LRU_ID : 2;

    UINT32 spare2 : 1;  // 保留字段
    // 标识符:VMS1394_AC_ID
    // 名  称:VMS1394_飞机ID
    // 说  明:主机所自行定义使用，目前预留置0
    // 单  位:
    // 起始字:0
    // 起始位:20
    UINT32 VMS1394_AC_ID : 5;

    // 标识符:VMS1394_BUS_ID
    // 名  称:VMS1394_BUS_ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:17
    UINT32 VMS1394_BUS_ID : 3;

    UINT32 spare1 : 17;  // 保留字段

} VMS1394_VMC_BRANCH_STATE_TYPE_DEF;

// 信 号 组 标 识 符: VMS1394_SYS_MODE_STATE
// 信 号 组 名    称: VMS1394_系统模式和状态字
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:VMS1394_PUBIT_MODE
    // 名  称:VMS1394_上电初始化模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:31
    UINT32 VMS1394_PUBIT_MODE : 1;

    // 标识符:VMS1394_CTRL_MODE
    // 名  称:VMS1394_控制管理模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:30
    UINT32 VMS1394_CTRL_MODE : 1;

    // 标识符:VMS1394_PBIT_MODE
    // 名  称:VMS1394_PBIT模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:29
    UINT32 VMS1394_PBIT_MODE : 1;

    // 标识符:VMS1394_OFP_LOAD
    // 名  称:VMS1394_OFP加载
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:28
    UINT32 VMS1394_OFP_LOAD : 1;

    // 标识符:VMS1394_PBIT_MODE_RW
    // 名  称:VMS1394_MBIT模式_读写
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:27
    UINT32 VMS1394_PBIT_MODE_RW : 1;

    // 标识符:VMS1394_CHMAINT_MODE
    // 名  称:VMS1394_单通道维护模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:26
    UINT32 VMS1394_CHMAINT_MODE : 1;

    // 标识符:VMS1394_PBIT_MODE_R
    // 名  称:VMS1394_MBIT模式_只读
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:25
    UINT32 VMS1394_PBIT_MODE_R : 1;

    // 标识符:VMS1394_PBIT_IN_PROGRESS
    // 名  称:VMS1394_PBIT_IN_PROGRESS
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 VMS1394_PBIT_IN_PROGRESS : 1;

    // 标识符:VMS1394_OFPLOAD_IN_PROGRESS
    // 名  称:VMS1394_OFPLOAD_IN_PROGRESS
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:23
    UINT32 VMS1394_OFPLOAD_IN_PROGRESS : 1;

    // 标识符:VMS1394_DIF_TEST
    // 名  称:VMS1394_DIF测试位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:22
    UINT32 VMS1394_DIF_TEST : 1;

    // 标识符:VMS1394_GSE
    // 名  称:VMS1394_GSE
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:21
    UINT32 VMS1394_GSE : 1;

    // 标识符:VMS1394_STOP_FAULT_RECORD
    // 名  称:VMS1394_停止故障记录标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:20
    UINT32 VMS1394_STOP_FAULT_RECORD : 1;

    // 标识符:VMS1394_GND_CHAIN_SAFE
    // 名  称:VMS1394_地面连锁安全
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:19
    UINT32 VMS1394_GND_CHAIN_SAFE : 1;

    // 标识符:VMS1394_WOW
    // 名  称:VMS1394_轮载
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:18
    UINT32 VMS1394_WOW : 1;

    UINT32 spare1 : 18;  // 保留字段

} VMS1394_SYS_MODE_STATE_TYPE_DEF;

// 信 号 组 标 识 符: VMS1394_date_calendartime
// 信 号 组 名    称: VMS1394_时间_日历日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:VMS1394_date_day
    // 名  称:VMS1394_日期_日
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 VMS1394_date_day;

    // 标识符:VMS1394_date_month
    // 名  称:VMS1394_日期_月
    // 说  明:有效范围1-12
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 VMS1394_date_month;

    // 标识符:VMS1394_date_year
    // 名  称:VMS1394_日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 VMS1394_date_year;

} VMS1394_DATE_CALENDARTIME_TYPE_DEF;

// 信 号 组 标 识 符: ac_end_height
// 信 号 组 名    称: 结束飞机海拔高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: -1000m~25000m
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} AC_END_HEIGHT_TYPE_DEF;

// 信 号 组 标 识 符: image_paras
// 信 号 组 名    称: 图像参数
// 信 号 组 字    数: 81
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IMAGE_time_hour
    // 名  称:图像时间_时
    // 说  明:0～23
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 IMAGE_time_hour;

    // 标识符:IMAGE_date_day
    // 名  称:图像时间_日期_日
    // 说  明:01～31
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 IMAGE_date_day;

    // 标识符:IMAGE_date_mounth
    // 名  称:图像时间_日期_月
    // 说  明:01～12
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT8 IMAGE_date_mounth;

    // 标识符:IMAGE_date_year
    // 名  称:图像时间_日期_年
    // 说  明:2000年开始为0
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 IMAGE_date_year;

    // 标识符:IMAGE_time_ms
    // 名  称:图像时间_毫秒
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 IMAGE_time_ms;

    // 标识符:IMAGE_time_second
    // 名  称:图像时间_秒
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 IMAGE_time_second;

    // 标识符:IMAGE_time_minute
    // 名  称:图像时间_分
    // 说  明:0～59
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 IMAGE_time_minute;

    // 标识符:IMG_ID
    // 名  称:图像帧序号
    // 说  明:共用。
    //        光电：图像总序号（可见光/红外分开计数）。
    //        雷达：即图像帧编号（即方位向图像编号），用于拼接及叠加：条带256K（距离）*2K（方位）为1帧分块；聚束为8K*8K为1帧分块，按照逐行从左到右（距离近到远），从下到上（航向方向）。
    //        帧号下电存在前端传感器，上电后按照上次的继续编号，满了从1开始编号（不同架次连续编）。雷达帧号不区分不同模式，连续编号。光电区分可见光和红外分别编。
    //
    // 单  位:
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 IMG_ID;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:A818_CycleNo
    // 名  称:周期号
    // 说  明:00000～65535，共用。
    //        光电定义：完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
    //        雷达定义：一张完整的聚束SAR的图像，作为一个周期；或者一副完整的条带SAR图像作为一个周期。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 A818_CycleNo;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:A818_LineNo
    // 名  称:条带号
    // 说  明:1～65535，共用。
    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
    //        雷达：与帧序号定义相同，但是每个周期从1开始编号。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 A818_LineNo;

    // 标识符:A818_EO_ImageColumnNum
    // 名  称:图像列数
    // 说  明:00000~99999，平行于航向的像素个数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 A818_EO_ImageColumnNum;

    // 标识符:A818_EO_ImageLineNum
    // 名  称:图像行数
    // 说  明:00000~99999，垂直于航向的像素个数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT32 A818_EO_ImageLineNum;

    // 标识符:A818_WideCover
    // 名  称:收容宽度
    // 说  明:单位：米。
    //        对于光电：广域模式和区域成像模式下垂直航向的实际宽度，区域监视模式下为一帧图像的实际宽度。
    //        对于侦察雷达：表示条带的幅宽、或聚束SAR的幅宽
    // 单  位:m
    // LSB  :1
    // 起始字:7
    // 起始位:0
    UINT32 A818_WideCover;

    // 标识符:fov_transverse
    // 名  称:相机横向视场
    // 说  明:共用。
    //        对于雷达：表示当前成像时波束方位向的波束宽度
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:8
    // 起始位:16
    UINT16 fov_transverse;

    // 标识符:fov_vertical
    // 名  称:相机纵向视场
    // 说  明:共用。
    //        对于雷达表示当前成像时波束俯仰向的波束宽度
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:8
    // 起始位:0
    UINT16 fov_vertical;

    // 标识符:fov_center_azimuth
    // 名  称:视场中心方位角
    // 说  明:共用，LSB=0.01
    //        对于光电：采用机体系；
    //        对于雷达：波束中心指向在水平面投影与正北方向夹角（东北天坐标系），从上往下看，顺时针为正。
    //
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:9
    // 起始位:16
    INT16 fov_center_azimuth;

    // 标识符:fov_center_el
    // 名  称:视场中心俯仰角
    // 说  明:共用，LSB=0.01
    //        对于光电：采用机体系；
    //        对于雷达：像时波束俯仰向中心线与水平面之间的夹角（东北天坐标系），向天为正，向地为负，取决于工作模式，属于雷达系统参数
    //
    // 单  位:Deg
    // LSB  :0.01
    // 起始字:9
    // 起始位:0
    INT16 fov_center_el;

    SPARE8 spare3[2];  // 保留字段

    // 标识符:A818_Beside_tgt_cover
    // 名  称:傍向重叠率
    // 说  明:00~99,百分比,垂直飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:10
    // 起始位:8
    UINT8 A818_Beside_tgt_cover;

    // 标识符:A818_Couse_tgt_cover
    // 名  称:航向重叠率
    // 说  明:00~99,像素百分比,平行飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:10
    // 起始位:0
    UINT8 A818_Couse_tgt_cover;

    // 标识符:A818_GROUND_RESOLUTION
    // 名  称:地面摄影分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置地面摄影分辨率。像元投影到地面后的分辨率。精度与飞机姿态参数精度、相对高度参数精度等相关
    // 单  位:m
    // LSB  :0.01
    // 起始字:11
    // 起始位:16
    UINT16 A818_GROUND_RESOLUTION;

    // 标识符:A818_CUR_RESOLUTION
    // 名  称:像元分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置分辨率（计算值，精度与飞机姿态参数精度、相对高度参数精度等相关）
    //        对于雷达表示图像斜距距离向的像元尺寸。
    // 单  位:m
    // LSB  :0.01
    // 起始字:11
    // 起始位:0
    UINT16 A818_CUR_RESOLUTION;

    SPARE8 spare4[2];  // 保留字段

    // 标识符:A818_ImageCenterHeight
    // 名  称:图像中心高度
    // 说  明:图像中心对应的地面海拔值（成像区域的海拔平均值）
    // 单  位:m
    // LSB  :1
    // 起始字:12
    // 起始位:0
    INT16 A818_ImageCenterHeight;

    // 标识符:image_center_longitude
    // 名  称:图像中心经度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    IMAGE_CENTER_LONGITUDE_TYPE_DEF image_center_longitude;

    // 标识符:image_center_latitude
    // 名  称:图像中心纬度
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    IMAGE_CENTER_LATITUDE_TYPE_DEF image_center_latitude;

    // 标识符:upleft_longitude
    // 名  称:左上角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    // 单  位:
    // 起始字:15
    // 起始位:0
    UPLEFT_LONGITUDE_TYPE_DEF upleft_longitude;

    // 标识符:upleft_latitude
    // 名  称:左上角纬度
    // 说  明:北向为正，几何校正后纬度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:16
    // 起始位:0
    UPLEFT_LATITUDE_TYPE_DEF upleft_latitude;

    // 标识符:downleft_longitude
    // 名  称:左下角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    // 单  位:
    // 起始字:17
    // 起始位:0
    DOWNLEFT_LONGITUDE_TYPE_DEF downleft_longitude;

    // 标识符:downleft_latitude
    // 名  称:左下角纬度
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    DOWNLEFT_LATITUDE_TYPE_DEF downleft_latitude;

    // 标识符:upright_longitude
    // 名  称:右上角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:19
    // 起始位:0
    UPRIGHT_LONGITUDE_TYPE_DEF upright_longitude;

    // 标识符:upright_latitude
    // 名  称:右上角纬度
    // 说  明:
    // 单  位:
    // 起始字:20
    // 起始位:0
    UPRIGHT_LATITUDE_TYPE_DEF upright_latitude;

    // 标识符:downright_longitude
    // 名  称:右下角经度
    // 说  明:东向为正，几何校正后经度
    //        LSB= 0.00001
    //
    // 单  位:
    // 起始字:21
    // 起始位:0
    DOWNRIGHT_LONGITUDE_TYPE_DEF downright_longitude;

    // 标识符:downright_latitude
    // 名  称:右下角纬度
    // 说  明:
    // 单  位:
    // 起始字:22
    // 起始位:0
    DOWNRIGHT_LATITUDE_TYPE_DEF downright_latitude;

    UINT32 spare5 : 14;  // 保留字段
    // 标识符:A818_SideViewDirection
    // 名  称:雷达侧视方向
    // 说  明:雷达专用，表示雷达侧视方向。条带SAR模式或SAR-GMTI模式下：1=左侧视、2=右侧视；其它模式填0
    // 单  位:No_Unit
    // 起始字:23
    // 起始位:16
    UINT32 A818_SideViewDirection : 2;

    // 标识符:A818_FrequencyNo
    // 名  称:工作频点号
    // 说  明:雷达独有，由于频点保密要求，输出频点号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:23
    // 起始位:0
    UINT32 A818_FrequencyNo : 16;

    // 标识符:A818_SlantRange
    // 名  称:场景中心斜距
    // 说  明:雷达独有，雷达到场景中心点的斜距，2位小数
    // 单  位:m
    // LSB  :0.01
    // 起始字:24
    // 起始位:0
    UINT32 A818_SlantRange;

    SPARE8 spare6[2];  // 保留字段

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:25
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:A818_AZPixelsNo
    // 名  称:图像方位向像元个数
    // 说  明:0~256K，一帧图像（块）方位向的像素个数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:26
    // 起始位:0
    UINT32 A818_AZPixelsNo;

    // 标识符:A818_RGPixelsNo
    // 名  称:图像距离向像元个数
    // 说  明:0~256K，一帧图像（块）距离向的像素个数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:27
    // 起始位:0
    UINT32 A818_RGPixelsNo;

    // 标识符:A818_EO_FocalLength
    // 名  称:相机焦距
    // 说  明:0~65535，毫米,相机焦距参数，光电独有
    // 单  位:mm
    // LSB  :1
    // 起始字:28
    // 起始位:16
    UINT16 A818_EO_FocalLength;

    // 标识符:A818_EO_TakeTimes
    // 名  称:照相次数
    // 说  明:000~999，共用。
    //        光电：每次接收拍照指令或模式变换时+1，对应数据记录时，建立新模式的文件夹
    //        雷达：对SAR雷达，一次飞行过程中开机的序号，每切换一次工作模式，开机次数需递增。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:28
    // 起始位:0
    UINT16 A818_EO_TakeTimes;

    SPARE8 spare7;  // 保留字段

    // 标识符:A818_EO_ImpotentTag
    // 名  称:重要目标标识
    // 说  明:0-不重要目标，1-重要目标，2-未知，使用中不做要求
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:29
    // 起始位:16
    UINT8 A818_EO_ImpotentTag;

    // 标识符:A818_EO_ExposureTime
    // 名  称:曝光时间
    // 说  明:000~999，图像曝光时间，分辨率为1微秒，光电独有
    // 单  位:Mic
    // LSB  :1
    // 起始字:29
    // 起始位:0
    UINT16 A818_EO_ExposureTime;

    // 标识符:REGION_CENTER_X
    // 名  称:区域中心位置X
    // 说  明:用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
    // 单  位:
    // 起始字:30
    // 起始位:0
    REGION_CENTER_X_TYPE_DEF REGION_CENTER_X;

    // 标识符:REGION_CENTER_Y
    // 名  称:区域中心位置Y
    // 说  明:用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有
    // 单  位:
    // 起始字:31
    // 起始位:0
    REGION_CENTER_Y_TYPE_DEF REGION_CENTER_Y;

    // 标识符:A818_SlantRangeAZpixelSize
    // 名  称:图像斜距方位向像元尺寸
    // 说  明:000.0~999.99，2位小数.方位相两个像素的间隔（投影到斜距上）。雷达独有
    // 单  位:m
    // LSB  :0.01
    // 起始字:32
    // 起始位:0
    UINT32 A818_SlantRangeAZpixelSize;

    // 标识符:A818_SlantRangeRGpixelSize
    // 名  称:图像斜距距离向像元尺寸
    // 说  明:000.0~999.99，2位小数
    // 单  位:m
    // 起始字:33
    // 起始位:0
    float A818_SlantRangeRGpixelSize;

    // 标识符:A818_NearestSlantRange
    // 名  称:最近斜距
    // 说  明:该图像帧的近边到平台的斜距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:34
    // 起始位:0
    UINT32 A818_NearestSlantRange;

    // 标识符:A818_FarthestSlantRange
    // 名  称:最远斜距
    // 说  明:该图像帧的远边到平台的斜距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:35
    // 起始位:0
    UINT32 A818_FarthestSlantRange;

    // 标识符:A818_NearestFloorDistance
    // 名  称:最近地距
    // 说  明:该图像帧的近边到平台的地距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:36
    // 起始位:0
    UINT32 A818_NearestFloorDistance;

    // 标识符:A818_FarthestFloorDistance
    // 名  称:最远地距
    // 说  明:该图像帧的远边到平台的地距，雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:37
    // 起始位:0
    UINT32 A818_FarthestFloorDistance;

    // 标识符:A818_ACRelativeAltitude
    // 名  称:飞机相对高度
    // 说  明:飞机与场景中心点相对高度（载机高度-场景中心高度），雷达独有
    // 单  位:m
    // LSB  :1
    // 起始字:38
    // 起始位:0
    UINT32 A818_ACRelativeAltitude;

    SPARE8 spare8[2];  // 保留字段

    // 标识符:A818_ViewNum
    // 名  称:视数
    // 说  明:方位向和距离向分辨率的比例，作为雷达内部参数使用。LSB=0.01，雷达独有
    // 单  位:No_Unit
    // LSB  :0.01
    // 起始字:39
    // 起始位:0
    UINT16 A818_ViewNum;

    // 标识符:A818_SATime
    // 名  称:合成孔径时间
    // 说  明:一个点的积累回波时间。与分辨率、作用距离、飞行速度等有关。3位小数，雷达独有
    // 单  位:Sec
    // LSB  :0.01
    // 起始字:40
    // 起始位:0
    UINT32 A818_SATime;

    // 标识符:A818_PRF
    // 名  称:脉冲重复频率
    // 说  明:发射重频，雷达独有
    // 单  位:Hz
    // LSB  :0.01
    // 起始字:41
    // 起始位:0
    UINT32 A818_PRF;

    // 标识符:A818_PRFCount
    // 名  称:PRF计数值
    // 说  明:当前图像对应回波数据起始PRF计数，雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:42
    // 起始位:0
    UINT64 A818_PRFCount;

    // 标识符:A818_DCF
    // 名  称:多普勒中心频率
    // 说  明:多普勒中心频率，雷达独有
    // 单  位:Hz
    // LSB  :1
    // 起始字:44
    // 起始位:0
    UINT32 A818_DCF;

    // 标识符:BeamAZWidth
    // 名  称:波束方位向宽度
    // 说  明:[-180,180]度，当前成像时波束方位向的波瓣宽度，取决于工作模式，属于雷达系统参数
    // 单  位:Deg
    // LSB  :0.00001
    // 起始字:45
    // 起始位:0
    INT32 BeamAZWidth;

    // 标识符:BeamPitchWidth
    // 名  称:波束俯仰向宽度
    // 说  明:[-180,180]度，当前成像时波束方位向的波瓣宽度，取决于工作模式，属于雷达系统参数
    // 单  位:Deg
    // LSB  :0.00001
    // 起始字:46
    // 起始位:0
    INT32 BeamPitchWidth;

    // 标识符:BeamAZAngle
    // 名  称:波束方位角
    // 说  明:0~+359.99，波束中心指向在水平面投影与正北方向夹角（东北天坐标系），从上往下看，顺时针为正。
    // 单  位:Deg
    // LSB  :0.0001
    // 起始字:47
    // 起始位:0
    INT32 BeamAZAngle;

    // 标识符:BeamPitchAngle
    // 名  称:波束俯仰角
    // 说  明:-90~+90，当前成像时波束俯仰向中心线与水平面之间的夹角（东北天坐标系），向天为正，向地为负，取决于工作模式，属于雷达系统参数
    // 单  位:Deg
    // LSB  :0.0001
    // 起始字:48
    // 起始位:0
    INT32 BeamPitchAngle;

    // 标识符:BeamStrabismusAngle
    // 名  称:波束斜视角
    // 说  明:-90~+90，雷达波束指向与航迹的夹角，前为正，后为负，雷达独有
    // 单  位:Deg
    // LSB  :0.0001
    // 起始字:49
    // 起始位:0
    INT32 BeamStrabismusAngle;

    // 标识符:BeamLevelWidth
    // 名  称:波束水平宽度
    // 说  明:[-45,45]度，波束水平面投影角度，雷达独有
    // 单  位:Deg
    // LSB  :0.00001
    // 起始字:50
    // 起始位:0
    INT32 BeamLevelWidth;

    // 标识符:A818_DataRate
    // 名  称:数据率
    // 说  明:兆比特/秒，传输峰值数据率
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:51
    // 起始位:0
    UINT32 A818_DataRate;

    SPARE8 spare9;  // 保留字段

    // 标识符:A818_INS_GroupStatus
    // 名  称:惯导组合状态
    // 说  明:0~3位：惯导1组合状态
    //        4~7位：惯导2组合状态
    //        8~11位：惯导3组合状态
    //
    //        0=无效（默认）
    //        1=惯性/RTK BDS组合
    //        2=惯性/RTD BDS组合
    //        3=惯性/单点BDS组合
    //        4=惯性/RTD GPS组合
    //        5=惯性/单点 GPS组合
    //        6=惯性/ VMC综合卫星组合
    //        7=惯性/毫米波组合
    //        8=惯性/飞行辅助引导设备组合
    //        9=惯性/SBAS BDS组合
    //        10=惯性/天文组合
    //        11=惯性/地景组合
    //        12=惯性/精定修正
    //        13=惯性/大气组合
    //        14=纯惯性（断开修正）
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:52
    // 起始位:8
    UINT16 A818_INS_GroupStatus;

    // 标识符:A818_INS_NOW
    // 名  称:当前使用惯导
    // 说  明:飞机惯导
    //        03H-载荷惯导
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:52
    // 起始位:0
    UINT8 A818_INS_NOW;

    // 标识符:AcLongitude
    // 名  称:载机经度
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:53
    // 起始位:0
    INT32 AcLongitude;

    // 标识符:AcLatitude
    // 名  称:载机纬度
    // 说  明:
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:54
    // 起始位:0
    INT32 AcLatitude;

    // 标识符:ac_height
    // 名  称:载机海拔高度
    // 说  明:[-500,30000]m
    //        融合后载机海拔高度。
    // 单  位:
    // 起始字:55
    // 起始位:0
    AC_HEIGHT_TYPE_DEF ac_height;

    // 标识符:AcHeading
    // 名  称:载机航向
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:56
    // 起始位:0
    INT32 AcHeading;

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //        仰角为正
    // 单  位:
    // 起始字:57
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //        右倾为正
    // 单  位:
    // 起始字:58
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_CDI_angle
    // 名  称:载机偏航角
    // 说  明:飞机纵轴与预定航线的夹角，相对预定航线左偏为正，
    //        LSB=0.001
    //
    // 单  位:
    // 起始字:59
    // 起始位:0
    AC_CDI_ANGLE_TYPE_DEF ac_CDI_angle;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //        速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:60
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:61
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    // 标识符:ac_true_airspeed
    // 名  称:载机真空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:62
    // 起始位:0
    AC_TRUE_AIRSPEED_TYPE_DEF ac_true_airspeed;

    // 标识符:ac_indicate_airspeed
    // 名  称:指示空速
    // 说  明:[0,2500]km/h
    // 单  位:
    // 起始字:63
    // 起始位:0
    AC_INDICATE_AIRSPEED_TYPE_DEF ac_indicate_airspeed;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:64
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:67
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:A818_INS_No
    // 名  称:惯导序号
    // 说  明:标识该组惯导参数在当前图像中对应的列号，由载荷提供，从00001开始计数
    //        雷达独有
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:70
    // 起始位:0
    UINT32 A818_INS_No;

    // 标识符:ac_end_longitude
    // 名  称:结束飞机经度
    // 说  明:(-180,180]度
    //        东向为正（雷达位置经度）
    // 单  位:mrad
    // LSB  :0.0000001
    // 起始字:71
    // 起始位:0
    INT32 ac_end_longitude;

    // 标识符:ac_end_latitude
    // 名  称:结束飞机纬度
    // 说  明:[-90,90]度
    //        北向为正（雷达位置纬度）
    // 单  位:mrad
    // LSB  :0.0000001
    // 起始字:72
    // 起始位:0
    INT32 ac_end_latitude;

    // 标识符:ac_end_height
    // 名  称:结束飞机海拔高度
    // 说  明:-1000m~25000m
    // 单  位:
    // 起始字:73
    // 起始位:0
    AC_END_HEIGHT_TYPE_DEF ac_end_height;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:74
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_heading_accel
    // 名  称:载机航向角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:75
    // 起始位:0
    AC_HEADING_ACCEL_TYPE_DEF ac_heading_accel;

    // 标识符:fVEl
    // 名  称:俯仰角速度
    // 说  明:
    // 单  位:mrad/s
    // 起始字:76
    // 起始位:0
    float fVEl;

    // 标识符:ac_pitch_accel
    // 名  称:载机俯仰角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:77
    // 起始位:0
    AC_PITCH_ACCEL_TYPE_DEF ac_pitch_accel;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:78
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_roll_accel
    // 名  称:载机横滚角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:79
    // 起始位:0
    AC_ROLL_ACCEL_TYPE_DEF ac_roll_accel;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //        相对于真北顺时针为正
    // 单  位:
    // 起始字:80
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

} IMAGE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: image_inner_paras
// 信 号 组 名    称: 图像应用参数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 256
// 信 号 组 说    明:
typedef struct
{
    // 标识符:image_inner_data
    // 名  称:图像自定义数据
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT32 image_inner_data;

} IMAGE_INNER_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: sensor_los_platform
// 信 号 组 名    称: 机体系_传感器LOS
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:data_valid
    // 名  称:数据有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 data_valid;

    // 标识符:sensor_LOS_az
    // 名  称:传感器LOS方位
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    SENSOR_LOS_AZ_TYPE_DEF sensor_LOS_az;

    // 标识符:sensor_LOS_el
    // 名  称:传感器LOS俯仰
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    SENSOR_LOS_EL_TYPE_DEF sensor_LOS_el;

} SENSOR_LOS_PLATFORM_TYPE_DEF;

// 信 号 组 标 识 符: members_IR_tgt_dot_correlation_info
// 信 号 组 名    称: 成员IRST点迹协同目标关联信息
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 3
// 信 号 组 说    明:
typedef struct
{
    // 标识符:member_no
    // 名  称:成员编号
    // 说  明:小编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 member_no;

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 IR_track_number;

    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 platform_fused_tgt_ID;

} MEMBERS_IR_TGT_DOT_CORRELATION_INFO_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_west
// 信 号 组 名    称: 目标西向速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_WEST_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_up
// 信 号 组 名    称: 目标天向速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_UP_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_north
// 信 号 组 名    称: 目标北向速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: tgt_slant_distance_ind
// 信 号 组 名    称: 目标斜距_单机
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_SLANT_DISTANCE_IND_TYPE_DEF;

// 信 号 组 标 识 符: tgt_slant_distance_coop
// 信 号 组 名    称: 目标斜距_协同
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_SLANT_DISTANCE_COOP_TYPE_DEF;

// 信 号 组 标 识 符: dot_paras_validity
// 信 号 组 名    称: 点迹有效性标志
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_tgt_el
    // 名  称:有效性_目标俯仰
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_tgt_el;

    // 标识符:validity_tgt_az
    // 名  称:有效性_目标方位
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_tgt_az;

    // 标识符:validity_tgt_velocity
    // 名  称:有效性_目标速度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_tgt_velocity;

    // 标识符:validity_tgt_distance
    // 名  称:有效性_目标距离
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_tgt_distance;

} DOT_PARAS_VALIDITY_TYPE_DEF;

// 信 号 组 标 识 符: IRST_tgt_dot_correlation_motion_paras
// 信 号 组 名    称: IRST点迹协同目标运动参数
// 信 号 组 字    数: 10
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:dot_paras_validity
    // 名  称:点迹有效性标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    DOT_PARAS_VALIDITY_TYPE_DEF dot_paras_validity;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:1
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:tgt_bearing
    // 名  称:目标方位_地理系
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_BEARING_TYPE_DEF tgt_bearing;

    // 标识符:tgt_pitch
    // 名  称:目标俯仰_地理系
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_PITCH_TYPE_DEF tgt_pitch;

    // 标识符:tgt_slant_distance_coop
    // 名  称:目标斜距_协同
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_SLANT_DISTANCE_COOP_TYPE_DEF tgt_slant_distance_coop;

    // 标识符:tgt_slant_distance_ind
    // 名  称:目标斜距_单机
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_SLANT_DISTANCE_IND_TYPE_DEF tgt_slant_distance_ind;

    // 标识符:tgt_velocity_north
    // 名  称:目标北向速度
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_VELOCITY_NORTH_TYPE_DEF tgt_velocity_north;

    // 标识符:tgt_velocity_west
    // 名  称:目标西向速度
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_VELOCITY_WEST_TYPE_DEF tgt_velocity_west;

    // 标识符:tgt_velocity_up
    // 名  称:目标天向速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    TGT_VELOCITY_UP_TYPE_DEF tgt_velocity_up;

} IRST_TGT_DOT_CORRELATION_MOTION_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: IRST_tgt_dot_correlation_info
// 信 号 组 名    称: IRST点迹协同目标关联信息
// 信 号 组 字    数: 18
// 信 号 组 数组长度: 10
// 信 号 组 说    明:
typedef struct
{
    // 标识符:platform_fused_tgt_ID
    // 名  称:平台级融合目标编号
    // 说  明:成员平台级目标融合编号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 platform_fused_tgt_ID;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 IR_track_number;

    // 标识符:members_IR_tgt_dot_correlation_info
    // 名  称:成员IRST点迹协同目标关联信息
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    MEMBERS_IR_TGT_DOT_CORRELATION_INFO_TYPE_DEF members_IR_tgt_dot_correlation_info[3];

    // 标识符:IRST_tgt_dot_correlation_motion_paras
    // 名  称:IRST点迹协同目标运动参数
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    IRST_TGT_DOT_CORRELATION_MOTION_PARAS_TYPE_DEF IRST_tgt_dot_correlation_motion_paras;

} IRST_TGT_DOT_CORRELATION_INFO_TYPE_DEF;

// 信 号 组 标 识 符: user_authority_state
// 信 号 组 名    称: 用户权限状态
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:erase_file_authority
    // 名  称:销密权限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 erase_file_authority;

    // 标识符:mission_secret_load_authority
    // 名  称:秘密数据加载使用权限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 mission_secret_load_authority;

    // 标识符:user_config_load_authority
    // 名  称:用户配置数据加载权限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 user_config_load_authority;

    // 标识符:system_config_load_authority
    // 名  称:系统配置数据加载权限
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 system_config_load_authority;

} USER_AUTHORITY_STATE_TYPE_DEF;

// 信 号 组 标 识 符: sys_security_user_state
// 信 号 组 名    称: 系统安全_用户状态
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:security_login_flag
    // 名  称:系统安全_登录标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 security_login_flag;

    // 标识符:security_lock_flag
    // 名  称:系统安全_锁定标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 security_lock_flag;

    // 标识符:security_user_ID
    // 名  称:系统安全_用户名
    // 说  明:用户名，8位字符串。ASCII码
    // 单  位:
    // 起始字:1
    // 起始位:0
    char_8 security_user_ID[8];

    // 标识符:security_login_failure_count
    // 名  称:系统安全_校验错误次数
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:24
    UINT32 security_login_failure_count : 8;

    // 标识符:security_code_validity
    // 名  称:系统安全_密码有效性
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 security_code_validity : 8;

    // 标识符:security_ID_validity
    // 名  称:系统安全_用户名有效性
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 security_ID_validity : 8;

    // 标识符:user_type
    // 名  称:用户类型
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 user_type : 8;

    // 标识符:user_authority_state
    // 名  称:用户权限状态
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    USER_AUTHORITY_STATE_TYPE_DEF user_authority_state;

} SYS_SECURITY_USER_STATE_TYPE_DEF;

// 信 号 组 标 识 符: security_mode_subsys
// 信 号 组 名    称: 子系统安全保密模式
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 20
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:security_State_Subsystem
    // 名  称:子系统保密状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 security_State_Subsystem : 8;

    // 标识符:Fail_OutSecurity
    // 名  称:切换非密失败
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 Fail_OutSecurity : 8;

    // 标识符:Fail_EnterSecurity
    // 名  称:切换秘密失败
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 Fail_EnterSecurity : 8;

} SECURITY_MODE_SUBSYS_TYPE_DEF;

// 信 号 组 标 识 符: sys_security_level_state
// 信 号 组 名    称: 系统安全_密级状态
// 信 号 组 字    数: 41
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:security_level
    // 名  称:系统安全_密级
    // 说  明:目前只有非密/秘密两种密级，后续可能会增加更多的密级
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 security_level : 8;

    // 标识符:security_mode_subsys
    // 名  称:子系统安全保密模式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    SECURITY_MODE_SUBSYS_TYPE_DEF security_mode_subsys[20];

} SYS_SECURITY_LEVEL_STATE_TYPE_DEF;

// 信 号 组 标 识 符: load_date
// 信 号 组 名    称: 加载日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} LOAD_DATE_TYPE_DEF;

// 信 号 组 标 识 符: limit_date
// 信 号 组 名    称: 有效期限
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} LIMIT_DATE_TYPE_DEF;

// 信 号 组 标 识 符: sys_security_authority_table_state
// 信 号 组 名    称: 系统安全_权限表状态
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 3
// 信 号 组 说    明: 描述3个权限表的状态
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:valid_invalid
    // 名  称:有效_无效
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 valid_invalid : 8;

    // 标识符:exist_notexist
    // 名  称:存在_不存在
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 exist_notexist : 8;

    // 标识符:user_type
    // 名  称:用户类型
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 user_type : 8;

    // 标识符:load_date
    // 名  称:加载日期
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    LOAD_DATE_TYPE_DEF load_date;

    // 标识符:limit_date
    // 名  称:有效期限
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    LIMIT_DATE_TYPE_DEF limit_date;

} SYS_SECURITY_AUTHORITY_TABLE_STATE_TYPE_DEF;

// 信 号 组 标 识 符: subsystem_module_state
// 信 号 组 名    称: 子系统模块运行状态
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 64
// 信 号 组 说    明: 用于表征子系统模块运行在正常态或是软件加载态。依据配置文件定义的ICP内部每个cpum的ID，以及DCLM /DCRM、 IN1M /IN2M、 DCLD/DCRD、 HUDM 、HMDM、 RDDP、 EWRM、 CNRM、ETTM 、 SMU1/ SMU2 、FASM 、DCAM 、UFCP 、CNAM等。
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:app_state
    // 名  称:应用软件状态
    // 说  明:正常运行时，应用软件状态仅为正常工作或非正常工作；
    //        仅在飞管系统进入OFP加载模式后，SYMM将所有功能单元的应用软件状态置为SW_LOAD，触发各子系统进入维护加载态。
    //        若任务系统处于正常运行态时，但某子系统或子系统某模块运行在软件加载态，则对应子系统状态置为SW_load。
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 app_state : 8;

    // 标识符:FC_net_state
    // 名  称:FC网络状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 FC_net_state : 8;

} SUBSYSTEM_MODULE_STATE_TYPE_DEF;

// 信 号 组 标 识 符: matrix_EL
// 信 号 组 名    称: 俯仰角协方差矩阵
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 元素11：目标俯仰角方差，单位为角度单位的平方；
//                    元素12：目标俯仰角与角速度协方差，单位为角度与角速度的乘积；
//                    元素21：目标俯仰角速度与俯仰角协方差，单位为角度与角速度的乘积；
//                    元素22：目标俯仰角速度方差，单位为角速度单位的平方。
typedef struct
{
    // 标识符:element11
    // 名  称:元素11
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 element11;

    // 标识符:element12
    // 名  称:元素12
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    INT32 element12;

    // 标识符:element21
    // 名  称:元素21
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:2
    // 起始位:0
    INT32 element21;

    // 标识符:element22
    // 名  称:元素22
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:3
    // 起始位:0
    INT32 element22;

} MATRIX_EL_TYPE_DEF;

// 信 号 组 标 识 符: matrix_AZ
// 信 号 组 名    称: 方位角协方差矩阵
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 元素11：目标方位角方差，单位为角度单位的平方；
//                    元素12：目标方位角与角速度协方差，单位为角度与角速度的乘积；
//                    元素21：目标方位角速度与方位角协方差，单位为角度与角速度的乘积；
//                    元素22：目标方位角速度方差，单位为角速度单位的平方。
typedef struct
{
    // 标识符:element11
    // 名  称:元素11
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 element11;

    // 标识符:element12
    // 名  称:元素12
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    INT32 element12;

    // 标识符:element21
    // 名  称:元素21
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:2
    // 起始位:0
    INT32 element21;

    // 标识符:element22
    // 名  称:元素22
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:3
    // 起始位:0
    INT32 element22;

} MATRIX_AZ_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_covariance_west
// 信 号 组 名    称: 目标西向速度方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_COVARIANCE_WEST_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_covariance_up
// 信 号 组 名    称: 目标天向速度方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_COVARIANCE_UP_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_covariance_north
// 信 号 组 名    称: 目标北向速度方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_COVARIANCE_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_W
// 信 号 组 名    称: 目标速度_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_W_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_U
// 信 号 组 名    称: 目标速度_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_U_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_N
// 信 号 组 名    称: 目标速度_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_N_TYPE_DEF;

// 信 号 组 标 识 符: tgt_closing_velocity_covariance
// 信 号 组 名    称: 目标接近速度方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_CLOSING_VELOCITY_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_closing_velocity
// 信 号 组 名    称: 目标接近速度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_CLOSING_VELOCITY_TYPE_DEF;

// 信 号 组 标 识 符: IR_velocity
// 信 号 组 名    称: IR目标速度
// 信 号 组 字    数: 9
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_vel_north;

    // 标识符:validity_tgt_closevelocity
    // 名  称:有效性_目标接近速度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_tgt_closevelocity;

    // 标识符:tgt_closing_velocity
    // 名  称:目标接近速度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_CLOSING_VELOCITY_TYPE_DEF tgt_closing_velocity;

    // 标识符:tgt_V_N
    // 名  称:目标速度_北向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_V_N_TYPE_DEF tgt_V_N;

    // 标识符:tgt_V_W
    // 名  称:目标速度_西向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_V_W_TYPE_DEF tgt_V_W;

    // 标识符:tgt_V_U
    // 名  称:目标速度_天向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_V_U_TYPE_DEF tgt_V_U;

    // 标识符:tgt_closing_velocity_covariance
    // 名  称:目标接近速度方差
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_CLOSING_VELOCITY_COVARIANCE_TYPE_DEF tgt_closing_velocity_covariance;

    // 标识符:tgt_velocity_covariance_north
    // 名  称:目标北向速度方差
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_VELOCITY_COVARIANCE_NORTH_TYPE_DEF tgt_velocity_covariance_north;

    // 标识符:tgt_velocity_covariance_west
    // 名  称:目标西向速度方差
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_VELOCITY_COVARIANCE_WEST_TYPE_DEF tgt_velocity_covariance_west;

    // 标识符:tgt_velocity_covariance_up
    // 名  称:目标天向速度方差
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_VELOCITY_COVARIANCE_UP_TYPE_DEF tgt_velocity_covariance_up;

} IR_VELOCITY_TYPE_DEF;

// 信 号 组 标 识 符: tgt_R_W
// 信 号 组 名    称: 目标距离_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_R_W_TYPE_DEF;

// 信 号 组 标 识 符: tgt_R_U
// 信 号 组 名    称: 目标距离_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_R_U_TYPE_DEF;

// 信 号 组 标 识 符: tgt_R_N
// 信 号 组 名    称: 目标距离_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_R_N_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance_covariance_west
// 信 号 组 名    称: 目标西向距离方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_COVARIANCE_WEST_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance_covariance_up
// 信 号 组 名    称: 目标天向距离方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_COVARIANCE_UP_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance_covariance_north
// 信 号 组 名    称: 目标北向距离方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_COVARIANCE_NORTH_TYPE_DEF;

// 信 号 组 标 识 符: IR_range_paras
// 信 号 组 名    称: IR目标距离信息
// 信 号 组 字    数: 9
// 信 号 组 数组长度: 2
// 信 号 组 说    明: IR目标距离信息[0]表示激光测距距离信息，
//                    IR目标距离信息[1]表示IR协同定位距离信息
typedef struct
{
    UINT32 spare1 : 8;  // 保留字段
    // 标识符:laser_range_memory_flag
    // 名  称:激光测距外推标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 laser_range_memory_flag : 8;

    // 标识符:range_source
    // 名  称:距离获取方式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 range_source : 8;

    // 标识符:IR_track_distance_validity
    // 名  称:目标距离有效性
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 IR_track_distance_validity : 8;

    // 标识符:tgt_slant_distance
    // 名  称:目标斜距
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_SLANT_DISTANCE_TYPE_DEF tgt_slant_distance;

    // 标识符:variance_of_target_distance
    // 名  称:目标斜距方差
    // 说  明:单位为距离单位的平方。
    // 单  位:No_Unit
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    INT32 variance_of_target_distance;

    // 标识符:tgt_R_N
    // 名  称:目标距离_北向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_R_N_TYPE_DEF tgt_R_N;

    // 标识符:tgt_R_W
    // 名  称:目标距离_西向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_R_W_TYPE_DEF tgt_R_W;

    // 标识符:tgt_R_U
    // 名  称:目标距离_天向
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_R_U_TYPE_DEF tgt_R_U;

    // 标识符:tgt_distance_covariance_north
    // 名  称:目标北向距离方差
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_DISTANCE_COVARIANCE_NORTH_TYPE_DEF tgt_distance_covariance_north;

    // 标识符:tgt_distance_covariance_west
    // 名  称:目标西向距离方差
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_DISTANCE_COVARIANCE_WEST_TYPE_DEF tgt_distance_covariance_west;

    // 标识符:tgt_distance_covariance_up
    // 名  称:目标天向距离方差
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_DISTANCE_COVARIANCE_UP_TYPE_DEF tgt_distance_covariance_up;

} IR_RANGE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: IR_character
// 信 号 组 名    称: IR目标识别信息
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:true_virtual_flag
    // 名  称:真实虚拟目标标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 true_virtual_flag : 8;

    // 标识符:confidence_tgt_size
    // 名  称:置信度_目标尺寸
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:0
    // 起始位:8
    UINT32 confidence_tgt_size : 16;

    // 标识符:target_physics_size
    // 名  称:目标物理尺寸
    // 说  明:目标机身长度范围大于25m为大尺寸目标
    //        目标机身长度范围为(10,25]m为中尺寸目标
    //        目标机身长度范围为(3,10]m为小尺寸目标
    //        目标机身长度范围为(0,3]m为超小尺寸目标
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 target_physics_size : 8;

    // 标识符:Target_Size
    // 名  称:像素尺寸
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 Target_Size;

    // 标识符:target_gray
    // 名  称:目标灰度值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 target_gray;

} IR_CHARACTER_TYPE_DEF;

// 信 号 组 标 识 符: IR_track_paras
// 信 号 组 名    称: IR空空跟踪目标参数
// 信 号 组 字    数: 49
// 信 号 组 数组长度: 10
// 信 号 组 说    明:
typedef struct
{
    // 标识符:target_track_state
    // 名  称:目标跟踪状态
    // 说  明:20230522:更改11-STT_DOT描述为“点迹截获进SAM”。
    //        20230608：新增“12-TRACK_SHOOTLIST-火控级跟踪”。
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 target_track_state : 8;

    // 标识符:target_special_tag
    // 名  称:目标特殊标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 target_special_tag : 8;

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 IR_track_number : 16;

    // 标识符:IR_range_paras
    // 名  称:IR目标距离信息
    // 说  明:IR目标距离信息[0]表示激光测距距离信息，
    //        IR目标距离信息[1]表示IR协同定位距离信息
    // 单  位:
    // 起始字:1
    // 起始位:0
    IR_RANGE_PARAS_TYPE_DEF IR_range_paras[2];

    // 标识符:IR_angular_paras
    // 名  称:IR目标角度信息
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    IR_ANGULAR_PARAS_TYPE_DEF IR_angular_paras;

    // 标识符:IR_velocity
    // 名  称:IR目标速度
    // 说  明:
    // 单  位:
    // 起始字:28
    // 起始位:0
    IR_VELOCITY_TYPE_DEF IR_velocity;

    // 标识符:matrix_AZ
    // 名  称:方位角协方差矩阵
    // 说  明:元素11：目标方位角方差，单位为角度单位的平方；
    //        元素12：目标方位角与角速度协方差，单位为角度与角速度的乘积；
    //        元素21：目标方位角速度与方位角协方差，单位为角度与角速度的乘积；
    //        元素22：目标方位角速度方差，单位为角速度单位的平方。
    // 单  位:
    // 起始字:37
    // 起始位:0
    MATRIX_AZ_TYPE_DEF matrix_AZ;

    // 标识符:matrix_EL
    // 名  称:俯仰角协方差矩阵
    // 说  明:元素11：目标俯仰角方差，单位为角度单位的平方；
    //        元素12：目标俯仰角与角速度协方差，单位为角度与角速度的乘积；
    //        元素21：目标俯仰角速度与俯仰角协方差，单位为角度与角速度的乘积；
    //        元素22：目标俯仰角速度方差，单位为角速度单位的平方。
    // 单  位:
    // 起始字:41
    // 起始位:0
    MATRIX_EL_TYPE_DEF matrix_EL;

    // 标识符:IR_character
    // 名  称:IR目标识别信息
    // 说  明:
    // 单  位:
    // 起始字:45
    // 起始位:0
    IR_CHARACTER_TYPE_DEF IR_character;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:target_track_unstable_state
    // 名  称:目标跟踪不稳定状态
    // 说  明:跟踪目标上报不稳定情况，快出框架角时上报火控更改下发AOC判断状态
    // 单  位:
    // 起始字:47
    // 起始位:8
    UINT32 target_track_unstable_state : 8;

    // 标识符:ET_tgt_ID
    // 名  称:ET_目标ID
    // 说  明:未匹配上	0
    //        目标训练ID	1～180
    //        保留	181-253
    //        评估分系统	254
    //        广播                        255
    // 单  位:
    // 起始字:47
    // 起始位:0
    UINT32 ET_tgt_ID : 8;

    // 标识符:confidence_rng_estimate
    // 名  称:置信度_估算距离
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:48
    // 起始位:16
    UINT16 confidence_rng_estimate;

    // 标识符:target_range_estimate
    // 名  称:目标估算距离
    // 说  明:
    // 单  位:km
    // LSB  :1
    // 起始字:48
    // 起始位:0
    UINT16 target_range_estimate;

} IR_TRACK_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: univesal_date
// 信 号 组 名    称: 时间_世界日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 世界时间的日期
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} UNIVESAL_DATE_TYPE_DEF;

// 信 号 组 标 识 符: deltatime_mission_RTC
// 信 号 组 名    称: 时间_任务RTC差值
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 指任务时间与RTC时间的差值，各子域根据该差值与读取的RTC时间相加，计算得到当前任务时间。
//                    注：该任务时间为绝对任务时间，为当前距离2000年1月1日0时的纳秒数。
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} DELTATIME_MISSION_RTC_TYPE_DEF;

// 信 号 组 标 识 符: date_missiontime
// 信 号 组 名    称: 时间_任务日期
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:24
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT8 date_month;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 date_year;

} DATE_MISSIONTIME_TYPE_DEF;

// 信 号 组 标 识 符: DataLoadCheckResult
// 信 号 组 名    称: 数据加载校验结果
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 100
// 信 号 组 说    明:
typedef struct
{
    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 folder_id;

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 file_id;

    // 标识符:data_load_status
    // 名  称:数据加载状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    UINT32 data_load_status : 8;

    // 标识符:dataload_countdown
    // 名  称:加载倒计时
    // 说  明:
    // 单  位:Sec
    // LSB  :1
    // 起始字:2
    // 起始位:8
    UINT32 dataload_countdown : 16;

    // 标识符:data_check_result
    // 名  称:数据校验结果
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 data_check_result : 8;

} DATALOADCHECKRESULT_TYPE_DEF;

// 信 号 组 标 识 符: tgt_pitch_angularvelocity
// 信 号 组 名    称: 目标俯仰角速度_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} TGT_PITCH_ANGULARVELOCITY_TYPE_DEF;

// 信 号 组 标 识 符: tgt_el_rate_covariance
// 信 号 组 名    称: 目标俯仰角速率方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} TGT_EL_RATE_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_el_covariance
// 信 号 组 名    称: 目标俯仰方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_EL_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_brg_angularvelocity
// 信 号 组 名    称: 目标方位角速度_地理系
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} TGT_BRG_ANGULARVELOCITY_TYPE_DEF;

// 信 号 组 标 识 符: tgt_az_rate_covariance
// 信 号 组 名    称: 目标方位角速率方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: [-720,720]deg/s
typedef struct
{
    // 标识符:_angular_rate
    // 名  称:_角速率
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angular_rate;

} TGT_AZ_RATE_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_az_covariance
// 信 号 组 名    称: 目标方位方差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_AZ_COVARIANCE_TYPE_DEF;

// 信 号 组 标 识 符: irst_mode_paras
// 信 号 组 名    称: IRST工作参数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:cue_state
    // 名  称:目标提示状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 cue_state : 8;

    // 标识符:irst_form_mode
    // 名  称:IRST成像模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 irst_form_mode : 8;

    // 标识符:irst_work_state
    // 名  称:IRST工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 irst_work_state : 8;

    // 标识符:irst_work_mode
    // 名  称:IRST工作模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 irst_work_mode : 8;

} IRST_MODE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: team_cue_region_paras
// 信 号 组 名    称: 编队提示搜索区参数
// 信 号 组 字    数: 6
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 编队提示搜索区空间线段的起点、终点相对于本机的地理系方位、俯仰和斜距。
typedef struct
{
    // 标识符:start_point_bearing
    // 名  称:起点方位
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 start_point_bearing;

    // 标识符:start_point_pitch
    // 名  称:起点俯仰
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:1
    // 起始位:0
    INT32 start_point_pitch;

    // 标识符:start_point_distance
    // 名  称:起点距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    INT32 start_point_distance;

    // 标识符:end_point_bearing
    // 名  称:终点方位
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:3
    // 起始位:0
    INT32 end_point_bearing;

    // 标识符:end_point_pitch
    // 名  称:终点俯仰
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:4
    // 起始位:0
    INT32 end_point_pitch;

    // 标识符:end_point_distance
    // 名  称:终点距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:5
    // 起始位:0
    INT32 end_point_distance;

} TEAM_CUE_REGION_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: cue_paras_ir_tgt
// 信 号 组 名    称: IR目标提示参数
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:target_azimuth_geo
    // 名  称:目标方位角_地理系
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 target_azimuth_geo;

    // 标识符:target_elevation_geo
    // 名  称:目标俯仰角_地理系
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:1
    // 起始位:0
    INT32 target_elevation_geo;

} CUE_PARAS_IR_TGT_TYPE_DEF;

// 信 号 组 标 识 符: scan_elevation_center
// 信 号 组 名    称: 扫描俯仰中心
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 传感器的扫描俯仰中心角度。以上为正。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SCAN_ELEVATION_CENTER_TYPE_DEF;

// 信 号 组 标 识 符: scan_azimuth_center
// 信 号 组 名    称: 扫描方位中心
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 传感器扫描范围的中心角度。以右为正。
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} SCAN_AZIMUTH_CENTER_TYPE_DEF;

// 信 号 组 标 识 符: cue_los_paras
// 信 号 组 名    称: 提示搜索LOS参数
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 随动于LOS的方位和俯仰角
//                    根据C281协调，LOS参数的方位中心、俯仰中心均使用地理系方位、俯仰。
typedef struct
{
    // 标识符:scan_azimuth_center
    // 名  称:扫描方位中心
    // 说  明:传感器扫描范围的中心角度。以右为正。
    // 单  位:
    // 起始字:0
    // 起始位:0
    SCAN_AZIMUTH_CENTER_TYPE_DEF scan_azimuth_center;

    // 标识符:scan_elevation_center
    // 名  称:扫描俯仰中心
    // 说  明:传感器的扫描俯仰中心角度。以上为正。
    // 单  位:
    // 起始字:1
    // 起始位:0
    SCAN_ELEVATION_CENTER_TYPE_DEF scan_elevation_center;

} CUE_LOS_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: irst_cue_state
// 信 号 组 名    称: IR提示搜索参数状态
// 信 号 组 字    数: 13
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:validity_cue_tgt
    // 名  称:有效性_提示搜索目标参数
    // 说  明:提示搜索以目标为中心控制参数的有效性。
    // 单  位:
    // 起始字:0
    // 起始位:8
    BOOL_8 validity_cue_tgt;

    // 标识符:validity_cue_los
    // 名  称:有效性_提示搜索LOS参数
    // 说  明:以LOS为中心进行提示搜索参数的有效性。
    // 单  位:
    // 起始字:0
    // 起始位:0
    BOOL_8 validity_cue_los;

    // 标识符:cue_los_paras
    // 名  称:提示搜索LOS参数
    // 说  明:随动于LOS的方位和俯仰角
    //        根据C281协调，LOS参数的方位中心、俯仰中心均使用地理系方位、俯仰。
    // 单  位:
    // 起始字:1
    // 起始位:0
    CUE_LOS_PARAS_TYPE_DEF cue_los_paras;

    // 标识符:cue_paras_ir_tgt
    // 名  称:IR目标提示参数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    CUE_PARAS_IR_TGT_TYPE_DEF cue_paras_ir_tgt;

    // 标识符:cue_mission_state
    // 名  称:提示任务执行状态
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    UINT32 cue_mission_state : 8;

    // 标识符:cue_counter
    // 名  称:提示任务计数
    // 说  明:传感器管理下发的提示搜索任务计数，每一个新的任务时，该计数加1。当计数达到最大值时，清零后从新开始计数。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:16
    UINT32 cue_counter : 8;

    // 标识符:cue_way_set
    // 名  称:提示搜索方式
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    UINT32 cue_way_set : 8;

    // 标识符:cue_on_off
    // 名  称:提示搜索开关
    // 说  明:提示搜索开关。
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 cue_on_off : 8;

    // 标识符:cue_el_coverage_16_bite
    // 名  称:提示俯仰宽度_16bite
    // 说  明:表示提示搜索的俯仰宽度，用16位无符号数表示。
    // 单  位:mrad
    // LSB  :0.1
    // 起始字:6
    // 起始位:16
    UINT16 cue_el_coverage_16_bite;

    // 标识符:cue_az_coverage_16bite
    // 名  称:提示方位宽度_16bite
    // 说  明:表示提示搜索方位的宽度，用16位无符号数表示。
    // 单  位:mrad
    // LSB  :0.01
    // 起始字:6
    // 起始位:0
    UINT16 cue_az_coverage_16bite;

    // 标识符:team_cue_region_paras
    // 名  称:编队提示搜索区参数
    // 说  明:编队提示搜索区空间线段的起点、终点相对于本机的地理系方位、俯仰和斜距。
    // 单  位:
    // 起始字:7
    // 起始位:0
    TEAM_CUE_REGION_PARAS_TYPE_DEF team_cue_region_paras;

} IRST_CUE_STATE_TYPE_DEF;

// 信 号 组 标 识 符: IR_Transom_paras
// 信 号 组 名    称: IR光窗参数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:Transom_temp
    // 名  称:光窗温度
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:0
    // 起始位:8
    INT32 Transom_temp : 8;

    // 标识符:Transom_mist_eliminate_state
    // 名  称:光窗去雾状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 Transom_mist_eliminate_state : 8;

} IR_TRANSOM_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: IR_prepare_paras
// 信 号 组 名    称: 准备状态参数
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:prepare_state
    // 名  称:准备状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 prepare_state : 8;

    // 标识符:infrared_correct_state
    // 名  称:红外校正状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 infrared_correct_state : 8;

    // 标识符:prepare_state_focus
    // 名  称:检调焦状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 prepare_state_focus : 8;

    // 标识符:prepare_state_dim
    // 名  称:检调光状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 prepare_state_dim : 8;

} IR_PREPARE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: IR_image_paras
// 信 号 组 名    称: IR图像参数
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:light_focus_mode
    // 名  称:可见光调焦模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 light_focus_mode : 8;

    // 标识符:light_dim_mode
    // 名  称:可见光调光模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 light_dim_mode : 8;

    // 标识符:light_enhance_mode
    // 名  称:可见光增强状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    UINT32 light_enhance_mode : 8;

    // 标识符:light_mist_eliminate_state
    // 名  称:可见光去雾状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 light_mist_eliminate_state : 8;

    // 标识符:light_exposure_time
    // 名  称:可见光曝光时间
    // 说  明:
    // 单  位:M_sc
    // LSB  :0.1
    // 起始字:1
    // 起始位:0
    INT32 light_exposure_time : 16;

    // 标识符:video_polar
    // 名  称:视频极化
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    UINT32 video_polar : 8;

    // 标识符:infrared_coefficient
    // 名  称:红外系数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:16
    UINT32 infrared_coefficient : 8;

    // 标识符:infrared_focus_mode
    // 名  称:红外调焦模式
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 infrared_focus_mode : 8;

    // 标识符:infrared_dim_mode
    // 名  称:红外调光模式
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 infrared_dim_mode : 8;

    // 标识符:focus_value_infrared
    // 名  称:红外调焦值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:24
    INT32 focus_value_infrared : 8;

    // 标识符:focus_value_light
    // 名  称:可见光调焦值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    INT32 focus_value_light : 8;

    // 标识符:environmnet_type
    // 名  称:环境类型
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 environmnet_type : 8;

    // 标识符:infrared_enhance_mode
    // 名  称:红外增强状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 infrared_enhance_mode : 8;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:non_uniform_correct_state
    // 名  称:非均匀校正状态
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 non_uniform_correct_state : 8;

    // 标识符:light_value_infrared
    // 名  称:红外调光值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:8
    INT32 light_value_infrared : 8;

    // 标识符:light_value_light
    // 名  称:可见光调光值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    INT32 light_value_light : 8;

} IR_IMAGE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: IR_wide_image_paras
// 信 号 组 名    称: IR广域成像范围参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IR_range_lowline
    // 名  称:IR距离近界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:0
    // 起始位:16
    UINT32 IR_range_lowline : 16;

    UINT32 spare1 : 10;  // 保留字段
    // 标识符:IR_WIDE_IMAGE_DIRECTION
    // 名  称:光电广域成像扫描方向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 IR_WIDE_IMAGE_DIRECTION : 3;

    // 标识符:IR_WIDE_IMAGE_MODE
    // 名  称:光电广域成像子模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 IR_WIDE_IMAGE_MODE : 3;

    // 标识符:IR_IMAGE_RANGE
    // 名  称:量程
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:1
    // 起始位:16
    UINT16 IR_IMAGE_RANGE;

    // 标识符:IR_range_upline
    // 名  称:IR距离远界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:1
    // 起始位:0
    UINT16 IR_range_upline;

    // 标识符:IR_scan_end_angle
    // 名  称:光电扫描结束角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.01
    // 起始字:2
    // 起始位:16
    INT16 IR_scan_end_angle;

    // 标识符:IR_scan_start_angle
    // 名  称:光电扫描起始角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    INT16 IR_scan_start_angle;

    // 标识符:D_area_altitude
    // 名  称:距离优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:3
    // 起始位:16
    INT16 D_area_altitude;

    // 标识符:AZ_area_altitude
    // 名  称:方位优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:3
    // 起始位:0
    INT16 AZ_area_altitude;

} IR_WIDE_IMAGE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: area_monitor_paras_IR
// 信 号 组 名    称: 光电区域监视范围参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:center_point_pos
    // 名  称:中心点位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    CENTER_POINT_POS_TYPE_DEF center_point_pos;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:IR_IMG_FLAG
    // 名  称:光电成像状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 IR_IMG_FLAG : 8;

} AREA_MONITOR_PARAS_IR_TYPE_DEF;

// 信 号 组 标 识 符: area_image_paras_IR
// 信 号 组 名    称: 光电区域成像范围参数
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 3
// 信 号 组 说    明:
typedef struct
{
    // 标识符:center_point_pos
    // 名  称:中心点位置
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    CENTER_POINT_POS_TYPE_DEF center_point_pos;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:Area_validity
    // 名  称:区域有效性
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 Area_validity : 8;

    // 标识符:IR_IMG_FLAG
    // 名  称:光电成像状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 IR_IMG_FLAG : 8;

    // 标识符:IR_AREA_LENGTH
    // 名  称:光电区域边长
    // 说  明:
    // 单  位:km
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 IR_AREA_LENGTH : 8;

} AREA_IMAGE_PARAS_IR_TYPE_DEF;

// 信 号 组 标 识 符: image_volum_IR_actual
// 信 号 组 名    称: 光雷实际成像参数
// 信 号 组 字    数: 21
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IR_wide_image_paras
    // 名  称:IR广域成像范围参数
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    IR_WIDE_IMAGE_PARAS_TYPE_DEF IR_wide_image_paras;

    // 标识符:area_image_paras_IR
    // 名  称:光电区域成像范围参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AREA_IMAGE_PARAS_IR_TYPE_DEF area_image_paras_IR[3];

    // 标识符:area_monitor_paras_IR
    // 名  称:光电区域监视范围参数
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    AREA_MONITOR_PARAS_IR_TYPE_DEF area_monitor_paras_IR;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:IR_IMG_MODE
    // 名  称:光电成像方式
    // 说  明:
    // 单  位:
    // 起始字:20
    // 起始位:0
    UINT32 IR_IMG_MODE : 8;

} IMAGE_VOLUM_IR_ACTUAL_TYPE_DEF;

// 信 号 组 标 识 符: image_volum_IR
// 信 号 组 名    称: 光电成像参数
// 信 号 组 字    数: 21
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:IR_wide_image_paras
    // 名  称:IR广域成像范围参数
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    IR_WIDE_IMAGE_PARAS_TYPE_DEF IR_wide_image_paras;

    // 标识符:area_image_paras_IR
    // 名  称:光电区域成像范围参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    AREA_IMAGE_PARAS_IR_TYPE_DEF area_image_paras_IR[3];

    // 标识符:area_monitor_paras_IR
    // 名  称:光电区域监视范围参数
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    AREA_MONITOR_PARAS_IR_TYPE_DEF area_monitor_paras_IR;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:IR_IMG_MODE
    // 名  称:光电成像方式
    // 说  明:
    // 单  位:
    // 起始字:20
    // 起始位:0
    UINT32 IR_IMG_MODE : 8;

} IMAGE_VOLUM_IR_TYPE_DEF;

// 信 号 组 标 识 符: VMS_usimKeyData_US
// 信 号 组 名    称: VMS_机电关键参数_机电综合
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:VMS_LGState_R
    // 名  称:VMS_起落架状态_右
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 VMS_LGState_R : 8;

    // 标识符:VMS_LGState_L
    // 名  称:VMS_起落架状态_左
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 VMS_LGState_L : 8;

    // 标识符:VMS_LGState_H
    // 名  称:VMS_起落架状态_前
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_LGState_H : 8;

    // 标识符:VMS_LGState_M
    // 名  称:VMS_起落架系统_主
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_LGState_M : 8;

    // 标识符:VMS_ZYLJ_F
    // 名  称:VMS_座椅离机_前
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:24
    UINT32 VMS_ZYLJ_F : 8;

    // 标识符:VMS_TSSB_F
    // 名  称:VMS_弹射手柄启动_前
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 VMS_TSSB_F : 8;

    // 标识符:VMS_CY_State
    // 名  称:VMS_冲压状态
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 VMS_CY_State : 8;

    // 标识符:VMS_TSSB_B
    // 名  称:VMS_弹射手柄启动_后
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 VMS_TSSB_B : 8;

    // 标识符:VMS_ZYLJ_B
    // 名  称:VMS_座椅离机_后
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:24
    UINT32 VMS_ZYLJ_B : 8;

    // 标识符:VMS_LDCstate
    // 名  称:VMS_液冷供液状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:16
    UINT32 VMS_LDCstate : 8;

    // 标识符:VMS_LC_State
    // 名  称:VMS_液冷状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 VMS_LC_State : 8;

    // 标识符:VMS_WC_State
    // 名  称:VMS_风冷状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 VMS_WC_State : 8;

    // 标识符:VMS_value_LDCtemp
    // 名  称:VMS_数据值_液冷温度
    // 说  明:
    // 单  位:Cel
    // LSB  :0.1
    // 起始字:3
    // 起始位:16
    INT32 VMS_value_LDCtemp : 16;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:VMS_valid_LDCTemp
    // 名  称:VMS_有效性_液冷温度
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 VMS_valid_LDCTemp : 8;

} VMS_USIMKEYDATA_US_TYPE_DEF;

// 信 号 组 标 识 符: VMS_usimKeyData_fuel
// 信 号 组 名    称: VMS_机电关键参数_燃油
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 24;  // 保留字段
    // 标识符:VMS_valid_fuel_use
    // 名  称:VMS_有效性_余油_可用油量
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_valid_fuel_use : 8;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:VMS_value_fuel_use
    // 名  称:VMS_数据值_余油_可用油量
    // 说  明:单位：Kg
    // 单  位:kg
    // LSB  :1
    // 起始字:1
    // 起始位:0
    INT16 VMS_value_fuel_use;

} VMS_USIMKEYDATA_FUEL_TYPE_DEF;

// 信 号 组 标 识 符: VMS_usimkeyData_ENG2
// 信 号 组 名    称: VMS_机电关键参数_发动机2
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare2 : 8;  // 保留字段
    // 标识符:VMS_REng_Mode
    // 名  称:VMS_右发_工作模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 VMS_REng_Mode : 8;

    // 标识符:VMS_LEng_Mode
    // 名  称:VMS_左发_工作模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_LEng_Mode : 8;

    UINT32 spare1 : 4;  // 保留字段
    // 标识符:VMS_valid_REng_T1
    // 名  称:VMS_有效性_右发_T1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 VMS_valid_REng_T1 : 1;

    // 标识符:VMS_valid_LEng_T1
    // 名  称:VMS_有效性_左发_T1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 VMS_valid_LEng_T1 : 1;

    // 标识符:VMS_valid_REng_Thor
    // 名  称:VMS_有效性_右发油门角度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 VMS_valid_REng_Thor : 1;

    // 标识符:VMS_valid_LEng_Thor
    // 名  称:VMS_有效性_左发油门角度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_valid_LEng_Thor : 1;

    // 标识符:VMS_value_REng_T1
    // 名  称:VMS_数据值_右发_T1
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:1
    // 起始位:16
    INT16 VMS_value_REng_T1;

    // 标识符:VMS_value_LEng_T1
    // 名  称:VMS_数据值_左发_T1
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:1
    // 起始位:0
    INT16 VMS_value_LEng_T1;

    // 标识符:VMS_value_REng_Thor
    // 名  称:VMS_数据值_右发油门角度
    // 说  明:WS10C取0~120°
    //        后续更新发动机型号后再确定值域范围。
    // 单  位:Deg
    // LSB  :0.1
    // 起始字:2
    // 起始位:16
    INT16 VMS_value_REng_Thor;

    // 标识符:VMS_value_LEng_Thor
    // 名  称:VMS_数据值_左发油门角度
    // 说  明:WS10C取0~120°
    //        后续更新发动机型号后再确定值域范围。
    // 单  位:Deg
    // LSB  :0.1
    // 起始字:2
    // 起始位:0
    INT16 VMS_value_LEng_Thor;

} VMS_USIMKEYDATA_ENG2_TYPE_DEF;

// 信 号 组 标 识 符: VMS_usimkeyData_ENG
// 信 号 组 名    称: VMS_机电关键参数_发动机
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare4 : 21;  // 保留字段
    // 标识符:VMS_warning_REng_AfterburnOFF
    // 名  称:VMS_右发加力未接通
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:10
    UINT32 VMS_warning_REng_AfterburnOFF : 1;

    // 标识符:VMS_REng_Afterburn
    // 名  称:VMS_右发加力
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:9
    UINT32 VMS_REng_Afterburn : 1;

    // 标识符:VMS_warning_LEng_AfterburnOFF
    // 名  称:VMS_左发加力未接通
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_warning_LEng_AfterburnOFF : 1;

    // 标识符:VMS_LEng_Afterburn
    // 名  称:VMS_左发加力
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:7
    UINT32 VMS_LEng_Afterburn : 1;

    // 标识符:VMS_valid_REng_T4
    // 名  称:VMS_有效性_右发_T4
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:6
    UINT32 VMS_valid_REng_T4 : 1;

    UINT32 spare3 : 1;  // 保留字段
    // 标识符:VMS_valid_REng_N2
    // 名  称:VMS_有效性_右发_N2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:4
    UINT32 VMS_valid_REng_N2 : 1;

    UINT32 spare2 : 1;  // 保留字段
    // 标识符:VMS_valid_LEng_T4
    // 名  称:VMS_有效性_左发_T4
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 VMS_valid_LEng_T4 : 1;

    UINT32 spare1 : 1;  // 保留字段
    // 标识符:VMS_valid_LEng_N2
    // 名  称:VMS_有效性_左发_N2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_valid_LEng_N2 : 1;

    SPARE8 spare5[2];  // 保留字段

    // 标识符:VMS_value_LEng_N2
    // 名  称:VMS_数据值_左发_N2
    // 说  明:
    // 单  位:%
    // LSB  :0.1
    // 起始字:1
    // 起始位:0
    INT16 VMS_value_LEng_N2;

    SPARE8 spare6[2];  // 保留字段

    // 标识符:VMS_value_LEng_T4
    // 名  称:VMS_数据值_左发_T4
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:2
    // 起始位:0
    INT16 VMS_value_LEng_T4;

    SPARE8 spare7[2];  // 保留字段

    // 标识符:VMS_value_REng_N2
    // 名  称:VMS_数据值_右发_N2
    // 说  明:
    // 单  位:%
    // LSB  :0.1
    // 起始字:3
    // 起始位:0
    INT16 VMS_value_REng_N2;

    SPARE8 spare8[2];  // 保留字段

    // 标识符:VMS_value_REng_T4
    // 名  称:VMS_数据值_右发_T4
    // 说  明:
    // 单  位:Cel
    // LSB  :1
    // 起始字:4
    // 起始位:0
    INT16 VMS_value_REng_T4;

} VMS_USIMKEYDATA_ENG_TYPE_DEF;

// 信 号 组 标 识 符: VMS_usimKeyData_elec
// 信 号 组 名    称: VMS_机电关键参数_供电
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 16;  // 保留字段
    // 标识符:VMS_elecPower_DCDC4
    // 名  称:VMS_供电_DCDC4
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:14
    UINT32 VMS_elecPower_DCDC4 : 2;

    // 标识符:VMS_elecPower_DCDC3
    // 名  称:VMS_供电_DCDC3
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:12
    UINT32 VMS_elecPower_DCDC3 : 2;

    // 标识符:VMS_elecPower_DCDC2
    // 名  称:VMS_供电_DCDC2
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:10
    UINT32 VMS_elecPower_DCDC2 : 2;

    // 标识符:VMS_elecPower_DCDC1
    // 名  称:VMS_供电_DCDC1
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_elecPower_DCDC1 : 2;

    // 标识符:VMS_elecPower_GenAsiss
    // 名  称:VMS_供电_直发状态_辅
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:6
    UINT32 VMS_elecPower_GenAsiss : 2;

    // 标识符:VMS_elecPower_GenR
    // 名  称:VMS_供电_直发状态_右
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:4
    UINT32 VMS_elecPower_GenR : 2;

    // 标识符:VMS_elecPower_GenL
    // 名  称:VMS_供电_直发状态_左
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 VMS_elecPower_GenL : 2;

    // 标识符:VMS_elecPower_GDS
    // 名  称:VMS_供电_地面电源状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_elecPower_GDS : 2;

} VMS_USIMKEYDATA_ELEC_TYPE_DEF;

// 信 号 组 标 识 符: VMS_FcsSigColection_AC_transfer
// 信 号 组 名    称: VMS_飞控信号采集数据_转发
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 直接从VMS1394转发的飞控信号采集数据中的重量信息：包括：飞机重量的数值和飞机重量的有效性。
//                    直接从VMS1394转发的飞控信号采集数据中的销密记录信号
typedef struct
{
    // 标识符:VMS_data_destroy_signal
    // 名  称:VMS_销密记录信号
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 VMS_data_destroy_signal : 8;

    // 标识符:valid_AC_weight_VMS
    // 名  称:有效性_飞机重量_VMS
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 valid_AC_weight_VMS : 8;

    // 标识符:value_AC_weight_VMS
    // 名  称:数值_飞机重量_VMS
    // 说  明:单位：吨
    //        值域：[10.00,50.00]
    //        LSB：0.01
    // 单  位:
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 value_AC_weight_VMS : 16;

} VMS_FCSSIGCOLECTION_AC_TRANSFER_TYPE_DEF;

// 信 号 组 标 识 符: VMS_AT_data
// 信 号 组 名    称: VMS_自动油门状态
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare2 : 12;  // 保留字段
    // 标识符:VMS_AT_ECO
    // 名  称:VMS_当前自动油门省油标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:19
    UINT32 VMS_AT_ECO : 1;

    // 标识符:VMS_AT_Display
    // 名  称:VMS_当前自动油门值显示
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:18
    UINT32 VMS_AT_Display : 1;

    // 标识符:VMS_AT_DEGRADED
    // 名  称:VMS_自动油门降级
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:17
    UINT32 VMS_AT_DEGRADED : 1;

    // 标识符:VMS_AT_CSS
    // 名  称:VMS_自动油门悬挂
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 VMS_AT_CSS : 1;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:VMS_AT_State
    // 名  称:VMS_自动油门接通状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_AT_State : 8;

    // 标识符:VMS_AT_MA
    // 名  称:VMS_当前马赫保持值
    // 说  明:[0,2.5]
    // 单  位:Mach
    // LSB  :0.01
    // 起始字:1
    // 起始位:16
    UINT16 VMS_AT_MA;

    // 标识符:VMS_AT_CAS
    // 名  称:VMS_当前表速保持值
    // 说  明:[0,1500]km/h
    // 单  位:km/h
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 VMS_AT_CAS;

    // 标识符:VMS_VirlCfg
    // 名  称:VMS_减速板放出百分比
    // 说  明:
    // 单  位:%
    // LSB  :1
    // 起始字:2
    // 起始位:16
    INT16 VMS_VirlCfg;

    // 标识符:VMS_AT_TOT
    // 名  称:VMS_当前地速保持值
    // 说  明:[0,1500]km/h
    // 单  位:km/h
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT16 VMS_AT_TOT;

} VMS_AT_DATA_TYPE_DEF;

// 信 号 组 标 识 符: VMS_AP_State
// 信 号 组 名    称: VMS_自动驾驶状态
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare1 : 9;  // 保留字段
    // 标识符:VMS_TF_ALT_twinkle
    // 名  称:VMS_地形跟随相对高度闪烁标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:22
    UINT32 VMS_TF_ALT_twinkle : 1;

    // 标识符:VMS_AP_Trk_Display
    // 名  称:VMS_当前航迹保持值显示
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:21
    UINT32 VMS_AP_Trk_Display : 1;

    // 标识符:VMS_AP_Alt_Display
    // 名  称:VMS_当前高度保持值显示
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:20
    UINT32 VMS_AP_Alt_Display : 1;

    // 标识符:VMS_AP_DEGRADED
    // 名  称:VMS_自动驾驶降级
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:19
    UINT32 VMS_AP_DEGRADED : 1;

    // 标识符:VMS_AP_CSS
    // 名  称:VMS_自动驾驶悬挂
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:18
    UINT32 VMS_AP_CSS : 1;

    // 标识符:VMS_AP_ENGAGE
    // 名  称:VMS_自动驾驶接通
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:17
    UINT32 VMS_AP_ENGAGE : 1;

    // 标识符:VMS_AP_Fail_CUT
    // 名  称:VMS_自动驾驶故障切除
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 VMS_AP_Fail_CUT : 1;

    // 标识符:VMS_AP_State_lat
    // 名  称:VMS_自动驾驶横向状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_AP_State_lat : 8;

    // 标识符:VMS_AP_State_long
    // 名  称:VMS_自动驾驶纵向状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_AP_State_long : 8;

    // 标识符:VMS_TF_ALT
    // 名  称:VMS_地形跟随相对高度
    // 说  明:(0，15000]m
    // 单  位:m
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT32 VMS_TF_ALT : 16;

    // 标识符:VMS_Sensors_of_LOC
    // 名  称:VMS_进场着陆阶段所选传感器
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 VMS_Sensors_of_LOC : 8;

    // 标识符:VMS_Cur_fly_status
    // 名  称:VMS_当前所处飞行阶段
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 VMS_Cur_fly_status : 8;

} VMS_AP_STATE_TYPE_DEF;

// 信 号 组 标 识 符: VMS_fcsKeyData
// 信 号 组 名    称: VMS_飞控关键参数
// 信 号 组 字    数: 10
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    UINT32 spare2 : 20;  // 保留字段
    // 标识符:VMS_PULLUP_FAULT
    // 名  称:VMS_防撞拉起故障状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:11
    UINT32 VMS_PULLUP_FAULT : 1;

    // 标识符:VMS_PULLUP_DEGRADED
    // 名  称:VMS_防撞拉起降级状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:10
    UINT32 VMS_PULLUP_DEGRADED : 1;

    // 标识符:VMS_PULLUP_CSS
    // 名  称:VMS_防撞拉起悬挂状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:9
    UINT32 VMS_PULLUP_CSS : 1;

    // 标识符:VMS_PULLUP_ENGAGE
    // 名  称:VMS_防撞拉起接通状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS_PULLUP_ENGAGE : 1;

    UINT32 spare1 : 4;  // 保留字段
    // 标识符:VMS_WOW_Main
    // 名  称:VMS_轮载状态_主
    // 说  明:主轮载状态
    // 单  位:
    // 起始字:0
    // 起始位:3
    UINT32 VMS_WOW_Main : 1;

    // 标识符:VMS_WOW_Right
    // 名  称:VMS_轮载状态_右
    // 说  明:右轮载状态
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 VMS_WOW_Right : 1;

    // 标识符:VMS_WOW_Left
    // 名  称:VMS_轮载状态_左
    // 说  明:左轮载状态
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 VMS_WOW_Left : 1;

    // 标识符:VMS_WOW_Front
    // 名  称:VMS_轮载状态_前
    // 说  明:前轮载状态
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS_WOW_Front : 1;

    // 标识符:VMS_Position_RLEF
    // 名  称:VMS_舵面位置_右前襟
    // 说  明:飞控舵面偏转角度——右前襟
    // 单  位:Deg
    // LSB  :40/16384
    // 起始字:1
    // 起始位:16
    INT16 VMS_Position_RLEF;

    // 标识符:VMS_Position_LLEF
    // 名  称:VMS_舵面位置_左前襟
    // 说  明:飞控舵面偏转角度——左前襟
    // 单  位:Deg
    // LSB  :40/16384
    // 起始字:1
    // 起始位:0
    INT16 VMS_Position_LLEF;

    // 标识符:VMS_AP_State
    // 名  称:VMS_自动驾驶状态
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    VMS_AP_STATE_TYPE_DEF VMS_AP_State;

    // 标识符:VMS_AP_TRACK_req
    // 名  称:VMS_自动驾驶航迹保持值
    // 说  明:
    // 单  位:S_c
    // LSB  :1/32768
    // 起始字:4
    // 起始位:16
    INT16 VMS_AP_TRACK_req;

    // 标识符:VMS_AP_ALT_req
    // 名  称:VMS_自动驾驶高度保持值
    // 说  明:[0,15000]米
    // 单  位:m
    // LSB  :1
    // 起始字:4
    // 起始位:0
    INT16 VMS_AP_ALT_req;

    // 标识符:VMS_AT_data
    // 名  称:VMS_自动油门状态
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    VMS_AT_DATA_TYPE_DEF VMS_AT_data;

    // 标识符:VMS_TF_desired_climbing_angle
    // 名  称:VMS_地形跟随期望爬升角
    // 说  明:
    // 单  位:S_c
    // LSB  :1/32768
    // 起始字:8
    // 起始位:16
    INT16 VMS_TF_desired_climbing_angle;

    // 标识符:VMS_PULLUP_Count_Down
    // 名  称:VMS_自动防撞倒计时
    // 说  明:自动防撞接通剩余时间百分比，范围[0,100]
    // 单  位:%
    // LSB  :1
    // 起始字:8
    // 起始位:0
    UINT16 VMS_PULLUP_Count_Down;

    // 标识符:VMS_Position_RC
    // 名  称:VMS_舵面位置_右鸭翼
    // 说  明:飞控舵面偏转角度——右鸭翼
    // 单  位:Deg
    // LSB  :40/16384
    // 起始字:9
    // 起始位:16
    INT16 VMS_Position_RC;

    // 标识符:VMS_Position_LC
    // 名  称:VMS_舵面位置_左鸭翼
    // 说  明:飞控舵面偏转角度——左鸭翼
    // 单  位:Deg
    // LSB  :40/16384
    // 起始字:9
    // 起始位:0
    INT16 VMS_Position_LC;

} VMS_FCSKEYDATA_TYPE_DEF;

// 信 号 组 标 识 符: VMS_FcsCcs_EM_state
// 信 号 组 名    称: VMS_飞管指控辐射状态
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 直接从VMS1394转发的高度表、起降引导、测控链路的辐射状态。
typedef struct
{
    UINT32 spare4 : 5;  // 保留字段
    // 标识符:VMS1394_YKZ_SDL_DOWN_WROKSTATUS
    // 名  称:VMS1394_遥控帧_S链下行工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 VMS1394_YKZ_SDL_DOWN_WROKSTATUS : 3;

    UINT32 spare3 : 2;  // 保留字段
    // 标识符:VMS1394_YKZ_KuDL_DOWN_WROKSTATUS
    // 名  称:VMS1394_遥控帧_Ku链下行工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:19
    UINT32 VMS1394_YKZ_KuDL_DOWN_WROKSTATUS : 3;

    // 标识符:VMS1394_YKZ_KaDL_DOWN_WROKSTATUS
    // 名  称:VMS1394_遥控帧_Ka链下行工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 VMS1394_YKZ_KaDL_DOWN_WROKSTATUS : 3;

    UINT32 spare2 : 2;  // 保留字段
    // 标识符:VMS1394_YKZ_LDL_DOWN_WROKSTATUS
    // 名  称:VMS1394_遥控帧_L链下行工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:11
    UINT32 VMS1394_YKZ_LDL_DOWN_WROKSTATUS : 3;

    // 标识符:VMS1394_YKZ_CDL_DOWN_WROKSTATUS
    // 名  称:VMS1394_遥控帧_C链下行工作状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 VMS1394_YKZ_CDL_DOWN_WROKSTATUS : 3;

    UINT32 spare1 : 5;  // 保留字段
    // 标识符:VMS1394_MWE_silence_status
    // 名  称:VMS1394_毫米波静默状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:2
    UINT32 VMS1394_MWE_silence_status : 1;

    // 标识符:VMS1394_RA2_silence_status
    // 名  称:VMS1394_高度表静默2状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:1
    UINT32 VMS1394_RA2_silence_status : 1;

    // 标识符:VMS1394_RA1_silence_status
    // 名  称:VMS1394_高度表静默1状态
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 VMS1394_RA1_silence_status : 1;

} VMS_FCSCCS_EM_STATE_TYPE_DEF;

// 信 号 组 标 识 符: view_fov_pitch
// 信 号 组 名    称: 视场大小_俯仰
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 表示视频在显示器上的视场的视频源的俯仰大小
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} VIEW_FOV_PITCH_TYPE_DEF;

// 信 号 组 标 识 符: view_fov_azimuth
// 信 号 组 名    称: 视场大小_方位
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 表示视频在显示器上的显示视场的视频源的方位大小
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} VIEW_FOV_AZIMUTH_TYPE_DEF;

// 信 号 组 标 识 符: image_center_y
// 信 号 组 名    称: 图像中心点坐标Y
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} IMAGE_CENTER_Y_TYPE_DEF;

// 信 号 组 标 识 符: image_center_x
// 信 号 组 名    称: 图像中心点坐标X
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_pixel
    // 名  称:_像素
    // 说  明:
    // 单  位:
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _pixel;

} IMAGE_CENTER_X_TYPE_DEF;

// 信 号 组 标 识 符: IR_surface_track
// 信 号 组 名    称: IR面目标参数
// 信 号 组 字    数: 17
// 信 号 组 数组长度: 4
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_in_SL
    // 名  称:目标与射击列表关联
    // 说  明:表明目标在射击列表内的位置。
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 tgt_in_SL : 8;

    // 标识符:target_exist_tag
    // 名  称:目标存在标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 target_exist_tag : 8;

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //        目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT32 IR_track_number : 16;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:range_source
    // 名  称:距离获取方式
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:16
    UINT32 range_source : 8;

    // 标识符:IR_track_distance_validity
    // 名  称:目标距离有效性
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:8
    UINT32 IR_track_distance_validity : 8;

    // 标识符:target_track_state
    // 名  称:目标跟踪状态
    // 说  明:20230522:更改11-STT_DOT描述为“点迹截获进SAM”。
    //        20230608：新增“12-TRACK_SHOOTLIST-火控级跟踪”。
    // 单  位:
    // 起始字:1
    // 起始位:0
    UINT32 target_track_state : 8;

    // 标识符:IR_track_azimuth
    // 名  称:IR目标方位
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:2
    // 起始位:0
    INT32 IR_track_azimuth;

    // 标识符:IR_track_elevation
    // 名  称:IR目标俯仰
    // 说  明:
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:3
    // 起始位:0
    INT32 IR_track_elevation;

    // 标识符:IR_track_distance
    // 名  称:IR目标距离
    // 说  明:
    // 单  位:m
    // LSB  :0.01
    // 起始字:4
    // 起始位:0
    INT32 IR_track_distance;

    // 标识符:IR_track_AZ_angularvelocity
    // 名  称:目标方位角速度
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.0001
    // 起始字:5
    // 起始位:0
    INT32 IR_track_AZ_angularvelocity;

    // 标识符:IR_track_AZ_angaccel
    // 名  称:目标方位角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.0001
    // 起始字:6
    // 起始位:0
    INT32 IR_track_AZ_angaccel;

    // 标识符:IR_track_EL_angularvelocity
    // 名  称:目标俯仰角速度
    // 说  明:
    // 单  位:mrad/s
    // LSB  :0.0001
    // 起始字:7
    // 起始位:0
    INT32 IR_track_EL_angularvelocity;

    // 标识符:IR_track_EL_angaccel
    // 名  称:目标俯仰角加速度
    // 说  明:
    // 单  位:mrad/s2
    // LSB  :0.0001
    // 起始字:8
    // 起始位:0
    INT32 IR_track_EL_angaccel;

    // 标识符:covariance_azimuth
    // 名  称:目标方位角方差
    // 说  明:单位为角度单位的平方。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:9
    // 起始位:0
    UINT32 covariance_azimuth;

    // 标识符:covariance_azimuth_angvel
    // 名  称:目标方位角与角速度协方差
    // 说  明:单位为角度与角速度的乘积。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:10
    // 起始位:0
    INT32 covariance_azimuth_angvel;

    // 标识符:covarance_anglvel_azimuth
    // 名  称:目标方位角速度与方位角协方差
    // 说  明:单位为角度与角速度的乘积。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:11
    // 起始位:0
    INT32 covarance_anglvel_azimuth;

    // 标识符:covariance_azimuth_angvelocity
    // 名  称:目标方位角速度方差
    // 说  明:单位为角速度单位的平方。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:12
    // 起始位:0
    INT32 covariance_azimuth_angvelocity;

    // 标识符:covariance_elevation
    // 名  称:目标俯仰角方差
    // 说  明:单位为角度单位的平方。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:13
    // 起始位:0
    INT32 covariance_elevation;

    // 标识符:covariance_elevation_angvel
    // 名  称:目标俯仰角与俯仰角速度协方差
    // 说  明:单位为角度与角速度的乘积。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:14
    // 起始位:0
    INT32 covariance_elevation_angvel;

    // 标识符:covarance_anglvel_elevation
    // 名  称:目标俯仰角速度与俯仰角协方差
    // 说  明:单位为角度与角速度的乘积。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:15
    // 起始位:0
    INT32 covarance_anglvel_elevation;

    // 标识符:covariance_elevation_angvelocity
    // 名  称:目标俯仰角速度方差
    // 说  明:单位为角速度单位的平方。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:16
    // 起始位:0
    INT32 covariance_elevation_angvelocity;

} IR_SURFACE_TRACK_TYPE_DEF;

// 信 号 组 标 识 符: tgt_stae_altitude
// 信 号 组 名    称: 目标惯性卫星大气高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} TGT_STAE_ALTITUDE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_precision
// 信 号 组 名    称: 目标数据精度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_data_manual_input_lable
    // 名  称:目标信息人工装订标识
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:24
    UINT32 tgt_data_manual_input_lable : 8;

    // 标识符:angular_precision
    // 名  称:角度精度
    // 说  明:载机对目标的测角误差小于等于0.25度时，角度精度为精
    //        载机对目标的测角误差小于等于1度且大于0.25度时，角度精度为粗
    //        载机对目标的测角误差小于等于3度且大于1度时，角度精度为极粗
    //        载机对目标的测角误差大于3度时，角度精度为无效
    // 单  位:
    // 起始字:0
    // 起始位:16
    UINT32 angular_precision : 8;

    // 标识符:velocity_precision
    // 名  称:速度精度
    // 说  明:载机对目标的测速误差小于等于25m/s时，速度精度为精
    //        载机对目标的测速误差小于等于50m/s且大于25m/s时，速度精度为粗
    //        载机对目标的测速误差小于等于150m/s且大于50m/s时，速度精度为极粗
    //        载机对目标的测速误差大于150m/s时，速度精度为无效
    // 单  位:
    // 起始字:0
    // 起始位:8
    UINT32 velocity_precision : 8;

    // 标识符:range_precison
    // 名  称:距离精度
    // 说  明:载机对目标的测距误差小于等于200m时，距离精度为精
    //        载机对目标的测距误差小于等于2000m且大于200m时，距离精度为粗
    //        载机对目标的测距误差小于等于4000m且大于2000m时，距离精度为极粗
    //        载机对目标的测距误差大于4000m时，距离精度为无效
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 range_precison : 8;

} TGT_PRECISION_TYPE_DEF;

// 信 号 组 标 识 符: tgt_longitude
// 信 号 组 名    称: 目标经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} TGT_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_latitude
// 信 号 组 名    称: 目标纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} TGT_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_altitude
// 信 号 组 名    称: 目标高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} TGT_ALTITUDE_TYPE_DEF;

// 信 号 组 标 识 符: tgtset_tgt_real_pos
// 信 号 组 名    称: 人工装订下的目标真实位置
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_longitude
    // 名  称:目标经度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_LONGITUDE_TYPE_DEF tgt_longitude;

    // 标识符:tgt_latitude
    // 名  称:目标纬度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_LATITUDE_TYPE_DEF tgt_latitude;

    // 标识符:tgt_altitude
    // 名  称:目标高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_ALTITUDE_TYPE_DEF tgt_altitude;

} TGTSET_TGT_REAL_POS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_Z_CGCS2000
// 信 号 组 名    称: 目标速度_Z_CGCS2000
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_Z_CGCS2000_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_Y_CGCS2000
// 信 号 组 名    称: 目标速度_Y_CGCS2000
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_Y_CGCS2000_TYPE_DEF;

// 信 号 组 标 识 符: tgt_V_X_CGCS2000
// 信 号 组 名    称: 目标速度_X_CGCS2000
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_V_X_CGCS2000_TYPE_DEF;

// 信 号 组 标 识 符: tgt_acceleration_W
// 信 号 组 名    称: 目标加速度_西向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} TGT_ACCELERATION_W_TYPE_DEF;

// 信 号 组 标 识 符: tgt_acceleration_U
// 信 号 组 名    称: 目标加速度_天向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} TGT_ACCELERATION_U_TYPE_DEF;

// 信 号 组 标 识 符: tgt_acceleration_N
// 信 号 组 名    称: 目标加速度_北向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_acceleration
    // 名  称:_加速度
    // 说  明:
    // 单  位:m/s2
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _acceleration;

} TGT_ACCELERATION_N_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_paras
// 信 号 组 名    称: 目标速度参数
// 信 号 组 字    数: 10
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_closing_velocity
    // 名  称:目标接近速度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_CLOSING_VELOCITY_TYPE_DEF tgt_closing_velocity;

    // 标识符:tgt_V_X_CGCS2000
    // 名  称:目标速度_X_CGCS2000
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_V_X_CGCS2000_TYPE_DEF tgt_V_X_CGCS2000;

    // 标识符:tgt_V_Y_CGCS2000
    // 名  称:目标速度_Y_CGCS2000
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_V_Y_CGCS2000_TYPE_DEF tgt_V_Y_CGCS2000;

    // 标识符:tgt_V_Z_CGCS2000
    // 名  称:目标速度_Z_CGCS2000
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_V_Z_CGCS2000_TYPE_DEF tgt_V_Z_CGCS2000;

    // 标识符:tgt_V_N
    // 名  称:目标速度_北向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_V_N_TYPE_DEF tgt_V_N;

    // 标识符:tgt_V_W
    // 名  称:目标速度_西向
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_V_W_TYPE_DEF tgt_V_W;

    // 标识符:tgt_V_U
    // 名  称:目标速度_天向
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_V_U_TYPE_DEF tgt_V_U;

    // 标识符:tgt_acceleration_N
    // 名  称:目标加速度_北向
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_ACCELERATION_N_TYPE_DEF tgt_acceleration_N;

    // 标识符:tgt_acceleration_U
    // 名  称:目标加速度_天向
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_ACCELERATION_U_TYPE_DEF tgt_acceleration_U;

    // 标识符:tgt_acceleration_W
    // 名  称:目标加速度_西向
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    TGT_ACCELERATION_W_TYPE_DEF tgt_acceleration_W;

} TGT_VELOCITY_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_horizontal_range
// 信 号 组 名    称: 目标水平距离
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_HORIZONTAL_RANGE_TYPE_DEF;

// 信 号 组 标 识 符: tgt_range_paras
// 信 号 组 名    称: 目标距离参数
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_slant_distance
    // 名  称:目标斜距
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_SLANT_DISTANCE_TYPE_DEF tgt_slant_distance;

    // 标识符:tgt_horizontal_range
    // 名  称:目标水平距离
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_HORIZONTAL_RANGE_TYPE_DEF tgt_horizontal_range;

    // 标识符:tgt_R_N
    // 名  称:目标距离_北向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_R_N_TYPE_DEF tgt_R_N;

    // 标识符:tgt_R_W
    // 名  称:目标距离_西向
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_R_W_TYPE_DEF tgt_R_W;

    // 标识符:tgt_R_U
    // 名  称:目标距离_天向
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_R_U_TYPE_DEF tgt_R_U;

} TGT_RANGE_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_pos
// 信 号 组 名    称: 目标位置
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_longitude
    // 名  称:目标经度
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_LONGITUDE_TYPE_DEF tgt_longitude;

    // 标识符:tgt_latitude
    // 名  称:目标纬度
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_LATITUDE_TYPE_DEF tgt_latitude;

    // 标识符:tgt_altitude
    // 名  称:目标高度
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_ALTITUDE_TYPE_DEF tgt_altitude;

} TGT_POS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_heading
// 信 号 组 名    称: 目标航向
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_HEADING_TYPE_DEF;

// 信 号 组 标 识 符: tgt_aspect
// 信 号 组 名    称: 目标进入角
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_ASPECT_TYPE_DEF;

// 信 号 组 标 识 符: tgt_kenimatics_paras
// 信 号 组 名    称: 目标运动参数
// 信 号 组 字    数: 25
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_azimuth
    // 名  称:目标方位_机体系
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_AZIMUTH_TYPE_DEF tgt_azimuth;

    // 标识符:tgt_elevation
    // 名  称:目标俯仰_机体系
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_ELEVATION_TYPE_DEF tgt_elevation;

    // 标识符:tgt_heading
    // 名  称:目标航向
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_HEADING_TYPE_DEF tgt_heading;

    // 标识符:tgt_aspect
    // 名  称:目标进入角
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TGT_ASPECT_TYPE_DEF tgt_aspect;

    // 标识符:tgt_range_paras
    // 名  称:目标距离参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_RANGE_PARAS_TYPE_DEF tgt_range_paras;

    // 标识符:tgt_velocity_paras
    // 名  称:目标速度参数
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    TGT_VELOCITY_PARAS_TYPE_DEF tgt_velocity_paras;

    // 标识符:tgt_pos
    // 名  称:目标位置
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    TGT_POS_TYPE_DEF tgt_pos;

    // 标识符:tgtset_tgt_real_pos
    // 名  称:人工装订下的目标真实位置
    // 说  明:
    // 单  位:
    // 起始字:22
    // 起始位:0
    TGTSET_TGT_REAL_POS_TYPE_DEF tgtset_tgt_real_pos;

} TGT_KENIMATICS_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: tgt_velocity_error
// 信 号 组 名    称: 目标速度误差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_velocity
    // 名  称:_速度
    // 说  明:用于速度相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.0001m/s，可表示范围从+/-0.1mm/s到约+/-40万km/h。
    // 单  位:m/s
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    INT32 _velocity;

} TGT_VELOCITY_ERROR_TYPE_DEF;

// 信 号 组 标 识 符: tgt_distance_error
// 信 号 组 名    称: 目标距离误差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_distance
    // 名  称:_距离
    // 说  明:单位：米，精度0.01米
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _distance;

} TGT_DISTANCE_ERROR_TYPE_DEF;

// 信 号 组 标 识 符: tgt_angle_error
// 信 号 组 名    称: 目标角度误差
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_angle_mrad
    // 名  称:_角度_毫弧度
    // 说  明:用于角度相关的信号表示。
    //        表示精度0.001mrad，表示范围可达+/-1000rad
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:0
    // 起始位:0
    INT32 _angle_mrad;

} TGT_ANGLE_ERROR_TYPE_DEF;

// 信 号 组 标 识 符: tgt_error_info
// 信 号 组 名    称: 目标误差信息
// 信 号 组 字    数: 3
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_distance_error
    // 名  称:目标距离误差
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    TGT_DISTANCE_ERROR_TYPE_DEF tgt_distance_error;

    // 标识符:tgt_velocity_error
    // 名  称:目标速度误差
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    TGT_VELOCITY_ERROR_TYPE_DEF tgt_velocity_error;

    // 标识符:tgt_angle_error
    // 名  称:目标角度误差
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    TGT_ANGLE_ERROR_TYPE_DEF tgt_angle_error;

} TGT_ERROR_INFO_TYPE_DEF;

// 信 号 组 标 识 符: tgt_altitude_dis
// 信 号 组 名    称: 目标显示高度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:0
    // 起始位:0
    INT32 _altitude;

} TGT_ALTITUDE_DIS_TYPE_DEF;

// 信 号 组 标 识 符: Benchmark_Sensor_Calibrate_Time
// 信 号 组 名    称: 基准传感器对准时间
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_time
    // 名  称:_时间
    // 说  明:时间信息的时分秒数据:
    //        1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //        2、用于一般计时时间最大值99:59:59(即<100小时)；
    //        3、用于特殊计时时间最大值9999.9小时；
    //        时间有符号是为了计算时方便，主要表示时差。
    // 单  位:ns
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT64 _time;

} BENCHMARK_SENSOR_CALIBRATE_TIME_TYPE_DEF;

// 信 号 组 标 识 符: AA_SL_tgt_paras
// 信 号 组 名    称: 空空射击列表目标参数
// 信 号 组 字    数: 50
// 信 号 组 数组长度: 8
// 信 号 组 说    明:
typedef struct
{
    // 标识符:tgt_dis_ID
    // 名  称:目标显示编号
    // 说  明:融合输出的目标显示编号，用两位表示。
    //        显示使用数字1~9、字母a~z组合表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 tgt_dis_ID;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //        显示使用数字1~9表示。
    //        若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:1
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:fused_layer_show_lable
    // 名  称:融合图层显示标识
    // 说  明:枚举值未全部列出，按bit定义某传感器的贡献与否，若为传感器贡献组合，则其值填为各单传感器的枚举值之和。如雷达+电子战，则值为1+2=3。
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 fused_layer_show_lable : 32;

    // 标识符:tgt_paras_validity
    // 名  称:目标数据有效性
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TGT_PARAS_VALIDITY_TYPE_DEF tgt_paras_validity;

    // 标识符:tgt_precision
    // 名  称:目标数据精度
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    TGT_PRECISION_TYPE_DEF tgt_precision;

    // 标识符:tgt_kenimatics_paras
    // 名  称:目标运动参数
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_KENIMATICS_PARAS_TYPE_DEF tgt_kenimatics_paras;

    // 标识符:threat_level
    // 名  称:目标威胁度
    // 说  明:[0,2]
    //        该信号表示目标威胁程度的归一化值。
    // 单  位:No_Unit
    // LSB  :0.01
    // 起始字:31
    // 起始位:24
    UINT32 threat_level : 8;

    // 标识符:threat_rank
    // 名  称:目标威胁等级
    // 说  明:极低	[0.0,0.2]	不具备空空攻击能力的目标，如：运输机、预警机、轰炸机、侦察机等
    //        低	[0.2,0.4]	具备作战能力的目标，距离较远
    //        中	[0.4,0.6]	具备作战能力，距离较近
    //        高	[0.6,0.9]	目标有能力发动攻击
    //        极高	[0.9,2.0]	目标有攻击能力，且具有较明显的攻击意图
    //        方括号中为威胁度计算值；
    // 单  位:
    // 起始字:31
    // 起始位:16
    UINT32 threat_rank : 8;

    // 标识符:tgt_attribute
    // 名  称:目标属性
    // 说  明:
    // 单  位:
    // 起始字:31
    // 起始位:8
    UINT32 tgt_attribute : 8;

    // 标识符:own_SL_tgt
    // 名  称:本机射击列表目标序号
    // 说  明:射击列表目标的排序：
    //        NTS目标排名第一，其它目标顺序排序。
    //        若值为0，表示该目标不是射击列表目标。
    // 单  位:
    // 起始字:31
    // 起始位:0
    UINT32 own_SL_tgt : 8;

    // 标识符:attack_state
    // 名  称:目标攻击态势
    // 说  明:前向：迎头
    //        后向：尾后
    // 单  位:
    // 起始字:32
    // 起始位:24
    UINT32 attack_state : 8;

    // 标识符:target_class
    // 名  称:目标类型
    // 说  明:注：ALL 普查，仅图像情报使用
    // 单  位:
    // 起始字:32
    // 起始位:16
    UINT32 target_class : 8;

    // 标识符:confidence_tgt_type
    // 名  称:置信度_目标类型
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:32
    // 起始位:0
    UINT32 confidence_tgt_type : 16;

    // 标识符:confidence_tgt_size
    // 名  称:置信度_目标尺寸
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:33
    // 起始位:16
    UINT32 confidence_tgt_size : 16;

    // 标识符:troop_tgt_property
    // 名  称:群目标特征
    // 说  明:
    // 单  位:
    // 起始字:33
    // 起始位:8
    UINT32 troop_tgt_property : 8;

    // 标识符:target_track_state
    // 名  称:目标跟踪状态
    // 说  明:20230522:更改11-STT_DOT描述为“点迹截获进SAM”。
    //        20230608：新增“12-TRACK_SHOOTLIST-火控级跟踪”。
    // 单  位:
    // 起始字:33
    // 起始位:0
    UINT32 target_track_state : 8;

    // 标识符:rcs_confidence
    // 名  称:置信度_目标RCS
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    //        表示发送的目标RCS值可信度。最大100%
    // 单  位:%
    // LSB  :0.01
    // 起始字:34
    // 起始位:16
    UINT32 rcs_confidence : 16;

    UINT32 spare1 : 4;  // 保留字段
    // 标识符:target_rcs_type_2GCS
    // 名  称:目标RCS类型_宽带下传
    // 说  明:目标RCS范围>19平米为大目标
    //        目标RCS范围为[1,19]平米为中目标
    //        目标RCS范围为[0.1,1)平米为小目标
    //        目标RCS范围为(0,0.1)平米为隐身目标
    // 单  位:
    // 起始字:34
    // 起始位:8
    UINT32 target_rcs_type_2GCS : 4;

    // 标识符:target_physics_size
    // 名  称:目标物理尺寸
    // 说  明:目标机身长度范围大于25m为大尺寸目标
    //        目标机身长度范围为(10,25]m为中尺寸目标
    //        目标机身长度范围为(3,10]m为小尺寸目标
    //        目标机身长度范围为(0,3]m为超小尺寸目标
    // 单  位:
    // 起始字:34
    // 起始位:0
    UINT32 target_physics_size : 8;

    // 标识符:tgt_RCS
    // 名  称:目标RCS
    // 说  明:用于衡量目标RCS大小。
    //        精度0.0001平方米，可表示+/-约10000km。
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:35
    // 起始位:0
    UINT32 tgt_RCS;

    // 标识符:LAND_STATE
    // 名  称:地形标识
    // 说  明:
    // 单  位:
    // 起始字:36
    // 起始位:24
    UINT32 LAND_STATE : 8;

    // 标识符:above_ground_height_type
    // 名  称:地形相对高度类型
    // 说  明:0：表示地形高度采用DTED来源；
    //        1：表示无线电测相对地形高度；
    //        2：表示采用装订气压高度作为地形高度。
    // 单  位:
    // 起始字:36
    // 起始位:16
    UINT32 above_ground_height_type : 8;

    // 标识符:validity_ground_height
    // 名  称:有效性_地形高度
    // 说  明:
    // 单  位:
    // 起始字:36
    // 起始位:8
    UINT32 validity_ground_height : 8;

    // 标识符:validity_above_ground_height
    // 名  称:有效性_地形相对高度
    // 说  明:
    // 单  位:
    // 起始字:36
    // 起始位:0
    UINT32 validity_above_ground_height : 8;

    // 标识符:above_ground_height
    // 名  称:地形相对高度
    // 说  明:[-500,30000]m
    //        相对地形高度。
    // 单  位:
    // 起始字:37
    // 起始位:0
    ABOVE_GROUND_HEIGHT_TYPE_DEF above_ground_height;

    // 标识符:ground_height
    // 名  称:地形高度
    // 说  明:[-500,10000]m
    //        地形高度。
    // 单  位:
    // 起始字:38
    // 起始位:0
    GROUND_HEIGHT_TYPE_DEF ground_height;

    // 标识符:tgt_stae_altitude
    // 名  称:目标惯性卫星大气高度
    // 说  明:
    // 单  位:
    // 起始字:39
    // 起始位:0
    TGT_STAE_ALTITUDE_TYPE_DEF tgt_stae_altitude;

    // 标识符:burst_tgt_flag
    // 名  称:猝发目标标志
    // 说  明:
    // 单  位:
    // 起始字:40
    // 起始位:24
    UINT32 burst_tgt_flag : 8;

    // 标识符:cpeg_tgt_flag
    // 名  称:CPEG目标状态
    // 说  明:
    // 单  位:
    // 起始字:40
    // 起始位:16
    UINT32 cpeg_tgt_flag : 8;

    // 标识符:guidance_onoff_state
    // 名  称:制导开关状态
    // 说  明:
    // 单  位:
    // 起始字:40
    // 起始位:8
    UINT32 guidance_onoff_state : 8;

    // 标识符:true_virtual_flag
    // 名  称:真实虚拟目标标识
    // 说  明:
    // 单  位:
    // 起始字:40
    // 起始位:0
    UINT32 true_virtual_flag : 8;

    // 标识符:target_jam_state
    // 名  称:目标干扰状态
    // 说  明:表示目标干扰状态。
    // 单  位:
    // 起始字:41
    // 起始位:24
    UINT32 target_jam_state : 8;

    // 标识符:jamed_distance_enable_tgt_flag
    // 名  称:使用雷达受干扰距离目标标志
    // 说  明:
    // 单  位:
    // 起始字:41
    // 起始位:16
    UINT32 jamed_distance_enable_tgt_flag : 8;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:guidance_tgt_flag
    // 名  称:制导目标标志
    // 说  明:
    // 单  位:
    // 起始字:41
    // 起始位:0
    UINT32 guidance_tgt_flag : 8;

    UINT32 spare3 : 8;  // 保留字段
    // 标识符:target_track_unstable_state
    // 名  称:目标跟踪不稳定状态
    // 说  明:跟踪目标上报不稳定情况，快出框架角时上报火控更改下发AOC判断状态
    // 单  位:
    // 起始字:42
    // 起始位:16
    UINT32 target_track_unstable_state : 8;

    // 标识符:validity_tgt_accel
    // 名  称:有效性_目标加速度
    // 说  明:
    // 单  位:
    // 起始字:42
    // 起始位:8
    UINT32 validity_tgt_accel : 8;

    // 标识符:jam_tgt_memory_flag
    // 名  称:干扰源目标外推标志
    // 说  明:
    // 单  位:
    // 起始字:42
    // 起始位:0
    UINT32 jam_tgt_memory_flag : 8;

    // 标识符:tgt_az_covariance
    // 名  称:目标方位方差
    // 说  明:
    // 单  位:
    // 起始字:43
    // 起始位:0
    TGT_AZ_COVARIANCE_TYPE_DEF tgt_az_covariance;

    // 标识符:Benchmark_Sensor_Calibrate_Time
    // 名  称:基准传感器对准时间
    // 说  明:
    // 单  位:
    // 起始字:44
    // 起始位:0
    BENCHMARK_SENSOR_CALIBRATE_TIME_TYPE_DEF Benchmark_Sensor_Calibrate_Time;

    // 标识符:tgt_error_info
    // 名  称:目标误差信息
    // 说  明:
    // 单  位:
    // 起始字:46
    // 起始位:0
    TGT_ERROR_INFO_TYPE_DEF tgt_error_info;

    // 标识符:tgt_altitude_dis
    // 名  称:目标显示高度
    // 说  明:
    // 单  位:
    // 起始字:49
    // 起始位:0
    TGT_ALTITUDE_DIS_TYPE_DEF tgt_altitude_dis;

} AA_SL_TGT_PARAS_TYPE_DEF;

// 信 号 组 标 识 符: RawData_MsSubSys_IRST
// 信 号 组 名    称: RawData_任务子系统_IRST
// 信 号 组 字    数: 96
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    UINT32 subdomain_ID : 32;

    // 标识符:SubSys_SW_VER
    // 名  称:主控软件版本
    // 说  明:子系统主控软件的版本号，格式要求：
    //        0x0ABC表示A.BC版本
    //        如0x0123表示1.23版本
    //        前1位固定为0
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 SubSys_SW_VER;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:subsys_work_state
    // 名  称:工作状态
    // 说  明:子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    //        20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
    //        20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
    //        20250515，增加应急状态，表示ICP处于28V供电的一个工作状态。
    // 单  位:
    // 起始字:2
    // 起始位:8
    UINT32 subsys_work_state : 8;

    // 标识符:subsys_main_mode
    // 名  称:工作模式
    // 说  明:描述系统的工作模式；
    //        初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
    // 单  位:
    // 起始字:2
    // 起始位:0
    UINT32 subsys_main_mode : 8;

    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    // 说  明:表征子系统上电次数
    //        不能上报的功能单元将该信号置0
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 subsys_electrify_amount;

    // 标识符:RawData_DataPlaceholder
    // 名  称:RawData_数据占位
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 RawData_DataPlaceholder[92];

} RAWDATA_MSSUBSYS_IRST_TYPE_DEF;

// 信 号 组 标 识 符: imaging_right_up_longitude
// 信 号 组 名    称: 图像右上角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGING_RIGHT_UP_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_right_up_latitude
// 信 号 组 名    称: 图像右上角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 根据协调单《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGING_RIGHT_UP_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_right_down_longitude
// 信 号 组 名    称: 图像右下角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGING_RIGHT_DOWN_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_right_down_latitude
// 信 号 组 名    称: 图像右下角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 根据协调单《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGING_RIGHT_DOWN_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_left_up_longitude
// 信 号 组 名    称: 图像左上角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGING_LEFT_UP_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_left_up_latitude
// 信 号 组 名    称: 图像左上角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 根据协调单《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGING_LEFT_UP_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_left_down_longitude
// 信 号 组 名    称: 图像左下角经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGING_LEFT_DOWN_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_left_down_latitude
// 信 号 组 名    称: 图像左下角纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明: 根据协调单《3.1.3空面雷达相关优化0910》修改
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGING_LEFT_DOWN_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: A818_RDR_Image_FC0_IS
// 信 号 组 名    称: 光电图像FC0帧注释信息图像参数
// 信 号 组 字    数: 24
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[2];  // 保留字段

    // 标识符:date_day
    // 名  称:日期_日
    // 说  明:注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:8
    UINT8 date_day;

    // 标识符:date_month
    // 名  称:日期_月
    // 说  明:有效范围1-12
    //        注：北斗数据：送不出月和日
    // 单  位:
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 date_month;

    // 标识符:IMG_ID
    // 名  称:图像帧序号
    // 说  明:共用。
    //        光电：图像总序号（可见光/红外分开计数）。
    //        雷达：即图像帧编号（即方位向图像编号），用于拼接及叠加：条带256K（距离）*2K（方位）为1帧分块；聚束为8K*8K为1帧分块，按照逐行从左到右（距离近到远），从下到上（航向方向）。
    //        帧号下电存在前端传感器，上电后按照上次的继续编号，满了从1开始编号（不同架次连续编）。雷达帧号不区分不同模式，连续编号。光电区分可见光和红外分别编。
    //
    // 单  位:
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT32 IMG_ID;

    // 标识符:A818_EO_CycleNo
    // 名  称:光电周期号
    // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 A818_EO_CycleNo;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:A818_LineNo
    // 名  称:条带号
    // 说  明:1～65535，共用。
    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
    //        雷达：与帧序号定义相同，但是每个周期从1开始编号。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 A818_LineNo;

    // 标识符:date_year
    // 名  称:日期_年
    // 说  明:有效范围0000-9999年
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:16
    UINT16 date_year;

    SPARE8 spare3[2];  // 保留字段

    // 标识符:A818_EO_ImageLineNum
    // 名  称:图像行数
    // 说  明:00000~99999，垂直于航向的像素个数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 A818_EO_ImageLineNum;

    // 标识符:A818_EO_ImageColumnNum
    // 名  称:图像列数
    // 说  明:00000~99999，平行于航向的像素个数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT32 A818_EO_ImageColumnNum;

    // 标识符:A818_WideCover
    // 名  称:收容宽度
    // 说  明:单位：米。
    //        对于光电：广域模式和区域成像模式下垂直航向的实际宽度，区域监视模式下为一帧图像的实际宽度。
    //        对于侦察雷达：表示条带的幅宽、或聚束SAR的幅宽
    // 单  位:m
    // LSB  :1
    // 起始字:7
    // 起始位:0
    UINT32 A818_WideCover;

    // 标识符:view_fov_pitch
    // 名  称:视场大小_俯仰
    // 说  明:表示视频在显示器上的视场的视频源的俯仰大小
    // 单  位:
    // 起始字:8
    // 起始位:0
    VIEW_FOV_PITCH_TYPE_DEF view_fov_pitch;

    // 标识符:view_fov_azimuth
    // 名  称:视场大小_方位
    // 说  明:表示视频在显示器上的显示视场的视频源的方位大小
    // 单  位:
    // 起始字:9
    // 起始位:0
    VIEW_FOV_AZIMUTH_TYPE_DEF view_fov_azimuth;

    // 标识符:view_fov_center_elevation
    // 名  称:视场中心_俯仰
    // 说  明:机体系
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:10
    // 起始位:0
    INT32 view_fov_center_elevation;

    // 标识符:view_fov_center_azimuth
    // 名  称:视场中心_方位
    // 说  明:机体系
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:11
    // 起始位:0
    INT32 view_fov_center_azimuth;

    // 标识符:A818_CUR_RESOLUTION
    // 名  称:像元分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置分辨率（计算值，精度与飞机姿态参数精度、相对高度参数精度等相关）
    //        对于雷达表示图像斜距距离向的像元尺寸。
    // 单  位:m
    // LSB  :0.01
    // 起始字:12
    // 起始位:16
    UINT16 A818_CUR_RESOLUTION;

    // 标识符:A818_Beside_tgt_cover
    // 名  称:傍向重叠率
    // 说  明:00~99,百分比,垂直飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:12
    // 起始位:8
    UINT8 A818_Beside_tgt_cover;

    // 标识符:A818_Couse_tgt_cover
    // 名  称:航向重叠率
    // 说  明:00~99,像素百分比,平行飞行方向两帧图像的重叠率
    // 单  位:
    // LSB  :1
    // 起始字:12
    // 起始位:0
    UINT8 A818_Couse_tgt_cover;

    // 标识符:A818_ImageCenterHeight
    // 名  称:图像中心高度
    // 说  明:图像中心对应的地面海拔值（成像区域的海拔平均值）
    // 单  位:m
    // LSB  :1
    // 起始字:13
    // 起始位:16
    INT16 A818_ImageCenterHeight;

    // 标识符:A818_GROUND_RESOLUTION
    // 名  称:地面摄影分辨率
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置地面摄影分辨率。像元投影到地面后的分辨率。精度与飞机姿态参数精度、相对高度参数精度等相关
    // 单  位:m
    // LSB  :0.01
    // 起始字:13
    // 起始位:0
    UINT16 A818_GROUND_RESOLUTION;

    // 标识符:image_center_longitude
    // 名  称:图像中心经度
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    IMAGE_CENTER_LONGITUDE_TYPE_DEF image_center_longitude;

    // 标识符:image_center_latitude
    // 名  称:图像中心纬度
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    IMAGE_CENTER_LATITUDE_TYPE_DEF image_center_latitude;

    // 标识符:imaging_left_up_longitude
    // 名  称:图像左上角经度
    // 说  明:《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:16
    // 起始位:0
    IMAGING_LEFT_UP_LONGITUDE_TYPE_DEF imaging_left_up_longitude;

    // 标识符:imaging_left_up_latitude
    // 名  称:图像左上角纬度
    // 说  明:根据协调单《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:17
    // 起始位:0
    IMAGING_LEFT_UP_LATITUDE_TYPE_DEF imaging_left_up_latitude;

    // 标识符:imaging_left_down_longitude
    // 名  称:图像左下角经度
    // 说  明:《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:18
    // 起始位:0
    IMAGING_LEFT_DOWN_LONGITUDE_TYPE_DEF imaging_left_down_longitude;

    // 标识符:imaging_left_down_latitude
    // 名  称:图像左下角纬度
    // 说  明:根据协调单《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:19
    // 起始位:0
    IMAGING_LEFT_DOWN_LATITUDE_TYPE_DEF imaging_left_down_latitude;

    // 标识符:imaging_right_up_longitude
    // 名  称:图像右上角经度
    // 说  明:《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:20
    // 起始位:0
    IMAGING_RIGHT_UP_LONGITUDE_TYPE_DEF imaging_right_up_longitude;

    // 标识符:imaging_right_up_latitude
    // 名  称:图像右上角纬度
    // 说  明:根据协调单《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:21
    // 起始位:0
    IMAGING_RIGHT_UP_LATITUDE_TYPE_DEF imaging_right_up_latitude;

    // 标识符:imaging_right_down_longitude
    // 名  称:图像右下角经度
    // 说  明:《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:22
    // 起始位:0
    IMAGING_RIGHT_DOWN_LONGITUDE_TYPE_DEF imaging_right_down_longitude;

    // 标识符:imaging_right_down_latitude
    // 名  称:图像右下角纬度
    // 说  明:根据协调单《3.1.3空面雷达相关优化0910》修改
    // 单  位:
    // 起始字:23
    // 起始位:0
    IMAGING_RIGHT_DOWN_LATITUDE_TYPE_DEF imaging_right_down_latitude;

} A818_RDR_IMAGE_FC0_IS_TYPE_DEF;

// 信 号 组 标 识 符: imaging_center_longitude
// 信 号 组 名    称: 成像中心经度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _longitude;

} IMAGING_CENTER_LONGITUDE_TYPE_DEF;

// 信 号 组 标 识 符: imaging_center_latitude
// 信 号 组 名    称: 成像中心纬度
// 信 号 组 字    数: 1
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:_latitude
    // 名  称:_纬度
    // 说  明:[-90,90]度
    //        地理位置纬度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:0
    // 起始位:0
    INT32 _latitude;

} IMAGING_CENTER_LATITUDE_TYPE_DEF;

// 信 号 组 标 识 符: A818_RDR_Image_FC0_CS
// 信 号 组 名    称: 光电图像FC0帧注释信息相机参数
// 信 号 组 字    数: 5
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:A818_EO_FocalLength
    // 名  称:相机焦距
    // 说  明:0~65535，毫米,相机焦距参数，光电独有
    // 单  位:mm
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 A818_EO_FocalLength;

    // 标识符:A818_EO_TakeTimes
    // 名  称:照相次数
    // 说  明:000~999，共用。
    //        光电：每次接收拍照指令或模式变换时+1，对应数据记录时，建立新模式的文件夹
    //        雷达：对SAR雷达，一次飞行过程中开机的序号，每切换一次工作模式，开机次数需递增。
    //
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 A818_EO_TakeTimes;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:A818_EO_ExposureTime
    // 名  称:曝光时间
    // 说  明:000~999，图像曝光时间，分辨率为1微秒，光电独有
    // 单  位:Mic
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT16 A818_EO_ExposureTime;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:A818_EO_ImpotentTag
    // 名  称:重要目标标识
    // 说  明:0-不重要目标，1-重要目标，2-未知，使用中不做要求
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT8 A818_EO_ImpotentTag;

    // 标识符:imaging_center_longitude
    // 名  称:成像中心经度
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    IMAGING_CENTER_LONGITUDE_TYPE_DEF imaging_center_longitude;

    // 标识符:imaging_center_latitude
    // 名  称:成像中心纬度
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    IMAGING_CENTER_LATITUDE_TYPE_DEF imaging_center_latitude;

} A818_RDR_IMAGE_FC0_CS_TYPE_DEF;

// 信 号 组 标 识 符: A818_EO_Image_FC0_MI
// 信 号 组 名    称: 光电图像FC0帧注释信息任务信息
// 信 号 组 字    数: 4
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    // 标识符:A818_MissionCode
    // 名  称:任务代号
    // 说  明:0000～9999，任务规划系统规划任务时确定。取自任务规划加载，用于区分哪个架次、哪次任务。后续数据分类整理可能用到，机上图像处理不用。该信号雷达和光电共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:16
    UINT16 A818_MissionCode;

    // 标识符:A818_EO_SignHead
    // 名  称:光电标识头
    // 说  明:0x7E7E，16进制，作为注释信息包头
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT16 A818_EO_SignHead;

    // 标识符:A818_AC_No
    // 名  称:飞机号
    // 说  明:0000～9999，飞机编号，缺省值00，与测控联网后从测控链获取。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:16
    UINT16 A818_AC_No;

    // 标识符:A818_AC_BatchNo
    // 名  称:飞机批号
    // 说  明:保留，默认取00。该信号非必须，共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:8
    UINT8 A818_AC_BatchNo;

    // 标识符:A818_AC_TYPE
    // 名  称:飞行器类型
    // 说  明:暂定缺省置0X4B(侦察型)，预警型待定。与测控联网后从测控取。
    //        该信号雷达与光电共用。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 A818_AC_TYPE;

    // 标识符:A818_MissionInfo
    // 名  称:任务信息
    // 说  明:Bit00-01: 传输方式
    //        0=地面回读
    //        1=实时传输
    //        2=选择传输
    //        载荷默认填0, AIMP根据实时传输模式填1或2
    //        Bit02-03: 载荷类型
    //        0=NA
    //        1=综合光电可见光，
    //        2=综合光电红外
    //        Bit03-05:载荷厂家
    //        0=NA
    //        1=613光电
    //        2=长光所光电
    //        3=长春通视光电
    //        Bit06-07:载图像位深
    //        0=NA
    //        1=8位
    //        2=12位
    //        3=16位
    //        Bit08:正/反扫标记
    //        0=正扫，1=反扫，顺航向从左到右为正扫，反之为反扫。
    //        Bit09:红外正负像标志
    //        0=白热，1=黑热
    //        Bit09~Bit11:定位精度
    //        0=NA
    //        1=精
    //        2=粗
    //        3=极粗
    //        4=无效
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:2
    // 起始位:0
    UINT32 A818_MissionInfo;

    SPARE8 spare1;  // 保留字段

    // 标识符:A818_CameraWorkMode
    // 名  称:相机工作模式
    // 说  明:0 H=N/A；
    //        1H=广域成像；
    //        2H=区域成像4x4km；
    //        3H=区域成像10x10km；
    //        4H=区域成像20x20km；
    //        5H=区域监视
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT8 A818_CameraWorkMode;

    // 标识符:A818_ImageCompressionRatio
    // 名  称:图像压缩比
    // 说  明:000～9999，载荷默认填0，由AIMP下传时填写
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 A818_ImageCompressionRatio;

} A818_EO_IMAGE_FC0_MI_TYPE_DEF;

// 信 号 组 标 识 符: HOTAS_T2_DEADBAND
// 信 号 组 名    称: HOTAS_T2_死区
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:HOTAS_T2_DEADBAND_X
    // 名  称:HOTAS_T2_死区_X方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    UINT8 HOTAS_T2_DEADBAND_X;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:HOTAS_T2_DEADBAND_Y
    // 名  称:HOTAS_T2_死区_Y方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    UINT8 HOTAS_T2_DEADBAND_Y;

} HOTAS_T2_DEADBAND_TYPE_DEF;

// 信 号 组 标 识 符: HOTAS_T2_Calibration_Para_F
// 信 号 组 名    称: HOTAS_T2_校准参数_前舱
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:HOTAS_T2_OFFSET_X
    // 名  称:HOTAS_T2_零位偏移_X方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT8 HOTAS_T2_OFFSET_X;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:HOTAS_T2_OFFSET_Y
    // 名  称:HOTAS_T2_零位偏移_Y方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    INT8 HOTAS_T2_OFFSET_Y;

} HOTAS_T2_CALIBRATION_PARA_F_TYPE_DEF;

// 信 号 组 标 识 符: HOTAS_T2_Calibration_Para_B
// 信 号 组 名    称: HOTAS_T2_校准参数_后舱
// 信 号 组 字    数: 2
// 信 号 组 数组长度: 1
// 信 号 组 说    明:
typedef struct
{
    SPARE8 spare1[3];  // 保留字段

    // 标识符:HOTAS_T2_OFFSET_X
    // 名  称:HOTAS_T2_零位偏移_X方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    INT8 HOTAS_T2_OFFSET_X;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:HOTAS_T2_OFFSET_Y
    // 名  称:HOTAS_T2_零位偏移_Y方向
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:1
    // 起始位:0
    INT8 HOTAS_T2_OFFSET_Y;

} HOTAS_T2_CALIBRATION_PARA_B_TYPE_DEF;

////////////////////////////////////////////分时信号结构定义///////////////////////////////////////////

////////////////////////////////////////////////主题结构定义///////////////////////////////////////

// 主题 标 识 符: A818_EO_Image
// 主题 名    称: 光电原始图像
// 主题 编    码: 4359
// 主题 类    型: 流数据包
// 主题 格式类型: 应用主题
// 主题 长    度: 33
// 主题 说    明:
typedef struct
{
    // 标识符:A818_EO_Image_FC0_MI
    // 名  称:光电图像FC0帧注释信息任务信息
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    A818_EO_IMAGE_FC0_MI_TYPE_DEF A818_EO_Image_FC0_MI;

    // 标识符:A818_RDR_Image_FC0_IS
    // 名  称:光电图像FC0帧注释信息图像参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    A818_RDR_IMAGE_FC0_IS_TYPE_DEF A818_RDR_Image_FC0_IS;

    // 标识符:A818_RDR_Image_FC0_CS
    // 名  称:光电图像FC0帧注释信息相机参数
    // 说  明:
    // 单  位:
    // 起始字:28
    // 起始位:0
    A818_RDR_IMAGE_FC0_CS_TYPE_DEF A818_RDR_Image_FC0_CS;

} A818_EO_IMAGE;

// 主题 标 识 符: AA_SL_sensor_correlation
// 主题 名    称: 空空射击列表目标传感器关联矩阵
// 主题 编    码: 1245
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 500
// 主题 说    明: 这里的目标总数表示射击列表中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 tgt_total_number;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:SL_correlate_matrix
    // 名  称:射击列表目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    SL_CORRELATE_MATRIX_TYPE_DEF SL_correlate_matrix[5];

    SPARE8 spare2[2];  // 保留字段

    // 标识符:I_team_no_self
    // 名  称:本机I链编队号
    // 说  明:编队号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:411
    // 起始位:0
    UINT16 I_team_no_self;

    SPARE32 spare3[88];  // 保留字段

} AA_SL_SENSOR_CORRELATION;

// 主题 标 识 符: AA_SL_target
// 主题 名    称: 空空射击列表目标
// 主题 编    码: 1234
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 406
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 tgt_total_number;

    // 标识符:AA_SL_tgt_paras
    // 名  称:空空射击列表目标参数
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    AA_SL_TGT_PARAS_TYPE_DEF AA_SL_tgt_paras[8];

} AA_SL_TARGET;

// 主题 标 识 符: AA_TOI_list
// 主题 名    称: 空空关注目标列表
// 主题 编    码: 2907
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 300
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 tgt_total_number;

    // 标识符:AA_TOI_list_paras
    // 名  称:关注目标列表参数
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    AA_TOI_LIST_PARAS_TYPE_DEF AA_TOI_list_paras[4];

    SPARE32 spare2[274];  // 保留字段

} AA_TOI_LIST;

// 主题 标 识 符: AA_track_correlate_matrix1
// 主题 名    称: 空空目标关联矩阵1
// 主题 编    码: 3188
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX1;

// 主题 标 识 符: AA_track_correlate_matrix10
// 主题 名    称: 空空目标关联矩阵10
// 主题 编    码: 3197
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX10;

// 主题 标 识 符: AA_track_correlate_matrix11
// 主题 名    称: 空空目标关联矩阵11
// 主题 编    码: 3560
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX11;

// 主题 标 识 符: AA_track_correlate_matrix12
// 主题 名    称: 空空目标关联矩阵12
// 主题 编    码: 3561
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX12;

// 主题 标 识 符: AA_track_correlate_matrix13
// 主题 名    称: 空空目标关联矩阵13
// 主题 编    码: 3562
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX13;

// 主题 标 识 符: AA_track_correlate_matrix14
// 主题 名    称: 空空目标关联矩阵14
// 主题 编    码: 3563
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX14;

// 主题 标 识 符: AA_track_correlate_matrix15
// 主题 名    称: 空空目标关联矩阵15
// 主题 编    码: 3564
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX15;

// 主题 标 识 符: AA_track_correlate_matrix16
// 主题 名    称: 空空目标关联矩阵16
// 主题 编    码: 3565
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX16;

// 主题 标 识 符: AA_track_correlate_matrix17
// 主题 名    称: 空空目标关联矩阵17
// 主题 编    码: 3566
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX17;

// 主题 标 识 符: AA_track_correlate_matrix18
// 主题 名    称: 空空目标关联矩阵18
// 主题 编    码: 3567
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX18;

// 主题 标 识 符: AA_track_correlate_matrix19
// 主题 名    称: 空空目标关联矩阵19
// 主题 编    码: 3568
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX19;

// 主题 标 识 符: AA_track_correlate_matrix2
// 主题 名    称: 空空目标关联矩阵2
// 主题 编    码: 3189
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX2;

// 主题 标 识 符: AA_track_correlate_matrix20
// 主题 名    称: 空空目标关联矩阵20
// 主题 编    码: 3569
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX20;

// 主题 标 识 符: AA_track_correlate_matrix3
// 主题 名    称: 空空目标关联矩阵3
// 主题 编    码: 3190
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX3;

// 主题 标 识 符: AA_track_correlate_matrix4
// 主题 名    称: 空空目标关联矩阵4
// 主题 编    码: 3191
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX4;

// 主题 标 识 符: AA_track_correlate_matrix5
// 主题 名    称: 空空目标关联矩阵5
// 主题 编    码: 3192
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX5;

// 主题 标 识 符: AA_track_correlate_matrix6
// 主题 名    称: 空空目标关联矩阵6
// 主题 编    码: 3193
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX6;

// 主题 标 识 符: AA_track_correlate_matrix7
// 主题 名    称: 空空目标关联矩阵7
// 主题 编    码: 3194
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX7;

// 主题 标 识 符: AA_track_correlate_matrix8
// 主题 名    称: 空空目标关联矩阵8
// 主题 编    码: 3195
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX8;

// 主题 标 识 符: AA_track_correlate_matrix9
// 主题 名    称: 空空目标关联矩阵9
// 主题 编    码: 3196
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT16 tgt_total_number;

    // 标识符:matrix_update_counter
    // 名  称:矩阵刷新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       初始时从1开始，“整个矩阵”（非单独这个消息）每变化一次时，加1。
    //       表示关联矩阵每一次“整体”刷新。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 matrix_update_counter;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:TGFX_target_correlation
    // 名  称:融合目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGFX_TARGET_CORRELATION_TYPE_DEF TGFX_target_correlation[5];

    SPARE32 spare1[160];  // 保留字段

} AA_TRACK_CORRELATE_MATRIX9;

// 主题 标 识 符: absolute_nav_data_fused
// 主题 名    称: 绝对导航融合飞行参数
// 主题 编    码: 421
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 145
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:ac_flight_vector
    // 名  称:载机飞行矢量数据
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    AC_FLIGHT_VECTOR_TYPE_DEF ac_flight_vector;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_ins
    // 名  称:主惯导来源
    // 说  明:
    // 单  位:
    // 起始字:84
    // 起始位:0
    UINT32 primary_ins : 8;

    // 标识符:satellite_nav_data
    // 名  称:卫星导航数据
    // 说  明:
    // 单  位:
    // 起始字:85
    // 起始位:0
    SATELLITE_NAV_DATA_TYPE_DEF satellite_nav_data;

    // 标识符:air_nav_data
    // 名  称:大气导航数据
    // 说  明:
    // 单  位:
    // 起始字:103
    // 起始位:0
    AIR_NAV_DATA_TYPE_DEF air_nav_data;

    // 标识符:horizontal_position_accuracy
    // 名  称:水平位置精度
    // 说  明:CEP（95%）
    // 单  位:
    // 起始字:127
    // 起始位:0
    HORIZONTAL_POSITION_ACCURACY_TYPE_DEF horizontal_position_accuracy;

    // 标识符:integrity_information
    // 名  称:完好性信息
    // 说  明:
    // 单  位:
    // 起始字:129
    // 起始位:0
    INTEGRITY_INFORMATION_TYPE_DEF integrity_information;

    // 标识符:ac_flight_vector_B
    // 名  称:载机飞行矢量数据B
    // 说  明:
    // 单  位:
    // 起始字:132
    // 起始位:0
    AC_FLIGHT_VECTOR_B_TYPE_DEF ac_flight_vector_B;

    // 标识符:ac_flight_vector_C
    // 名  称:载机飞行矢量数据C
    // 说  明:
    // 单  位:
    // 起始字:137
    // 起始位:0
    AC_FLIGHT_VECTOR_C_TYPE_DEF ac_flight_vector_C;

    SPARE32 spare2[1];  // 保留字段

} ABSOLUTE_NAV_DATA_FUSED;

// 主题 标 识 符: AC_Data_FCS_USIM
// 主题 名    称: 飞机参数_飞控机电参数
// 主题 编    码: 1251
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 64
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:VMS_usimkeyData_ENG
    // 名  称:VMS_机电关键参数_发动机
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    VMS_USIMKEYDATA_ENG_TYPE_DEF VMS_usimkeyData_ENG;

    // 标识符:VMS_usimKeyData_fuel
    // 名  称:VMS_机电关键参数_燃油
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    VMS_USIMKEYDATA_FUEL_TYPE_DEF VMS_usimKeyData_fuel;

    // 标识符:VMS_usimKeyData_elec
    // 名  称:VMS_机电关键参数_供电
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    VMS_USIMKEYDATA_ELEC_TYPE_DEF VMS_usimKeyData_elec;

    // 标识符:VMS_usimKeyData_US
    // 名  称:VMS_机电关键参数_机电综合
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    VMS_USIMKEYDATA_US_TYPE_DEF VMS_usimKeyData_US;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:VMS_control_manage_mode
    // 名  称:飞管系统控制管理模式
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    UINT32 VMS_control_manage_mode : 8;

    // 标识符:VMS_usimkeyData_ENG2
    // 名  称:VMS_机电关键参数_发动机2
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    VMS_USIMKEYDATA_ENG2_TYPE_DEF VMS_usimkeyData_ENG2;

    UINT32 spare3 : 8;  // 保留字段
    // 标识符:VMS1394_AC_Type_ID
    // 名  称:VMS1394_飞机构型
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:8
    UINT32 VMS1394_AC_Type_ID : 16;

    UINT32 spare2 : 4;  // 保留字段
    // 标识符:VMS_AC_ID
    // 名  称:VMS_飞机ID
    // 说  明:0 歼-20飞机01状态01-05架
    //       1 歼-20飞机01状态06架起
    //       2 歼-20飞机02状态，不装航炮
    //       3 歼-20飞机02状态，装航炮
    //       4 歼-20双座机，配装涡扇-10C
    //       5 歼-20双座机，配装涡扇-15
    //       6 歼-20A飞机，配装涡扇-10C
    //       7 歼-20A飞机，配装涡扇-15
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT32 VMS_AC_ID : 4;

    // 标识符:VMS_fcsKeyData
    // 名  称:VMS_飞控关键参数
    // 说  明:
    // 单  位:
    // 起始字:20
    // 起始位:0
    VMS_FCSKEYDATA_TYPE_DEF VMS_fcsKeyData;

    // 标识符:VMS1394_fly_status
    // 名  称:VMS1394_飞行阶段
    // 说  明:
    // 单  位:
    // 起始字:30
    // 起始位:16
    UINT32 VMS1394_fly_status : 16;

    // 标识符:VMS1394_YKZ_AC_NUM
    // 名  称:VMS1394_遥控帧_飞行器编号
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:30
    // 起始位:8
    UINT32 VMS1394_YKZ_AC_NUM : 8;

    // 标识符:VMS1394_YKZ_AC_TYPE
    // 名  称:VMS1394_遥控帧_飞行器类型
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:30
    // 起始位:0
    UINT32 VMS1394_YKZ_AC_TYPE : 8;

    // 标识符:VMS1394_tag_IFDL_PowerLimit
    // 名  称:VMS1394_机间链天线限功率标志
    // 说  明:
    // 单  位:
    // 起始字:31
    // 起始位:24
    UINT32 VMS1394_tag_IFDL_PowerLimit : 8;

    // 标识符:VMS1394_tag_LAIU_PowerLimit
    // 名  称:VMS1394_L波段天线限功率标志
    // 说  明:
    // 单  位:
    // 起始字:31
    // 起始位:16
    UINT32 VMS1394_tag_LAIU_PowerLimit : 8;

    // 标识符:VMS1394_validity_IFDL_PowerLimit
    // 名  称:VMS1394_有效性_机间链天线限功率
    // 说  明:
    // 单  位:
    // 起始字:31
    // 起始位:8
    UINT32 VMS1394_validity_IFDL_PowerLimit : 8;

    // 标识符:VMS1394_validity_LAIU_PowerLimit
    // 名  称:VMS1394_有效性_L波段天线限功率
    // 说  明:
    // 单  位:
    // 起始字:31
    // 起始位:0
    UINT32 VMS1394_validity_LAIU_PowerLimit : 8;

    // 标识符:VMS_FcsCcs_EM_state
    // 名  称:VMS_飞管指控辐射状态
    // 说  明:直接从VMS1394转发的高度表、起降引导、测控链路的辐射状态。
    // 单  位:
    // 起始字:32
    // 起始位:0
    VMS_FCSCCS_EM_STATE_TYPE_DEF VMS_FcsCcs_EM_state;

    SPARE32 spare4[5];  // 保留字段

    // 标识符:VMS_FcsSigColection_AC_transfer
    // 名  称:VMS_飞控信号采集数据_转发
    // 说  明:直接从VMS1394转发的飞控信号采集数据中的重量信息：包括：飞机重量的数值和飞机重量的有效性。
    //       直接从VMS1394转发的飞控信号采集数据中的销密记录信号
    // 单  位:
    // 起始字:38
    // 起始位:0
    VMS_FCSSIGCOLECTION_AC_TRANSFER_TYPE_DEF VMS_FcsSigColection_AC_transfer;

    SPARE32 spare5[24];  // 保留字段

    // 标识符:VMS_apParaDataBlock_Valid
    // 名  称:自动驾驶参数数据包有效性
    // 说  明:该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中自动驾驶高度、航迹保持值参数的总有效性。
    // 单  位:
    // 起始字:63
    // 起始位:24
    UINT32 VMS_apParaDataBlock_Valid : 8;

    // 标识符:VMS_apStateDataBlock_Valid
    // 名  称:自动驾驶状态数据包有效性
    // 说  明:该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中"VMS_自动驾驶状态"参数的总有效性。
    // 单  位:
    // 起始字:63
    // 起始位:16
    UINT32 VMS_apStateDataBlock_Valid : 8;

    // 标识符:VMS_fcskeyDataBlock_Valid
    // 名  称:飞控关键参数数据包有效性
    // 说  明:该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中除"VMS_自动驾驶状态"及自动驾驶高度、航迹保持值参数以外的所有参数的总有效性。
    // 单  位:
    // 起始字:63
    // 起始位:8
    UINT32 VMS_fcskeyDataBlock_Valid : 8;

    // 标识符:VMS_usimkeyDataBlock_Valid
    // 名  称:机电关键参数数据包有效性
    // 说  明:该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_机电关键参数_发动机"、"VMS_机电关键参数_燃油"、"VMS_机电关键参数_供电"、"VMS_机电关键参数_机电综合"中所有参数的总有效性。
    // 单  位:
    // 起始字:63
    // 起始位:0
    UINT32 VMS_usimkeyDataBlock_Valid : 8;

} AC_DATA_FCS_USIM;

// 主题 标 识 符: ARINC615a_LOAD_NORMAL_OMP
// 主题 名    称: ARINC615a_LOAD_NORMAL_OMP
// 主题 编    码: 4016
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 490
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    SPARE32 spare1[487];  // 保留字段

} ARINC615A_LOAD_NORMAL_OMP;

// 主题 标 识 符: ARINC615a_LOAD_STREAM_OMP
// 主题 名    称: ARINC615a_LOAD_STREAM_OMP
// 主题 编    码: 4017
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 490
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    SPARE32 spare1[487];  // 保留字段

} ARINC615A_LOAD_STREAM_OMP;

// 主题 标 识 符: AS_SL_correlate_matrix
// 主题 名    称: 空面射击列表目标关联矩阵
// 主题 编    码: 2944
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 这里的目标总数表示所有包中的目标总数。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT16 tgt_total_number;

    // 标识符:SL_correlate_matrix
    // 名  称:射击列表目标关联矩阵
    // 说  明:目标关联矩阵
    // 单  位:
    // 起始字:4
    // 起始位:0
    SL_CORRELATE_MATRIX_TYPE_DEF SL_correlate_matrix[5];

    SPARE8 spare2[2];  // 保留字段

    // 标识符:I_team_no_self
    // 名  称:本机I链编队号
    // 说  明:编队号
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:409
    // 起始位:0
    UINT16 I_team_no_self;

    SPARE32 spare3[86];  // 保留字段

} AS_SL_CORRELATE_MATRIX;

// 主题 标 识 符: burst_paras
// 主题 名    称: 猝发测距参数
// 主题 编    码: 1970
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 20
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:IR_track_number
    // 名  称:IR目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    //       目标编号范围从1到256
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:16
    UINT16 IR_track_number;

    // 标识符:fused_tgt_ID
    // 名  称:融合目标编号
    // 说  明:融合输出的目标编号。
    //       显示使用数字1~9表示。
    //       若该信号值为0，表示该目标无效。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 fused_tgt_ID;

    // 标识符:tgt_paras_validity
    // 名  称:目标数据有效性
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    TGT_PARAS_VALIDITY_TYPE_DEF tgt_paras_validity;

    // 标识符:tgt_bearing
    // 名  称:目标方位_地理系
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    TGT_BEARING_TYPE_DEF tgt_bearing;

    // 标识符:tgt_pitch
    // 名  称:目标俯仰_地理系
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    TGT_PITCH_TYPE_DEF tgt_pitch;

    // 标识符:tgt_brg_angularvelocity
    // 名  称:目标方位角速度_地理系
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    TGT_BRG_ANGULARVELOCITY_TYPE_DEF tgt_brg_angularvelocity;

    // 标识符:tgt_pitch_angularvelocity
    // 名  称:目标俯仰角速度_地理系
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    TGT_PITCH_ANGULARVELOCITY_TYPE_DEF tgt_pitch_angularvelocity;

    // 标识符:tgt_az_covariance
    // 名  称:目标方位方差
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    TGT_AZ_COVARIANCE_TYPE_DEF tgt_az_covariance;

    // 标识符:tgt_el_covariance
    // 名  称:目标俯仰方差
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    TGT_EL_COVARIANCE_TYPE_DEF tgt_el_covariance;

    // 标识符:tgt_az_rate_covariance
    // 名  称:目标方位角速率方差
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:13
    // 起始位:0
    TGT_AZ_RATE_COVARIANCE_TYPE_DEF tgt_az_rate_covariance;

    // 标识符:tgt_el_rate_covariance
    // 名  称:目标俯仰角速率方差
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:14
    // 起始位:0
    TGT_EL_RATE_COVARIANCE_TYPE_DEF tgt_el_rate_covariance;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:EW_tgt_no
    // 名  称:EW目标编号
    // 说  明:若该传感器未对某个目标形成航迹，则该信号置0。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:15
    // 起始位:0
    UINT16 EW_tgt_no;

    SPARE32 spare2[4];  // 保留字段

} BURST_PARAS;

// 主题 标 识 符: data_load_msg_IRRM
// 主题 名    称: 数据加载通知_IRRM
// 主题 编    码: 3452
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 6
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:loading_type
    // 名  称:加载类型
    // 说  明:描述文件/数据在的场景类型：
    //       1=在任务系统正常模式下进行的战术任务数据加载；
    //       2=在任务系统维护模式下进行的维护配置数据加载；
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 loading_type : 8;

    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 folder_id;

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 file_id;

} DATA_LOAD_MSG_IRRM;

// 主题 标 识 符: DataBaseInfo
// 主题 名    称: 数据库信息
// 主题 编    码: 2092
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 95
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:config_item_count
    // 名  称:配置项数量
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 config_item_count;

    // 标识符:DataBaseCfgInfo
    // 名  称:数据库配置信息
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    DATABASECFGINFO_TYPE_DEF DataBaseCfgInfo[5];

} DATABASEINFO;

// 主题 标 识 符: DCD_act_req_report
// 主题 名    称: DCD_活动请求通告
// 主题 编    码: 1220
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 7
// 主题 说    明: 各子域发送该主题，以确认收到活动请求。活动请求通告是向发出请求的子域通告活动的执行结果，是该活动的终结状态消息。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:req_publisher_ID
    // 名  称:请求发布者ID
    // 说  明:发布活动请求者的ID号。
    // 单  位:
    // 起始字:3
    // 起始位:0
    REQ_PUBLISHER_ID_TYPE_DEF req_publisher_ID;

    // 标识符:activity_number_64
    // 名  称:活动编号_64
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT64 activity_number_64;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:act_refused_reason
    // 名  称:拒绝请求原因
    // 说  明:仅当活动状态等于NACK的时候，该信号有效：
    //       1.无效的参数：活动请求所包含的附加参数无效或不存在。
    //       2.无效的活动：活动请求的类型无效，或者不能被执行。
    //       3.无效的请求方：接收方不能识别发起请求的子域。例如请求子域ID无效。
    //       4.辐射限制：受传感器计划或飞行员控制的影响，传感器不允许辐射，因而不能执行所请求的活动。
    //       5.时间限制：受传感器本身限制，在请求的时间内不能完成所请求的活动；或者因为在请求的时间范围内，该活动不被允许。
    //       6.安全因素：因安全因素不能完成所请求的活动。例如地面不允许辐射，当前状态不允许开舱，不允许激光发射，不允许发射干扰弹等。
    //       7.无法执行：活动执行方因故障、或者非操作状态等不能完成所请求的活动。例如设备处于测试状态，但要求设备进行目标测量等。
    // 单  位:
    // 起始字:6
    // 起始位:8
    UINT32 act_refused_reason : 8;

    // 标识符:activity_state
    // 名  称:活动状态
    // 说  明:NACK：活动未能开始时，需要发送。不论是因为错误的请求，还是请求不能执行，在拒绝请求原因信号中进行详细说明。
    //       CANCELLED：当活动被取消，或者已经开始但被中止。可能是因为系统资源丢失，或者系统进入不能运行该请求的状态。
    //       COMPLETED：活动正常完成，并从活动清单中已清除。
    //       ECHO：表示收到活动请求。
    // 单  位:
    // 起始字:6
    // 起始位:0
    UINT32 activity_state : 8;

} DCD_ACT_REQ_REPORT;

// 主题 标 识 符: file_load_state_report
// 主题 名    称: 文件加载状态报告
// 主题 编    码: 451
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 16
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 folder_id;

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 file_id;

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //       软件版本号包括：
    //           1-2：机型识别码;
    //         3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //            11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //            12：字母“V”
    //       13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //       19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:5
    // 起始位:0
    char_8 ver_number[24];

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:load_fail_reason
    // 名  称:加载失败原因
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    UINT32 load_fail_reason : 8;

    // 标识符:load_state
    // 名  称:加载状态
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    UINT32 load_state : 8;

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:loading_type
    // 名  称:加载类型
    // 说  明:描述文件/数据在的场景类型：
    //       1=在任务系统正常模式下进行的战术任务数据加载；
    //       2=在任务系统维护模式下进行的维护配置数据加载；
    // 单  位:
    // 起始字:12
    // 起始位:0
    UINT32 loading_type : 8;

    // 标识符:Time_Load
    // 名  称:加载时间
    // 说  明:加载软件、数据的日历时间，
    //       格式为：XXXX年XX月XX日  XX时XX分XX秒
    // 单  位:
    // 起始字:13
    // 起始位:0
    TIME_LOAD_TYPE_DEF Time_Load;

} FILE_LOAD_STATE_REPORT;

// 主题 标 识 符: General_Video
// 主题 名    称: 视频流_通用主题
// 主题 编    码: 1038
// 主题 类    型: 视频
// 主题 格式类型: 应用主题
// 主题 长    度: 15
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:video_bult_time
    // 名  称:视频产生时间
    // 说  明:根据系统时间，视频产生时打上的系统时间标签。
    // 单  位:ns
    // LSB  :1
    // 起始字:3
    // 起始位:0
    INT64 video_bult_time;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:video_width
    // 名  称:视频宽度
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 video_width;

    SPARE8 spare2[2];  // 保留字段

    // 标识符:video_height
    // 名  称:视频高度
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT16 video_height;

    // 标识符:view_fov_azimuth
    // 名  称:视场大小_方位
    // 说  明:表示视频在显示器上的显示视场的视频源的方位大小
    // 单  位:
    // 起始字:7
    // 起始位:0
    VIEW_FOV_AZIMUTH_TYPE_DEF view_fov_azimuth;

    // 标识符:view_fov_pitch
    // 名  称:视场大小_俯仰
    // 说  明:表示视频在显示器上的视场的视频源的俯仰大小
    // 单  位:
    // 起始字:8
    // 起始位:0
    VIEW_FOV_PITCH_TYPE_DEF view_fov_pitch;

    // 标识符:view_fov_center_elevation
    // 名  称:视场中心_俯仰
    // 说  明:机体系
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:9
    // 起始位:0
    INT32 view_fov_center_elevation;

    // 标识符:view_fov_center_azimuth
    // 名  称:视场中心_方位
    // 说  明:机体系
    // 单  位:mrad
    // LSB  :0.001
    // 起始字:10
    // 起始位:0
    INT32 view_fov_center_azimuth;

    // 标识符:image_center_x
    // 名  称:图像中心点坐标X
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    IMAGE_CENTER_X_TYPE_DEF image_center_x;

    // 标识符:image_center_y
    // 名  称:图像中心点坐标Y
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    IMAGE_CENTER_Y_TYPE_DEF image_center_y;

    UINT32 spare3 : 24;  // 保留字段
    // 标识符:pixel_format
    // 名  称:像素格式
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 pixel_format : 8;

    UINT32 spare4 : 24;  // 保留字段
    // 标识符:pixel_data_type
    // 名  称:像素数据类型
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    UINT32 pixel_data_type : 8;

} GENERAL_VIDEO;

// 主题 标 识 符: HOTAS_Report_Calibration_para
// 主题 名    称: HOTAS_报告_校准参数
// 主题 编    码: 3403
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 20
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:HOTAS_T2_Calibration_Para_F
    // 名  称:HOTAS_T2_校准参数_前舱
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    HOTAS_T2_CALIBRATION_PARA_F_TYPE_DEF HOTAS_T2_Calibration_Para_F;

    // 标识符:HOTAS_T2_Calibration_Para_B
    // 名  称:HOTAS_T2_校准参数_后舱
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    HOTAS_T2_CALIBRATION_PARA_B_TYPE_DEF HOTAS_T2_Calibration_Para_B;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:TDC_Rate_Control_F
    // 名  称:TDC移动速率控制_前舱
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    UINT32 TDC_Rate_Control_F : 8;

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:TDC_Rate_Control_B
    // 名  称:TDC移动速率控制_后舱
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    UINT32 TDC_Rate_Control_B : 8;

    // 标识符:HOTAS_T2_DEADBAND
    // 名  称:HOTAS_T2_死区
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    HOTAS_T2_DEADBAND_TYPE_DEF HOTAS_T2_DEADBAND;

    UINT32 spare3 : 24;  // 保留字段
    // 标识符:Conflict_TDC_Control
    // 名  称:冲突控制权_TDC
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    UINT32 Conflict_TDC_Control : 8;

    UINT32 spare4 : 24;  // 保留字段
    // 标识符:RDR_AA_Control
    // 名  称:雷达_空空权限
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    UINT32 RDR_AA_Control : 8;

    UINT32 spare5 : 24;  // 保留字段
    // 标识符:RDR_AS_Control
    // 名  称:雷达_空面权限
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 RDR_AS_Control : 8;

    UINT32 spare6 : 24;  // 保留字段
    // 标识符:SYN_MODE
    // 名  称:前后舱同步/异步模式
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    UINT32 SYN_MODE : 8;

    SPARE32 spare7[5];  // 保留字段

} HOTAS_REPORT_CALIBRATION_PARA;

// 主题 标 识 符: HW_config_info_report
// 主题 名    称: 硬件配置信息报告
// 主题 编    码: 391
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 500
// 主题 说    明: 本主题包括了子系统的硬件配置信息。该主题提供了必要的信息用于校验软件（OFP和MDF）和硬件的匹配性。该主题也提供了一种记录硬件配置数据的机制。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:config_item_count
    // 名  称:配置项数量
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 config_item_count;

    // 标识符:HW_config_info
    // 名  称:硬件配置信息
    // 说  明:硬件配置信息应包括每个设备或模块的详细配置信息，包括设备或模块的LCN编码(用于后勤保障和定货等)、名称、序列号、累计工作时间、硬件的版本、以及硬件的描述信息。
    // 单  位:
    // 起始字:5
    // 起始位:0
    HW_CONFIG_INFO_TYPE_DEF HW_config_info[6];

    SPARE32 spare2[237];  // 保留字段

} HW_CONFIG_INFO_REPORT;

// 主题 标 识 符: ID_data_transmit_state
// 主题 名    称: 情报数据传输状态
// 主题 编    码: 4526
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 10
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:ID_data_trans_flag
    // 名  称:情报数据传输标识
    // 说  明:按照顺序，第一维代表通道1，第二维代表通道2，以此类推。如果只存在一个通道，则填第一维即可。
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT8 ID_data_trans_flag[3];

    SPARE32 spare2[6];  // 保留字段

} ID_DATA_TRANSMIT_STATE;

// 主题 标 识 符: INS1_nav_data
// 主题 名    称: INS1导航数据
// 主题 编    码: 393
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 228
// 主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//                其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//                卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                每一类数据时标信号之后的数据为其对应的该类数据。且惯导1转发飞管A、C通道大气数据。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:hybrid_nav_data_A
    // 名  称:组合导航数据A
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    HYBRID_NAV_DATA_A_TYPE_DEF hybrid_nav_data_A;

    // 标识符:hybrid_nav_data_B
    // 名  称:组合导航数据B
    // 说  明:
    // 单  位:
    // 起始字:73
    // 起始位:0
    HYBRID_NAV_DATA_B_TYPE_DEF hybrid_nav_data_B;

    // 标识符:pure_inertial_nav_data_A
    // 名  称:纯惯导航数据A
    // 说  明:
    // 单  位:
    // 起始字:95
    // 起始位:0
    PURE_INERTIAL_NAV_DATA_A_TYPE_DEF pure_inertial_nav_data_A;

    // 标识符:pure_inertia_nav_data_B
    // 名  称:纯惯导航数据B
    // 说  明:
    // 单  位:
    // 起始字:152
    // 起始位:0
    PURE_INERTIA_NAV_DATA_B_TYPE_DEF pure_inertia_nav_data_B;

    // 标识符:satellite_nav_data
    // 名  称:卫星导航数据
    // 说  明:
    // 单  位:
    // 起始字:158
    // 起始位:0
    SATELLITE_NAV_DATA_TYPE_DEF satellite_nav_data;

    // 标识符:air_nav_data_A
    // 名  称:大气导航数据_A
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:176
    // 起始位:0
    AIR_NAV_DATA_A_TYPE_DEF air_nav_data_A;

    // 标识符:air_nav_data_C
    // 名  称:大气导航数据_C
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:202
    // 起始位:0
    AIR_NAV_DATA_C_TYPE_DEF air_nav_data_C;

} INS1_NAV_DATA;

// 主题 标 识 符: INS1_NAV_data_5ms
// 主题 名    称: INS1导航数据_5ms
// 主题 编    码: 2115
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 48
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:data_generated_time1
    // 名  称:数据生成时间1
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:6
    // 起始位:0
    DATA_GENERATED_TIME1_TYPE_DEF data_generated_time1;

    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_pitch_rate;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    // 标识符:validity_roll_accel
    // 名  称:有效性_横滚角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:24
    BOOL_8 validity_roll_accel;

    // 标识符:validity_pitch_accel
    // 名  称:有效性_俯仰角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:16
    BOOL_8 validity_pitch_accel;

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_roll_rate;

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:24
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:16
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:8
    BOOL_8 validity_vel_north;

    // 标识符:validity_heading_accel
    // 名  称:有效性_航向角加速度
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    BOOL_8 validity_heading_accel;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:24
    BOOL_8 validity_inertial_AOA;

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    BOOL_8 validity_accel_north;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:24
    BOOL_8 validity_climbing_angle;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:16
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:8
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    BOOL_8 validity_ground_speed;

    // 标识符:validity_baro_pressure_inertial_alt
    // 名  称:有效性_惯性气压参考高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:16
    BOOL_8 validity_baro_pressure_inertial_alt;

    // 标识符:validity_pressure_inertial_alt
    // 名  称:有效性_惯性气压高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    BOOL_8 validity_pressure_inertial_alt;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    BOOL_8 validity_position;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //       仰角为正
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //       右倾为正
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_pitch_accel
    // 名  称:载机俯仰角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_PITCH_ACCEL_TYPE_DEF ac_pitch_accel;

    // 标识符:ac_roll_accel
    // 名  称:载机横滚角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:23
    // 起始位:0
    AC_ROLL_ACCEL_TYPE_DEF ac_roll_accel;

    // 标识符:ac_heading_accel
    // 名  称:载机航向角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:24
    // 起始位:0
    AC_HEADING_ACCEL_TYPE_DEF ac_heading_accel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:25
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:28
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //       速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:31
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //       速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:32
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //       速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:34
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //       爬升为正
    // 单  位:
    // 起始字:35
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //       (-180,180]deg
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:AC_pressure_inertial_alt
    // 名  称:载机惯性气压高度
    // 说  明:[-500,30000]m
    //       INS阻尼后的气压高度
    // 单  位:
    // 起始字:38
    // 起始位:0
    AC_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_pressure_inertial_alt;

    // 标识符:AC_baro_pressure_inertial_alt
    // 名  称:载机惯性气压参考高度
    // 说  明:[-5500,30000]m
    //       =惯性气压高度－场压装订高度
    // 单  位:
    // 起始字:39
    // 起始位:0
    AC_BARO_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_baro_pressure_inertial_alt;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:40
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    SPARE32 spare3[7];  // 保留字段

} INS1_NAV_DATA_5MS;

// 主题 标 识 符: INS1_operational_paras
// 主题 名    称: INS1工作参数报告
// 主题 编    码: 388
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 25
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:INS_sub_mode_state
    // 名  称:惯导当前子模式
    // 说  明:惯导向任务系统上报当前工作模式；
    //       目前无6-传递对准模式；
    //       增加7-对准失败模式；
    //       初始化上报0；
    //       其余按当前工作模式上报；
    // 单  位:
    // 起始字:4
    // 起始位:24
    UINT32 INS_sub_mode_state : 8;

    // 标识符:INS_sub_mode_req
    // 名  称:惯导子模式请求
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 INS_sub_mode_req : 8;

    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 primary_secondary : 8;

    // 标识符:WOW_main
    // 名  称:轮载状态_主
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 WOW_main : 8;

    // 标识符:SAT_select_state
    // 名  称:惯导当前选择卫星
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    UINT32 SAT_select_state : 8;

    // 标识符:INS_SAT_type_req
    // 名  称:惯导卫星选择请求
    // 说  明:自动（优先级：BD军、BD民、GPS、内置、转发）
    //       此条请求本来为任务系统向惯导发活动请求后，惯导回报相关请求，现阶段，惯导不响应任务系统的命令（以1394为主），目前按惯导当前工作状态填值；
    //       报送状态时：
    //       如果VMC的1394命令中，"惯导航强选指令"为自主，则上报1-AUTO 自动；
    // 单  位:
    // 起始字:5
    // 起始位:16
    UINT32 INS_SAT_type_req : 8;

    // 标识符:INS_operation_mode_state
    // 名  称:惯导当前工作方式
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    UINT32 INS_operation_mode_state : 8;

    // 标识符:INS_operation_mode_req
    // 名  称:惯导工作方式请求
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 INS_operation_mode_req : 8;

    // 标识符:align_done_state
    // 名  称:对准完成状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:24
    UINT32 align_done_state : 8;

    // 标识符:enhanced_align_state
    // 名  称:增强对准状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    UINT32 enhanced_align_state : 8;

    // 标识符:satellite_use_state
    // 名  称:卫星使用状态
    // 说  明:此信号用于表征卫星的使用状态。
    // 单  位:
    // 起始字:6
    // 起始位:8
    UINT32 satellite_use_state : 8;

    // 标识符:dipper_operational_mod
    // 名  称:北斗工作模式
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    UINT32 dipper_operational_mod : 8;

    // 标识符:INS_align_param
    // 名  称:惯导对准参数信息
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    INS_ALIGN_PARAM_TYPE_DEF INS_align_param;

    // 标识符:primary_secondary_recommend_type
    // 名  称:主备推荐方式
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    UINT32 primary_secondary_recommend_type : 8;

    // 标识符:num_of_satellite
    // 名  称:定位卫星数目
    // 说  明:从卫星报文的GGA语句中解析得到
    // 单  位:
    // LSB  :1
    // 起始字:13
    // 起始位:16
    UINT32 num_of_satellite : 8;

    // 标识符:ADS_data_channel_state
    // 名  称:大气数据通道选择状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    UINT32 ADS_data_channel_state : 8;

    // 标识符:GNSS_inertial_ADS_alt_state
    // 名  称:惯性卫星大气高度通道组合状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 GNSS_inertial_ADS_alt_state : 8;

    // 标识符:IC_invalid_state
    // 名  称:IC失效状态
    // 说  明:用于表征卫星军码IC的失效状态。其中：
    //       “正常有效”指IC失效的日期与当前的日期差大于8周；
    //       “邻近失效”指IC失效的日期与当前的日期差在8周内；
    //       “失效”指IC失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:24
    UINT32 IC_invalid_state : 8;

    // 标识符:PRM_invalid_state
    // 名  称:PRM失效状态
    // 说  明:用于表征卫星军码PRM的失效状态。其中：
    //       “正常有效”指PRM失效的日期与当前的日期差大于8周；
    //       “邻近失效”指PRM失效的日期与当前的日期差在8周内；
    //       “失效”指PRM失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:16
    UINT32 PRM_invalid_state : 8;

    // 标识符:num_of_satellite_bd_JUN
    // 名  称:北斗卫星数目_军码
    // 说  明:表示当前可用的北斗卫星数目（军码）。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:8
    UINT32 num_of_satellite_bd_JUN : 8;

    // 标识符:num_of_satellite_gps
    // 名  称:GPS卫星数目
    // 说  明:表示当前可用的GPS卫星数目。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:0
    UINT32 num_of_satellite_gps : 8;

    // 标识符:PRM_invalid_time
    // 名  称:PRM失效时间
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    PRM_INVALID_TIME_TYPE_DEF PRM_invalid_time;

    // 标识符:IC_invalid_time
    // 名  称:IC失效时间
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    IC_INVALID_TIME_TYPE_DEF IC_invalid_time;

    // 标识符:Integrated_NAV_Work_State_
    // 名  称:组合通道工作状态字
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:24
    UINT32 Integrated_NAV_Work_State_ : 8;

    // 标识符:Integ_NAV_Forced_Selec_Mode
    // 名  称:惯导组合导航强选指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:16
    UINT32 Integ_NAV_Forced_Selec_Mode : 8;

    // 标识符:INS_ALIGNMENT_WAY_
    // 名  称:惯导对准方式
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:8
    UINT32 INS_ALIGNMENT_WAY_ : 8;

    // 标识符:INS_cmd_Aim_cmd
    // 名  称:VMC惯导对准指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    UINT32 INS_cmd_Aim_cmd : 8;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:GNSS_Reset_CMD
    // 名  称:接收机重启指令
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    UINT32 GNSS_Reset_CMD : 8;

    // 标识符:Destroy_Key_cmd2_
    // 名  称:毁钥指令2_
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:24
    UINT32 Destroy_Key_cmd2_ : 8;

    // 标识符:Destroy_Key_cmd1
    // 名  称:毁钥指令1
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:16
    UINT32 Destroy_Key_cmd1 : 8;

    // 标识符:Force_BD_J_cmd_
    // 名  称:强制BD军指令_
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:8
    UINT32 Force_BD_J_cmd_ : 8;

    // 标识符:BDS_C_P_cmd
    // 名  称:BD C引P 指令
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT32 BDS_C_P_cmd : 8;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:num_of_satellite_bd_MIN
    // 名  称:北斗卫星数目_民码
    // 说  明:表示当前可用的北斗卫星数目（民码）。
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:0
    UINT8 num_of_satellite_bd_MIN;

    SPARE32 spare3[4];  // 保留字段

} INS1_OPERATIONAL_PARAS;

// 主题 标 识 符: INS2_nav_data
// 主题 名    称: INS2导航数据
// 主题 编    码: 399
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 228
// 主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//                其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//                卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                每一类数据时标信号之后的数据为其对应的该类数据。且惯导2转发飞管B、D通道大气数据。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:hybrid_nav_data_A
    // 名  称:组合导航数据A
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    HYBRID_NAV_DATA_A_TYPE_DEF hybrid_nav_data_A;

    // 标识符:hybrid_nav_data_B
    // 名  称:组合导航数据B
    // 说  明:
    // 单  位:
    // 起始字:73
    // 起始位:0
    HYBRID_NAV_DATA_B_TYPE_DEF hybrid_nav_data_B;

    // 标识符:pure_inertial_nav_data_A
    // 名  称:纯惯导航数据A
    // 说  明:
    // 单  位:
    // 起始字:95
    // 起始位:0
    PURE_INERTIAL_NAV_DATA_A_TYPE_DEF pure_inertial_nav_data_A;

    // 标识符:pure_inertia_nav_data_B
    // 名  称:纯惯导航数据B
    // 说  明:
    // 单  位:
    // 起始字:152
    // 起始位:0
    PURE_INERTIA_NAV_DATA_B_TYPE_DEF pure_inertia_nav_data_B;

    // 标识符:satellite_nav_data
    // 名  称:卫星导航数据
    // 说  明:
    // 单  位:
    // 起始字:158
    // 起始位:0
    SATELLITE_NAV_DATA_TYPE_DEF satellite_nav_data;

    // 标识符:air_nav_data_B
    // 名  称:大气导航数据_B
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:176
    // 起始位:0
    AIR_NAV_DATA_B_TYPE_DEF air_nav_data_B;

    // 标识符:air_nav_data_D
    // 名  称:大气导航数据_D
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:202
    // 起始位:0
    AIR_NAV_DATA_D_TYPE_DEF air_nav_data_D;

} INS2_NAV_DATA;

// 主题 标 识 符: INS2_NAV_data_5ms
// 主题 名    称: INS2导航数据_5ms
// 主题 编    码: 2116
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 48
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:data_generated_time1
    // 名  称:数据生成时间1
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:6
    // 起始位:0
    DATA_GENERATED_TIME1_TYPE_DEF data_generated_time1;

    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_pitch_rate;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    // 标识符:validity_roll_accel
    // 名  称:有效性_横滚角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:24
    BOOL_8 validity_roll_accel;

    // 标识符:validity_pitch_accel
    // 名  称:有效性_俯仰角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:16
    BOOL_8 validity_pitch_accel;

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_roll_rate;

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:24
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:16
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:8
    BOOL_8 validity_vel_north;

    // 标识符:validity_heading_accel
    // 名  称:有效性_航向角加速度
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    BOOL_8 validity_heading_accel;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:24
    BOOL_8 validity_inertial_AOA;

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    BOOL_8 validity_accel_north;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:24
    BOOL_8 validity_climbing_angle;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:16
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:8
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    BOOL_8 validity_ground_speed;

    // 标识符:validity_baro_pressure_inertial_alt
    // 名  称:有效性_惯性气压参考高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:16
    BOOL_8 validity_baro_pressure_inertial_alt;

    // 标识符:validity_pressure_inertial_alt
    // 名  称:有效性_惯性气压高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    BOOL_8 validity_pressure_inertial_alt;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    BOOL_8 validity_position;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //       仰角为正
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //       右倾为正
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_pitch_accel
    // 名  称:载机俯仰角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_PITCH_ACCEL_TYPE_DEF ac_pitch_accel;

    // 标识符:ac_roll_accel
    // 名  称:载机横滚角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:23
    // 起始位:0
    AC_ROLL_ACCEL_TYPE_DEF ac_roll_accel;

    // 标识符:ac_heading_accel
    // 名  称:载机航向角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:24
    // 起始位:0
    AC_HEADING_ACCEL_TYPE_DEF ac_heading_accel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:25
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:28
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //       速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:31
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //       速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:32
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //       速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:34
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //       爬升为正
    // 单  位:
    // 起始字:35
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //       (-180,180]deg
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:AC_pressure_inertial_alt
    // 名  称:载机惯性气压高度
    // 说  明:[-500,30000]m
    //       INS阻尼后的气压高度
    // 单  位:
    // 起始字:38
    // 起始位:0
    AC_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_pressure_inertial_alt;

    // 标识符:AC_baro_pressure_inertial_alt
    // 名  称:载机惯性气压参考高度
    // 说  明:[-5500,30000]m
    //       =惯性气压高度－场压装订高度
    // 单  位:
    // 起始字:39
    // 起始位:0
    AC_BARO_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_baro_pressure_inertial_alt;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:40
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    SPARE32 spare3[7];  // 保留字段

} INS2_NAV_DATA_5MS;

// 主题 标 识 符: INS2_operational_paras
// 主题 名    称: INS2工作参数报告
// 主题 编    码: 389
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 25
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:INS_sub_mode_state
    // 名  称:惯导当前子模式
    // 说  明:惯导向任务系统上报当前工作模式；
    //       目前无6-传递对准模式；
    //       增加7-对准失败模式；
    //       初始化上报0；
    //       其余按当前工作模式上报；
    // 单  位:
    // 起始字:4
    // 起始位:24
    UINT32 INS_sub_mode_state : 8;

    // 标识符:INS_sub_mode_req
    // 名  称:惯导子模式请求
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 INS_sub_mode_req : 8;

    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 primary_secondary : 8;

    // 标识符:WOW_main
    // 名  称:轮载状态_主
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 WOW_main : 8;

    // 标识符:SAT_select_state
    // 名  称:惯导当前选择卫星
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    UINT32 SAT_select_state : 8;

    // 标识符:INS_SAT_type_req
    // 名  称:惯导卫星选择请求
    // 说  明:自动（优先级：BD军、BD民、GPS、内置、转发）
    //       此条请求本来为任务系统向惯导发活动请求后，惯导回报相关请求，现阶段，惯导不响应任务系统的命令（以1394为主），目前按惯导当前工作状态填值；
    //       报送状态时：
    //       如果VMC的1394命令中，"惯导航强选指令"为自主，则上报1-AUTO 自动；
    // 单  位:
    // 起始字:5
    // 起始位:16
    UINT32 INS_SAT_type_req : 8;

    // 标识符:INS_operation_mode_state
    // 名  称:惯导当前工作方式
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    UINT32 INS_operation_mode_state : 8;

    // 标识符:INS_operation_mode_req
    // 名  称:惯导工作方式请求
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 INS_operation_mode_req : 8;

    // 标识符:align_done_state
    // 名  称:对准完成状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:24
    UINT32 align_done_state : 8;

    // 标识符:enhanced_align_state
    // 名  称:增强对准状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    UINT32 enhanced_align_state : 8;

    // 标识符:satellite_use_state
    // 名  称:卫星使用状态
    // 说  明:此信号用于表征卫星的使用状态。
    // 单  位:
    // 起始字:6
    // 起始位:8
    UINT32 satellite_use_state : 8;

    // 标识符:dipper_operational_mod
    // 名  称:北斗工作模式
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    UINT32 dipper_operational_mod : 8;

    // 标识符:INS_align_param
    // 名  称:惯导对准参数信息
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    INS_ALIGN_PARAM_TYPE_DEF INS_align_param;

    // 标识符:primary_secondary_recommend_type
    // 名  称:主备推荐方式
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    UINT32 primary_secondary_recommend_type : 8;

    // 标识符:num_of_satellite
    // 名  称:定位卫星数目
    // 说  明:从卫星报文的GGA语句中解析得到
    // 单  位:
    // LSB  :1
    // 起始字:13
    // 起始位:16
    UINT32 num_of_satellite : 8;

    // 标识符:ADS_data_channel_state
    // 名  称:大气数据通道选择状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    UINT32 ADS_data_channel_state : 8;

    // 标识符:GNSS_inertial_ADS_alt_state
    // 名  称:惯性卫星大气高度通道组合状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 GNSS_inertial_ADS_alt_state : 8;

    // 标识符:IC_invalid_state
    // 名  称:IC失效状态
    // 说  明:用于表征卫星军码IC的失效状态。其中：
    //       “正常有效”指IC失效的日期与当前的日期差大于8周；
    //       “邻近失效”指IC失效的日期与当前的日期差在8周内；
    //       “失效”指IC失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:24
    UINT32 IC_invalid_state : 8;

    // 标识符:PRM_invalid_state
    // 名  称:PRM失效状态
    // 说  明:用于表征卫星军码PRM的失效状态。其中：
    //       “正常有效”指PRM失效的日期与当前的日期差大于8周；
    //       “邻近失效”指PRM失效的日期与当前的日期差在8周内；
    //       “失效”指PRM失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:16
    UINT32 PRM_invalid_state : 8;

    // 标识符:num_of_satellite_bd_JUN
    // 名  称:北斗卫星数目_军码
    // 说  明:表示当前可用的北斗卫星数目（军码）。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:8
    UINT32 num_of_satellite_bd_JUN : 8;

    // 标识符:num_of_satellite_gps
    // 名  称:GPS卫星数目
    // 说  明:表示当前可用的GPS卫星数目。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:0
    UINT32 num_of_satellite_gps : 8;

    // 标识符:IC_invalid_time
    // 名  称:IC失效时间
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    IC_INVALID_TIME_TYPE_DEF IC_invalid_time;

    // 标识符:PRM_invalid_time
    // 名  称:PRM失效时间
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    PRM_INVALID_TIME_TYPE_DEF PRM_invalid_time;

    // 标识符:Integrated_NAV_Work_State_
    // 名  称:组合通道工作状态字
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:24
    UINT32 Integrated_NAV_Work_State_ : 8;

    // 标识符:Integ_NAV_Forced_Selec_Mode
    // 名  称:惯导组合导航强选指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:16
    UINT32 Integ_NAV_Forced_Selec_Mode : 8;

    // 标识符:INS_ALIGNMENT_WAY_
    // 名  称:惯导对准方式
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:8
    UINT32 INS_ALIGNMENT_WAY_ : 8;

    // 标识符:INS_cmd_Aim_cmd
    // 名  称:VMC惯导对准指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    UINT32 INS_cmd_Aim_cmd : 8;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:GNSS_Reset_CMD
    // 名  称:接收机重启指令
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    UINT32 GNSS_Reset_CMD : 8;

    // 标识符:Destroy_Key_cmd2_
    // 名  称:毁钥指令2_
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:24
    UINT32 Destroy_Key_cmd2_ : 8;

    // 标识符:Destroy_Key_cmd1
    // 名  称:毁钥指令1
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:16
    UINT32 Destroy_Key_cmd1 : 8;

    // 标识符:Force_BD_J_cmd_
    // 名  称:强制BD军指令_
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:8
    UINT32 Force_BD_J_cmd_ : 8;

    // 标识符:BDS_C_P_cmd
    // 名  称:BD C引P 指令
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT32 BDS_C_P_cmd : 8;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:num_of_satellite_bd_MIN
    // 名  称:北斗卫星数目_民码
    // 说  明:表示当前可用的北斗卫星数目（民码）。
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:0
    UINT8 num_of_satellite_bd_MIN;

    SPARE32 spare3[4];  // 保留字段

} INS2_OPERATIONAL_PARAS;

// 主题 标 识 符: INS3_nav_data
// 主题 名    称: INS3导航数据
// 主题 编    码: 4195
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 228
// 主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//                其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//                卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//                每一类数据时标信号之后的数据为其对应的该类数据。且惯导2转发飞管B、D通道大气数据。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:hybrid_nav_data_A
    // 名  称:组合导航数据A
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    HYBRID_NAV_DATA_A_TYPE_DEF hybrid_nav_data_A;

    // 标识符:hybrid_nav_data_B
    // 名  称:组合导航数据B
    // 说  明:
    // 单  位:
    // 起始字:73
    // 起始位:0
    HYBRID_NAV_DATA_B_TYPE_DEF hybrid_nav_data_B;

    // 标识符:pure_inertial_nav_data_A
    // 名  称:纯惯导航数据A
    // 说  明:
    // 单  位:
    // 起始字:95
    // 起始位:0
    PURE_INERTIAL_NAV_DATA_A_TYPE_DEF pure_inertial_nav_data_A;

    // 标识符:pure_inertia_nav_data_B
    // 名  称:纯惯导航数据B
    // 说  明:
    // 单  位:
    // 起始字:152
    // 起始位:0
    PURE_INERTIA_NAV_DATA_B_TYPE_DEF pure_inertia_nav_data_B;

    // 标识符:satellite_nav_data
    // 名  称:卫星导航数据
    // 说  明:
    // 单  位:
    // 起始字:158
    // 起始位:0
    SATELLITE_NAV_DATA_TYPE_DEF satellite_nav_data;

    // 标识符:air_nav_data_B
    // 名  称:大气导航数据_B
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:176
    // 起始位:0
    AIR_NAV_DATA_B_TYPE_DEF air_nav_data_B;

    // 标识符:air_nav_data_D
    // 名  称:大气导航数据_D
    // 说  明:“飞管数据包有效性”根据SVPC、心跳原则判断。
    //       “飞管通道有效性”根据CHV判断。
    // 单  位:
    // 起始字:202
    // 起始位:0
    AIR_NAV_DATA_D_TYPE_DEF air_nav_data_D;

} INS3_NAV_DATA;

// 主题 标 识 符: INS3_NAV_data_5ms
// 主题 名    称: INS3导航数据_5ms
// 主题 编    码: 4196
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 48
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 primary_secondary : 8;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    // 标识符:data_generated_time1
    // 名  称:数据生成时间1
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:6
    // 起始位:0
    DATA_GENERATED_TIME1_TYPE_DEF data_generated_time1;

    // 标识符:validity_pitch_rate
    // 名  称:有效性_俯仰角速率
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    BOOL_8 validity_pitch_rate;

    // 标识符:validity_true_heading
    // 名  称:有效性_真航向
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    BOOL_8 validity_true_heading;

    // 标识符:validity_roll_angle
    // 名  称:有效性_横滚角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:8
    BOOL_8 validity_roll_angle;

    // 标识符:validity_pitch_angle
    // 名  称:有效性_俯仰角
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    BOOL_8 validity_pitch_angle;

    // 标识符:validity_roll_accel
    // 名  称:有效性_横滚角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:24
    BOOL_8 validity_roll_accel;

    // 标识符:validity_pitch_accel
    // 名  称:有效性_俯仰角加速度
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:16
    BOOL_8 validity_pitch_accel;

    // 标识符:validity_heading_rate
    // 名  称:有效性_航向角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_heading_rate;

    // 标识符:validity_roll_rate
    // 名  称:有效性_横滚角速率
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_roll_rate;

    // 标识符:validity_vel_up
    // 名  称:有效性_速度天向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:24
    BOOL_8 validity_vel_up;

    // 标识符:validity_vel_west
    // 名  称:有效性_速度西向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:16
    BOOL_8 validity_vel_west;

    // 标识符:validity_vel_north
    // 名  称:有效性_速度北向
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:8
    BOOL_8 validity_vel_north;

    // 标识符:validity_heading_accel
    // 名  称:有效性_航向角加速度
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    BOOL_8 validity_heading_accel;

    // 标识符:validity_inertial_AOA
    // 名  称:有效性_惯性攻角
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:24
    BOOL_8 validity_inertial_AOA;

    // 标识符:validity_accel_up
    // 名  称:有效性_加速度天向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:16
    BOOL_8 validity_accel_up;

    // 标识符:validity_accel_west
    // 名  称:有效性_加速度西向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:8
    BOOL_8 validity_accel_west;

    // 标识符:validity_accel_north
    // 名  称:有效性_加速度北向
    // 说  明:
    // 单  位:
    // 起始字:11
    // 起始位:0
    BOOL_8 validity_accel_north;

    // 标识符:validity_climbing_angle
    // 名  称:有效性_爬升角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:24
    BOOL_8 validity_climbing_angle;

    // 标识符:validity_ground_track_angle
    // 名  称:有效性_航迹角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:16
    BOOL_8 validity_ground_track_angle;

    // 标识符:validity_sl_angle
    // 名  称:有效性_偏流角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:8
    BOOL_8 validity_sl_angle;

    // 标识符:validity_inertial_AOS
    // 名  称:有效性_惯性侧滑角
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    BOOL_8 validity_inertial_AOS;

    // 标识符:validity_ground_speed
    // 名  称:有效性_地速
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    BOOL_8 validity_ground_speed;

    // 标识符:validity_baro_pressure_inertial_alt
    // 名  称:有效性_惯性气压参考高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:16
    BOOL_8 validity_baro_pressure_inertial_alt;

    // 标识符:validity_pressure_inertial_alt
    // 名  称:有效性_惯性气压高度
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    BOOL_8 validity_pressure_inertial_alt;

    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    BOOL_8 validity_position;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:ac_pitch
    // 名  称:载机俯仰角
    // 说  明:[-90,90]deg
    //       仰角为正
    // 单  位:
    // 起始字:16
    // 起始位:0
    AC_PITCH_TYPE_DEF ac_pitch;

    // 标识符:ac_roll
    // 名  称:载机横滚角
    // 说  明:(-180,180]deg
    //       右倾为正
    // 单  位:
    // 起始字:17
    // 起始位:0
    AC_ROLL_TYPE_DEF ac_roll;

    // 标识符:ac_true_heading
    // 名  称:载机真航向
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:18
    // 起始位:0
    AC_TRUE_HEADING_TYPE_DEF ac_true_heading;

    // 标识符:ac_pitch_rate
    // 名  称:载机俯仰角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:19
    // 起始位:0
    AC_PITCH_RATE_TYPE_DEF ac_pitch_rate;

    // 标识符:ac_roll_rate
    // 名  称:载机横滚角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:20
    // 起始位:0
    AC_ROLL_RATE_TYPE_DEF ac_roll_rate;

    // 标识符:ac_heading_rate
    // 名  称:载机航向角速率
    // 说  明:[-720,720]deg/s
    // 单  位:
    // 起始字:21
    // 起始位:0
    AC_HEADING_RATE_TYPE_DEF ac_heading_rate;

    // 标识符:ac_pitch_accel
    // 名  称:载机俯仰角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:22
    // 起始位:0
    AC_PITCH_ACCEL_TYPE_DEF ac_pitch_accel;

    // 标识符:ac_roll_accel
    // 名  称:载机横滚角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:23
    // 起始位:0
    AC_ROLL_ACCEL_TYPE_DEF ac_roll_accel;

    // 标识符:ac_heading_accel
    // 名  称:载机航向角加速度
    // 说  明:[-1000,1000]deg/s2
    // 单  位:
    // 起始字:24
    // 起始位:0
    AC_HEADING_ACCEL_TYPE_DEF ac_heading_accel;

    // 标识符:ac_plat_vel
    // 名  称:载机平台系速度
    // 说  明:[-1000,1000]m/s;[-1000,1000]m/s;[-1000,1000]m/s
    // 单  位:
    // 起始字:25
    // 起始位:0
    AC_PLAT_VEL_TYPE_DEF ac_plat_vel;

    // 标识符:ac_plat_accel
    // 名  称:载机平台系加速度
    // 说  明:[-100,100]m/s/s;[-100,100]m/s/s;[-100,100]m/s/s
    // 单  位:
    // 起始字:28
    // 起始位:0
    AC_PLAT_ACCEL_TYPE_DEF ac_plat_accel;

    // 标识符:ac_inertial_AOA
    // 名  称:载机惯性攻角
    // 说  明:[-90,90]deg
    //       速度矢量在飞机对称面的投影与飞机纵轴之间的夹角，夹角在飞机平面下方为正。
    // 单  位:
    // 起始字:31
    // 起始位:0
    AC_INERTIAL_AOA_TYPE_DEF ac_inertial_AOA;

    // 标识符:ac_inertial_AOS
    // 名  称:载机惯性侧滑角
    // 说  明:[-45,45]deg
    //       速度矢量在飞机平面（XY轴平面）的投影与飞机纵轴之间的夹角，向右侧滑为正。
    // 单  位:
    // 起始字:32
    // 起始位:0
    AC_INERTIAL_AOS_TYPE_DEF ac_inertial_AOS;

    // 标识符:ac_sl_angle
    // 名  称:载机偏流角
    // 说  明:[-45,45]deg
    //       速度矢量在水平面的投影与飞机纵轴在水平面投影之间的夹角，速度偏向机轴右侧为正。
    // 单  位:
    // 起始字:33
    // 起始位:0
    AC_SL_ANGLE_TYPE_DEF ac_sl_angle;

    // 标识符:ac_ground_track_angle
    // 名  称:载机航迹角
    // 说  明:[0,360)deg
    //       相对于真北顺时针为正
    // 单  位:
    // 起始字:34
    // 起始位:0
    AC_GROUND_TRACK_ANGLE_TYPE_DEF ac_ground_track_angle;

    // 标识符:ac_climbing_angle
    // 名  称:载机爬升角
    // 说  明:[-90,90]deg
    //       爬升为正
    // 单  位:
    // 起始字:35
    // 起始位:0
    AC_CLIMBING_ANGLE_TYPE_DEF ac_climbing_angle;

    // 标识符:ac_position_data
    // 名  称:载机位置数据
    // 说  明:[-90,90]deg
    //       (-180,180]deg
    // 单  位:
    // 起始字:36
    // 起始位:0
    AC_POSITION_DATA_TYPE_DEF ac_position_data;

    // 标识符:AC_pressure_inertial_alt
    // 名  称:载机惯性气压高度
    // 说  明:[-500,30000]m
    //       INS阻尼后的气压高度
    // 单  位:
    // 起始字:38
    // 起始位:0
    AC_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_pressure_inertial_alt;

    // 标识符:AC_baro_pressure_inertial_alt
    // 名  称:载机惯性气压参考高度
    // 说  明:[-5500,30000]m
    //       =惯性气压高度－场压装订高度
    // 单  位:
    // 起始字:39
    // 起始位:0
    AC_BARO_PRESSURE_INERTIAL_ALT_TYPE_DEF AC_baro_pressure_inertial_alt;

    // 标识符:ac_ground_speed
    // 名  称:载机地速
    // 说  明:[-1000,1000]m/s
    // 单  位:
    // 起始字:40
    // 起始位:0
    AC_GROUND_SPEED_TYPE_DEF ac_ground_speed;

    SPARE32 spare3[7];  // 保留字段

} INS3_NAV_DATA_5MS;

// 主题 标 识 符: INS3_operational_paras
// 主题 名    称: INS3工作参数报告
// 主题 编    码: 4193
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 25
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:INS_sub_mode_state
    // 名  称:惯导当前子模式
    // 说  明:惯导向任务系统上报当前工作模式；
    //       目前无6-传递对准模式；
    //       增加7-对准失败模式；
    //       初始化上报0；
    //       其余按当前工作模式上报；
    // 单  位:
    // 起始字:4
    // 起始位:24
    UINT32 INS_sub_mode_state : 8;

    // 标识符:INS_sub_mode_req
    // 名  称:惯导子模式请求
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 INS_sub_mode_req : 8;

    // 标识符:primary_secondary
    // 名  称:主备状态
    // 说  明:主备状态标志
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 primary_secondary : 8;

    // 标识符:WOW_main
    // 名  称:轮载状态_主
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 WOW_main : 8;

    // 标识符:SAT_select_state
    // 名  称:惯导当前选择卫星
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:24
    UINT32 SAT_select_state : 8;

    // 标识符:INS_SAT_type_req
    // 名  称:惯导卫星选择请求
    // 说  明:自动（优先级：BD军、BD民、GPS、内置、转发）
    //       此条请求本来为任务系统向惯导发活动请求后，惯导回报相关请求，现阶段，惯导不响应任务系统的命令（以1394为主），目前按惯导当前工作状态填值；
    //       报送状态时：
    //       如果VMC的1394命令中，"惯导航强选指令"为自主，则上报1-AUTO 自动；
    // 单  位:
    // 起始字:5
    // 起始位:16
    UINT32 INS_SAT_type_req : 8;

    // 标识符:INS_operation_mode_state
    // 名  称:惯导当前工作方式
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:8
    UINT32 INS_operation_mode_state : 8;

    // 标识符:INS_operation_mode_req
    // 名  称:惯导工作方式请求
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 INS_operation_mode_req : 8;

    // 标识符:align_done_state
    // 名  称:对准完成状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:24
    UINT32 align_done_state : 8;

    // 标识符:enhanced_align_state
    // 名  称:增强对准状态
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:16
    UINT32 enhanced_align_state : 8;

    // 标识符:satellite_use_state
    // 名  称:卫星使用状态
    // 说  明:此信号用于表征卫星的使用状态。
    // 单  位:
    // 起始字:6
    // 起始位:8
    UINT32 satellite_use_state : 8;

    // 标识符:dipper_operational_mod
    // 名  称:北斗工作模式
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    UINT32 dipper_operational_mod : 8;

    // 标识符:INS_align_param
    // 名  称:惯导对准参数信息
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    INS_ALIGN_PARAM_TYPE_DEF INS_align_param;

    // 标识符:primary_secondary_recommend_type
    // 名  称:主备推荐方式
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    UINT32 primary_secondary_recommend_type : 8;

    // 标识符:num_of_satellite
    // 名  称:定位卫星数目
    // 说  明:从卫星报文的GGA语句中解析得到
    // 单  位:
    // LSB  :1
    // 起始字:13
    // 起始位:16
    UINT32 num_of_satellite : 8;

    // 标识符:ADS_data_channel_state
    // 名  称:大气数据通道选择状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    UINT32 ADS_data_channel_state : 8;

    // 标识符:GNSS_inertial_ADS_alt_state
    // 名  称:惯性卫星大气高度通道组合状态
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 GNSS_inertial_ADS_alt_state : 8;

    // 标识符:IC_invalid_state
    // 名  称:IC失效状态
    // 说  明:用于表征卫星军码IC的失效状态。其中：
    //       “正常有效”指IC失效的日期与当前的日期差大于8周；
    //       “邻近失效”指IC失效的日期与当前的日期差在8周内；
    //       “失效”指IC失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:24
    UINT32 IC_invalid_state : 8;

    // 标识符:PRM_invalid_state
    // 名  称:PRM失效状态
    // 说  明:用于表征卫星军码PRM的失效状态。其中：
    //       “正常有效”指PRM失效的日期与当前的日期差大于8周；
    //       “邻近失效”指PRM失效的日期与当前的日期差在8周内；
    //       “失效”指PRM失效的日期超过了当前的日期。
    // 单  位:
    // 起始字:14
    // 起始位:16
    UINT32 PRM_invalid_state : 8;

    // 标识符:num_of_satellite_bd_JUN
    // 名  称:北斗卫星数目_军码
    // 说  明:表示当前可用的北斗卫星数目（军码）。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:8
    UINT32 num_of_satellite_bd_JUN : 8;

    // 标识符:num_of_satellite_gps
    // 名  称:GPS卫星数目
    // 说  明:表示当前可用的GPS卫星数目。
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:0
    UINT32 num_of_satellite_gps : 8;

    // 标识符:PRM_invalid_time
    // 名  称:PRM失效时间
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    PRM_INVALID_TIME_TYPE_DEF PRM_invalid_time;

    // 标识符:IC_invalid_time
    // 名  称:IC失效时间
    // 说  明:
    // 单  位:
    // 起始字:16
    // 起始位:0
    IC_INVALID_TIME_TYPE_DEF IC_invalid_time;

    // 标识符:Integrated_NAV_Work_State_
    // 名  称:组合通道工作状态字
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:24
    UINT32 Integrated_NAV_Work_State_ : 8;

    // 标识符:Integ_NAV_Forced_Selec_Mode
    // 名  称:惯导组合导航强选指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:16
    UINT32 Integ_NAV_Forced_Selec_Mode : 8;

    // 标识符:INS_ALIGNMENT_WAY_
    // 名  称:惯导对准方式
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:8
    UINT32 INS_ALIGNMENT_WAY_ : 8;

    // 标识符:INS_cmd_Aim_cmd
    // 名  称:VMC惯导对准指令
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    UINT32 INS_cmd_Aim_cmd : 8;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:GNSS_Reset_CMD
    // 名  称:接收机重启指令
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    UINT32 GNSS_Reset_CMD : 8;

    // 标识符:Destroy_Key_cmd2_
    // 名  称:毁钥指令2_
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:24
    UINT32 Destroy_Key_cmd2_ : 8;

    // 标识符:Destroy_Key_cmd1
    // 名  称:毁钥指令1
    // 说  明:"仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
    //
    // 单  位:
    // 起始字:19
    // 起始位:16
    UINT32 Destroy_Key_cmd1 : 8;

    // 标识符:Force_BD_J_cmd_
    // 名  称:强制BD军指令_
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:8
    UINT32 Force_BD_J_cmd_ : 8;

    // 标识符:BDS_C_P_cmd
    // 名  称:BD C引P 指令
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT32 BDS_C_P_cmd : 8;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:num_of_satellite_bd_MIN
    // 名  称:北斗卫星数目_民码
    // 说  明:表示当前可用的北斗卫星数目（民码）。
    // 单  位:
    // LSB  :1
    // 起始字:20
    // 起始位:0
    UINT8 num_of_satellite_bd_MIN;

    SPARE32 spare3[4];  // 保留字段

} INS3_OPERATIONAL_PARAS;

// 主题 标 识 符: IR_AA_search_report
// 主题 名    称: 红外点迹目标报告
// 主题 编    码: 1018
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 303
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:ir_aa_search
    // 名  称:IR空空点迹参数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    IR_AA_SEARCH_TYPE_DEF ir_aa_search[50];

    SPARE32 spare1[150];  // 保留字段

} IR_AA_SEARCH_REPORT;

// 主题 标 识 符: IR_AA_track_report
// 主题 名    称: IR空空跟踪目标报告
// 主题 编    码: 1280
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    SPARE8 spare1[3];  // 保留字段

    // 标识符:target_acount
    // 名  称:目标数目
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT8 target_acount;

    // 标识符:IR_track_paras
    // 名  称:IR空空跟踪目标参数
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    IR_TRACK_PARAS_TYPE_DEF IR_track_paras[10];

} IR_AA_TRACK_REPORT;

// 主题 标 识 符: IR_LOS_ground_alt
// 主题 名    称: 光雷LOS地形高度请求
// 主题 编    码: 3319
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 20
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:area_radius
    // 名  称:区域半径
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 area_radius : 8;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:validity_position
    // 名  称:有效性_位置
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 validity_position : 8;

    // 标识符:position_los_cross
    // 名  称:LOS交点位置
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    POSITION_LOS_CROSS_TYPE_DEF position_los_cross;

    SPARE32 spare3[14];  // 保留字段

} IR_LOS_GROUND_ALT;

// 主题 标 识 符: IR_LOS_map_ground_alt
// 主题 名    称: 光雷LOS地面交点地形高度
// 主题 编    码: 3321
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 20
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    UINT32 spare2 : 8;  // 保留字段
    // 标识符:area_radius
    // 名  称:区域半径
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:16
    UINT32 area_radius : 8;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:validity_ground_height
    // 名  称:有效性_地形高度
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 validity_ground_height : 8;

    // 标识符:position_los_cross
    // 名  称:LOS交点位置
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    POSITION_LOS_CROSS_TYPE_DEF position_los_cross;

    // 标识符:ground_height
    // 名  称:地形高度
    // 说  明:[-500,10000]m
    //       地形高度。
    // 单  位:
    // 起始字:8
    // 起始位:0
    GROUND_HEIGHT_TYPE_DEF ground_height;

    SPARE32 spare3[11];  // 保留字段

} IR_LOS_MAP_GROUND_ALT;

// 主题 标 识 符: IR_nav_data
// 主题 名    称: 光电IMU导航数据
// 主题 编    码: 4489
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 20
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:IR_IMU_data
    // 名  称:光电IMU数据
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    IR_IMU_DATA_TYPE_DEF IR_IMU_data;

    SPARE32 spare1[14];  // 保留字段

} IR_NAV_DATA;

// 主题 标 识 符: IR_surface_track_report
// 主题 名    称: IR面目标参数报告
// 主题 编    码: 1021
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 71
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:IR_surface_track
    // 名  称:IR面目标参数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    IR_SURFACE_TRACK_TYPE_DEF IR_surface_track[4];

} IR_SURFACE_TRACK_REPORT;

// 主题 标 识 符: IRST_act_req
// 主题 名    称: IRST活动请求
// 主题 编    码: 1017
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 60
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:activity_number_64
    // 名  称:活动编号_64
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT64 activity_number_64;

    // 标识符:general_act_req
    // 名  称:通用活动请求
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 general_act_req : 32;

    // 标识符:general_act_req_paras
    // 名  称:通用活动请求附加参数
    // 说  明:该信号仅在“通用活动请求”枚举值不为“NA”或“特殊活动请求”时有效
    // 单  位:
    // 起始字:6
    // 起始位:0
    GENERAL_ACT_REQ_PARAS_TYPE_DEF general_act_req_paras;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:unique_act_req_IRS
    // 名  称:特殊活动请求_IRST
    // 说  明:
    // 单  位:
    // 起始字:7
    // 起始位:0
    UINT32 unique_act_req_IRS : 8;

    // 标识符:unique_act_req_paras_IRST
    // 名  称:特殊活动请求附加参数_IRST
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:0
    UNIQUE_ACT_REQ_PARAS_IRST_TYPE_DEF unique_act_req_paras_IRST;

    SPARE32 spare2[19];  // 保留字段

} IRST_ACT_REQ;

// 主题 标 识 符: IRST_act_req_report
// 主题 名    称: IRST_活动请求通告
// 主题 编    码: 1104
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 7
// 主题 说    明: 各子域发送该主题，以确认收到活动请求。活动请求通告是向发出请求的子域通告活动的执行结果，是该活动的终结状态消息。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:req_publisher_ID
    // 名  称:请求发布者ID
    // 说  明:发布活动请求者的ID号。
    // 单  位:
    // 起始字:3
    // 起始位:0
    REQ_PUBLISHER_ID_TYPE_DEF req_publisher_ID;

    // 标识符:activity_number_64
    // 名  称:活动编号_64
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT64 activity_number_64;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:act_refused_reason
    // 名  称:拒绝请求原因
    // 说  明:仅当活动状态等于NACK的时候，该信号有效：
    //       1.无效的参数：活动请求所包含的附加参数无效或不存在。
    //       2.无效的活动：活动请求的类型无效，或者不能被执行。
    //       3.无效的请求方：接收方不能识别发起请求的子域。例如请求子域ID无效。
    //       4.辐射限制：受传感器计划或飞行员控制的影响，传感器不允许辐射，因而不能执行所请求的活动。
    //       5.时间限制：受传感器本身限制，在请求的时间内不能完成所请求的活动；或者因为在请求的时间范围内，该活动不被允许。
    //       6.安全因素：因安全因素不能完成所请求的活动。例如地面不允许辐射，当前状态不允许开舱，不允许激光发射，不允许发射干扰弹等。
    //       7.无法执行：活动执行方因故障、或者非操作状态等不能完成所请求的活动。例如设备处于测试状态，但要求设备进行目标测量等。
    // 单  位:
    // 起始字:6
    // 起始位:8
    UINT32 act_refused_reason : 8;

    // 标识符:activity_state
    // 名  称:活动状态
    // 说  明:NACK：活动未能开始时，需要发送。不论是因为错误的请求，还是请求不能执行，在拒绝请求原因信号中进行详细说明。
    //       CANCELLED：当活动被取消，或者已经开始但被中止。可能是因为系统资源丢失，或者系统进入不能运行该请求的状态。
    //       COMPLETED：活动正常完成，并从活动清单中已清除。
    //       ECHO：表示收到活动请求。
    // 单  位:
    // 起始字:6
    // 起始位:0
    UINT32 activity_state : 8;

} IRST_ACT_REQ_REPORT;

// 主题 标 识 符: IRST_cooperation_tgt_report_I
// 主题 名    称: 光雷协同目标参数报告_I
// 主题 编    码: 3797
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 332
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    SPARE8 spare1[3];  // 保留字段

    // 标识符:irst_target_acount
    // 名  称:光雷航迹目标数目
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT8 irst_target_acount;

    // 标识符:irst_tgt_det_paras
    // 名  称:光雷目标探测参数
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    IRST_TGT_DET_PARAS_TYPE_DEF irst_tgt_det_paras;

    // 标识符:irst_cooperation_track_paras
    // 名  称:光雷协同航迹目标参数
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    IRST_COOPERATION_TRACK_PARAS_TYPE_DEF irst_cooperation_track_paras[10];

} IRST_COOPERATION_TGT_REPORT_I;

// 主题 标 识 符: IRST_cooperation_tgt_report_IFDL
// 主题 名    称: 光雷协同目标参数报告_IFDL
// 主题 编    码: 3798
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 450
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:irst_target_acount
    // 名  称:光雷航迹目标数目
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:9
    // 起始位:0
    UINT8 irst_target_acount;

    // 标识符:irst_tgt_det_paras
    // 名  称:光雷目标探测参数
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    IRST_TGT_DET_PARAS_TYPE_DEF irst_tgt_det_paras;

    // 标识符:irst_cooperation_track_paras
    // 名  称:光雷协同航迹目标参数
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    IRST_COOPERATION_TRACK_PARAS_TYPE_DEF irst_cooperation_track_paras[10];

    SPARE32 spare3[112];  // 保留字段

} IRST_COOPERATION_TGT_REPORT_IFDL;

// 主题 标 识 符: IRST_cooperation_tgt_report_IFDL1
// 主题 名    称: 光雷协同目标参数报告_IFDL1
// 主题 编    码: 3799
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 450
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:irst_target_acount
    // 名  称:光雷航迹目标数目
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:9
    // 起始位:0
    UINT8 irst_target_acount;

    // 标识符:irst_tgt_det_paras
    // 名  称:光雷目标探测参数
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    IRST_TGT_DET_PARAS_TYPE_DEF irst_tgt_det_paras;

    // 标识符:irst_cooperation_track_paras
    // 名  称:光雷协同航迹目标参数
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    IRST_COOPERATION_TRACK_PARAS_TYPE_DEF irst_cooperation_track_paras[10];

    SPARE32 spare3[112];  // 保留字段

} IRST_COOPERATION_TGT_REPORT_IFDL1;

// 主题 标 识 符: IRST_cooperation_tgt_report_IFDL2
// 主题 名    称: 光雷协同目标参数报告_IFDL2
// 主题 编    码: 3800
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 450
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    SPARE8 spare2[3];  // 保留字段

    // 标识符:irst_target_acount
    // 名  称:光雷航迹目标数目
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:9
    // 起始位:0
    UINT8 irst_target_acount;

    // 标识符:irst_tgt_det_paras
    // 名  称:光雷目标探测参数
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    IRST_TGT_DET_PARAS_TYPE_DEF irst_tgt_det_paras;

    // 标识符:irst_cooperation_track_paras
    // 名  称:光雷协同航迹目标参数
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    IRST_COOPERATION_TRACK_PARAS_TYPE_DEF irst_cooperation_track_paras[10];

    SPARE32 spare3[112];  // 保留字段

} IRST_COOPERATION_TGT_REPORT_IFDL2;

// 主题 标 识 符: IRST_LOS
// 主题 名    称: IRST传感器LOS参数
// 主题 编    码: 1013
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 10
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:sensor_los_geo
    // 名  称:地理系_传感器LOS
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SENSOR_LOS_GEO_TYPE_DEF sensor_los_geo;

    // 标识符:sensor_los_platform
    // 名  称:机体系_传感器LOS
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    SENSOR_LOS_PLATFORM_TYPE_DEF sensor_los_platform;

    SPARE32 spare1[1];  // 保留字段

} IRST_LOS;

// 主题 标 识 符: IRST_operational_paras
// 主题 名    称: IRST工作参数报告
// 主题 编    码: 1011
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 100
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:security_level
    // 名  称:系统安全_密级
    // 说  明:目前只有非密/秘密两种密级，后续可能会增加更多的密级
    // 单  位:
    // 起始字:3
    // 起始位:24
    UINT32 security_level : 8;

    // 标识符:WOW_main
    // 名  称:轮载状态_主
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 WOW_main : 8;

    // 标识符:MS_phase
    // 名  称:任务阶段
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 MS_phase : 8;

    // 标识符:mission_main_mode
    // 名  称:任务主模式
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 mission_main_mode : 8;

    UINT32 spare1 : 30;  // 保留字段
    // 标识符:cool_state
    // 名  称:制冷状态
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 cool_state : 2;

    // 标识符:irst_cue_state
    // 名  称:IR提示搜索参数状态
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    IRST_CUE_STATE_TYPE_DEF irst_cue_state;

    // 标识符:irst_mode_paras
    // 名  称:IRST工作参数
    // 说  明:
    // 单  位:
    // 起始字:18
    // 起始位:0
    IRST_MODE_PARAS_TYPE_DEF irst_mode_paras;

    UINT32 spare2 : 16;  // 保留字段
    // 标识符:sendstate_818_eots
    // 名  称:情报数据818总线发送状态_EOTS
    // 说  明:
    // 单  位:
    // 起始字:19
    // 起始位:0
    UINT8 sendstate_818_eots[2];

    SPARE32 spare3[1];  // 保留字段

    // 标识符:IR_image_paras
    // 名  称:IR图像参数
    // 说  明:
    // 单  位:
    // 起始字:21
    // 起始位:0
    IR_IMAGE_PARAS_TYPE_DEF IR_image_paras;

    SPARE32 spare4[1];  // 保留字段

    // 标识符:image_volum_IR
    // 名  称:光电成像参数
    // 说  明:
    // 单  位:
    // 起始字:27
    // 起始位:0
    IMAGE_VOLUM_IR_TYPE_DEF image_volum_IR;

    // 标识符:image_volum_IR_actual
    // 名  称:光雷实际成像参数
    // 说  明:
    // 单  位:
    // 起始字:48
    // 起始位:0
    IMAGE_VOLUM_IR_ACTUAL_TYPE_DEF image_volum_IR_actual;

    // 标识符:IR_Transom_paras
    // 名  称:IR光窗参数
    // 说  明:
    // 单  位:
    // 起始字:69
    // 起始位:0
    IR_TRANSOM_PARAS_TYPE_DEF IR_Transom_paras;

    UINT32 spare5 : 8;  // 保留字段
    // 标识符:development_company
    // 名  称:研制厂家
    // 说  明:以此来区分三个厂家
    // 单  位:
    // 起始字:70
    // 起始位:16
    UINT32 development_company : 8;

    // 标识符:IR_LOCATION_MARK
    // 名  称:光电地理定位标志
    // 说  明:
    // 单  位:
    // 起始字:70
    // 起始位:8
    UINT32 IR_LOCATION_MARK : 8;

    // 标识符:IR_INS_ALIGN_STATE
    // 名  称:光电惯导对准状态
    // 说  明:
    // 单  位:
    // 起始字:70
    // 起始位:0
    UINT32 IR_INS_ALIGN_STATE : 8;

    // 标识符:IR_prepare_paras
    // 名  称:准备状态参数
    // 说  明:
    // 单  位:
    // 起始字:71
    // 起始位:0
    IR_PREPARE_PARAS_TYPE_DEF IR_prepare_paras;

    // 标识符:paras_validity
    // 名  称:参数有效性
    // 说  明:
    // 单  位:
    // 起始字:72
    // 起始位:24
    UINT32 paras_validity : 8;

    // 标识符:IR_SENSOR
    // 名  称:光电传感器状态
    // 说  明:
    // 单  位:
    // 起始字:72
    // 起始位:16
    UINT32 IR_SENSOR : 8;

    // 标识符:TGT_TRACK_STATE
    // 名  称:图像跟踪状态
    // 说  明:
    // 单  位:
    // 起始字:72
    // 起始位:8
    UINT32 TGT_TRACK_STATE : 8;

    // 标识符:IR_scan_work_state
    // 名  称:IRST扫描工作状态
    // 说  明:
    // 单  位:
    // 起始字:72
    // 起始位:0
    UINT32 IR_scan_work_state : 8;

    UINT32 spare6 : 8;  // 保留字段
    // 标识符:IRST_Video_BAND
    // 名  称:IRST_区域监视视频带宽
    // 说  明:
    // 单  位:
    // 起始字:73
    // 起始位:16
    UINT32 IRST_Video_BAND : 8;

    // 标识符:cue_on_off
    // 名  称:提示搜索开关
    // 说  明:提示搜索开关。
    // 单  位:
    // 起始字:73
    // 起始位:8
    UINT32 cue_on_off : 8;

    // 标识符:frozen_state
    // 名  称:冻结状态
    // 说  明:
    // 单  位:
    // 起始字:73
    // 起始位:0
    UINT32 frozen_state : 8;

    UINT32 spare7 : 28;  // 保留字段
    // 标识符:TGT_TRACK_ID
    // 名  称:动目标ID
    // 说  明:
    // 单  位:
    // 起始字:74
    // 起始位:0
    UINT32 TGT_TRACK_ID : 4;

    SPARE32 spare8[25];  // 保留字段

} IRST_OPERATIONAL_PARAS;

// 主题 标 识 符: IRST_pixel_paras
// 主题 名    称: IRST像元参数
// 主题 编    码: 2900
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 50
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:total_num_of_pixel
    // 名  称:像元总数
    // 说  明:描述探测器像元数，如IRST探测器总数为640*512。DAS的每个探测器像元总数为512*512。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 total_num_of_pixel;

    // 标识符:total_damage_pixel_num
    // 名  称:坏元总数
    // 说  明:本信号描述光雷探测器坏总数，或每一个DAS探测器坏元总数。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 total_damage_pixel_num;

    // 标识符:ratio
    // 名  称:坏元率
    // 说  明:
    // 单  位:%
    // LSB  :0.000001
    // 起始字:5
    // 起始位:0
    UINT32 ratio;

    // 标识符:block_pixel_paras
    // 名  称:探测器分块像元参数
    // 说  明:该信号组描述探测器阵面各区域的坏元情况。
    //       各探测器阵面按照9方格划分为9块。按照数组元素0--8的顺序，分别表示上左、上、上右、中左、中、中右、下左、下、下右各块的参数。
    // 单  位:
    // 起始字:6
    // 起始位:0
    BLOCK_PIXEL_PARAS_TYPE_DEF block_pixel_paras[9];

    SPARE32 spare1[8];  // 保留字段

} IRST_PIXEL_PARAS;

// 主题 标 识 符: IRST_tgt_dot_correlation_data_report
// 主题 名    称: IRST点迹协同目标关联数据报告
// 主题 编    码: 3886
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 200
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_generated_time
    // 名  称:数据生成时间
    // 说  明:该信号表示传感器数据的产生时间（任务时间），该时间应该尽可能消除采集、计算、传输等带来的延迟的影响，尽可能的与传感器的真实采样时刻一致。消息发布后在后续的传输转发中，该时间不会变化。
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_GENERATED_TIME_TYPE_DEF data_generated_time;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:tgt_total_number
    // 名  称:目标总数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 tgt_total_number;

    // 标识符:IRST_tgt_dot_correlation_info
    // 名  称:IRST点迹协同目标关联信息
    // 说  明:
    // 单  位:
    // 起始字:6
    // 起始位:0
    IRST_TGT_DOT_CORRELATION_INFO_TYPE_DEF IRST_tgt_dot_correlation_info[10];

    SPARE32 spare2[14];  // 保留字段

} IRST_TGT_DOT_CORRELATION_DATA_REPORT;

// 主题 标 识 符: link_member_nav_info_IFDL
// 主题 名    称: 机间数据链编队成员导航信息
// 主题 编    码: 2003
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL;

// 主题 标 识 符: link_member_nav_info_IFDL1
// 主题 名    称: 机间数据链编队成员导航信息1
// 主题 编    码: 3381
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL1;

// 主题 标 识 符: link_member_nav_info_IFDL2
// 主题 名    称: 机间数据链编队成员导航信息2
// 主题 编    码: 3382
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL2;

// 主题 标 识 符: link_member_nav_info_IFDL3
// 主题 名    称: 机间数据链编队成员导航信息3
// 主题 编    码: 4442
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL3;

// 主题 标 识 符: link_member_nav_info_IFDL4
// 主题 名    称: 机间数据链编队成员导航信息4
// 主题 编    码: 4443
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL4;

// 主题 标 识 符: link_member_nav_info_IFDL5
// 主题 名    称: 机间数据链编队成员导航信息5
// 主题 编    码: 4444
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL5;

// 主题 标 识 符: link_member_nav_info_IFDL6
// 主题 名    称: 机间数据链编队成员导航信息6
// 主题 编    码: 4445
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 45
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    // 标识符:link_message_source_destination
    // 名  称:消息源目的端
    // 说  明:与消息收发标识配合使用，当为接收消息时，表示源端；当为发送消息时，表示目的端。
    // 单  位:
    // 起始字:4
    // 起始位:0
    LINK_MESSAGE_SOURCE_DESTINATION_TYPE_DEF link_message_source_destination;

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    // 标识符:member_PPLI_info_IFDL
    // 名  称:成员精确定位与识别信息_IFDL
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MEMBER_PPLI_INFO_IFDL_TYPE_DEF member_PPLI_info_IFDL;

    SPARE32 spare2[2];  // 保留字段

    // 标识符:rnav_measure_paras
    // 名  称:相对导航测量参数
    // 说  明:本机测量目标的TOA、相对方位角、相对俯仰角
    // 单  位:
    // 起始字:35
    // 起始位:0
    RNAV_MEASURE_PARAS_TYPE_DEF rnav_measure_paras;

    SPARE32 spare3[2];  // 保留字段

} LINK_MEMBER_NAV_INFO_IFDL6;

// 主题 标 识 符: link_net_nav_info_IFDL
// 主题 名    称: 机间数据链网内成员导航信息
// 主题 编    码: 4320
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    UINT32 spare3 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    UINT32 spare2 : 8;  // 保留字段

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    SPARE8 spare4[2];  // 保留字段

    // 标识符:member_number
    // 名  称:成员总数
    // 说  明:成员总数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:9
    // 起始位:0
    UINT16 member_number;

    // 标识符:member_PPLI_info_team_IFDL
    // 名  称:成员精确定位与识别信息编队间_IFDL
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    MEMBER_PPLI_INFO_TEAM_IFDL_TYPE_DEF member_PPLI_info_team_IFDL[16];

    SPARE32 spare5[86];  // 保留字段

} LINK_NET_NAV_INFO_IFDL;

// 主题 标 识 符: link_net_nav_info_IFDL1
// 主题 名    称: 机间数据链网内成员导航信息1
// 主题 编    码: 4321
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 编队成员发送的位置和姿态消息
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:link_message_tr_route
    // 名  称:消息收发链路
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 link_message_tr_route : 8;

    UINT32 spare3 : 16;  // 保留字段
    // 标识符:link_message_tr_flag
    // 名  称:消息收发标识
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 link_message_tr_flag : 8;

    UINT32 spare2 : 8;  // 保留字段

    // 标识符:link_message_tr_time
    // 名  称:消息收发时间
    // 说  明:数据链消息从链路上接收/发送的时间，包含当时的网络时间和任务时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    LINK_MESSAGE_TR_TIME_TYPE_DEF link_message_tr_time;

    SPARE8 spare4[2];  // 保留字段

    // 标识符:member_number
    // 名  称:成员总数
    // 说  明:成员总数
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:9
    // 起始位:0
    UINT16 member_number;

    // 标识符:member_PPLI_info_team_IFDL
    // 名  称:成员精确定位与识别信息编队间_IFDL
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    MEMBER_PPLI_INFO_TEAM_IFDL_TYPE_DEF member_PPLI_info_team_IFDL[16];

    SPARE32 spare5[86];  // 保留字段

} LINK_NET_NAV_INFO_IFDL1;

// 主题 标 识 符: list_knob_cmd
// 主题 名    称: 俯仰滚轮指令
// 主题 编    码: 3209
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 8
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 8;  // 保留字段
    // 标识符:knob_sum_value
    // 名  称:滚轮积分值
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:8
    INT32 knob_sum_value : 16;

    // 标识符:el_chg_tag
    // 名  称:俯仰修改标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 el_chg_tag : 8;

    // 标识符:delt_el_los
    // 名  称:俯仰中心变化增量单位值
    // 说  明:
    // 单  位:Deg
    // LSB  :0.00001
    // 起始字:4
    // 起始位:0
    INT32 delt_el_los;

    SPARE32 spare2[3];  // 保留字段

} LIST_KNOB_CMD;

// 主题 标 识 符: load_int_check_report
// 主题 名    称: 加载综合校验报告
// 主题 编    码: 3412
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 303
// 主题 说    明: 用于对各功能子域/单元反馈的文件校验结果进行判断后，统一发布综合数据校验结果信息；同时也用于画面加载状态及倒计时显示。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:DataLoadCheckResult
    // 名  称:数据加载校验结果
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATALOADCHECKRESULT_TYPE_DEF DataLoadCheckResult[100];

} LOAD_INT_CHECK_REPORT;

// 主题 标 识 符: LOAD_operational_paras_OMP
// 主题 名    称: 软件加载工作参数报告_OMP
// 主题 编    码: 3834
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 490
// 主题 说    明: 利用空位新增任务系统运行模态信号，表征当前是否需要切换到维护加载态执行软件在线加载。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:ms_sys_main_mode
    // 名  称:任务系统运行模态
    // 说  明:描述任务系统的运行模态，
    //       分为正常运行态和维护加载态，正常运行时为NORMAL
    //       仅当飞管系统进入OFP加载模式后，任务系统启动进入维护加载态，由该信号触发。
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 ms_sys_main_mode : 8;

    // 标识符:sys_network_state_OMP
    // 名  称:系统网络状态_OMP
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    SYS_NETWORK_STATE_OMP_TYPE_DEF sys_network_state_OMP[128];

    SPARE32 spare2[102];  // 保留字段

} LOAD_OPERATIONAL_PARAS_OMP;

// 主题 标 识 符: LSR_calibrate_paras
// 主题 名    称: 激光校轴参数
// 主题 编    码: 2030
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 10
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:LSR_test_state
    // 名  称:激光测试状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 LSR_test_state : 8;

    // 标识符:calibrate_mode_state
    // 名  称:校轴模式状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 calibrate_mode_state : 8;

    // 标识符:calibirate_paras_cureent
    // 名  称:光轴偏差参数_当前值
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    CALIBIRATE_PARAS_CUREENT_TYPE_DEF calibirate_paras_cureent;

    // 标识符:calibirate_paras_test
    // 名  称:光轴偏差参数_测试值
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    CALIBIRATE_PARAS_TEST_TYPE_DEF calibirate_paras_test;

    SPARE32 spare2[4];  // 保留字段

} LSR_CALIBRATE_PARAS;

// 主题 标 识 符: mission_event_report
// 主题 名    称: 战术任务事件报告
// 主题 编    码: 412
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 32
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:WU_main
    // 名  称:起落架状态_主
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:24
    UINT32 WU_main : 8;

    // 标识符:WOW_main
    // 名  称:轮载状态_主
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 WOW_main : 8;

    // 标识符:MS_phase
    // 名  称:任务阶段
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 MS_phase : 8;

    // 标识符:mission_main_mode
    // 名  称:任务主模式
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 mission_main_mode : 8;

    // 标识符:ms_event_update_counter
    // 名  称:任务事件更新计数
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断“任务事件”信号组及“本机任务事件”信号是否发生变化，即是否有新的需要记录的任务事件发生。
    //       计数器初始化=0，此时表示没有发送过任何需要记录的任务事件，当“任务事件”信号组或“本机任务事件”信号中定义的任何任务事件发生时，计数器每次增加1。
    //       若计数器增加到最大值时有新的事件发生则重新从1开始计数。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:4
    // 起始位:16
    UINT32 ms_event_update_counter : 16;

    // 标识符:GS_state
    // 名  称:地速状态
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 GS_state : 8;

    // 标识符:ET_mode
    // 名  称:嵌入式训练模式
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 ET_mode : 8;

    // 标识符:mission_sequence
    // 名  称:任务序列
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    MISSION_SEQUENCE_TYPE_DEF mission_sequence;

    // 标识符:mission_event
    // 名  称:任务事件
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    MISSION_EVENT_TYPE_DEF mission_event;

    UINT32 spare1 : 16;  // 保留字段
    // 标识符:is_EOF_state
    // 名  称:EOF状态标志
    // 说  明:EOF状态标志
    //       飞机速度降低到50km/h以下，且主轮载信号从空中变为地面，当前进入EOF状态
    // 单  位:
    // 起始字:29
    // 起始位:8
    UINT32 is_EOF_state : 8;

    // 标识符:main_plan_on_off
    // 名  称:主计划开关
    // 说  明:
    // 单  位:
    // 起始字:29
    // 起始位:0
    UINT32 main_plan_on_off : 8;

    UINT32 spare2 : 12;  // 保留字段
    // 标识符:VMS_AC_ID
    // 名  称:VMS_飞机ID
    // 说  明:0 歼-20飞机01状态01-05架
    //       1 歼-20飞机01状态06架起
    //       2 歼-20飞机02状态，不装航炮
    //       3 歼-20飞机02状态，装航炮
    //       4 歼-20双座机，配装涡扇-10C
    //       5 歼-20双座机，配装涡扇-15
    //       6 歼-20A飞机，配装涡扇-10C
    //       7 歼-20A飞机，配装涡扇-15
    // 单  位:
    // 起始字:30
    // 起始位:16
    UINT32 VMS_AC_ID : 4;

    // 标识符:VMS1394_AC_Type_ID
    // 名  称:VMS1394_飞机构型
    // 说  明:
    // 单  位:
    // 起始字:30
    // 起始位:0
    UINT32 VMS1394_AC_Type_ID : 16;

    SPARE32 spare3[1];  // 保留字段

} MISSION_EVENT_REPORT;

// 主题 标 识 符: NAV_paras
// 主题 名    称: 导航参数报告
// 主题 编    码: 439
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:NAV_paras_validity
    // 名  称:导航参数_有效性
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    NAV_PARAS_VALIDITY_TYPE_DEF NAV_paras_validity;

    // 标识符:MLS_station_az
    // 名  称:微波站方位
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    MLS_STATION_AZ_TYPE_DEF MLS_station_az;

    // 标识符:ILS_station_az
    // 名  称:仪表站方位
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:0
    ILS_STATION_AZ_TYPE_DEF ILS_station_az;

    // 标识符:FAF_point_ground_distance
    // 名  称:FAF地面距离
    // 说  明:载机与FAF点的地面距离
    // 单  位:
    // 起始字:15
    // 起始位:0
    FAF_POINT_GROUND_DISTANCE_TYPE_DEF FAF_point_ground_distance;

    // 标识符:FAF_point_az
    // 名  称:FAF点方位
    // 说  明:FAF点到载机位置的连线与真北的夹角
    // 单  位:
    // 起始字:16
    // 起始位:0
    FAF_POINT_AZ_TYPE_DEF FAF_point_az;

    // 标识符:turn_point_ground_distance
    // 名  称:转弯点地面距离
    // 说  明:转弯点与载机位置的地面距离
    // 单  位:
    // 起始字:17
    // 起始位:0
    TURN_POINT_GROUND_DISTANCE_TYPE_DEF turn_point_ground_distance;

    // 标识符:turn_point_az
    // 名  称:转弯点方位
    // 说  明:转弯点到载机位置的连线与真北的夹角
    // 单  位:
    // 起始字:18
    // 起始位:0
    TURN_POINT_AZ_TYPE_DEF turn_point_az;

    // 标识符:steering_point_ground_distance
    // 名  称:操纵点地面距离
    // 说  明:载机与操纵点的地面距离
    // 单  位:
    // 起始字:19
    // 起始位:0
    STEERING_POINT_GROUND_DISTANCE_TYPE_DEF steering_point_ground_distance;

    // 标识符:steering_point_slant_distance
    // 名  称:操纵点斜距
    // 说  明:载机与操纵点的斜距
    // 单  位:
    // 起始字:20
    // 起始位:0
    STEERING_POINT_SLANT_DISTANCE_TYPE_DEF steering_point_slant_distance;

    // 标识符:steering_point_plat_NW_distance
    // 名  称:操纵点平台系北西距离
    // 说  明:载机与操纵点的距离在平台系的北西向分量
    // 单  位:
    // 起始字:21
    // 起始位:0
    STEERING_POINT_PLAT_NW_DISTANCE_TYPE_DEF steering_point_plat_NW_distance;

    // 标识符:steering_point_plat_up_distance
    // 名  称:操纵点平台系天向距离
    // 说  明:载机与操纵点的距离在平台系的天向分量
    // 单  位:
    // 起始字:23
    // 起始位:0
    STEERING_POINT_PLAT_UP_DISTANCE_TYPE_DEF steering_point_plat_up_distance;

    // 标识符:steering_point_body_azel
    // 名  称:操纵点机体系方位俯仰
    // 说  明:操纵点相对于载机的方位俯仰在机体系的投影。
    // 单  位:
    // 起始字:24
    // 起始位:0
    STEERING_POINT_BODY_AZEL_TYPE_DEF steering_point_body_azel;

    // 标识符:steering_point_plat_el
    // 名  称:操纵点平台系俯仰
    // 说  明:操纵点相对于载机的俯仰在平台系的投影。
    // 单  位:
    // 起始字:26
    // 起始位:0
    STEERING_POINT_PLAT_EL_TYPE_DEF steering_point_plat_el;

    // 标识符:steering_point_plat_az
    // 名  称:操纵点平台系方位
    // 说  明:操纵点相对于载机的方位在平台系的投影。
    // 单  位:
    // 起始字:27
    // 起始位:0
    STEERING_POINT_PLAT_AZ_TYPE_DEF steering_point_plat_az;

    // 标识符:steering_point_OAP_ground_distance
    // 名  称:操纵点OAP地面距离
    // 说  明:载机与操纵点的OAP的地面距离
    // 单  位:
    // 起始字:28
    // 起始位:0
    STEERING_POINT_OAP_GROUND_DISTANCE_TYPE_DEF steering_point_OAP_ground_distance;

    // 标识符:steering_point_OAP_slant_distance
    // 名  称:操纵点OAP斜距
    // 说  明:载机与操纵点的OAP的斜距
    // 单  位:
    // 起始字:29
    // 起始位:0
    STEERING_POINT_OAP_SLANT_DISTANCE_TYPE_DEF steering_point_OAP_slant_distance;

    // 标识符:steering_point_OAP_plat_NW_distance
    // 名  称:操纵点OAP平台系北西距离
    // 说  明:载机与操纵点的OAP的距离在平台系的北西分量
    // 单  位:
    // 起始字:30
    // 起始位:0
    STEERING_POINT_OAP_PLAT_NW_DISTANCE_TYPE_DEF steering_point_OAP_plat_NW_distance;

    // 标识符:steering_point_OAP_plat_up_distance
    // 名  称:操纵点OAP平台系天向距离
    // 说  明:载机与操纵点的OAP的距离在平台系的天向分量
    // 单  位:
    // 起始字:32
    // 起始位:0
    STEERING_POINT_OAP_PLAT_UP_DISTANCE_TYPE_DEF steering_point_OAP_plat_up_distance;

    // 标识符:steering_point_OAP_body_azel
    // 名  称:操纵点OAP机体系方位俯仰
    // 说  明:操纵点的OAP相对于载机的方位俯仰在机体系的投影。
    // 单  位:
    // 起始字:33
    // 起始位:0
    STEERING_POINT_OAP_BODY_AZEL_TYPE_DEF steering_point_OAP_body_azel;

    // 标识符:steering_point_OAP_plat_az
    // 名  称:操纵点OAP平台系方位
    // 说  明:操纵点的OAP相对于载机的方位在平台系的投影。
    // 单  位:
    // 起始字:35
    // 起始位:0
    STEERING_POINT_OAP_PLAT_AZ_TYPE_DEF steering_point_OAP_plat_az;

    // 标识符:steering_point_OAP_plat_el
    // 名  称:操纵点OAP平台系俯仰
    // 说  明:操纵点的OAP相对于载机的俯仰在平台系的投影。
    // 单  位:
    // 起始字:36
    // 起始位:0
    STEERING_POINT_OAP_PLAT_EL_TYPE_DEF steering_point_OAP_plat_el;

    // 标识符:TTG
    // 名  称:预计到达所需时间
    // 说  明:
    // 单  位:
    // 起始字:37
    // 起始位:0
    TTG_TYPE_DEF TTG;

    // 标识符:ETA
    // 名  称:预计到达时刻
    // 说  明:
    // 单  位:
    // 起始字:39
    // 起始位:0
    ETA_TYPE_DEF ETA;

    // 标识符:deltaTOT
    // 名  称:预计到达时刻差
    // 说  明:
    // 单  位:
    // 起始字:41
    // 起始位:0
    DELTATOT_TYPE_DEF deltaTOT;

    // 标识符:ERF
    // 名  称:预计剩余油量
    // 说  明:
    // 单  位:
    // 起始字:43
    // 起始位:0
    ERF_TYPE_DEF ERF;

    // 标识符:SP_type_course_offset
    // 名  称:操纵点航线偏差距离
    // 说  明:载机位置相对于操纵点类型航线的距离。飞机在选择航线正向的左边为正。
    // 单  位:
    // 起始字:44
    // 起始位:0
    SP_TYPE_COURSE_OFFSET_TYPE_DEF SP_type_course_offset;

    // 标识符:TACAN_type_course_offset
    // 名  称:塔康航线偏差距离
    // 说  明:载机位置相对于塔康类型航线的距离。飞机在选择航线正向的左边为正。
    // 单  位:
    // 起始字:45
    // 起始位:0
    TACAN_TYPE_COURSE_OFFSET_TYPE_DEF TACAN_type_course_offset;

    // 标识符:steering_point_localizer_dev
    // 名  称:操纵点方位偏差
    // 说  明:载机位置的相对于操纵点类型选择航线的方位偏差。
    // 单  位:
    // 起始字:46
    // 起始位:0
    STEERING_POINT_LOCALIZER_DEV_TYPE_DEF steering_point_localizer_dev;

    // 标识符:SCA_gls_dev
    // 名  称:自主着陆下滑道偏差
    // 说  明:
    // 单  位:
    // 起始字:47
    // 起始位:0
    SCA_GLS_DEV_TYPE_DEF SCA_gls_dev;

    // 标识符:steer_direct_desired_alt
    // 名  称:期望高度指引
    // 说  明:
    // 单  位:
    // 起始字:48
    // 起始位:0
    STEER_DIRECT_DESIRED_ALT_TYPE_DEF steer_direct_desired_alt;

    // 标识符:steer_direct_desired_vel
    // 名  称:期望速度指引
    // 说  明:
    // 单  位:
    // 起始字:51
    // 起始位:0
    STEER_DIRECT_DESIRED_VEL_TYPE_DEF steer_direct_desired_vel;

    // 标识符:steer_direct_desired_heading
    // 名  称:期望航向指引
    // 说  明:
    // 单  位:
    // 起始字:53
    // 起始位:0
    STEER_DIRECT_DESIRED_HEADING_TYPE_DEF steer_direct_desired_heading;

    // 标识符:steer_direct_desired_track
    // 名  称:期望航迹指引
    // 说  明:
    // 单  位:
    // 起始字:54
    // 起始位:0
    STEER_DIRECT_DESIRED_TRACK_TYPE_DEF steer_direct_desired_track;

    // 标识符:nav_heading_steer_direct
    // 名  称:航向操纵指引杆
    // 说  明:
    // 单  位:
    // 起始字:56
    // 起始位:0
    NAV_HEADING_STEER_DIRECT_TYPE_DEF nav_heading_steer_direct;

    // 标识符:flight_director_cue
    // 名  称:飞行操纵指引符
    // 说  明:
    // 单  位:
    // 起始字:57
    // 起始位:0
    FLIGHT_DIRECTOR_CUE_TYPE_DEF flight_director_cue;

    // 标识符:bullseye_point_plat_az
    // 名  称:波塞点平台系方位
    // 说  明:载机相对于当前选择的波塞点的方位在平台系的投影。（即以波塞点为原点，从波塞点到载机位置的连线与真北的夹角）
    // 单  位:
    // 起始字:59
    // 起始位:0
    BULLSEYE_POINT_PLAT_AZ_TYPE_DEF bullseye_point_plat_az;

    // 标识符:bullseye_point_ground_distance
    // 名  称:波塞点地面距离
    // 说  明:当前选择波塞点与载机间的地面距离
    // 单  位:
    // 起始字:60
    // 起始位:0
    BULLSEYE_POINT_GROUND_DISTANCE_TYPE_DEF bullseye_point_ground_distance;

    // 标识符:bingo_fuel
    // 名  称:bingo燃油量
    // 说  明:
    // 单  位:
    // 起始字:61
    // 起始位:0
    BINGO_FUEL_TYPE_DEF bingo_fuel;

    // 标识符:nav_point_ground_distance
    // 名  称:导航点地面距离
    // 说  明:当前导航点的地面距离
    // 单  位:
    // 起始字:62
    // 起始位:0
    NAV_POINT_GROUND_DISTANCE_TYPE_DEF nav_point_ground_distance;

    // 标识符:nav_point_plat_az
    // 名  称:导航点平台系方位
    // 说  明:导航点相对于载机的方位在平台系的投影。
    // 单  位:
    // 起始字:63
    // 起始位:0
    NAV_POINT_PLAT_AZ_TYPE_DEF nav_point_plat_az;

    // 标识符:nav_point_plat_el
    // 名  称:导航点平台系俯仰
    // 说  明:导航点相对于载机的俯仰在平台系的投影。
    // 单  位:
    // 起始字:64
    // 起始位:0
    NAV_POINT_PLAT_EL_TYPE_DEF nav_point_plat_el;

    // 标识符:EnableMark_AP_PreGLS
    // 名  称:允许标志_自动驾驶预备GLS
    // 说  明:
    // 单  位:
    // 起始字:65
    // 起始位:24
    UINT32 EnableMark_AP_PreGLS : 8;

    // 标识符:EnableMark_AT_TOT
    // 名  称:允许标志_自动油门定时到达
    // 说  明:
    // 单  位:
    // 起始字:65
    // 起始位:16
    UINT32 EnableMark_AT_TOT : 8;

    // 标识符:AT_TOT_GS
    // 名  称:定时到达期望地速
    // 说  明:
    // 单  位:km/h
    // LSB  :1
    // 起始字:65
    // 起始位:0
    INT32 AT_TOT_GS : 16;

    // 标识符:stpt_position
    // 名  称:操纵点位置
    // 说  明:
    // 单  位:
    // 起始字:66
    // 起始位:0
    STPT_POSITION_TYPE_DEF stpt_position;

    // 标识符:SPOI_nav_info
    // 名  称:关注操纵点导航信息
    // 说  明:
    // 单  位:
    // 起始字:70
    // 起始位:0
    SPOI_NAV_INFO_TYPE_DEF SPOI_nav_info;

    // 标识符:fast_climb_paras
    // 名  称:最速爬升参数
    // 说  明:
    // 单  位:
    // 起始字:90
    // 起始位:0
    FAST_CLIMB_PARAS_TYPE_DEF fast_climb_paras;

    SPARE32 spare1[403];  // 保留字段

} NAV_PARAS;

// 主题 标 识 符: NAV_state
// 主题 名    称: 导航状态报告
// 主题 编    码: 436
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 100
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:apr_phase
    // 名  称:进场着陆阶段
    // 说  明:进场着陆的各个阶段
    // 单  位:
    // 起始字:3
    // 起始位:24
    UINT32 apr_phase : 8;

    // 标识符:return_mode
    // 名  称:返航方式
    // 说  明:返航的方式
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 return_mode : 8;

    // 标识符:cruise_mode
    // 名  称:巡航方式
    // 说  明:巡航的方式
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 cruise_mode : 8;

    // 标识符:nav_submode
    // 名  称:导航子模式
    // 说  明:导航的子模式
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 nav_submode : 8;

    // 标识符:sp_number
    // 名  称:操纵点编号
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:16
    UINT32 sp_number : 16;

    // 标识符:fly_plan
    // 名  称:飞行计划号
    // 说  明:飞行计划，包括A~K（I除外）计划、标记点、波塞点、标定点、初始位置、最近机场、机场
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 fly_plan : 8;

    // 标识符:sp_change_mode
    // 名  称:操纵点切换方式
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 sp_change_mode : 8;

    // 标识符:route_point_name
    // 名  称:航线点名称
    // 说  明:
    // 单  位:
    // 起始字:5
    // 起始位:0
    ROUTE_POINT_NAME_TYPE_DEF route_point_name;

    // 标识符:faf_turn_dir_mode
    // 名  称:进场定位转弯方向模式
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:24
    UINT32 faf_turn_dir_mode : 8;

    // 标识符:APR_sensor_selected
    // 名  称:进场着陆传感器选择
    // 说  明:
    // 单  位:
    // 起始字:8
    // 起始位:16
    UINT32 APR_sensor_selected : 8;

    // 标识符:CDI_types
    // 名  称:航线偏差指引类型
    // 说  明:航线偏差指引类型，表示航线偏差指示符根据何种传感器数据指示。
    // 单  位:
    // 起始字:8
    // 起始位:8
    UINT32 CDI_types : 8;

    // 标识符:router_point_types
    // 名  称:航线点类型
    // 说  明:航线点类型，包括了航路点的“常规、塔康、机场、参考”点类型，及攻击投放计划中的“投放、目标”点类型。协同点和标记点引入飞行计划后作为常规点。
    // 单  位:
    // 起始字:8
    // 起始位:0
    UINT32 router_point_types : 8;

    SPARE8 spare1;  // 保留字段

    // 标识符:FAF_turn_direction
    // 名  称:进场定位转弯方向
    // 说  明:FAF阶段的转弯方向。
    // 单  位:
    // 起始字:9
    // 起始位:16
    BOOL_8 FAF_turn_direction;

    // 标识符:validity_sel_true_course
    // 名  称:有效性_选择真航线
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:8
    BOOL_8 validity_sel_true_course;

    // 标识符:validity_sel_mag_course
    // 名  称:有效性_选择磁航线
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    BOOL_8 validity_sel_mag_course;

    // 标识符:sel_mag_course
    // 名  称:选择磁航线
    // 说  明:[0,360)
    //       选择磁航线相对于磁北顺时针为正
    // 单  位:
    // 起始字:10
    // 起始位:0
    SEL_MAG_COURSE_TYPE_DEF sel_mag_course;

    // 标识符:sel_true_course
    // 名  称:选择真航线
    // 说  明:[0,360)
    //       选择航线相对于真北的夹角，顺时针为正
    // 单  位:
    // 起始字:11
    // 起始位:0
    SEL_TRUE_COURSE_TYPE_DEF sel_true_course;

    UINT32 spare3 : 8;  // 保留字段
    // 标识符:nav_point_num
    // 名  称:导航点编号
    // 说  明:1、当前 操纵点为连续点(不为01点)，且操纵点切换方式为自动，则导航点编号为长航线内部插点顺序编号(1-40)，当前导航点即正在飞往的内部点；
    //       2、当前为战斗巡逻方式，当前操纵点为战斗巡逻点，导航点编号为战斗巡逻点的转折点编号(基点为1，热段终点为2，然后按顺序编号)，当前导航点即正在飞往的战斗巡逻点转折点。
    // 单  位:
    // LSB  :1
    // 起始字:12
    // 起始位:16
    UINT32 nav_point_num : 8;

    // 标识符:tacan_paras_mode
    // 名  称:塔康参数控制方式
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:8
    UINT32 tacan_paras_mode : 8;

    UINT32 spare2 : 8;  // 保留字段

    // 标识符:cap_phase
    // 名  称:战斗巡逻阶段
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:24
    UINT32 cap_phase : 8;

    // 标识符:bulls_eye_num
    // 名  称:波塞点编号
    // 说  明:表征波塞点编号数值
    // 单  位:
    // LSB  :1
    // 起始字:13
    // 起始位:16
    UINT32 bulls_eye_num : 8;

    // 标识符:bullseye_on_off
    // 名  称:波塞点功能_开关
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:8
    UINT32 bullseye_on_off : 8;

    // 标识符:validity_bullseye_func
    // 名  称:有效性_波塞点功能
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    UINT32 validity_bullseye_func : 8;

    SPARE8 spare4;  // 保留字段

    // 标识符:APAT_Link
    // 名  称:自动驾驶自动油门关联状态
    // 说  明:
    // 单  位:
    // 起始字:14
    // 起始位:16
    BOOL_8 APAT_Link;

    // 标识符:airport_num
    // 名  称:机场号
    // 说  明:机场号表示范围为0~999
    //       当前航线点类型或当前航路点类型不为机场时，则机场号=0；
    //       当前航线点类型或当前航路点类型为机场时，则根据机场号赋相应值，范围为1~999
    // 单  位:
    // LSB  :1
    // 起始字:14
    // 起始位:0
    UINT16 airport_num;

    // 标识符:bingo_tgt_para
    // 名  称:bingo目标参数
    // 说  明:
    // 单  位:
    // 起始字:15
    // 起始位:0
    BINGO_TGT_PARA_TYPE_DEF bingo_tgt_para;

    // 标识符:fast_climb_state
    // 名  称:最速爬升状态
    // 说  明:
    // 单  位:
    // 起始字:23
    // 起始位:0
    FAST_CLIMB_STATE_TYPE_DEF fast_climb_state;

    SPARE32 spare5[75];  // 保留字段

} NAV_STATE;

// 主题 标 识 符: NORMAL_Image_818
// 主题 名    称: 通用原始图像
// 主题 编    码: 4367
// 主题 类    型: 流数据包
// 主题 格式类型: 应用主题
// 主题 长    度: 490
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:1
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:A818_Image_common_paras
    // 名  称:图像任务信息
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    A818_IMAGE_COMMON_PARAS_TYPE_DEF A818_Image_common_paras;

    SPARE32 spare1[3];  // 保留字段

    // 标识符:image_paras
    // 名  称:图像参数
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    IMAGE_PARAS_TYPE_DEF image_paras;

    SPARE32 spare2[9];  // 保留字段

    // 标识符:image_inner_paras
    // 名  称:图像应用参数
    // 说  明:
    // 单  位:
    // 起始字:100
    // 起始位:0
    IMAGE_INNER_PARAS_TYPE_DEF image_inner_paras[256];

    SPARE32 spare3[134];  // 保留字段

} NORMAL_IMAGE_818;

// 主题 标 识 符: PHM_Data_Event_MS_SUB
// 主题 名    称: 健康管理_Event数据_MS_SUB
// 主题 编    码: 2066
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 99
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:EventData_total_list_number
    // 名  称:EventData_总条数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 EventData_total_list_number;

    SPARE32 spare2[3];  // 保留字段

    // 标识符:EventData_Data_Item_MS_SUB
    // 名  称:EventData数据项_MS_SUB
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    EVENTDATA_DATA_ITEM_MS_SUB_TYPE_DEF EventData_Data_Item_MS_SUB[6];

} PHM_DATA_EVENT_MS_SUB;

// 主题 标 识 符: PHM_Data_HMC_MS_SUB
// 主题 名    称: 健康管理_HMC数据_MS_SUB
// 主题 编    码: 2065
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 59
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:HMC_total_list_number
    // 名  称:HMC_总条数
    // 说  明:
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT16 HMC_total_list_number;

    SPARE32 spare2[3];  // 保留字段

    // 标识符:HMC_Data_Item_MS_Sub
    // 名  称:HMC数据项_任务子系统
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    HMC_DATA_ITEM_MS_SUB_TYPE_DEF HMC_Data_Item_MS_Sub[10];

} PHM_DATA_HMC_MS_SUB;

// 主题 标 识 符: PHM_Data_Raw_IRST
// 主题 名    称: 健康管理_Raw数据_IRST
// 主题 编    码: 2076
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 110
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:RawData_MsSubSys_IRST
    // 名  称:RawData_任务子系统_IRST
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    RAWDATA_MSSUBSYS_IRST_TYPE_DEF RawData_MsSubSys_IRST;

    SPARE32 spare1[11];  // 保留字段

} PHM_DATA_RAW_IRST;

// 主题 标 识 符: PHM_report
// 主题 名    称: 健康管理报告
// 主题 编    码: 704
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:subsys_state_info
    // 名  称:子系统状态信息
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SUBSYS_STATE_INFO_TYPE_DEF subsys_state_info[60];

    SPARE32 spare1[193];  // 保留字段

} PHM_REPORT;

// 主题 标 识 符: Reconnaised_area_IR_2GCS_Event
// 主题 名    称: 侦察覆盖区域参数_IR
// 主题 编    码: 4558
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 95
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:A818_Image_common_paras
    // 名  称:图像任务信息
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    A818_IMAGE_COMMON_PARAS_TYPE_DEF A818_Image_common_paras;

    SPARE32 spare1[1];  // 保留字段

    // 标识符:image_paras_transit
    // 名  称:图像参数_下传
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    IMAGE_PARAS_TRANSIT_TYPE_DEF image_paras_transit;

    // 标识符:AC_ins_info
    // 名  称:飞机惯导信息
    // 说  明:
    // 单  位:
    // 起始字:65
    // 起始位:0
    AC_INS_INFO_TYPE_DEF AC_ins_info;

} RECONNAISED_AREA_IR_2GCS_EVENT;

// 主题 标 识 符: Reconnaised_area_TV_2GCS_Event
// 主题 名    称: 侦察覆盖区域参数_TV
// 主题 编    码: 4557
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 95
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:update_counter
    // 名  称:更新计数器
    // 说  明:无量纲，无符号位的整形数值。
    //       更新标志，用于判断该信号组内是否有信号发生了变化。
    //       初始时从1开始，每变化一次时，加1。
    // 单  位:
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT32 update_counter;

    // 标识符:A818_Image_common_paras
    // 名  称:图像任务信息
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    A818_IMAGE_COMMON_PARAS_TYPE_DEF A818_Image_common_paras;

    SPARE32 spare1[1];  // 保留字段

    // 标识符:image_paras_transit
    // 名  称:图像参数_下传
    // 说  明:
    // 单  位:
    // 起始字:9
    // 起始位:0
    IMAGE_PARAS_TRANSIT_TYPE_DEF image_paras_transit;

    // 标识符:AC_ins_info
    // 名  称:飞机惯导信息
    // 说  明:
    // 单  位:
    // 起始字:65
    // 起始位:0
    AC_INS_INFO_TYPE_DEF AC_ins_info;

} RECONNAISED_AREA_TV_2GCS_EVENT;

// 主题 标 识 符: slave_paras
// 主题 名    称: 随动控制参数
// 主题 编    码: 1015
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 200
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:burst_time
    // 名  称:时间_猝发测距时间间隔
    // 说  明:[0,99]sec
    // 单  位:Sec
    // LSB  :1
    // 起始字:3
    // 起始位:24
    UINT32 burst_time : 8;

    // 标识符:validity_slave_TGT
    // 名  称:有效性_随动目标参数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:16
    UINT32 validity_slave_TGT : 8;

    // 标识符:validity_slave_LOS
    // 名  称:有效性_随动LOS参数
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 validity_slave_LOS : 8;

    // 标识符:slave_main_sensor
    // 名  称:随动主传感器
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 slave_main_sensor : 8;

    // 标识符:slave_los_paras
    // 名  称:随动LOS参数
    // 说  明:随动于LOS的方位和俯仰角
    // 单  位:
    // 起始字:4
    // 起始位:0
    SLAVE_LOS_PARAS_TYPE_DEF slave_los_paras;

    // 标识符:slave_tgt_paras
    // 名  称:随动目标参数
    // 说  明:以目标为中心的随动参数。
    // 单  位:
    // 起始字:6
    // 起始位:0
    SLAVE_TGT_PARAS_TYPE_DEF slave_tgt_paras;

    SPARE32 spare1[184];  // 保留字段

} SLAVE_PARAS;

// 主题 标 识 符: special_maint_data
// 主题 名    称: 特殊维护数据
// 主题 编    码: 955
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 170
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    UINT32 spare2 : 16;  // 保留字段
    // 标识符:special_maint_data_type
    // 名  称:特殊维护参数类型
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:8
    UINT32 special_maint_data_type : 8;

    UINT32 spare1 : 8;  // 保留字段

    // 标识符:special_maint_para
    // 名  称:特殊维护参数
    // 说  明:特殊维护参数包括汉字、字母、数字、符号等
    // 单  位:
    // 起始字:5
    // 起始位:0
    char_8 special_maint_para[660];

} SPECIAL_MAINT_DATA;

// 主题 标 识 符: SPI_paras
// 主题 名    称: 系统关注点信息
// 主题 编    码: 3037
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 30
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:spi_location
    // 名  称:SPI点位置
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SPI_LOCATION_TYPE_DEF spi_location;

    SPARE32 spare1[23];  // 保留字段

} SPI_PARAS;

// 主题 标 识 符: stream_data_file
// 主题 名    称: 流数据_文件
// 主题 编    码: 462
// 主题 类    型: 流数据包
// 主题 格式类型: 应用主题
// 主题 长    度: 46
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:stream_info_file
    // 名  称:文件流信息
    // 说  明:描述当前传输的流数据文件信息
    // 单  位:
    // 起始字:3
    // 起始位:0
    STREAM_INFO_FILE_TYPE_DEF stream_info_file;

} STREAM_DATA_FILE;

// 主题 标 识 符: SW_config_info_report
// 主题 名    称: 软件配置信息报告
// 主题 编    码: 390
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 190
// 主题 说    明: 本主题包括了子系统/子域的软件配置信息，同时，加载到子系统内部的配置库信息也作为软件配置信息上报。该主题提供了必要的信息用于校验软件（OFP和MDF）和硬件的匹配性。该主题也提供了一种记录软件和数据库配置信息的机制。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    DATA_BLOCK_TRANS_MARK_TYPE_DEF data_block_trans_mark;

    SPARE8 spare1[2];  // 保留字段

    // 标识符:config_item_count
    // 名  称:配置项数量
    // 说  明:
    // 单  位:
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT16 config_item_count;

    // 标识符:SW_config_info
    // 名  称:软件配置信息
    // 说  明:数据库信息以软件配置信息的格式一同发送，发送时软件CSCI信息，再发送数据库配置信息。
    //       软件版本信息，包含以下信息：
    //       1、数组元素有效性：表征该数组元素是否有效，当不需占用全部的数组元素时，未占用的元素该信号置无效。
    //       2、软件配置项代码：8位ASCII数字字母。
    //       3、软件名称：按标准发布的软件名称填写，不超过20个字符。
    //       4、版本号：软件当前版本信息，按统一格式编码。
    //       5、校验码：软件在地面生成时用于校验软件正确性的编码。
    //       6、加载时间：软件加载到机上的日历时间的年月日和时间。
    // 单  位:
    // 起始字:5
    // 起始位:0
    SW_CONFIG_INFO_TYPE_DEF SW_config_info[7];

    SPARE32 spare2[3];  // 保留字段

} SW_CONFIG_INFO_REPORT;

// 主题 标 识 符: SW_load_state_report_OMP
// 主题 名    称: 软件加载状态报告_OMP
// 主题 编    码: 2064
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 40
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:loading_type
    // 名  称:加载类型
    // 说  明:描述文件/数据在的场景类型：
    //       1=在任务系统正常模式下进行的战术任务数据加载；
    //       2=在任务系统维护模式下进行的维护配置数据加载；
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 loading_type : 8;

    // 标识符:SW_CSCI_code
    // 名  称:软件配置项代码
    // 说  明:软件部件的工作单元代码，ASCII字符。
    // 单  位:
    // 起始字:4
    // 起始位:0
    char_8 SW_CSCI_code[8];

    // 标识符:folder_id
    // 名  称:文件夹编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT32 folder_id;

    // 标识符:software_name
    // 名  称:软件名称
    // 说  明:软件名称，不超过20个字符（汉字、数字、字母、符号）
    // 单  位:
    // 起始字:7
    // 起始位:0
    char_8 software_name[40];

    // 标识符:ver_number
    // 名  称:版本号
    // 说  明:软件、硬件、数据库、驱动的版本号均由24个字母数字组成。ASCII码。
    //       软件版本号包括：
    //           1-2：机型识别码;
    //         3-10：部件代码;为软硬件的PBS编码，前对齐，不满补0;
    //            11：版本类型，S=应用软件版本，H=硬件版本，B=数据库版本，D=驱动版本，F=FPGA版本，O=其他类型版本，L＝基线版本
    //            12：字母“V”
    //       13-18：软件标识符,其中13-14软件大版本号，15-16软件小版本号，17-18附加版本号;
    //       19-24：发布日期，YYMMDD
    // 单  位:
    // 起始字:17
    // 起始位:0
    char_8 ver_number[24];

    // 标识符:file_id
    // 名  称:文件编号
    // 说  明:无量纲，无符号位的整形数值
    // 单  位:
    // LSB  :1
    // 起始字:23
    // 起始位:0
    UINT32 file_id;

    // 标识符:file_name
    // 名  称:文件名称
    // 说  明:加载文件名称，不大于5个字符
    // 单  位:
    // 起始字:24
    // 起始位:0
    char_8 file_name[12];

    UINT32 spare3 : 16;  // 保留字段
    // 标识符:load_state
    // 名  称:加载状态
    // 说  明:
    // 单  位:
    // 起始字:27
    // 起始位:8
    UINT32 load_state : 8;

    UINT32 spare2 : 8;  // 保留字段

    UINT32 spare4 : 24;  // 保留字段
    // 标识符:translate_state
    // 名  称:传输状态
    // 说  明:
    // 单  位:
    // 起始字:28
    // 起始位:0
    UINT32 translate_state : 8;

    SPARE8 spare5[3];  // 保留字段

    // 标识符:translate_percent
    // 名  称:传输百分比
    // 说  明:用于表示百分比数值
    // 单  位:%
    // LSB  :1
    // 起始字:29
    // 起始位:0
    UINT8 translate_percent;

    SPARE8 spare6[3];  // 保留字段

    // 标识符:load_percent
    // 名  称:加载百分比
    // 说  明:用于表示百分比数值
    // 单  位:%
    // LSB  :1
    // 起始字:30
    // 起始位:0
    UINT8 load_percent;

    // 标识符:Time_Load
    // 名  称:加载时间
    // 说  明:加载软件、数据的日历时间，
    //       格式为：XXXX年XX月XX日  XX时XX分XX秒
    // 单  位:
    // 起始字:31
    // 起始位:0
    TIME_LOAD_TYPE_DEF Time_Load;

    // 标识符:MD5_check
    // 名  称:MD5校验
    // 说  明:
    // 单  位:
    // 起始字:34
    // 起始位:0
    MD5_CHECK_TYPE_DEF MD5_check;

    // 标识符:file_volume_byte
    // 名  称:文件体积
    // 说  明:描述文件体积大小，单位Byte。最大可表示不超过约4GB的文件。
    // 单  位:
    // LSB  :1
    // 起始字:38
    // 起始位:0
    UINT32 file_volume_byte;

    SPARE32 spare7[1];  // 保留字段

} SW_LOAD_STATE_REPORT_OMP;

// 主题 标 识 符: SYM_operational_paras
// 主题 名    称: 系统管理工作参数报告
// 主题 编    码: 485
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 496
// 主题 说    明: 利用空位新增任务系统运行模态信号，表征当前是否需要切换到维护加载态执行软件在线加载。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:sys_network_state
    // 名  称:系统网络状态
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    SYS_NETWORK_STATE_TYPE_DEF sys_network_state[150];

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:ms_sys_main_mode
    // 名  称:任务系统运行模态
    // 说  明:描述任务系统的运行模态，
    //       分为正常运行态和维护加载态，正常运行时为NORMAL
    //       仅当飞管系统进入OFP加载模式后，任务系统启动进入维护加载态，由该信号触发。
    // 单  位:
    // 起始字:453
    // 起始位:0
    UINT32 ms_sys_main_mode : 8;

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:ms_sw_match_result
    // 名  称:任务系统软件匹配状态
    // 说  明:
    // 单  位:
    // 起始字:454
    // 起始位:0
    UINT32 ms_sw_match_result : 8;

    SPARE32 spare3[41];  // 保留字段

} SYM_OPERATIONAL_PARAS;

// 主题 标 识 符: SYM_security_state_report
// 主题 名    称: 系统管理安全状态报告
// 主题 编    码: 478
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 190
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:sys_security_authority_table_state
    // 名  称:系统安全_权限表状态
    // 说  明:描述3个权限表的状态
    // 单  位:
    // 起始字:3
    // 起始位:0
    SYS_SECURITY_AUTHORITY_TABLE_STATE_TYPE_DEF sys_security_authority_table_state[3];

    // 标识符:sys_security_user_state
    // 名  称:系统安全_用户状态
    // 说  明:
    // 单  位:
    // 起始字:12
    // 起始位:0
    SYS_SECURITY_USER_STATE_TYPE_DEF sys_security_user_state;

    // 标识符:sys_security_level_state
    // 名  称:系统安全_密级状态
    // 说  明:
    // 单  位:
    // 起始字:17
    // 起始位:0
    SYS_SECURITY_LEVEL_STATE_TYPE_DEF sys_security_level_state;

    SPARE32 spare1[4];  // 保留字段

    // 标识符:subsystem_module_state
    // 名  称:子系统模块运行状态
    // 说  明:用于表征子系统模块运行在正常态或是软件加载态。依据配置文件定义的ICP内部每个cpum的ID，以及DCLM /DCRM、 IN1M /IN2M、 DCLD/DCRD、 HUDM 、HMDM、 RDDP、 EWRM、 CNRM、ETTM 、 SMU1/ SMU2 、FASM 、DCAM 、UFCP 、CNAM等。
    // 单  位:
    // 起始字:62
    // 起始位:0
    SUBSYSTEM_MODULE_STATE_TYPE_DEF subsystem_module_state[64];

} SYM_SECURITY_STATE_REPORT;

// 主题 标 识 符: SYM_time_config_state_report
// 主题 名    称: 系统管理时间配置状态报告
// 主题 编    码: 481
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 6
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:time_calendar_config
    // 名  称:时间_日历时间配置
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TIME_CALENDAR_CONFIG_TYPE_DEF time_calendar_config;

    UINT32 spare1 : 24;  // 保留字段
    // 标识符:time_mission_sync_type
    // 名  称:时间_任务时间授时同步方式
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    UINT32 time_mission_sync_type : 8;

    UINT32 spare2 : 24;  // 保留字段
    // 标识符:time_stopwatch_state
    // 名  称:时间_秒表计时状态
    // 说  明:秒表计时的状态：
    //       正在正计时
    //       正在倒计时
    //       正计时暂停
    //       倒计时暂停
    //       秒表非激活（T=0）
    //       秒表非激活（T>0）
    // 单  位:
    // 起始字:5
    // 起始位:0
    UINT32 time_stopwatch_state : 8;

} SYM_TIME_CONFIG_STATE_REPORT;

// 主题 标 识 符: SYM_time_report
// 主题 名    称: 系统管理时间信息报告
// 主题 编    码: 483
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 16
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:univesal_date
    // 名  称:时间_世界日期
    // 说  明:世界时间的日期
    // 单  位:
    // 起始字:3
    // 起始位:0
    UNIVESAL_DATE_TYPE_DEF univesal_date;

    // 标识符:univesal_time
    // 名  称:时间_世界时间
    // 说  明:时间信息的时分秒数据:
    //       1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //       2、用于一般计时时间最大值99:59:59(即<100小时)；
    //       3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT64 univesal_time;

    // 标识符:continual_flight_time
    // 名  称:时间_续航时间
    // 说  明:时间信息的时分秒数据:
    //       1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //       2、用于一般计时时间最大值99:59:59(即<100小时)；
    //       3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT64 continual_flight_time;

    // 标识符:timer_time
    // 名  称:时间_秒表时间
    // 说  明:
    // 单  位:ns
    // LSB  :1
    // 起始字:8
    // 起始位:0
    UINT64 timer_time;

    // 标识符:date_missiontime
    // 名  称:时间_任务日期
    // 说  明:
    // 单  位:
    // 起始字:10
    // 起始位:0
    DATE_MISSIONTIME_TYPE_DEF date_missiontime;

    // 标识符:deltatime_mission_RTC
    // 名  称:时间_任务RTC差值
    // 说  明:指任务时间与RTC时间的差值，各子域根据该差值与读取的RTC时间相加，计算得到当前任务时间。
    //       注：该任务时间为绝对任务时间，为当前距离2000年1月1日0时的纳秒数。
    // 单  位:
    // 起始字:11
    // 起始位:0
    DELTATIME_MISSION_RTC_TYPE_DEF deltatime_mission_RTC;

    // 标识符:date_calendartime
    // 名  称:时间_日历日期
    // 说  明:
    // 单  位:
    // 起始字:13
    // 起始位:0
    DATE_CALENDARTIME_TYPE_DEF date_calendartime;

    // 标识符:time_calendartime
    // 名  称:时间_日历时间
    // 说  明:时间信息的时分秒数据:
    //       1、用于表示日历时间信号时最大值23:59:59(即<24小时)。
    //       2、用于一般计时时间最大值99:59:59(即<100小时)；
    //       3、用于特殊计时时间最大值9999.9小时；
    // 单  位:ns
    // LSB  :1
    // 起始字:14
    // 起始位:0
    UINT64 time_calendartime;

} SYM_TIME_REPORT;

// 主题 标 识 符: TDC_cursor_rate
// 主题 名    称: TDC光标速率
// 主题 编    码: 1016
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 5
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:TDC_cursor_rate_X
    // 名  称:TDC光标X向速率
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:3
    // 起始位:0
    INT32 TDC_cursor_rate_X;

    // 标识符:TDC_cursor_rate_Y
    // 名  称:TDC光标Y向速率
    // 说  明:
    // 单  位:No_Unit
    // LSB  :0.0001
    // 起始字:4
    // 起始位:0
    INT32 TDC_cursor_rate_Y;

} TDC_CURSOR_RATE;

// 主题 标 识 符: TDC_location
// 主题 名    称: TDC光标位置参数
// 主题 编    码: 1014
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 5
// 主题 说    明:
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:TDC_AZ
    // 名  称:TDC光标方位
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    TDC_AZ_TYPE_DEF TDC_AZ;

    // 标识符:TDC_EL
    // 名  称:TDC光标俯仰
    // 说  明:
    // 单  位:
    // 起始字:4
    // 起始位:0
    TDC_EL_TYPE_DEF TDC_EL;

} TDC_LOCATION;

// 主题 标 识 符: VMS1394_STOF
// 主题 名    称: VMS1394_STOF包
// 主题 编    码: 61743
// 主题 类    型: 数据块
// 主题 格式类型: 飞控类型
// 主题 长    度: 9
// 主题 说    明: STOF主题定义不包含STOF包的1394头、1394数据CRC、垂直奇偶校验部分。
//                STOF包是由VMC发送的帧开始包，用于本地总线同步，并广播系统内的公共信息。VMC每15.0ms ± 150μs发送一个STOF包。
//                远程节点仅接收STOF包，不发送STOF包。
typedef struct
{
    // 标识符:VMS1394_VMC_State
    // 名  称:VMS1394_VMC_状态字
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    VMS1394_VMC_STATE_TYPE_DEF VMS1394_VMC_State;

    // 标识符:VMS1394_VMC_Branch_State
    // 名  称:VMS1394_VMC分支状态字
    // 说  明:
    // 单  位:
    // 起始字:1
    // 起始位:0
    VMS1394_VMC_BRANCH_STATE_TYPE_DEF VMS1394_VMC_Branch_State;

    // 标识符:VMS1394_SYS_MODE_STATE
    // 名  称:VMS1394_系统模式和状态字
    // 说  明:
    // 单  位:
    // 起始字:2
    // 起始位:0
    VMS1394_SYS_MODE_STATE_TYPE_DEF VMS1394_SYS_MODE_STATE;

    // 标识符:VMS1394_date_calendartime
    // 名  称:VMS1394_时间_日历日期
    // 说  明:
    // 单  位:
    // 起始字:3
    // 起始位:0
    VMS1394_DATE_CALENDARTIME_TYPE_DEF VMS1394_date_calendartime;

    // 标识符:VMS1394_time
    // 名  称:VMS1394_日历时间
    // 说  明:飞管总线日历时间，单位1ms
    // 单  位:M_sc
    // LSB  :1
    // 起始字:4
    // 起始位:0
    UINT32 VMS1394_time;

    // 标识符:VMS1394_SYS_COUNTER
    // 名  称:VMS1394_SYS_COUNTER
    // 说  明:SYS Counter是一个32位长整型数，由CC软件填写，用于传输VMS系统计数值，每一总线周期（15ms±150us）传输一次，SYS Counter由系统软件产生。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 VMS1394_SYS_COUNTER;

    // 标识符:VMS1394_MBI_COUNTER
    // 名  称:VMS1394_MBI_COUNTER
    // 说  明:MBI Counter是一个32位长整型数，由硬件填写，每一总线周期（15ms±150us）传输一次。默认置0，每总线周期加1。
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:6
    // 起始位:0
    UINT32 VMS1394_MBI_COUNTER;

    SPARE32 spare1[2];  // 保留字段

} VMS1394_STOF;

// 主题 标 识 符: work_state_report
// 主题 名    称: 工作状态报告
// 主题 编    码: 385
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 6
// 主题 说    明: 当子系统/子域初始化完成、工作模式、工作状态信号的值发生改变、或系统请求修改工作模式、工作状态时，将该主题作为事件消息发送至任务系统健康管理子域和系统管理子域。另外当子系统执行BIT时，以160ms周期组播自检测进度。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:start_remain_time
    // 名  称:时间_启动倒计时
    // 说  明:
    // 单  位:Sec
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT32 start_remain_time : 16;

    // 标识符:subsys_work_state
    // 名  称:工作状态
    // 说  明:子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    //       20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
    //       20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
    //       20250515，增加应急状态，表示ICP处于28V供电的一个工作状态。
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 subsys_work_state : 8;

    // 标识符:subsys_main_mode
    // 名  称:工作模式
    // 说  明:描述系统的工作模式；
    //       初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 subsys_main_mode : 8;

    UINT32 spare1 : 4;  // 保留字段
    // 标识符:AC_ID
    // 名  称:飞机ID
    // 说  明:0 歼-20飞机01状态01-05架
    //       1 歼-20飞机01状态06架起
    //       2 歼-20飞机02状态，不装航炮
    //       3 歼-20飞机02状态，装航炮
    //       4 歼-20双座机，配装涡扇-10C
    //       5 歼-20双座机，配装涡扇-15
    //       6 歼-20A飞机，配装涡扇-10C
    //       7 歼-20A飞机，配装涡扇-15
    // 单  位:
    // 起始字:4
    // 起始位:24
    UINT32 AC_ID : 4;

    // 标识符:security_level
    // 名  称:系统安全_密级
    // 说  明:目前只有非密/秘密两种密级，后续可能会增加更多的密级
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 security_level : 8;

    // 标识符:bit_process_percent
    // 名  称:自检测进度
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:4
    // 起始位:0
    UINT32 bit_process_percent : 16;

    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    // 说  明:表征子系统上电次数
    //       不能上报的功能单元将该信号置0
    // 单  位:
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 subsys_electrify_amount;

} WORK_STATE_REPORT;

// 主题 标 识 符: work_state_report_OMP
// 主题 名    称: 工作状态报告_OMP
// 主题 编    码: 3832
// 主题 类    型: 数据块
// 主题 格式类型: 应用主题
// 主题 长    度: 6
// 主题 说    明: 当子系统/子域初始化完成、工作模式、工作状态信号的值发生改变、或系统请求修改工作模式、工作状态时，将该主题作为事件消息发送至任务系统健康管理子域和系统管理子域。另外当子系统执行BIT时，以160ms周期组播自检测进度。
typedef struct
{
    // 标识符:msg_publish_time
    // 名  称:消息发布时间
    // 说  明:消息发布时的系统RTC时间。消息发布后在后续的传输中，该时间不会变化。
    // 单  位:
    // 起始字:0
    // 起始位:0
    MSG_PUBLISH_TIME_TYPE_DEF msg_publish_time;

    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    // 说  明:发布本消息的设备/功能单元ID。由系统在ICD文件中明确定义。
    // 单  位:
    // 起始字:2
    // 起始位:0
    MSG_PUBLISHER_ID_TYPE_DEF msg_publisher_ID;

    // 标识符:start_remain_time
    // 名  称:时间_启动倒计时
    // 说  明:
    // 单  位:Sec
    // LSB  :1
    // 起始字:3
    // 起始位:16
    UINT32 start_remain_time : 16;

    // 标识符:subsys_work_state
    // 名  称:工作状态
    // 说  明:子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    //       20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
    //       20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
    //       20250515，增加应急状态，表示ICP处于28V供电的一个工作状态。
    // 单  位:
    // 起始字:3
    // 起始位:8
    UINT32 subsys_work_state : 8;

    // 标识符:subsys_main_mode
    // 名  称:工作模式
    // 说  明:描述系统的工作模式；
    //       初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
    // 单  位:
    // 起始字:3
    // 起始位:0
    UINT32 subsys_main_mode : 8;

    UINT32 spare1 : 4;  // 保留字段
    // 标识符:AC_ID
    // 名  称:飞机ID
    // 说  明:0 歼-20飞机01状态01-05架
    //       1 歼-20飞机01状态06架起
    //       2 歼-20飞机02状态，不装航炮
    //       3 歼-20飞机02状态，装航炮
    //       4 歼-20双座机，配装涡扇-10C
    //       5 歼-20双座机，配装涡扇-15
    //       6 歼-20A飞机，配装涡扇-10C
    //       7 歼-20A飞机，配装涡扇-15
    // 单  位:
    // 起始字:4
    // 起始位:24
    UINT32 AC_ID : 4;

    // 标识符:security_level
    // 名  称:系统安全_密级
    // 说  明:目前只有非密/秘密两种密级，后续可能会增加更多的密级
    // 单  位:
    // 起始字:4
    // 起始位:16
    UINT32 security_level : 8;

    // 标识符:bit_process_percent
    // 名  称:自检测进度
    // 说  明:用于表示百分比数值，LSB=0.01表示的是0.01%。
    // 单  位:%
    // LSB  :0.01
    // 起始字:4
    // 起始位:0
    UINT32 bit_process_percent : 16;

    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    // 说  明:表征子系统上电次数
    //       不能上报的功能单元将该信号置0
    // 单  位:
    // LSB  :1
    // 起始字:5
    // 起始位:0
    UINT32 subsys_electrify_amount;

} WORK_STATE_REPORT_OMP;
#pragma pack()
#endif
