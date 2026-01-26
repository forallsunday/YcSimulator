///*
// * YC_Controller_Computer.h
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *
// *
// *  描述：主控内部计算头文件
// */

#ifndef YC_CONTROLLER_COMPUTER_H_
#define YC_CONTROLLER_COMPUTER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "ICDB_ENUM_STRUCT_IRRM.h"
#include "ICDB_TOPIC_STRUCT_IRRM.h"
#include "math.h"
#include "sysTypes.h"
#pragma pack(1)

typedef struct
{
    // 标识符:IR_range_lowline
    // 名  称:IR距离近界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:0
    // 起始位:16
    float IR_range_lowline;

    // 标识符:IR_WIDE_IMAGE_DIRECTION
    // 名  称:光电广域成像扫描方向
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:3
    IR_WIDE_IMAGE_DIRECTION IR_WIDE_IMAGE_DIRECTION;

    // 标识符:IR_WIDE_IMAGE_MODE
    // 名  称:光电广域成像子模式
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:0
    IR_WIDE_IMAGE_MODE IR_WIDE_IMAGE_MODE;

    // 标识符:D_area_altitude
    // 名  称:距离优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:3
    // 起始位:16
    float D_area_altitude;

    // 标识符:AZ_area_altitude
    // 名  称:方位优先目标区域高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //
    // 单  位:m
    // LSB  :0.5
    // 起始字:3
    // 起始位:0
    float AZ_area_altitude;

    // 标识符:IR_range_upline
    // 名  称:IR距离远界
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:1
    // 起始位:0
    float IR_range_upline;

    // 标识符:IR_scan_start_angle
    // 名  称:光电扫描起始角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.1
    // 起始字:2
    // 起始位:16
    float IR_scan_start_angle;

    // 标识符:IR_IMAGE_TANGE
    // 名  称:量程
    // 说  明:
    // 单  位:km
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    float IR_IMAGE_RANGE;

    // 标识符:IR_scan_end_angle
    // 名  称:光电扫描结束角
    // 说  明:
    // 单  位:mrad
    // LSB  :0.1
    // 起始字:3
    // 起始位:0
    float IR_scan_end_angle;

} COMP_IR_WIDE_IMAGE_PARAS;
// 信 号 组 标 识 符: area_image_paras
// 信 号 组 名    称: IR区域成像范围参数
// 信 号 组 字    数: 4
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
    float latitude;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    float longitude;

    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    float altitude;

    // 标识符:AREA_num
    // 名  称:区域编号
    // 说  明:表征区域编号数值
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:3
    // 起始位:8
    UINT8 AREA_num;

    // 标识符:IR_AREA_LENGTH
    // 名  称:光电区域边长
    // 说  明:
    // 单  位:km
    // LSB  :1
    // 起始字:3
    // 起始位:0
    UINT8 IR_AREA_LENGTH;

    // 标识符:IR_IMG_FLAG
    // 名  称:光电成像状态，是否超界
    //	 0,	无意义
    //  1,超界
    //	 2,	正常
    IR_IMG_FLAG IR_IMG_FLAG;

} COMP_AREA_IMAGE_PARAS;

// 信 号 组 标 识 符: area_monitor_paras
// 信 号 组 名    称: IR区域监视范围参数
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
    float latitude;

    // 标识符:_longitude
    // 名  称:_经度
    // 说  明:(-180,180]度
    //        地理位置经度：表示精度0.00001mrad，
    // 单  位:mrad
    // LSB  :0.00001
    // 起始字:1
    // 起始位:0
    float longitude;

    // 标识符:_altitude
    // 名  称:_高度
    // 说  明:用于高度等相关信号表示，带符号为是为了在计算过程中可能产生负值。
    //        精度0.01米，可表示+/-约10000km。
    // 单  位:m
    // LSB  :0.01
    // 起始字:2
    // 起始位:0
    float altitude;

    // 标识符:IR_IMG_FLAG
    // 名  称:光电成像状态，是否超界
    //	 0,	无意义
    //  1,超界
    //	 2,	正常
    IR_IMG_FLAG IR_IMG_FLAG;

} COMP_AREA_MONITOR_PARAS;

// 主控计算用参数，主要包含两类，（一）计算输入参数和（二）计算输出参数
// 一、计算输入参数包括两类：
// 1.来自FC上端接收，需要定义相关变量进行缓存,主要包括各种工作模式使用的参数,以及其他控制参数
typedef struct Struct_Compute_INput_FromFC {
    // 名  称:IR广域成像范围参数1
    COMP_IR_WIDE_IMAGE_PARAS comp_IR_wide_image_paras;
    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    COMP_AREA_IMAGE_PARAS comp_area_image_paras[3];
    // 代表0，1，2三个区域的有效性，1：有效，0：无效1
    UINT8 comp_area_image_paras_validity[3];
    // 名  称:IR区域监视范围参数1
    COMP_AREA_MONITOR_PARAS comp_area_monitor_paras;
    // 名  称:图像跟踪信息1
    IR_TGT_TRACK_INFO_TYPE_DEF comp_IR_TGT_TRACK_INFO;
    // 名  称:区域成像方式
    IR_IMG_MODE comp_IR_AREA_IMA_MODE;
} PARAM_COMPUTE_INPUT_FROMFC;
// 2.来自内部fpga各分系统,也要定义一个结构体，用mess_From_Fpga中的相关参数乘以LSB后进行缓存(该操作在fpga_Mess_Process函数中进行)
typedef struct Struct_Compute_INput_Fromfpga {
    // 主控设置的相关标志位
    UINT8 flag_GYQYPhoto_FIRST_Compute; // 第一次调用摆扫计算，用于知道从近机点还是远机点扫；0：非第一次；1：第一次调用
    UINT8 flag_Speed_OR_Locate;         // 速度位置信号；1：位置；0：速度；不工作时都是位置
    UINT8 flag_First_Into_Speed;        // 从位置进入速度信号标志位；1：刚刚进入；0：非刚进入（1由主控外部控制赋值；0由计算函数赋值），用于计算判断换向
    UINT8 flag_First_TJ;                // 调焦状态下第一次进入，1：第一次；0：不是第一次

    // 焦距相关
    UINT8 flag_view_State; // 大小视场状态,0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦
    float jj_Small_KJ;     // 可见小视场-长焦 MM1500
    float jj_Big_KJ;       // 可见大视场-短焦
    float jj_Small_HW;     // 红外小视场-长焦
    float jj_Big_HW;       // 红外大视场-短焦

    // 补充从分系统收到的，计算需要的参数
    // 从pos来的飞机姿态信息
    float longitude;    // 经度LSB=π/2^31---1
    float latitude;     // 纬度LSB=π/2^31---1
    float altitude;     // 高度 有符号数(-500m~25000m)， LSB=0.001m---1
    float true_heading; // 真航向   有符号数(-π~+π)，LSB=π/2^31rad---1
    float pitch;        // 俯仰角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    float roll;         // 横滚角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    float north_speed;  // 北向速度  有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    float east_speed;   // 东向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    float ground_speed; // 地向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1

    // 从伺服系统接收的参数信息
    float rtime_pitch_frame;        // 框架实时俯仰角（LSB = 0.0001°)
    float rtime_direction_frame;    // 框架实时方位角（LSB = 0.0001°)
    float exposure_pitch_frame;     // 框架曝光时刻俯仰角（LSB = 0.0001°)
    float exposure_direction_frame; // 框架曝光时刻方位角（LSB = 0.0001°)
    float kfbgskfybcwz;             // 快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
    float kfbgskfwbcwz;             // 快反曝光时刻方位补偿位置（LSB = 0.0001°)

} PARAM_COMPUTE_INPUT_FROMFPGA;

// 二、计算输出参数,所有计算结果参数都填入该结构体。主控计算输出参数,计算完成向其中赋值
typedef struct Struct_Compute_Output {
    // 主控fpga用--------------------------------------------------------------------------
    UINT8 frames_Num;      // 当前条带总帧数
    UINT8 qy_zq_num;       // 区域周期号——只用于区域成像模式，连续成像
    UINT8 qy_td_total_num; // 区域内条带总数

    float toFPGA_time_speed;    // 速度信号时间LSB=1ms
    float toFPGA_time_location; // 位置信号时间LSB=1ms
    int   QYCX_Over_flag;       // 已完成扫描标志 0-未完成 1-已完成区域扫描

    // 框架用--------------------------------------------------------------------------
    float toKJ_pitch_start;     // 框架俯仰指令   起始角（LSB=0.0001°）
    float toKJ_pitch_end;       // 框架俯仰指令   结束角（LSB=0.0001°）
    float toKJ_direction_start; // 框架方位指令   起始角（LSB=0.0001°）
    float toKJ_direction_end;   // 框架方位指令   结束角（LSB=0.0001°）

    float toKJ_pitch_speed;                     // 框架俯仰扫描速度指令（LSB=0.01°/s）
    float toKJ_direction_speed;                 // 框架方位扫描速度指令（LSB=0.01°/s）
    float toKJ_speed_hight;                     // 速高比（LSB=0.001）
    float toKJ_pitch_image_motion_velocity;     // 给定快反俯仰前向像移速度（LSB=0.001°/s)
    float toKJ_direction_image_motion_velocity; // 给定快反方位前向像移速度（LSB=0.001°/s)

    // 调焦用--------------------------------------------------------------------------
    UINT32 toTJ_distance; // 照相距离——调焦用

    // 实时上报LOS信息
    float sensor_los_geo_az;      // 地理系_传感器LOS_方位mrad
    float sensor_los_geo_el;      // 地理系_传感器LOS_俯仰mrad
    float sensor_los_platform_az; // 机体系_传感器LOS_方位mrad
    float sensor_los_platform_el; // 机体系_传感器LOS_俯仰mrad

    // 注释信息用--------------------------------------------------------------------------
    // 名  称:收容宽度
    // 说  明:单位：米。   对于光电：广域模式和区域成像模式下垂直航向的实际宽度，区域监视模式下为一帧图像的实际宽度。
    UINT32 wideCover;
    // 名  称:视场中心_俯仰    机体系   //LSB  :0.01	//单  位:°
    float view_fov_center_elevation;
    // 名  称:视场中心_方位    机体系 //LSB  :0.01	//单  位:°
    float view_fov_center_azimuth;
    // 名  称:像元分辨率//LSB  :0.01
    float A818_CUR_RESOLUTION;
    // 名  称:傍向重叠率	00~99
    UINT8 A818_Beside_tgt_cover;
    // 名  称:航向重叠率 00~99
    UINT8 A818_Couse_tgt_cover;
    // 名  称:图像中心高度
    INT16 A818_ImageCenterHeight;
    // 名  称:地面摄影分辨率//LSB  :0.01
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置地面摄影分辨率。像元投影到地面后的分辨率。精度与飞机姿态参数精度、相对高度参数精度等相关
    float A818_GROUND_RESOLUTION;
    // 名  称:图像中心经度//LSB  :0.00001
    float image_center_longitude;
    // 名  称:图像中心纬度//LSB  :0.00001
    float image_center_latitude;
    // 名  称:图像左上角经度//LSB  :0.00001
    float imaging_left_up_longitude;
    // 名  称:图像左上角纬度//LSB  :0.00001
    float imaging_left_up_latitude;
    // 名  称:图像左下角经度//LSB  :0.00001
    float imaging_left_down_longitude;
    // 名  称:图像左下角纬度//LSB  :0.00001
    float imaging_left_down_latitude;
    // 名  称:图像右上角经度//LSB  :0.00001
    float imaging_right_up_longitude;
    // 名  称:图像右上角纬度//LSB  :0.00001
    float imaging_right_up_latitude;
    // 名  称:图像右下角经度//LSB  :0.00001
    float imaging_right_down_longitude;
    // 名  称:图像右下角纬度//LSB  :0.00001
    float imaging_right_down_latitude;

    // 实际成像参数,载荷真实的成像参数
    // 名  称:IR广域成像范围参数1
    COMP_IR_WIDE_IMAGE_PARAS real_IR_wide_image_paras;
    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    COMP_AREA_IMAGE_PARAS real_area_image_paras[3];
    // 名  称:IR区域监视范围参数1
    COMP_AREA_MONITOR_PARAS real_area_monitor_paras;

} PARAM_COMPUTE_OUTPUT;

#pragma pack()

// 根据
// gpio0AIn(4);//0A_4为位置/速度信号；高电平为位置；低电平为速度
// gpio0AIn(3);//0A_3为曝光同步信号，高有效，持续4ms

//---------------------------计算用-----------------------------------------
// 框架角  结构体
typedef struct Struct_KJAgl {
    double WKJ;
    double NKJ;
} struct_KJAgl;

// 向量  结构体
typedef struct Struct_LSB_float64 {
    double X;
    double Y;
    double Z;
} struct_LSB_float64;

// 姿态  结构体
typedef struct Struct_AttiAgl {
    double Yaw;
    double Pitch;
    double Roll;
} struct_AttiAgl;
// 坐标 结构体
typedef struct Struct_Position_float64 {
    double X;
    double Y;
    double Z;
} struct_Position_float64;

// 经纬高 结构体
typedef struct Struct_GPS_float64 {
    double Lon;
    double Lat;
    double Alt;
} struct_GPS_float64;

//-------------------------计算用-----END----------------------------------

// 计算中使用变量初始化
void comp_Parm_init();
//=========================================================外部调用函数===========================================
//-------------------------广域成像用------------------------------
// 1.根据距离算角度-距离优先模式使用：检调光、正常工作使用
// 根据距离近界、距离远界、扫描方向、目标区域高度，计算指令角等工作参数
// 返回值为是否超限
UINT8 comp_GY_Dis_Normal();
// 2.根据量程和起始角结束角算——方位优先使用：检调光、正常工作使用
UINT8 comp_GY_Az_Normal();
// 3.准备中的检调焦使用——距离优先
// 侧向（距离优先）：只考虑左右倾，方位按85°，俯仰按照距离32km计算，算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_GY_Dis_ZB_JTJ();
// 4.准备中的检调焦使用——方位优先
// 前向（方位优先）：右侧前，方位右侧倾角30°（前为0），前向俯仰角按距离32km计算，算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_GY_Az_ZB_JTJ();
// 5.维护自检，执行广域成像——距离优先，右倾成像
UINT8 comp_GY_Dis_WHZJ();
// 6.准备中调光使用——广域成像——距离优先
// 返回值为是否超限
UINT8 comp_GY_Dis_ZB_JTG();
// 7.准备中调光使用——广域成像——方位优先
// 返回值为是否超限
UINT8 comp_GY_Az_ZB_JTG();
//-------------------------广域成像用--END----------------------------

//-------------------------区域成像用------------------------------
// 1.区域成像准备中——检调光用
// 按照某一个区域成像参数的中心点经纬高参数提取左右倾斜方向，方位按80°，俯仰摆扫角度以距离50km为中心摆扫，使用第一个有效的区域参数
UINT8 comp_QY_Photo_ZB_JTG();
// 2.区域成像准备中——检调焦用
// 先用经纬高算左右，方位按85°，俯仰按照距离32km计算，计算出经纬高(准备中检调焦用的  经纬高)，使用第一个有效的区域参数
UINT8 comp_QY_Photo_ZB_JTJ();
// 3.区域成像正常，根据收到的三组区域成像参数进行计算,注意要实时修改哪个区域正在成像的标志位（cmd_From_FC中的irst_cmd_param_area_image_paras_photoing[3];）
UINT8 comp_QY_Photo_Normal();
// 4.区域超限计算---251124联试添加
UINT8 comp_QY_over(UINT8 QY_num);
//-------------------------区域成像用--END----------------------------

//-------------------------区域监视用------------------------------
// 1.区域监视准备中——检调光用
// 按照区域监视的中心点经纬高参数提取左右倾斜方向，方位按80°，以距离50km为中心凝视，计算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_QY_Video_ZB_JTG();
// 2.区域监视准备中——检调焦用
// 先用经纬高算左右，方位按85°，俯仰按照距离32km计算，计算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_QY_Video_ZB_JTJ();
// 3.按照准备计算出的目标进行成像，广域、区域和监视中都会调用
UINT8 comp_QY_Video_ZB();
// 4.区域监视--按照正常下发参数进行成像
UINT8 comp_QY_Video_Normal();

//-------------------------区域监视用--END----------------------------
//=========================外部调用函数==END=========================================

//=========================内部调用函数===========================================
// 处理姿态角
void Process_Atti_ParaComputer(void);
// 地理坐标系转地球坐标系（得到从地理坐标系向地球坐标系转换的矩阵NED_ECEF）
void NEDToECEF(double NED_ECEF_t[3][4], struct Struct_GPS_float64 GPS_t);
// 处理框架角有关参数计算
void Process_KJAgl_ParaComputer(void);
// 处理距离有关参数计算
void Process_Dis_ParaComputer();
// 处理速度有关参数计算
void Process_Speed_ParaComputer(double *SGB_t, double *XOmiga_t, double *YOmiga_t);
// 计算获得扫描航向角
void GetScanTarYaw(void);
// 计算广域距离优先模式下的内框架远/近角
void Process_TarAgl_GY_Dis_ParaComputer(void);
// 计算广域成像条带帧数
void GYCX_Dis_GetTDPhotoNum(double *TDAgl_bigger_t, double *TDAgl_smaller_t, int *GY_TarAglOver);
// 广域成像条带起始角计算（保持条带航向角和俯仰角）
void GYCX_GetKJPos_simple(struct_KJAgl *KJ_Agl_t, struct_AttiAgl AttitudeAC_t, struct_KJAgl Hope_KJ_Agl_t, double Tar_YawAgl_t, double Tar_PitchAgl_t);
// 计算广域方位优先模式下的外框架远/近角
void Process_TarAgl_GY_AZ_ParaComputer(void);
// 计算广域成像条带帧数-方位优先
void GYCX_AZ_GetTDPhotoNum(double *TDAgl_bigger_t, double *TDAgl_smaller_t, int *GY_TarAglOver);

// 地理跟踪，根据目标经纬高，计算需要的所有参数
int GeoTrack_ParaComputer(double Tar_Lon_t, double Tar_Lat_t, double Tar_Alt_t);
// 经纬度坐标转ECEF坐标
void GPSToECEF(struct_Position_float64 *Tar_ecef_t, double Tar_Lon_t, double Tar_Lat_t, double Tar_Alt_t);
// ECEF坐标系到NED坐标系转换矩阵
void ECEFToNED(double ECEF_NED_t[3][4], struct_GPS_float64 GPS_t);
// 依据目标在ECEF中坐标，给出视轴单位向量
void GetOneLSBbyTarECEF_ParaComputer(struct_LSB_float64 *oneLSB_t, struct_Position_float64 *ecef_Tar_t);
// 依据理想视轴向量及当前姿态角，给出框架指向角
void GetKJAglbyLSB_ParaComputer(struct_KJAgl *kj_Agl_t, const struct_LSB_float64 *ned_lsb_t);
// 给定外框架和内框架角，计算得到目标在ECEF中坐标
void GetTarECEFbyKJAgl_ParaComputer(struct_Position_float64 *ecef_Tar_t, const struct_KJAgl *hope_agl_kj_t);
// 用目标投影在地球坐标求目标在地球坐标系坐标
void ECEFGeolocat(double ECEFTarget_t[3], double k_t[3], double b_t[3], double GeodeticHeightTarget_t);
// 地球坐标系下坐标转GPS，得到GPSTarget
void ECEFToGPS(double GPS_t[3], double ECEF_t[3]);
// 区域成像计算条带数、条带帧数和起始角
UINT8 QYCX_GetTDPhotoNum(struct_GPS_float64 GPS_Tar, double Tar_Range);
// 区域成像计算条带起始角
void QYCX_GetTDstart();
// 目标地理定位
void Geolocation();
// 目标地理定位
void ComptGps(double x, double y, struct_GPS_float64 *Tar_gps);
// 距离优先广域返回参数
void Out_GY_Dis();
// 方位优先广域返回参数
void Out_GY_Az();
// 区域返回参数
void Out_QY();
// 监视返回参数
void Out_JS();
// 计算当前视轴
void ComptLos();
// 计算近距远距
void ComptRange();
// 输入参数处理
void ProcessInPram();
// 输出参数处理
void ProcessOutPram();
// 计算修正参数
void GetRevise();

//=========================内部调用函数==END=========================================

#ifdef __cplusplus
}
#endif
#endif /* YC_CONTROLLER_COMPUTER_H_ */
