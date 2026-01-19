///*
// * YC_Controller_Computer.c
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *
// *
// *  描述：主控内部计算函数
// */

#include "YC_Controller_Computer.h"
#include "YC_Controller_globalVal_Ext.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>

// Note: lcy 添加定位模块
#include <geolocation.h>
#include <rotation.h>

#define Agl_PI 0.01745329
#define PI_Agl 57.2957795

//------------------------参数计算用变量 byL.B----------------------------//
//----------输入
struct_GPS_float64 AC_Position_pi; // 位置坐标 计算用载机位置
struct_AttiAgl     AttitudeAC_pi;  // 姿态
struct_KJAgl       KJAgl_pi;       // 框架角
struct_KJAgl       KJAgl_exp_pi;   // 曝光时刻框架角
struct_KJAgl       KFKZAgl_exp_pi; // 曝光时刻快反角
//--------输出
struct_KJAgl KJ_start_pi;         // 框架起始角
struct_KJAgl KJ_end_pi;           // 框架结束角
struct_KJAgl KJ_omiga_pi;         // 框架角速度角
float        speed_hight;         // 速高比
float        img_move_omiga_x_pi; // 前向向像移速度
float        img_move_omiga_y_pi; // 横向向像移速度
float        photo_Dis;           // 成像距离 m
float        TD_Time;             // 一条带周期时间 s
int          TD_Num;              // 条带数
int          TD_PhotoNum;         // 每条带成像帧数
float        speed_time;          // 速度信号时间 s
float        location_time;       // 位置信号时间 s
int          QYCX_NeedTDNum;      // 需要扫描条带
int          QYCX_ScanOverTime;   // 已完成扫描次数
float        range_lowline;       // 距离近界
float        range_upline;        // 距离远界
// 焦距、帧频、像元尺寸、像元数
int   tocal_foclen_KJ;  // 可见焦距 单位: mm
float tocal_pixsize_KJ; // 像元尺寸4.5

struct_Position_float64 ZB_ecef_Tar;                 // 准备用ECEF中目标坐标
struct_AttiAgl          sin_AttiAgl;                 // 姿态角的sin值
struct_AttiAgl          cos_AttiAgl;                 // 姿态角的cos值
float                   AC_NED[3][3];                // AC坐标系向NED坐标系转换
float                   NED_ECEF[3][4];              // NED坐标系向ECEF坐标系转换
float                   AC_ECEF[3][4];               // AC坐标系向ECEF坐标系转换
float                   planTar_high;                // 相对高度 米
float                   tar_high;                    // 目标高度
struct_KJAgl            sin_KJAgl;                   // 框架角sin值
struct_KJAgl            cos_KJAgl;                   // 框架角cos值
struct_KJAgl            sin_KJAgl_exp;               // 框架角sin值
struct_KJAgl            cos_KJAgl_exp;               // 框架角cos值
float                   AC_speed;                    // 速度
double                  ECEF_NED_Plan[3][4];         // ECEF到飞机NED坐标系转换矩阵
float                   GYCX_Tar_YawAgl_last_sin[4]; // 记录当前航向角sin
float                   GYCX_Tar_YawAgl_last_cos[4]; // 记录当前航向角cos
int                     LL_yaw_i;                    // 航向计数
float                   GYCX_YawAgl_pi;              // 广域成像用航向角
float                   GYCX_PitchAgl_pi;            // 广域成像用俯仰角
float                   GYCX_WKJ_omiga;              // 广域成像外框架角速度
float                   GYCX_NKJ_omiga;              // 广域成像内框架角速度
float                   GYCX_TarAgl_pi;              // 广域成像 目标倾斜角 弧度
float                   GYCX_TarAgl_near_pi;         // 距离优先广域成像 目标倾斜角近界 弧度
float                   GYCX_TarAgl_far_pi;          // 距离优先广域成像 目标倾斜角远界 弧度
float                   GYCX_TarAgl_min_pi;          // 方位优先广域成像 方位角小角 弧度
float                   GYCX_TarAgl_max_pi;          // 方位优先广域成像 方位角大角 弧度
float                   GYCX_TarAgl_FYAgl_pi;        // 方位优先广域成像 俯仰角大角 弧度

float QYCX_WKJ_omiga; // 区域成像外框架角速度
int   QYCX_Over_flag; // 已完成扫描标志
int   QYCX_ScanTDNum; // 已扫描条带数

int   QYCX_QYNo_Doing;      // 正在执行的区域号
int   QYCX_DointQY_flag;    // 是否正在执行一个区域
float QYCX_TDAgl_WKJ_first; // 区域用起始外框架
float QYCX_TDAgl_NKJ_first; // 区域用起始内框架
float QYCX_WKJ_change;      // 区域用外框架变化量
float QYCX_NKJ_change;      // 区域用内框架变化量

// 目标在ECEF坐标
float ECEF_TarA[3];
// 目标在ECEF坐标
float ECEF_TarC[3];

struct_KJAgl KJAgl_AC_pi;  // AC坐标系下框架角
struct_KJAgl KJAgl_NED_pi; // NED坐标系下框架角
int          cover_wide;   // 垂直航向覆盖宽度

struct_Position_float64 GeoTrack_ecef_Tar; // 地理跟踪用ECEF中目标坐标
float                   geo_WKJ_ParaErro;  // 定位修正角 外框架定位计算角 度
float                   geo_NKJ_ParaErro;  // 定位修正角 内框架定位计算角 度

//------------------------参数计算用变量 byL.B---------end-------------------//

// 计算中使用变量初始化
void comp_Parm_init() {
    memset(&AC_Position_pi, 0, sizeof(struct_GPS_float64)); // 位置坐标 计算用载机位置
    memset(&AttitudeAC_pi, 0, sizeof(AttitudeAC_pi));       // 姿态
    memset(&KJAgl_pi, 0, sizeof(KJAgl_pi));                 // 框架角
    memset(&KJAgl_exp_pi, 0, sizeof(KJAgl_exp_pi));         // 曝光时刻框架角
    memset(&KFKZAgl_exp_pi, 0, sizeof(KFKZAgl_exp_pi));     // 曝光时刻快反角
    memset(&KJ_start_pi, 0, sizeof(KJ_start_pi));           // 框架起始角
    memset(&KJ_end_pi, 0, sizeof(KJ_end_pi));               // 框架结束角
    memset(&KJ_omiga_pi, 0, sizeof(KJ_omiga_pi));           // 框架角速度角
    speed_hight         = 0.007;                            // 速高比
    img_move_omiga_x_pi = 0;                                // 前向向像移速度
    img_move_omiga_y_pi = 0;                                // 横向向像移速度
    photo_Dis           = 0;                                // 成像距离 m
    TD_Time             = 0;                                // 一条带周期时间 s
    TD_Num              = 0;                                // 条带数
    TD_PhotoNum         = 0;                                // 每条带成像帧数
    speed_time          = 0;                                // 速度信号时间 s
    location_time       = 0;                                // 位置信号时间 s
    tocal_foclen_KJ     = 1906;                             // 可见焦距 单位: mm
    tocal_pixsize_KJ    = 4.5;                              // 像元尺寸4.5
    memset(&ZB_ecef_Tar, 0, sizeof(ZB_ecef_Tar));           // 准备用ECEF中目标坐标
    memset(&sin_AttiAgl, 0, sizeof(sin_AttiAgl));           // 姿态角的sin值
    memset(&cos_AttiAgl, 0, sizeof(cos_AttiAgl));           // 姿态角的cos值
    memset(&AC_NED, 0, sizeof(AC_NED));                     // 姿态角的cos值

    planTar_high = 0; // 相对高度 米
    tar_high     = 0; // 目标高度

    memset(&sin_KJAgl, 0, sizeof(sin_KJAgl));         // 框架角sin值
    memset(&cos_KJAgl, 0, sizeof(cos_KJAgl));         // 框架角cos值
    memset(&sin_KJAgl_exp, 0, sizeof(sin_KJAgl_exp)); // 框架角sin值
    memset(&cos_KJAgl_exp, 0, sizeof(cos_KJAgl_exp)); // 框架角cos值
    AC_speed = 0;                                     // 速度

    LL_yaw_i             = 0; // 航向计数
    GYCX_YawAgl_pi       = 0; // 广域成像用航向角
    GYCX_PitchAgl_pi     = 0; // 广域成像用俯仰角
    GYCX_WKJ_omiga       = 0; // 广域成像外框架角速度
    GYCX_NKJ_omiga       = 0; // 广域成像内框架角速度
    GYCX_TarAgl_pi       = 0; // 广域成像 目标倾斜角 弧度
    GYCX_TarAgl_near_pi  = 0; // 距离优先广域成像 目标倾斜角近界 弧度
    GYCX_TarAgl_far_pi   = 0; // 距离优先广域成像 目标倾斜角远界 弧度
    GYCX_TarAgl_min_pi   = 0; // 方位优先广域成像 方位角小角 弧度
    GYCX_TarAgl_max_pi   = 0; // 方位优先广域成像 方位角大角 弧度
    GYCX_TarAgl_FYAgl_pi = 0; // 方位优先广域成像 俯仰角大角 弧度

    QYCX_WKJ_omiga       = 0;                                 // 区域成像外框架角速度
    QYCX_Over_flag       = 0;                                 // 已完成扫描标志
    QYCX_ScanTDNum       = 0;                                 // 已扫描条带数
    QYCX_NeedTDNum       = 0;                                 // 需要扫描条带
    QYCX_QYNo_Doing      = 0;                                 // 正在执行的区域号
    QYCX_DointQY_flag    = 0;                                 // 是否正在执行一个区域
    QYCX_TDAgl_WKJ_first = 0;                                 // 区域用起始外框架
    QYCX_TDAgl_NKJ_first = 0;                                 // 区域用起始内框架
    QYCX_WKJ_change      = 0;                                 // 区域用外框架变化量
    QYCX_NKJ_change      = 0;                                 // 区域用内框架变化量
    QYCX_ScanOverTime    = 0;                                 // 已完成扫描次数
    memset(&KJAgl_AC_pi, 0, sizeof(struct_KJAgl));            // AC坐标系下框架角
    memset(&KJAgl_NED_pi, 0, sizeof(struct_KJAgl));           // NED坐标系下框架角
    cover_wide = 0;                                           // 垂直航向覆盖宽度
    memset(&GeoTrack_ecef_Tar, 0, sizeof(GeoTrack_ecef_Tar)); // 地理跟踪用ECEF中目标坐标
    geo_WKJ_ParaErro = 0;                                     // 定位修正角 外框架定位计算角 度
    geo_NKJ_ParaErro = 0;                                     // 定位修正角 内框架定位计算角 度

    GYCX_Tar_YawAgl_last_sin[0] = 0; // 记录当前航向角sin
    GYCX_Tar_YawAgl_last_sin[1] = 0; // 记录当前航向角sin
    GYCX_Tar_YawAgl_last_sin[2] = 0; // 记录当前航向角sin
    GYCX_Tar_YawAgl_last_sin[3] = 0; // 记录当前航向角sin

    GYCX_Tar_YawAgl_last_cos[0] = 1; // 记录当前航向角cos
    GYCX_Tar_YawAgl_last_cos[1] = 1; // 记录当前航向角cos
    GYCX_Tar_YawAgl_last_cos[2] = 1; // 记录当前航向角cos
    GYCX_Tar_YawAgl_last_cos[3] = 1; // 记录当前航向角cos

    range_lowline = 0; // 距离近界
    range_upline  = 0; // 距离远界
    /*
    float AC_NED[3][3];//AC坐标系向NED坐标系转换
    float NED_ECEF[3][4];//NED坐标系向ECEF坐标系转换
    float AC_ECEF[3][4];//AC坐标系向ECEF坐标系转换
    float ECEF_NED_Plan[3][4];//ECEF到飞机NED坐标系转换矩阵
     */
}

// 1.根据距离算角度-距离优先模式使用：检调光、正常工作使用
// 根据距离近界、距离远界、扫描方向、目标区域高度，计算指令角等工作参数
// 返回值为是否超限
UINT8 comp_GY_Dis_Normal() {
    int   overPara_flag_t = 0;    // 参数超限标识
    float TDAgl_bigger_t;         // 条带较大角
    float TDAgl_smaller_t;        // 条带较小角
    ProcessInPram();              // 处理接收数据
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    // 更新广域成像扫描航向角
    GetScanTarYaw();
    // 更新目标倾斜角
    Process_TarAgl_GY_Dis_ParaComputer();
    // 更新条带帧数，条带时间及起始结束角
    GYCX_Dis_GetTDPhotoNum(&TDAgl_bigger_t, &TDAgl_smaller_t, &overPara_flag_t);

    location_time = TD_Time - TD_PhotoNum * GYCX_pfs - Sec_KJSpeedREADY; // 位置信号时间  s
    speed_time    = TD_Time - location_time;                             // 速度信号时间 s

    struct_KJAgl KJ_Agl_start; // 赋值用框架起始角
    struct_KJAgl KJ_Agl_end;   // 赋值用框架结束角

    KJ_Agl_start.NKJ = TDAgl_smaller_t;
    KJ_Agl_end.NKJ   = TDAgl_bigger_t;

    if (V_IR_WIDE_IMAGE_DIRECTION_LEFT == param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION) // 左
    {
        KJ_Agl_start.WKJ = -85 * Agl_PI; // 起始角
        KJ_Agl_end.WKJ   = -90 * Agl_PI; // 结束角
    } else                               // 右倾
    {
        KJ_Agl_start.WKJ = 85 * Agl_PI; // 起始角
        KJ_Agl_end.WKJ   = 90 * Agl_PI; // 结束角
    }

    cover_wide = tan(fabs(TDAgl_bigger_t)) * planTar_high - tan(fabs(TDAgl_smaller_t)) * planTar_high; // 垂直航向覆盖宽度

    // 给定外框架和内框架角，计算得到目标在ECEF中坐标,成像前准备用
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &KJ_Agl_start);

    // 依据姿态给出指向控制角
    GYCX_GetKJPos_simple(&KJ_start_pi, AttitudeAC_pi, KJ_Agl_start, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);
    GYCX_GetKJPos_simple(&KJ_end_pi, AttitudeAC_pi, KJ_Agl_end, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);

    KJ_omiga_pi.WKJ = img_move_omiga_y_pi; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = GYCX_NKJ_omiga;      // 框架俯仰扫描速度指令 °/s

    if (1 == TD_PhotoNum) {
        KJ_omiga_pi.WKJ = 0;
        KJ_omiga_pi.NKJ = 0;
    }
    param_Compute_Output.A818_Beside_tgt_cover = GYCX_P_x; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = GYCX_P_y; // 前向重叠率

    Geolocation(); // 定位计算

    ComptLos(); // 计算当前视轴

    ProcessOutPram(); // 输出参数处理

    ComptRange(); // 计算近距远距

    Out_GY_Dis(); // 距离优先广域返回参数
    return overPara_flag_t;
}
// 2.根据量程和起始角结束角算——方位优先使用：检调光、正常工作使用
UINT8 comp_GY_Az_Normal() {
    int   overPara_flag_t = 0; // 参数超限标识
    float TDAgl_bigger_t;      // 条带较大角
    float TDAgl_smaller_t;     // 条带较小角
    float temp_dis = 0;
    //	float temp_agl = 0;//临时近界角
    ProcessInPram();              // 处理接收数据
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.AZ_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    GetScanTarYaw();                     // 更新广域成像扫描航向角
    Process_TarAgl_GY_AZ_ParaComputer(); // 更新目标倾斜角
    // 更新条带帧数，条带时间及起始结束角
    GYCX_AZ_GetTDPhotoNum(&TDAgl_bigger_t, &TDAgl_smaller_t, &overPara_flag_t);

    location_time = TD_Time - TD_PhotoNum * GYCX_pfs - Sec_KJSpeedREADY; // 位置信号时间  s
    speed_time    = TD_Time - location_time;                             // 速度信号时间 s

    struct_KJAgl KJ_Agl_start; // 赋值用框架起始角
    struct_KJAgl KJ_Agl_end;   // 赋值用框架结束角

    KJ_Agl_start.WKJ = TDAgl_smaller_t;
    KJ_Agl_end.WKJ   = TDAgl_bigger_t;

    KJ_Agl_start.NKJ = GYCX_TarAgl_FYAgl_pi;           // 起始角
    KJ_Agl_end.NKJ   = GYCX_TarAgl_FYAgl_pi - 0.08726; // 结束角

    temp_dis = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE * 1000; // 目标距离
    if (temp_dis == 0) {
        temp_dis = 1;
    }

    if ((TDAgl_bigger_t * TDAgl_smaller_t) < 0) {
        cover_wide = tan(fabs(TDAgl_bigger_t)) * temp_dis + tan(fabs(TDAgl_smaller_t)) * temp_dis; // 垂直航向覆盖宽度
    } else {
        cover_wide = fabs(tan(fabs(TDAgl_bigger_t)) * temp_dis - tan(fabs(TDAgl_smaller_t)) * temp_dis); // 垂直航向覆盖宽度
    }

    // 给定外框架和内框架角，计算得到目标在ECEF中坐标,成像前准备用
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &KJ_Agl_start);
    // 依据姿态给出指向控制角
    GYCX_GetKJPos_simple(&KJ_start_pi, AttitudeAC_pi, KJ_Agl_start, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);
    GYCX_GetKJPos_simple(&KJ_end_pi, AttitudeAC_pi, KJ_Agl_end, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);

    KJ_omiga_pi.WKJ = GYCX_WKJ_omiga;      // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = img_move_omiga_x_pi; // 框架俯仰扫描速度指令 °/s

    param_Compute_Output.A818_Beside_tgt_cover = GYCX_P_y; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = GYCX_P_x; // 前向重叠率

    Geolocation(); // 定位计算
    ComptLos();    // 计算当前视轴

    ProcessOutPram(); // 输出参数处理
    ComptRange();     // 计算近距远距
    Out_GY_Az();      // 方位优先广域返回参数

    return overPara_flag_t;
}

// 3.准备中的检调焦使用——距离优先
// 侧向（距离优先）：只考虑左右倾，方位按85°，俯仰按照距离32km计算
UINT8 comp_GY_Dis_ZB_JTJ() {
    int overPara_flag_t = 0;                                                    // 参数超限标识
    ProcessInPram();                                                            // 输入参数处理
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    GetScanTarYaw();                                                            // 更新广域成像扫描航向角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    struct_KJAgl       hope_agl_kj_t;  // 理想框架角
    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    if (V_IR_WIDE_IMAGE_DIRECTION_RIGHT == param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION) {
        hope_agl_kj_t.WKJ = 85 * Agl_PI;
    } else {
        hope_agl_kj_t.WKJ = -85 * Agl_PI;
    }
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 32000);
    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 1; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理

    return overPara_flag_t;
}
// 4.准备中的检调焦使用——方位优先
// 前向（方位优先）：右侧前，方位右侧倾角30°（前为0），前向俯仰角按距离32km计算
UINT8 comp_GY_Az_ZB_JTJ() {
    int overPara_flag_t = 0;                                                    // 参数超限标识
    ProcessInPram();                                                            // 输入参数处理
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    GetScanTarYaw();                                                            // 更新广域成像扫描航向角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    struct_KJAgl       hope_agl_kj_t;  // 理想框架角
    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    hope_agl_kj_t.WKJ = 30 * Agl_PI;
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 32000);
    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 1; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理

    return overPara_flag_t;
}

// 5.维护自检，执行广域成像——距离优先，右倾成像
UINT8 comp_GY_Dis_WHZJ() {
    int   overPara_flag_t = 0;    // 参数超限标识
    float TDAgl_bigger_t;         // 条带较大角
    float TDAgl_smaller_t;        // 条带较小角
    ProcessInPram();              // 处理接收数据
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    // 处理距离有关参数计算
    Process_Dis_ParaComputer();
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    // 更新广域成像扫描航向角
    GetScanTarYaw();

    //----------自检用赋值
    if (speed_hight < 0.07) {
        speed_hight = 0.07;
    }
    GYCX_TarAgl_pi      = 80 * Agl_PI;
    GYCX_TarAgl_near_pi = 75 * Agl_PI;
    GYCX_TarAgl_far_pi  = 85 * Agl_PI;
    //----------自检用赋值
    // 更新条带帧数，条带时间及起始结束角
    GYCX_Dis_GetTDPhotoNum(&TDAgl_bigger_t, &TDAgl_smaller_t, &overPara_flag_t);

    location_time = (TD_Time - TD_PhotoNum * GYCX_pfs - Sec_KJSpeedREADY); // 位置信号时间 s
    speed_time    = TD_Time - location_time;                               // 速度信号时间 s

    struct_KJAgl KJ_Agl_start; // 赋值用框架起始角
    struct_KJAgl KJ_Agl_end;   // 赋值用框架结束角

    AttitudeAC_pi.Yaw   = param_Compute_Input_Fromfpga.true_heading; // 航向角
    AttitudeAC_pi.Pitch = param_Compute_Input_Fromfpga.pitch;        // 俯仰角
    AttitudeAC_pi.Roll  = param_Compute_Input_Fromfpga.roll;         // 横滚角

    KJ_Agl_start.NKJ = TDAgl_smaller_t;
    KJ_Agl_end.NKJ   = TDAgl_bigger_t;

    // 按照右倾
    KJ_Agl_start.WKJ = 90 * Agl_PI; // 起始角
    KJ_Agl_end.WKJ   = 95 * Agl_PI; // 结束角

    // 依据姿态给出指向控制角
    GYCX_GetKJPos_simple(&KJ_start_pi, AttitudeAC_pi, KJ_Agl_start, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);
    GYCX_GetKJPos_simple(&KJ_end_pi, AttitudeAC_pi, KJ_Agl_end, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);

    KJ_omiga_pi.WKJ = img_move_omiga_y_pi; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = GYCX_NKJ_omiga;      // 框架俯仰扫描速度指令 °/s

    param_Compute_Output.A818_Beside_tgt_cover = GYCX_P_x; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = GYCX_P_y; // 前向重叠率

    range_lowline = tan(KJ_Agl_start.NKJ * Agl_PI) * planTar_high; // 近距

    ComptLos();       // 计算当前视轴
    Out_GY_Dis();     // 距离优先广域返回参数
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

// 6.准备中调光使用——广域成像——距离优先
// 返回值为是否超限
UINT8 comp_GY_Dis_ZB_JTG() {
    int   overPara_flag_t = 0;    // 参数超限标识
    float TDAgl_bigger_t;         // 条带较大角
    float TDAgl_smaller_t;        // 条带较小角
    ProcessInPram();              // 处理接收数据
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    // 更新广域成像扫描航向角
    GetScanTarYaw();
    // 更新目标倾斜角
    Process_TarAgl_GY_Dis_ParaComputer();
    // 更新条带帧数，条带时间及起始结束角
    GYCX_Dis_GetTDPhotoNum(&TDAgl_bigger_t, &TDAgl_smaller_t, &overPara_flag_t);

    if (TD_PhotoNum > 30) // 调光用条带最多30帧
    {
        TD_PhotoNum = 30;
    }
    location_time = Sec_KJPosREADY_WKJ;                        // 调光用位置信号时间  s
    speed_time    = GYCX_pfs * TD_PhotoNum + Sec_KJSpeedREADY; // 速度信号时间 s

    struct_KJAgl KJ_Agl_start; // 赋值用框架起始角
    struct_KJAgl KJ_Agl_end;   // 赋值用框架结束角

    KJ_Agl_start.NKJ = TDAgl_smaller_t;
    KJ_Agl_end.NKJ   = TDAgl_bigger_t;

    if (V_IR_WIDE_IMAGE_DIRECTION_LEFT == param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION) // 左
    {
        KJ_Agl_start.WKJ = -85 * Agl_PI; // 起始角
        KJ_Agl_end.WKJ   = -90 * Agl_PI; // 结束角
    } else                               // 右倾
    {
        KJ_Agl_start.WKJ = 85 * Agl_PI; // 起始角
        KJ_Agl_end.WKJ   = 90 * Agl_PI; // 结束角
    }

    cover_wide = tan(fabs(TDAgl_bigger_t)) * planTar_high - tan(fabs(TDAgl_smaller_t)) * planTar_high; // 垂直航向覆盖宽度

    // 给定外框架和内框架角，计算得到目标在ECEF中坐标,成像前准备用
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &KJ_Agl_start);

    // 依据姿态给出指向控制角
    GYCX_GetKJPos_simple(&KJ_start_pi, AttitudeAC_pi, KJ_Agl_start, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);
    GYCX_GetKJPos_simple(&KJ_end_pi, AttitudeAC_pi, KJ_Agl_end, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);

    KJ_omiga_pi.WKJ = img_move_omiga_y_pi; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = GYCX_NKJ_omiga;      // 框架俯仰扫描速度指令 °/s

    if (1 == TD_PhotoNum) {
        KJ_omiga_pi.WKJ = 0;
        KJ_omiga_pi.NKJ = 0;
    }
    param_Compute_Output.A818_Beside_tgt_cover = GYCX_P_x; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = GYCX_P_y; // 前向重叠率

    Geolocation(); // 定位计算

    ComptLos(); // 计算当前视轴

    ComptRange();     // 计算近距远距
    Out_GY_Dis();     // 距离优先广域返回参数
    ProcessOutPram(); // 输出参数处理

    return overPara_flag_t;
}
// 7.准备中调光使用——广域成像——方位优先
// 返回值为是否超限
UINT8 comp_GY_Az_ZB_JTG() {
    int   overPara_flag_t = 0; // 参数超限标识
    float TDAgl_bigger_t;      // 条带较大角
    float TDAgl_smaller_t;     // 条带较小角
    float temp_dis = 0;
    //	float temp_agl = 0;//临时近界角
    ProcessInPram();              // 处理接收数据
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.AZ_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    GetScanTarYaw();                     // 更新广域成像扫描航向角
    Process_TarAgl_GY_AZ_ParaComputer(); // 更新目标倾斜角
    // 更新条带帧数，条带时间及起始结束角
    GYCX_AZ_GetTDPhotoNum(&TDAgl_bigger_t, &TDAgl_smaller_t, &overPara_flag_t);

    if (TD_PhotoNum > 30) // 调光用条带最多30帧
    {
        TD_PhotoNum = 30;
    }
    location_time = Sec_KJPosREADY_WKJ;                        // 调光用位置信号时间  s
    speed_time    = GYCX_pfs * TD_PhotoNum + Sec_KJSpeedREADY; // 速度信号时间 s

    struct_KJAgl KJ_Agl_start; // 赋值用框架起始角
    struct_KJAgl KJ_Agl_end;   // 赋值用框架结束角

    KJ_Agl_start.WKJ = TDAgl_smaller_t;
    KJ_Agl_end.WKJ   = TDAgl_bigger_t;

    KJ_Agl_start.NKJ = GYCX_TarAgl_FYAgl_pi;           // 起始角
    KJ_Agl_end.NKJ   = GYCX_TarAgl_FYAgl_pi - 0.08726; // 结束角

    temp_dis = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE * 1000; // 目标距离
    if (temp_dis == 0) {
        temp_dis = 1;
    }

    if ((TDAgl_bigger_t * TDAgl_smaller_t) < 0) {
        cover_wide = tan(fabs(TDAgl_bigger_t)) * temp_dis + tan(fabs(TDAgl_smaller_t)) * temp_dis; // 垂直航向覆盖宽度
    } else {
        cover_wide = fabs(tan(fabs(TDAgl_bigger_t)) * temp_dis - tan(fabs(TDAgl_smaller_t)) * temp_dis); // 垂直航向覆盖宽度
    }

    // 给定外框架和内框架角，计算得到目标在ECEF中坐标,成像前准备用
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &KJ_Agl_start);
    // 依据姿态给出指向控制角
    GYCX_GetKJPos_simple(&KJ_start_pi, AttitudeAC_pi, KJ_Agl_start, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);
    GYCX_GetKJPos_simple(&KJ_end_pi, AttitudeAC_pi, KJ_Agl_end, GYCX_YawAgl_pi, GYCX_PitchAgl_pi);

    KJ_omiga_pi.WKJ = GYCX_WKJ_omiga;      // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = img_move_omiga_x_pi; // 框架俯仰扫描速度指令 °/s

    param_Compute_Output.A818_Beside_tgt_cover = GYCX_P_y; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = GYCX_P_x; // 前向重叠率

    Geolocation();    // 定位计算
    ComptLos();       // 计算当前视轴
    ComptRange();     // 计算近距远距
    Out_GY_Az();      // 方位优先广域返回参数
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

// 1.区域成像准备中——检调光用
// 按照区域成像的中心点经纬高参数提取左右倾斜方向，方位按80°，俯仰摆扫角度以距离50km为中心摆扫
UINT8 comp_QY_Photo_ZB_JTG() {
    int                overPara_flag_t = 0; // 参数超限标识
    int                temp_int;
    float              Tar_Lon;
    float              Tar_lat;
    float              Tar_alt;
    struct_KJAgl       hope_agl_kj_t;  // 理想框架角
    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    ProcessInPram();              // 输入参数处理
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    QYCX_QYNo_Doing = 0;                         // 正在执行的区域号
    for (temp_int = 1; temp_int < 4; temp_int++) // 最多查找3个
    {
        // 若区域编号无效
        if (0 == param_Compute_Input_Fromfc.comp_area_image_paras_validity[QYCX_QYNo_Doing]) {
            QYCX_QYNo_Doing++; // 正在扫描区域
        } else                 // 区域有效
        {
            break; // 跳出循环
        }
    } // 查找可用区域结束

    Tar_Lon = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].longitude;
    Tar_lat = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].latitude;
    Tar_alt = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].altitude;
    // 计算框架角
    overPara_flag_t = GeoTrack_ParaComputer(Tar_Lon, Tar_lat, Tar_alt);
    if (KJ_start_pi.WKJ > 0) {
        hope_agl_kj_t.WKJ = 80 * Agl_PI;
    } else {
        hope_agl_kj_t.WKJ = -80 * Agl_PI;
    }
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 50000);

    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理

    return overPara_flag_t;
}

// 2.区域成像准备中——检调焦用
// 先用经纬高算左右，方位按85°，俯仰按照距离32km计算，计算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_QY_Photo_ZB_JTJ() {
    int                overPara_flag_t = 0; // 参数超限标识
    int                temp_int;
    float              Tar_Lon;
    float              Tar_lat;
    float              Tar_alt;
    struct_KJAgl       hope_agl_kj_t;                                                   // 理想框架角
    struct_KJAgl       cal_agl_kj_t;                                                    // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t;                                                  // 理想视轴在NED中指向
    ProcessInPram();                                                                    // 处理接收数据
    Process_Atti_ParaComputer();                                                        // 处理姿态角
    Process_KJAgl_ParaComputer();                                                       // 处理框架角
    tar_high     = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    // 处理距离有关参数计算
    Process_Dis_ParaComputer();
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    QYCX_QYNo_Doing = 0;
    for (temp_int = 1; temp_int < 4; temp_int++) // 最多查找3个
    {
        // 若区域编号无效
        if (0 == param_Compute_Input_Fromfc.comp_area_image_paras_validity[QYCX_QYNo_Doing]) {
            QYCX_QYNo_Doing++; // 正在扫描区域
        } else                 // 区域有效
        {
            break; // 跳出循环
        }
    } // 查找可用区域结束

    Tar_Lon = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].longitude / 1000;
    Tar_lat = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].latitude / 1000;
    Tar_alt = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].altitude;
    // 计算框架角
    overPara_flag_t = GeoTrack_ParaComputer(Tar_Lon, Tar_lat, Tar_alt);
    if (KJ_start_pi.WKJ > 0) {
        hope_agl_kj_t.WKJ = 85 * Agl_PI;
    } else {
        hope_agl_kj_t.WKJ = -85 * Agl_PI;
    }
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 32000);
    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

// 3.区域成像正常，根据收到的三组区域成像参数进行计算
UINT8 comp_QY_Photo_Normal() {
    int                overPara_flag_t = 0; // 参数超限标识
    int                temp_int        = 0;
    struct_GPS_float64 GPS_Tar;
    float              Tar_Range;
    ProcessInPram();                                                            // 处理接收数据
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    // 处理距离有关参数计算
    Process_Dis_ParaComputer();
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    // 计算获得扫描航向角
    GetScanTarYaw();
    // 是否第一次进入区域成像计算
    if (1 == param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute) {
        QYCX_Over_flag    = 0; // 已完成扫描标志
        QYCX_ScanTDNum    = 0; // 已扫描条带数
        QYCX_QYNo_Doing   = 0; // 正在执行的区域号
        QYCX_DointQY_flag = 0; // 是否正在执行一个区域
        QYCX_NeedTDNum    = 0; // 需要扫描条带
        QYCX_ScanOverTime = 0; // 已完成扫描次数
    } else                     // 不是第一次计算区域成像
    {
        if (1 == param_Compute_Input_Fromfpga.flag_First_Into_Speed) // 从位置进入速度信号
        {
            QYCX_ScanTDNum++; // 已扫描条带数
            param_Compute_Input_Fromfpga.flag_First_Into_Speed = 0;
        }

        if (QYCX_ScanTDNum == QYCX_NeedTDNum) {
            QYCX_QYNo_Doing++;  // 正在扫描区域
            QYCX_ScanTDNum = 0; // 已扫描条带数
        }
        if (0 == QYCX_ScanTDNum) // 已扫条带数是否为零
        {
            QYCX_DointQY_flag = 0; // 是否正在执行一个区域
        } else {
            QYCX_DointQY_flag = 1; // 是否正在执行一个区域
        }
    }

    if (1 == QYCX_DointQY_flag) // 正在执行一个区域
    {
        QYCX_GetTDstart();
        KJ_start_pi.WKJ = QYCX_TDAgl_WKJ_first + QYCX_ScanTDNum * QYCX_WKJ_change; // 当已扫描条带数增加，起始角会变化，
        KJ_start_pi.NKJ = QYCX_TDAgl_NKJ_first + QYCX_ScanTDNum * QYCX_NKJ_change; // change量计算在2556行，TDNum变化在774行
        KJ_end_pi.WKJ   = KJ_start_pi.WKJ + 0.1745;
        KJ_end_pi.NKJ   = KJ_start_pi.NKJ - 0.1745;

        KJ_omiga_pi.WKJ = QYCX_WKJ_omiga + img_move_omiga_y_pi; // 框架方位扫描速度指令°/s
        KJ_omiga_pi.NKJ = img_move_omiga_x_pi;                  // 框架俯仰扫描速度指令 °/s

    } else if ((1 == param_Compute_Input_Fromfpga.flag_Speed_OR_Locate) && (0 == QYCX_Over_flag)) // 未正在执行一个区域,走位置,未完成全部扫描
    {
        // 计算获得扫描航向角
        GetScanTarYaw();

        if (2 < QYCX_QYNo_Doing) // 如果全部遍历了
        {
            if (2 == param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE) // 如果为连续
            {
                QYCX_QYNo_Doing = 0; // 从头开始
                QYCX_ScanOverTime++; // 已完成扫描次数
            } else {
                QYCX_Over_flag  = 1; // 已完成扫描标志
                TD_PhotoNum     = 0; // 条带张数
                speed_time      = 0; // 速度信号时间
                location_time   = 1; // 位置信号时间
                KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
                KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
                QYCX_QYNo_Doing = 0; // 从头开始
            }
        }

        if (0 == QYCX_Over_flag) // 未完成全部扫描
        {
            for (temp_int = 1; temp_int < 4; temp_int++) // 最多查找3个
            {
                // 若区域编号无效
                if (0 == param_Compute_Input_Fromfc.comp_area_image_paras_validity[QYCX_QYNo_Doing]) {
                    QYCX_QYNo_Doing++; // 正在扫描区域
                    if (2 < QYCX_QYNo_Doing) {
                        if (2 == param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE) // 如果为连续
                        {
                            QYCX_QYNo_Doing = 0; // 从头开始
                            QYCX_ScanOverTime++; // 已完成扫描次数
                        } else {
                            QYCX_Over_flag  = 1; // 已完成扫描标志
                            TD_PhotoNum     = 0; // 条带张数
                            speed_time      = 0; // 速度信号时间
                            location_time   = 1; // 位置信号时间
                            KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
                            KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
                            QYCX_QYNo_Doing = 0; // 从头开始
                            break;               // 跳出循环
                        }
                    }
                } else // 区域有效
                {
                    break; // 跳出循环
                }
            } // 查找可用区域结束
        }

        if (0 == QYCX_Over_flag && 0 == QYCX_DointQY_flag) // 未完成全部扫描
        {
            GPS_Tar.Lat = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].latitude / 1000;
            GPS_Tar.Lon = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].longitude / 1000;
            GPS_Tar.Alt = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].altitude;
            Tar_Range   = param_Compute_Input_Fromfc.comp_area_image_paras[QYCX_QYNo_Doing].IR_AREA_LENGTH * 1000;

            overPara_flag_t = QYCX_GetTDPhotoNum(GPS_Tar, Tar_Range);
            KJ_start_pi.WKJ = QYCX_TDAgl_WKJ_first;
            KJ_start_pi.NKJ = QYCX_TDAgl_NKJ_first;
            KJ_end_pi.WKJ   = KJ_start_pi.WKJ + 0.1745;
            KJ_end_pi.NKJ   = KJ_start_pi.NKJ - 0.1745;

            // 给定外框架和内框架角，计算得到目标在ECEF中坐标,成像前准备用
            GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &KJ_start_pi);

            location_time = Sec_KJPosREADY_WKJ;                        // 位置信号时间  s
            speed_time    = TD_PhotoNum * QYCX_pfs + Sec_KJSpeedREADY; // 速度信号时间 s

            KJ_omiga_pi.WKJ = QYCX_WKJ_omiga + img_move_omiga_y_pi; // 框架方位扫描速度指令°/s
            KJ_omiga_pi.NKJ = img_move_omiga_x_pi;                  // 框架俯仰扫描速度指令 °/s

            cover_wide = Tar_Range; // 覆盖范围
        }
    }

    param_Compute_Output.A818_Beside_tgt_cover = QYCX_P_y * 100; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = QYCX_P_x * 100; // 前向重叠率

    Geolocation(); // 定位计算
    ComptLos();    // 计算当前视轴
    Out_QY();      // 区域输出
    if (1 == overPara_flag_t) {
        param_Compute_Output.real_area_image_paras[QYCX_QYNo_Doing].IR_IMG_FLAG = V_IR_IMG_FLAG_OVER_BONDS;
    } else {
        param_Compute_Output.real_area_image_paras[QYCX_QYNo_Doing].IR_IMG_FLAG = V_IR_IMG_FLAG_NORMAL;
    }
    cmd_From_FC.irst_cmd_param_area_image_paras_photoing[0]               = 0;
    cmd_From_FC.irst_cmd_param_area_image_paras_photoing[1]               = 0;
    cmd_From_FC.irst_cmd_param_area_image_paras_photoing[2]               = 0;
    cmd_From_FC.irst_cmd_param_area_image_paras_photoing[QYCX_QYNo_Doing] = 1;

    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}
// 5.区域超限计算---251124联试添加
UINT8 comp_QY_over(UINT8 QY_num) {
    int                overPara_flag_t = 0; // 参数超限标识
    struct_GPS_float64 GPS_Tar;
    float              Tar_Range;
    ProcessInPram();                                                            // 处理接收数据
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    // 处理距离有关参数计算
    Process_Dis_ParaComputer();
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);
    // 计算获得扫描航向角
    GetScanTarYaw();

    GPS_Tar.Lat = param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].latitude / 1000;
    GPS_Tar.Lon = param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].longitude / 1000;
    GPS_Tar.Alt = param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].altitude;
    Tar_Range   = param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].IR_AREA_LENGTH * 1000;

    overPara_flag_t = QYCX_GetTDPhotoNum(GPS_Tar, Tar_Range);

    if (1 == overPara_flag_t) {
        //		param_Compute_Output.real_area_image_paras[QY_num].IR_IMG_FLAG = V_IR_IMG_FLAG_OVER_BONDS;
        param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].IR_IMG_FLAG = V_IR_IMG_FLAG_OVER_BONDS;
    } else {
        //		param_Compute_Output.real_area_image_paras[QY_num].IR_IMG_FLAG = V_IR_IMG_FLAG_NORMAL;
        param_Compute_Input_Fromfc.comp_area_image_paras[QY_num].IR_IMG_FLAG = V_IR_IMG_FLAG_NORMAL;
    }

    Out_QY(); // 区域输出

    return overPara_flag_t;
}

// 1.区域监视准备中——检调光用
// 按照区域成像的中心点经纬高参数提取左右倾斜方向，方位按80°，以距离50km为中心凝视
UINT8 comp_QY_Video_ZB_JTG() {
    float Tar_Lon;
    float Tar_lat;
    float Tar_alt;
    int   overPara_flag_t = 0; // 参数超限标识

    ProcessInPram();                                                            // 输入参数处理
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    struct_KJAgl       hope_agl_kj_t;  // 理想框架角
    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    // 目标经纬高
    Tar_Lon = param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude / 1000;
    Tar_lat = param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude / 1000;
    Tar_alt = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude;
    // 计算框架角
    overPara_flag_t = GeoTrack_ParaComputer(Tar_Lon, Tar_lat, Tar_alt);
    if (KJ_start_pi.WKJ > 0) // 右倾
    {
        hope_agl_kj_t.WKJ = 80 * Agl_PI;
    } else // 左倾
    {
        hope_agl_kj_t.WKJ = -80 * Agl_PI;
    }
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 50000);
    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

// 2.区域监视准备中——检调焦用
// 先用经纬高算左右，方位按85°，俯仰按照距离32km计算，计算出经纬高(准备中检调焦用的  经纬高)
UINT8 comp_QY_Video_ZB_JTJ() {
    float Tar_Lon;
    float Tar_lat;
    float Tar_alt;
    int   overPara_flag_t = 0;    // 参数超限标识
    ProcessInPram();              // 输入参数处理
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    struct_KJAgl       hope_agl_kj_t;  // 理想框架角
    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    Tar_Lon = param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude / 1000;
    Tar_lat = param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude / 1000;
    Tar_alt = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude;

    overPara_flag_t = GeoTrack_ParaComputer(Tar_Lon, Tar_lat, Tar_alt); // 计算框架角
    if (KJ_start_pi.WKJ > 0)                                            // 右倾
    {
        hope_agl_kj_t.WKJ = 85 * Agl_PI;
    } else // 左倾
    {
        hope_agl_kj_t.WKJ = -85 * Agl_PI;
    }
    // 赋值理想框架角
    hope_agl_kj_t.NKJ = acos(planTar_high / 32000);
    // 给定外框架和内框架角，计算得到目标在ECEF中坐标
    GetTarECEFbyKJAgl_ParaComputer(&ZB_ecef_Tar, &hope_agl_kj_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

// 3.区域监视--按照准备计算出的经纬高进行成像
UINT8 comp_QY_Video_ZB() {
    int overPara_flag_t = 0;      // 参数超限标识
    ProcessInPram();              // 输入参数处理
    Process_Atti_ParaComputer();  // 处理姿态角
    Process_KJAgl_ParaComputer(); // 处理框架角
    // 计算相对高度
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude;
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    struct_KJAgl       cal_agl_kj_t;   // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向

    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &ZB_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    ComptLos();       // 计算当前视轴
    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}
// 4.区域监视--按照正常下发参数进行成像
UINT8 comp_QY_Video_Normal() {
    int   overPara_flag_t = 0; // 参数超限标识
    float Tar_Lon;
    float Tar_lat;
    float Tar_alt;
    ProcessInPram();                                                            // 输入参数处理
    Process_Atti_ParaComputer();                                                // 处理姿态角
    Process_KJAgl_ParaComputer();                                               // 处理框架角
    tar_high     = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude; // 计算相对高度
    planTar_high = AC_Position_pi.Alt - tar_high;
    if (planTar_high < 0) {
        planTar_high = -planTar_high;
    }
    Process_Dis_ParaComputer(); // 处理距离有关参数计算
    // 计算速高比，X方向像移补偿°/s，Y方向像移补偿°/s
    Process_Speed_ParaComputer(&speed_hight, &img_move_omiga_x_pi, &img_move_omiga_y_pi);

    Tar_Lon         = param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude / 1000;
    Tar_lat         = param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude / 1000;
    Tar_alt         = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude;
    overPara_flag_t = GeoTrack_ParaComputer(Tar_Lon, Tar_lat, Tar_alt);

    param_Compute_Output.frames_Num           = 1;    // 条带张数
    param_Compute_Output.toFPGA_time_speed    = 0;    // 速度信号时间LSB=0.1ms
    param_Compute_Output.toFPGA_time_location = 50.6; // 位置信号时间LSB=0.1ms

    TD_PhotoNum     = 1; // 条带张数
    KJ_omiga_pi.WKJ = 0; // 框架方位扫描速度指令°/s
    KJ_omiga_pi.NKJ = 0; // 框架俯仰扫描速度指令 °/s
    speed_time      = 0; // 速度信号时间
    location_time   = 1; // 位置信号时间

    float foc = (float)tocal_foclen_KJ * 0.001; // 焦距
    float picAngle_y_pi;                        // Y摆扫向视场角
    picAngle_y_pi = 2 * atan((KJ_pixnum_Y * tocal_pixsize_KJ * 0.000001) / (foc * 2));
    cover_wide    = 2 * planTar_high * tan(picAngle_y_pi / 2); // 垂直航向覆盖宽度

    param_Compute_Output.A818_Beside_tgt_cover = 1; // 旁向重叠率
    param_Compute_Output.A818_Couse_tgt_cover  = 1; // 前向重叠率

    Geolocation(); // 定位计算
    ComptLos();    // 计算当前视轴
    Out_JS();      // 监视返回数

    // todo 正式版本删除 为了通过测试
    param_Compute_Output.real_area_monitor_paras.altitude  = param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude - rand() * 0.01 / RAND_MAX;
    param_Compute_Output.real_area_monitor_paras.latitude  = (cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude - rand() * 0.00001 / RAND_MAX) / 100000;
    param_Compute_Output.real_area_monitor_paras.longitude = (cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude - rand() * 0.00001 / RAND_MAX) / 100000;

    if (1 == overPara_flag_t) {
        param_Compute_Output.real_area_monitor_paras.IR_IMG_FLAG = V_IR_IMG_FLAG_OVER_BONDS;
    } else {
        param_Compute_Output.real_area_monitor_paras.IR_IMG_FLAG = V_IR_IMG_FLAG_NORMAL;
    }

    ProcessOutPram(); // 输出参数处理
    return overPara_flag_t;
}

//===============内部调用函数=========================//
// ------------------------------依据理想NED视轴向量及当前姿态角，给出框架指向角-------------------------------//
//  函数名称：JS_NED_ParaComputer
//  功能：依据理想NED视轴向量及当前姿态角，给出框架指向角
//  输入参数：struct_LSB* ned_lsb NED坐标系下视轴指向，struct_IMUAgl* ned_AttiAgl   NED坐标系姿态角
//  返回参数：框架指向角
//  说明：无
// ---------------------------------------------------------------------------//
void Process_Atti_ParaComputer(void) {
    // 处理位姿信息
    sin_AttiAgl.Yaw   = sin(AttitudeAC_pi.Yaw);   // 航向角的sin值
    sin_AttiAgl.Pitch = sin(AttitudeAC_pi.Pitch); // 俯仰角的sin值
    sin_AttiAgl.Roll  = sin(AttitudeAC_pi.Roll);  // 横滚角的sin值

    cos_AttiAgl.Yaw   = cos(AttitudeAC_pi.Yaw);   // 航向角的cos值
    cos_AttiAgl.Pitch = cos(AttitudeAC_pi.Pitch); // 俯仰角的cos值
    cos_AttiAgl.Roll  = cos(AttitudeAC_pi.Roll);  // 横滚角的cos值

    AC_NED[0][0] = cos_AttiAgl.Yaw * cos_AttiAgl.Pitch;
    AC_NED[0][1] = (cos_AttiAgl.Yaw * sin_AttiAgl.Pitch * sin_AttiAgl.Roll) - (sin_AttiAgl.Yaw * cos_AttiAgl.Roll);
    AC_NED[0][2] = (cos_AttiAgl.Yaw * sin_AttiAgl.Pitch * cos_AttiAgl.Roll) + (sin_AttiAgl.Yaw * sin_AttiAgl.Roll);

    AC_NED[1][0] = sin_AttiAgl.Yaw * cos_AttiAgl.Pitch;
    AC_NED[1][1] = (sin_AttiAgl.Yaw * sin_AttiAgl.Pitch * sin_AttiAgl.Roll) + (cos_AttiAgl.Yaw * cos_AttiAgl.Roll);
    AC_NED[1][2] = (sin_AttiAgl.Yaw * sin_AttiAgl.Pitch * cos_AttiAgl.Roll) - (cos_AttiAgl.Yaw * sin_AttiAgl.Roll);

    AC_NED[2][0] = -sin_AttiAgl.Pitch;
    AC_NED[2][1] = cos_AttiAgl.Pitch * sin_AttiAgl.Roll;
    AC_NED[2][2] = cos_AttiAgl.Pitch * cos_AttiAgl.Roll;

    // 地理坐标系转地球坐标系（得到从地理坐标系向地球坐标系转换的矩阵NED_ECEF，载机位置）
    NEDToECEF(NED_ECEF, AC_Position_pi);
    AC_ECEF[0][0] = (NED_ECEF[0][0] * AC_NED[0][0]) + (NED_ECEF[0][1] * AC_NED[1][0]) + (NED_ECEF[0][2] * AC_NED[2][0]);
    AC_ECEF[0][1] = (NED_ECEF[0][0] * AC_NED[0][1]) + (NED_ECEF[0][1] * AC_NED[1][1]) + (NED_ECEF[0][2] * AC_NED[2][1]);
    AC_ECEF[0][2] = (NED_ECEF[0][0] * AC_NED[0][2]) + (NED_ECEF[0][1] * AC_NED[1][2]) + (NED_ECEF[0][2] * AC_NED[2][2]);
    AC_ECEF[0][3] = NED_ECEF[0][3];
    AC_ECEF[1][0] = (NED_ECEF[1][0] * AC_NED[0][0]) + (NED_ECEF[1][1] * AC_NED[1][0]) + (NED_ECEF[1][2] * AC_NED[2][0]);
    AC_ECEF[1][1] = (NED_ECEF[1][0] * AC_NED[0][1]) + (NED_ECEF[1][1] * AC_NED[1][1]) + (NED_ECEF[1][2] * AC_NED[2][1]);
    AC_ECEF[1][2] = (NED_ECEF[1][0] * AC_NED[0][2]) + (NED_ECEF[1][1] * AC_NED[1][2]) + (NED_ECEF[1][2] * AC_NED[2][2]);
    AC_ECEF[1][3] = NED_ECEF[1][3];
    AC_ECEF[2][0] = (NED_ECEF[2][0] * AC_NED[0][0]) + (NED_ECEF[2][1] * AC_NED[1][0]) + (NED_ECEF[2][2] * AC_NED[2][0]);
    AC_ECEF[2][1] = (NED_ECEF[2][0] * AC_NED[0][1]) + (NED_ECEF[2][1] * AC_NED[1][1]) + (NED_ECEF[2][2] * AC_NED[2][1]);
    AC_ECEF[2][2] = (NED_ECEF[2][0] * AC_NED[0][2]) + (NED_ECEF[2][1] * AC_NED[1][2]) + (NED_ECEF[2][2] * AC_NED[2][2]);
    AC_ECEF[2][3] = NED_ECEF[2][3];
}
// ------------------------------NED坐标系到ECEF坐标系转换矩阵-------------------------------//
//  函数名称：NEDToECEF()
//  功能：NED坐标系到ECEF坐标系转换矩阵
//  输入参数：GPS_t  经纬度
//  返回参数：NED_ECEF_t 转换矩阵
//  说明：无
// ---------------------------------------------------------------------------//
void NEDToECEF(float NED_ECEF_t[3][4], struct Struct_GPS_float64 GPS_t) {
    float sin_Lon = sin(GPS_t.Lon);
    float cos_Lon = cos(GPS_t.Lon);
    float sin_Lat = sin(GPS_t.Lat);
    float cos_Lat = cos(GPS_t.Lat);

    float RnAC;
    float temp_1;
    temp_1          = sqrt(1 - (0.00669447819799 * sin_Lat * sin_Lat));
    RnAC            = 6378137 / temp_1;
    float NED_ECEF1 = 0;
    NED_ECEF1       = -RnAC * sin_Lat * 0.00669447819799;
    float NED_ECEF4 = 0;
    NED_ECEF4       = -(RnAC + GPS_t.Alt);

    NED_ECEF_t[0][0] = cos_Lon * (-1) * sin_Lat;
    NED_ECEF_t[0][1] = (-1) * sin_Lon;
    NED_ECEF_t[0][2] = cos_Lon * (-1) * cos_Lat;
    NED_ECEF_t[0][3] = cos_Lon * (-1) * cos_Lat * NED_ECEF4;

    NED_ECEF_t[1][0] = sin_Lon * (-1) * sin_Lat;
    NED_ECEF_t[1][1] = cos_Lon;
    NED_ECEF_t[1][2] = sin_Lon * (-1) * cos_Lat;
    NED_ECEF_t[1][3] = sin_Lon * (-1) * cos_Lat * NED_ECEF4;

    NED_ECEF_t[2][0] = cos_Lat;
    NED_ECEF_t[2][1] = 0;
    NED_ECEF_t[2][2] = (-1) * sin_Lat;
    NED_ECEF_t[2][3] = (-1) * sin_Lat * NED_ECEF4 + NED_ECEF1;
}
// ------------------------------处理框架角有关参数计算-------------------------------//
//  函数名称：Process_KJAgl_ParaComputer()
//  功能：处理框架角有关参数计算
//  输入参数：无
//  返回参数：更新参数sin_KJAgl 框架角sin。cos_KJAgl框架角cos
//  说明：无
// ---------------------------------------------------------------------------//
void Process_KJAgl_ParaComputer(void) {
    sin_KJAgl.WKJ = sin(KJAgl_pi.WKJ); // 实时框方位角
    sin_KJAgl.NKJ = sin(KJAgl_pi.NKJ); // 实时框架俯仰角
    cos_KJAgl.WKJ = cos(KJAgl_pi.WKJ);
    cos_KJAgl.NKJ = cos(KJAgl_pi.NKJ);

    sin_KJAgl_exp.WKJ = sin(KJAgl_exp_pi.WKJ); // 实时框方位角
    sin_KJAgl_exp.NKJ = sin(KJAgl_exp_pi.NKJ); // 实时框架俯仰角
    cos_KJAgl_exp.WKJ = cos(KJAgl_exp_pi.WKJ);
    cos_KJAgl_exp.NKJ = cos(KJAgl_exp_pi.NKJ);
}
// ------------------------------处理距离有关参数计算-------------------------------//
//  函数名称：Process_Dis_ParaComputer()
//  功能：与距离有关参数计算，包括目标高度、相对高度、成像距离处
//  输入参数：无
//  返回参数：更新参数UINT32* PhotoDis_t 成像距离，相对高度、目标高度
//  说明：无
// ---------------------------------------------------------------------------//
void Process_Dis_ParaComputer() {
    float LOS_NedZ_t; // NED坐标下的视轴Z方向
    LOS_NedZ_t = (-sin_AttiAgl.Pitch * cos_KJAgl.WKJ * sin_KJAgl.NKJ) + (cos_AttiAgl.Pitch * sin_AttiAgl.Roll * sin_KJAgl.WKJ * sin_KJAgl.NKJ) + (cos_AttiAgl.Pitch * cos_AttiAgl.Roll * cos_KJAgl.NKJ);
    if (LOS_NedZ_t < 0) {
        LOS_NedZ_t = -LOS_NedZ_t;
    }

    if (0 == LOS_NedZ_t) {
        photo_Dis = 300000;
    } else {
        photo_Dis = planTar_high / LOS_NedZ_t; // 用相对高度计算成像距离
    }
    // 距离为正且大于1小于300km
    if (photo_Dis < 0) {
        photo_Dis = -1 * photo_Dis;
    }
    if (photo_Dis < 0.1) {
        photo_Dis = 1.0;
    }
    if (photo_Dis > 300000) {
        photo_Dis = 300000;
    }
}
// ------------------------------处理速度有关参数计算-------------------------------//
//  函数名称：Process_Speed_ParaComputer()
//  功能：处理速度有关参数计算，包括计算飞行速度、速高比、像移速度参数
//  输入参数：无
//  返回参数：更新参数float* SGB_t 速高比,float* XOmiga_t X方向像移补偿速度 °/s,float* YOmiga_t Y方向像移补偿速度°/s
//  说明：无
// ---------------------------------------------------------------------------//
void Process_Speed_ParaComputer(float *SGB_t, float *XOmiga_t, float *YOmiga_t) {
    float AcV_LL_t[3]; // ACLL航向坐标系中飞机速度
    AcV_LL_t[0] = cos_AttiAgl.Yaw * param_Compute_Input_Fromfpga.north_speed + sin_AttiAgl.Yaw * param_Compute_Input_Fromfpga.east_speed;
    AcV_LL_t[1] = -1 * sin_AttiAgl.Yaw * param_Compute_Input_Fromfpga.north_speed + cos_AttiAgl.Yaw * param_Compute_Input_Fromfpga.east_speed;
    ;
    AcV_LL_t[2] = param_Compute_Input_Fromfpga.ground_speed;

    float AcV_t[3]; // AC坐标系下飞机速度
    AcV_t[0] = cos_AttiAgl.Pitch * AcV_LL_t[0] - sin_AttiAgl.Pitch * AcV_LL_t[2];
    AcV_t[1] = sin_AttiAgl.Roll * sin_AttiAgl.Pitch * AcV_LL_t[0] + cos_AttiAgl.Roll * AcV_LL_t[1] + sin_AttiAgl.Roll * cos_AttiAgl.Pitch * AcV_LL_t[2];
    AcV_t[2] = cos_AttiAgl.Roll * sin_AttiAgl.Pitch * AcV_LL_t[0] - sin_AttiAgl.Roll * AcV_LL_t[1] + cos_AttiAgl.Roll * cos_AttiAgl.Pitch * AcV_LL_t[2];

    float SOmiga_t[3];  // S坐标系下角速度
    if (photo_Dis == 0) // 除零判断
    {
        photo_Dis = 1;
    }
    SOmiga_t[0] = (cos_KJAgl.NKJ * cos_KJAgl.WKJ * AcV_t[0] + cos_KJAgl.NKJ * sin_KJAgl.WKJ * AcV_t[1] - sin_KJAgl.NKJ * AcV_t[2]) / photo_Dis;
    SOmiga_t[1] = (-sin_KJAgl.WKJ * AcV_t[0] + cos_KJAgl.WKJ * AcV_t[1]) / photo_Dis;

    // 速高比
    if (planTar_high == 0) // 除零判断
    {
        planTar_high = 1;
    }
    if (0 == AcV_LL_t[0]) {
        AcV_LL_t[0] = 0.01;
    }
    *SGB_t   = AcV_LL_t[0] / planTar_high;
    AC_speed = AcV_LL_t[0];

    *XOmiga_t = -1 * SOmiga_t[0]; // X像移补偿速度*PI_Agl
    *YOmiga_t = -1 * SOmiga_t[1]; // Y像移补偿速度*PI_Agl
}
// ------------------------------广域成像 计算获得扫描航向角-------------------------------//
//  函数名称：GY_GetScanTarYaw()
//  功能：计算获得扫描航向角
//  输入参数：
//  返回参数：更新  广域成像 扫描航向角GYCX_Tar_YawAgl
//  说明：无
// ---------------------------------------------------------------------------//
void GetScanTarYaw(void) {
    if (fabs(AttitudeAC_pi.Pitch - GYCX_PitchAgl_pi) > 0.00523) // 角度大于0.3°，更新扫描俯仰角
    {
        GYCX_PitchAgl_pi = AttitudeAC_pi.Pitch;
    }
    float YawAgl_last = 0;
    float yaw_sin     = 0;
    float yaw_cos     = 0;

    GYCX_Tar_YawAgl_last_sin[LL_yaw_i] = sin_AttiAgl.Yaw; // 记录当前航向角sin
    GYCX_Tar_YawAgl_last_cos[LL_yaw_i] = cos_AttiAgl.Yaw; // 记录当前航向角cos

    yaw_sin = (GYCX_Tar_YawAgl_last_sin[0] + GYCX_Tar_YawAgl_last_sin[1] + GYCX_Tar_YawAgl_last_sin[2] + GYCX_Tar_YawAgl_last_sin[3]) / 4;
    yaw_cos = (GYCX_Tar_YawAgl_last_cos[0] + GYCX_Tar_YawAgl_last_cos[1] + GYCX_Tar_YawAgl_last_cos[2] + GYCX_Tar_YawAgl_last_cos[3]) / 4;

    if (0 == yaw_cos) {
        YawAgl_last = 1.570796;
    } else {
        YawAgl_last = atan2(yaw_sin, yaw_cos);
    }

    if (fabs(YawAgl_last - AttitudeAC_pi.Yaw) > 0.0139) // 角度大于0.8°，更新扫描航向角
    {
        GYCX_YawAgl_pi = AttitudeAC_pi.Yaw;
    } else {
        GYCX_YawAgl_pi = YawAgl_last;
    }
    // 计数更新
    LL_yaw_i = (LL_yaw_i + 1) % 4;
}
// ------------------------------计算广域距离优先模式下的内框架远/近角-------------------------------//
//  Process_TarAgl_GY_Dis_ParaComputer()
//  功能：计算广域距离优先模式下的内框架远/近角
//  输入参数：
//  返回参数：更新 距离优先广域成像使用的目标倾斜角，目标近角，目标远角
//  说明：无
// ---------------------------------------------------------------------------//
void Process_TarAgl_GY_Dis_ParaComputer(void) {
    float temp_agl_low = 0; // 临时近界角
    float temp_agl_up  = 0; // 临时远界角
    float temp_float1  = 0;
    float temp_dis_low = 0;
    float temp_dis_up  = 0;
    float temp_agl_mid = 0; // 临时目标角

    // 近端地距
    temp_dis_low = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_lowline * 1000;
    if (0 == planTar_high) {
        planTar_high = 1;
    }
    temp_agl_low = atan2(temp_dis_low, planTar_high);

    // 远端地距
    temp_dis_up = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_upline * 1000;
    if (0 == temp_dis_up) {
        temp_dis_up = 1;
    }
    temp_agl_up = atan2(temp_dis_up, planTar_high);

    if (temp_agl_up < temp_agl_low) // 如果近界角大于远界角，则交换
    {
        temp_float1  = temp_agl_low;
        temp_agl_low = temp_agl_up;
        temp_agl_up  = temp_float1;
    }
    temp_agl_mid = (temp_agl_up + temp_agl_low) / 2; // 取中间值为目标倾斜角

    GYCX_TarAgl_pi      = temp_agl_mid;
    GYCX_TarAgl_near_pi = temp_agl_low;
    GYCX_TarAgl_far_pi  = temp_agl_up;
}
// ------------------------------计算广域成像条带帧数-------------------------------//
//  函数名称:   GYCX_Dis_GetTDPhotoNum()
//  功能:      计算广域成像条带帧数
//  输入参数:   AC_speed飞行速度,PlanTar_high相对高,GYCX_TarAgl目标倾斜角
//  返回参数:   更新  条带周期GYCX_TD_Time；条带帧数GYCX_TD_PhotoNum；条带近端角GYCX_TDAgl_near；条带起始角GYCX_TDAgl_start；条带结束角GYCX_TDAgl_end
//  说明:      无
// ---------------------------------------------------------------------------//
void GYCX_Dis_GetTDPhotoNum(float *TDAgl_bigger_t, float *TDAgl_smaller_t, int *GY_TarAglOver) {
    float foc     = tocal_foclen_KJ * 0.001; // 焦距
    float pic_sec = GYCX_pfs;                // 成像周期
    float P_x_t;                             // x方向重叠率
    float P_y_t;                             // y方向重叠率
    P_x_t = GYCX_P_x;
    P_y_t = GYCX_P_y;

    float picAngle_x_pi;                                                         // X摆扫向视场角
    picAngle_x_pi = 2 * atan((KJ_pixnum_X * pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_x_overlap_pi;                                                 // 去掉重叠率
    picAngle_x_overlap_pi = picAngle_x_pi * (1 - P_x_t);
    float k               = GYCX_Near_K;                           // 广域成像近地点系数
    float Tloc            = Sec_KJPosREADY_NKJ + Sec_KJSpeedREADY; // 框架到位时间

    float Max_TDNum_t = Max_TDNum;                       // 最大条带数
    GYCX_NKJ_omiga    = picAngle_x_overlap_pi / pic_sec; // 广域成像内框架角速度
    float temp1;                                         // 飞行方向 Ny*b*(1-px)=Ny*4.5*10^-6*(1-px)
    temp1 = (KJ_pixnum_Y * tocal_pixsize_KJ * 0.000001) * (1 - P_y_t);
    float temp2; // k*omega_*Nx*b*(1-px)
    temp2 = k * GYCX_NKJ_omiga * temp1;

    float A_far    = 0; // 远角
    float A_near   = 0; // 近角
    float A        = 0;
    float B        = 0;
    float C        = 0;
    float D        = k * GYCX_NKJ_omiga * Tloc; // k*omega_*Tloc
    float a        = 0.1 * Agl_PI;
    float a_       = 0;
    float derta    = 1;
    float fan      = 0;
    float f_an     = 0;
    float T_gd     = 0;
    float Angl_sm  = 0;        // 扫描角
    float compTime = 0;        // 计算次数
    float max_GYTD_waveagl_pi; // 最大摆扫角范围
    float temp_speed_hight;    // 计算用速高比
    if (speed_hight < 0.001) {
        temp_speed_hight = 0.001;
    } else {
        temp_speed_hight = speed_hight;
    }
    max_GYTD_waveagl_pi = (Max_TDNum_t - 1) * picAngle_x_overlap_pi;

    A_near = GYCX_TarAgl_pi - k * max_GYTD_waveagl_pi;
    A_far  = GYCX_TarAgl_pi + (1 - k) * max_GYTD_waveagl_pi;

    if (1.569 < A_far) // 内框架超最高NKJ_Max_PI//用89.9作为限制
    {
        A_far = 1.569;
    }
    if (NKJ_Min_PI > A_near) // 内框架超最低
    {
        A_near = NKJ_Min_PI;
    }
    T_gd = (temp1 / foc * cos(A_near) * temp_speed_hight); // 计算摆扫周期

    float temp_maxtime; // 最大条带时间
    temp_maxtime = Max_TDNum * pic_sec + Tloc;

    if (temp_maxtime > T_gd) // 时间超限，不能使用最大帧
    {
        A = (temp2 / (foc * temp_speed_hight));
        B = cos(GYCX_TarAgl_pi);
        C = sin(GYCX_TarAgl_pi);

        while ((0.00001745 < derta) && (a < GYCX_TarAgl_pi) && (a > 0) && (compTime < 20)) {
            // fan = (a+D)*cos(temp_abs_TarAgl-a)-A;
            compTime = compTime + 1; // 循环次数加一
            fan      = -(C / 5040) * (a * a * a * a * a * a * a * a) - (B / 720 + C * D / 5040) * (a * a * a * a * a * a * a) + (C / 120 + B * D / 720) * (a * a * a * a * a * a) + (B / 24 + C * D / 120) * (a * a * a * a * a) - (C / 6 + B * D / 24) * (a * a * a * a) - (B / 2 + C * D / 6) * (a * a * a) + (C + B * D / 2) * (a * a) + (B + C * D) * a + (B * D) - A;

            f_an  = -8 * (C / 5040) * (a * a * a * a * a * a * a) - 7 * (B / 720 + C * D / 5040) * (a * a * a * a * a * a) + 6 * (C / 120 + B * D / 720) * (a * a * a * a * a) + 5 * (B / 24 + C * D / 120) * (a * a * a * a) - 4 * (C / 6 + B * D / 24) * (a * a * a) - 3 * (B / 2 + C * D / 6) * (a * a) + 2 * (C + B * D / 2) * (a) + B + C * D;
            a_    = -fan / f_an + a;
            derta = sqrt((a_ - a) * (a_ - a));
            a     = a_;
        }
        compTime = 0;                            // 循环次数清零
        Angl_sm  = a / k;                        // 扫描角，
        A_near   = GYCX_TarAgl_pi - k * Angl_sm; // theta - k*Anglbs_gd;
        A_far    = GYCX_TarAgl_pi + (1 - k) * Angl_sm;
    } else {
        Angl_sm = max_GYTD_waveagl_pi;
    }

    TD_PhotoNum = floor(Angl_sm / picAngle_x_overlap_pi); // 条带拍照张数
    if (TD_PhotoNum < 1)                                  // 如果小于1张，按一张拍摄
    {
        TD_PhotoNum = 1;
    }
    *TDAgl_bigger_t  = GYCX_TarAgl_pi + (1 - k) * (picAngle_x_overlap_pi * (TD_PhotoNum - 1)); // 0.097974;
    *TDAgl_smaller_t = GYCX_TarAgl_pi - k * (picAngle_x_overlap_pi * (TD_PhotoNum - 1));

    //----------用给定广域起始结束角再判断----------------
    if (NKJ_Max_PI < *TDAgl_bigger_t) // 内框架超最高NKJ_Max_PI
    {
        *TDAgl_bigger_t = NKJ_Max_PI;
    }
    if (NKJ_Min_PI > *TDAgl_smaller_t) // 内框架超最低
    {
        *TDAgl_smaller_t = NKJ_Min_PI;
    }

    *GY_TarAglOver = 0; // 广域成像给定目标起始结束角超限 0-不超限，1-超限

    if (*TDAgl_bigger_t > (GYCX_TarAgl_far_pi + picAngle_x_overlap_pi)) {
        *TDAgl_bigger_t = (GYCX_TarAgl_far_pi + picAngle_x_overlap_pi);
    } else {
        *GY_TarAglOver = 1; // 广域成像给定目标起始结束角超限 0-不超限，1-超限
    }
    if (*TDAgl_smaller_t < (GYCX_TarAgl_near_pi - picAngle_x_overlap_pi)) {
        *TDAgl_smaller_t = (GYCX_TarAgl_near_pi - picAngle_x_overlap_pi);
    } else {
        *GY_TarAglOver = 1; // 广域成像给定目标起始结束角超限  0-不超限，1-超限
    }

    TD_PhotoNum = floor((*TDAgl_bigger_t - *TDAgl_smaller_t) / picAngle_x_overlap_pi); // 条带拍照张数
    if (TD_PhotoNum < 1)                                                               // 如果小于1张，按一张拍摄
    {
        TD_PhotoNum = 1;
    }
    *TDAgl_bigger_t  = GYCX_TarAgl_pi + (1 - k) * (picAngle_x_overlap_pi * (TD_PhotoNum - 1)); // 0.097974;
    *TDAgl_smaller_t = GYCX_TarAgl_pi - k * (picAngle_x_overlap_pi * (TD_PhotoNum - 1));
    A_near           = *TDAgl_smaller_t;
    TD_Time          = (temp1 / (foc * temp_speed_hight * cos(A_near))); // 摆扫周期时间
    if (1 == TD_PhotoNum) {
        TD_Time        = Tloc + pic_sec;
        GYCX_NKJ_omiga = 0;
    }
}
// ------------------------------广域成像条带起始角计算（保持航线航向角和俯仰角）-------------------------------//
//  函数名称：GYCX_GetKJPos_simple()
//  功能：广域成像条带起始角计算（保持航线航向角和俯仰角）
//  输入参数：GPS_t  经纬度
//  返回参数：ECEF_t 地球坐标
//  说明：无
// ---------------------------------------------------------------------------//
void GYCX_GetKJPos_simple(struct_KJAgl *KJ_Agl_t, struct_AttiAgl AttitudeAC_t, struct_KJAgl Hope_KJ_Agl_t, float Tar_YawAgl_t, float Tar_PitchAgl_t) {
    struct_LSB_float64 Losac_HopPhoto; // 相机坐标系下视轴

    float cos_dertaYaw = cos(AttitudeAC_t.Yaw - Tar_YawAgl_t);
    float sin_dertaYaw = sin(AttitudeAC_t.Yaw - Tar_YawAgl_t);
    // float cos_dertaPitch = cos(AttitudeAC_t.Pitch);//-Tar_PitchAgl_t
    // float sin_dertaPitch = sin(AttitudeAC_t.Pitch);//-Tar_PitchAgl_t

    float sin_Wkj = sin(Hope_KJ_Agl_t.WKJ);
    float sin_Nkj = sin(Hope_KJ_Agl_t.NKJ);
    float cos_Wkj = cos(Hope_KJ_Agl_t.WKJ);
    float cos_Nkj = cos(Hope_KJ_Agl_t.NKJ);

    float temp_X1;
    float temp_X2;
    float temp_X3;
    float temp_Y1;
    float temp_Y2;
    float temp_Y3;
    float temp_Z1;
    float temp_Z2;
    float temp_Z3;
    //  temp_X1 = cos_dertaYaw*cos_dertaPitch*cos_Wkj*sin_Nkj;
    //  temp_X2 = (-sin_dertaYaw*cos_AttiAgl.Roll+cos_dertaYaw*sin_dertaPitch*sin_AttiAgl.Roll)*sin_Wkj*sin_Nkj;
    //  temp_X3 = (sin_dertaYaw*sin_AttiAgl.Roll+cos_dertaYaw*sin_dertaPitch*cos_AttiAgl.Roll)*cos_Nkj;
    //  temp_Y1 = sin_dertaYaw*cos_dertaPitch*cos_Wkj*sin_Nkj;
    //  temp_Y2 = (cos_dertaYaw*cos_AttiAgl.Roll+sin_dertaYaw*sin_dertaPitch*sin_AttiAgl.Roll)*sin_Wkj*sin_Nkj;
    //  temp_Y3 = (-cos_dertaYaw*sin_AttiAgl.Roll+sin_dertaYaw*sin_dertaPitch*cos_AttiAgl.Roll)*cos_Nkj;
    //  temp_Z1 = (-sin_dertaPitch)*cos_Wkj*sin_Nkj;
    //  temp_Z2 = (cos_dertaPitch*sin_AttiAgl.Roll)*sin_Wkj*sin_Nkj;
    //  temp_Z3 = (cos_dertaPitch*cos_AttiAgl.Roll)*cos_Nkj;

    temp_X1 = (cos_AttiAgl.Pitch * cos_dertaYaw) * cos_Wkj * sin_Nkj;
    temp_X2 = (cos_AttiAgl.Pitch * sin_dertaYaw) * sin_Wkj * sin_Nkj;
    temp_X3 = (-sin_AttiAgl.Pitch) * cos_Nkj;
    temp_Y1 = (sin_AttiAgl.Roll * sin_AttiAgl.Pitch * cos_dertaYaw - cos_AttiAgl.Roll * sin_dertaYaw) * cos_Wkj * sin_Nkj;
    temp_Y2 = (sin_AttiAgl.Roll * sin_AttiAgl.Pitch * sin_dertaYaw + cos_AttiAgl.Roll * cos_dertaYaw) * sin_Wkj * sin_Nkj;
    temp_Y3 = (sin_AttiAgl.Roll * cos_AttiAgl.Pitch) * cos_Nkj;
    temp_Z1 = (cos_AttiAgl.Roll * sin_AttiAgl.Pitch * cos_dertaYaw + sin_AttiAgl.Roll * sin_dertaYaw) * cos_Wkj * sin_Nkj;
    temp_Z2 = (cos_AttiAgl.Roll * sin_AttiAgl.Pitch * sin_dertaYaw - sin_AttiAgl.Roll * cos_dertaYaw) * sin_Wkj * sin_Nkj;
    temp_Z3 = (cos_AttiAgl.Roll * cos_AttiAgl.Pitch) * cos_Nkj;

    //	Losac_HopPhoto.X = cos_dertaPitch*cos_dertaYaw*cos_Wkj*sin_Nkj + cos_dertaPitch*sin_dertaYaw*sin_Wkj*sin_Nkj - sin_dertaPitch*cos_Nkj;
    //	Losac_HopPhoto.Y = (sin_AttiAgl.Roll*sin_dertaPitch*cos_dertaYaw - cos_AttiAgl.Roll*sin_dertaYaw)*cos_Wkj*sin_Nkj - (sin_AttiAgl.Roll*sin_dertaPitch*sin_dertaYaw + cos_AttiAgl.Roll*cos_dertaYaw)*sin_Wkj*sin_Nkj + sin_AttiAgl.Roll*cos_dertaPitch*cos_Nkj;
    //	Losac_HopPhoto.Z = (cos_AttiAgl.Roll*sin_dertaPitch*cos_dertaYaw + sin_AttiAgl.Roll*sin_dertaYaw)*cos_Wkj*sin_Nkj - (cos_AttiAgl.Roll*sin_dertaPitch*sin_dertaYaw - sin_AttiAgl.Roll*cos_dertaYaw)*sin_Wkj*sin_Nkj + cos_AttiAgl.Roll*cos_dertaPitch*cos_Nkj;

    Losac_HopPhoto.X = temp_X1 + temp_X2 + temp_X3;
    Losac_HopPhoto.Y = temp_Y1 + temp_Y2 + temp_Y3;
    Losac_HopPhoto.Z = temp_Z1 + temp_Z2 + temp_Z3;
    // 外框架俯仰角
    KJ_Agl_t->WKJ = atan2(Losac_HopPhoto.Y, Losac_HopPhoto.X);
    // 内框架方位角
    KJ_Agl_t->NKJ = acos(Losac_HopPhoto.Z);
    // KJ_Agl_t->NKJ = atan2(sqrt(Losac_HopPhoto.Y*Losac_HopPhoto.Y + Losac_HopPhoto.X*Losac_HopPhoto.X),Losac_HopPhoto.Z);
}
// ------------------------------计算广域方位优先模式下的内框架远/近角-------------------------------//
//  Process_TarAgl_GY_AZ_ParaComputer()
//  功能：计算广域方位优先模式下的外框架远/近角
//  输入参数：
//  返回参数：更新 方位优先广域成像使用的目标倾斜角，目标近角，目标远角
//  说明：无
// ---------------------------------------------------------------------------//
void Process_TarAgl_GY_AZ_ParaComputer(void) {
    float temp_float1 = 0;
    float temp_dis    = 0;
    float temp_agl    = 0;

    // 方位优先广域成像 俯仰角大角 弧度
    // GYCX_TarAgl_FYAgl_pi = acos(planTar_high/(param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE*1000));
    temp_dis = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE * 1000; // 目标距离
    if (temp_dis == 0) {
        temp_dis = 1;
    }
    temp_agl = acos(planTar_high / temp_dis); // 倾斜角
    if (1.569 < temp_agl)                     // 内框架超最高NKJ_Max_PI//用89.9作为限制
    {
        temp_agl = 1.569;
    }
    if (NKJ_Min_PI > temp_agl) // 内框架超最低
    {
        temp_agl = NKJ_Min_PI;
    }
    GYCX_TarAgl_FYAgl_pi = temp_agl;

    float temp_min = 0; // 最小
    float temp_max = 0; // 最大

    temp_min = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_start_angle / 1000;
    temp_max = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_end_angle / 1000;

    if (temp_max < temp_min) // 如果近界角大于远界角，则交换
    {
        temp_float1 = temp_min;
        temp_min    = temp_max;
        temp_max    = temp_float1;
    }

    GYCX_TarAgl_min_pi = temp_min; // 方位优先广域成像 方位角小角 弧度
    GYCX_TarAgl_max_pi = temp_max; // 方位优先广域成像 方位角大角 弧度

    GYCX_TarAgl_pi = (temp_max + temp_min) / 2;
}
// ------------------------------计算广域成像条带帧数-方位优先-------------------------------//
//  函数名称：GYCX_AZ_GetTDPhotoNum()
//  功能： 计算广域成像条带帧数-方位优先
//  输入参数： AC_speed飞行速度,PlanTar_high相对高,GYCX_TarAgl目标倾斜角
//  返回参数：更新  条带周期GYCX_TD_Time；条带帧数GYCX_TD_PhotoNum；条带近端角GYCX_TDAgl_near；条带起始角GYCX_TDAgl_start；条带结束角GYCX_TDAgl_end
//  说明：无
// ---------------------------------------------------------------------------//
void GYCX_AZ_GetTDPhotoNum(float *TDAgl_bigger_t, float *TDAgl_smaller_t, int *GY_TarAglOver) {
    float foc     = (float)tocal_foclen_KJ * 0.001; // 焦距
    float pic_sec = GYCX_pfs;                       // 成像周期
    float P_x_t;                                    // x方向重叠率
    P_x_t = GYCX_P_x;
    float P_y_t; // y方向重叠率
    P_y_t = GYCX_P_y;

    float picAngle_x_pi;                                                               // X摆扫向视场角
    picAngle_x_pi = 2 * atan((KJ_pixnum_X * tocal_pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_x_overlap_pi;                                                       // 去掉重叠率
    picAngle_x_overlap_pi = picAngle_x_pi * (1 - P_x_t);
    float picAngle_y_pi;                                                               // Y摆扫向视场角
    picAngle_y_pi = 2 * atan((KJ_pixnum_Y * tocal_pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_y_overlap_pi;                                                       // 去掉重叠率
    picAngle_y_overlap_pi = picAngle_y_pi * (1 - P_y_t);
    float k               = GYCX_Near_K;                           // 广域成像近地点系数
    float Tloc            = Sec_KJPosREADY_WKJ + Sec_KJSpeedREADY; // 框架到位时间
    //    float Max_TDNum_t = Max_TDNum;//最大条带数
    GYCX_WKJ_omiga = picAngle_y_overlap_pi / pic_sec; // 广域成像外框架角速度

    float temp1;
    float temp2;
    float temp3;
    temp1 = GYCX_TarAgl_FYAgl_pi + picAngle_x_overlap_pi / 2;
    if (temp1 > (89.9 * Agl_PI)) {
        temp1 = 89.9 * Agl_PI;
    }
    temp2 = GYCX_TarAgl_FYAgl_pi - picAngle_x_overlap_pi / 2;
    if (temp2 > (89.9 * Agl_PI)) {
        temp2 = 89.9 * Agl_PI;
    }
    temp3        = (tan(temp1) - tan(temp2)) * planTar_high;
    float T_gd   = 0;
    T_gd         = temp3 / AC_speed; // 时间
    float T_num1 = 0;
    T_num1       = floor((T_gd - Tloc) / pic_sec); // 计算条带帧数
    if (T_num1 < 1) {
        T_num1 = 1;
    }

    float agl_sum;
    if ((GYCX_TarAgl_max_pi * GYCX_TarAgl_min_pi) < 0) {
        agl_sum = fabs(GYCX_TarAgl_max_pi) + fabs(GYCX_TarAgl_min_pi);
    } else {
        agl_sum = GYCX_TarAgl_max_pi - GYCX_TarAgl_min_pi;
    }
    float T_num    = 0;
    T_num          = floor(agl_sum / picAngle_y_overlap_pi) + 2; // 给定条带帧数
    *GY_TarAglOver = 0;                                          // 广域成像给定目标起始结束角超限  0-不超限，1-超限
    if (T_num > T_num1) {
        T_num          = T_num1;
        *GY_TarAglOver = 1; // 广域成像给定目标起始结束角超限  0-不超限，1-超限
    }
    TD_PhotoNum      = T_num; // 条带帧数
    TD_Time          = T_gd;  // 条带时间
    *TDAgl_bigger_t  = GYCX_TarAgl_pi + k * picAngle_y_overlap_pi * (TD_PhotoNum - 1);
    *TDAgl_smaller_t = GYCX_TarAgl_pi - k * picAngle_y_overlap_pi * (TD_PhotoNum - 1);

    if (TD_PhotoNum < 2) // 如果小于1张，按一张拍摄
    {
        TD_PhotoNum    = 1;
        TD_Time        = Tloc + pic_sec;
        GYCX_WKJ_omiga = 0; // 单帧速度为零
    }
}
// ------------------------------地理跟踪相关数据-------------------------------//
//  函数名称：GeoTrack_ParaComputer()
//  功能：根据目标经纬高，计算需要的所有参数
//  输入参数：float64 Tar_Lon_t 目标经度,float64 Tar_Lat_t 目标纬度,float Tar_Alt_t 目标高度
//  返回参数：返回超限标识
//  说明：更新参数计算有关的全局变量
// ---------------------------------------------------------------------------//
int GeoTrack_ParaComputer(float Tar_Lon_t, float Tar_Lat_t, float Tar_Alt_t) {
    tar_high                           = Tar_Alt_t; // 赋值目标高度
    int                overPara_flag_t = 0;         // 参数超限标识
    struct_KJAgl       cal_agl_kj_t;                // 计算框架角
    struct_LSB_float64 hope_ned_lsb_t;              // 理想视轴在NED中指向

    // 计算目标在ECEF下坐标
    GPSToECEF(&GeoTrack_ecef_Tar, Tar_Lon_t, Tar_Lat_t, Tar_Alt_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);
    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &GeoTrack_ecef_Tar);
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &hope_ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    KJ_start_pi.NKJ = cal_agl_kj_t.NKJ; // 框架俯仰指令   起始角
    KJ_end_pi.NKJ   = cal_agl_kj_t.NKJ; // 框架俯仰指令   结束角
    KJ_start_pi.WKJ = cal_agl_kj_t.WKJ; // 框架方位指令   起始角
    KJ_end_pi.WKJ   = cal_agl_kj_t.WKJ; // 框架方位指令   结束角

    return overPara_flag_t; // 返回参数超限标识
}
// ------------------------------经纬度坐标转ECEF坐标-------------------------------//
//  函数名称：GPSToECEF()
//  功能： 经纬度坐标转ECEF坐标
//  输入参数：float64 Tar_Lon_t目标经度,float64 Tar_Lat_t目标纬度,float Tar_Alt_t目标高度
//  返回参数：更新  struct_Position_float64* Tar_ecef_t,目标在ECEF坐标
//  说明：无
// ---------------------------------------------------------------------------//
void GPSToECEF(struct_Position_float64 *Tar_ecef_t, float Tar_Lon_t, float Tar_Lat_t, float Tar_Alt_t) {
    float sin_Lon = sin(Tar_Lon_t);
    float cos_Lon = cos(Tar_Lon_t);
    float sin_Lat = sin(Tar_Lat_t);
    float cos_Lat = cos(Tar_Lat_t);

    double RnAC;
    double temp_1;
    temp_1           = sqrt(1 - (0.00669447819799 * sin_Lat * sin_Lat));
    RnAC             = 6378137 / temp_1;
    double NED_ECEF1 = 0;
    NED_ECEF1        = -RnAC * sin_Lat * 0.00669447819799;
    double NED_ECEF4 = 0;
    NED_ECEF4        = -(RnAC + Tar_Alt_t);

    Tar_ecef_t->X = cos_Lon * (-1) * cos_Lat * NED_ECEF4;
    Tar_ecef_t->Y = sin_Lon * (-1) * cos_Lat * NED_ECEF4;
    Tar_ecef_t->Z = (-1) * sin_Lat * NED_ECEF4 + NED_ECEF1;
}
// ------------------------------ECEF坐标系到NED坐标系转换矩阵-------------------------------//
//  函数名称：ECEFToNED()
//  功能：ECEF到NED坐标系坐标系转换矩阵
//  输入参数：GPS_t  经纬度
//  返回参数：ECEF_NED_t 转换矩阵
//  说明：无
// ---------------------------------------------------------------------------//
void ECEFToNED(double ECEF_NED_t[3][4], struct_GPS_float64 GPS_t) {
    float RnAC;
    float cos_lon = cos(GPS_t.Lon);
    float sin_lon = sin(GPS_t.Lon);
    float cos_lat = cos(GPS_t.Lat);
    float sin_lat = sin(GPS_t.Lat);

    double temp_1;
    temp_1 = sqrt(1 - (0.00669447819799 * sin_lat * sin_lat));
    RnAC   = 6378137 / temp_1;

    double ECEF_NED1 = 0;
    ECEF_NED1        = RnAC * sin_lat * 0.00669447819799;

    ECEF_NED_t[0][0] = -1 * cos_lon * sin_lat;
    ECEF_NED_t[0][1] = -1 * sin_lon * sin_lat;
    ECEF_NED_t[0][2] = cos_lat;
    ECEF_NED_t[0][3] = cos_lat * ECEF_NED1;

    ECEF_NED_t[1][0] = -1 * sin_lon;
    ECEF_NED_t[1][1] = cos_lon;
    ECEF_NED_t[1][2] = 0;
    ECEF_NED_t[1][3] = 0;

    ECEF_NED_t[2][0] = -1 * cos_lon * cos_lat;
    ECEF_NED_t[2][1] = -1 * sin_lon * cos_lat;
    ECEF_NED_t[2][2] = -1 * sin_lat;
    ECEF_NED_t[2][3] = -1 * sin_lat * ECEF_NED1 + RnAC + GPS_t.Alt;
}
// ------------------------------依据目标在ECEF中坐标，给出视轴单位向量-------------------------------//
//  函数名称：GetOneLSBbyTarECEF_ParaComputer()
//  功能：依据目标在ECEF中坐标，给出视轴单位向量
//  输入参数：struct_Position_float64* ecef_Tar_t 目标在ECEF中坐标
//  返回参数：struct_LSB_float64* oneLSB_t 单位视轴向量
//  说明：无
// ---------------------------------------------------------------------------//
void GetOneLSBbyTarECEF_ParaComputer(struct_LSB_float64 *oneLSB_t, struct_Position_float64 *ecef_Tar_t) {
    // 目标 在飞机为中心NED坐标
    double NEDAC_Tar[3];
    NEDAC_Tar[0] = ECEF_NED_Plan[0][0] * ecef_Tar_t->X + ECEF_NED_Plan[0][1] * ecef_Tar_t->Y + ECEF_NED_Plan[0][2] * ecef_Tar_t->Z + ECEF_NED_Plan[0][3];
    NEDAC_Tar[1] = ECEF_NED_Plan[1][0] * ecef_Tar_t->X + ECEF_NED_Plan[1][1] * ecef_Tar_t->Y + ECEF_NED_Plan[1][2] * ecef_Tar_t->Z + ECEF_NED_Plan[1][3];
    NEDAC_Tar[2] = ECEF_NED_Plan[2][0] * ecef_Tar_t->X + ECEF_NED_Plan[2][1] * ecef_Tar_t->Y + ECEF_NED_Plan[2][2] * ecef_Tar_t->Z + ECEF_NED_Plan[2][3];

    // 视轴到目标点单位向量
    double temp_T[3];
    temp_T[0] = NEDAC_Tar[0];
    temp_T[1] = NEDAC_Tar[1];
    temp_T[2] = NEDAC_Tar[2];
    double norm_T;
    norm_T = sqrt(temp_T[0] * temp_T[0] + temp_T[1] * temp_T[1] + temp_T[2] * temp_T[2]);
    if (norm_T == 0) {
        norm_T = 1;
    }

    double one_T[3]; // 单位向量
    one_T[0] = temp_T[0] / norm_T;
    one_T[1] = temp_T[1] / norm_T;
    one_T[2] = temp_T[2] / norm_T;

    oneLSB_t->X = one_T[0];
    oneLSB_t->Y = one_T[1];
    oneLSB_t->Z = one_T[2];
}
// ------------------------------依据理想NED视轴向量及当前姿态角，给出框架指向角-------------------------------//
//  函数名称：JS_NED_ParaComputer
//  功能：依据理想NED视轴向量及当前姿态角，给出框架指向角
//  输入参数：struct_LSB* ned_lsb NED坐标系下视轴指向，struct_IMUAgl* ned_AttiAgl   NED坐标系姿态角
//  返回参数：框架指向角
//  说明：无
// ---------------------------------------------------------------------------//

void GetKJAglbyLSB_ParaComputer(struct_KJAgl *kj_Agl_t, const struct_LSB_float64 *ned_lsb_t) {

    // 目标点指向框架角
    struct_LSB_float64 temp_lsb_ac; // 计算AC坐标系下视轴向量

    temp_lsb_ac.X = cos_AttiAgl.Pitch * cos_AttiAgl.Yaw * ned_lsb_t->X + cos_AttiAgl.Pitch * sin_AttiAgl.Yaw * ned_lsb_t->Y - sin_AttiAgl.Pitch * ned_lsb_t->Z;
    temp_lsb_ac.Y = (sin_AttiAgl.Roll * sin_AttiAgl.Pitch * cos_AttiAgl.Yaw - cos_AttiAgl.Roll * sin_AttiAgl.Yaw) * ned_lsb_t->X + (sin_AttiAgl.Roll * sin_AttiAgl.Pitch * sin_AttiAgl.Yaw + cos_AttiAgl.Roll * cos_AttiAgl.Yaw) * ned_lsb_t->Y + sin_AttiAgl.Roll * cos_AttiAgl.Pitch * ned_lsb_t->Z;
    temp_lsb_ac.Z = (cos_AttiAgl.Roll * sin_AttiAgl.Pitch * cos_AttiAgl.Yaw + sin_AttiAgl.Roll * sin_AttiAgl.Yaw) * ned_lsb_t->X + (cos_AttiAgl.Roll * sin_AttiAgl.Pitch * sin_AttiAgl.Yaw - sin_AttiAgl.Roll * cos_AttiAgl.Yaw) * ned_lsb_t->Y + cos_AttiAgl.Roll * cos_AttiAgl.Pitch * ned_lsb_t->Z;
    // 返回内框架角计算结果
    kj_Agl_t->WKJ = atan2(temp_lsb_ac.Y, temp_lsb_ac.X);
    // 返回外框架角计算结果
    kj_Agl_t->NKJ = acos(temp_lsb_ac.Z);
}
// ------------------------------给定外框架和内框架角，计算得到目标在ECEF中坐标-------------------------------//
//  函数名称：GetTarECEFbyKJAgl_ParaComputer(struct_KJAgl* hope_agl_kj)
//  功能：给定外框架和内框架角，计算得到目标在ECEF中坐标
//  输入参数：struct_KJAgl* hope_agl_kj 给定框架指向角
//  返回参数：指向角
//  说明：无
// ---------------------------------------------------------------------------//
void GetTarECEFbyKJAgl_ParaComputer(struct_Position_float64 *ecef_Tar_t, const struct_KJAgl *hope_agl_kj_t) {
    double       ECEFTarget_t[3]; // ECEF坐标系下目标
    double       k[3], b[3];
    float        B_STar[3];
    struct_KJAgl sin_KJAgl_t;
    struct_KJAgl cos_KJAgl_t;
    float        foc = 0.001 * tocal_foclen_KJ;

    sin_KJAgl_t.NKJ = sin(hope_agl_kj_t->NKJ);
    sin_KJAgl_t.WKJ = sin(hope_agl_kj_t->WKJ);
    cos_KJAgl_t.NKJ = cos(hope_agl_kj_t->NKJ);
    cos_KJAgl_t.WKJ = cos(hope_agl_kj_t->WKJ);

    B_STar[0] = cos_KJAgl_t.WKJ * sin_KJAgl_t.NKJ * foc;
    B_STar[1] = sin_KJAgl_t.WKJ * sin_KJAgl_t.NKJ * foc;
    B_STar[2] = cos_KJAgl_t.NKJ * foc;

    k[0] = AC_ECEF[0][0] * B_STar[0] + AC_ECEF[0][1] * B_STar[1] + AC_ECEF[0][2] * B_STar[2];
    k[1] = AC_ECEF[1][0] * B_STar[0] + AC_ECEF[1][1] * B_STar[1] + AC_ECEF[1][2] * B_STar[2];
    k[2] = AC_ECEF[2][0] * B_STar[0] + AC_ECEF[2][1] * B_STar[1] + AC_ECEF[2][2] * B_STar[2];

    // 地球坐标系下坐标相机原点
    b[0] = NED_ECEF[0][3];
    b[1] = NED_ECEF[1][3];
    b[2] = NED_ECEF[2][3];

    // 求解目标在ECEF坐标系下坐标
    ECEFGeolocat(ECEFTarget_t, k, b, tar_high);

    ecef_Tar_t->X = ECEFTarget_t[0];
    ecef_Tar_t->Y = ECEFTarget_t[1];
    ecef_Tar_t->Z = ECEFTarget_t[2];
}
// ------------------------------用目标投影在地球坐标求目标在地球坐标系坐标-------------------------------//
//  函数名称：ECEFGeolocat
//  功能：依据理想NED视轴向量及当前姿态角，给出框架指向角
//  输入参数：float k_t[3],float b_t[3],float GeodeticHeightTarget_t  目标高度
//  返回参数：float ECEFTarget_t[3] ECEF中目标位置
//  说明：无
// ---------------------------------------------------------------------------//
void ECEFGeolocat(double ECEFTarget_t[3], double k_t[3], double b_t[3], float GeodeticHeightTarget_t) {
    double bTarget;
    double b[3];

    b[0] = b_t[0];
    b[1] = b_t[1];
    b[2] = b_t[2];

    // 赋值半长轴计算用
    bTarget = (6356752 + GeodeticHeightTarget_t) * (6356752 + GeodeticHeightTarget_t);
    double aa, bb, cc;
    double xx[2], yy[2], zz[2], Distance2[2];

    double temp_1 = k_t[0] / k_t[2];
    double temp_2 = temp_1 * temp_1;
    double temp_3 = k_t[1] / k_t[2];
    double temp_4 = temp_3 * temp_3;
    double temp_5 = (6356752 + GeodeticHeightTarget_t) * (6356752 + GeodeticHeightTarget_t);

    aa = ((temp_2 + temp_4) / temp_5) + (1 / bTarget);
    bb = (2 * temp_1 * b[0] - 2 * temp_2 * b[2] + 2 * temp_3 * b[1] - 2 * temp_4 * b[2]) / temp_5;
    cc = ((temp_1 * b[2] - b[0]) * (temp_1 * b[2] - b[0]) + (temp_3 * b[2] - b[1]) * (temp_3 * b[2] - b[1])) / temp_5 - 1;

    double temp_8;
    temp_8 = sqrt(fabs(bb * bb - 4 * aa * cc));

    zz[0] = (-bb + temp_8) / 2 / aa;
    zz[1] = (-bb - temp_8) / 2 / aa;

    double temp_6 = 0;
    double temp_7 = 0;

    temp_6       = temp_1 * (zz[0] - b[2]);
    temp_7       = temp_3 * (zz[0] - b[2]);
    xx[0]        = temp_6 + b[0];
    yy[0]        = temp_7 + b[1];
    Distance2[0] = temp_6 * temp_6 + temp_7 * temp_7 + (zz[0] - b[2]) * (zz[0] - b[2]);

    temp_6       = temp_1 * (zz[1] - b[2]);
    temp_7       = temp_3 * (zz[1] - b[2]);
    xx[1]        = temp_6 + b[0];
    yy[1]        = temp_7 + b[1];
    Distance2[1] = temp_6 * temp_6 + temp_7 * temp_7 + (zz[1] - b[2]) * (zz[1] - b[2]);

    // 解结果
    if (Distance2[1] > Distance2[0]) {
        ECEFTarget_t[0] = xx[0];
        ECEFTarget_t[1] = yy[0];
        ECEFTarget_t[2] = zz[0];
    } else {
        ECEFTarget_t[0] = xx[1];
        ECEFTarget_t[1] = yy[1];
        ECEFTarget_t[2] = zz[1];
    }
}
// 地球坐标系下坐标转GPS，得到GPSTarget
void ECEFToGPS(double GPS_t[3], double ECEF_t[3]) {
    int    i;
    double ZECEF = ECEF_t[2];
    double Rn, Latitude, Longitude, GeodeticHeight;
    long   aEarth = 6378137;
    Rn            = aEarth * 1.0;

    // 经度
    Longitude = atan(ECEF_t[1] / ECEF_t[0]);
    if ((ECEF_t[0] < 0) && (Longitude > 0)) {
        Longitude = Longitude - PI;
    } else if ((ECEF_t[0] < 0) && (Longitude < 0)) {
        Longitude = Longitude + PI;
    }
    // 纬度
    double temp_1 = ECEF_t[0] * ECEF_t[0];
    double temp_2 = ECEF_t[1] * ECEF_t[1];
    double temp_3 = 0.006694478197993;
    double temp_5 = sqrt(temp_1 + temp_2);

    GeodeticHeight = sqrt(temp_1 + temp_2 + (ZECEF * ZECEF)) - 6367435.522329535;

    double temp_4 = ZECEF * (Rn + GeodeticHeight);

    Latitude = atan(temp_4 / (temp_5 * (Rn * (1 - temp_3) + GeodeticHeight)));

    for (i = 0; i < 4; i++) {
        Rn             = aEarth / sqrt(1 - temp_3 * (sin(Latitude) * sin(Latitude)));
        GeodeticHeight = sqrt(temp_1 + temp_2) / cos(Latitude) - Rn;
        temp_4         = ZECEF * (Rn + GeodeticHeight);
        Latitude       = atan(temp_4 / (temp_5 * (Rn * (1 - temp_3) + GeodeticHeight)));
    }
    GPS_t[0] = Latitude;
    GPS_t[1] = Longitude;
    GPS_t[2] = GeodeticHeight;
}

// ------------------------------区域成像计算条带数、条带帧数和起始角-------------------------------//
//  函数名称：QYCX_GetTDPhotoNum
//  功能：区域成像计算条带数、条带帧数和起始角
//  输入参数：float64 Tar_Lon_t 目标经度,float64 Tar_Lat_t 目标纬度,float Tar_Alt_t 目标高度
//  返回参数：更新  条带周期GYCX_TD_Time；条带帧数GYCX_TD_PhotoNum；条带近端角GYCX_TDAgl_near
//  说明：无
// ---------------------------------------------------------------------------//
UINT8 QYCX_GetTDPhotoNum(struct_GPS_float64 GPS_Tar, float Tar_Range) {
    int                overPara_flag_t = 0; // 参数超限标识
    struct_LSB_float64 ned_lsb_t;
    struct_KJAgl       cal_agl_kj_t;                         // 计算框架角
    float              foc = (float)tocal_foclen_KJ * 0.001; // 焦距
    float              P_x_t;                                // x方向重叠率
    P_x_t = QYCX_P_x;
    float P_y_t; // y方向重叠率
    P_y_t = QYCX_P_y;
    float picAngle_x_pi;                                                               // X摆扫向视场角
    picAngle_x_pi = 2 * atan((KJ_pixnum_X * tocal_pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_x_overlap_pi;                                                       // 去掉重叠率
    picAngle_x_overlap_pi = picAngle_x_pi * (1 - P_x_t);
    float picAngle_y_pi;                                                               // Y摆扫向视场角
    picAngle_y_pi = 2 * atan((KJ_pixnum_Y * tocal_pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_y_overlap_pi;                                                       // 去掉重叠率
    picAngle_y_overlap_pi = picAngle_y_pi * (1 - P_y_t);
    float pic_sec         = QYCX_pfs;                        // 成像周期
    QYCX_WKJ_omiga        = picAngle_y_overlap_pi / pic_sec; // 广域成像外框架角速度

    // 计算中心点方向
    struct_LSB_float64 hope_ned_lsb_t; // 理想视轴在NED中指向
    // 计算目标在ECEF下坐标
    GPSToECEF(&GeoTrack_ecef_Tar, GPS_Tar.Lon, GPS_Tar.Lat, GPS_Tar.Alt);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);

    // 依据目标在ECEF中坐标，给出视轴单位向量
    GetOneLSBbyTarECEF_ParaComputer(&hope_ned_lsb_t, &GeoTrack_ecef_Tar);

    //----------------依据飞行速度判断超限------------------------------//
    float Tloc = Sec_KJPosREADY_WKJ + Sec_KJSpeedREADY; // 框架到位时间
    float lsb_fy;                                       // 视轴在NED下俯仰角
    lsb_fy = acos(hope_ned_lsb_t.Z);
    float temp1;
    float temp2;
    float temp3;
    temp1 = lsb_fy + picAngle_y_overlap_pi / 2;
    if (temp1 > (89.9 * Agl_PI)) {
        temp1 = 89.9 * Agl_PI;
    }
    temp2 = lsb_fy - picAngle_y_overlap_pi / 2;
    if (temp2 > (89.9 * Agl_PI)) {
        temp2 = 89.9 * Agl_PI;
    }
    temp3        = (tan(temp1) - tan(temp2)) * planTar_high;
    float T_gd   = 0;
    T_gd         = temp3 / AC_speed; // 时间
    float T_num1 = 0;
    T_num1       = floor((T_gd - Tloc) / pic_sec); // 计算条带帧数
    float temp_range;                              // 预计摆扫范围
    temp_range = temp3 * T_num1 * 0.5;
    //    float temp_lesscent;//缩小比例
    if (temp_range < Tar_Range) // 如果超限
    {
        overPara_flag_t = 1;          // 超限
        Tar_Range       = temp_range; // 缩小比例
    }
    //-----------依据飞行判断超限  结束--------------------------

    float lsb_yaw; // 视轴在NED下方位角
    lsb_yaw = atan2(hope_ned_lsb_t.Y, hope_ned_lsb_t.X);

    float NED_ECEF_Tar[4][4]; // NED到目标坐标系转换矩阵

    float KJ_PI_A[2]; // A点视轴指向
    float KJ_PI_B[2]; // B点视轴指向
    float KJ_PI_C[2]; // C点视轴指向
    //	float KJ_PI_D[2];//D点视轴指向

    // 在LL坐标系下目标四角点
    float LL_TarArea_A[2];
    float LL_TarArea_B[2];
    float LL_TarArea_C[2];
    float LL_TarArea_D[2];

    //  ^	C	D
    // 目标区域的四个角            |   A   B
    float TarArea_A[2];
    float TarArea_B[2];
    float TarArea_C[2];
    float TarArea_D[2];
    float temp_float = 0;

    float sin_Lon = sin(GPS_Tar.Lon);
    float cos_Lon = cos(GPS_Tar.Lon);
    float sin_Lat = sin(GPS_Tar.Lat);
    float cos_Lat = cos(GPS_Tar.Lat);

    double RnAC;
    double temp_1;
    temp_1 = sqrt(1 - (0.00669447819799 * sin_Lat * sin_Lat));
    // 除数不为零
    if (temp_1 != 0) {
        RnAC = 6378137 / temp_1;
    } else {
        RnAC = 6378137;
    }
    double NED_ECEF1 = 0;
    NED_ECEF1        = -RnAC * sin_Lat * 0.00669447819799;
    double NED_ECEF4 = 0;
    NED_ECEF4        = -(RnAC + GPS_Tar.Alt);

    NED_ECEF_Tar[0][0] = cos_Lon * (-1) * sin_Lat;
    NED_ECEF_Tar[0][1] = (-1) * sin_Lon;
    NED_ECEF_Tar[0][2] = cos_Lon * (-1) * cos_Lat;
    NED_ECEF_Tar[0][3] = cos_Lon * (-1) * cos_Lat * NED_ECEF4;

    NED_ECEF_Tar[1][0] = sin_Lon * (-1) * sin_Lat;
    NED_ECEF_Tar[1][1] = cos_Lon;
    NED_ECEF_Tar[1][2] = sin_Lon * (-1) * cos_Lat;
    NED_ECEF_Tar[1][3] = sin_Lon * (-1) * cos_Lat * NED_ECEF4;

    NED_ECEF_Tar[2][0] = cos_Lat;
    NED_ECEF_Tar[2][1] = 0;
    NED_ECEF_Tar[2][2] = (-1) * sin_Lat;
    NED_ECEF_Tar[2][3] = (-1) * sin_Lat * NED_ECEF4 + NED_ECEF1;

    temp_float      = Tar_Range * 0.707; // 范围
    LL_TarArea_A[0] = -1 * temp_float;
    LL_TarArea_B[0] = -1 * temp_float;
    LL_TarArea_C[0] = temp_float;
    LL_TarArea_D[0] = temp_float;

    LL_TarArea_A[1] = -1 * temp_float;
    LL_TarArea_B[1] = temp_float;
    LL_TarArea_C[1] = -1 * temp_float;
    LL_TarArea_D[1] = temp_float;

    float cos_Yaw = cos(lsb_yaw);
    float sin_Yaw = sin(lsb_yaw);

    TarArea_A[0] = cos_Yaw * LL_TarArea_A[0] - sin_Yaw * LL_TarArea_A[1];
    TarArea_A[1] = sin_Yaw * LL_TarArea_A[0] + cos_Yaw * LL_TarArea_A[1];

    TarArea_B[0] = cos_Yaw * LL_TarArea_B[0] - sin_Yaw * LL_TarArea_B[1];
    TarArea_B[1] = sin_Yaw * LL_TarArea_B[0] + cos_Yaw * LL_TarArea_B[1];

    TarArea_C[0] = cos_Yaw * LL_TarArea_C[0] - sin_Yaw * LL_TarArea_C[1];
    TarArea_C[1] = sin_Yaw * LL_TarArea_C[0] + cos_Yaw * LL_TarArea_C[1];

    TarArea_D[0] = cos_Yaw * LL_TarArea_D[0] - sin_Yaw * LL_TarArea_D[1];
    TarArea_D[1] = sin_Yaw * LL_TarArea_D[0] + cos_Yaw * LL_TarArea_D[1];

    ECEF_TarA[0] = NED_ECEF_Tar[0][0] * TarArea_A[0] + NED_ECEF_Tar[0][1] * TarArea_A[1] + NED_ECEF_Tar[0][3];
    ECEF_TarA[1] = NED_ECEF_Tar[1][0] * TarArea_A[0] + NED_ECEF_Tar[1][1] * TarArea_A[1] + NED_ECEF_Tar[1][3];
    ECEF_TarA[2] = NED_ECEF_Tar[2][0] * TarArea_A[0] + NED_ECEF_Tar[2][1] * TarArea_A[1] + NED_ECEF_Tar[2][3];

    // 目标 在飞机为中心NED坐标
    double NEDAC_TarA[3];
    NEDAC_TarA[0] = ECEF_NED_Plan[0][0] * ECEF_TarA[0] + ECEF_NED_Plan[0][1] * ECEF_TarA[1] + ECEF_NED_Plan[0][2] * ECEF_TarA[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarA[1] = ECEF_NED_Plan[1][0] * ECEF_TarA[0] + ECEF_NED_Plan[1][1] * ECEF_TarA[1] + ECEF_NED_Plan[1][2] * ECEF_TarA[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarA[2] = ECEF_NED_Plan[2][0] * ECEF_TarA[0] + ECEF_NED_Plan[2][1] * ECEF_TarA[1] + ECEF_NED_Plan[2][2] * ECEF_TarA[2] + ECEF_NED_Plan[2][3];

    // 视轴到A点单位向量
    float temp_A[3];
    temp_A[0] = NEDAC_TarA[0];
    temp_A[1] = NEDAC_TarA[1];
    temp_A[2] = NEDAC_TarA[2];
    float norm_A;
    norm_A = sqrt(fabs(temp_A[0] * temp_A[0] + temp_A[1] * temp_A[1] + temp_A[2] * temp_A[2]));
    // 被除数不为零
    if (norm_A == 0) {
        norm_A = 1;
    }
    float one_A[3]; // 单位向量
    one_A[0] = temp_A[0] / norm_A;
    one_A[1] = temp_A[1] / norm_A;
    one_A[2] = temp_A[2] / norm_A;

    // 目标在ECEF坐标
    double ECEF_TarB[3];
    ECEF_TarB[0] = NED_ECEF_Tar[0][0] * TarArea_B[0] + NED_ECEF_Tar[0][1] * TarArea_B[1] + NED_ECEF_Tar[0][3];
    ECEF_TarB[1] = NED_ECEF_Tar[1][0] * TarArea_B[0] + NED_ECEF_Tar[1][1] * TarArea_B[1] + NED_ECEF_Tar[1][3];
    ECEF_TarB[2] = NED_ECEF_Tar[2][0] * TarArea_B[0] + NED_ECEF_Tar[2][1] * TarArea_B[1] + NED_ECEF_Tar[2][3];

    // 目标 在飞机为中心NED坐标
    float NEDAC_TarB[3];
    NEDAC_TarB[0] = ECEF_NED_Plan[0][0] * ECEF_TarB[0] + ECEF_NED_Plan[0][1] * ECEF_TarB[1] + ECEF_NED_Plan[0][2] * ECEF_TarB[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarB[1] = ECEF_NED_Plan[1][0] * ECEF_TarB[0] + ECEF_NED_Plan[1][1] * ECEF_TarB[1] + ECEF_NED_Plan[1][2] * ECEF_TarB[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarB[2] = ECEF_NED_Plan[2][0] * ECEF_TarB[0] + ECEF_NED_Plan[2][1] * ECEF_TarB[1] + ECEF_NED_Plan[2][2] * ECEF_TarB[2] + ECEF_NED_Plan[2][3];

    // 视轴到B点单位向量
    float temp_B[3];
    temp_B[0] = NEDAC_TarB[0];
    temp_B[1] = NEDAC_TarB[1];
    temp_B[2] = NEDAC_TarB[2];
    float norm_B;
    norm_B = sqrt(temp_B[0] * temp_B[0] + temp_B[1] * temp_B[1] + temp_B[2] * temp_B[2]);
    // 被除数不为零
    if (norm_B == 0) {
        norm_B = 1;
    }
    float one_B[3]; // 单位向量
    one_B[0] = temp_B[0] / norm_B;
    one_B[1] = temp_B[1] / norm_B;
    one_B[2] = temp_B[2] / norm_B;

    ECEF_TarC[0] = NED_ECEF_Tar[0][0] * TarArea_C[0] + NED_ECEF_Tar[0][1] * TarArea_C[1] + NED_ECEF_Tar[0][3];
    ECEF_TarC[1] = NED_ECEF_Tar[1][0] * TarArea_C[0] + NED_ECEF_Tar[1][1] * TarArea_C[1] + NED_ECEF_Tar[1][3];
    ECEF_TarC[2] = NED_ECEF_Tar[2][0] * TarArea_C[0] + NED_ECEF_Tar[2][1] * TarArea_C[1] + NED_ECEF_Tar[2][3];

    // 目标 在飞机为中心NED坐标
    float NEDAC_TarC[3];
    NEDAC_TarC[0] = ECEF_NED_Plan[0][0] * ECEF_TarC[0] + ECEF_NED_Plan[0][1] * ECEF_TarC[1] + ECEF_NED_Plan[0][2] * ECEF_TarC[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarC[1] = ECEF_NED_Plan[1][0] * ECEF_TarC[0] + ECEF_NED_Plan[1][1] * ECEF_TarC[1] + ECEF_NED_Plan[1][2] * ECEF_TarC[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarC[2] = ECEF_NED_Plan[2][0] * ECEF_TarC[0] + ECEF_NED_Plan[2][1] * ECEF_TarC[1] + ECEF_NED_Plan[2][2] * ECEF_TarC[2] + ECEF_NED_Plan[2][3];

    // 视轴到C点单位向量
    float temp_C[3];
    temp_C[0] = NEDAC_TarC[0];
    temp_C[1] = NEDAC_TarC[1];
    temp_C[2] = NEDAC_TarC[2];

    float norm_C;
    norm_C = sqrt(temp_C[0] * temp_C[0] + temp_C[1] * temp_C[1] + temp_C[2] * temp_C[2]);
    // 被除数不为零
    if (norm_C == 0) {
        norm_C = 1;
    }
    norm_C = sqrt(temp_C[0] * temp_C[0] + temp_C[1] * temp_C[1] + temp_C[2] * temp_C[2]);
    float one_C[3]; // 单位向量
    one_C[0] = temp_C[0] / norm_C;
    one_C[1] = temp_C[1] / norm_C;
    one_C[2] = temp_C[2] / norm_C;

    // 目标在ECEF坐标
    double ECEF_TarD[3];
    ECEF_TarD[0] = NED_ECEF_Tar[0][0] * TarArea_D[0] + NED_ECEF_Tar[0][1] * TarArea_D[1] + NED_ECEF_Tar[0][3];
    ECEF_TarD[1] = NED_ECEF_Tar[1][0] * TarArea_D[0] + NED_ECEF_Tar[1][1] * TarArea_D[1] + NED_ECEF_Tar[1][3];
    ECEF_TarD[2] = NED_ECEF_Tar[2][0] * TarArea_D[0] + NED_ECEF_Tar[2][1] * TarArea_D[1] + NED_ECEF_Tar[2][3];

    // 目标 在飞机为中心NED坐标
    float NEDAC_TarD[3];
    NEDAC_TarD[0] = ECEF_NED_Plan[0][0] * ECEF_TarD[0] + ECEF_NED_Plan[0][1] * ECEF_TarD[1] + ECEF_NED_Plan[0][2] * ECEF_TarD[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarD[1] = ECEF_NED_Plan[1][0] * ECEF_TarD[0] + ECEF_NED_Plan[1][1] * ECEF_TarD[1] + ECEF_NED_Plan[1][2] * ECEF_TarD[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarD[2] = ECEF_NED_Plan[2][0] * ECEF_TarD[0] + ECEF_NED_Plan[2][1] * ECEF_TarD[1] + ECEF_NED_Plan[2][2] * ECEF_TarD[2] + ECEF_NED_Plan[2][3];

    // 视轴到D点单位向量
    float temp_D[3];
    temp_D[0] = NEDAC_TarD[0];
    temp_D[1] = NEDAC_TarD[1];
    temp_D[2] = NEDAC_TarD[2];
    float norm_D;
    norm_D = sqrt(temp_D[0] * temp_D[0] + temp_D[1] * temp_D[1] + temp_D[2] * temp_D[2]);
    // 被除数不为零
    if (norm_D == 0) {
        norm_D = 1;
    }
    float one_D[3]; // 单位向量
    one_D[0] = temp_D[0] / norm_D;
    one_D[1] = temp_D[1] / norm_D;
    one_D[2] = temp_D[2] / norm_D;

    // A点指向框架角
    ned_lsb_t.X = one_A[0];
    ned_lsb_t.Y = one_A[1];
    ned_lsb_t.Z = one_A[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    // 外框架横滚角
    KJ_PI_A[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    KJ_PI_A[1] = cal_agl_kj_t.NKJ;

    // B点指向框架角
    ned_lsb_t.X = one_B[0];
    ned_lsb_t.Y = one_B[1];
    ned_lsb_t.Z = one_B[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    // 外框架横滚角
    KJ_PI_B[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    KJ_PI_B[1] = cal_agl_kj_t.NKJ;

    // C点指向框架角
    ned_lsb_t.X = one_C[0];
    ned_lsb_t.Y = one_C[1];
    ned_lsb_t.Z = one_C[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    // 外框架横滚角
    KJ_PI_C[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    KJ_PI_C[1] = cal_agl_kj_t.NKJ;

    // D点指向框架角
    ned_lsb_t.X = one_D[0];
    ned_lsb_t.Y = one_D[1];
    ned_lsb_t.Z = one_D[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        overPara_flag_t  = 1; // 超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        overPara_flag_t  = 1; // 超限标识
    }

    // 外框架横滚角
    // 	KJ_PI_D[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    // 	KJ_PI_D[1] = cal_agl_kj_t.NKJ;

    float derta_agl_nkj;                                               // 内框架差值
    derta_agl_nkj  = fabs(KJ_PI_A[1] - KJ_PI_C[1]);                    // 内框架差值
    QYCX_NeedTDNum = (int)(derta_agl_nkj / picAngle_x_overlap_pi) + 3; // 条带数
    float derta_agl_wkj;                                               // 外框架差值
    if ((KJ_PI_A[0] * KJ_PI_B[0]) > 0)                                 // 在一侧
    {
        derta_agl_wkj = fabs(KJ_PI_A[0] - KJ_PI_B[0]);                    // 外框架差值
        TD_PhotoNum   = (int)(derta_agl_wkj / picAngle_y_overlap_pi) + 3; // 条带帧数
    } else {
        derta_agl_wkj = fabs(KJ_PI_A[0]) + fabs(KJ_PI_B[0]);              // 外框架差值
        TD_PhotoNum   = (int)(derta_agl_wkj / picAngle_y_overlap_pi) + 3; // 条带帧数
    }

    QYCX_TDAgl_WKJ_first = KJ_PI_A[0]; // 外框架
    QYCX_TDAgl_NKJ_first = KJ_PI_A[1]; // 内框架

    if (QYCX_NeedTDNum == 1) {

        QYCX_WKJ_change = 0;
        QYCX_NKJ_change = 0;
    } else {
        QYCX_WKJ_change = (KJ_PI_C[0] - KJ_PI_A[0]) / (QYCX_NeedTDNum - 1); // 区域用外框架变化量
        QYCX_NKJ_change = (KJ_PI_C[1] - KJ_PI_A[1]) / (QYCX_NeedTDNum - 1); // 区域用内框架变化量
    }

    return overPara_flag_t;
}

// 区域成像计算条带起始角
void QYCX_GetTDstart() {
    //	int overPara_flag_t = 0;//参数超限标识
    struct_LSB_float64 ned_lsb_t;
    struct_KJAgl       cal_agl_kj_t;                         // 计算框架角
    float              KJ_PI_A[2];                           // A点视轴指向
    float              KJ_PI_C[2];                           // C点视轴指向
    float              foc = (float)tocal_foclen_KJ * 0.001; // 焦距
    float              P_x_t;                                // x方向重叠率
    P_x_t = QYCX_P_x;
    float picAngle_x_pi;                                                               // X摆扫向视场角
    picAngle_x_pi = 2 * atan((KJ_pixnum_X * tocal_pixsize_KJ * 0.000001) / (foc * 2)); // Ny*b=2134*4.5*10^-6/((foc*2))
    float picAngle_x_overlap_pi;                                                       // 去掉重叠率
    picAngle_x_overlap_pi = picAngle_x_pi * (1 - P_x_t);
    // 将ECEF坐标系转到以目标中心为原点 转换矩阵
    ECEFToNED(ECEF_NED_Plan, AC_Position_pi);

    // 目标 在飞机为中心NED坐标
    float NEDAC_TarA[3];
    NEDAC_TarA[0] = ECEF_NED_Plan[0][0] * ECEF_TarA[0] + ECEF_NED_Plan[0][1] * ECEF_TarA[1] + ECEF_NED_Plan[0][2] * ECEF_TarA[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarA[1] = ECEF_NED_Plan[1][0] * ECEF_TarA[0] + ECEF_NED_Plan[1][1] * ECEF_TarA[1] + ECEF_NED_Plan[1][2] * ECEF_TarA[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarA[2] = ECEF_NED_Plan[2][0] * ECEF_TarA[0] + ECEF_NED_Plan[2][1] * ECEF_TarA[1] + ECEF_NED_Plan[2][2] * ECEF_TarA[2] + ECEF_NED_Plan[2][3];

    // 视轴到A点单位向量
    float temp_A[3];
    temp_A[0] = NEDAC_TarA[0];
    temp_A[1] = NEDAC_TarA[1];
    temp_A[2] = NEDAC_TarA[2];
    float norm_A;
    norm_A = sqrt(fabs(temp_A[0] * temp_A[0] + temp_A[1] * temp_A[1] + temp_A[2] * temp_A[2]));
    // 被除数不为零
    if (norm_A == 0) {
        norm_A = 1;
    }
    float one_A[3]; // 单位向量
    one_A[0] = temp_A[0] / norm_A;
    one_A[1] = temp_A[1] / norm_A;
    one_A[2] = temp_A[2] / norm_A;

    // 目标 在飞机为中心NED坐标
    float NEDAC_TarC[3];
    NEDAC_TarC[0] = ECEF_NED_Plan[0][0] * ECEF_TarC[0] + ECEF_NED_Plan[0][1] * ECEF_TarC[1] + ECEF_NED_Plan[0][2] * ECEF_TarC[2] + ECEF_NED_Plan[0][3];
    NEDAC_TarC[1] = ECEF_NED_Plan[1][0] * ECEF_TarC[0] + ECEF_NED_Plan[1][1] * ECEF_TarC[1] + ECEF_NED_Plan[1][2] * ECEF_TarC[2] + ECEF_NED_Plan[1][3];
    NEDAC_TarC[2] = ECEF_NED_Plan[2][0] * ECEF_TarC[0] + ECEF_NED_Plan[2][1] * ECEF_TarC[1] + ECEF_NED_Plan[2][2] * ECEF_TarC[2] + ECEF_NED_Plan[2][3];

    // 视轴到C点单位向量
    float temp_C[3];
    temp_C[0] = NEDAC_TarC[0];
    temp_C[1] = NEDAC_TarC[1];
    temp_C[2] = NEDAC_TarC[2];

    float norm_C;
    norm_C = sqrt(temp_C[0] * temp_C[0] + temp_C[1] * temp_C[1] + temp_C[2] * temp_C[2]);
    // 被除数不为零
    if (norm_C == 0) {
        norm_C = 1;
    }
    norm_C = sqrt(temp_C[0] * temp_C[0] + temp_C[1] * temp_C[1] + temp_C[2] * temp_C[2]);
    float one_C[3]; // 单位向量
    one_C[0] = temp_C[0] / norm_C;
    one_C[1] = temp_C[1] / norm_C;
    one_C[2] = temp_C[2] / norm_C;

    // A点指向框架角
    ned_lsb_t.X = one_A[0];
    ned_lsb_t.Y = one_A[1];
    ned_lsb_t.Z = one_A[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        //        overPara_flag_t = 1;//超限标识
    }

    // 外框架横滚角
    KJ_PI_A[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    KJ_PI_A[1] = cal_agl_kj_t.NKJ;

    // C点指向框架角
    ned_lsb_t.X = one_C[0];
    ned_lsb_t.Y = one_C[1];
    ned_lsb_t.Z = one_C[2];
    // 依据理想视轴向量及当前姿态角，给出框架指向角
    GetKJAglbyLSB_ParaComputer(&cal_agl_kj_t, &ned_lsb_t);

    // 内框架角是否超限
    if (cal_agl_kj_t.NKJ > NKJ_Max_PI) {
        cal_agl_kj_t.NKJ = NKJ_Max_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    if (cal_agl_kj_t.NKJ < NKJ_Min_PI) {
        cal_agl_kj_t.NKJ = NKJ_Min_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    // 外框架角是否超限
    if (cal_agl_kj_t.WKJ > WKJ_Max_PI) {
        cal_agl_kj_t.WKJ = WKJ_Max_PI;
        //        overPara_flag_t = 1;//超限标识
    }
    if (cal_agl_kj_t.WKJ < WKJ_Min_PI) {
        cal_agl_kj_t.WKJ = WKJ_Min_PI;
        //        overPara_flag_t = 1;//超限标识
    }

    // 外框架横滚角
    KJ_PI_C[0] = cal_agl_kj_t.WKJ;
    // 内框架俯仰角
    KJ_PI_C[1] = cal_agl_kj_t.NKJ;

    float derta_agl_nkj;                                               // 内框架差值
    derta_agl_nkj  = fabs(KJ_PI_A[1] - KJ_PI_C[1]);                    // 内框架差值
    QYCX_NeedTDNum = (int)(derta_agl_nkj / picAngle_x_overlap_pi) + 3; // 条带数

    QYCX_TDAgl_WKJ_first = KJ_PI_A[0]; // 外框架
    QYCX_TDAgl_NKJ_first = KJ_PI_A[1]; // 内框架

    if (QYCX_NeedTDNum == 1) {

        QYCX_WKJ_change = 0;
        QYCX_NKJ_change = 0;
    } else {
        QYCX_WKJ_change = (KJ_PI_C[0] - KJ_PI_A[0]) / (QYCX_NeedTDNum - 1); // 区域用外框架变化量
        QYCX_NKJ_change = (KJ_PI_C[1] - KJ_PI_A[1]) / (QYCX_NeedTDNum - 1); // 区域用内框架变化量
    }
}

// ------------------------------目标地理定位-------------------------------//
//  函数名称：Geolocation
//  功能：目标地理定位
//  输入参数
//  返回参数：
//  说明：无
// ---------------------------------------------------------------------------//
void Geolocation() {
    // float              x; //
    // float              y; //
    // struct_GPS_float64 Tar_gps;
    // //==============右上点================
    // x = -1 * KJ_pixnum_X * pixsize_KJ * 0.000001 / 2; // 飞行方向
    // y = -1 * KJ_pixnum_Y * pixsize_KJ * 0.000001 / 2; // 扫描方向

    // ComptGps(x, y, &Tar_gps);

    // param_Compute_Output.imaging_right_up_latitude  = Tar_gps.Lat;
    // param_Compute_Output.imaging_right_up_longitude = Tar_gps.Lon;

    // //==============右下点================
    // x = KJ_pixnum_X * pixsize_KJ * 0.000001 / 2;      // 飞行方向
    // y = -1 * KJ_pixnum_Y * pixsize_KJ * 0.000001 / 2; // 扫描方向

    // ComptGps(x, y, &Tar_gps);

    // param_Compute_Output.imaging_right_down_latitude  = Tar_gps.Lat;
    // param_Compute_Output.imaging_right_down_longitude = Tar_gps.Lon;

    // //==============左上点================
    // x = -1 * KJ_pixnum_X * pixsize_KJ * 0.000001 / 2; // 飞行方向
    // y = KJ_pixnum_Y * pixsize_KJ * 0.000001 / 2;      // 扫描方向

    // ComptGps(x, y, &Tar_gps);

    // param_Compute_Output.imaging_left_up_latitude  = Tar_gps.Lat;
    // param_Compute_Output.imaging_left_up_longitude = Tar_gps.Lon;

    // //==============左下点================
    // x = KJ_pixnum_X * pixsize_KJ * 0.000001 / 2; // 飞行方向
    // y = KJ_pixnum_Y * pixsize_KJ * 0.000001 / 2; // 扫描方向

    // ComptGps(x, y, &Tar_gps);

    // param_Compute_Output.imaging_left_down_latitude  = Tar_gps.Lat;
    // param_Compute_Output.imaging_left_down_longitude = Tar_gps.Lon;

    // //==============中心点================
    // x = 0; // 飞行方向
    // y = 0; // 扫描方向

    // ComptGps(x, y, &Tar_gps);

    // param_Compute_Output.image_center_latitude  = Tar_gps.Lat;
    // param_Compute_Output.image_center_longitude = Tar_gps.Lon;
    // param_Compute_Output.A818_ImageCenterHeight = (int)Tar_gps.Alt;

    // Note: lcy BEGIN -----------------------------------------
    constexpr double fx = 1960e-3;
    constexpr double fy = 1960e-3;
    constexpr double cx = (5120 - 1) / 2.0;
    constexpr double cy = (4096 - 1) / 2.0;

    Eigen::Vector3d body_lla{AC_Position_pi.Lat * PI_Agl, AC_Position_pi.Lon * PI_Agl, AC_Position_pi.Alt};
    double          yaw        = AttitudeAC_pi.Yaw;   // 航向角
    double          pitch      = AttitudeAC_pi.Pitch; // 俯仰角
    double          roll       = AttitudeAC_pi.Roll;  // 横滚角
    double          depression = (param_Compute_Input_Fromfpga.rtime_pitch_frame + 90) * Agl_PI;
    double          azimuth    = (param_Compute_Input_Fromfpga.rtime_direction_frame + 90) * Agl_PI;

    Eigen::Vector3d rvec = rot::calcRotationVector(yaw, pitch, roll, depression, azimuth, true);

    GeolocatorLOS geolocator(body_lla, fx, fy, cx, cy, rvec);

    // 中心 左上 右上 左下 右下
    Eigen::Vector2d px_center, px_lefttop, px_righttop, px_leftdown, px_rightdown;
    px_center    = Eigen::Vector2d(cx, cy);
    px_lefttop   = Eigen::Vector2d(0, 0);
    px_righttop  = Eigen::Vector2d(5120 - 1, 0);
    px_leftdown  = Eigen::Vector2d(0, 4096 - 1);
    px_rightdown = Eigen::Vector2d(5120 - 1, 4096 - 1);

    Eigen::Vector3d lla_center, lla_lefttop, lla_righttop, lla_leftdown, lla_rightdown;
    lla_center   = geolocator.get_target_lla(px_center, tar_high);
    lla_lefttop  = geolocator.get_target_lla(px_lefttop, tar_high);
    lla_righttop = geolocator.get_target_lla(px_righttop, tar_high);
    lla_leftdown = geolocator.get_target_lla(px_leftdown, tar_high);

    param_Compute_Output.image_center_latitude        = lla_center[0];
    param_Compute_Output.image_center_longitude       = lla_center[1];
    param_Compute_Output.A818_ImageCenterHeight       = std::round(lla_center[2]);
    param_Compute_Output.imaging_left_up_latitude     = lla_lefttop[0];
    param_Compute_Output.imaging_left_up_longitude    = lla_lefttop[1];
    param_Compute_Output.imaging_right_up_latitude    = lla_righttop[0];
    param_Compute_Output.imaging_right_up_longitude   = lla_righttop[1];
    param_Compute_Output.imaging_left_down_latitude   = lla_leftdown[0];
    param_Compute_Output.imaging_left_down_longitude  = lla_leftdown[1];
    param_Compute_Output.imaging_right_down_latitude  = lla_rightdown[0];
    param_Compute_Output.imaging_right_down_longitude = lla_rightdown[1];

    // Note: lcy END -------------------------------------------

    param_Compute_Output.view_fov_center_azimuth   = (KJAgl_exp_pi.WKJ + KFKZAgl_exp_pi.WKJ + geo_WKJ_ParaErro) * PI_Agl;
    param_Compute_Output.view_fov_center_elevation = (KJAgl_exp_pi.NKJ + KFKZAgl_exp_pi.NKJ + geo_NKJ_ParaErro) * PI_Agl;
}
// 目标地理定位
void ComptGps(float x, float y, struct_GPS_float64 *Tar_gps) {
    double GPSTarget[3];
    double b[3]; // 地球坐标系下坐标相机原点
    b[0] = NED_ECEF[0][3];
    b[1] = NED_ECEF[1][3];
    b[2] = NED_ECEF[2][3];

    float sin_WKJ;
    float sin_NKJ;
    float cos_WKJ;
    float cos_NKJ;
    cos_WKJ = cos(KJAgl_exp_pi.WKJ + KFKZAgl_exp_pi.WKJ / 2.5 + geo_WKJ_ParaErro);
    cos_NKJ = cos(KJAgl_exp_pi.NKJ + KFKZAgl_exp_pi.NKJ / 2.5 + geo_NKJ_ParaErro);
    sin_WKJ = sin(KJAgl_exp_pi.WKJ + KFKZAgl_exp_pi.WKJ / 2.5 + geo_WKJ_ParaErro);
    sin_NKJ = sin(KJAgl_exp_pi.NKJ + KFKZAgl_exp_pi.NKJ / 2.5 + geo_NKJ_ParaErro);
    // 长焦2.5，短焦0.5

    float  z = -tocal_foclen_KJ * 0.001; //
    float  B_STar[3];
    double k[3];

    B_STar[0] = cos_WKJ * cos_NKJ * x - sin_WKJ * y + cos_WKJ * sin_NKJ * z;
    B_STar[1] = sin_WKJ * cos_NKJ * x + cos_WKJ * y + sin_WKJ * sin_NKJ * z;
    B_STar[2] = -sin_NKJ * x + cos_NKJ * z;

    k[0] = AC_ECEF[0][0] * B_STar[0] + AC_ECEF[0][1] * B_STar[1] + AC_ECEF[0][2] * B_STar[2];
    k[1] = AC_ECEF[1][0] * B_STar[0] + AC_ECEF[1][1] * B_STar[1] + AC_ECEF[1][2] * B_STar[2];
    k[2] = AC_ECEF[2][0] * B_STar[0] + AC_ECEF[2][1] * B_STar[1] + AC_ECEF[2][2] * B_STar[2];

    double ECEFTarget[3];
    // 求解目标在地球坐标系下坐标
    ECEFGeolocat(ECEFTarget, k, b, tar_high);
    ECEFToGPS(GPSTarget, ECEFTarget);

    Tar_gps->Lat = GPSTarget[0] * PI_Agl;
    Tar_gps->Lon = GPSTarget[1] * PI_Agl;
    Tar_gps->Alt = GPSTarget[2];
}
// 距离优先广域返回参数
void Out_GY_Dis() {
    // 实际成像参数,载荷真实的成像参数
    // 名  称:IR广域成像范围参数1
    memset(&param_Compute_Output.real_IR_wide_image_paras, 0, sizeof(COMP_IR_WIDE_IMAGE_PARAS));
    param_Compute_Output.real_IR_wide_image_paras.IR_range_lowline        = range_lowline / 1000;
    param_Compute_Output.real_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION;
    param_Compute_Output.real_IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = V_IR_WIDE_IMAGE_MODE_DIS_PRIO;
    param_Compute_Output.real_IR_wide_image_paras.D_area_altitude         = tar_high;
    param_Compute_Output.real_IR_wide_image_paras.IR_range_upline         = range_upline / 1000;

    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    memset(&param_Compute_Output.real_area_image_paras[0], 0, sizeof(COMP_AREA_IMAGE_PARAS) * 3);
    // 名  称:IR区域监视范围参数1
    memset(&param_Compute_Output.real_area_monitor_paras, 0, sizeof(COMP_AREA_MONITOR_PARAS));
}
// 方位优先广域返回参数
void Out_GY_Az() {
    // 实际成像参数,载荷真实的成像参数
    // 名  称:IR广域成像范围参数1
    memset(&param_Compute_Output.real_IR_wide_image_paras, 0, sizeof(COMP_IR_WIDE_IMAGE_PARAS));
    param_Compute_Output.real_IR_wide_image_paras.AZ_area_altitude    = tar_high;
    param_Compute_Output.real_IR_wide_image_paras.IR_scan_start_angle = KJ_start_pi.WKJ * 1000;
    param_Compute_Output.real_IR_wide_image_paras.IR_IMAGE_RANGE      = range_lowline / 1000;
    param_Compute_Output.real_IR_wide_image_paras.IR_scan_end_angle   = KJ_end_pi.WKJ * 1000;
    param_Compute_Output.real_IR_wide_image_paras.IR_WIDE_IMAGE_MODE  = V_IR_WIDE_IMAGE_MODE_AZ_PRIO;

    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    memset(&param_Compute_Output.real_area_image_paras[0], 0, sizeof(COMP_AREA_IMAGE_PARAS) * 3);
    // 名  称:IR区域监视范围参数1
    memset(&param_Compute_Output.real_area_monitor_paras, 0, sizeof(COMP_AREA_MONITOR_PARAS));
}
// 区域返回参数
void Out_QY() {
    // 实际成像参数,载荷真实的成像参数
    // 名  称:IR广域成像范围参数1
    memset(&param_Compute_Output.real_IR_wide_image_paras, 0, sizeof(COMP_IR_WIDE_IMAGE_PARAS));
    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    memcpy(&param_Compute_Output.real_area_image_paras[0], &param_Compute_Input_Fromfc.comp_area_image_paras[0], sizeof(COMP_AREA_IMAGE_PARAS) * 3);

    // 名  称:IR区域监视范围参数1
    memset(&param_Compute_Output.real_area_monitor_paras, 0, sizeof(COMP_AREA_MONITOR_PARAS));
}
// 监视返回参数
void Out_JS() {
    // 实际成像参数,载荷真实的成像参数
    // 名  称:IR广域成像范围参数1
    memset(&param_Compute_Output.real_IR_wide_image_paras, 0, sizeof(COMP_IR_WIDE_IMAGE_PARAS));
    // 名  称:IR区域成像范围参数,根据区域编号缓存三个1
    memset(&param_Compute_Output.real_area_image_paras[0], 0, sizeof(COMP_AREA_IMAGE_PARAS) * 3);
    // 名  称:IR区域监视范围参数1
    memset(&param_Compute_Output.real_area_monitor_paras, 0, sizeof(COMP_AREA_MONITOR_PARAS));

    param_Compute_Output.real_area_monitor_paras.latitude  = param_Compute_Output.image_center_latitude * Agl_PI * 1000;
    param_Compute_Output.real_area_monitor_paras.longitude = param_Compute_Output.image_center_longitude * Agl_PI * 1000;
    param_Compute_Output.real_area_monitor_paras.altitude  = param_Compute_Output.A818_ImageCenterHeight;
}
// 计算当前视轴
void ComptLos() {
    KJAgl_AC_pi.NKJ = KJAgl_pi.NKJ; // AC坐标系下内框架角
    KJAgl_AC_pi.WKJ = KJAgl_pi.WKJ; // AC坐标系下外框架角

    float sin_WKJ;
    float sin_NKJ;
    float cos_WKJ;
    float cos_NKJ;
    cos_WKJ = cos(KJAgl_pi.WKJ); // + geo_WKJ_ParaErro
    cos_NKJ = cos(KJAgl_pi.NKJ); //+ geo_NKJ_ParaErro
    sin_WKJ = sin(KJAgl_pi.WKJ); // + geo_WKJ_ParaErro
    sin_NKJ = sin(KJAgl_pi.NKJ); //+ geo_NKJ_ParaErro

    float                   los_ac[3];
    struct_Position_float64 los_ned;

    los_ac[0] = cos_WKJ * sin_NKJ;
    los_ac[1] = sin_WKJ * sin_NKJ;
    los_ac[2] = cos_NKJ;

    los_ned.X = AC_NED[0][0] * los_ac[0] + AC_NED[0][1] * los_ac[1] + AC_NED[0][2] * los_ac[2];
    los_ned.Y = AC_NED[1][0] * los_ac[0] + AC_NED[1][1] * los_ac[1] + AC_NED[1][2] * los_ac[2];
    los_ned.Z = AC_NED[2][0] * los_ac[0] + AC_NED[2][1] * los_ac[1] + AC_NED[2][2] * los_ac[2];

    // 返回内框架角计算结果
    KJAgl_NED_pi.WKJ = atan2(los_ned.Y, los_ned.X);
    // 返回外框架角计算结果
    KJAgl_NED_pi.NKJ = acos(los_ned.Z);
}

// 计算近距远距
void ComptRange() {

    struct_KJAgl            temp_startAgl;
    struct_KJAgl            temp_endAgl;
    struct_KJAgl            temp_KJAgl_NED;
    float                   sin_WKJ;
    float                   sin_NKJ;
    float                   cos_WKJ;
    float                   cos_NKJ;
    float                   los_ac[3];
    struct_Position_float64 los_ned;

    if (NKJ_Max_PI < KJ_start_pi.NKJ) // 内框架超最高NKJ_Max_PI
    {
        temp_startAgl.NKJ = NKJ_Max_PI;
    } else if (NKJ_Min_PI > KJ_start_pi.NKJ) // 内框架超最低
    {
        temp_startAgl.NKJ = NKJ_Min_PI;
    } else {
        temp_startAgl.NKJ = KJ_start_pi.NKJ;
    }

    if (WKJ_Max_PI < KJ_start_pi.WKJ) // 内框架超最高NKJ_Max_PI
    {
        temp_startAgl.WKJ = WKJ_Max_PI;
    } else if (WKJ_Min_PI > KJ_start_pi.WKJ) // 内框架超最低
    {
        temp_startAgl.WKJ = WKJ_Min_PI;
    } else {
        temp_startAgl.WKJ = KJ_start_pi.WKJ;
    }

    cos_WKJ = cos(temp_startAgl.WKJ); // + geo_WKJ_ParaErro
    cos_NKJ = cos(temp_startAgl.NKJ); //+ geo_NKJ_ParaErro
    sin_WKJ = sin(temp_startAgl.WKJ); // + geo_WKJ_ParaErro
    sin_NKJ = sin(temp_startAgl.NKJ); //+ geo_NKJ_ParaErro

    los_ac[0] = cos_WKJ * sin_NKJ;
    los_ac[1] = sin_WKJ * sin_NKJ;
    los_ac[2] = cos_NKJ;

    los_ned.X = AC_NED[0][0] * los_ac[0] + AC_NED[0][1] * los_ac[1] + AC_NED[0][2] * los_ac[2];
    los_ned.Y = AC_NED[1][0] * los_ac[0] + AC_NED[1][1] * los_ac[1] + AC_NED[1][2] * los_ac[2];
    los_ned.Z = AC_NED[2][0] * los_ac[0] + AC_NED[2][1] * los_ac[1] + AC_NED[2][2] * los_ac[2];

    // 返回内框架角计算结果
    temp_KJAgl_NED.WKJ = atan2(los_ned.Y, los_ned.X);
    // 返回外框架角计算结果
    temp_KJAgl_NED.NKJ = acos(los_ned.Z);

    range_lowline = tan(temp_KJAgl_NED.NKJ) * planTar_high; // 近距

    //-------------远距

    if (NKJ_Max_PI < KJ_end_pi.NKJ) // 内框架超最高NKJ_Max_PI
    {
        temp_endAgl.NKJ = NKJ_Max_PI;
    } else if (NKJ_Min_PI > KJ_end_pi.NKJ) // 内框架超最低
    {
        temp_endAgl.NKJ = NKJ_Min_PI;
    } else {
        temp_endAgl.NKJ = KJ_end_pi.NKJ;
    }

    if (WKJ_Max_PI < KJ_end_pi.WKJ) // 内框架超最高NKJ_Max_PI
    {
        temp_endAgl.WKJ = WKJ_Max_PI;
    } else if (WKJ_Min_PI > KJ_end_pi.WKJ) // 内框架超最低
    {
        temp_endAgl.WKJ = WKJ_Min_PI;
    } else {
        temp_endAgl.WKJ = KJ_end_pi.WKJ;
    }

    cos_WKJ = cos(temp_endAgl.WKJ); // + geo_WKJ_ParaErro
    cos_NKJ = cos(temp_endAgl.NKJ); //+ geo_NKJ_ParaErro
    sin_WKJ = sin(temp_endAgl.WKJ); // + geo_WKJ_ParaErro
    sin_NKJ = sin(temp_endAgl.NKJ); //+ geo_NKJ_ParaErro

    los_ac[0] = cos_WKJ * sin_NKJ;
    los_ac[1] = sin_WKJ * sin_NKJ;
    los_ac[2] = cos_NKJ;

    los_ned.X = AC_NED[0][0] * los_ac[0] + AC_NED[0][1] * los_ac[1] + AC_NED[0][2] * los_ac[2];
    los_ned.Y = AC_NED[1][0] * los_ac[0] + AC_NED[1][1] * los_ac[1] + AC_NED[1][2] * los_ac[2];
    los_ned.Z = AC_NED[2][0] * los_ac[0] + AC_NED[2][1] * los_ac[1] + AC_NED[2][2] * los_ac[2];

    // 返回内框架角计算结果
    temp_KJAgl_NED.WKJ = atan2(los_ned.Y, los_ned.X);
    // 返回外框架角计算结果
    temp_KJAgl_NED.NKJ = acos(los_ned.Z);

    range_upline = tan(temp_KJAgl_NED.NKJ) * planTar_high; // 远距
}
// ------------------------------输入参数处理-------------------------------//
//  函数名称：ProcessInPram
//  功能：处理计算需要的参数
//  输入参数：
//  返回参数：
//  说明：无
// ---------------------------------------------------------------------------//
void ProcessInPram() {
    AC_Position_pi.Lat  = param_Compute_Input_Fromfpga.latitude;     // 载机纬度 (弧度)
    AC_Position_pi.Lon  = param_Compute_Input_Fromfpga.longitude;    // 载机经度
    AC_Position_pi.Alt  = param_Compute_Input_Fromfpga.altitude;     // 载机高度
    AttitudeAC_pi.Yaw   = param_Compute_Input_Fromfpga.true_heading; // 航向角
    AttitudeAC_pi.Pitch = param_Compute_Input_Fromfpga.pitch;        // 俯仰角
    AttitudeAC_pi.Roll  = param_Compute_Input_Fromfpga.roll;         // 横滚角

    KJAgl_pi.WKJ     = param_Compute_Input_Fromfpga.rtime_direction_frame * Agl_PI;       // 实时外框架角
    KJAgl_pi.NKJ     = (param_Compute_Input_Fromfpga.rtime_pitch_frame + 90) * Agl_PI;    // 实时内框架角
    KJAgl_exp_pi.WKJ = param_Compute_Input_Fromfpga.exposure_direction_frame * Agl_PI;    // 曝光时刻外框架角
    KJAgl_exp_pi.NKJ = (param_Compute_Input_Fromfpga.exposure_pitch_frame + 90) * Agl_PI; // 曝光时刻内框架角

    KFKZAgl_exp_pi.WKJ = param_Compute_Input_Fromfpga.kfbgskfwbcwz * Agl_PI; // 曝光时刻快反角
    KFKZAgl_exp_pi.NKJ = param_Compute_Input_Fromfpga.kfbgskfybcwz * Agl_PI; // 曝光时刻快反角

    if (1 == param_Compute_Input_Fromfpga.flag_view_State) // 小视场
    {
        tocal_foclen_KJ = param_Compute_Input_Fromfpga.jj_Big_KJ; // 可见大视场-短焦
        if (tocal_foclen_KJ > 492 || tocal_foclen_KJ < 292) {
            tocal_foclen_KJ = 392;
        }
    } else {
        tocal_foclen_KJ = param_Compute_Input_Fromfpga.jj_Small_KJ; // 可见小视场-长焦 1960mm
        if (tocal_foclen_KJ > 1990 || tocal_foclen_KJ < 1930) {
            tocal_foclen_KJ = 1960;
        }
    }

    tocal_pixsize_KJ = 4.5; // 像元尺寸4.5
}
// ------------------------------输出参数处理-------------------------------//
//  函数名称：ProcessOutPram
//  功能：处理计算需要的参数
//  输入参数：
//  返回参数：
//  说明：无
// ---------------------------------------------------------------------------//
void ProcessOutPram() {
    param_Compute_Output.toKJ_direction_speed = KJ_omiga_pi.WKJ * PI_Agl; // 框架方位扫描速度指令°/s
    param_Compute_Output.toKJ_pitch_speed     = KJ_omiga_pi.NKJ * PI_Agl; // 框架俯仰扫描速度指令 °/s
    if (param_Compute_Output.toKJ_direction_speed > 20) {
        param_Compute_Output.toKJ_direction_speed = 20;
    }
    if (param_Compute_Output.toKJ_pitch_speed > 20) {
        param_Compute_Output.toKJ_pitch_speed = 20;
    }
    if (param_Compute_Output.toKJ_direction_speed < -20) {
        param_Compute_Output.toKJ_direction_speed = -20;
    }
    if (param_Compute_Output.toKJ_pitch_speed < -20) {
        param_Compute_Output.toKJ_pitch_speed = -20;
    }

    if (WKJ_Max_PI < KJ_start_pi.WKJ) // 内框架超最高NKJ_Max_PI
    {
        KJ_start_pi.WKJ = WKJ_Max_PI;
    }
    if (WKJ_Min_PI > KJ_start_pi.WKJ) // 内框架超最低
    {
        KJ_start_pi.WKJ = WKJ_Min_PI;
    }

    param_Compute_Output.toKJ_direction_start = KJ_start_pi.WKJ * PI_Agl; // 框架方位指令   起始角（LSB=0.0001°）

    if (WKJ_Max_PI < KJ_end_pi.WKJ) // 内框架超最高NKJ_Max_PI
    {
        KJ_end_pi.WKJ = WKJ_Max_PI;
    }
    if (WKJ_Min_PI > KJ_end_pi.WKJ) // 内框架超最低
    {
        KJ_end_pi.WKJ = WKJ_Min_PI;
    }
    param_Compute_Output.toKJ_direction_end = KJ_end_pi.WKJ * PI_Agl; // 框架方位指令   结束角 °

    if (NKJ_Max_PI < KJ_start_pi.NKJ) // 内框架超最高NKJ_Max_PI
    {
        KJ_start_pi.NKJ = NKJ_Max_PI;
    }
    if (NKJ_Min_PI > KJ_start_pi.NKJ) // 内框架超最低
    {
        KJ_start_pi.NKJ = NKJ_Min_PI;
    }
    param_Compute_Output.toKJ_pitch_start = KJ_start_pi.NKJ * PI_Agl - 90; // 框架俯仰指令   起始角 °

    if (NKJ_Max_PI < KJ_end_pi.NKJ) // 内框架超最高NKJ_Max_PI
    {
        KJ_end_pi.NKJ = NKJ_Max_PI;
    }
    if (NKJ_Min_PI > KJ_end_pi.NKJ) // 内框架超最低
    {
        KJ_end_pi.NKJ = NKJ_Min_PI;
    }
    param_Compute_Output.toKJ_pitch_end = KJ_end_pi.NKJ * PI_Agl - 90; // 框架俯仰指令   结束角 °

    param_Compute_Output.toKJ_speed_hight                     = speed_hight;                  // 速高比
    param_Compute_Output.toKJ_pitch_image_motion_velocity     = img_move_omiga_x_pi * PI_Agl; // 前向向像移速度
    param_Compute_Output.toKJ_direction_image_motion_velocity = img_move_omiga_y_pi * PI_Agl; // 横向像移速度

    param_Compute_Output.toTJ_distance   = photo_Dis;
    param_Compute_Output.frames_Num      = TD_PhotoNum;           // 每条带成像帧数
    param_Compute_Output.qy_zq_num       = QYCX_ScanOverTime + 1; // 区域周期号-连续成像正在执行第几次（从1开始）
    param_Compute_Output.qy_td_total_num = QYCX_NeedTDNum;        // 当前区域条带总数

    param_Compute_Output.toFPGA_time_speed    = speed_time * 1000;    // 速度信号时间
    param_Compute_Output.toFPGA_time_location = location_time * 1000; // 位置信号时间
    param_Compute_Output.QYCX_Over_flag       = QYCX_Over_flag;       // 已完成扫描标志

    param_Compute_Output.sensor_los_geo_az      = KJAgl_NED_pi.WKJ * 1000;                 // 地理系_传感器LOS_方位mrad
    param_Compute_Output.sensor_los_geo_el      = (KJAgl_NED_pi.NKJ - 90 * Agl_PI) * 1000; // 地理系_传感器LOS_俯仰mrad
    param_Compute_Output.sensor_los_platform_az = KJAgl_AC_pi.WKJ * 1000;                  // 机体系_传感器LOS_方位mrad
    param_Compute_Output.sensor_los_platform_el = (KJAgl_AC_pi.NKJ - 90 * Agl_PI) * 1000;  // 机体系_传感器LOS_俯仰mrad

    param_Compute_Output.wideCover = cover_wide; // 垂直航向覆盖宽度

    param_Compute_Output.A818_CUR_RESOLUTION    = (0.0045 / tocal_foclen_KJ) * photo_Dis; // 可见像元分辨率
    param_Compute_Output.A818_GROUND_RESOLUTION = (photo_Dis / 30000) * 1.5;              // 地面摄影分辨率

    //	logMsg("WKJ_V:%d,NKJ_V:%d\r\n",(KJ_omiga_pi.WKJ*57.2957795*1000),(KJ_omiga_pi.NKJ*57.2957795*1000),3,4,5,6);
    //	logMsg("WK_start:%d,WK_end:%d\r\n",(KJ_start_pi.WKJ*57.2957795*1000),(KJ_end_pi.WKJ*57.2957795*1000),3,4,5,6);
    //	logMsg("NK_start:%d,NK_end:%d\r\n",(KJ_start_pi.NKJ*57.2957795*1000),(KJ_end_pi.NKJ*57.2957795*1000),3,4,5,6);
    //	logMsg("dis:%d,TD_num:%d,speed_time:%d,dis_time:%d\r\n",(photo_Dis),(TD_PhotoNum),(speed_time*1000),(location_time*1000),5,6);
    //	logMsg("qx_move:%d,hx_move:%d\r\n",( img_move_omiga_x_pi*57.2957795*1000),(img_move_omiga_y_pi*57.2957795*1000),3,4,5,6);
}
