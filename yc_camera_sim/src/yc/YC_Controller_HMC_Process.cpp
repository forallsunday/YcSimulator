/*
 * YC_Controller_HMC_Process.c
 *
 *  Created on: 2025年9月8日
 *      Author: wangx
 */

#include "YC_Controller_HMC_Process.h"
// #include "String.h"
#include "YC_Controller_globalVal_Ext.h"
#include <cstring>
#include <math.h>
// #include "semYc.h"
#include "YC_Controller_Main_Process.h"

HMC_IRST_NB nb_HMC_DATA;
// 内部HMC数据初始化，主要是编号
void nb_HMC_DATA_INIT() {
    int i = 0;

    memset(&nb_HMC_DATA, 0, sizeof(HMC_IRST_NB));

    for (i = 0; i < TOTAL_HMC_NUM; i++) {
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_LCN   = 0;     // LCN码，暂定为全0
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_HSC   = i + 1; // HSC码，从1-50
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_HASC  = 10;    // HASC码，上电10，周期30，启动40，维护50
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_State = 0;     // HMC状态，发生1、消失0
    }

    // 通信功能异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[0].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[0].HMC_HSC = 1;
    // 参数超限
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[1].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[1].HMC_HSC = 2;
    // 伺服功能异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[2].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[2].HMC_HSC = 3;
    // 检焦功能异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[3].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[3].HMC_HSC = 4;
    // 检调光功能异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[4].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[4].HMC_HSC = 5;
    // 可见光图像通路异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[5].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[5].HMC_HSC = 6;
    // 红外图像通路异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[6].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[6].HMC_HSC = 7;
    // 隐身光窗去雾异常（实际是光窗RS422异常）
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[7].HMC_LCN = 398000300;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[7].HMC_HSC = 8;
    // 光机组件控制器通信接口故障
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[8].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[8].HMC_HSC = 1001;
    // POS通信故障
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[9].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[9].HMC_HSC = 1002;
    // 光机组件-输入俯仰角参数超限
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[10].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[10].HMC_HSC = 1003;
    // 光机组件-速高比超限
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[11].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[11].HMC_HSC = 1004;
    // 光机组件-输入速度参数超限（速度>100km/h）
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[12].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[12].HMC_HSC = 1005;
    // 光机组件-输入高度参数超限（高度>20000m,<1000m）
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[13].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[13].HMC_HSC = 1006;
    // 光机组件-输入偏流角参数超限
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[14].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[14].HMC_HSC = 1007;
    // 光机组件-输入横滚角参数超限
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[15].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[15].HMC_HSC = 1008;
    // 框架控制分系统RS422
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[16].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[16].HMC_HSC = 1009;
    // 外框架陀螺异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[17].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[17].HMC_HSC = 1010;
    // 外框架编码器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[18].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[18].HMC_HSC = 1011;
    // 外框架位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[19].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[19].HMC_HSC = 1012;
    // 外框架速度超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[20].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[20].HMC_HSC = 1013;
    // 内框架陀螺异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[21].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[21].HMC_HSC = 1014;
    // 内框架编码器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[22].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[22].HMC_HSC = 1015;
    // 内框架位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[23].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[23].HMC_HSC = 1016;
    // 内框架速度超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[24].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[24].HMC_HSC = 1017;
    // 框架位置/速度信号异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[25].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[25].HMC_HSC = 1018;
    // 框架接收快反启动信号异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[26].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[26].HMC_HSC = 1019;
    // 补偿镜RS422
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[27].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[27].HMC_HSC = 1020;
    // 快反方位AD采集异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[28].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[28].HMC_HSC = 1021;
    // 快反俯仰AD异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[29].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[29].HMC_HSC = 1022;
    // 快反方位电机状态异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[30].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[30].HMC_HSC = 1023;
    // 快反俯仰电机状态异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[31].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[31].HMC_HSC = 1024;
    // 快反方位位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[32].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[32].HMC_HSC = 1025;
    // 快反俯仰位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[33].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[33].HMC_HSC = 1026;
    // 检调焦RS422通信故障
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[34].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[34].HMC_HSC = 1027;
    // 可见调焦编码器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[35].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[35].HMC_HSC = 1028;
    // 红外调焦编码器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[36].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[36].HMC_HSC = 1029;
    // 可见检校超时
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[37].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[37].HMC_HSC = 1030;
    // 红外检校超时
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[38].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[38].HMC_HSC = 1031;
    // 压力传感器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[39].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[39].HMC_HSC = 1032;
    // 变倍位置异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[40].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[40].HMC_HSC = 1033;
    // 变倍超时
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[41].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[41].HMC_HSC = 1034;
    // 可见调焦位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[42].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[42].HMC_HSC = 1035;
    // 红外调焦位置超差
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[43].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[43].HMC_HSC = 1036;
    // 数据转换版RS422
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[44].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[44].HMC_HSC = 1037;
    // 可见光照度过低
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[45].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[45].HMC_HSC = 1038;
    // 可见光照度过高
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[46].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[46].HMC_HSC = 1039;
    // 可见探测器通信异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[47].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[47].HMC_HSC = 1040;
    // 红外探测器通信异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[48].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[48].HMC_HSC = 1041;
    // 红外校正位置异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[49].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[49].HMC_HSC = 1042;
    // 红外制冷异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[50].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[50].HMC_HSC = 1043;
    // 图像预处理单元RS422通信故障
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[51].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[51].HMC_HSC = 1044;
    // 本体温度控制器RS422控制器通信异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[52].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[52].HMC_HSC = 1045;
    // 本体温度传感器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[53].HMC_LCN = 398000100;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[53].HMC_HSC = 1046;
    // 窗口温度控制器Rs422
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[54].HMC_LCN = 398000300;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[54].HMC_HSC = 2001;
    // 窗口温度传感器异常
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[55].HMC_LCN = 398000300;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[55].HMC_HSC = 2002;
}

void set_One_HMC(int i, int state) {
    nb_HMC_DATA.flag_CURRENT_HMC[i]               = state;
    nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_State = state; // HMC状态，发生1、消失0
}

// HMC信息获取函数
void nb_HMC_DATA_SET() {
    int i         = 0;
    int temp_HASC = 0; // 临时hasc码
    int sum       = 0;

    // 故障0051：通信功能异常
    if (nb_HMC_DATA.flag_CURRENT_HMC[8] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[9] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[16] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[27] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[34] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[44] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[51] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[52] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[54] == 1) {
        set_One_HMC(0, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(0, 0); // 消失故障
    }
    // 故障0052：参数超限
    if (nb_HMC_DATA.flag_CURRENT_HMC[10] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[11] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[12] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[13] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[14] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[15] == 1) {
        set_One_HMC(1, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(1, 0); // 消失故障
    }
    // 故障0053：伺服功能异常
    if (nb_HMC_DATA.flag_CURRENT_HMC[16] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[17] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[18] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[19] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[20] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[21] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[22] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[23] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[24] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[25] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[26] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[27] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[28] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[29] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[30] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[31] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[32] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[33] == 1) {
        set_One_HMC(2, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(2, 0); // 消失故障
    }

    // 故障0054：调焦功能异常
    if (nb_HMC_DATA.flag_CURRENT_HMC[34] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[35] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[26] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[37] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[38] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[39] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[40] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[41] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[42] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[43] == 1) {
        set_One_HMC(3, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(3, 0); // 消失故障
    }

    // 故障0055：调光功能异常
    if ((nb_HMC_DATA.flag_CURRENT_HMC[45] == 1 && temp_mess_FromFc_MISSION_EVENT_REPORT.WOW_main == V_WOW_MAIN_WOW_AIR) || nb_HMC_DATA.flag_CURRENT_HMC[46] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[47] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[48] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[49] == 1 || nb_HMC_DATA.flag_CURRENT_HMC[50] == 1) {

        set_One_HMC(4, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(4, 0); // 消失故障
    }

    // 故障0045：图像预处理单元可见光图像通路异常
    if (mess_From_TXCL.fault_bit2) {
        set_One_HMC(5, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(5, 0); // 消失故障
    }
    // 故障0046：图像预处理单元红外图像通路异常
    if (mess_From_TXCL.fault_bit3) {
        set_One_HMC(6, 1); // 产生故障
        //		update_Work_State(V_SUBSYS_WORK_STATE_DEGRADE);//更新相机工作状态——降级
    } else {
        set_One_HMC(6, 0); // 消失故障
    }

    // 故障0049：隐身光窗去雾异常（实际是光窗422异常）
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_gc == 1) {
        set_One_HMC(7, 1); // 产生故障
    } else {
        set_One_HMC(7, 0); // 消失故障
    }

    // //故障0001：光机组件控制器通信接口故障
    // if(ACoreOs_atomic32_get(&flag_Fpga_down_times) > 50)
    // {
    // 	set_One_HMC(8, 1);//产生故障
    // }
    // else
    // {
    // 	set_One_HMC(8, 0);//消失故障
    // }

    // 故障0002：POS通信故障
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_pos) {
        set_One_HMC(9, 1); // 产生故障
    } else {
        set_One_HMC(9, 0); // 消失故障
    }
    // 故障0003：输入俯仰角参数超限
    if (mess_From_PCS_DATA.pitch * (PI / pow(2, 31)) * 57.2958 > 5.0 || mess_From_PCS_DATA.pitch * (PI / pow(2, 31)) * 57.2958 < -5.0) {
        set_One_HMC(10, 1); // 产生故障
    } else {
        set_One_HMC(10, 0); // 消失故障
    }
    // 故障0004：速高比超限
    if (param_Compute_Output.toKJ_speed_hight > 0.02) {
        set_One_HMC(11, 1); // 产生故障
    } else {
        set_One_HMC(11, 0); // 消失故障
    }
    // 故障0005：输入速度参数超限
    if (sqrt(param_Compute_Input_Fromfpga.north_speed * param_Compute_Input_Fromfpga.north_speed +
             param_Compute_Input_Fromfpga.east_speed * param_Compute_Input_Fromfpga.east_speed) *
            0.001 * 3.6 >
        1000) {
        set_One_HMC(12, 1); // 产生故障
    } else {
        set_One_HMC(12, 0); // 消失故障
    }
    // 故障0006：输入高度参数超限
    if (param_Compute_Input_Fromfpga.altitude * 0.001 > 20000 || param_Compute_Input_Fromfpga.altitude * 0.001 < 1000) {
        set_One_HMC(13, 1); // 产生故障
    } else {
        set_One_HMC(13, 0); // 消失故障
    }

    // 故障0007：输入偏流角参数超限
    if (temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_sl_angle._angle_mrad * 1000 * 57.2958 > 5.0 || temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED.ac_flight_vector.ac_sl_angle._angle_mrad * 1000 * 57.2958 < -5.0) {
        set_One_HMC(14, 1); // 产生故障
    } else {
        set_One_HMC(14, 0); // 消失故障
    }
    // 故障0008：输入横滚角参数超限
    if (mess_From_PCS_DATA.roll * (PI / pow(2, 31)) * 57.2958 > 5.0 || mess_From_PCS_DATA.roll * (PI / pow(2, 31)) * 57.2958 < -5.0) {
        set_One_HMC(15, 1); // 产生故障
    } else {
        set_One_HMC(15, 0); // 消失故障
    }
    // 故障0009：框架控制分系统RS422故障
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_kj) {
        set_One_HMC(16, 1); // 产生故障
    } else {
        set_One_HMC(16, 0); // 消失故障
    }
    // 故障0010：外框架陀螺异常
    if (mess_From_KJ.error_kj_kjfwtlyc) {
        set_One_HMC(17, 1); // 产生故障
    } else {
        set_One_HMC(17, 0); // 消失故障
    }
    // 故障0011：外框架编码器异常
    if (mess_From_KJ.error_kj_fwbmqyc) {
        set_One_HMC(18, 1); // 产生故障
    } else {
        set_One_HMC(18, 0); // 消失故障
    }
    // 故障0012：外框架位置超差
    if (mess_From_KJ.error_kj_kjfwwzcc) {
        set_One_HMC(19, 1); // 产生故障
    } else {
        set_One_HMC(19, 0); // 消失故障
    }
    // 故障0013：外框架速度超差
    if (mess_From_KJ.error_kj_kjfwsdcc) {
        set_One_HMC(20, 1); // 产生故障
    } else {
        set_One_HMC(20, 0); // 消失故障
    }
    // 故障0014：内框架陀螺异常
    if (mess_From_KJ.error_kj_kjfytlyc) {
        set_One_HMC(21, 1); // 产生故障
    } else {
        set_One_HMC(21, 0); // 消失故障
    }
    // 故障0015：内框架编码器异常
    if (mess_From_KJ.error_kj_kjfybmqyc) {
        set_One_HMC(22, 1); // 产生故障
    } else {
        set_One_HMC(22, 0); // 消失故障
    }
    // 故障0016：内框架位置超差
    if (mess_From_KJ.error_kj_kjfywzcc) {
        set_One_HMC(23, 1); // 产生故障
    } else {
        set_One_HMC(23, 0); // 消失故障
    }
    // 故障0017：内框架速度超差
    if (mess_From_KJ.error_kj_kjfysdcc) {
        set_One_HMC(24, 1); // 产生故障
    } else {
        set_One_HMC(24, 0); // 消失故障
    }
    // 故障0018：框架位置/速度信号异常
    if (mess_From_KJ.error_wzsdtbxh) {
        set_One_HMC(25, 1); // 产生故障
    } else {
        set_One_HMC(25, 0); // 消失故障
    }
    // 故障0019：框架接收的快反启动信号异常
    if (mess_From_KJ.error_xybczqxhyc) {
        set_One_HMC(26, 1); // 产生故障
    } else {
        set_One_HMC(26, 0); // 消失故障
    }
    // 故障0020：补偿镜控制分系统RS422故障
    if (mess_From_KJ.error_kf422txyc) {
        set_One_HMC(27, 1); // 产生故障
    } else {
        set_One_HMC(27, 0); // 消失故障
    }
    // 故障0021：快反方位AD采集异常
    if (mess_From_KJ.error_kfADcyyc) {
        set_One_HMC(28, 1); // 产生故障
    } else {
        set_One_HMC(28, 0); // 消失故障
    }
    // 故障0022：快反俯仰AD采集异常
    if (mess_From_KJ.error_kfADcyyc) {
        set_One_HMC(29, 1); // 产生故障
    } else {
        set_One_HMC(29, 0); // 消失故障
    }
    // 故障0023：快反方位电机状态异常
    if (mess_From_KJ.error_fwwzcc) {
        set_One_HMC(30, 1); // 产生故障
    } else {
        set_One_HMC(30, 0); // 消失故障
    }
    // 故障0024：快反俯仰电机状态异常
    if (mess_From_KJ.error_fywzcc) {
        set_One_HMC(31, 1); // 产生故障
    } else {
        set_One_HMC(31, 0); // 消失故障
    }
    // 故障0025：快反方位位置超差
    if (mess_From_KJ.error_fwwzcc) {
        set_One_HMC(32, 1); // 产生故障
    } else {
        set_One_HMC(32, 0); // 消失故障
    }
    // 故障0026：快反俯仰位置超差
    if (mess_From_KJ.error_fywzcc) {
        set_One_HMC(33, 1); // 产生故障
    } else {
        set_One_HMC(33, 0); // 消失故障
    }
    // 故障0027：调焦RS422通信故障
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_tj) {
        set_One_HMC(34, 1); // 产生故障
    } else {
        set_One_HMC(34, 0); // 消失故障
    }
    // 故障0028：可见调焦编码器异常
    if (mess_From_TJ.error1_kj_tjbmq) {
        set_One_HMC(35, 1); // 产生故障
    } else {
        set_One_HMC(35, 0); // 消失故障
    }
    // 故障0029：红外调焦编码器异常
    if (mess_From_TJ.error1_hw_tjbmq) {
        set_One_HMC(36, 1); // 产生故障
    } else {
        set_One_HMC(36, 0); // 消失故障
    }
    // 故障0030：可见检焦超时
    if (mess_From_TJ.error1_kj_jjcs) {
        set_One_HMC(37, 1); // 产生故障
    } else {
        set_One_HMC(37, 0); // 消失故障
    }
    // 故障0031：红外检焦超时
    if (mess_From_TJ.error1_hw_timeout) {
        set_One_HMC(38, 1); // 产生故障
    } else {
        set_One_HMC(38, 0); // 消失故障
    }
    // 故障0032：压力传感器异常
    if (mess_From_TJ.error2_ylcgq) {
        set_One_HMC(39, 1); // 产生故障
    } else {
        set_One_HMC(39, 0); // 消失故障
    }
    // 故障0033：变倍位置异常
    if (mess_From_TJ.error1_bbj_dw) {
        set_One_HMC(40, 1); // 产生故障
    } else {
        set_One_HMC(40, 0); // 消失故障
    }
    // 故障0034：变倍超时
    if (mess_From_TJ.error1_bbj_timeout) {
        set_One_HMC(41, 1); // 产生故障
    } else {
        set_One_HMC(41, 0); // 消失故障
    }
    // 故障0035：可见调焦位置超差
    if (mess_From_TJ.error1_kj_wzcc) {
        set_One_HMC(42, 1); // 产生故障
    } else {
        set_One_HMC(42, 0); // 消失故障
    }
    // 故障0036：红外调焦位置超差
    if (mess_From_TJ.error1_hw_wzcc) {
        set_One_HMC(43, 1); // 产生故障
    } else {
        set_One_HMC(43, 0); // 消失故障
    }
    // 故障0037：数据转换板控制分系统RS422故障
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_qn) {
        set_One_HMC(44, 1); // 产生故障
    } else {
        set_One_HMC(44, 0); // 消失故障
    }
    // 故障0038：可见光照度过低
    if (mess_From_TG.KJGZD_LowError) {
        set_One_HMC(45, 1); // 产生故障
    } else {
        set_One_HMC(45, 0); // 消失故障
    }
    // 故障0039：可见光照度过高
    if (mess_From_TG.KJGZD_HighError) {
        set_One_HMC(46, 1); // 产生故障
    } else {
        set_One_HMC(46, 0); // 消失故障
    }
    // 故障0040：可见探测器通信异常
    if (mess_From_TG.KJTCQ_Error | mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_qn) {
        set_One_HMC(47, 1); // 产生故障
    } else {
        set_One_HMC(47, 0); // 消失故障
    }
    // 故障0041：红外探测器通信异常
    if (mess_From_TG.HWTCQ_Error | mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_qn) {
        set_One_HMC(48, 1); // 产生故障
    } else {
        set_One_HMC(48, 0); // 消失故障
    }
    // 故障0042：校正位置异常
    if (mess_From_TJ.error2_jzb_dw) {
        set_One_HMC(49, 1); // 产生故障
    } else {
        set_One_HMC(49, 0); // 消失故障
    }
    // 故障0043：红外制冷异常
    if (mess_From_TG.HW_Coolling_Error) {
        set_One_HMC(50, 1); // 产生故障
    } else {
        set_One_HMC(50, 0); // 消失故障
    }
    // 故障0044：图像预处理单元RS422通信故障
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_tx) {
        set_One_HMC(51, 1); // 产生故障
    } else {
        set_One_HMC(51, 0); // 消失故障
    }

    // 故障0047：载荷本体温度控制器RS422通讯
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_qnwk == 1) {
        set_One_HMC(52, 1); // 产生故障
    } else {
        set_One_HMC(52, 0); // 消失故障
    }
    // 故障0048：载荷温度传感器异常
    if (mess_From_QNSJ.error1 != 0 || mess_From_QNSJ.error2 != 0) {
        set_One_HMC(53, 1); // 产生故障
    } else {
        set_One_HMC(53, 0); // 消失故障
    }
    // 故障0049：窗口温度控制器RS422通讯
    if (mess_From_FPGA.fpga_422ERR.fpag_422Err.error_commu_gc == 1) {
        set_One_HMC(54, 1); // 产生故障
    } else {
        set_One_HMC(54, 0); // 消失故障
    }
    // 故障0050：窗口温度传感器异常
    if (mess_From_GCWK.tem_error) {
        set_One_HMC(55, 1); // 产生故障
    } else {
        set_One_HMC(55, 0); // 消失故障
    }

    // 如果可见红外图像都传输异常，则置为失效
    if (nb_HMC_DATA.flag_CURRENT_HMC[5] == 1 && nb_HMC_DATA.flag_CURRENT_HMC[6] == 1) {
        //		update_Work_State(V_SUBSYS_WORK_STATE_FAIL);//更新相机工作状态——失效
    }

    for (i = 0; i < TOTAL_HMC_NUM; i++) {
        sum += nb_HMC_DATA.flag_CURRENT_HMC[i];
    }

    // 如果没有故障，取消故障
    if (sum == 0) {
        update_Work_State(-1); // 更新相机工作状态——取消
    }

    // 当前状态获取，用于设置//HASC码，上电10，周期30，启动40，维护50
    if (main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_TEST)           // 维护50
        temp_HASC = 50;                                                          // 临时hasc码
    else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_INIT) // 上电10
        temp_HASC = 10;                                                          // 临时hasc码
    else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_BIT)  // 启动40
        temp_HASC = 40;                                                          // 临时hasc码
    else                                                                         // 周期自检
        temp_HASC = 30;                                                          // 临时hasc码

    for (i = 0; i < TOTAL_HMC_NUM; i++) {
        // 时间设置
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].date_day          = temp_mess_FromFc_SYM_TIME_REPORT.univesal_date.date_day;
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].date_month        = temp_mess_FromFc_SYM_TIME_REPORT.univesal_date.date_month;
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].date_year         = temp_mess_FromFc_SYM_TIME_REPORT.univesal_date.date_year;
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].time_calendartime = temp_mess_FromFc_SYM_TIME_REPORT.time_calendartime;
        // HASC码设置
        nb_HMC_DATA.HMC_Data_Item_MS_Sub[i].HMC_HASC = temp_HASC;
    }

    nb_HMC_DATA_UPLOAD(); // 记录需要上报的故障信息：包括个数和内容
}

// 记录需要上报的故障信息：包括个数和内容
void nb_HMC_DATA_UPLOAD() {
    int i                        = 0;
    nb_HMC_DATA.hmc_count_upload = 0; // 需要上报的故障数量清零
    nb_HMC_DATA.pack_count       = 0;
    // 判断current和last是否一致，不一致的上报
    for (i = 0; i < TOTAL_HMC_NUM; i++) {
        // 如果有变化
        if (nb_HMC_DATA.flag_LAST_HMC[i] != nb_HMC_DATA.flag_CURRENT_HMC[i]) {
            // 记录需要上报的HMC内容
            memcpy(&(nb_HMC_DATA.HMC_Data_Item_MS_Sub_upload[nb_HMC_DATA.hmc_count_upload]),
                   &(nb_HMC_DATA.HMC_Data_Item_MS_Sub[i]), sizeof(HMC_DATA_ITEM_MS_SUB_TYPE_DEF));
            nb_HMC_DATA.hmc_count_upload++; // 上报故障数量增加
        }
    }

    // 上报后，用current替换last
    for (i = 0; i < TOTAL_HMC_NUM; i++) {
        nb_HMC_DATA.flag_LAST_HMC[i] = nb_HMC_DATA.flag_CURRENT_HMC[i];
        if (nb_HMC_DATA.hmc_count_upload % 10 == 0)
            nb_HMC_DATA.pack_count = nb_HMC_DATA.hmc_count_upload / 10; // 需要上报的HMC包数
        else
            nb_HMC_DATA.pack_count = nb_HMC_DATA.hmc_count_upload / 10 + 1; // 需要上报的HMC包数
    }
}

// 清除HMC信息函数
void nb_HMC_DATA_CLEAR() {
    nb_HMC_DATA_INIT(); // 重新初始化
}
