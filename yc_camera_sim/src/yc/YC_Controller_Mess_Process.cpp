/*
 * YC_Controller_ToolsFunc.c
 *
 *  Created on: 2025年5月16日
 *      Author: wangx
 */

#include "YC_Controller_Mess_Process.h"
#include <sysTypes.h>
// #include <tasks.h>
// #include <attribute.h>
#include "AppTopicIdDef.h"
// #include "YC_Controller_FC_Trans.h"
// #include "YC_Controller_FPGA_Trans.h"
#include "YC_Controller_HMC_Process.h"
#include "YC_Controller_globalVal_Ext.h"
// #include "fcUsrVos.h"
// #include "ficType.h"
// #include "ioFcApi.h"
// #include "ioFcCfg.h"
// #include "semYc.h"
// #include <acClock.h>
// #include <acSmp.h>
// #include <config_appcfg.h>
// #include <logLib.h>
// #include <lstLib.h>
// #include <mosErrno.h>
// #include <printk.h>
#include <stdio.h>
#include <stdlib.h>

// lcy add.
#include <cstring>
#include <global_vars.h>
#include <log_def.h>
#include <udp_trans.h>
#include <utils.h>

// 系数
const double rad_to_deg  = 180.0 / PI;        // 弧度转度
const double mrad_to_deg = 1e-3 * 180.0 / PI; // 毫弧度转度
const double deg_to_rad  = PI / 180.0;        // 度转弧度
const double deg_to_mrad = 1e3 * PI / 180.0;  // 度转毫弧度

// 发送IRST_活动请求通告
void send_Mess_IRST_ACT_REQ_REPORT(UINT8 activity_state, UINT8 act_refused_reason) {
    // 消息发布时间
    mess_ToFC_IRST_ACT_REQ_REPORT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    // 消息发布者ID
    mess_ToFC_IRST_ACT_REQ_REPORT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 名  称:请求发布者ID
    mess_ToFC_IRST_ACT_REQ_REPORT.req_publisher_ID.subdomain_ID = cmd_From_FC.current_IRST_ACT_REQ.msg_publisher_ID.subdomain_ID;
    // 名  称:活动编号_64
    mess_ToFC_IRST_ACT_REQ_REPORT.activity_number_64 = cmd_From_FC.current_IRST_ACT_REQ.activity_number_64;
    // 名  称:拒绝请求原因
    mess_ToFC_IRST_ACT_REQ_REPORT.act_refused_reason = act_refused_reason;
    // 名  称:活动状态
    mess_ToFC_IRST_ACT_REQ_REPORT.activity_state = activity_state;
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_IRST_ACT_REQ_REPORT, (UINT8 *)&mess_ToFC_IRST_ACT_REQ_REPORT, sizeof(IRST_ACT_REQ_REPORT));
}

// 工作状态报告
void send_Mess_WORK_STATE_REPORT(UINT32 start_remain_time, UINT32 bitpercent) {
    // 消息发布时间
    mess_ToFC_WORK_STATE_REPORT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    mess_ToFC_WORK_STATE_REPORT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:start_remain_time
    // 名  称:时间_启动倒计时
    mess_ToFC_WORK_STATE_REPORT.start_remain_time = start_remain_time;
    // 标识符:subsys_work_state
    // 名  称:工作状态
    mess_ToFC_WORK_STATE_REPORT.subsys_work_state = main_Control_State_Param.work_state;
    // 标识符:subsys_main_mode
    // 名  称:工作模式
    mess_ToFC_WORK_STATE_REPORT.subsys_main_mode = main_Control_State_Param.main_mode;
    // 标识符:AC_ID
    // 名  称:飞机ID
    mess_ToFC_WORK_STATE_REPORT.AC_ID = temp_mess_FromFc_MISSION_EVENT_REPORT.VMS_AC_ID;
    // 标识符:security_level
    // 名  称:系统安全_密级
    mess_ToFC_WORK_STATE_REPORT.security_level = V_SECURITY_LEVEL_SECRET; // 秘密
    // 标识符:bit_process_percent
    // 名  称:自检测进度,用于表示百分比数值，LSB=0.01表示的是0.01%。
    mess_ToFC_WORK_STATE_REPORT.bit_process_percent = bitpercent;
    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    mess_ToFC_WORK_STATE_REPORT.subsys_electrify_amount = nbMess_hwInfo_FLASH.electrify_amount_From_FPGAsave;
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_WORK_STATE_REPORT, (UINT8 *)&mess_ToFC_WORK_STATE_REPORT, sizeof(WORK_STATE_REPORT));
}

// IRST工作参数报告
void make_Mess_IRST_OPERATIONAL_PARAS() {
    int i = 0;
    // 消息发布时间
    mess_ToFC_IRST_OPERATIONAL_PARAS.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    // 标识符:msg_publisher_ID
    // 名  称:消息发布者ID
    mess_ToFC_IRST_OPERATIONAL_PARAS.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_IRST_OPERATIONAL_PARAS.security_level                = V_SECURITY_LEVEL_SECRET; // 密级
    mess_ToFC_IRST_OPERATIONAL_PARAS.paras_validity                = 1;                       // 参数有效性为有效

    // 名  称:轮载状态_主
    mess_ToFC_IRST_OPERATIONAL_PARAS.WOW_main = temp_mess_FromFc_MISSION_EVENT_REPORT.WOW_main;
    // 名  称:任务阶段
    mess_ToFC_IRST_OPERATIONAL_PARAS.MS_phase = mess_ToFC_IRST_OPERATIONAL_PARAS.MS_phase;
    // 名  称:任务主模式
    mess_ToFC_IRST_OPERATIONAL_PARAS.mission_main_mode = mess_ToFC_IRST_OPERATIONAL_PARAS.mission_main_mode;
    // 名  称:制冷状态，接收红外探测器返回参数后处理
    if (mess_From_TG.HW_Coolling_Error == 1)
        mess_ToFC_IRST_OPERATIONAL_PARAS.cool_state = 3;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.cool_state = mess_From_TG.Cool_state + 1;
    // 名  称:IRST工作参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.irst_mode_paras.irst_form_mode  = main_Control_State_Param.irst_form_mode;
    mess_ToFC_IRST_OPERATIONAL_PARAS.irst_mode_paras.irst_work_state = main_Control_State_Param.irst_work_state;
    mess_ToFC_IRST_OPERATIONAL_PARAS.irst_mode_paras.irst_work_mode  = main_Control_State_Param.main_mode;
    // 名  称:IR图像参数----------------------------------------------------------------------------------------------
    // 名  称:可见光调焦模式
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_focus_mode = mess_From_TJ.state_tjmode_kj + 1;
    // 名  称:可见光调光模式,调光
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_dim_mode = mess_From_TG.KJTG_Mode_back + 1; // bit0 0-可见自动调光,1-可见手动调光;
    // 名  称:可见光增强状态,调光
    if (mess_From_TG.KJImg_EnHance_back == 0)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_enhance_mode = 2;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_enhance_mode = 1;
    // 名  称:可见光去雾状态,调光
    if (mess_From_TG.KJImg_ReMoveMist_back == 0)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_mist_eliminate_state = 2;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_mist_eliminate_state = 1;
    // 名  称:可见光曝光时间,调光
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_exposure_time = mess_From_TG.KJExpTime_back;
    // 名  称:视频极化,调光
    // bit4 红外图像极性，0-白热，1-黑热
    if (mess_From_TG.HWImg_Ply_back == 1)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.video_polar = 1;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.video_polar = 2;
    // 名  称:红外系数,调光
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.infrared_coefficient = mess_From_TG.HW_Coff_back;
    // 名  称:红外调焦模式
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.infrared_focus_mode = mess_From_TJ.state_tjmode_hw + 1;
    // 名  称:红外调光模式,调光
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.infrared_dim_mode = mess_From_TG.HWTG_Mode_back + 1;
    // 名  称:红外调焦值
    //	mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.focus_value_infrared = mess_From_TJ.jmwz_hw_real;//返回真实值
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.focus_value_infrared = cmd_From_FC.irst_cmd_param_IR_image_paras_infra.focus_value;
    // 名  称:可见光调焦值
    //	mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.focus_value_light = mess_From_TJ.jmwz_kj_real;//返回真实值
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.focus_value_light = cmd_From_FC.irst_cmd_param_IR_image_paras_light.focus_value;
    // 名  称:环境类型
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.environmnet_type = cmd_From_FC.irst_cmd_param_environmnet_type;
    // 名  称:红外增强状态
    if (mess_From_TG.HWImg_EnHance_back == 0)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.infrared_enhance_mode = 2;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.infrared_enhance_mode = 1;

    // 名  称:非均匀校正状态
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.non_uniform_correct_state = main_Control_State_Param.jiaozheng_state;
    // 名  称:红外调光值,调光-暂时写曝光时间
    //	mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_value_infrared = mess_From_TG.HWExpTime_back * 0.1;
    // 名  称:可见光调光值,调光
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_image_paras.light_value_light = cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_value;
    // 名  称:光电成像参数
    // 名  称:IR广域成像范围参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_range_lowline        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_lowline;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_IMAGE_RANGE          = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_IMAGE_RANGE;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_range_upline         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_upline;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_scan_end_angle       = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_end_angle;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.IR_scan_start_angle     = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_start_angle;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.D_area_altitude         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.D_area_altitude;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_wide_image_paras.AZ_area_altitude        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.AZ_area_altitude;

    // 名  称:光电区域成像范围参数
    for (i = 0; i < 3; i++) {
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_image_paras_IR[i].center_point_pos = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_image_paras_IR[i].IR_IMG_FLAG      = param_Compute_Output.real_area_image_paras[i].IR_IMG_FLAG;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_image_paras_IR[i].IR_AREA_LENGTH   = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
        // 名  称:区域有效性
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_image_paras_IR[i].Area_validity = cmd_From_FC.irst_cmd_param_area_image_paras_validity[i];
    }
    // 名  称:光电区域监视范围参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_monitor_paras_IR.center_point_pos = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.area_monitor_paras_IR.IR_IMG_FLAG      = param_Compute_Output.real_area_monitor_paras.IR_IMG_FLAG;

    // 名  称:光电成像方式
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR.IR_IMG_MODE = param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE;
    // 名  称:光雷实际成像参数
    // 名  称:IR广域成像范围参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_range_lowline        = param_Compute_Output.real_IR_wide_image_paras.IR_range_lowline * 100;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = param_Compute_Output.real_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = param_Compute_Output.real_IR_wide_image_paras.IR_WIDE_IMAGE_MODE;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.AZ_area_altitude        = param_Compute_Output.real_IR_wide_image_paras.AZ_area_altitude * 2;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.D_area_altitude         = param_Compute_Output.real_IR_wide_image_paras.D_area_altitude * 2;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_range_upline         = param_Compute_Output.real_IR_wide_image_paras.IR_range_upline * 100;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_scan_start_angle     = param_Compute_Output.real_IR_wide_image_paras.IR_scan_start_angle * 10;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_IMAGE_RANGE          = param_Compute_Output.real_IR_wide_image_paras.IR_IMAGE_RANGE * 100;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_wide_image_paras.IR_scan_end_angle       = param_Compute_Output.real_IR_wide_image_paras.IR_scan_end_angle * 10;
    // 名  称:光电区域成像范围参数
    for (i = 0; i < 3; i++) {
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._altitude  = param_Compute_Output.real_area_image_paras[i].altitude * 100;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._latitude  = param_Compute_Output.real_area_image_paras[i].latitude * 100000;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._longitude = param_Compute_Output.real_area_image_paras[i].longitude * 100000;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].IR_IMG_FLAG                 = param_Compute_Output.real_area_image_paras[i].IR_IMG_FLAG;
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].IR_AREA_LENGTH              = param_Compute_Output.real_area_image_paras[i].IR_AREA_LENGTH;
        // 名  称:区域有效性
        mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].Area_validity = cmd_From_FC.irst_cmd_param_area_image_paras_validity[i];
        if (mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].Area_validity == V_AREA_VALIDITY_INVALID) {
            mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._altitude  = 0;
            mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._latitude  = 0;
            mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].center_point_pos._longitude = 0;
            mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].IR_IMG_FLAG                 = 0;
            mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_image_paras_IR[i].IR_AREA_LENGTH              = 0;
        }
    }
    // 名  称:光电区域监视范围参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_monitor_paras_IR.center_point_pos._latitude  = param_Compute_Output.real_area_monitor_paras.latitude * 100000;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_monitor_paras_IR.center_point_pos._longitude = param_Compute_Output.real_area_monitor_paras.longitude * 100000;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_monitor_paras_IR.center_point_pos._altitude  = param_Compute_Output.real_area_monitor_paras.altitude * 100;
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.area_monitor_paras_IR.IR_IMG_FLAG                 = param_Compute_Output.real_area_monitor_paras.IR_IMG_FLAG;

    // 名  称:光电成像方式
    mess_ToFC_IRST_OPERATIONAL_PARAS.image_volum_IR_actual.IR_IMG_MODE = param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE;

    // 名  称:IR光窗参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_Transom_paras.Transom_temp = mess_From_GCWK.temp * 0.1;
    if (mess_From_GCWK.cmd == GCWK_CMD_OPEN)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_Transom_paras.Transom_mist_eliminate_state = V_TRANSOM_MIST_ELIMINATE_STATE_ON;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_Transom_paras.Transom_mist_eliminate_state = V_TRANSOM_MIST_ELIMINATE_STATE_OFF;
    // 名  称:研制厂家
    mess_ToFC_IRST_OPERATIONAL_PARAS.development_company = V_DEVELOPMENT_COMPANY_CIOMP;

    // 名  称:光电地理定位标志
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_LOCATION_MARK = V_IR_LOCATION_MARK_IR_INS;

    // 名  称:光电惯导对准状态
    if (mess_From_PCS_DATA.status_gdgzms == 3)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_INS_ALIGN_STATE = V_IR_INS_ALIGN_STATE_SUCCESS;
    else if (mess_From_PCS_DATA.status_gdgzms == 0 || mess_From_PCS_DATA.status_gdgzms == 1 || mess_From_PCS_DATA.status_gdgzms == 2)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_INS_ALIGN_STATE = V_IR_INS_ALIGN_STATE_ALIGN_ING;
    else if (mess_From_PCS_DATA.status_sbzt == 1 || mess_From_PCS_DATA.status_gdgzms == 4)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_INS_ALIGN_STATE = V_IR_INS_ALIGN_STATE_MISALIGN;

    // 名  称:准备状态参数
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_prepare_paras.prepare_state          = V_PREPARE_STATE_NORMAL;
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_prepare_paras.infrared_correct_state = main_Control_State_Param.jiaozheng_state;
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_prepare_paras.prepare_state_focus    = main_Control_State_Param.tj_state;
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_prepare_paras.prepare_state_dim      = main_Control_State_Param.tg_state;

    // 名  称:参数有效性
    mess_ToFC_IRST_OPERATIONAL_PARAS.paras_validity = V_CALIBRATE_DATA_VALIDITY_YES;

    // 名  称:光电传感器状态
    mess_ToFC_IRST_OPERATIONAL_PARAS.IR_SENSOR = cmd_From_FC.irst_cmd_param_IR_SENSOR;
    // 名  称:图像跟踪状态
    mess_ToFC_IRST_OPERATIONAL_PARAS.TGT_TRACK_STATE = main_Control_State_Param.track_state;
    // 名  称:IRST扫描工作状态
    if (*(UINT16 *)(((void *)&mess_From_KJ) + 3) != 0)
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_scan_work_state = V_IR_SCAN_WORK_STATE_DEGRADE;
    else
        mess_ToFC_IRST_OPERATIONAL_PARAS.IR_scan_work_state = V_IR_SCAN_WORK_STATE_NORMAL;
    // 名  称:IRST_区域监视视频带宽
    mess_ToFC_IRST_OPERATIONAL_PARAS.IRST_Video_BAND = cmd_From_FC.irst_cmd_param_IRST_Video_BAND;
    // 名  称:冻结状态，不用做了，在注释信息中标注
    //	mess_ToFC_IRST_OPERATIONAL_PARAS.frozen_state ;
}

// IRST工作参数报告-发送
void send_Mess_IRST_OPERATIONAL_PARAS() {
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_IRST_OPERATIONAL_PARAS, (UINT8 *)&mess_ToFC_IRST_OPERATIONAL_PARAS, sizeof(IRST_OPERATIONAL_PARAS));
}

// 硬件配置信息报告
void send_Mess_HW_CONFIG_INFO_REPORT() {
    // 消息发布时间
    mess_ToFC_HW_CONFIG_INFO_REPORT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_HW_CONFIG_INFO_REPORT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    mess_ToFC_HW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_serial_number = 0; // 第0包
    mess_ToFC_HW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_total_count   = 1; // 共1包
    // 标识符:config_item_count
    // 名  称:配置项数量
    mess_ToFC_HW_CONFIG_INFO_REPORT.config_item_count = 4;
    // 标识符:HW_config_info
    // 名  称:硬件配置信息，待补充
    memcpy((void *)(mess_ToFC_HW_CONFIG_INFO_REPORT.HW_config_info), (void *)(nbMess_hwInfo_FLASH.HW_config_info), sizeof(HW_CONFIG_INFO_TYPE_DEF) * 6);

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_HW_CONFIG_INFO_REPORT, (UINT8 *)&mess_ToFC_HW_CONFIG_INFO_REPORT, sizeof(HW_CONFIG_INFO_REPORT));
}

// 软件配置信息报告
void send_Mess_SW_CONFIG_INFO_REPORT() {
    // 消息发布时间
    mess_ToFC_SW_CONFIG_INFO_REPORT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_SW_CONFIG_INFO_REPORT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    mess_ToFC_SW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_serial_number = 1; // 第1包
    mess_ToFC_SW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_total_count   = 2; // 共2包
    // 标识符:config_item_count
    // 名  称:配置项数量
    mess_ToFC_SW_CONFIG_INFO_REPORT.config_item_count = 7;
    // 标识符:SW_config_info
    // 名  称:软件配置信息，待补充
    memcpy((void *)(mess_ToFC_SW_CONFIG_INFO_REPORT.SW_config_info), (void *)(nbMess_hwInfo_FLASH.SW_config_info), sizeof(SW_CONFIG_INFO_TYPE_DEF) * 7);

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_SW_CONFIG_INFO_REPORT, (UINT8 *)&mess_ToFC_SW_CONFIG_INFO_REPORT, sizeof(SW_CONFIG_INFO_REPORT));

    memset(&mess_ToFC_SW_CONFIG_INFO_REPORT, 0, sizeof(SW_CONFIG_INFO_REPORT));

    // 消息发布时间
    mess_ToFC_SW_CONFIG_INFO_REPORT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_SW_CONFIG_INFO_REPORT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    mess_ToFC_SW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_serial_number = 2; // 第2包
    mess_ToFC_SW_CONFIG_INFO_REPORT.data_block_trans_mark.data_block_total_count   = 2; // 共2包
    // 标识符:config_item_count
    // 名  称:配置项数量
    mess_ToFC_SW_CONFIG_INFO_REPORT.config_item_count = 1;
    // 标识符:SW_config_info
    // 名  称:软件配置信息，待补充
    memcpy((void *)(mess_ToFC_SW_CONFIG_INFO_REPORT.SW_config_info), &nbMess_hwInfo_FLASH.SW_config_info[7], sizeof(SW_CONFIG_INFO_TYPE_DEF));
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_SW_CONFIG_INFO_REPORT, (UINT8 *)&mess_ToFC_SW_CONFIG_INFO_REPORT, sizeof(SW_CONFIG_INFO_REPORT));
}

// 健康管理_Raw数据_IRST
void send_Mess_PHM_DATA_RAW_IRST() {
    // 消息发布时间
    mess_ToFC_PHM_DATA_RAW_IRST.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_PHM_DATA_RAW_IRST.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:subdomain_ID
    // 名  称:功能单元ID
    mess_ToFC_PHM_DATA_RAW_IRST.RawData_MsSubSys_IRST.subdomain_ID = V_NODE_IRRM;
    // 标识符:SubSys_SW_VER
    // 名  称:主控软件版本
    // 说  明:子系统主控软件的版本号，格式要求：
    //        0x0ABC表示A.BC版本
    //        如0x0123表示1.23版本
    //        前1位固定为0
    mess_ToFC_PHM_DATA_RAW_IRST.RawData_MsSubSys_IRST.SubSys_SW_VER = SW_VER;
    // 标识符:subsys_work_state
    // 名  称:工作状态
    // 说  明:子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    //        20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
    //        20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
    mess_ToFC_PHM_DATA_RAW_IRST.RawData_MsSubSys_IRST.subsys_work_state = main_Control_State_Param.work_state;
    // 标识符:subsys_main_mode
    // 名  称:工作模式
    mess_ToFC_PHM_DATA_RAW_IRST.RawData_MsSubSys_IRST.subsys_main_mode = main_Control_State_Param.main_mode;
    // 标识符:subsys_electrify_amount
    // 名  称:上电次数
    // 说  明:表征子系统上电次数
    //        不能上报的功能单元将该信号置0
    mess_ToFC_PHM_DATA_RAW_IRST.RawData_MsSubSys_IRST.subsys_electrify_amount = nbMess_hwInfo_FLASH.electrify_amount_From_FPGAsave;
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_PHM_DATA_RAW_IRST, (UINT8 *)&mess_ToFC_PHM_DATA_RAW_IRST, sizeof(PHM_DATA_RAW_IRST));
}

// 健康管理_Event数据_MS_SUB
void send_Mess_PHM_DATA_EVENT_MS_SUB() {
    static UINT32 update_counter = 0;
    // 消息发布时间
    mess_ToFC_PHM_DATA_EVENT_MS_SUB.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_PHM_DATA_EVENT_MS_SUB.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    update_counter++;
    mess_ToFC_PHM_DATA_EVENT_MS_SUB.update_counter = update_counter; // 从1开始累加
    // todo 补充其他内容
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_PHM_DATA_EVENT_MS_SUB, (UINT8 *)&mess_ToFC_PHM_DATA_EVENT_MS_SUB, sizeof(PHM_DATA_EVENT_MS_SUB));
}

// 健康管理_HMC数据_MS_SUB
void send_Mess_PHM_DATA_HMC_MS_SUB(int pack_num) // 从1开始
{
    static UINT32 update_counter = 0;
    // 消息发布时间
    mess_ToFC_PHM_DATA_HMC_MS_SUB.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_PHM_DATA_HMC_MS_SUB.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    update_counter++;
    mess_ToFC_PHM_DATA_HMC_MS_SUB.update_counter = update_counter; // 从1开始累加

    mess_ToFC_PHM_DATA_HMC_MS_SUB.data_block_trans_mark.data_block_total_count   = nb_HMC_DATA.pack_count;       // 总包数
    mess_ToFC_PHM_DATA_HMC_MS_SUB.data_block_trans_mark.data_block_serial_number = pack_num;                     // 当前包号
    mess_ToFC_PHM_DATA_HMC_MS_SUB.HMC_total_list_number                          = nb_HMC_DATA.hmc_count_upload; // 总条数

    // 如果是最后一包
    if (pack_num * 10 > nb_HMC_DATA.hmc_count_upload) {
        memcpy(mess_ToFC_PHM_DATA_HMC_MS_SUB.HMC_Data_Item_MS_Sub,
               &(nb_HMC_DATA.HMC_Data_Item_MS_Sub_upload[(pack_num - 1) * 10]),
               (nb_HMC_DATA.hmc_count_upload - (pack_num - 1) * 10) * sizeof(HMC_DATA_ITEM_MS_SUB_TYPE_DEF));
    } else // 如果不是最后一包
    {
        memcpy(mess_ToFC_PHM_DATA_HMC_MS_SUB.HMC_Data_Item_MS_Sub,
               &(nb_HMC_DATA.HMC_Data_Item_MS_Sub_upload[(pack_num - 1) * 10]), 10 * sizeof(HMC_DATA_ITEM_MS_SUB_TYPE_DEF));
    }

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_PHM_DATA_HMC_MS_SUB, (UINT8 *)&mess_ToFC_PHM_DATA_HMC_MS_SUB, sizeof(PHM_DATA_HMC_MS_SUB));
}

// 数据库信息
void send_Mess_DATABASEINFO() {
    // 消息发布时间
    mess_ToFC_DATABASEINFO.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_DATABASEINFO.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    // 标识符:data_block_trans_mark
    // 名  称:数据包传输标识
    mess_ToFC_DATABASEINFO.data_block_trans_mark.data_block_serial_number = 0; // 第0包
    mess_ToFC_DATABASEINFO.data_block_trans_mark.data_block_total_count   = 1; // 共1包
    // 标识符:config_item_count
    // 名  称:配置项数量
    mess_ToFC_DATABASEINFO.config_item_count = 6;
    // todo 标识符:DataBaseCfgInfo
    // 名  称:数据库配置信息
    //	DATABASECFGINFO_TYPE_DEF		DataBaseCfgInfo[5];
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_DATABASEINFO, (UINT8 *)&mess_ToFC_DATABASEINFO, sizeof(DATABASEINFO));
}

// IRST像元参数
void send_Mess_IRST_PIXEL_PARAS() {
    // 消息发布时间
    mess_ToFC_IRST_PIXEL_PARAS.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_IRST_PIXEL_PARAS.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_IRST_PIXEL_PARAS.total_num_of_pixel            = 5120 * 4096;
    mess_ToFC_IRST_PIXEL_PARAS.total_damage_pixel_num        = 0;
    mess_ToFC_IRST_PIXEL_PARAS.ratio                         = 0;
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_IRST_PIXEL_PARAS, (UINT8 *)&mess_ToFC_IRST_PIXEL_PARAS, sizeof(IRST_PIXEL_PARAS));
}

// 上报los数据
void send_Mess_IRST_LOS(UINT8 data_valid) {
    mess_ToFC_IRST_LOS.msg_publish_time.time_sys_RTC            = fcSysRtcGet();
    mess_ToFC_IRST_LOS.msg_publisher_ID.subdomain_ID            = V_NODE_IRRM;
    mess_ToFC_IRST_LOS.sensor_los_geo.data_valid                = data_valid;
    mess_ToFC_IRST_LOS.sensor_los_geo.sensor_LOS_az._angle_mrad = param_Compute_Output.sensor_los_geo_az * 1000;
    mess_ToFC_IRST_LOS.sensor_los_geo.sensor_LOS_el._angle_mrad = param_Compute_Output.sensor_los_geo_el * 1000;

    mess_ToFC_IRST_LOS.sensor_los_platform.data_valid                = data_valid;
    mess_ToFC_IRST_LOS.sensor_los_platform.sensor_LOS_az._angle_mrad = param_Compute_Output.sensor_los_platform_az * 1000;
    mess_ToFC_IRST_LOS.sensor_los_platform.sensor_LOS_el._angle_mrad = param_Compute_Output.sensor_los_platform_el * 1000;

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_IRST_LOS, (UINT8 *)&mess_ToFC_IRST_LOS, sizeof(IRST_LOS));
}
// 上报光电IMU导航数据
void send_Mess_IR_NAV_DATA() {
    mess_ToFC_IR_NAV_DATA.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_IR_NAV_DATA.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;

    // 标识符:irst_INS_valid
    // 名  称:IRST载机姿态有效标志
    // 说  明:
    // 单  位:
    // 起始字:0
    // 起始位:8
    if (mess_From_PCS_DATA.status_wxdjyxx == 0 || temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.primary_ins != V_PRIMARY_INS_NA) {
        mess_ToFC_IR_NAV_DATA.IR_IMU_data.irst_INS_valid = 1;
    }

    // 标识符:A818_INS_NOW
    // 名  称:当前使用惯导
    // 说  明:飞机惯导
    //        03H-载荷惯导
    // 单  位:No_Unit
    // LSB  :1
    // 起始字:0
    // 起始位:0
    if (mess_From_PCS_DATA.status_wxdjyxx == 0)
        mess_ToFC_IR_NAV_DATA.IR_IMU_data.A818_INS_NOW = 0x03;
    else
        mess_ToFC_IR_NAV_DATA.IR_IMU_data.A818_INS_NOW = 0x02;

    // 标识符:irst_fly_pitch
    // 名  称:IRST载机俯仰姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:0
    // 起始位:16
    mess_ToFC_IR_NAV_DATA.IR_IMU_data.flight_status.irst_fly_pitch = mess_From_PCS_DATA.pitch * (PI / pow(2, 31)) * 10000;

    // 标识符:irst_fly_course
    // 名  称:IRST载机航向姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:0
    // 起始位:0
    mess_ToFC_IR_NAV_DATA.IR_IMU_data.flight_status.irst_fly_course = mess_From_PCS_DATA.true_heading * (PI / pow(2, 31)) * 10000;

    // 标识符:irst_fly_roll
    // 名  称:IRST载机横滚姿态角
    // 说  明:
    // 单  位:Rad
    // LSB  :0.0001
    // 起始字:1
    // 起始位:0
    mess_ToFC_IR_NAV_DATA.IR_IMU_data.flight_status.irst_fly_roll = mess_From_PCS_DATA.roll * (PI / pow(2, 31)) * 10000;

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_IR_NAV_DATA, (UINT8 *)&mess_ToFC_IR_NAV_DATA, sizeof(IR_NAV_DATA));
}

// 上报红外注释信息
void send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT() {
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.update_counter++;
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras, &mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras,
           sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit, &mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit,
           sizeof(IMAGE_PARAS_TRANSIT_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.AC_ins_info, &mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info,
           sizeof(AC_INS_INFO_TYPE_DEF));

    // 如果是广域或区域成像
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG || main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IRST_IMG_IR;
    }
    // 如果是区域监视
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO;
    }
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.move_tgt_acount  = mess_From_TXCL.tg_count;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_upleft_x    = mess_From_TXCL.tgt1_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_upleft_Y    = mess_From_TXCL.tgt1_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_downright_x = mess_From_TXCL.tgt1_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_downright_y = mess_From_TXCL.tgt1_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_upleft_x    = mess_From_TXCL.tgt2_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_upleft_Y    = mess_From_TXCL.tgt2_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_downright_x = mess_From_TXCL.tgt2_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_downright_y = mess_From_TXCL.tgt2_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_upleft_x    = mess_From_TXCL.tgt3_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_upleft_Y    = mess_From_TXCL.tgt3_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_downright_x = mess_From_TXCL.tgt3_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_downright_y = mess_From_TXCL.tgt3_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_upleft_x    = mess_From_TXCL.tgt4_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_upleft_Y    = mess_From_TXCL.tgt4_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_downright_x = mess_From_TXCL.tgt4_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_downright_y = mess_From_TXCL.tgt4_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_upleft_x    = mess_From_TXCL.tgt5_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_upleft_Y    = mess_From_TXCL.tgt5_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_downright_x = mess_From_TXCL.tgt5_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_downright_y = mess_From_TXCL.tgt5_downright_y;

    // 红外焦距
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.A818_EO_FocalLength = mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_x;
    // 红外曝光时间
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.A818_EO_ExposureTime = mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_Y;

    // 条带张数
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.spare1[0] = mess_To_FPGA.frames_Num;
    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_IR_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT, sizeof(RECONNAISED_AREA_IR_2GCS_EVENT));
}
// 上报可见注释信息
void send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT() {
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.update_counter++;
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras, &mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras,
           sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit, &mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit,
           sizeof(IMAGE_PARAS_TRANSIT_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.AC_ins_info, &mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info,
           sizeof(AC_INS_INFO_TYPE_DEF));

    // 如果是广域或区域成像
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG || main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IRST_IMG_CCD;
    }
    // 如果是区域监视
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO;
    }
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.move_tgt_acount  = mess_From_TXCL.tg_count;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_upleft_x    = mess_From_TXCL.tgt1_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_upleft_Y    = mess_From_TXCL.tgt1_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_downright_x = mess_From_TXCL.tgt1_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_downright_y = mess_From_TXCL.tgt1_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_upleft_x    = mess_From_TXCL.tgt2_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_upleft_Y    = mess_From_TXCL.tgt2_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_downright_x = mess_From_TXCL.tgt2_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_downright_y = mess_From_TXCL.tgt2_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_upleft_x    = mess_From_TXCL.tgt3_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_upleft_Y    = mess_From_TXCL.tgt3_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_downright_x = mess_From_TXCL.tgt3_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_downright_y = mess_From_TXCL.tgt3_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_upleft_x    = mess_From_TXCL.tgt4_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_upleft_Y    = mess_From_TXCL.tgt4_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_downright_x = mess_From_TXCL.tgt4_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_downright_y = mess_From_TXCL.tgt4_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_upleft_x    = mess_From_TXCL.tgt5_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_upleft_Y    = mess_From_TXCL.tgt5_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_downright_x = mess_From_TXCL.tgt5_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_downright_y = mess_From_TXCL.tgt5_downright_y;
    // 条带张数
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.spare1[0] = mess_To_FPGA.frames_Num;
    // 发送消息，发送正常注释信息
    fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_TV_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT, sizeof(RECONNAISED_AREA_TV_2GCS_EVENT));
}

// 上报红外注释信息
void send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT_VIEW() {
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.update_counter++;
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras, &mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras,
           sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit, &mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit,
           sizeof(IMAGE_PARAS_TRANSIT_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.AC_ins_info, &mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info,
           sizeof(AC_INS_INFO_TYPE_DEF));

    // 如果是广域或区域成像
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG || main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IRST_IMG_IR;
    }
    // 如果是区域监视
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO;
    }
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.move_tgt_acount  = mess_From_TXCL.tg_count;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_upleft_x    = mess_From_TXCL.tgt1_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_upleft_Y    = mess_From_TXCL.tgt1_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_downright_x = mess_From_TXCL.tgt1_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt1_downright_y = mess_From_TXCL.tgt1_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_upleft_x    = mess_From_TXCL.tgt2_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_upleft_Y    = mess_From_TXCL.tgt2_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_downright_x = mess_From_TXCL.tgt2_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt2_downright_y = mess_From_TXCL.tgt2_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_upleft_x    = mess_From_TXCL.tgt3_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_upleft_Y    = mess_From_TXCL.tgt3_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_downright_x = mess_From_TXCL.tgt3_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt3_downright_y = mess_From_TXCL.tgt3_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_upleft_x    = mess_From_TXCL.tgt4_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_upleft_Y    = mess_From_TXCL.tgt4_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_downright_x = mess_From_TXCL.tgt4_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt4_downright_y = mess_From_TXCL.tgt4_downright_y;

    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_upleft_x    = mess_From_TXCL.tgt5_upleft_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_upleft_Y    = mess_From_TXCL.tgt5_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_downright_x = mess_From_TXCL.tgt5_downright_x;
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.tgt5_downright_y = mess_From_TXCL.tgt5_downright_y;

    // 红外焦距
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.A818_EO_FocalLength = mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_x;
    // 红外曝光时间
    mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.image_paras_transit.A818_EO_ExposureTime = mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_Y;

    // 发送监视模式下的单帧注释信息
    if (mess_To_TXCL_ZSXX.tx_info[3] == 1) // 如果是单帧图像
    {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO_IMG_IR; // 区域监视单帧红外
        // 发送单帧的注释信息
        fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_IR_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT, sizeof(RECONNAISED_AREA_IR_2GCS_EVENT));
    }
    if (mess_To_TXCL_ZSXX.tx_info[3] == 2) // 如果是冻结帧
    {
        mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO_FRZ_IR; // 区域监视冻结帧红外
                                                                                                                        // 发送单帧的注释信息
        fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_IR_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT, sizeof(RECONNAISED_AREA_IR_2GCS_EVENT));
    }
}
// 上报可见注释信息
void send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT_VIEW() {
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.update_counter++;
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras, &mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras,
           sizeof(A818_IMAGE_COMMON_PARAS_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit, &mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit,
           sizeof(IMAGE_PARAS_TRANSIT_TYPE_DEF));
    memcpy(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.AC_ins_info, &mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info,
           sizeof(AC_INS_INFO_TYPE_DEF));

    // 如果是广域或区域成像
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG || main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IRST_IMG_CCD;
    }
    // 如果是区域监视
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO;
    }
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.move_tgt_acount  = mess_From_TXCL.tg_count;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_upleft_x    = mess_From_TXCL.tgt1_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_upleft_Y    = mess_From_TXCL.tgt1_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_downright_x = mess_From_TXCL.tgt1_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt1_downright_y = mess_From_TXCL.tgt1_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_upleft_x    = mess_From_TXCL.tgt2_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_upleft_Y    = mess_From_TXCL.tgt2_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_downright_x = mess_From_TXCL.tgt2_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt2_downright_y = mess_From_TXCL.tgt2_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_upleft_x    = mess_From_TXCL.tgt3_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_upleft_Y    = mess_From_TXCL.tgt3_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_downright_x = mess_From_TXCL.tgt3_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt3_downright_y = mess_From_TXCL.tgt3_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_upleft_x    = mess_From_TXCL.tgt4_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_upleft_Y    = mess_From_TXCL.tgt4_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_downright_x = mess_From_TXCL.tgt4_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt4_downright_y = mess_From_TXCL.tgt4_downright_y;

    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_upleft_x    = mess_From_TXCL.tgt5_upleft_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_upleft_Y    = mess_From_TXCL.tgt5_upleft_Y;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_downright_x = mess_From_TXCL.tgt5_downright_x;
    mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.image_paras_transit.tgt5_downright_y = mess_From_TXCL.tgt5_downright_y;

    // 发送监视模式下的单帧注释信息
    if (mess_To_TXCL_ZSXX.tx_info[3] == 1) // 如果是单帧图像
    {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO_IMG_CCD; // 区域监视单帧可见光
        // 发送单帧的注释信息
        fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_TV_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT, sizeof(RECONNAISED_AREA_TV_2GCS_EVENT));
    }
    if (mess_To_TXCL_ZSXX.tx_info[3] == 2) // 如果是冻结帧
    {
        mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.A818_Image_common_paras.Payload_type = V_PAYLOAD_TYPE_IR_VIDEO_RRZ_CCD; // 区域监视冻结帧可见光
                                                                                                                         // 发送单帧的注释信息
        fc_Send_Message(V_TOPIC_IRRM_RECONNAISED_AREA_TV_2GCS_EVENT, (UINT8 *)&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT, sizeof(RECONNAISED_AREA_TV_2GCS_EVENT));
    }
}

// 情报数据传输状态
void send_Mess_ToFC_ID_DATA_TRANSMIT_STATE(ID_DATA_TRANS_FLAG trans_State) {
    mess_ToFC_ID_DATA_TRANSMIT_STATE.msg_publish_time.time_sys_RTC = fcSysRtcGet();
    mess_ToFC_ID_DATA_TRANSMIT_STATE.msg_publisher_ID.subdomain_ID = V_NODE_IRRM;

    // 0是1通道，可见光
    // 1是2通道，红外、H.265视频
    // 如果是非传输
    if (trans_State == V_ID_DATA_TRANS_FLAG_NO) {
        mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_NO;
        mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_NO;
    } else {
        // 如果是广域或区域成像
        if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG ||
            main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
            // 如果是可见光
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LIGHT) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_YES;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_NO;
            }
            // 如果是红外
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_INFRARED) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_NO;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_YES;
            }
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LANDI || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_IANDL || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_NA) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_YES;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_YES;
            }
        }
        // 如果是监视
        if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
            // 如果是可见光
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LIGHT) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_YES;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_YES;
            }
            // 如果是红外
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_INFRARED) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_NO;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_YES;
            }
            if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LANDI || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_IANDL || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_NA) {
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[0] = V_ID_DATA_TRANS_FLAG_YES;
                mess_ToFC_ID_DATA_TRANSMIT_STATE.ID_data_trans_flag[1] = V_ID_DATA_TRANS_FLAG_YES;
            }
        }
    }

    // 发送消息
    fc_Send_Message(V_TOPIC_IRRM_ID_DATA_TRANSMIT_STATE, (UINT8 *)&mess_ToFC_ID_DATA_TRANSMIT_STATE, sizeof(ID_DATA_TRANSMIT_STATE));
}

// 调焦消息构建
void make_Mess_To_TJ(UINT8 cmd, INT8 view_cmd) {
    mess_To_TJ.head_number++;
    mess_To_TJ.cmd = cmd;
    // 可见手动/自动调焦标志 1：手动；0：自动
    if (cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_focus_mode != 2) {
        mess_To_TJ.control_tjmode_kj = 0; // 自动
    } else {
        mess_To_TJ.control_tjmode_kj = 1; // 手动
    }
    // 红外手动/自动调焦标志 1：手动；0：自动
    if (cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_focus_mode != 2) {
        mess_To_TJ.control_tjmode_hw = 0; // 自动
    } else {
        mess_To_TJ.control_tjmode_hw = 1; // 手动
    }

    if (view_cmd == -1)
        mess_To_TJ.control_bb = cmd_From_FC.irst_cmd_VIEW_STATE; // 变倍开关，0：长焦（小视场）1：短焦（大视场）
    else
        mess_To_TJ.control_bb = view_cmd; // 准备中使用

    if (TJ_CMD_CellBIT == cmd) {
        mess_To_TJ.control_dmzj = 1; // 是否地面自检状态标志位 1：是；0：否
    } else {
        mess_To_TJ.control_dmzj = 0; // 是否地面自检状态标志位 1：是；0：否
    }
    mess_To_TJ.control_sjss = 0; // 进行实景搜索标志位；1:进行；0：完成

    if (mess_From_TG.HWJiaoZheng == 2) {
        mess_To_TJ.control_tgjzzt = 1; // 调光反馈的校正状态：0：未完成；1：已完成
    } else {
        mess_To_TJ.control_tgjzzt = 0; // 调光反馈的校正状态：0：未完成；1：已完成
    }

    mess_To_TJ.control_lzstate = mess_ToFC_IRST_OPERATIONAL_PARAS.WOW_main - 1;

    mess_To_TJ.distance   = param_Compute_Output.toTJ_distance;                          // 照相距离
    mess_To_TJ.zjwdxx     = mess_From_QNSJ.zjwdxx;                                       // 主镜温度信息，来自温控
    mess_To_TJ.cjwdxx     = mess_From_QNSJ.cjwdxx;                                       // 次镜温度信息，来自温控
    mess_To_TJ.sdtjjzl_kj = cmd_From_FC.irst_cmd_param_IR_image_paras_light.focus_value; // 手动调焦校准量-可见
    mess_To_TJ.sdtjjzl_hw = cmd_From_FC.irst_cmd_param_IR_image_paras_infra.focus_value; // 手动调焦校准量-红外
    mess_To_TJ.ylz        = mess_From_QNSJ.ylz;                                          // 压力值，来自温控
}

// 框架消息构建
void make_Mess_To_KJ(UINT8 cmd, UINT8 kf_mode) {
    mess_To_KJ.head1 = 0xEB;
    mess_To_KJ.head2 = 0x90;
    mess_To_KJ.cmd   = cmd; // 控制字

    mess_To_KJ.toKJ_pitch_start     = param_Compute_Output.toKJ_pitch_start * 10000;     // 框架俯仰指令   起始角（LSB=0.0001°）
    mess_To_KJ.toKJ_pitch_end       = param_Compute_Output.toKJ_pitch_end * 10000;       // 框架俯仰指令   结束角（LSB=0.0001°）
    mess_To_KJ.toKJ_direction_start = param_Compute_Output.toKJ_direction_start * 10000; // 框架方位指令   起始角（LSB=0.0001°）
    mess_To_KJ.toKJ_direction_end   = param_Compute_Output.toKJ_direction_end * 10000;   // 框架方位指令   结束角（LSB=0.0001°）
    mess_To_KJ.toKJ_pitch_speed     = param_Compute_Output.toKJ_pitch_speed * 100;       // 框架俯仰扫描速度指令（LSB=0.01°/s）
    mess_To_KJ.toKJ_direction_speed = param_Compute_Output.toKJ_direction_speed * 100;   // 框架方位扫描速度指令（LSB=0.01°/s）

    if (main_Control_State_Param.view_State == 0) // 大小视场状态,0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦
    {
        mess_To_KJ.kj_f = nbMess_hwInfo_FLASH.jj_Small_KJ; // 可见焦距值（LSB = 1mm）
        mess_To_KJ.hw_f = nbMess_hwInfo_FLASH.jj_Small_HW; // 红外焦距值（LSB = 1mm）
    } else {
        mess_To_KJ.kj_f = nbMess_hwInfo_FLASH.jj_Big_KJ; // 可见焦距值（LSB = 1mm）
        mess_To_KJ.hw_f = nbMess_hwInfo_FLASH.jj_Big_HW; // 红外焦距值（LSB = 1mm）
    }

    //	mess_To_KJ.pitch_tracking_speed = -255;   		//俯仰单根跟踪（速度）（LSB=0.01°/s）
    //	mess_To_KJ.direction_tracking_speed = 244;   	//方位单根跟踪（速度）（LSB=0.01°/s）

    if (V_IR_SENSOR_LIGHT == cmd_From_FC.irst_cmd_param_IR_SENSOR || V_IR_SENSOR_LANDI == cmd_From_FC.irst_cmd_param_IR_SENSOR) {
        mess_To_KJ.trackvideo = 1; // 视频跟踪模式：0x00初始化值；0x01可见跟踪；0x02红外跟踪
    } else if (V_IR_SENSOR_INFRARED == cmd_From_FC.irst_cmd_param_IR_SENSOR || V_IR_SENSOR_IANDL == cmd_From_FC.irst_cmd_param_IR_SENSOR) {
        mess_To_KJ.trackvideo = 2;
    } else {
        mess_To_KJ.trackvideo = 0;
    }

    mess_To_KJ.speed_hight = param_Compute_Output.toKJ_speed_hight * 1000; // 速高比（LSB=0.001）

    mess_To_KJ.pitch_image_motion_velocity     = param_Compute_Output.toKJ_pitch_image_motion_velocity * 1000;     // 给定快反俯仰前向像移速度（LSB=0.001°/s)
    mess_To_KJ.direction_image_motion_velocity = param_Compute_Output.toKJ_direction_image_motion_velocity * 1000; // 给定快反方位前向像移速度（LSB=0.001°/s)

    mess_To_KJ.kf_working_mode = kf_mode; // 快反工作模式

    if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) // 如果在内部拍照模式
    {
        mess_To_KJ.toKJ_pitch_start     = nbMess_jt_Photo.toKJ_pitch_start;     // 框架俯仰指令   起始角（LSB=0.0001°）
        mess_To_KJ.toKJ_pitch_end       = nbMess_jt_Photo.toKJ_pitch_start;     // 框架俯仰指令   结束角（LSB=0.0001°）
        mess_To_KJ.toKJ_direction_start = nbMess_jt_Photo.toKJ_direction_start; // 框架方位指令   起始角（LSB=0.0001°）
        mess_To_KJ.toKJ_direction_end   = nbMess_jt_Photo.toKJ_direction_start; // 框架方位指令   结束角（LSB=0.0001°）

        mess_To_KJ.toKJ_pitch_speed     = 0; // 框架俯仰扫描速度指令（LSB=0.01°/s）
        mess_To_KJ.toKJ_direction_speed = 0; // 框架方位扫描速度指令（LSB=0.01°/s）

        mess_To_KJ.pitch_tracking_speed     = 0; // 俯仰单根跟踪（速度）（LSB=0.01°/s）
        mess_To_KJ.direction_tracking_speed = 0; // 方位单根跟踪（速度）（LSB=0.01°/s）

        mess_To_KJ.speed_hight = 0; // 速高比（LSB=0.001）

        mess_To_KJ.pitch_image_motion_velocity     = 0; // 给定快反俯仰前向像移速度（LSB=0.001°/s)
        mess_To_KJ.direction_image_motion_velocity = 0; // 给定快反方位前向像移速度（LSB=0.001°/s)
    }

    // 上下电开关
    mess_To_KJ.yuliu = nbMess_jt_Photo.sf_switch;
}
// 图像处理指令消息
void make_Mess_To_TXCL_CMD(UINT8 cmd) {
    mess_To_TXCL_CMD.head1 = 0xEB;
    mess_To_TXCL_CMD.head2 = 0x90;
    mess_To_TXCL_CMD.cmd   = cmd;
    // 如果是可见/红外跟踪，给脱靶量
    if (mess_To_TXCL_CMD.cmd == TX_CMD_TRACK) {
        mess_To_TXCL_CMD.diff_pitch = (INT16)cmd_From_FC.irst_cmd_param_IR_TGT_TRACK_INFO.horizontal_deviation._pixel;
        mess_To_TXCL_CMD.diff_roll  = (INT16)cmd_From_FC.irst_cmd_param_IR_TGT_TRACK_INFO.vertical_deviation._pixel;
    } else {
        mess_To_TXCL_CMD.diff_pitch = 0;
        mess_To_TXCL_CMD.diff_roll  = 0;
    }
    // 图像传感器类型状态
    mess_To_TXCL_CMD.mode_IR_SENSOR = cmd_From_FC.irst_cmd_param_IR_SENSOR;
    // 视频带宽设置
    mess_To_TXCL_CMD.Video_BAND = cmd_From_FC.irst_cmd_param_IRST_Video_BAND;
}

// 光窗温控
void make_Mess_To_GCWK() {
    if (cmd_From_FC.irst_cmd_param_IR_Transom_paras.Transom_mist_eliminate_state == 1) // 开
        mess_To_GCWK.cmd = GCWK_CMD_OPEN;
    if (cmd_From_FC.irst_cmd_param_IR_Transom_paras.Transom_mist_eliminate_state == 2) // 开
        mess_To_GCWK.cmd = GCWK_CMD_CLOSE;
}
// 电源分系统消息构建
// 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
// 数字供电0：关 1：开
// 功率供电0：关 1：开
// 热控供电本机：0：关 1：开
// 热控供电光窗：0：关 1：开
void make_Mess_To_DY(UINT8 work_mode, UINT8 cmd_szgd, UINT8 cmd_glgd, UINT8 cmd_rkbjgd, UINT8 cmd_rkgcgd) {
    mess_To_DY.work_mode = work_mode; // 工作模式选择:0 ：并行工作模式  3：分时工作模式 5：在线升级
    // 电源开关字
    mess_To_DY.cmd_szgd   = cmd_szgd;   // 数字供电0：关 1：开
    mess_To_DY.cmd_glgd   = cmd_glgd;   // 功率供电0：关 1：开
    mess_To_DY.cmd_rkbjgd = cmd_rkbjgd; // 热控供电本机：0：关 1：开
    mess_To_DY.cmd_rkgcgd = cmd_rkgcgd; // 热控供电光窗：0：关 1：开
}

// 惯导导航数据包
// 数据使用逻辑：
// 先使用导航融合数据（周期40ms）若导航融合数据不在，取惯导数据（10ms）
// 主惯导判断：优先使用绝对导航融合工作参数，如果其离线，一次使用INV1/2/3的工作参数
// 若此时不是一个主惯导，则按3>1>2优先级确定主惯导
void make_Mess_To_PCS_DATA(UINT8 cmd) {
    // 判断逻辑从各个导航数据中取数，目前只从绝对导航中取数，todo
    mess_TO_PCS_DATA.head_number      = 0x55AA;                                                                       // 帧编号0xAA55
    mess_TO_PCS_DATA.num_of_satellite = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.num_of_satellite; // 定位卫星数目
    mess_TO_PCS_DATA.HDOP             = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.HDOP;             // 水平精度因子

    mess_TO_PCS_DATA.validity_GNSS_alt           = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_GNSS_alt;           // 有效性-卫星高度
    mess_TO_PCS_DATA.validity_position_wx        = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_position;           // 有效性-位置
    mess_TO_PCS_DATA.validity_vel_up             = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_up;             // 有效性-速度天向
    mess_TO_PCS_DATA.validity_vel_west           = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_west;           // 有效性-速度西向
    mess_TO_PCS_DATA.validity_vel_north          = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_vel_north;          // 有效性-速度北向
    mess_TO_PCS_DATA.validity_CNI_GNSS_time      = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_CNI_GNSS_time;      // 有效性-卫星时间
    mess_TO_PCS_DATA.validity_ground_speed       = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_ground_speed;       // 有效性-地速
    mess_TO_PCS_DATA.validity_ground_track_angle = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.satellite_nav_data_validity.validity_ground_track_angle; // 有效性-航迹角

    mess_TO_PCS_DATA.validity_pressure_alt      = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.air_nav_data_validity.validity_pressure_alt;      // 有效性-气压高度
    mess_TO_PCS_DATA.validity_pressure_alt_rate = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.air_nav_data_validity.validity_pressure_alt_rate; // 有效性-气压高度变化率

    mess_TO_PCS_DATA.date_year              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_year;       // 卫星时间_日历日期_日期_年
    mess_TO_PCS_DATA.date_month             = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_month;      // 卫星时间_日历日期_日期_月
    mess_TO_PCS_DATA.date_day               = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.date_gnss_calendartime.date_day;        // 卫星时间_日历日期_日期_日
    mess_TO_PCS_DATA.time_gnss_calendartime = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.time_gnss_calendartime;                 // 卫星时间_日历时间
    mess_TO_PCS_DATA.wx_latitude            = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._latitude;        // 载机卫星位置数据-纬度
    mess_TO_PCS_DATA.wx_longitude           = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_position_data._longitude;       // 载机卫星位置数据-经度
    mess_TO_PCS_DATA.ac_GNSS_alt            = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_alt;                            // 载机卫星高度-高度
    mess_TO_PCS_DATA.Vel_North_wx           = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_plat_vel.Vel_North;             // 载机卫星平台系速度-北向速度
    mess_TO_PCS_DATA.Vel_West_wx            = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_plat_vel.Vel_West;              // 载机卫星平台系速度-西向速度
    mess_TO_PCS_DATA.Vel_Up_wx              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_gnss_plat_vel.Vel_Up;                // 载机卫星平台系速度-天向速度
    mess_TO_PCS_DATA._angle_mrad            = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_ground_track_angle._angle_mrad; // 载机卫星航迹角_角度_毫弧度
    mess_TO_PCS_DATA._velocity              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.satellite_nav_data.ac_GNSS_ground_speed._velocity;         // 载机卫星地速

    mess_TO_PCS_DATA.ac_pressure_alt_rate = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.ac_pressure_alt_rate; // 载机气压高度变化率
    mess_TO_PCS_DATA.AC_pressure_alt      = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.AC_pressure_alt;      // 载机气压高度

    mess_TO_PCS_DATA.data_generated_time      = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.data_generated_time;         // 数据生成时间_时间_任务时间
    mess_TO_PCS_DATA.ac_pitch                 = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_pitch;                    // 载机俯仰角_角度_毫弧度
    mess_TO_PCS_DATA.ac_roll                  = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_roll;                     // 载机横滚角_角度_毫弧度
    mess_TO_PCS_DATA.ac_true_heading          = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_true_heading;             // 载机真航向_角度_毫弧度
    mess_TO_PCS_DATA.Vel_North_pt             = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_North;       // 载机平台系速度-速度_北向
    mess_TO_PCS_DATA.Vel_West_pt              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_West;        // 载机平台系速度-速度_西向
    mess_TO_PCS_DATA.Vel_Up_pt                = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_Up;          // 载机平台系速度-速度_天向
    mess_TO_PCS_DATA.pt_latitude              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_position_data._latitude;  // 载机位置数据_纬度
    mess_TO_PCS_DATA.pt_longitude             = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_position_data._longitude; // 载机位置数据__经度
    mess_TO_PCS_DATA.ac_height                = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_height;                   // 载机海拔高度
    mess_TO_PCS_DATA.AC_GNSS_inertial_ADS_alt = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.AC_GNSS_inertial_ADS_alt;    // 载机惯性卫星大气高度_高度

    mess_TO_PCS_DATA.validity_zt_angle              = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_flight_vector_validity.validity_pitch_angle;           // 有效性-姿态角（俯仰、横滚、真航向）
    mess_TO_PCS_DATA.validity_vel                   = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_flight_vector_validity.validity_vel_up;                // 有效性-速度（北向、西向、天向）
    mess_TO_PCS_DATA.validity_position_pt           = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_flight_vector_validity.validity_position;              // 有效性_位置
    mess_TO_PCS_DATA.validity_height                = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_flight_vector_validity.validity_height;                // 有效性_载机海拔高度
    mess_TO_PCS_DATA.validity_GNSS_inertial_ADS_alt = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_flight_vector_validity.validity_GNSS_inertial_ADS_alt; // 有效性_惯性卫星大气高度

    mess_TO_PCS_DATA.cmd = cmd;

    // 611实验用，正式时删除！！todo
    //	mess_TO_PCS_DATA.Vel_North_wx = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_North;  //载机平台系速度-速度_北向
    //	mess_TO_PCS_DATA.Vel_West_wx  = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_West;   //载机平台系速度-速度_西向
    //	mess_TO_PCS_DATA.Vel_Up_wx    = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_vel.Vel_Up;     //载机平台系速度-速度_天向

    // 校验和
    mess_TO_PCS_DATA.checksum = 0;
    int i                     = 0;
    for (i = 0; i < sizeof(Mess_TO_PCS_DATA) - 4; i++) {
        mess_TO_PCS_DATA.checksum += *(UINT8 *)((UINT8 *)(&mess_TO_PCS_DATA) + 2 + i);
    }

    mess_TO_PCS_DATA.end = 0xBB; // 消息尾 0xBB

    //	logMsg("----msg to pcs-----time: %lld------checksum: %d------\n",
    //			mess_TO_PCS_DATA.time_gnss_calendartime, mess_TO_PCS_DATA.checksum, 3,4,5,6);
}

// 惯导升级数据包
void make_Mess_To_PCS_Update() {
}

// 处理从fpga接收到的所有消息
void fpga_Mess_Process() {
    // 框架快反消息处理
    param_Compute_Input_Fromfpga.rtime_pitch_frame        = mess_From_KJ.rtime_pitch_frame * 0.0001;        // 框架实时俯仰角（LSB = 0.0001°)
    param_Compute_Input_Fromfpga.rtime_direction_frame    = mess_From_KJ.rtime_direction_frame * 0.0001;    // 框架实时方位角（LSB = 0.0001°)
    param_Compute_Input_Fromfpga.exposure_pitch_frame     = mess_From_KJ.exposure_pitch_frame * 0.0001;     // 框架曝光时刻俯仰角（LSB = 0.0001°)
    param_Compute_Input_Fromfpga.exposure_direction_frame = mess_From_KJ.exposure_direction_frame * 0.0001; // 框架曝光时刻方位角（LSB = 0.0001°)
    param_Compute_Input_Fromfpga.kfbgskfybcwz             = mess_From_KJ.kfbgskfybcwz * 0.0001;             // 快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
    param_Compute_Input_Fromfpga.kfbgskfwbcwz             = mess_From_KJ.kfbgskfwbcwz * 0.0001;             // 快反曝光时刻方位补偿位置（LSB = 0.0001°)
    nbMess_jt_Photo.kfssfybcwz                            = mess_From_KJ.kfssfybcwz;
    nbMess_jt_Photo.kfssfwbcwz                            = mess_From_KJ.kfssfwbcwz;
    nbMess_jt_Photo.kfbgskfybcwz                          = mess_From_KJ.kfbgskfybcwz;
    nbMess_jt_Photo.kfbgskfwbcwz                          = mess_From_KJ.kfbgskfwbcwz;

    nbMess_jt_Photo.rtime_pitch_frame     = mess_From_KJ.rtime_pitch_frame;     // 框架实时俯仰角（LSB = 0.0001°)
    nbMess_jt_Photo.rtime_direction_frame = mess_From_KJ.rtime_direction_frame; // 框架实时方位角（LSB = 0.0001°)

    // 调焦消息处理
    param_Compute_Input_Fromfpga.flag_view_State = mess_From_TJ.state_bb;     // 大小视场状态,0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦
    nbMess_jt_Photo.view_state                   = mess_From_TJ.state_bb;     // 大小视场状态
    nbMess_jt_Photo.jmwz_kj_real                 = mess_From_TJ.jmwz_kj_real; // 曝光时刻可见焦面位置LSB=0.001mm#
    nbMess_jt_Photo.jmwz_hw_real                 = mess_From_TJ.jmwz_hw_real; // 曝光时刻红外焦面位置LSB=0.001mm#
    main_Control_State_Param.view_State          = mess_From_TJ.state_bb;

    // PCS惯导消息处理----------------------------------------------------------------------------
    param_Compute_Input_Fromfpga.longitude    = mess_From_PCS_DATA.longitude * PI / pow(2, 31);    // 经度LSB=π/2^31---1
    param_Compute_Input_Fromfpga.latitude     = mess_From_PCS_DATA.latitude * PI / pow(2, 31);     // 纬度LSB=π/2^31---1
    param_Compute_Input_Fromfpga.altitude     = mess_From_PCS_DATA.altitude * 0.001;               // 高度 有符号数(-500m~25000m)， LSB=0.001m---1
    param_Compute_Input_Fromfpga.true_heading = mess_From_PCS_DATA.true_heading * PI / pow(2, 31); // 真航向   有符号数(-π~+π)，LSB=π/2^31rad---1
    param_Compute_Input_Fromfpga.pitch        = mess_From_PCS_DATA.pitch * PI / pow(2, 31);        // 俯仰角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    param_Compute_Input_Fromfpga.roll         = mess_From_PCS_DATA.roll * PI / pow(2, 31);         // 横滚角  有符号数 (-π~+π)，LSB=π/2^31 rad---1
    param_Compute_Input_Fromfpga.north_speed  = mess_From_PCS_DATA.north_speed * 0.001;            // 北向速度  有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    param_Compute_Input_Fromfpga.east_speed   = mess_From_PCS_DATA.east_speed * 0.001;             // 东向速度	 有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1
    param_Compute_Input_Fromfpga.ground_speed = mess_From_PCS_DATA.ground_speed * 0.001;           // 地向速度   有符号数 (-1000~+1000)m/s，LSB =0.001m/s---1

    // 球内数据消息处理----------------------------------------------------------------------------
    // 检测仪显示
    nbMess_jt_Photo.zjwdxx = mess_From_QNSJ.zjwdxx; // 主镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    nbMess_jt_Photo.cjwdxx = mess_From_QNSJ.cjwdxx; // 次镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    nbMess_jt_Photo.tem_ID = mess_From_QNSJ.tem_ID; // 温度信息ID-1-10循环发送
    nbMess_jt_Photo.temp   = mess_From_QNSJ.temp;   // 温度值，LSB=0.1℃

    // 图像处理消息处理----------------------------------------------------------------------------
    if (mess_From_TXCL.state1_trackstate == 1) // 稳定跟踪
    {
        main_Control_State_Param.track_state = V_TGT_TRACK_STATE_TRACK_ING;
    } else if (mess_From_TXCL.state1_trackstate == 0) // 未跟踪
    {
        main_Control_State_Param.track_state = V_TGT_TRACK_STATE_NOT_TRACKED;
    } else // 匹配中
    {
        main_Control_State_Param.track_state = V_TGT_TRACK_STATE_MATCH_ING;
    }

    // 调光消息处理
    nbMess_jt_Photo.hw_cold_state = mess_From_TG.HWRef_state_back;
    tcq_mess_Process();

    // 地面测试参数输入
    if (nbMess_jt_Photo.position_flag == 1) {
        param_Compute_Input_Fromfpga.longitude    = nbMess_jt_Photo.Carrier_longitude * PI / 180.0;    // 载机经度    单位°    精度0.000001°
        param_Compute_Input_Fromfpga.latitude     = nbMess_jt_Photo.Carrier_latitude * PI / 180.0;     // 载机纬度     单位°    精度0.000001°
        param_Compute_Input_Fromfpga.altitude     = nbMess_jt_Photo.Carrier_altitude;                  // 载机高度        单位米    精度1m      范围-500m-25000m
        param_Compute_Input_Fromfpga.true_heading = nbMess_jt_Photo.Carrier_true_heading * PI / 180.0; // 载机真航向    单位°    精度0.001°    范围-180°-180°
        param_Compute_Input_Fromfpga.pitch        = nbMess_jt_Photo.Carrier_pitch * PI / 180.0;        // 载机俯仰角    单位°    精度0.001°    范围-180°-180°
        param_Compute_Input_Fromfpga.roll         = nbMess_jt_Photo.Carrier_roll * PI / 180.0;         // 载机横滚角    单位°    精度0.001°    范围-180°-180°
        param_Compute_Input_Fromfpga.north_speed  = nbMess_jt_Photo.Carrier_north_speed;               // 载机北向速度    单位m/s     精度0.0001
        param_Compute_Input_Fromfpga.east_speed   = nbMess_jt_Photo.Carrier_east_speed;
        param_Compute_Input_Fromfpga.ground_speed = nbMess_jt_Photo.Carrier_ground_speed;
        // log_proc("使用地面测试POS参数\n经度: %.6f 纬度: %.6f 高度: %.2f 真航向: %.3f 俯仰角: %.3f 横滚角: %.3f 北向速度: %.4f 东向速度: %.4f 地速: %.4f\n",
        //          nbMess_jt_Photo.Carrier_longitude,
        //          nbMess_jt_Photo.Carrier_latitude,
        //          nbMess_jt_Photo.Carrier_altitude,
        //          nbMess_jt_Photo.Carrier_true_heading,
        //          nbMess_jt_Photo.Carrier_pitch,
        //          nbMess_jt_Photo.Carrier_roll,
        //          nbMess_jt_Photo.Carrier_north_speed,
        //          nbMess_jt_Photo.Carrier_east_speed,
        //          nbMess_jt_Photo.Carrier_ground_speed);
    }

    // 电源故障信息
    // 电源子系统状态字1
    nbMess_jt_Photo.state_szgd   = mess_From_DY.state_szgd;   // 数字供电0：关 1：开
    nbMess_jt_Photo.state_glgd   = mess_From_DY.state_glgd;   // 功率供电0：关 1：开
    nbMess_jt_Photo.state_rkbjgd = mess_From_DY.state_rkbjgd; // 热控供电本机：0：关 1：开
    nbMess_jt_Photo.state_rkgcgd = mess_From_DY.state_rkgcgd; // 热控供电光窗：0：关 1：开

    // 电源子系统故障字1:故障位“1”表示存在，“0”表示不存在或消失
    nbMess_jt_Photo.error1_kj   = mess_From_DY.error1_kj;   // 框架控制供电
    nbMess_jt_Photo.error1_jk   = mess_From_DY.error1_jk;   // 接口供电
    nbMess_jt_Photo.error1_txcl = mess_From_DY.error1_txcl; // 图像处理供电
    nbMess_jt_Photo.error1_pcs  = mess_From_DY.error1_pcs;  // pcs供电
    nbMess_jt_Photo.error1_sjjl = mess_From_DY.error1_sjjl; // 数据记录供电
    nbMess_jt_Photo.error1_kjqd = mess_From_DY.error1_kjqd; // 框架驱动供电
    nbMess_jt_Photo.error1_tjqd = mess_From_DY.error1_tjqd; // 调焦驱动供电
    nbMess_jt_Photo.error1_bbqd = mess_From_DY.error1_bbqd; // 变倍驱动供电

    // 电源子系统故障字2:故障位“1”表示存在，“0”表示不存在或消失
    nbMess_jt_Photo.error2_gsjqd = mess_From_DY.error2_gsjqd; // 高速机驱动供电
    nbMess_jt_Photo.error2_rkbj  = mess_From_DY.error2_rkbj;  // 热控供电本机
    nbMess_jt_Photo.error2_rkgc  = mess_From_DY.error2_rkgc;  // 热控供电光窗
    nbMess_jt_Photo.error2_tem   = mess_From_DY.error2_tem;   // 温度传感器

    nbMess_jt_Photo.power_tem = mess_From_DY.power_tem; // 电源子系统温度LSB = 1
}

// 向记录仪发
void make_Mess_To_JLY(UINT8 cmd) {

    mess_To_JLY.head = 0x90EB; // 0xEB90
    mess_To_JLY.cmd  = cmd;    // 指令

    mess_To_JLY.param_channel1 = 1; // 通道1
    mess_To_JLY.param_channel2 = 1; // 通道2
    mess_To_JLY.param_channel3 = 1; // 通道3
    mess_To_JLY.param_channel4 = 1; // 通道4
}
// 向球内数据发--可见探测器
void make_Mess_To_QNSJ_KJTCQ(UINT8 cmd, UINT8 data1, UINT8 data2) {
    mess_To_QNSJ.mess_To_TCQ_KJ.KJCmd      = cmd;
    mess_To_QNSJ.mess_To_TCQ_KJ.KJSendDat1 = data1;
    mess_To_QNSJ.mess_To_TCQ_KJ.KJSendDat2 = data2;
}

// 向球内数据发--红外探测器
void make_Mess_To_QNSJ_HWTCQ(UINT8 cmd, UINT8 data1, UINT8 data2) {
    mess_To_QNSJ.mess_To_TCQ_HW.HWCmd      = cmd;
    mess_To_QNSJ.mess_To_TCQ_HW.HWSendDat1 = data1;
    mess_To_QNSJ.mess_To_TCQ_HW.HWSendDat2 = data2;
}

// 向球内数据发--温控探测器
void make_Mess_To_QNSJ_WK(UINT8 cmd) {
    mess_To_QNSJ.mess_To_QNWK.head     = 0x7E7E; // 0x7E7E
    mess_To_QNSJ.mess_To_QNWK.cmd      = cmd;    // 指令
    mess_To_QNSJ.mess_To_QNWK.cmd_mode = 1;      // 手动/自动温控   0：自动 1：手动
}

// 向FPGA发
void make_Mess_To_FPGA(UINT8 cmd, UINT8 irst_form_mode, UINT8 zsxx_valid) {
    mess_To_FPGA.cmd            = cmd;
    mess_To_FPGA.irst_form_mode = irst_form_mode;

    mess_To_FPGA.zsxx_valid = zsxx_valid;
    mess_To_FPGA.time_kj    = mess_From_TG.KJExpTime_back * 3000; // 可见曝光时间LSB=0.1ms
    mess_To_FPGA.time_hw    = mess_From_TG.HWExpTime_back * 3000; // 红外曝光时间LSB=0.1ms

    mess_To_FPGA.frames_Num    = param_Compute_Output.frames_Num;                   // 条带帧数
    mess_To_FPGA.time_speed    = param_Compute_Output.toFPGA_time_speed * 30000;    // 速度信号时间LSB=1ms
    mess_To_FPGA.time_location = param_Compute_Output.toFPGA_time_location * 30000; // 位置信号时间LSB=1ms

    // mess_To_FPGA.frames_Num    = 44;         // 条带张数
    // mess_To_FPGA.time_speed    = 94044112;   // 速度信号时间LSB=1ms
    // mess_To_FPGA.time_location = 3758561792; // 位置信号时间LSB=1ms
}

// 向调光发（写结构体）
void make_Mess_To_TG(UINT8 cmd, UINT8 jg_mode) {
    mess_To_TG.Control_Cmd = cmd;     // 命令字
    mess_To_TG.JG_Mode     = jg_mode; // 检光模式---工作模式

    if (cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_dim_mode != 2) // 不是手动
    {
        mess_To_TG.KJTG_Mode = 0; // 可见调光模式，自动
    } else {
        mess_To_TG.KJTG_Mode = 1; // 可见调光模式，手动
    }

    mess_To_TG.TargetType = cmd_From_FC.irst_cmd_param_environmnet_type; // 对陆对海
    if (param_Compute_Output.toKJ_direction_start > 0)                   // 左倾
    {
        mess_To_TG.XJ_SlopeMode_Rec = XJ_SLOPEMODE_LEFT; // 左倾斜方式
    } else {
        mess_To_TG.XJ_SlopeMode_Rec = XJ_SLOPEMODE_RIGHT; // 右倾斜方式
    }

    mess_To_TG.KJsdtg_cnt = cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_value; // 可见手动调光值

    // 可见光增强状态
    mess_To_TG.KJImg_EnHance = cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_enhance_mode;

    // 红外增强
    mess_To_TG.HWImg_EnHance = cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_enhance_mode;
    // 红外黑白热
    if (cmd_From_FC.irst_cmd_param_IR_image_paras_infra.video_polar == V_VIDEO_POLAR_BHOT)
        mess_To_TG.HWImg_Ply = 1;
    else
        mess_To_TG.HWImg_Ply = 0;

    mess_To_TG.Camera_FOV_Switch = cmd_From_FC.irst_cmd_VIEW_STATE; // 调光大小视场

    // 可见光去雾状态
    mess_To_TG.KJImg_ReMoveMist = cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_mist_eliminate_state;
    // 红外探测器制冷开关,只在收藏发送
    if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
        mess_To_TG.HWTCQ_Ref_Switch = nbMess_jt_Photo.zl_Switch;
    }
}

// 图像处理注释信息消息
void make_Mess_To_TXCL_ZSXX() {
    std::lock_guard<std::mutex> lock(mutex_shm);
    // 任务信息
    // 名  称:任务代号
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_MissionCode = temp_mess_FromFc_MISSION_EVENT_REPORT.ms_event_update_counter;
    // 名  称:图像信息包头
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.message_header = 0x7E7E;
    // 名  称:飞机号
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_AC_No = 0x22;
    // 名  称:飞机批号
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_AC_BatchNo = 0;
    // 名  称:飞行器类型
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_AC_TYPE = 0X4B; // 侦察型;
    // 名  称:定位精度
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.location_presise = 1;
    // 名  称:极化类型
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.IR_pole_type = mess_From_TG.HWImg_Ply_back;
    // 名  称:扫描方向标志
    // 说  明:顺航向从左到右为正扫，反之为反扫。光电专用
    if (cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE == V_IR_WIDE_IMAGE_MODE_AZ_PRIO) // 如果是方位
    {
        mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.scan_direct_tag = 0; // 方位从左向右扫
    } else                                                                     // 如果是距离优先
    {
        if (cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION == V_IR_WIDE_IMAGE_DIRECTION_LEFT)
            mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.scan_direct_tag = 1; // 左倾，从右向左扫
        else
            mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.scan_direct_tag = 0; // 右倾，从左向右扫
    }
    // 名  称:图像位深，8位
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_ImageBitDepth = 1;
    // 名  称:载荷厂家
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.Payload_Factory = 2;
    // 名  称:载荷类型，需要图像处理填写
    //	mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.Payload_type:4;
    // 名  称:传输方式_3bit
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.transitmit_type = 0;
    // 名  称:任务段号，不知道来源
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_MissionStageNo = 0;
    // 名  称:设备工作模式
    // 说  明:共用，对于侦察雷达表示雷达成像模式；对于综合光电表示相机工作模式。
    // 单  位:
    // 起始字:3
    // 起始位:16
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG) {
        mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 1;
    } else if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 5;
    } else if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 2;
        if (cmd_From_FC.irst_cmd_param_area_image_paras_validity[0] && cmd_From_FC.irst_cmd_param_area_image_paras_photoing[0]) {
            if (cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_AREA_LENGTH == 4)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 2;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_AREA_LENGTH == 10)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 3;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_AREA_LENGTH == 20)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 4;
        }
        if (cmd_From_FC.irst_cmd_param_area_image_paras_validity[1] && cmd_From_FC.irst_cmd_param_area_image_paras_photoing[1]) {
            if (cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_AREA_LENGTH == 4)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 2;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_AREA_LENGTH == 10)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 3;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_AREA_LENGTH == 20)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 4;
        }
        if (cmd_From_FC.irst_cmd_param_area_image_paras_validity[2] && cmd_From_FC.irst_cmd_param_area_image_paras_photoing[2]) {
            if (cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_AREA_LENGTH == 4)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 2;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_AREA_LENGTH == 10)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 3;
            if (cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_AREA_LENGTH == 20)
                mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.device_work_mode = 4;
        }
    }
    // 名  称:图像压缩比，待定
    mess_To_TXCL_ZSXX.to_Txcl_A818_Image_common_paras.A818_ImageCompressionRatio = 0;

    // 图像参数_下传
    // 名  称:图像帧序号
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMG_ID = main_Control_State_Param.totalNo;
    // 名  称:条带号
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_LineNo = main_Control_State_Param.lineNo;
    // 名  称:周期号
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_CycleNo = main_Control_State_Param.cycleNo;
    // 名  称:条带内序号
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_LineNo = main_Control_State_Param.in_lineNo;
    // 名  称:收容宽度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_WideCover = param_Compute_Output.wideCover;
    // 相机视场
    if (main_Control_State_Param.view_State == 0) // 如果是小视场
    {
        // 名  称:相机纵向视场
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_vertical = 67;
        // 名  称:相机横向视场
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_transverse = 54;
        // 名  称:相机焦距——可见//可见小视场-长焦
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_FocalLength = nbMess_hwInfo_FLASH.jj_Small_KJ;
        // 红外小视场-长焦
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_x = nbMess_hwInfo_FLASH.jj_Small_HW;
    } else {
        // 名  称:相机纵向视场
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_vertical = 337;
        // 名  称:相机横向视场
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_transverse = 269;
        // 名  称:相机焦距——可见//可见大视场-短焦
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_FocalLength = nbMess_hwInfo_FLASH.jj_Big_KJ;
        // 红外大视场-短焦
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_x = nbMess_hwInfo_FLASH.jj_Big_HW;
    }
    // 名  称:视场中心俯仰角
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_center_el = param_Compute_Output.view_fov_center_elevation * 100;
    // 名  称:视场中心方位角
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fov_center_azimuth = param_Compute_Output.view_fov_center_azimuth * 100;
    // 名  称:傍向重叠率
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_Beside_tgt_cover = param_Compute_Output.A818_Beside_tgt_cover;
    // 名  称:航向重叠率
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_Couse_tgt_cover = param_Compute_Output.A818_Couse_tgt_cover;
    // 名  称:地面摄影分辨率
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_GROUND_RESOLUTION = param_Compute_Output.A818_GROUND_RESOLUTION * 100;
    // 名  称:像元分辨率
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_CUR_RESOLUTION = param_Compute_Output.A818_CUR_RESOLUTION * 100;
    // 名  称:图像中心高度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_ImageCenterHeight = param_Compute_Output.A818_ImageCenterHeight;
    // 名  称:图像中心经度
    // todo: 下面的等号右面的单位是度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.image_center_longitude._longitude = param_Compute_Output.image_center_longitude * deg_to_mrad * 100000;
    // 名  称:图像中心纬度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.image_center_latitude._latitude = param_Compute_Output.image_center_latitude * deg_to_mrad * 100000;
    // 名  称:图像左上角经度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.upleft_longitude._longitude = param_Compute_Output.imaging_left_up_longitude * deg_to_mrad * 100000;
    // 名  称:图像左上角纬度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.upleft_latitude._latitude = param_Compute_Output.imaging_left_up_latitude * deg_to_mrad * 100000;
    // 名  称:图像左下角经度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.downleft_longitude._longitude = param_Compute_Output.imaging_left_down_longitude * deg_to_mrad * 100000;
    // 名  称:图像左下角纬度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.downleft_latitude._latitude = param_Compute_Output.imaging_left_down_latitude * deg_to_mrad * 100000;
    // 名  称:图像右上角经度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.upright_longitude._longitude = param_Compute_Output.imaging_right_up_longitude * deg_to_mrad * 100000;
    // 名  称:图像右上角纬度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.upright_latitude._latitude = param_Compute_Output.imaging_right_up_latitude * deg_to_mrad * 100000;
    // 名  称:图像右下角经度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.downright_longitude._longitude = param_Compute_Output.imaging_right_down_longitude * deg_to_mrad * 100000;
    // 名  称:图像右下角纬度
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.downright_latitude._latitude = param_Compute_Output.imaging_right_down_latitude * deg_to_mrad * 100000;
    // 名  称:照相次数
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_TakeTimes = main_Control_State_Param.takeTimes;
    // 名  称:融合目标编号
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.fused_tgt_ID = 0;
    // 名  称:曝光时间-可见
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_ExposureTime = mess_From_TG.KJExpTime_back * 100;
    // 红外曝光时间
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.tgt1_upleft_Y = mess_From_TG.HWExpTime_back * 100;

    // 说  明:用于显示区域成像/区域监视的中心点位置（按照统一的经纬度格式定义），光电独有

    // 区域监视
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
        // 名  称:区域中心位置X
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_X._longitude = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude;
        // 名  称:区域中心位置Y
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_Y._latitude = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude;
    }
    // 区域成像
    else if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
        UINT8 i = 0;
        if (cmd_From_FC.irst_cmd_param_area_image_paras_photoing[0] == 1)
            i = 0;
        if (cmd_From_FC.irst_cmd_param_area_image_paras_photoing[1] == 1)
            i = 1;
        if (cmd_From_FC.irst_cmd_param_area_image_paras_photoing[2] == 1)
            i = 2;
        // 名  称:区域中心位置X
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_X._longitude = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude;
        // 名  称:区域中心位置Y
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_Y._latitude = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude;
    }
    // 广域成像
    else {
        // 名  称:区域中心位置X
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_X._longitude = 0;
        // 名  称:区域中心位置Y
        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.REGION_CENTER_Y._latitude = 0;
    }

    // 后面定义自己需要的注释信息内容(相机内部待补充)
    memcpy(&mess_To_TXCL_ZSXX.fpga_info, &mess_From_FPGA.fpga_422ERR.fpag_422Err, 2);
    memcpy(mess_To_TXCL_ZSXX.kj_info, (void *)(&mess_From_KJ) + 3, 44);
    memcpy(mess_To_TXCL_ZSXX.tj_info, (void *)(&mess_From_TJ) + 6, 20);
    memcpy(mess_To_TXCL_ZSXX.tg_info, (void *)(&mess_From_TG) + 2, 30);
    // 球内数据8字节
    mess_To_TXCL_ZSXX.zjwdxx = mess_From_QNSJ.zjwdxx; // 主镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    mess_To_TXCL_ZSXX.cjwdxx = mess_From_QNSJ.cjwdxx; // 次镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦
    mess_To_TXCL_ZSXX.error1 = mess_From_QNSJ.error1; // 温控传感器故障字1:Bit0-bit7：代表8个区域传感器故障
    mess_To_TXCL_ZSXX.error2 = mess_From_QNSJ.error2; // 温控传感器故障字2:Bit0-bit5：代表6个区域传感器故障
    mess_To_TXCL_ZSXX.ylz    = mess_From_QNSJ.ylz;    // 压力值，来自温控

    // 主控需要保存的注释信息
    mess_To_TXCL_ZSXX.distance             = mess_To_TJ.distance;             // 照相距离
    mess_To_TXCL_ZSXX.toKJ_pitch_start     = mess_To_KJ.toKJ_pitch_start;     // 框架俯仰指令   起始角（LSB=0.0001°）
    mess_To_TXCL_ZSXX.toKJ_pitch_end       = mess_To_KJ.toKJ_pitch_end;       // 框架俯仰指令   结束角（LSB=0.0001°）
    mess_To_TXCL_ZSXX.toKJ_direction_start = mess_To_KJ.toKJ_direction_start; // 框架方位指令   起始角（LSB=0.0001°）
    mess_To_TXCL_ZSXX.toKJ_direction_end   = mess_To_KJ.toKJ_direction_end;   // 框架方位指令   结束角（LSB=0.0001°）

    mess_To_TXCL_ZSXX.toKJ_pitch_speed     = mess_To_KJ.toKJ_pitch_speed;     // 框架俯仰扫描速度指令（LSB=0.01°/s）
    mess_To_TXCL_ZSXX.toKJ_direction_speed = mess_To_KJ.toKJ_direction_speed; // 框架方位扫描速度指令（LSB=0.01°/s）

    mess_To_TXCL_ZSXX.pitch_image_motion_velocity     = mess_To_KJ.pitch_image_motion_velocity;     // 给定快反俯仰前向像移速度（LSB=0.001°/s)
    mess_To_TXCL_ZSXX.direction_image_motion_velocity = mess_To_KJ.direction_image_motion_velocity; // 给定快反方位前向像移速度（LSB=0.001°/s)
    // 图像处理4字节,最后一个是保留
    memcpy(&mess_To_TXCL_ZSXX.tx_info[0], (void *)(&mess_From_TXCL) + 3, 1);
    memcpy(&mess_To_TXCL_ZSXX.tx_info[1], (void *)(&mess_From_TXCL) + 4, 1);
    memcpy(&mess_To_TXCL_ZSXX.tx_info[2], (void *)(&mess_From_TXCL) + 46, 1);

    // 每秒1帧标记，如果在监视模式下，并且如果模24等于1，说明是每秒的第一帧
    if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI && main_Control_State_Param.cycleNo % 24 == 1) {
        mess_To_TXCL_ZSXX.tx_info[3] = 1;     // 每秒1帧标记
        if (cmd_From_FC.irst_cmd_FROZEN == 1) // 如果收到冻结指令
        {
            mess_To_TXCL_ZSXX.tx_info[3] = 2; // 冻结标记
            cmd_From_FC.irst_cmd_FROZEN  = 0; // 清除冻结指令
        }
    } else {
        mess_To_TXCL_ZSXX.tx_info[3] = 0; // 正常帧标记
    }
}

// 图像处理注释信息消息-时间信息、pos信息获取
void make_Mess_To_TXCL_ZSXX_Time_Pos() {
    std::lock_guard<std::mutex> lock(mutex_shm);
    // 系统时间设置-----------------------------------------------
    const UINT64 NS_PER_MS     = 1000000ULL;
    const UINT64 NS_PER_SECOND = 1000000000ULL;
    const UINT64 NS_PER_MINUTE = 60ULL * NS_PER_SECOND;
    const UINT64 NS_PER_HOUR   = 3600ULL * NS_PER_SECOND;
    UINT64       ns            = temp_mess_FromFc_SYM_TIME_REPORT.time_calendartime;
    UINT32       h             = ns / NS_PER_HOUR;
    ns %= NS_PER_HOUR;
    UINT32 m = ns / NS_PER_MINUTE;
    ns %= NS_PER_MINUTE;
    UINT32 s  = ns / NS_PER_SECOND;
    UINT32 ms = (ns % NS_PER_SECOND) / NS_PER_MS;
    // 名  称:图像时间_时
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_time_hour = h;
    // 名  称:图像时间_分
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_time_minute = m;
    // 名  称:图像时间_秒
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_time_second = s;
    // 名  称:图像时间_毫秒
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_time_ms = ms;
    // 名  称:图像时间_日期_日
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_date_day = temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_day;
    // 名  称:图像时间_日期_月
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_date_mounth = temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_month;
    // 名  称:图像时间_日期_年
    mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMAGE_date_year = temp_mess_FromFc_SYM_TIME_REPORT.date_calendartime.date_year - 2000;

    // 名  称:飞机惯导信息
    // 名  称:当前使用惯导
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.A818_INS_NOW = 0x03;
    // 名  称:惯导组合状态
    UINT16 value = 0;
    value        = (value & 0xF000) | // 保留bit12-15
            ((temp_mess_FromFc_INS3_OPERATIONAL_PARAS.Integrated_NAV_Work_State_ & 0x0F) << 8) |
            ((temp_mess_FromFc_INS2_OPERATIONAL_PARAS.Integrated_NAV_Work_State_ & 0x0F) << 4) |
            (temp_mess_FromFc_INS1_OPERATIONAL_PARAS.Integrated_NAV_Work_State_ & 0x0F);
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.A818_INS_GroupStatus = value;

    // // 名  称:成像开始时刻载机数据
    // // 名  称:载机位置数据
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_position_data._latitude  = mess_From_PCS_DATA.latitude * PI / pow(2, 31) * 100000;
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_position_data._longitude = mess_From_PCS_DATA.longitude * PI / pow(2, 31) * 100000;
    // // 名  称:载机海拔高度
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_height._altitude = mess_From_PCS_DATA.altitude * 1000;
    // // 名  称:载机真航向
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_true_heading._angle_mrad = mess_From_PCS_DATA.true_heading * PI / pow(2, 31) * 1000;
    // // 名  称:载机俯仰角
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_pitch._angle_mrad = mess_From_PCS_DATA.pitch * PI / pow(2, 31) * 1000;
    // // 名  称:载机横滚角
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_roll._angle_mrad = mess_From_PCS_DATA.roll * PI / pow(2, 31) * 1000;
    // // 名  称:载机偏航角
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_CDI_angle._angle_mrad = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_ground_track_angle._angle_mrad;
    // // 名  称:载机偏流角
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_sl_angle._angle_mrad = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_sl_angle._angle_mrad;
    // // 名  称:载机地速
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_ground_speed._velocity = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_ground_speed._velocity;
    // // 名  称:载机真空速
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_true_airspeed._velocity = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.ac_true_airspeed._velocity;
    // // 名  称:指示空速
    // //	mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_indicate_airspeed._velocity = ;
    // // 名  称:速度_东向
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_East._velocity = mess_From_PCS_DATA.east_speed * 10;
    // // 名  称:速度_北向
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_North._velocity = mess_From_PCS_DATA.north_speed * 10;
    // // 名  称:速度_天向
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_Up._velocity = -mess_From_PCS_DATA.ground_speed * 10;
    // // 名  称:飞机东向加速度_
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_East._acceleration = -temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_West._acceleration;
    // // 名  称:飞机北向加速度_
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_North._acceleration = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_North._acceleration;
    // // 名  称:飞机天向加速度_
    // mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_Up._acceleration = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_Up._acceleration;

    // Note: 等号左右的单位不太对
    // 名  称:成像开始时刻载机数据
    // 名  称:载机位置数据
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_position_data._latitude  = mess_From_PCS_DATA.latitude * PI / pow(2, 31) * 1e3 * 100000;
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_position_data._longitude = mess_From_PCS_DATA.longitude * PI / pow(2, 31) * 1e3 * 100000;
    // 名  称:载机海拔高度
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_height._altitude = mess_From_PCS_DATA.altitude * 1000 * 100;
    // 名  称:载机真航向
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_true_heading._angle_mrad = mess_From_PCS_DATA.true_heading * PI / pow(2, 31) * 1e3 * 1000;
    // 名  称:载机俯仰角
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_pitch._angle_mrad = mess_From_PCS_DATA.pitch * PI / pow(2, 31) * 1e3 * 1000;
    // 名  称:载机横滚角
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_roll._angle_mrad = mess_From_PCS_DATA.roll * PI / pow(2, 31) * 1e3 * 1000;
    // 名  称:载机偏航角
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_CDI_angle._angle_mrad = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_ground_track_angle._angle_mrad;
    // 名  称:载机偏流角
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_sl_angle._angle_mrad = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_sl_angle._angle_mrad;
    // 名  称:载机地速
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_ground_speed._velocity = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_ground_speed._velocity;
    // 名  称:载机真空速
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_true_airspeed._velocity = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.air_nav_data.ac_true_airspeed._velocity;
    // 名  称:指示空速
    //	mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_indicate_airspeed._velocity = ;
    // 名  称:速度_东向
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_East._velocity = mess_From_PCS_DATA.east_speed * 10;
    // 名  称:速度_北向
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_North._velocity = mess_From_PCS_DATA.north_speed * 10;
    // 名  称:速度_天向
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.Vel_Up._velocity = -1 * mess_From_PCS_DATA.ground_speed * 10;
    // 名  称:飞机东向加速度_
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_East._acceleration = -1 * temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_West._acceleration;
    // 名  称:飞机北向加速度_
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_North._acceleration = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_North._acceleration;
    // 名  称:飞机天向加速度_
    mess_To_TXCL_ZSXX.to_Txcl_AC_ins_info.AC_data_start.ac_accel_Up._acceleration = temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_plat_accel.Accel_Up._acceleration;

    // 载荷惯导时间
    mess_To_TXCL_ZSXX.pos_time_year   = mess_From_PCS_DATA.time_year;   // 年
    mess_To_TXCL_ZSXX.pos_time_mounth = mess_From_PCS_DATA.time_mounth; // 月
    mess_To_TXCL_ZSXX.pos_time_day    = mess_From_PCS_DATA.time_day;    // 日
    mess_To_TXCL_ZSXX.pos_time_hour   = mess_From_PCS_DATA.time_hour;   // 时
    mess_To_TXCL_ZSXX.pos_time_min    = mess_From_PCS_DATA.time_min;    // 分
    mess_To_TXCL_ZSXX.pos_time_s      = mess_From_PCS_DATA.time_s;      // 秒
    mess_To_TXCL_ZSXX.pos_time_ms     = mess_From_PCS_DATA.time_ms;     // 毫秒
}

// FC系统RTC时间获取
// Note: 修改为系统时间
UINT64 fcSysRtcGet() {
    // TSS_ADAPTOR_RETURN_CODE_TYPE iRet       = 0;
    // UINT64                       ulLocalRtc = 0;
    // TSS_ADAPTOR_PARAM_TYPE       tTssParam  = {0};
    // tTssParam.uiQueryCmd                    = V_TIMESERV_GET_SYS_RTC;
    // tTssParam.uiHandle                      = V_NET_FC;
    // tTssParam.pvOutPara                     = (void *)&ulLocalRtc;

    // TSS_Adaptor_Get_Time_Parameter(V_TSS_TIMESERV_MODULE, &tTssParam, &iRet);

    // return ulLocalRtc;
    return getSysRTC();
}

// fpga测试函数
void test_forFpga() {
    int i;
    //		make_Mess_To_KJ(KJ_CMD_CHECK,KJ_CMD_KF_MODE_STOP);
    //		make_Mess_To_GCWK(0xAA);
    //		make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_MODEL2);
    //		make_Mess_To_TXCL_ZSXX();
    //		make_Mess_To_DY(0,1,1,1,1);//电源分系统消息构建1
    //				make_Mess_To_GCWK(*(UINT8*)((void*)&mess_From_GCWK + 2));
    //				printf("-----------------KJ------------------------------------------------------------\n");
    //				printf("Mess_From_KJ:");
    //				for(i = 0; i < 52; i++)
    //				{
    //					if(i%10 == 0) printf("\n");
    //					printf("0x%X ",*(UINT8*)((void*)&mess_From_KJ + i));
    //
    //				}
    //				printf("\n\n");
    //
    //				printf("Mess_To_KJ:");
    //				for(i = 0; i < 40; i++)
    //				{
    //					if(i%10 == 0) printf("\n");
    //					printf("0x%X ",*(UINT8*)((void*)&mess_To_KJ + i));
    //
    //				}
    //				printf("\n\n");
    //						printf("-----------------QNSJ------------------------------------------------------------\n");
    //						printf("mess_From_QNSJ:");
    //						for(i = 0; i < 56; i++)
    //						{
    //							if(i%10 == 0) printf("\n");
    //							printf("0x%X ",*(UINT8*)((void*)&mess_From_QNSJ + i));
    //
    //						}
    //						printf("\n\n");

    printf("-----------------TXCL_MESS------------------------------------------------------------\n");
    printf("Mess_From_TXCL:");
    for (i = 0; i < sizeof(Mess_From_TXCL); i++) {
        if (i % 10 == 0)
            printf("\n");
        printf("0x%X ", *(UINT8 *)((void *)&mess_From_TXCL + i));
    }
    printf("\n\n");

    //
    //		printf("-----------------RECV_MESS------------------------------------------------------------\n");
    //		printf("MESS_From_QNSJ:");
    //		for(i = 0; i < sizeof(MESS_From_QNSJ); i++)
    //		{
    //			if(i%10 == 0) printf("\n");
    //			printf("0x%X ",*(UINT8*)((void*)&mess_From_QNSJ + i));
    //
    //		}
    //		printf("\n\n");

    //						printf("Mess_TO_PCS_DATA:%d\n",sizeof(Mess_TO_PCS_DATA));
    //		printf("-----------------GCWK------------------------------------------------------------\n");
    //		printf("mess_From_GCWK:");
    //		for(i = 0; i < 8; i++)
    //		{
    //			if(i%10 == 0) printf("\n");
    //			printf("0x%X ",*(UINT8*)((void*)&mess_From_GCWK + i));
    //		}
    //		printf("\n\n");
}
// 注释信息测试
void test_forTXCL_ZZXX() {
    // 注释信息用--------------------------------------------------------------------------
    // 名  称:收容宽度
    // 说  明:单位：米。   对于光电：广域模式和区域成像模式下垂直航向的实际宽度，区域监视模式下为一帧图像的实际宽度。
    param_Compute_Output.wideCover = 121.14;
    // 名  称:视场中心_俯仰    机体系   //LSB  :0.001
    param_Compute_Output.view_fov_center_elevation = 15.56;
    // 名  称:视场中心_方位    机体系 //LSB  :0.001
    param_Compute_Output.view_fov_center_azimuth = 0.2211;
    // 名  称:像元分辨率//LSB  :0.01
    param_Compute_Output.A818_CUR_RESOLUTION = 685.55;
    // 名  称:傍向重叠率	00~99
    param_Compute_Output.A818_Beside_tgt_cover = 0.1;
    // 名  称:航向重叠率 00~99
    param_Compute_Output.A818_Couse_tgt_cover = 0.06;
    // 名  称:图像中心高度
    param_Compute_Output.A818_ImageCenterHeight = 5000;
    // 名  称:地面摄影分辨率//LSB  :0.01
    // 说  明:共用，00.00~99.99，单位：米。像面投影中心位置地面摄影分辨率。像元投影到地面后的分辨率。精度与飞机姿态参数精度、相对高度参数精度等相关
    param_Compute_Output.A818_GROUND_RESOLUTION = 1215.4;
    // 名  称:图像中心经度//LSB  :0.00001
    param_Compute_Output.image_center_longitude = 546;
    // 名  称:图像中心纬度//LSB  :0.00001
    param_Compute_Output.image_center_latitude = 25.5;
    // 名  称:图像左上角经度//LSB  :0.00001
    param_Compute_Output.imaging_left_up_longitude = 235.6;
    // 名  称:图像左上角纬度//LSB  :0.00001
    param_Compute_Output.imaging_left_up_latitude = 123.1;
    // 名  称:图像左下角经度//LSB  :0.00001
    param_Compute_Output.imaging_left_down_longitude = 132.1;
    // 名  称:图像左下角纬度//LSB  :0.00001
    param_Compute_Output.imaging_left_down_latitude = 2123.66;
    // 名  称:图像右上角经度//LSB  :0.00001
    param_Compute_Output.imaging_right_up_longitude = 4564.555;
    // 名  称:图像右上角纬度//LSB  :0.00001
    param_Compute_Output.imaging_right_up_latitude = 84.5;
    // 名  称:图像右下角经度//LSB  :0.00001
    param_Compute_Output.imaging_right_down_longitude = 22.54;
    // 名  称:图像右下角纬度//LSB  :0.00001
    param_Compute_Output.imaging_right_down_latitude = 54.5;
}
