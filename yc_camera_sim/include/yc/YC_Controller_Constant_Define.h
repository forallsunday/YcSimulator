///*
// * YC_Controller_Constant_Define.h
// *
// *  Created on: 2025年4月10日
// *      Author: 王潇逸
// *      
// *  描述：在该文件中定义所有常量定义
// */

#ifndef YC_CONTROLLER_CONSTANT_DEFINE_H_
#define YC_CONTROLLER_CONSTANT_DEFINE_H_
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "aoxe_output.h"
#include "ICDB_ENUM_STRUCT_IRRM.H"
#include "ICDB_TOPIC_STRUCT_IRRM.H"

//======================================================================================
//============================外场入网环境和内部调试环境的宏定义===========================
#define _APP_IN_SYSTEM_ 0			//应用接入大系统，接入大系统时为1，在家调试为0
//============================外场入网环境和内部调试环境的宏定义===========================
//======================================================================================
#define 	SW_VER 					0x0101  			//主控软件版本号
#define		FLASH_ADDR				(0x980000 + 0x400)	//主控可以写的flash地址
#define 	V_TOPIC_NEIBU_MESS		0xEB01				//持久化存储消息
#define 	V_TOPIC_JT_PHOTO 		0xEB02				//静态成像使用消息

//====================================与内部分系统通信地址定义==================================================
#define OFFSET_TO_FPGA_KJ				0x01C4		//写框架
#define OFFSET_FROM_FPGA_KJ				0x1844		//读框架

#define OFFSET_TO_FPGA_PCS				0x1B44		//写惯导
#define OFFSET_FROM_FPGA_PCS			0x1644		//读惯导

#define OFFSET_TO_FPGA_JLY				0x0144		//写记录仪
#define OFFSET_FROM_FPGA_JLY			0x1604		//读记录仪

#define OFFSET_TO_FPGA_DY				0x0104		//写电源
#define OFFSET_FROM_FPGA_DY				0x1584		//读电源

#define OFFSET_TO_FPGA_TJ				0x00C4		//写调焦
#define OFFSET_FROM_FPGA_TJ				0x1504		//读调焦

#define OFFSET_TO_FPGA_CK				0x0084		//写窗口
#define OFFSET_FROM_FPGA_CK				0x1444		//读窗口

#define OFFSET_TO_FPGA_ZKFPGA			0x0044		//写  主控-FPGA信息交互（包括持久化存储）
#define OFFSET_FROM_FPGA_ZKFPGA			0x1344		//读  主控-FPGA信息交互

#define OFFSET_TO_FPGA_QNSJ				0x0004		//写球内数据
#define OFFSET_FROM_FPGA_QNSJ			0x1004		//读球内数据

#define OFFSET_TO_FPGA_TXCL_CMD			0x0204		//写图像指令
#define OFFSET_TO_FPGA_TXCL_ZSXX		(0x0204 + sizeof(Mess_To_TXCL_CMD))		//写图像注释信息0x0210
#define OFFSET_FROM_FPGA_IMAGE			0x1944		//读图像

//====================================与内部分系统通信地址定义=======end===========================================
//gpio中断用
#define FT_GPIO0_BASE        (0x28004000)
#define FT_GPIO1_BASE        (0x28005000)
#define	GPIO_PORTA_EOI		 (0x38)


//FC-----内部桌面联试使用
#define UIFICNO 		0   //设备号，等待总体分配
#define UILOCALDEVID 	2   //本地id，等待总体分配（点对点测试为1）
#define UITOPMODE		1   //拓扑模式，入网为0，平时为1
#define UICFGFILEMODE	0   //内部测试为0* 配置模式：0, 无配置表；1，FLASH模式；2，C文件模式；3，自动生成配置表，仅点对点有效。*/


//应用层宏定义
#define SHORT_MSG_SLEEP_TIME            (5)//接收消息延时,微秒
#define PERIOD_TASK_TIME 				(360)//周期任务时间360ms
#define MAIN_PERIOD_TIME 				(5)//主流程时间5ms
#define INIT_TIME						50//初始化时间，50s
#define PI 								3.14159265358//π



//------------------------------------内部使用结构体定义-------------------------------------
#pragma pack(1)
//定义链表节点结构体，用于存储message
typedef struct Mess_Node
{
	// todo: 该 node 与 xml中定义的node冲突
    // struct node *next; /* 指向链表下一个节点的指针 */
    // struct node *previous; /* 指向链表上一个节点的指针 */
    
    UINT32 mess_typeId;	//消息id
    UINT32 mess_len;	//消息长度
    UINT8  mess_data[SHORT_MSG_MAX_LEN];	//消息内容
}MESS_NODE;

//主控从fc收到的可以执行的指令寄存器，用于在work_Controll中进行判断执行
typedef struct Cmd_From_FC
{
	IRST_ACT_REQ current_IRST_ACT_REQ;//当前处理的指令报文,从fc接收的可以执行的报文

	
	//指令区域-----------------------------------------------------------------------
	//记录可执行的活动请求指令，0：为指令无效；1：为指令有效
	//在指令可以执行时置为1，执行完成时置为0（调用clean_cmd_From_FC();）
	//通用活动请求7个指令
	UINT8 general_cmd_MODE_SWITCH:1;		//工作模式请求
	UINT8 general_cmd_BIT_OPERATION:1;		//执行BIT请求
//	UINT8 general_cmd_MFL_OPERATION:1;		//MFL操作请求——清除mfc
//	UINT8 general_cmd_DATA_REQ:1;			//子域数据请求
//	UINT8 general_cmd_ICP1_MODE_SWITCH:1;	//ICP1工作模式请求
//	UINT8 general_cmd_ICP2_MODE_SWITCH:1;	//ICP2工作模式请求
//	UINT8 general_cmd_UNIQUE_ACT:1;			//特殊活动请求
	UINT8 general_cmd_baoliu:5;				//保留

	//特殊活动请求16个指令
	UINT16 irst_cmd_STATE_SET:1;					//1.修改光电工作状态———按状态转换图
	UINT16 irst_cmd_IMAGE_MODE_CHG:1;				//2.成像模式修改——收藏、待机、拍照可接收，只有准备中、拍照有动作，其他保存参数
	UINT16 irst_cmd_WIDE_IMAGE_CNTL:1;				//3.修改广域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
	UINT16 irst_cmd_AREA_IMAGE_CNTL:1;				//4.修改区域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
	UINT16 irst_cmd_WIDE_MONI_CNTL:1;				//5.修改区域监视参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
	UINT16 irst_cmd_LIGHT_IMA_PARS_UPDATE:1;		//6.可见光成像参数修改——收藏、待机、拍照，直接转发
	UINT16 irst_cmd_INFRA_IMA_PARS_UPDATE:1;		//7.红外成像参数修改——收藏、待机、拍照，直接转发
	UINT16 irst_cmd_SENSOR_SET:1;					//8.成像传感器控制——收藏、待机、拍照
//	UINT16 irst_cmd_SCENE_TYPE_CHANGE:1;			//9.修改场景类型——只有收藏可修改场景————————该条不用判断，work_control中直接按参数转发即可
//	UINT16 irst_cmd_WINDOW_FOG_REMOVE:1;			//10.光窗去雾——收藏状态————————该条不用判断，work_control中直接按参数转发即可
	UINT16 irst_cmd_ENTER_TGT_TRACK:1;				//11.进入图像跟踪——只有拍照、区域监视
	UINT16 irst_cmd_EXIT_TGT_TRACK:1;				//12.退出图像跟踪——只有拍照、区域监视
	UINT16 irst_cmd_IMU_ALIGN:1;					//13.IMU对准_待机和收藏可响应
	UINT16 irst_cmd_INFRA_CORRECT:1;				//14.红外校正——只有待机
	UINT16 irst_cmd_FROZEN:1;						//15.冻结——拍照、区域监视	
	UINT16 irst_cmd_VIDEO_BAND_SET:1;				//16.视频带宽设置————收藏、待机
	UINT16 irst_cmd_baoliu:4;						//保留	
	//指令区域-------------------------------------------------------------------END----

	
	//通用活动请求参数区域------------------------记录下发的、可以执行的工作参数--------------------------------------------------------------------------------
	//名  称:MFL操作类型
	MFL_OPERATION              	MFL_operation;
	//名  称:自检测模式
	BIT_MODE              		bit_mode;
	//名  称:子系统工作模式
	SUBSYS_MAIN_OPER_MODE       subsys_main_oper_mode;
	
	
	//特殊活动请求参数区域------------------------记录下发的、可以执行的工作参数--------------------------------------------------------------------------------
	//名  称:IRST工作状态1
	IRST_WORK_STATE             		irst_cmd_param_irst_work_state;
	//名  称:IR可见光图像参数1
	IR_IMAGE_PARAS_LIGHT_TYPE_DEF		irst_cmd_param_IR_image_paras_light;
	//名  称:IR红外图像参数1
	IR_IMAGE_PARAS_INFRA_TYPE_DEF		irst_cmd_param_IR_image_paras_infra;
	//名  称:IR光窗参数1
	IR_TRANSOM_PARAS_TYPE_DEF			irst_cmd_param_IR_Transom_paras;
	//名  称:IRST成像模式1
	IRST_FORM_MODE              		irst_cmd_param_irst_form_mode;
	//名  称:IR广域成像范围参数1
	IR_WIDE_IMAGE_PARAS_REQ_TYPE_DEF	irst_cmd_param_IR_wide_image_paras;
	//广域成像范围参数有效性1：有效，0：无效1
	UINT8            					irst_cmd_param_IR_wide_image_paras_validity;
	
	
	//名  称:IR区域成像范围参数,根据区域编号缓存三个1
	AREA_IMAGE_PARAS_REQ_TYPE_DEF		irst_cmd_param_area_image_paras[3];
	//代表0，1，2三个区域的有效性，1：有效，0：无效1
	UINT8            					irst_cmd_param_area_image_paras_validity[3];
	//代表0，1，2三个区域哪个正在成像，1：正在成像，0：非正在成像
	UINT8            					irst_cmd_param_area_image_paras_photoing[3];
	//名  称:IRST_区域监视视频带宽1
	UINT8            					irst_cmd_param_IRST_Video_BAND;
	//名  称:IR区域监视范围参数1
	AREA_MONITOR_PARAS_TYPE_DEF			irst_cmd_param_area_monitor_paras;
	//区域监视参数有效性1：有效，0：无效1
	UINT8            					irst_cmd_param_area_monitor_paras_validity;
	
	
	//名  称:图像跟踪信息1
	IR_TGT_TRACK_INFO_TYPE_DEF			irst_cmd_param_IR_TGT_TRACK_INFO;
	//名  称:环境类型1
	ENVIRONMNET_TYPE              		irst_cmd_param_environmnet_type;

	//名  称:光电传感器状态1
	IR_SENSOR              					irst_cmd_param_IR_SENSOR;
	
	//名  称:大小视场，0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦
	UINT8              					irst_cmd_VIEW_STATE;
	
}CMD_FROM_FC;


//主控从状态、控制数据记录等
typedef struct Main_control_State_Param
{
	//主控用相关状态位
	SUBSYS_WORK_STATE 	work_state;			//相机工作状态，上报的工作状态,不受控制，自己上报。subsys_work_state子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
	SUBSYS_MAIN_MODE 	main_mode;			//相机工作模式，上报的工作模式。
	IRST_WORK_STATE		irst_work_state;	//IRST工作状态:初始化、收藏、准备中
	IRST_FORM_MODE		irst_form_mode;		//IRST成像模式:广域成像、区域成像、区域监视
	
	TGT_TRACK_STATE				track_state;//自动跟踪状态
	INFRARED_CORRECT_STATE 		jiaozheng_state;//非均匀性校正状态
	PREPARE_STATE_FOCUS 		tj_state;//检调焦状态
	PREPARE_STATE_DIM 			tg_state;//检调光状态
	ID_DATA_TRANS_FLAG			trans_state;//传图状态
	

	UINT8				view_State;//大小视场状态,0:小视场（长焦）；1：大视场（短焦），默认未小视场长焦
	
	//名  称:图像帧序号
	UINT32              		totalNo;
	//名  称:光电周期号
	//说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
	UINT32              		cycleNo;

	//名  称:条带号
	//       光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
	UINT16              		lineNo;
	
	//名  称:条带内序号
	//       表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
	UINT16              		in_lineNo;
	

	
	//名  称:照相次数
	//说  明:000~999，共用。
	//       光电：每次接收拍照指令或模式变换时+1，对应数据记录时，建立新模式的文件夹
	UINT16              		takeTimes;
}MAIN_CONTROL_STATE_PARAM;

//持久化存储相关参数
typedef struct Struct_HWINFO_FLASH
{
	UINT32 						electrify_amount_From_FPGAsave;	//上电次数,每次上电累加
	float						jj_Small_KJ;			//可见小视场-长焦
	float						jj_Big_KJ;			//可见大视场-短焦
	float						jj_Small_HW;			//红外小视场-长焦
	float						jj_Big_HW;			//红外大视场-短焦
	SW_CONFIG_INFO_TYPE_DEF		SW_config_info[8];				//名  称:软件配置信息，一共8个
	HW_CONFIG_INFO_TYPE_DEF		HW_config_info[6];				//名  称:硬件配置信息
}MESS_FROMFC_HWINFO_FLASH;

//静态成像ICD
typedef struct Struct_JT_PHOTO
{
	INT8		zl_Switch;			//红外制冷开关1：打开制冷 0:关闭制冷；-1：无效
	UINT8  		position_flag;           //位置姿态地面仿真标识     TRUE：有效     FALSE：无效
	UINT8  		sf_switch;           //伺服上下电开关伺服上下电：0xAA下电；0x00上电，默认上
	
	INT32       toKJ_pitch_start;   		//框架俯仰指令   起始角（LSB=0.0001°）
	INT32       toKJ_direction_start;       //框架方位指令   起始角（LSB=0.0001°）


    float 		Carrier_longitude;      //载机经度    单位°    精度0.000001°
    float 		Carrier_latitude;       //载机纬度     单位°    精度0.000001°
    float 		Carrier_altitude;       //载机高度        单位米    精度1m      范围-500m-25000m
    float 		Carrier_true_heading;    //载机真航向    单位°    精度0.001°    范围-180°-180°
    float 		Carrier_pitch;          //载机俯仰角    单位°    精度0.001°    范围-180°-180°
    float 		Carrier_roll;           //载机横滚角    单位°    精度0.001°    范围-180°-180°
    float 		Carrier_north_speed;    //载机北向速度    单位m/s     精度0.0001
    float 		Carrier_east_speed;     //载机北向速度    单位m/s     精度0.0001
    float 		Carrier_ground_speed;;    //载机北向速度    单位m/s     精度0.0001

    //回报的状态
    INT8 		hw_cold_state;      //红外制冷开关状态  1：打开制冷   0：关闭制冷   -1：无效
    INT8 		view_state;        //大小视场状态    0:小视场    1：大视场
    
    //检测仪显示
	INT16			zjwdxx;							//主镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦 
	INT16			cjwdxx;							//次镜温度信息，来自温控   LSB=0.1℃ 仅传给调焦 

	UINT8			tem_ID;							//温度信息ID-1-10循环发送
	INT16			temp;							//温度值，LSB=0.1℃
	
	INT16			jmwz_kj_real;						//曝光时刻可见焦面位置LSB=0.001mm#
	INT16			jmwz_hw_real;						//曝光时刻红外焦面位置LSB=0.001mm#
	
	INT16     		kfssfybcwz;     						//快反实时俯仰补偿位置（LSB = 0.0001°)
	INT16     		kfssfwbcwz;     						//快反实时方位补偿位置（LSB = 0.01°/s)
	INT16     		kfbgskfybcwz;     					//快反曝光时刻俯仰补偿位置（LSB = 0.0001°)
	INT16     		kfbgskfwbcwz;     					//快反曝光时刻方位补偿位置（LSB = 0.0001°)
    	
	INT32    		rtime_pitch_frame;    		  		//框架实时俯仰角（LSB = 0.0001°)
	INT32     		rtime_direction_frame;         		//框架实时方位角（LSB = 0.0001°)
	
	
	//电源子系统状态字1
	UINT8			state_szgd:1;				//数字供电0：关 1：开
	UINT8			state_glgd:1;				//功率供电0：关 1：开
	UINT8			state_rkbjgd:1;				//热控供电本机：0：关 1：开
	UINT8			state_rkgcgd:1;				//热控供电光窗：0：关 1：开
	UINT8			state_baoliu:4;			//保留
	
	//电源子系统故障字1:故障位“1”表示存在，“0”表示不存在或消失
	UINT8			error1_kj:1;			//框架控制供电	
	UINT8			error1_jk:1;			//接口供电	
	UINT8			error1_txcl:1;			//图像处理供电	
	UINT8			error1_pcs:1;			//pcs供电	
	UINT8			error1_sjjl:1;			//数据记录供电	
	UINT8			error1_kjqd:1;			//框架驱动供电	
	UINT8			error1_tjqd:1;			//调焦驱动供电	
	UINT8			error1_bbqd:1;			//变倍驱动供电	
	
	//电源子系统故障字2:故障位“1”表示存在，“0”表示不存在或消失
	UINT8			error2_gsjqd:1;		//高速机驱动供电	
	UINT8			error2_baoliu1:1;		//保留
	UINT8			error2_rkbj:1;		//热控供电本机
	UINT8			error2_rkgc:1;		//热控供电光窗
	UINT8			error2_baoliu2:1;		//保留
	UINT8			error2_tem:1;		//温度传感器
	UINT8			error2_baoliu3:2;		//保留
	
	UINT8			power_tem;		//电源子系统温度LSB = 1
	
	
	
}MESS_FROMFC_JT_PHOTO;


//记录各功能单元的应用状态结构体
typedef struct Struct_V_NODE_APP_STATE
{
	APP_STATE app_state_V_NODE_IIPM;//IIPM/*	图像情报处理（可能后续会分为多个子应用）	*/
	APP_STATE app_state_V_NODE_DCLD;//DCLD/*	左数管单元	*/
	APP_STATE app_state_V_NODE_TMMM;//TMMM/*	战术管理处理单元	*/
	APP_STATE app_state_V_NODE_DCRM;//DCRM/*	右混合接口单元	*/
	APP_STATE app_state_V_NODE_DCLM;//DCLM/*	左混合接口单元	*/
	APP_STATE app_state_V_NODE_DCRD;//DCRD/*	右数管单元	*/
	APP_STATE app_state_V_NODE_SRMM;//SRMM/*	传感器任务管理单元	*/
	APP_STATE app_state_V_NODE_SYMM;//SYMM/*	系统管理单元	11*/
	APP_STATE app_state_V_NODE_MPHL;//MPHL/*	任务系统左健康管理单元	11*/
	APP_STATE app_state_V_NODE_MPHR;//MPHR/*	任务系统右健康管理单元	11*/
	APP_STATE app_state_V_NODE_SYMD;//SYMD/*	系统数据库单元	*/
}V_NODE_APP_STATE;

#pragma pack()
//------------------------------------内部使用结构体定义-------END------------------------------


// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_CONSTANT_DEFINE_H_ */
