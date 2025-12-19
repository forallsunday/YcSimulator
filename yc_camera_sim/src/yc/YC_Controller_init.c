/*
 * YC_Controller_init.c
 *
 *  Created on: 2025年4月30日
 *      Author: wangx
 *      初始化系统变量函数
 */

// #include "YC_Controller_init.h"
// #include "String.h"
#include "YC_Controller_Constant_Define.h"
#include "YC_Controller_HMC_Process.h"
// #include "YC_Controller_Main_Process.h"
#include "YC_Controller_Mess_Process.h"
#include "YC_Controller_TG_Process.h"
// #include "ft_gpio.h"
// #include "semYc.h"
#include <YC_Controller_Constant_Define.h>
#include <YC_Controller_globalVal_Ext.h>
// #include <interrupt.h>

// //**************************创建线程**************************
// //**UINT32 affinity:处理器核号
// //**ACoreOs_task_priority priority：优先级
// //**ULONG stack_size：任务栈大小
// //**ACoreOs_name name：任务名称
// //**Task_ID task_id：任务id
// //**ACoreOs_task_entry entryPoint：任务入口函数
// //**************************创建线程**************************
// void yc_Create_Task(UINT32 affinity, ACoreOs_task_priority priority, ULONG stack_size, ACoreOs_name name, Task_ID task_id, ACoreOs_task_entry entryPoint) {
//     ACoreOs_Task_Param  taskCreateParam;              // 创建线程用的参数，可复用
//     ACoreOs_status_code retCode = ACOREOS_SUCCESSFUL; // 返回值接收

//     taskCreateParam.affinity         = affinity;                            // 任务无亲核属性设置ACOREOS_TASK_NO_AFFINITY，否则给定处理器核号
//     taskCreateParam.attribute_set    = ACOREOS_PREEMPT | ACOREOS_TIMESLICE; // 就用这个不用改
//     taskCreateParam.domain           = (ULONG)ACOREOS_KERNEL_ID;            // 就用这个不用改
//     taskCreateParam.initial_priority = priority;                            // 优先级
//     taskCreateParam.stack_size       = stack_size;                          // 字节
//     // 创建YC_Others_Porcess
//     retCode = ACoreOs_task_create(name, &taskCreateParam, &task_id);
//     if (retCode != ACOREOS_SUCCESSFUL) {
//         printf("Failed to create %s, return code:%#x!\n", name, retCode);
//     }
//     // 启动YC_Others_Porcess其他消息线程，等到init函数执行完才启动，启动前任务状态为ready，执行中为running
//     retCode = ACoreOs_task_start(task_id, entryPoint, 0);
//     if (retCode != ACOREOS_SUCCESSFUL) {
//         printf("Failed to start %s, return code:%d!\n", name, retCode);
//     }
//     printf("Create %s success!!\n\n", name);
// }

// //**************************创建周期线程**************************
// //**UINT32 affinity:处理器核号
// //**ACoreOs_task_priority priority：优先级
// //**ULONG stack_size：任务栈大小
// //**ACoreOs_name name：任务名称
// //**Task_ID task_id：任务id
// //**ACoreOs_task_entry entryPoint：任务入口函数
// //**periodLength：周期
// //**************************创建线程**************************
// void yc_Create_Period_Task(UINT32 affinity, ACoreOs_task_priority priority, ULONG stack_size, ACoreOs_name name, Task_ID *task_id, ACoreOs_task_entry entryPoint, ACoreOs_interval periodLength) {
//     *task_id = ACoreOs_periodtask_create(name, priority, stack_size, ACOREOS_DEFAULT_ATTRIBUTES, entryPoint, 0, periodLength, periodLength, affinity);
//     if (*task_id != NULL) {
//         printf("Create Period YC_Period_Send_Mess success!!\n");
//     }
//     UINT32              count;
//     ACoreOs_status_code ret = ACoreOs_periodtask_start(task_id, 1, &count);
//     if (ret == ACOREOS_SUCCESSFUL) {
//         printf("Start %d Period Task success!!\n", count);
//     } else {
//         printf("Failed to start period task!\n");
//     }
// }

void param_Init() {
    // // 线程id定义
    // YC_FC_Recv          = NULL; // 接收FC消息线程，放入list缓冲区
    // YC_Main_Control     = NULL; // 主流程控制线程
    // YC_Others_Porcess   = NULL; // 其他消息处理线程
    // YC_Period_Send_Mess = NULL; // 周期发送线程

    // timer_id_5ms = 0; // 5ms周期定时器

    // lstInit(&list_Mess_FromFc_IRST_act_req); // FC接收消息缓冲区
    // lstInit(&list_Mess_FromFc_Others);       // FC接收消息缓冲区-其他消息

    // // 创建信号量
    // bSemId_list_Mess_FromFc_IRST_act_req = createBinarysem(bSemName_list_Mess_FromFc_IRST_act_req); // FC接收消息缓冲区互斥锁
    // bSemId_list_Mess_FromFc_Others       = createBinarysem(bSemName_list_Mess_FromFc_Others);       // FC接收消息缓冲区互斥锁

    // 主控用标志位
    flag_Fpga_Interrupt  = 0; // fpga中断，0为未收到中断，1为已收到中断
    flag_Fpga_down_times = 0; // 统计fpga未触发次数
    flag_Fpga_bg         = 0; // 曝光信号到达

    memset(&main_Control_State_Param, 0, sizeof(MAIN_CONTROL_STATE_PARAM));
    main_Control_State_Param.totalNo = 0;
    // 主控用相关状态位
    main_Control_State_Param.work_state      = V_SUBSYS_WORK_STATE_NORMAL; // 正常
    main_Control_State_Param.main_mode       = V_SUBSYS_MAIN_MODE_INI;     // 相机工作模式，上报的工作模式,开机默认成初始化
    main_Control_State_Param.irst_work_state = V_IRST_WORK_STATE_INIT;     // IRST工作状态:初始化
    main_Control_State_Param.irst_form_mode  = V_IRST_FORM_MODE_NA;        // IRST成像模式广域成像、区域成像、区域监视
    main_Control_State_Param.trans_state     = V_ID_DATA_TRANS_FLAG_NO;    // 传图状态，初始化为否

    memset(&param_Compute_Output, 0, sizeof(PARAM_COMPUTE_OUTPUT)); // 主控计算输出参数结构体

    memset(&cmd_From_FC, 0, sizeof(CMD_FROM_FC)); // 用于缓存从fc来的IRST_ACT_REQ消息，和能执行的指令
    memset(&param_Compute_Input_Fromfc, 0, sizeof(PARAM_COMPUTE_INPUT_FROMFC));
    memset(&param_Compute_Input_Fromfpga, 0, sizeof(PARAM_COMPUTE_INPUT_FROMFPGA));
    memset(&vnode_APP_STATE, 0, sizeof(V_NODE_APP_STATE)); // 记录各功能单元的应用状态结构体

    // 调光用相关参数
    memset(&tg_Param, 0, sizeof(TG_PARAM));         // 调光用参数结构体
    memset(&mess_To_TG, 0, sizeof(MESS_TO_TG));     // 向调光发送
    memset(&mess_From_TG, 0, sizeof(MESS_FROM_TG)); // 从调光接收

    // 静态成像ICD
    memset(&nbMess_jt_Photo, 0, sizeof(MESS_FROMFC_JT_PHOTO));
    nbMess_jt_Photo.zl_Switch = 1; // 红外制冷机默认为1-开

    param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1;
    // 消息初始化
    mess_Init();

    TG_VarInit(); // 调光初始化-25-8-15,sc

    flash_Data_Init(); // 持久化存储信息初始化

    nb_HMC_DATA_INIT(); // HMC初始化

    comp_Parm_init(); // 计算初始化

    make_Mess_To_JLY(JLY_CMD_OPEN); // 记录仪

    // 默认参设置
    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_focus_mode           = V_LIGHT_FOCUS_MODE_AUTO;            // 名  称:可见光调焦模式
    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_dim_mode             = V_LIGHT_DIM_MODE_AUTO;              // 名  称:可见光调光模式
    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_enhance_mode         = V_LIGHT_ENHANCE_MODE_OFF;           // 名  称:可见光增强状态
    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_mist_eliminate_state = V_LIGHT_MIST_ELIMINATE_STATE_OFF;   // 名  称:可见光去雾状态
    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_focus_mode        = V_INFRARED_FOCUS_MODE_AUTO;         // 名  称:红外调焦模式
    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode          = V_INFRARED_DIM_MODE_AUTO;           // 名  称: 红外调光模式
    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_enhance_mode      = V_INFRARED_ENHANCE_MODE_OFF;        ////名  称:红外增强状态
    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.video_polar                = V_VIDEO_POLAR_WHOT;                 // 名  称:视频极化
    cmd_From_FC.irst_cmd_param_IR_Transom_paras.Transom_mist_eliminate_state   = V_TRANSOM_MIST_ELIMINATE_STATE_OFF; ////名  称:光窗去雾状态
    cmd_From_FC.irst_cmd_param_irst_form_mode                                  = V_IRST_FORM_MODE_WIDE_IMAG;         // 名  称:IRST成像模式1

    cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_IMG_MODE = V_IR_IMG_MODE_CONTINUES; // 名  称:光电成像方式
    cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_IMG_MODE = V_IR_IMG_MODE_CONTINUES; // 名  称:光电成像方式
    cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_IMG_MODE = V_IR_IMG_MODE_CONTINUES; // 名  称:光电成像方式
    cmd_From_FC.irst_cmd_param_IRST_Video_BAND                 = V_IRST_VIDEO_BAND_NA;    ////名  称:IRST_区域监视视频带宽1
    cmd_From_FC.irst_cmd_param_environmnet_type                = V_ENVIRONMNET_TYPE_AUTO; // 设置默认值
    cmd_From_FC.irst_cmd_param_IR_SENSOR                       = V_IR_SENSOR_LANDI;       // 传感器状态：默认可见+红外
    cmd_From_FC.irst_cmd_VIEW_STATE                            = 0;                       // 名  称:大小视场，0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦

    // 广域成像默认参数
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_lowline        = 6000;                           // 距离近界60km
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = V_IR_WIDE_IMAGE_DIRECTION_LEFT; // 扫描方向，左侧
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = V_IR_WIDE_IMAGE_MODE_DIS_PRIO;  // 光电广域成像子模式，距离优先
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_IMAGE_RANGE          = 10000;                          // 量程，100km
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_upline         = 12000;                          // 距离近界120km
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_start_angle     = -5236;                          // 光电扫描起始角,-30度
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_end_angle       = 5236;                           // 光电扫描结束角,30度
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.D_area_altitude         = 0;                              // 高度，0
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras.AZ_area_altitude        = 0;                              // 高度，0
    cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity                = 1;                              // 有效性默认为1
    cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_AREA_LENGTH          = 4;                              // 区域边长默认为4km
    cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_AREA_LENGTH          = 4;                              // 区域边长默认为4km
    cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_AREA_LENGTH          = 4;                              // 区域边长默认为4km
}

// 持久化存储信息初始化
void flash_Data_Init() {
    // 持久化存储信息初始化
    memcpy(&nbMess_hwInfo_FLASH, (void *)FLASH_ADDR, sizeof(MESS_FROMFC_HWINFO_FLASH));                        // 放入接收缓存
    nbMess_hwInfo_FLASH.electrify_amount_From_FPGAsave++;                                                      // 累加上电次数
    my_flash_write(FLASH_ADDR, (void *)&(nbMess_hwInfo_FLASH.electrify_amount_From_FPGAsave), sizeof(UINT32)); // 写回flash

    // 20251128增加保存帧序号功能
    memcpy((void *)(&(main_Control_State_Param.totalNo)), (void *)(FLASH_ADDR + sizeof(MESS_FROMFC_HWINFO_FLASH)), sizeof(UINT32)); // 从持久化中读取帧序号

    printf("readflash:%d\n", main_Control_State_Param.totalNo);

    param_Compute_Input_Fromfpga.jj_Small_KJ = nbMess_hwInfo_FLASH.jj_Small_KJ; // 可见小视场-长焦
    param_Compute_Input_Fromfpga.jj_Big_KJ   = nbMess_hwInfo_FLASH.jj_Big_KJ;   // 可见大视场-短焦
    param_Compute_Input_Fromfpga.jj_Small_HW = nbMess_hwInfo_FLASH.jj_Small_HW; // 红外小视场-长焦
    param_Compute_Input_Fromfpga.jj_Big_HW   = nbMess_hwInfo_FLASH.jj_Big_HW;   // 红外大视场-短焦
}

// 消息初始化
void mess_Init() {
    // FC通信消息初始化
    memset(&temp_mess_FromFc_SYM_OPERATIONAL_PARAS, 0, sizeof(SYM_OPERATIONAL_PARAS));     // 系统管理工作参数报告
    memset(&temp_mess_FromFc_SYM_TIME_REPORT, 0, sizeof(SYM_TIME_REPORT));                 // 系统管理时间信息报告
    memset(&temp_mess_FromFc_INS1_OPERATIONAL_PARAS, 0, sizeof(INS1_OPERATIONAL_PARAS));   // INS1工作参数报告
    memset(&temp_mess_FromFc_INS2_OPERATIONAL_PARAS, 0, sizeof(INS2_OPERATIONAL_PARAS));   // INS2工作参数报告
    memset(&temp_mess_FromFc_INS3_OPERATIONAL_PARAS, 0, sizeof(INS3_OPERATIONAL_PARAS));   // INS3工作参数报告
    memset(&temp_mess_FromFc_INS1_NAV_DATA, 0, sizeof(INS1_NAV_DATA));                     // INS1导航数据
    memset(&temp_mess_FromFc_INS2_NAV_DATA, 0, sizeof(INS2_NAV_DATA));                     // INS2导航数据
    memset(&temp_mess_FromFc_INS3_NAV_DATA, 0, sizeof(INS3_NAV_DATA));                     // INS3导航数据
    memset(&temp_mess_FromFc_ABSOLUTE_NAV_DATA_FUSED, 0, sizeof(ABSOLUTE_NAV_DATA_FUSED)); // 绝对导航融合飞行参数
    memset(&temp_mess_FromFc_NAV_PARAS, 0, sizeof(NAV_PARAS));                             // 导航参数报告
    memset(&temp_mess_FromFc_MISSION_EVENT_REPORT, 0, sizeof(MISSION_EVENT_REPORT));       // 战术任务事件报告

    memset(&mess_ToFC_IRST_ACT_REQ_REPORT, 0, sizeof(IRST_ACT_REQ_REPORT));                       // IRST_活动请求通告
    memset(&mess_ToFC_WORK_STATE_REPORT, 0, sizeof(IRST_ACT_REQ_REPORT));                         // 工作状态报告
    memset(&mess_ToFC_IRST_OPERATIONAL_PARAS, 0, sizeof(IRST_OPERATIONAL_PARAS));                 // IRST工作参数报告
    memset(&temp_mess_ToFC_IRST_OPERATIONAL_PARAS, 0, sizeof(IRST_OPERATIONAL_PARAS));            // IRST工作参数报告
    memset(&mess_ToFC_HW_CONFIG_INFO_REPORT, 0, sizeof(HW_CONFIG_INFO_REPORT));                   // 硬件配置信息报告
    memset(&mess_ToFC_SW_CONFIG_INFO_REPORT, 0, sizeof(SW_CONFIG_INFO_REPORT));                   // 软件配置信息报告
    memset(&mess_ToFC_PHM_DATA_RAW_IRST, 0, sizeof(PHM_DATA_RAW_IRST));                           // 健康管理_Raw数据_IRST
    memset(&mess_ToFC_PHM_DATA_EVENT_MS_SUB, 0, sizeof(PHM_DATA_EVENT_MS_SUB));                   // 健康管理_Event数据_MS_SUB
    memset(&mess_ToFC_PHM_DATA_HMC_MS_SUB, 0, sizeof(PHM_DATA_HMC_MS_SUB));                       // 健康管理_HMC数据_MS_SUB
    memset(&mess_ToFC_DATABASEINFO, 0, sizeof(DATABASEINFO));                                     // 数据库信息
    memset(&mess_ToFC_IRST_PIXEL_PARAS, 0, sizeof(IRST_PIXEL_PARAS));                             // IRST像元参数10
    memset(&mess_ToFC_IRST_LOS, 0, sizeof(IRST_LOS));                                             // 上报los数据
    memset(&mess_ToFC_IR_NAV_DATA, 0, sizeof(IR_NAV_DATA));                                       // 光电IMU导航数据
    memset(&mess_ToFC_RECONNAISED_AREA_IR_2GCS_EVENT, 0, sizeof(RECONNAISED_AREA_IR_2GCS_EVENT)); // 侦察覆盖区域参数_IR,红外注释信息
    memset(&mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT, 0, sizeof(RECONNAISED_AREA_TV_2GCS_EVENT)); // 侦察覆盖区域参数_TV,可见注释信息
    memset(&mess_ToFC_ID_DATA_TRANSMIT_STATE, 0, sizeof(ID_DATA_TRANSMIT_STATE));                 // 情报数据传输状态

    // 内部fpga消息初始化
    memset(&mess_To_TJ, 0, sizeof(Mess_To_TJ));                 // 向调焦发
    memset(&mess_To_KJ, 0, sizeof(Mess_To_KJ));                 // 向框架发
    memset(&mess_To_TXCL_CMD, 0, sizeof(Mess_To_TXCL_CMD));     // 向图像处理指令
    memset(&mess_To_TXCL_ZSXX, 0, sizeof(Mess_To_TXCL_ZSXX));   // 图像处理-注释信息
    memset(&mess_To_DY, 0, sizeof(Mess_To_DY));                 // 向电源发
    memset(&mess_To_GCWK, 0, sizeof(MESS_To_GCWK));             // 向光窗温控发
    memset(&mess_TO_PCS_DATA, 0, sizeof(Mess_TO_PCS_DATA));     // 向惯导发数据包
    memset(&mess_To_PCS_Update, 0, sizeof(MESS_To_PCS_Update)); // 向惯导发
    memset(&mess_To_JLY, 0, sizeof(MESS_To_JLY));               // 向记录仪发
    memset(&mess_To_QNSJ, 0, sizeof(MESS_To_QNSJ));             // 向球内数据发
    memset(&mess_To_FPGA, 0, sizeof(MESS_To_FPGA));             // 向FPGA发

    memset(&mess_From_TJ, 0, sizeof(Mess_From_TJ));             // 从调焦收
    memset(&mess_From_KJ, 0, sizeof(Mess_From_KJ));             // 从框架收
    memset(&mess_From_TXCL, 0, sizeof(Mess_From_TXCL));         // 从图像处理收
    memset(&mess_From_DY, 0, sizeof(Mess_From_DY));             // 从电源收
    memset(&mess_From_PCS_DATA, 0, sizeof(Mess_From_PCS_DATA)); // 从PCS收
    memset(&mess_From_GCWK, 0, sizeof(MESS_From_GCWK));         // 从光窗温控收
    memset(&mess_From_JLY, 0, sizeof(MESS_From_JLY));           // 向记录仪发
    memset(&mess_From_QNSJ, 0, sizeof(MESS_From_QNSJ));         // 向球内数据发
    memset(&mess_From_FPGA, 0, sizeof(MESS_From_FPGA));         // 向FPGA发

    make_Mess_To_DY(0, 1, 1, 1, 1); // 电源分系统通信，打开所有电源
}

// // 中断初始化
// void interrupt_Init() {
//     int ret;
//     // 复用为gpio,全部复用为gpio
//     gpio_pinmux();
//     // gpio输入/输出初始化
//     gpio_input_output_init();
//     // gpio中断初始化
//     gpio_int_init();
//     // 绑定中断响应函数
//     ret = ACoreOs_interrupt_set_handler(GPIO0_INT_IRQ_NUM, isr_Fpga_Mess, FALSE, 0);
//     if (ret != ACOREOS_SUCCESSFUL) {
//         return;
//     }
//     // 使能中断
//     ret = ACoreOs_intPIC_enable(GPIO0_INT_IRQ_NUM);
//     if (ret != ACOREOS_SUCCESSFUL) {
//         return;
//     }
// }
