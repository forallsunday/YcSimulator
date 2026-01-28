/*
 * YC_Controller_TG_Process.c
 *
 *  Created on: 2025年9月11日
 *      Author: wangx
 */

#include "YC_Controller_TG_Process.h"
#include "YC_Controller_FPGA_Mess.h"
#include "YC_Controller_Mess_Process.h"
#include "YC_Controller_globalVal_Ext.h"
// UINT32	ExpSig_cnt;
//-------------------------------调光用--------------------------------------------------------
// 调光变量初始化,25-7-20
void TG_VarInit() {
    UINT8 index1 = 0;
    //	ExpSig_cnt = 0;

    tg_Param.TG_WorkOrder = TG_CMD_None; // 调光工作指令
    tg_Param.Photo_Mode   = 1;           // 成像模式，1-广域成像，2-区域成像，3-区域监视
    //	tg_Param.JG_Mode = 1;					//检光模式，1-广域成像，2-区域成像，3-区域监视

    //	tg_Param.KJTCQ_JGConfig_Flag = 0;		//bit0
    //	tg_Param.HWTCQ_JGConfig_Flag = 0;		//bit1
    //	tg_Param.KJTCQ_JJConfig_Flag = 0;		//bit2
    //	tg_Param.KJImgGrads_Flag = 0;			//可见图像清晰度评价值更新标志位
    //	tg_Param.HWImgGrads_Flag = 0;			//红外图像清晰度评价值更新标志位
    //	tg_Param.TG_Condition_Update = 1;		//调光图像参数更新标志位
    //	tg_Param.HWJZ_SFWZ_State = 0;			//红外校正伺服到位信号
    //	tg_Param.HWRef_state = 1;
    tg_Param.HWTCQ_Ref_Switch   = 1; // 红外制冷机开关状态
    tg_Param.HWImg_Ply          = 0; // 红外图像极性，0-白热，1-黑热
    tg_Param.KJTCQ_InitConfig   = 0; // bit0 可见探测器初始化配置完成标志位
    tg_Param.HWTCQ_InitConfig   = 0; // bit1 红外探测器初始化配置完成标志位
    tg_Param.TCQ_InitConfig_Rdy = 0; // bit2 探测器初始化配置完成标志位

    tg_Param.TG_Collect_Allow = 0; // bit0 首次收到收藏指令标志位
    tg_Param.TG_CellBIT_Allow = 0; // bit1 首次收到自检指令标志位
    //	tg_Param.TG_KJselfFocus_Allow = 0;		//bit2 首次收到可见自准直检焦指令标志位
    //	tg_Param.TG_KJImgFocus_Allow = 0;		//bit3 首次收到可见图像检焦指令标志位
    //	tg_Param.TG_HWselfFocus_Allow = 0;		//bit4 首次收到红外自准直检焦指令标志位
    tg_Param.TG_Light_Allow            = 0; // bit5 首次收到检光指令标志位
    tg_Param.TG_HWJZ_Allow             = 0; // bit6 首次收到红外校正指令标志位
    tg_Param.TG_Wait_Allow             = 0; // bit7 首次收到待机指令标志位
    tg_Param.TG_GYCX_Allow             = 0; // bit0 首次收到广域成像指令标志位
    tg_Param.TG_QYCX_Allow             = 0; // bit1 首次收到区域成像指令标志位
    tg_Param.TG_QYJS_Allow             = 0; // bit2 首次收到区域监视指令标志位
    tg_Param.TG_PicLinkTestBegin_Allow = 0; // bit3 首次收到图像链路测试开始指令标志位
    tg_Param.TG_PicLinkTestEnd_Allow   = 0; // bit4 首次收到图像链路测试结束指令标志位
    tg_Param.TG_FlyFocus_Allow         = 0; // bit5 首次收到实景检焦指令标志位
    tg_Param.TG_StaticPhoto_Allow      = 0; // bit6 首次收到静态成像指令标志位
    tg_Param.TG_None_Allow             = 0; // bit7 首次收到空指令标志位

    // 调光控制参数
    //	tg_Param.KJJG_Completed = 4;					//可见检光结束标志位
    //	tg_Param.HWJG_Completed = 4;					//红外检光结束标志位

    tg_Param.KJimg_ValueTarget        = KJIMG_VALUETARGET_LAND;                      // 可见图像调光目标值
    tg_Param.KJimg_ValueLow           = KJIMG_VALUETARGET_LAND - KJIMG_TGVALUE_BAND; // 可见图像调光阈值下限
    tg_Param.KJimg_ValueHigh          = KJIMG_VALUETARGET_LAND + KJIMG_TGVALUE_BAND; // 可见图像调光阈值上限
    tg_Param.KJimg_ValueGZlow         = KJIMG_VALUEGZLOW;                            // 可见图像调光光照度过低值
    tg_Param.KJimg_ValueGZhigh        = KJIMG_VALUEGZHIGH;                           // 可见图像调光光照度过高值
    tg_Param.KJimg_ValueGZlow_cancel  = KJIMG_VALUEGZLOW_CANCEL;                     // 可见图像调光光照度过低取消值
    tg_Param.KJimg_ValueGZhigh_cancel = KJIMG_VALUEGZHIGH_CANCEL;                    // 可见图像调光光照度过高取消值
    tg_Param.HWimg_ValueTarget        = HWIMG_VALUETARGET;                           // 红外图像调光目标值
    tg_Param.HWimg_ValueLow           = HWIMG_VALUETARGET - HWIMG_TGVALUE_BAND;      // 红外图像调光阈值下限
    tg_Param.HWimg_ValueHigh          = HWIMG_VALUETARGET + HWIMG_TGVALUE_BAND;      // 红外图像调光阈值上限
    tg_Param.HWimg_ValueGZlow         = HWIMG_VALUEGZLOW;                            // 红外图像调光光照度过低值
    tg_Param.HWimg_ValueGZhigh        = HWIMG_VALUEGZHIGH;                           // 红外图像调光光照度过高值
    tg_Param.HWimg_ValueGZlow_cancel  = HWIMG_VALUEGZLOW_CANCEL;                     // 红外图像调光光照度过低取消值
    tg_Param.HWimg_ValueGZhigh_cancel = HWIMG_VALUEGZHIGH_CANCEL;                    // 红外图像调光光照度过高取消值

    tg_Param.KJGZHigh_Timer = 0; // 可见光照度过高次数计数器
    tg_Param.KJGZLow_Timer  = 0; // 可见光照度过低次数计数器
    tg_Param.HWGZHigh_Timer = 0; // 红外光照度过高次数计数器
    tg_Param.HWGZLow_Timer  = 0; // 红外光照度过低次数计数器
    //	tg_Param.KJTG_ENTIMER = 1;                //可见图像灰度超出阈值范围需要调光的准入次数，在调光和拍照设置
    //	tg_Param.HWTG_ENTIMER = 1;                //红外图像灰度超出阈值范围需要调光的准入次数，在调光和拍照设置
    tg_Param.KJTG_En_Timer = 0; // 可见调光准入次数
    tg_Param.HWTG_En_Timer = 0; // 红外调光准入次数

    // 工作参数
    tg_Param.KJ_ExpTime = 20; // 可见曝光时间
    //	tg_Param.KJ_ExpTime_float = 0.0;		//可见曝光时间
    //	tg_Param.KJImageSatuNum_float = 0.0;	//可见饱和像元数
    tg_Param.KJ_AGain      = 3;   // 可见模拟增益
    tg_Param.KJ_AGain_mtpl = 4.2; // 可见模拟增益
    //	tg_Param.KJ_ExpTime_Temp = 0;			//可见实景检焦曝光时间
    //	tg_Param.KJ_AGain_Temp = 0;			//可见实景检焦模拟增益
    //	tg_Param.KJsdtg_cnt_Done = 0;			//可见手动调光次数-已发送
    tg_Param.HW_ExpTime = 6000; // 红外积分时间
    //	tg_Param.HW_ExpTime_float = 0.0;		//红外积分时间
    tg_Param.HW_Gain = 1; // 红外增益
    tg_Param.HW_Coff = 9; // 红外校正系数
    //	tg_Param.KJ_ExpMultiply_float = 0.0;	//可见曝光倍数
    //	tg_Param.KJ_ExpTimeL8 = 0;				//可见曝光时间
    //	tg_Param.KJ_ExpTimeH8 = 0;				//可见曝光时间
    //	tg_Param.HW_ExpTimeL8 = 0;				//红外曝光时间
    //	tg_Param.HW_ExpTimeH8 = 0;				//红外曝光时间
    tg_Param.KJsdtg_cnt_Itr = 0; // 可见手动调光次数

    tg_Param.CoolingTime_EN = 1; // 红外制冷计时器使能
    tg_Param.CoolingTimeCnt = 0; // 红外制冷及探测器初始化计时
    //	tg_Param.HWTCQCorrectFlag = 0;    	//红外校正标志位
    //	tg_Param.JiaoZheng_TimeON = 0;    	//红外校正开始计时标志位
    //	tg_Param.CorrectTimeCnt = 0;      	//红外校正时间计数器
    //	tg_Param.HWJZ_SFWZ_WaitON = 0;			//红外校正等待伺服到位标志位
    //	tg_Param.HWJZ_SFWZ_WaitCnt = 0;			//红外校正等待伺服到位计数器
    //	tg_Param.FlyFocus_TGcnt = 0;			//实景检焦调光计时
    tg_Param.KJComErr       = 0; // 可见探测器通信内容错误标志位
    tg_Param.KJComErr_Timer = 0; // 可见探测器通信内容错误计时
    tg_Param.HWComErr       = 0; // 红外探测器通信内容错误标志位
    tg_Param.HWComErr_Timer = 0; // 红外探测器通信内容错误计时
    //	tg_Param.HWRef_state = 1;				//红外制冷机开关状态

    // 图像参数
    for (index1 = 0; index1 < 250; index1++) {
        tg_Param.KJImageGray[index1]    = 0x00; // 可见图像灰度均值数组
        tg_Param.HWImageGray[index1]    = 0x00; // 红外图像灰度均值数组
        tg_Param.KJImageSatuNum[index1] = 0x00; // 可见图像饱和像元数数组
    }
    //	tg_Param.KJImageGray_INDEX = 0;   		//可见图像灰度索引值
    //	tg_Param.HWImageGray_INDEX = 0;   		//红外图像灰度索引值
    //	tg_Param.KJImageSatuNum_INDEX = 0;       //可见灰度饱和像元数索引值
    //	tg_Param.KJImageGray_Mean = 0;				//读取可见图像灰度均值
    //	tg_Param.KJImageGray_MeanH = 0;				//读取可见图像灰度均值
    //	tg_Param.KJImageGray_MeanL = 0;				//读取可见图像灰度均值
    //	tg_Param.HWImageGray_Mean = 0;				//读取红外图像灰度均值
    //	tg_Param.HWImageGray_MeanH = 0;				//读取红外图像灰度均值
    //	tg_Param.HWImageGray_MeanL = 0;				//读取红外图像灰度均值
    //	tg_Param.KJImageSatuNum_Mean = 0;      	//可见图像饱和像元数
    //	tg_Param.KJImageSatuNum_MeanH = 0;      	//可见图像饱和像元数
    //	tg_Param.KJImageSatuNum_MeanL = 0;      	//可见图像饱和像元数
    tg_Param.KJImageGray_Value        = 0;    // 当前可见图像调光均值
    tg_Param.KJImageGray_Value_Last   = 2000; // 上一帧可见图像调光均值
    tg_Param.KJImageGray_Value_Update = 0;    // 可见图像调光均值更新标志位，0为可更新，1为不可更新
    tg_Param.HWImageGray_Value        = 0;    // 当前红外图像调光均值
    tg_Param.HWImageGray_Value_Last   = 8000; // 上一帧红外图像调光均值
    tg_Param.HWImageGray_Value_Update = 0;    // 红外图像调光均值更新标志位，0为可更新，1为不可更新
    tg_Param.KJImageSatuNum_Value     = 0;    // 当前可见图像饱和像元数值
    //	tg_Param.KJImageGrads = 0;        		//可见图像清晰度评价值
    //	tg_Param.KJImageGradsLL = 0;        		//可见图像清晰度评价值最低
    //	tg_Param.KJImageGradsLH = 0;        		//可见图像清晰度评价值次低
    //	tg_Param.KJImageGradsHL = 0;        		//可见图像清晰度评价值次高
    //	tg_Param.KJImageGradsHH = 0;        		//可见图像清晰度评价值最高
    //	tg_Param.HWImageGrads = 0;        		//红外图像清晰度评价值
    //	tg_Param.HWImageGradsH = 0;        		//红外图像清晰度评价值
    //	tg_Param.HWImageGradsL = 0;        		//红外图像清晰度评价值
    //	tg_Param.KJROI_RowBegin = 0;					//可见开窗行起始
    //	tg_Param.KJROI_RowResol = KJROWRESOL_IMG;		//可见开窗行分辨率
    //	tg_Param.KJROI_ColumBegin = 0;					//可见开窗列起始
    //	tg_Param.KJROI_ColumResol = KJCOLUMNRESOL_IMG;	//可见开窗列分辨率
    tg_Param.HWROI_RowBegin   = HWROWBEGIN_IMG;    // 红外开窗行起始
    tg_Param.HWROI_RowResol   = HWROWRESOL_IMG;    // 红外开窗行分辨率
    tg_Param.HWROI_ColumBegin = HWCOLUMNBEGIN_IMG; // 红外开窗列起始
    tg_Param.HWROI_ColumResol = HWCOLUMNRESOL_IMG; // 红外开窗列分辨率

    // 探测器状态和参数
    //	tg_Param.KJWorkMode = KJTCQ_WORKMODE_Pic;          //可见探测器工作模式
    //	tg_Param.KJImgTestMode = TCQ_Send_NULL;       	  //可见测试图像类型
    //	tg_Param.KJSyncMode = KJTCQ_TRIGMODE_OUT;          //可见同步方式变量
    //	tg_Param.KJInSyncFre = TCQ_Send_NULL;         	  //可见内触发帧频
    tg_Param.KJTurnMode = KJTCQ_IMAGE_VFlip; // 可见翻转方式
    //	tg_Param.KJROI_OutputType = KJTCQROI_OUTPUTIMG;		  //可见开窗输出类型
    //	tg_Param.KJTCQTemp_Pos = KJTCQ_TempSensor;			  //可见探测器温度位置
    //	tg_Param.KJImgGray_Type = KJTCQ_GET_GrayMean;		  //可见图像灰度类型
    //	tg_Param.HWWorkMode = HWTCQ_WORKMODE_Pic;          //红外探测器工作模式
    //	tg_Param.HWImgTestMode = TCQ_Send_NULL;       	  //红外测试图像类型
    //	tg_Param.HWSyncMode = HWTCQ_TRIGMODE_OUT;          //红外同步方式变量
    //	tg_Param.HWInSyncFre = TCQ_Send_NULL;         	  //红外内触发帧频
    tg_Param.HWTurnMode = HWTCQ_IMAGE_HVFlip; // 红外翻转方式
    //	tg_Param.HWImg_Plty = HWTCQ_PolarityWhite;			  //红外图像极性
    //	tg_Param.HWTCQTemp_Pos = HWTCQ_SensorTemp;			  //红外探测器温度位置
    //	tg_Param.HWROI_OutputType = HWTCQROI_ITPLIMG;			//可见开窗输出类型

    tg_Param.KJTCQ_Cmd = TCQ_Send_NULL; // 给可见探测器发送的指令
    tg_Param.HWTCQ_Cmd = TCQ_Send_NULL; // 给红外探测器发送的指令
    //	tg_Param.KJCOMCNT_Flag = 0;				//可见通讯内容标志位
    //	tg_Param.HWCOMCNT_Flag = 0;				//红外通讯内容标志位
    //	tg_Param.SendKJTime_EN = 0;        	//监视下向可见探测器发送曝光时间等待使能
    //	tg_Param.SendKJTime_cnt = 0;       	//监视下向可见探测器发送曝光时间等待时间计数器
    //	tg_Param.SendKJGain_EN = 0;        	//监视下向可见探测器发送增益等待使能
    //	tg_Param.SendKJGain_cnt = 0;       	//监视下向可见探测器发送增益等待时间计数器
    //	tg_Param.SendKJRmm_EN = 0;			//向可见探测器发送去雾等待使能
    //	tg_Param.SendKJRmm_cnt = 0;			//向可见探测器发送去雾等待时间计数器
    //	tg_Param.SendKJEhc_EN = 0;			//向可见探测器发送增强等待使能
    //	tg_Param.SendKJEhc_cnt = 0;			//向可见探测器发送增强等待时间计数器
    //	tg_Param.SendHWTime_EN = 0;        	//监视下向红外探测器发送曝光时间等待使能
    //	tg_Param.SendHWTime_cnt = 0;       	//监视下向红外探测器发送曝光时间等待时间计数器
    //	tg_Param.SendHWGain_EN = 0;				//监视下向红外探测器发送增益等待使能
    //	tg_Param.SendHWGain_cnt = 0;			//监视下向红外探测器发送增益等待时间计数器
    tg_Param.KJSendCmd_cnt    = 0; // 向可见发送指令次数计数器
    tg_Param.HWSendCmd_cnt    = 0; // 向红外发送指令次数计数器
    tg_Param.KJRecMsg_TimerON = 0; // 接收可见探测器反馈消息计时使能
    tg_Param.KJRecMsg_Timer   = 0; // 接收可见探测器反馈消息计时
    tg_Param.HWRecMsg_TimerON = 0; // 接收红外探测器反馈消息计时使能
    tg_Param.HWRecMsg_Timer   = 0; // 接收红外探测器反馈消息计时

    //	tg_Param.KJJS_SDWZ_Sig = 0;			//可见监视下速度位置信号
    //	tg_Param.HWJS_SDWZ_Sig = 0;			//红外监视下速度位置信号

    // 从主控接收指令及参数
    mess_To_TG.Control_Cmd = TG_CMD_None; // 命令字
    //	mess_To_TG.KJTG_Mode = 0x00;		//调光条件
    //	mess_To_TG.JG_Mode = 0x00;		//调光条件
    mess_To_TG.TargetType = 0; // 调光条件
    //	mess_To_TG.HWJZ_SFWZ_State = 0x00;		//调光条件
    //	mess_To_TG.KJExpTime_Rec = 0;			//可见曝光时间设定值
    //	mess_To_TG.KJTCQAGain_Rec = 0;			//可见探测器模拟增益设定值
    //	mess_To_TG.HWExpTime_Rec = 0;			//红外积分时间设定值
    //	mess_To_TG.HWTCQGain_Rec = 0x00;		//红外探测器增益设定值
    //	mess_To_TG.XJ_SlopeMode_Rec = 0;		//设备倾斜方式
    //	mess_To_TG.HWROI_RowBegin_Rec = 0;		//红外开窗行起始
    //	mess_To_TG.HWROI_ColBegin_Rec = 0;		//红外开窗列起始
    //	mess_To_TG.KJsdtg_cnt = 0;				//可见手动调光次数
    //	mess_To_TG.HWTCQ_Ref_Switch = 1;			//红外制冷机状态
    //	mess_To_TG.HWImg_Ply = 0;					//红外图像黑白热
    // 调光工作状态字
    //	mess_From_TG.KJTG_Mode_back = 0;			//0-可见自动调光,1-可见手动调光
    //	mess_From_TG.HWTG_Mode_back = 0;			//0-红外自动调光,1-红外手动调光
    mess_From_TG.Cool_state = 0; // 0-正在制冷，1-制冷到温
    //	mess_From_TG.HWRef_state_back = 1;		//0-制冷机关闭，1-制冷机开启
    //	mess_From_TG.KJGradsCalc_state = 0;	//00-未开始计算，01-正在计算，02-计算完成
    //	mess_From_TG.HWGradsCalc_state = 0;	//00-未开始计算，01-正在计算，02-计算完成
    //	mess_From_TG.JianGuang = 0;			//00-检光未开始，01-正在检光，02-检光完成
    //	mess_From_TG.HWJiaoZheng = 0;		//00-校正未开始，01-正在校正，02-校正完成
    //	mess_From_TG.JianJiao_state = 0;		//00-检焦未开始，01-正在检焦，02-检焦完成
    //	mess_From_TG.FlyFocus_state = 0;		//00-检焦未开始，01-正在检焦，02-检焦完成
    //	mess_From_TG.SelfTest = 0;			//00-自检未开始，01-正在自检，02-自检完成
    //	mess_From_TG.FlyFocus_TGState = 0;		//00-调光未开始，01-正在调光，02-调光完成
    //	mess_From_TG.Photo_state = 0;		//0-未拍照，1-拍照
    mess_From_TG.Tuce_state = 0; // 0-停止图像链路测试，1-正在进行图像链路测试
    //	mess_From_TG.HWImg_Ply_back = 0;		//0-红外图像白热，1-红外图像黑热
    mess_From_TG.TCQInit_Flag = 0; // 0-探测器初始化未完成，1-探测器初始化完成

    // 调光故障字
    mess_From_TG.KJTCQ_Error       = 0; // 可见探测器通讯内容异常
    mess_From_TG.HWTCQ_Error       = 0; // 红外探测器通讯内容异常
    mess_From_TG.KJGZD_HighError   = 0; // 可见光照度过高
    mess_From_TG.KJGZD_LowError    = 0; // 可见光照度过低
    mess_From_TG.HWGZD_HighError   = 0; // 红外光照度过高
    mess_From_TG.HWGZD_LowError    = 0; // 红外光照度过低
    mess_From_TG.HW_Coolling_Error = 0; // 红外探测器制冷异常

    // 调光反馈状态
    mess_From_TG.KJ_AGain_back = 3; // 反馈模拟增益
    mess_From_TG.HW_Gain_back  = 1; // 反馈红外探测器增益
    //	mess_From_TG.KJImg_TurnMode_back = 0;			//可见图像翻转方式
    //	mess_From_TG.HWImg_TurnMode_back = 0;			//红外图像翻转方式
    mess_From_TG.KJExpTime_back = 20; // 反馈可见探测器曝光时间
    mess_From_TG.HWExpTime_back = 60; // 反馈红外探测器积分时间
    mess_From_TG.HW_Coff_back   = 9;  // 反馈红外系数
    //	mess_From_TG.TargetType = 0;					//气溶胶类型
    mess_From_TG.KJTCQ_Temp = 20;  // 可见探测器温度
    mess_From_TG.HWTCQ_Temp = 200; // 红外探测器温度
    //	mess_From_TG.KJImgGray_Mean_back = 0;			//可见图像灰度均值
    //	mess_From_TG.HWImgGray_Mean_back = 0;			//红外图像灰度均值
    //	mess_From_TG.KJ_WorkState1 = 0x00;				//可见工作状态1
    //	mess_From_TG.KJ_WorkState2 = 0x00;				//可见工作状态2
    //	mess_From_TG.HW_WorkState1 = 0x00;				//红外工作状态1
    //	mess_From_TG.HW_WorkState2 = 0x00;				//红外工作状态2
    //	mess_From_TG.HW_SelfTestState1 = 0x00;			//红外自检状态1
    //	mess_From_TG.HW_SelfTestState2 = 0x00;			//红外自检状态1
}

// 调光参数初始化
void TGParam_Init() {
    tg_Param.KJSendCmd_cnt        = 0; // 向可见发送指令次数计数器
    tg_Param.HWSendCmd_cnt        = 0; // 向红外发送指令次数计数器
    tg_Param.KJRecMsg_TimerON     = 0; // 接收可见探测器反馈消息计时使能
    tg_Param.KJRecMsg_Timer       = 0; // 接收可见探测器反馈消息计时
    tg_Param.HWRecMsg_TimerON     = 0; // 接收红外探测器反馈消息计时使能
    tg_Param.HWRecMsg_Timer       = 0; // 接收红外探测器反馈消息计时
    tg_Param.SendKJTime_EN        = 0; // 监视下向可见探测器发送曝光时间等待使能
    tg_Param.SendKJTime_cnt       = 0; // 监视下向可见探测器发送曝光时间等待时间计数器
    tg_Param.SendKJGain_EN        = 0; // 监视下向可见探测器发送增益等待使能
    tg_Param.SendKJGain_cnt       = 0; // 监视下向可见探测器发送增益等待时间计数器
    tg_Param.SendKJRmm_EN         = 0; // 向可见探测器发送去雾等待使能
    tg_Param.SendKJRmm_cnt        = 0; // 向可见探测器发送去雾等待时间计数器
    tg_Param.SendKJEhc_EN         = 0; // 向可见探测器发送增强等待使能
    tg_Param.SendKJEhc_cnt        = 0; // 向可见探测器发送增强等待时间计数器
    tg_Param.SendHWTime_EN        = 0; // 监视下向红外探测器发送曝光时间等待使能
    tg_Param.SendHWTime_cnt       = 0; // 监视下向红外探测器发送曝光时间等待时间计数器
    tg_Param.SendHWGain_EN        = 0; // 监视下向红外探测器发送增益等待使能
    tg_Param.SendHWGain_cnt       = 0; // 监视下向红外探测器发送增益等待时间计数器
    tg_Param.SendHWPly_EN         = 0; // 拍照时向红外发送黑白热等待使能
    tg_Param.SendHWPly_cnt        = 0; // 拍照时向红外发送黑白热等待计数器
    tg_Param.SendHWFilter_EN      = 0; // 拍照时向红外发送滤波等待使能
    tg_Param.SendHWFilter_cnt     = 0; // 拍照时向红外发送滤波等待计数器
    tg_Param.SendHWEhc_EN         = 0; // 拍照时向红外发送增强等待使能
    tg_Param.SendHWEhc_cnt        = 0; // 拍照时向红外发送增强等待计数器
    tg_Param.KJImageGray_INDEX    = 0;
    tg_Param.KJImageSatuNum_INDEX = 0;
    tg_Param.HWImageGray_INDEX    = 0;
    tg_Param.KJTG_Count           = 0;
    tg_Param.HWTG_Count           = 0;
    tg_Param.KJJS_SDWZ_Sig        = 0; // 可见监视下速度位置信号
    tg_Param.HWJS_SDWZ_Sig        = 0; // 红外监视下速度位置信号

    tg_Param.KJTG_GetGray_EN          = 0; // 可见读取灰度完成标志位
    tg_Param.HWTG_GetGray_EN          = 0; // 红外读取灰度完成标志位
    tg_Param.KJTG_Anal_EN             = 0; // 可见调光分析使能
    tg_Param.HWTG_Anal_EN             = 0; // 红外调光分析使能
    tg_Param.KJTG_Calc_EN             = 0; // 可见调光计算使能
    tg_Param.HWTG_Calc_EN             = 0; // 红外调光计算使能
    tg_Param.KJ_TimeCntFromExpPule_EN = 0; // 可见距离曝光开始时刻的时间计数使能
    tg_Param.HW_TimeCntFromExpPule_EN = 0; // 红外距离曝光开始时刻的时间计数使能
    //	tg_Param.KJ_TimeCntFromExpPule = 0;       	//可见距离曝光开始时刻计时
    //	tg_Param.HW_TimeCntFromExpPule = 0;       	//红外距离曝光开始时刻计时

    tg_Param.TGZJStart_Flag = 0; // 调光自检开始标志位
    tg_Param.TGZJTimer_cnt  = 0; // 调光自检定时计数器
}
// 探测器初始化,25-9-21
void TCQ_Configure() {
    if ((tg_Param.KJTCQ_InitConfig == 1) && (tg_Param.HWTCQ_InitConfig == 1)) {
        tg_Param.TCQ_InitConfig_Rdy = 1;
        mess_From_TG.TCQInit_Flag   = 1;
    }
    if ((tg_Param.CoolingTimeCnt > TCQINITTIME) && (tg_Param.TCQ_InitConfig_Rdy == 0)) {
        if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器成像模式
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_WorkMode, KJTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_WorkMode);
                //                tg_Param.KJWorkMode=KJTCQ_WORKMODE_Pic;
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.KJSendCmd_cnt) // 配置可见图像翻转
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ImagState, tg_Param.KJTurnMode, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_ImagState);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 2, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 2, 0, 0);
                }
            }
        } else if (2 == tg_Param.KJSendCmd_cnt) // 配置可见8bit
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_OutBitSet, KJTCQ_IMG8Bit, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_OutBitSet);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 3, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 3, 0, 0);
                }
            }
        } else if (3 == tg_Param.KJSendCmd_cnt) // 配置可见探测器外触发
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_TrigMode, KJTCQ_TRIGMODE_OUT, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_TrigMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 4, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 4, 0, 0);
                }
            }
        } else if (4 == tg_Param.KJSendCmd_cnt) // 配置可见探测器手动曝光
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpMode, KJTCQ_EXPMODE_MANUAL, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_ExpMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 5, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 5, 0, 0);
                }
            }
        } else if (5 == tg_Param.KJSendCmd_cnt) // 配置可见探测器十字丝开关
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_CrossCurse, KJTCQ_CRSCUS_DIS, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_CrossCurse);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 6, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 6, 0, 0);
                }
            }
        } else if (6 == tg_Param.KJSendCmd_cnt) // 配置可见探测器曝光时间2ms
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
                tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
                SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 7, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 7, 0, 0);
                }
            }
        } else if (7 == tg_Param.KJSendCmd_cnt) // 配置可见模拟增益
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 8, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 8, 0, 0);
                }
            }
        } else // 空指令
        {
            make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.KJTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.KJTCQ_InitConfig = 1;
        }
        if (0 == tg_Param.HWSendCmd_cnt) // 配置红外探测器成像模式
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_WorkMode, HWTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.HWSendCmd_cnt) // 设置红外图像翻转
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImagDir, tg_Param.HWTurnMode, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_ImagDir);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 2, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 2, 0, 0);
                }
            }
        } else if (2 == tg_Param.HWSendCmd_cnt) // 设置红外有效位宽8bit
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_BandWidth, HWTCQ_ImgBandWidth8, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_BandWidth);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 3, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 3, 0, 0);
                }
            }
        } else if (3 == tg_Param.HWSendCmd_cnt) // 设置红外开窗-行起始
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_RowBegin, tg_Param.HWROI_RowBegin & 0x00FF, (tg_Param.HWROI_RowBegin >> 8) & 0x00FF);
                SendHWTCQ_Param(HWTCQ_CMD_RowBegin);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 4, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 4, 0, 0);
                }
            }
        } else if (4 == tg_Param.HWSendCmd_cnt) // 设置红外开窗-行分辨率
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_RowResol, tg_Param.HWROI_RowResol & 0x00FF, (tg_Param.HWROI_RowResol >> 8) & 0x00FF);
                SendHWTCQ_Param(HWTCQ_CMD_RowResol);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 5, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 5, 0, 0);
                }
            }
        } else if (5 == tg_Param.HWSendCmd_cnt) // 设置红外开窗-列起始
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ColBegin, tg_Param.HWROI_ColumBegin & 0x00FF, (tg_Param.HWROI_ColumBegin >> 8) & 0x00FF);
                SendHWTCQ_Param(HWTCQ_CMD_ColBegin);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 6, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 6, 0, 0);
                }
            }
        } else if (6 == tg_Param.HWSendCmd_cnt) // 设置红外开窗-列分辨率
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ColResol, tg_Param.HWROI_ColumResol & 0x00FF, (tg_Param.HWROI_ColumResol >> 8) & 0x00FF);
                SendHWTCQ_Param(HWTCQ_CMD_ColResol);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 7, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 7, 0, 0);
                }
            }
        } else if (7 == tg_Param.HWSendCmd_cnt) // 设置红外开窗-使能
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgROIEnable, HWTCQROI_ITPLIMG, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_ImgROIEnable);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 8, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 8, 0, 0);
                }
            }
        } else if (8 == tg_Param.HWSendCmd_cnt) // 红外外同步
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_TrigMode, HWTCQ_TRIGMODE_OUT, HWTCQ_TRIGMODE_OUT);
                SendHWTCQ_Param(HWTCQ_CMD_TrigMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 9, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 9, 0, 0);
                }
            }
        } else if (9 == tg_Param.HWSendCmd_cnt) // 红外制冷机开
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_Refrig, tg_Param.HWTCQ_Ref_Switch, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_Refrig);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 10, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 10, 0, 0);
                }
            }
        } else if (10 == tg_Param.HWSendCmd_cnt) // 红外图像白热
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPolarity, tg_Param.HWImg_Ply, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_ImgPolarity);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 11, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 11, 0, 0);
                }
            }
        } else if (11 == tg_Param.HWSendCmd_cnt) // 红外图像十字丝开关
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_CrsCurs, HWTCQ_CRSCURS_OFF, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_CrsCurs);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 12, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 12, 0, 0);
                }
            }
        } else if (12 == tg_Param.HWSendCmd_cnt) // 设置红外积分时间
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                tg_Param.HW_ExpTimeL8 = tg_Param.HW_ExpTime & 0x00FF;
                tg_Param.HW_ExpTimeH8 = (tg_Param.HW_ExpTime >> 8) & 0x00FF;
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ExpTimeSet, tg_Param.HW_ExpTimeL8, tg_Param.HW_ExpTimeH8);
                SendHWTCQ_Param(HWTCQ_CMD_ExpTimeSet);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 13, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 13, 0, 0);
                }
            }
        } else if (13 == tg_Param.HWSendCmd_cnt) // 设置红外增益
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 14, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 14, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.HWTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.HWTCQ_InitConfig = 1;
        }
    }
}

// 红外制冷判断,25-9-22
void HWTCQ_CoolingJudge() {
    if (1 == tg_Param.TCQ_InitConfig_Rdy) {
        if (0 == mess_From_TG.HWRef_state_back) // 制冷机关闭
        {
            tg_Param.CoolingTime_EN        = 0; // 红外制冷计时器使能
            tg_Param.CoolingTimeCnt        = 0; // 红外制冷及探测器初始化计时
            mess_From_TG.Cool_state        = 0;
            mess_From_TG.HW_Coolling_Error = 0;
        } else // 制冷机打开
        {
            tg_Param.CoolingTime_EN = 1;
            if ((mess_From_TG.HW_WorkState2 & 0x06) == 0x06) {
                mess_From_TG.Cool_state        = 0;
                mess_From_TG.HW_Coolling_Error = 1;
            }
            if (tg_Param.CoolingTimeCnt >= COOLINGTIMEOVER) // 制冷时间超过10min
            {
                mess_From_TG.Cool_state        = 0;
                mess_From_TG.HW_Coolling_Error = 1; // 上报红外探测器制冷故障
            } else                                  // 制冷未超时
            {
                if ((mess_From_TG.HW_WorkState2 & 0x06) == 0x04) // 正常制冷结束
                {
                    mess_From_TG.Cool_state        = 1;
                    mess_From_TG.HW_Coolling_Error = 0;
                }
            }
        }
    }
}

// 调光故障判断,25-7-21
void TG_ErrCheck() {
    // 探测器通讯内容错误判断
    if (tg_Param.KJComErr_Timer >= TCQCOM_ERR) {
        mess_From_TG.KJTCQ_Error = 1;
    } else {
        mess_From_TG.KJTCQ_Error = 0;
    }
    if (tg_Param.HWComErr_Timer >= TCQCOM_ERR) {
        mess_From_TG.HWTCQ_Error = 1;
    } else {
        mess_From_TG.HWTCQ_Error = 0;
    }
    /*
//红外制冷故障判断
    if((mess_From_TG.HW_WorkState2 & 0x06) == 0x06)	//制冷故障
    {
            mess_From_TG.HW_Coolling_Error=1;
            mess_From_TG.HWRef_state_back=1;
    }
    else if((mess_From_TG.HW_WorkState2 & 0x06) == 0x04)    //制冷正常
    {
            mess_From_TG.HW_Coolling_Error=0;
            mess_From_TG.HWRef_state_back=1;
    }
    else if((mess_From_TG.HW_WorkState2 & 0x06) == 0x02)	//制冷未到温
    {
            if(tg_Param.CoolingTimeCnt>=COOLINGTIMEOVER)
            {
                    mess_From_TG.HW_Coolling_Error=1;
                    mess_From_TG.HWRef_state_back=1;
            }
            else
            {
                    mess_From_TG.HW_Coolling_Error=0;
                    mess_From_TG.HWRef_state_back=1;
            }
    }
    else		//制冷机未上电
    {
            mess_From_TG.HW_Coolling_Error=0;
            mess_From_TG.HWRef_state_back=0;
    }
    */
    // 光照度过高过低判断
    if (tg_Param.KJGZHigh_Timer >= 3) {
        mess_From_TG.KJGZD_HighError = 1; // 上报光照度过高故障
        mess_From_TG.KJGZD_LowError  = 0; // 取消光照度过低故障
        tg_Param.KJGZHigh_Timer      = 3;
    } else {
        mess_From_TG.KJGZD_HighError = 0; // 取消光照度过高故障
    }
    if (tg_Param.KJGZLow_Timer >= 3) {
        mess_From_TG.KJGZD_HighError = 0; // 取消光照度过高故障
        mess_From_TG.KJGZD_LowError  = 1; // 上报光照度过低故障
        tg_Param.KJGZLow_Timer       = 3;
    } else {
        mess_From_TG.KJGZD_LowError = 0; // 取消光照度过低故障
    }
    if (tg_Param.HWGZHigh_Timer >= 3) {
        mess_From_TG.HWGZD_HighError = 1; // 报光照度过高故障
        mess_From_TG.HWGZD_LowError  = 0; // 取消光照度过低故障
        tg_Param.HWGZHigh_Timer      = 3;
    } else {
        mess_From_TG.HWGZD_HighError = 0; // 取消光照度过高故障
    }
    if (tg_Param.HWGZLow_Timer >= 3) {
        mess_From_TG.HWGZD_HighError = 0; // 取消光照度过高故障
        mess_From_TG.HWGZD_LowError  = 1; // 上报光照度过低故障
        tg_Param.HWGZLow_Timer       = 3;
    } else {
        mess_From_TG.HWGZD_LowError = 0; // 取消光照度过低故障
    }
}

// 5ms定时调光处理,25-9-22
void TG_5msInterrupt() {
    /*
//读取图像参数计时
    if((tg_Param.KJ_TimeCntFromExpPule<TCQ_READPARAM_DELAYMAX)&&(tg_Param.KJ_TimeCntFromExpPule_EN == 1))
    {
            tg_Param.KJ_TimeCntFromExpPule++;
    }
    if((tg_Param.HW_TimeCntFromExpPule<TCQ_READPARAM_DELAYMAX)&&(tg_Param.HW_TimeCntFromExpPule_EN == 1))
    {
            tg_Param.HW_TimeCntFromExpPule++;
    }
    */
    /*
//向探测器发送消息等待时间计时
if((tg_Param.SendKJTime_EN == 1)&&(tg_Param.SendKJTime_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendKJTime_cnt ++;
}
if((tg_Param.SendKJGain_EN==1)&&(tg_Param.SendKJGain_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendKJGain_cnt ++;
}
if((tg_Param.SendKJRmm_EN==1)&&(tg_Param.SendKJRmm_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendKJRmm_cnt ++;
}
if((tg_Param.SendKJEhc_EN==1)&&(tg_Param.SendKJEhc_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendKJEhc_cnt ++;
}
if((tg_Param.SendHWTime_EN==1)&&(tg_Param.SendHWTime_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendHWTime_cnt ++;
}
if((tg_Param.SendHWGain_EN==1)&&(tg_Param.SendHWGain_cnt<=(SEND_TCQTIME_JS+10)))
{
    tg_Param.SendHWGain_cnt ++;
}
*/
    // 等待探测器反馈消息时间计时
    if ((tg_Param.KJRecMsg_Timer < (TCQCOM_WAITTIME_MAX + 5)) && (tg_Param.KJRecMsg_TimerON == 1)) {
        tg_Param.KJRecMsg_Timer++;
    }
    if ((tg_Param.HWRecMsg_Timer < (TCQCOM_WAITTIME_MAX + 5)) && (tg_Param.HWRecMsg_TimerON == 1)) {
        tg_Param.HWRecMsg_Timer++;
    }
    // 红外制冷计时
    if ((tg_Param.CoolingTime_EN == 1) && (tg_Param.CoolingTimeCnt <= (UINT32)(COOLINGTIMEOVER + 10)) && (mess_From_TG.Cool_state != 1)) {
        tg_Param.CoolingTimeCnt++;
    }
    // 红外校正时间
    if ((tg_Param.JiaoZheng_TimeON == 1) && (tg_Param.CorrectTimeCnt < (HWJZ_TIMEOUT + 10))) {
        tg_Param.CorrectTimeCnt++;
    }
    // 红外校正等待伺服到位时间
    if ((tg_Param.HWJZ_SFWZ_WaitON == 1) && (tg_Param.HWJZ_SFWZ_WaitCnt < (HWJZ_SFWZ_TIMEOUT + 10))) {
        tg_Param.HWJZ_SFWZ_WaitCnt++;
    }
    // 调光自检时间
    if ((tg_Param.TGZJStart_Flag == 1) && (tg_Param.TGZJTimer_cnt < (TGSELFTEST_TIMEOUT + 10))) {
        tg_Param.TGZJTimer_cnt++;
    }
    /*
        //实景检焦可见调光时间计数
        if((mess_From_TG.FlyFocus_TGState==1)&&(tg_Param.FlyFocus_TGcnt<=(FLYFOCUS_TGTIMEOUT+10)))
        {
            tg_Param.FlyFocus_TGcnt ++;
        }
    */
    // 探测器通信内容错误报故判断
    if ((tg_Param.KJComErr == 1) && (tg_Param.KJComErr_Timer <= (TCQCOM_ERR + 10))) {
        tg_Param.KJComErr_Timer++;
    } else {
        if (0 == tg_Param.KJComErr) {
            tg_Param.KJComErr_Timer = 0;
        }
    }
    if ((tg_Param.HWComErr == 1) && (tg_Param.HWComErr_Timer <= (TCQCOM_ERR + 10))) {
        tg_Param.HWComErr_Timer++;
    } else {
        if (0 == tg_Param.HWComErr) {
            tg_Param.HWComErr_Timer = 0;
        }
    }
}

// 内部采集信号中断调光处理，在内部采集信号中断中调用,25-9-20
void TG_NBCJInterrupt() {
    if ((0 == tg_Param.KJJS_SDWZ_Sig) || (0 == SIG_SDWZ)) {
        tg_Param.KJ_TimeCntFromExpPule_EN = 1; // 读取图像参数
        //		tg_Param.KJ_TimeCntFromExpPule=0;
        tg_Param.KJRecMsg_TimerON = 0; // 与探测器通讯接收
        tg_Param.KJRecMsg_Timer   = 0;
        tg_Param.KJTG_GetGray_EN  = 0; // 监视用
        tg_Param.KJTG_Count++;
    }
    if ((0 == tg_Param.HWJS_SDWZ_Sig) || (0 == SIG_SDWZ)) {
        tg_Param.HW_TimeCntFromExpPule_EN = 1;
        //		tg_Param.HW_TimeCntFromExpPule=0;
        tg_Param.HWRecMsg_TimerON = 0;
        tg_Param.HWRecMsg_Timer   = 0;
        tg_Param.HWTG_GetGray_EN  = 0;
        tg_Param.HWTG_Count++;
    }
}

// 收藏调光处理,25-9-21
void TG_ShouCang() {
    if (tg_Param.TG_Collect_Allow == 1) {
        tg_Param.TG_Collect_Allow = 0;
        TGParam_Init();
        TG_State_Flag(0, 0, 0, 0, 0);
    } else {
        TGCondition();
        if (0 == tg_Param.KJSendCmd_cnt) // 读取可见探测器温度
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetTemp, KJTCQ_TempSensor, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_GetTemp);
                tg_Param.KJTCQTemp_Pos = KJTCQ_TempSensor;
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 0, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 0, 0, 0);
                }
            }
        }
        if (tg_Param.HWSendCmd_cnt == 0) // 红外制冷机开关
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_Refrig, tg_Param.HWTCQ_Ref_Switch, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_Refrig);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else // 读取红外探测器温度
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetTemp, HWTCQ_SensorTemp, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_GetTemp);
                tg_Param.HWTCQTemp_Pos = HWTCQ_SensorTemp;
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                        if (mess_From_TG.HWRef_state_back != tg_Param.HWTCQ_Ref_Switch) {
                            RecHWTCQ_Param(0, 0, 0, 0);
                        }
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                    if (mess_From_TG.HWRef_state_back != tg_Param.HWTCQ_Ref_Switch) {
                        RecHWTCQ_Param(1, 0, 0, 0);
                    }
                }
            }
        }
    }
}

// 待机调光处理,25-10-3
void TG_Wait() {
    if (tg_Param.TG_Wait_Allow == 1) {
        tg_Param.TG_Wait_Allow = 0;
        TGParam_Init();
        mess_From_TG.KJImg_TurnConfig_Flag = 0; // 可见翻转设置成功标志位
        mess_From_TG.HWImg_TurnConfig_Flag = 0; // 红外翻转设置成功标志位
        TG_State_Flag(0, 0, 0, 0, 0);
    } else {
        TGCondition();

        if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器去雾
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ReMoveMist, tg_Param.KJImg_ReMoveMist, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_ReMoveMist);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.KJSendCmd_cnt) // 配置可见探测器增强
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_IMGEnHance, tg_Param.KJImg_EnHance, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_IMGEnHance);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 2, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 2, 0, 0);
                }
            }
        } else if (2 == tg_Param.KJSendCmd_cnt) // 配置可见探测器曝光时间
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
                tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
                SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 3, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 3, 0, 0);
                }
            }
        } else if (3 == tg_Param.KJSendCmd_cnt) // 配置可见图像翻转
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ImagState, tg_Param.KJTurnMode, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_ImagState);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 4, 0, 0);
                        mess_From_TG.KJImg_TurnConfig_Flag = 1;
                    }
                } else {
                    RecKJTCQ_Param(1, 4, 0, 0);
                    //					mess_From_TG.KJImg_TurnConfig_Flag = 1;
                }
            }
        } else // 读取可见探测器温度
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetTemp, KJTCQ_TempSensor, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_GetTemp);
                tg_Param.KJTCQTemp_Pos = KJTCQ_TempSensor;
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 0, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 0, 0, 0);
                }
            }
        }
        if (0 == tg_Param.HWSendCmd_cnt) // 配置红外图像黑白热
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPolarity, tg_Param.HWImg_Ply, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_ImgPolarity);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                        //						mess_From_TG.HWImg_Ply_back = tg_Param.HWImg_Ply;
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.HWSendCmd_cnt) // 配置红外图像增强
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, tg_Param.HWImg_EnHance, HWTCQ_DDE);
                SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 2, 0, 0);
                        //						mess_From_TG.HWImg_EnHance_back = tg_Param.HWImg_EnHance;
                    }
                } else {
                    RecHWTCQ_Param(1, 2, 0, 0);
                }
            }
        } else if (tg_Param.HWSendCmd_cnt == 2) // 红外制冷机开关
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_Refrig, tg_Param.HWTCQ_Ref_Switch, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_Refrig);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 3, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 3, 0, 0);
                }
            }
        } else if (3 == tg_Param.HWSendCmd_cnt) // 设置红外图像翻转
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImagDir, tg_Param.HWTurnMode, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_ImagDir);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 4, 0, 0);
                        mess_From_TG.HWImg_TurnConfig_Flag = 1;
                    }
                } else {
                    RecHWTCQ_Param(1, 4, 0, 0);
                    //					mess_From_TG.HWImg_TurnConfig_Flag = 1;
                }
            }
        } else // 读取红外探测器温度
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetTemp, HWTCQ_SensorTemp, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_GetTemp);
                tg_Param.HWTCQTemp_Pos = HWTCQ_SensorTemp;
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 0, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 0, 0, 0);
                }
            }
        }
    }
}

// 红外校正调光处理,25-9-21
void HW_JiaoZheng() {
    if (tg_Param.TG_HWJZ_Allow == 1) {
        TGParam_Init();
        tg_Param.TG_HWJZ_Allow     = 0;
        tg_Param.JiaoZheng_TimeON  = 0;
        tg_Param.CorrectTimeCnt    = 0;
        tg_Param.HWTCQCorrectFlag  = 0;
        tg_Param.HWJZ_SFWZ_WaitON  = 1; // 红外校正等待伺服到位标志位
        tg_Param.HWJZ_SFWZ_WaitCnt = 0; // 红外校正等待伺服到位计数器
        //		HWTCQCOEF_ChsKv();
        HWTCQCOEF_ChsHy();
        TG_State_Flag(0, 1, 0, 0, 0);
    } else {
        if ((mess_From_TG.HW_Coolling_Error == 1) || (mess_From_TG.Cool_state == 0) || (mess_From_TG.HWRef_state_back == 0)) // 红外制冷故障或制冷中或制冷机关闭跳出校正
        {
            tg_Param.HWTCQCorrectFlag = 2;
        }
        if (tg_Param.HWTCQCorrectFlag == 0) {
            if ((mess_From_TJ.status2_jzb_dw == 1) || (tg_Param.HWJZ_SFWZ_WaitCnt > HWJZ_SFWZ_TIMEOUT)) // 检焦或伺服到达校正位置
            {
                if (0 == tg_Param.HWRecMsg_TimerON) {
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_SPCorrect, tg_Param.HW_Coff, tg_Param.HW_Coff);
                    SendHWTCQ_Param(HWTCQ_CMD_SPCorrect);
                } else {
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_HWJZ_WAITTIME)) {
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            tg_Param.HWTCQCorrectFlag = 1;
                            tg_Param.JiaoZheng_TimeON = 1;
                            tg_Param.CorrectTimeCnt   = 0;
                            RecHWTCQ_Param(0, 0, 0, 0);
                        }
                    } else {
                        RecHWTCQ_Param(1, 0, 0, 0);
                        tg_Param.HWTCQCorrectFlag = 2;
                    }
                }
            }
        } else if (tg_Param.HWTCQCorrectFlag == 1) {
            if (tg_Param.CorrectTimeCnt < HWJZ_TIMEOUT) // 红外校正最长时间10s
            {
                if (0 == tg_Param.HWRecMsg_TimerON) {
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetTemp, HWTCQ_SensorTemp, TCQ_Send_NULL);
                    SendHWTCQ_Param(HWTCQ_CMD_GetTemp);
                    tg_Param.HWTCQTemp_Pos = HWTCQ_SensorTemp;
                } else {
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            if ((mess_From_TG.HW_WorkState1 & 0x0C) == 0x08) {
                                tg_Param.JiaoZheng_TimeON = 0;
                                tg_Param.HWTCQCorrectFlag = 2;
                            }
                            RecHWTCQ_Param(0, 0, 0, 0);
                        }
                    } else {
                        RecHWTCQ_Param(1, 0, 0, 0);
                    }
                }
            } else {
                tg_Param.JiaoZheng_TimeON = 0;
                tg_Param.HWTCQCorrectFlag = 2;
            }
        } else {
            TGParam_Init();
            tg_Param.JiaoZheng_TimeON = 0;
            tg_Param.HWJZ_SFWZ_WaitON = 0; // 红外校正等待伺服到位标志位
            mess_From_TG.HWJiaoZheng  = 2;
        }
    }
}

// 准备检光调光处理,25-9-21
/**
 * @brief 检光功能函数
 *
 * @details 该函数负责管理检光(JianGuang)模式的初始化和执行流程。
 *          - 初始化阶段：当允许检光时，配置所有检光参数，包括定时器、完成状态、曝光时间、
 *            增益等参数，然后初始化参数和检查条件。
 *          - 配置阶段：循环配置可见光探测器(KJ)和红外探测器(HW)的曝光时间和增益参数，
 *            通过与QNSJ模块的通信来发送和接收配置命令。
 *          - 执行阶段：当配置完成后，根据检光模式(广域成像、区域成像或监视模式)
 *            执行相应的扫描或凝视操作。
 *
 * @note 该函数采用状态机设计，通过TG_Light_Allow和相关标志位来控制执行流程的推进。
 *       KJSendCmd_cnt和HWSendCmd_cnt用于标识命令发送的序列号。
 *
 * @return void
 *
 * @see TGParam_Init()
 * @see TGCondition()
 * @see TG_State_Flag()
 * @see SendKJTCQ_Param()
 * @see SendHWTCQ_Param()
 * @see ScanJG()
 * @see GazeJG()
 */
void JianGuang() {
    // 检查是否允许进行检光
    if (1 == tg_Param.TG_Light_Allow) {
        // 设置可见调光准入次数为1
        tg_Param.KJTG_ENTIMER = 1;
        // 设置红外调光准入次数为1
        tg_Param.HWTG_ENTIMER = 1;
        // 设置可见检光完成标志位为4
        tg_Param.KJJG_Completed = 4;
        // 设置红外检光完成标志位为4
        tg_Param.HWJG_Completed = 4;
        // 设置可见曝光时间为20
        tg_Param.KJ_ExpTime = 20;
        // 设置可见模拟增益为3
        tg_Param.KJ_AGain = 3;
        // 设置可见模拟增益倍数为4.2
        tg_Param.KJ_AGain_mtpl = 4.2;
        // 设置红外积分时间为6000
        tg_Param.HW_ExpTime = 6000;
        // 设置红外增益为1
        tg_Param.HW_Gain = 1;
        // 清除可见探测器检光配置完成标志位
        tg_Param.KJTCQ_JGConfig_Flag = 0;
        // 清除红外探测器检光配置完成标志位
        tg_Param.HWTCQ_JGConfig_Flag = 0;
        // 调光参数初始化
        TGParam_Init();
        // 检查调光条件
        TGCondition();
        // 设置调光状态为0
        TG_State_Flag(0, 0, 0, 0, 0);
        // 清除检光允许标志位
        tg_Param.TG_Light_Allow = 0;
    } else {
        // 检查检光状态是否为未开始
        if (0 == mess_From_TG.JianGuang) {
            // 检查可见和红外探测器配置是否完成
            if ((tg_Param.KJTCQ_JGConfig_Flag == 1) && (tg_Param.HWTCQ_JGConfig_Flag == 1)) {
                // 调光参数初始化
                TGParam_Init();
                // 设置检光状态为正在检光
                TG_State_Flag(1, 0, 0, 0, 0);
            }
            // 检查可见发送命令计数器是否为0
            if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器曝光时间
            {
                // 检查是否未发送消息
                if (0 == tg_Param.KJRecMsg_TimerON) {
                    // 将曝光时间高字节赋值
                    tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
                    // 将曝光时间低字节赋值
                    tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
                    // 制作发送给QNSJ的消息：设置可见曝光时间
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
                    // 发送可见探测器参数
                    SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
                } else {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            // 将可见发送命令计数器更新为1，清除错误标志
                            RecKJTCQ_Param(0, 1, 0, 0);
                        }
                    } else {
                        // 等待超时，置错误标志并更新计数器为1
                        RecKJTCQ_Param(1, 1, 0, 0);
                    }
                }
            } else if (1 == tg_Param.KJSendCmd_cnt) // 配置可见模拟增益
            {
                // 检查是否未发送消息
                if (0 == tg_Param.KJRecMsg_TimerON) {
                    // 制作发送给QNSJ的消息：设置可见模拟增益
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                    // 发送可见探测器参数
                    SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                } else {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            // 将可见发送命令计数器更新为2，清除错误标志
                            RecKJTCQ_Param(0, 2, 0, 0);
                        }
                    } else {
                        // 等待超时，置错误标志并更新计数器为2
                        RecKJTCQ_Param(1, 2, 0, 0);
                    }
                }
            } else {
                // 配置完成，发送空指令
                make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                // 发送空指令
                SendKJTCQ_Param(TCQ_Send_NULL);
                // 设置可见探测器检光配置完成标志位
                tg_Param.KJTCQ_JGConfig_Flag = 1;
            }
            // 检查红外发送命令计数器是否为0
            if (0 == tg_Param.HWSendCmd_cnt) // 设置红外积分时间
            {
                // 检查是否未发送消息
                if (0 == tg_Param.HWRecMsg_TimerON) {
                    // 将积分时间低字节赋值
                    tg_Param.HW_ExpTimeL8 = tg_Param.HW_ExpTime & 0x00FF;
                    // 将积分时间高字节赋值
                    tg_Param.HW_ExpTimeH8 = (tg_Param.HW_ExpTime >> 8) & 0x00FF;
                    // 制作发送给QNSJ的消息：设置红外积分时间
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ExpTimeSet, tg_Param.HW_ExpTimeL8, tg_Param.HW_ExpTimeH8);
                    // 发送红外探测器参数
                    SendHWTCQ_Param(HWTCQ_CMD_ExpTimeSet);
                } else {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            // 将红外发送命令计数器更新为1，清除错误标志
                            RecHWTCQ_Param(0, 1, 0, 0);
                        }
                    } else {
                        // 等待超时，置错误标志并更新计数器为1
                        RecHWTCQ_Param(1, 1, 0, 0);
                    }
                }
            } else if (1 == tg_Param.HWSendCmd_cnt) // 设置红外增益
            {
                // 检查是否未发送消息
                if (0 == tg_Param.HWRecMsg_TimerON) {
                    // 制作发送给QNSJ的消息：设置红外积分增益
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                    // 发送红外探测器参数
                    SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
                } else {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            // 将红外发送命令计数器更新为2，清除错误标志
                            RecHWTCQ_Param(0, 2, 0, 0);
                        }
                    } else {
                        // 等待超时，置错误标志并更新计数器为2
                        RecHWTCQ_Param(1, 2, 0, 0);
                    }
                }
            } else {
                // 配置完成，发送空指令
                make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                // 发送空指令
                SendHWTCQ_Param(TCQ_Send_NULL);
                // 设置红外探测器检光配置完成标志位
                tg_Param.HWTCQ_JGConfig_Flag = 1;
            }
        } else {
            // 检查检光状态是否为正在检光
            if (1 == mess_From_TG.JianGuang) {
                // 检查检光是否完成
                if ((tg_Param.KJJG_Completed == 1) && (tg_Param.HWJG_Completed == 1)) {
                    // 调光参数初始化
                    TGParam_Init();
                    // 设置检光状态为检光完成
                    TG_State_Flag(2, 0, 0, 0, 0);
                }
                // 检查检光模式是否为广域成像或区域成像
                if ((JTGMODE_GY == mess_To_TG.JG_Mode) || (JTGMODE_QY == mess_To_TG.JG_Mode)) // 广域成像、区域成像
                {
                    // 执行广域检光处理
                    ScanJG();
                } else // 监视
                {
                    // 执行监视检光处理
                    GazeJG();
                }
            }
        }
    }
}

// 拍照调光处理,25-9-20
void TiaoGuang() {
    if ((tg_Param.TG_GYCX_Allow == 1) || (tg_Param.TG_QYCX_Allow == 1) || (tg_Param.TG_QYJS_Allow == 1) || (tg_Param.TG_StaticPhoto_Allow == 1)) {
        TGParam_Init();
        tg_Param.KJTG_ENTIMER = 3;
        tg_Param.HWTG_ENTIMER = 3;

        tg_Param.TG_GYCX_Allow        = 0;
        tg_Param.TG_QYCX_Allow        = 0;
        tg_Param.TG_QYJS_Allow        = 0;
        tg_Param.TG_StaticPhoto_Allow = 0;
        TG_State_Flag(0, 0, 0, 1, 0);
    } else {
        TGCondition();
        if ((JTGMODE_GY == tg_Param.Photo_Mode) || (JTGMODE_QY == tg_Param.Photo_Mode)) // 广域成像、区域成像
        {
            ScanTG();
        } else // 监视
        {
            GazeTG();
        }
    }
}

// 自检调光处理,25-9-21
void TG_SelfTest() {
    if (tg_Param.TG_CellBIT_Allow == 1) {
        tg_Param.TG_CellBIT_Allow = 0;
        TGParam_Init();
        TG_State_Flag(0, 0, 0, 0, 1);
        tg_Param.KJTCQ_SelfTest = 0;
        tg_Param.HWTCQ_SelfTest = 0;
    } else {
        if ((tg_Param.KJTCQ_SelfTest == 1) && (tg_Param.HWTCQ_SelfTest == 1)) {
            mess_From_TG.SelfTest = 2;
        }
        if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器成像模式
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_WorkMode, KJTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.KJSendCmd_cnt) // 配置可见探测器外触发
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_TrigMode, KJTCQ_TRIGMODE_OUT, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_TrigMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 2, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 2, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            SendKJTCQ_Param(TCQ_Send_NULL);
            tg_Param.KJRecMsg_TimerON = 0;
            tg_Param.KJTCQ_SelfTest   = 1;
        }
        if (0 == tg_Param.HWSendCmd_cnt) // 配置红外探测器成像模式
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_WorkMode, HWTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else if (1 == tg_Param.HWSendCmd_cnt) {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_TrigMode, HWTCQ_TRIGMODE_OUT, HWTCQ_TRIGMODE_OUT);
                SendHWTCQ_Param(HWTCQ_CMD_TrigMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 2, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 2, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            SendHWTCQ_Param(TCQ_Send_NULL);
            tg_Param.HWRecMsg_TimerON = 0;
            tg_Param.HWTCQ_SelfTest   = 1;
        }
    }
}

// 实景检焦调光处理,25-9-21
void TG_FlyFocus() {
    if (tg_Param.TG_FlyFocus_Allow == 1) {
        TGParam_Init();
        tg_Param.KJTG_ENTIMER   = 1;
        tg_Param.KJJG_Completed = 7;
        tg_Param.HWJG_Completed = 1;
        TG_State_Flag(0, 0, 0, 0, 0);
        tg_Param.TG_FlyFocus_Allow = 0;
    } else {
        if (mess_From_TG.JianJiao_state == 0) {
            if (tg_Param.KJJG_Completed == 1) {
                mess_From_TG.JianJiao_state = 1;
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetDefiValue, KJTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
                tg_Param.KJTCQ_Cmd = KJTCQ_CMD_GetDefiValue;
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetDefiValue, HWTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
                tg_Param.HWTCQ_Cmd = HWTCQ_CMD_GetDefiValue;
            }
            GazeJG();
        }
    }
}

// 图像链路测试开始调光处理,25-9-21
void TG_TuCeStart() {
    if (tg_Param.TG_PicLinkTestBegin_Allow == 1) {
        tg_Param.TG_PicLinkTestBegin_Allow = 0;
        TGParam_Init();
        tg_Param.KJTCQ_TestConfig = 0;
        tg_Param.HWTCQ_TestConfig = 0;
        TG_State_Flag(0, 0, 0, 0, 0);
    } else {
        if ((tg_Param.KJTCQ_TestConfig == 1) && (tg_Param.HWTCQ_TestConfig == 1)) {
            mess_From_TG.Tuce_state = 1;
            //			tg_Param.KJTCQ_TestConfig=0;
            //			tg_Param.HWTCQ_TestConfig=0;
        }
        if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器测试模式
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_WorkMode, KJTCQ_WORKMODE_Test, KJTCQ_TESTMODE_JBHJ);
                SendKJTCQ_Param(KJTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 1, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.KJTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.KJTCQ_TestConfig = 1;
        }
        if (0 == tg_Param.HWSendCmd_cnt) // 配置红外探测器测试模式
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_WorkMode, HWTCQ_WORKMODE_Test, HWTCQ_TESTTYPE_JBHJ);
                SendHWTCQ_Param(HWTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.HWTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.HWTCQ_TestConfig = 1;
        }
    }
}
// 图像链路测试结束调光处理,25-9-21
void TG_TuCeStop() {
    if (tg_Param.TG_PicLinkTestEnd_Allow == 1) {
        tg_Param.TG_PicLinkTestEnd_Allow = 0;
        TGParam_Init();
        tg_Param.KJTCQ_TestConfig = 0;
        tg_Param.HWTCQ_TestConfig = 0;
    } else {
        if ((tg_Param.KJTCQ_TestConfig == 1) && (tg_Param.HWTCQ_TestConfig == 1)) {
            mess_From_TG.Tuce_state = 0;
            //			tg_Param.KJTCQ_TestConfig=0;
            //			tg_Param.HWTCQ_TestConfig=0;
        }
        if (0 == tg_Param.KJSendCmd_cnt) // 配置可见探测器成像模式
        {
            if (0 == tg_Param.KJRecMsg_TimerON) {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_WorkMode, KJTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        RecKJTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecKJTCQ_Param(1, 1, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.KJTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.KJTCQ_TestConfig = 1;
        }
        if (0 == tg_Param.HWSendCmd_cnt) // 配置红外探测器成像模式
        {
            if (0 == tg_Param.HWRecMsg_TimerON) {
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_WorkMode, HWTCQ_WORKMODE_Pic, TCQ_Send_NULL);
                SendHWTCQ_Param(HWTCQ_CMD_WorkMode);
            } else {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        RecHWTCQ_Param(0, 1, 0, 0);
                    }
                } else {
                    RecHWTCQ_Param(1, 1, 0, 0);
                }
            }
        } else {
            make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
            tg_Param.HWTCQ_Cmd        = TCQ_Send_NULL;
            tg_Param.HWTCQ_TestConfig = 1;
        }
    }
}

// 监视检光处理,25-9-21
void GazeJG() {
    if (tg_Param.KJJG_Completed > 1) {
        if (0 == tg_Param.KJJS_SDWZ_Sig) {
            if (tg_Param.KJTG_Count < GAZEPHOTO_TGNUM) {
                KJImg_GetGray();
                tg_Param.KJTG_Anal_EN = 1;
                if ((tg_Param.KJTG_Count == (GAZEPHOTO_TGNUM - 1)) && (1 == tg_Param.KJTG_GetGray_EN)) {
                    tg_Param.KJJS_SDWZ_Sig = 1;
                }
            } else {
                if (tg_Param.KJTG_Count > ((GAZEPHOTO_TGNUM - 1) * 4)) {
                    tg_Param.KJTG_Count           = 0;
                    tg_Param.KJImageGray_INDEX    = 0;
                    tg_Param.KJImageSatuNum_INDEX = 0;
                    tg_Param.KJTG_Anal_EN         = 0;
                    tg_Param.KJJS_SDWZ_Sig        = 0;
                    tg_Param.KJRecMsg_TimerON     = 0;
                    tg_Param.KJRecMsg_Timer       = 0;
                }
            }
        } else {
            if (1 == tg_Param.KJTG_Anal_EN) {
                tg_Param.KJTG_Anal_EN = 0;
                KJImg_Analyse();
                tg_Param.KJTG_Calc_EN = 0;
                KJTCQ_CaculateExp();
                tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
                tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
                SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
                SendKJTCQ_TGParam(1, 0, 0, 0);
            } else {
                if (tg_Param.SendKJTime_EN == 1) {
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            SendKJTCQ_TGParam(0, 1, 0, 0);
                            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                            SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                        }
                    } else {
                        //    					SendKJTCQ_TGParam(0,1,0,0);
                        tg_Param.KJComErr = 1;
                        //                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet,tg_Param.KJ_AGain,TCQ_Send_NULL);
                        //                        SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                    }
                }
                if (tg_Param.SendKJGain_EN == 1) {
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            tg_Param.KJJG_Completed = tg_Param.KJJG_Completed - 1;
                            tg_Param.KJJS_SDWZ_Sig  = 0;
                            tg_Param.KJTG_Count     = 0;
                            SendKJTCQ_TGParam(0, 0, 0, 0);
                        }
                    } else {
                        //                        tg_Param.KJJG_Completed = tg_Param.KJJG_Completed - 1;
                        tg_Param.KJJS_SDWZ_Sig = 0;
                        tg_Param.KJTG_Count    = 0;
                        tg_Param.KJComErr      = 1;
                        SendKJTCQ_TGParam(0, 0, 0, 0);
                    }
                }
            }
        }
    }

    if (tg_Param.HWJG_Completed > 1) {
        if (0 == tg_Param.HWJS_SDWZ_Sig) {
            if (tg_Param.HWTG_Count < GAZEPHOTO_TGNUM) {
                HWImg_GetGray(); // 采集红外图像灰度均值
                tg_Param.HWTG_Anal_EN = 1;
                if ((tg_Param.HWTG_Count == (GAZEPHOTO_TGNUM - 1)) && (1 == tg_Param.HWTG_GetGray_EN)) {
                    tg_Param.HWJS_SDWZ_Sig = 1;
                }
            } else {
                if (tg_Param.HWTG_Count > ((GAZEPHOTO_TGNUM - 1) * 4)) {
                    tg_Param.HWTG_Count        = 0;
                    tg_Param.HWImageGray_INDEX = 0;
                    tg_Param.HWTG_Anal_EN      = 0;
                    tg_Param.HWJS_SDWZ_Sig     = 0;
                    tg_Param.HWRecMsg_TimerON  = 0;
                    tg_Param.HWRecMsg_Timer    = 0;
                }
            }
        } else {
            if (1 == tg_Param.HWTG_Anal_EN) {
                tg_Param.HWTG_Anal_EN = 0;
                HWImg_Analyse();
                tg_Param.HWTG_Calc_EN = 0;
                HWTCQ_CaculateExp(); // 计算红外图像的积分时间
                tg_Param.HW_ExpTimeL8 = tg_Param.HW_ExpTime & 0x00FF;
                tg_Param.HW_ExpTimeH8 = (tg_Param.HW_ExpTime >> 8) & 0x00FF;
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ExpTimeSet, tg_Param.HW_ExpTimeL8, tg_Param.HW_ExpTimeH8);
                SendHWTCQ_Param(HWTCQ_CMD_ExpTimeSet);
                SendHWTCQ_TGParam(1, 0, 0, 0, 0);
            } else {
                if (tg_Param.SendHWTime_EN == 1) {
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            SendHWTCQ_TGParam(0, 1, 0, 0, 0);
                            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                            SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
                        }
                    } else {
                        tg_Param.HWComErr = 1;
                        SendHWTCQ_TGParam(0, 1, 0, 0, 0);
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                        SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
                    }
                }
                if (tg_Param.SendHWGain_EN == 1) {
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            tg_Param.HWJG_Completed = tg_Param.HWJG_Completed - 1;
                            tg_Param.HWJS_SDWZ_Sig  = 0;
                            tg_Param.HWTG_Count     = 0;
                            SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                        }
                    } else {
                        tg_Param.HWJG_Completed = tg_Param.HWJG_Completed - 1;
                        tg_Param.HWJS_SDWZ_Sig  = 0;
                        tg_Param.HWTG_Count     = 0;
                        tg_Param.HWComErr       = 1;
                        SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                    }
                }
            }
        }
    }
}

// 广域检光处理,25-9-21
// 广域检光处理,25-9-21
void ScanJG() {
    // 可见探测器检光处理
    if (tg_Param.KJJG_Completed > 1) {
        // 检查可见信号速度位置信号是否为0（未完成采集）
        if (0 == SIG_SDWZ) {
            // 读取可见图像灰度均值
            KJImg_GetGray();
            // 使能可见图像灰度分析
            tg_Param.KJTG_Anal_EN = 1;
        } else {
            // 可见图像分析使能
            if (1 == tg_Param.KJTG_Anal_EN) {
                // 禁用可见图像灰度分析
                tg_Param.KJTG_Anal_EN = 0;
                // 执行可见图像灰度分析
                KJImg_Analyse();
                // 禁用可见曝光计算
                tg_Param.KJTG_Calc_EN = 0;
                // 计算可见探测器曝光时间
                KJTCQ_CaculateExp();
                // 将曝光时间高字节赋值
                tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
                // 将曝光时间低字节赋值
                tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
                // 制作发送给QNSJ的消息：设置可见曝光时间
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
                // 发送可见探测器参数
                SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
                // 使能发送曝光时间
                SendKJTCQ_TGParam(1, 0, 0, 0);
            } else {
                // 可见曝光时间发送处理
                if (tg_Param.SendKJTime_EN == 1) {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            // 使能发送模拟增益
                            SendKJTCQ_TGParam(0, 1, 0, 0);
                            // 制作发送给QNSJ的消息：设置可见模拟增益
                            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                            // 发送可见探测器参数
                            SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                        }
                    } else {
                        // 等待超时处理
                        // 使能发送模拟增益
                        SendKJTCQ_TGParam(0, 1, 0, 0);
                        // 制作发送给QNSJ的消息：设置可见模拟增益
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                        // 发送可见探测器参数
                        SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                        // 置标志位表示可见通信错误
                        tg_Param.KJComErr = 1;
                    }
                }
                // 可见模拟增益发送处理
                if (tg_Param.SendKJGain_EN == 1) {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.KJCOMCNT_Flag == 1) {
                            // 可见检光完成次数递减
                            tg_Param.KJJG_Completed = tg_Param.KJJG_Completed - 1;
                            // 禁用所有可见调光参数发送
                            SendKJTCQ_TGParam(0, 0, 0, 0);
                            // 清零可见调光计数
                            tg_Param.KJTG_Count = 0;
                        }
                    } else {
                        // 等待超时处理
                        // 可见检光完成次数递减
                        tg_Param.KJJG_Completed = tg_Param.KJJG_Completed - 1;
                        // 置标志位表示可见通信错误
                        tg_Param.KJComErr = 1;
                        // 禁用所有可见调光参数发送
                        SendKJTCQ_TGParam(0, 0, 0, 0);
                        // 清零可见调光计数
                        tg_Param.KJTG_Count = 0;
                    }
                }
            }
        }
    }

    // 红外探测器检光处理
    if (tg_Param.HWJG_Completed > 1) {
        // 检查红外信号速度位置信号是否为0（未完成采集）
        if (0 == SIG_SDWZ) {
            // 读取红外图像灰度均值
            HWImg_GetGray();
            // 使能红外图像灰度分析
            tg_Param.HWTG_Anal_EN = 1;
        } else {
            // 红外图像分析处理
            if (1 == tg_Param.HWTG_Anal_EN) {
                // 禁用红外图像灰度分析
                tg_Param.HWTG_Anal_EN = 0;
                // 执行红外图像灰度分析
                HWImg_Analyse();
                // 禁用红外曝光计算
                tg_Param.HWTG_Calc_EN = 0;
                // 计算红外探测器积分时间
                HWTCQ_CaculateExp();
                // 将积分时间低字节赋值
                tg_Param.HW_ExpTimeL8 = tg_Param.HW_ExpTime & 0x00FF;
                // 将积分时间高字节赋值
                tg_Param.HW_ExpTimeH8 = (tg_Param.HW_ExpTime >> 8) & 0x00FF;
                // 制作发送给QNSJ的消息：设置红外积分时间
                make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ExpTimeSet, tg_Param.HW_ExpTimeL8, tg_Param.HW_ExpTimeH8);
                // 发送红外探测器参数
                SendHWTCQ_Param(HWTCQ_CMD_ExpTimeSet);
                // 使能发送积分时间
                SendHWTCQ_TGParam(1, 0, 0, 0, 0);
            } else {
                // 红外积分时间发送处理
                if (tg_Param.SendHWTime_EN == 1) {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            // 使能发送积分增益
                            SendHWTCQ_TGParam(0, 1, 0, 0, 0);
                            // 制作发送给QNSJ的消息：设置红外积分增益
                            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                            // 发送红外探测器参数
                            SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
                        }
                    } else {
                        // 等待超时处理
                        // 使能发送积分增益
                        SendHWTCQ_TGParam(0, 1, 0, 0, 0);
                        // 置标志位表示红外通信错误
                        tg_Param.HWComErr = 1;
                        // 制作发送给QNSJ的消息：设置红外积分增益
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_IntegGainSet, HWTCQ_INTTYPE_ITR, tg_Param.HW_Gain);
                        // 发送红外探测器参数
                        SendHWTCQ_Param(HWTCQ_CMD_IntegGainSet);
                    }
                }
                // 红外积分增益发送处理
                if (tg_Param.SendHWGain_EN == 1) {
                    // 检查是否收到反馈消息且在超时范围内
                    if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                        // 检查通信内容标志位
                        if (tg_Param.HWCOMCNT_Flag == 1) {
                            // 红外检光完成次数递减
                            tg_Param.HWJG_Completed = tg_Param.HWJG_Completed - 1;
                            // 禁用所有红外调光参数发送
                            SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                            // 清零红外调光计数
                            tg_Param.HWTG_Count = 0;
                        }
                    } else {
                        // 等待超时处理
                        // 红外检光完成次数递减
                        tg_Param.HWJG_Completed = tg_Param.HWJG_Completed - 1;
                        // 置标志位表示红外通信错误
                        tg_Param.HWComErr = 1;
                        // 禁用所有红外调光参数发送
                        SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                        // 清零红外调光计数
                        tg_Param.HWTG_Count = 0;
                    }
                }
            }
        }
    }
}

// 监视调光处理,25-9-20
void GazeTG() {
    if (0 == tg_Param.KJJS_SDWZ_Sig) {
        if (tg_Param.KJTG_Count < GAZEPHOTO_TGNUM) {
            KJImg_GetGray();
            tg_Param.KJTG_Anal_EN = 1;
            if ((tg_Param.KJTG_Count == (GAZEPHOTO_TGNUM - 1)) && (1 == tg_Param.KJTG_GetGray_EN)) {
                tg_Param.KJJS_SDWZ_Sig = 1;
            }
        } else {
            if (tg_Param.KJTG_Count >= ((GAZEPHOTO_TGNUM - 1) * 4)) {
                tg_Param.KJTG_Count           = 0;
                tg_Param.KJImageGray_INDEX    = 0;
                tg_Param.KJImageSatuNum_INDEX = 0;
                tg_Param.KJTG_Anal_EN         = 0;
                tg_Param.KJJS_SDWZ_Sig        = 0;
                tg_Param.KJRecMsg_TimerON     = 0;
                tg_Param.KJRecMsg_Timer       = 0;
            }
        }
    } else {
        if (1 == tg_Param.KJTG_Anal_EN) {
            tg_Param.KJTG_Anal_EN = 0;
            KJImg_Analyse();
            if ((mess_To_TG.KJTG_Mode == 0) && (tg_Param.KJTG_Calc_EN == 1)) // 可见自动调光
            {
                tg_Param.KJTG_Calc_EN = 0;
                KJTCQ_CaculateExp();
            }
            tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
            tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
            SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
            SendKJTCQ_TGParam(1, 0, 0, 0);
        } else {
            if (tg_Param.SendKJTime_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 1, 0, 0);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 1, 0, 0);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJGain_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 1, 0);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ReMoveMist, tg_Param.KJImg_ReMoveMist, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_ReMoveMist);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 1, 0);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ReMoveMist, tg_Param.KJImg_ReMoveMist, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_ReMoveMist);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJRmm_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 0, 1);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_IMGEnHance, tg_Param.KJImg_EnHance, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_IMGEnHance);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 0, 1);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_IMGEnHance, tg_Param.KJImg_EnHance, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_IMGEnHance);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJEhc_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 0, 0);
                        make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                        SendKJTCQ_Param(TCQ_Send_NULL);
                        tg_Param.KJJS_SDWZ_Sig = 0;
                        tg_Param.KJTG_Count    = 0;
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 0, 0);
                    make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                    SendKJTCQ_Param(TCQ_Send_NULL);
                    tg_Param.KJComErr      = 1;
                    tg_Param.KJJS_SDWZ_Sig = 0;
                    tg_Param.KJTG_Count    = 0;
                }
            }
        }
    }

    if (0 == tg_Param.HWJS_SDWZ_Sig) {
        if (tg_Param.HWTG_Count < GAZEPHOTO_TGNUM) {
            HWImg_GetGray(); // 采集红外图像灰度均值
            tg_Param.HWTG_Anal_EN = 1;
            if ((tg_Param.HWTG_Count == (GAZEPHOTO_TGNUM - 1)) && (1 == tg_Param.HWTG_GetGray_EN)) {
                tg_Param.HWJS_SDWZ_Sig = 1;
            }
        } else {
            if (tg_Param.HWTG_Count >= ((GAZEPHOTO_TGNUM - 1) * 4)) {
                tg_Param.HWTG_Count        = 0;
                tg_Param.HWImageGray_INDEX = 0;
                tg_Param.HWTG_Anal_EN      = 0;
                tg_Param.HWJS_SDWZ_Sig     = 0;
                tg_Param.HWRecMsg_TimerON  = 0;
                tg_Param.HWRecMsg_Timer    = 0;
            }
        }
    } else {
        if (1 == tg_Param.HWTG_Anal_EN) {
            tg_Param.HWTG_Anal_EN = 0;
            HWImg_Analyse();
            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPolarity, tg_Param.HWImg_Ply, TCQ_Send_NULL);
            SendHWTCQ_Param(HWTCQ_CMD_ImgPolarity);
            SendHWTCQ_TGParam(0, 0, 1, 0, 0);
        } else {
            if (1 == tg_Param.SendHWPly_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        SendHWTCQ_TGParam(0, 0, 0, 1, 0);
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, tg_Param.HWImg_EnHance, HWTCQ_DDE);
                        SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 1, 0);
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, tg_Param.HWImg_EnHance, HWTCQ_DDE);
                    SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    tg_Param.HWComErr = 1;
                }
            }
            if (1 == tg_Param.SendHWEhc_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        SendHWTCQ_TGParam(0, 0, 0, 0, 1);
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, HWTCQ_ImgPro_ON, HWTCQ_FILTER);
                        SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 0, 1);
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, HWTCQ_ImgPro_ON, HWTCQ_FILTER);
                    SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    tg_Param.HWComErr = 1;
                }
            }
            if (1 == tg_Param.SendHWFilter_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        mess_From_TG.HWImg_Filter_back = HWTCQ_ImgPro_ON;
                        SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                        make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                        SendHWTCQ_Param(TCQ_Send_NULL);
                        tg_Param.HWJS_SDWZ_Sig = 0;
                        tg_Param.HWTG_Count    = 0;
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                    make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                    SendHWTCQ_Param(TCQ_Send_NULL);
                    tg_Param.HWComErr      = 1;
                    tg_Param.HWJS_SDWZ_Sig = 0;
                    tg_Param.HWTG_Count    = 0;
                }
            }
        }
    }
}

// 广域调光处理,25-9-20
void ScanTG() {
    if (0 == SIG_SDWZ) // 可见调光
    {
        KJImg_GetGray();
        tg_Param.KJTG_Anal_EN = 1;
    } else {
        if (1 == tg_Param.KJTG_Anal_EN) {
            tg_Param.KJTG_Anal_EN = 0;
            KJImg_Analyse();
            if ((mess_To_TG.KJTG_Mode == 0) && (tg_Param.KJTG_Calc_EN == 1)) // 可见自动调光
            {
                tg_Param.KJTG_Calc_EN = 0;
                KJTCQ_CaculateExp();
            }
            tg_Param.KJ_ExpTimeH8 = ((UINT16)tg_Param.KJ_ExpTime >> 8) & 0x00FF;
            tg_Param.KJ_ExpTimeL8 = (UINT16)tg_Param.KJ_ExpTime & 0x00FF;
            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ExpTimeSet, tg_Param.KJ_ExpTimeL8, tg_Param.KJ_ExpTimeH8);
            SendKJTCQ_Param(KJTCQ_CMD_ExpTimeSet);
            SendKJTCQ_TGParam(1, 0, 0, 0);
        } else {
            if (tg_Param.SendKJTime_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 1, 0, 0);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 1, 0, 0);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_AGainSet, tg_Param.KJ_AGain, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_AGainSet);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJGain_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 1, 0);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ReMoveMist, tg_Param.KJImg_ReMoveMist, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_ReMoveMist);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 1, 0);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_ReMoveMist, tg_Param.KJImg_ReMoveMist, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_ReMoveMist);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJRmm_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 0, 1);
                        make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_IMGEnHance, tg_Param.KJImg_EnHance, TCQ_Send_NULL);
                        SendKJTCQ_Param(KJTCQ_CMD_IMGEnHance);
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 0, 1);
                    make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_IMGEnHance, tg_Param.KJImg_EnHance, TCQ_Send_NULL);
                    SendKJTCQ_Param(KJTCQ_CMD_IMGEnHance);
                    tg_Param.KJComErr = 1;
                }
            }
            if (tg_Param.SendKJEhc_EN == 1) {
                if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.KJCOMCNT_Flag == 1) {
                        SendKJTCQ_TGParam(0, 0, 0, 0);
                        make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                        SendKJTCQ_Param(TCQ_Send_NULL);
                        tg_Param.KJTG_Count = 0;
                    }
                } else {
                    SendKJTCQ_TGParam(0, 0, 0, 0);
                    make_Mess_To_QNSJ_KJTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                    SendKJTCQ_Param(TCQ_Send_NULL);
                    tg_Param.KJComErr   = 1;
                    tg_Param.KJTG_Count = 0;
                }
            }
        }
    }

    if (0 == SIG_SDWZ) // 红外调光
    {
        HWImg_GetGray(); // 采集红外图像灰度均值
        tg_Param.HWTG_Anal_EN = 1;
    } else {
        if (1 == tg_Param.HWTG_Anal_EN) {
            tg_Param.HWTG_Anal_EN = 0;
            HWImg_Analyse();
            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPolarity, tg_Param.HWImg_Ply, TCQ_Send_NULL);
            SendHWTCQ_Param(HWTCQ_CMD_ImgPolarity);
            SendHWTCQ_TGParam(0, 0, 1, 0, 0);
        } else {
            if (1 == tg_Param.SendHWPly_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        SendHWTCQ_TGParam(0, 0, 0, 1, 0);
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, tg_Param.HWImg_EnHance, HWTCQ_DDE);
                        SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 1, 0);
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, tg_Param.HWImg_EnHance, HWTCQ_DDE);
                    SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    tg_Param.HWComErr = 1;
                }
            }
            if (1 == tg_Param.SendHWEhc_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        SendHWTCQ_TGParam(0, 0, 0, 0, 1);
                        make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, HWTCQ_ImgPro_OFF, HWTCQ_FILTER);
                        SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 0, 1);
                    make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_ImgPro, HWTCQ_ImgPro_OFF, HWTCQ_FILTER);
                    SendHWTCQ_Param(HWTCQ_CMD_ImgPro);
                    tg_Param.HWComErr = 1;
                }
            }
            if (1 == tg_Param.SendHWFilter_EN) {
                if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                    if (tg_Param.HWCOMCNT_Flag == 1) {
                        mess_From_TG.HWImg_Filter_back = HWTCQ_ImgPro_OFF;
                        SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                        make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                        SendHWTCQ_Param(TCQ_Send_NULL);
                        tg_Param.HWTG_Count = 0;
                    }
                } else {
                    SendHWTCQ_TGParam(0, 0, 0, 0, 0);
                    make_Mess_To_QNSJ_HWTCQ(TCQ_Send_NULL, TCQ_Send_NULL, TCQ_Send_NULL);
                    SendHWTCQ_Param(TCQ_Send_NULL);
                    tg_Param.HWComErr   = 1;
                    tg_Param.HWTG_Count = 0;
                }
            }
        }
    }
}

// 读取可见图像灰度均值,25-9-25
void KJImg_GetGray() {
    if (1 == tg_Param.KJ_TimeCntFromExpPule_EN) {
        //	    if(0 == tg_Param.KJSendCmd_cnt)
        //	    {
        if (0 == tg_Param.KJRecMsg_TimerON) // 读取图像灰度均值和饱和像元数
        {
            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetGrayValue, KJTCQ_GET_GrayMeanSatuNum, TCQ_Send_NULL);
            SendKJTCQ_Param(KJTCQ_CMD_GetGrayValue);
            tg_Param.KJImgGray_Type = KJTCQ_GET_GrayMeanSatuNum;
        } else {
            if ((1 == tg_Param.KJRecMsg_TimerON) && (tg_Param.KJRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                if (tg_Param.KJCOMCNT_Flag == 1) {
                    tg_Param.KJImageGray[tg_Param.KJImageGray_INDEX]       = tg_Param.KJImageGray_Mean;
                    tg_Param.KJImageSatuNum[tg_Param.KJImageSatuNum_INDEX] = tg_Param.KJImageSatuNum_Mean;
                    tg_Param.KJImageGray_INDEX++;    // 记录当前成像帧索引值，在调用处对该值清零
                    tg_Param.KJImageSatuNum_INDEX++; // 记录当前成像帧索引值，在调用处对该值清零
                    tg_Param.KJTG_GetGray_EN          = 1;
                    tg_Param.KJImageGray_Value_Update = 0; // 可更新图像灰度均值
                    RecKJTCQ_Param(0, 0, 0, 0);
                    tg_Param.KJ_TimeCntFromExpPule_EN = 0;
                }
            } else {
                tg_Param.KJImageGray_Value_Update = 1; // 不可更新图像灰度均值
                RecKJTCQ_Param(1, 0, 0, 0);
                tg_Param.KJTG_GetGray_EN          = 1;
                tg_Param.KJ_TimeCntFromExpPule_EN = 0;
            }
        }
        //	    }
        /*
        else				//读取图像饱和像元数
        {
            if(0 == tg_Param.KJRecMsg_TimerON)
            {
                make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetGrayValue,KJTCQ_GET_SatuNum,TCQ_Send_NULL);
                SendKJTCQ_Param(KJTCQ_CMD_GetGrayValue);
                tg_Param.KJImgGray_Type=KJTCQ_GET_SatuNum;
            }
            else
            {
                if((1 == tg_Param.KJRecMsg_TimerON)&&(tg_Param.KJRecMsg_Timer<TCQCOM_WAITTIME_MAX))
                {
                                    if(tg_Param.KJCOMCNT_Flag == 1)
                                    {
                                            tg_Param.KJImageSatuNum[tg_Param.KJImageSatuNum_INDEX]=tg_Param.KJImageSatuNum_Mean;
                                            tg_Param.KJTG_GetGray_EN=1;
                                            tg_Param.KJImageSatuNum_INDEX++;     		//记录当前成像帧索引值，在调用处对该值清零
                                            RecKJTCQ_Param(0,0,0,0);
                                            tg_Param.KJ_TimeCntFromExpPule_EN=0;        // 回参数完毕后，停止本次图像灰度值读取
                                    }
                }
                else
                {
                    RecKJTCQ_Param(1,0,0,0);
                            tg_Param.KJTG_GetGray_EN=1;
                                    tg_Param.KJ_TimeCntFromExpPule_EN=0;        // 回参数完毕后，停止本次图像灰度值读取
                }
            }
        }
        */
    }
}

// 读取红外图像灰度均值,25-9-21
void HWImg_GetGray() {
    if (tg_Param.HW_TimeCntFromExpPule_EN == 1) {
        if (0 == tg_Param.HWRecMsg_TimerON) {
            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetAveGrayValue, HWTCQ_CMD_GetAveGrayValue, TCQ_Send_NULL);
            SendHWTCQ_Param(HWTCQ_CMD_GetAveGrayValue);
        } else {
            if ((1 == tg_Param.HWRecMsg_TimerON) && (tg_Param.HWRecMsg_Timer < TCQCOM_WAITTIME_MAX)) {
                if (tg_Param.HWCOMCNT_Flag == 1) {
                    tg_Param.HWImageGray[tg_Param.HWImageGray_INDEX] = tg_Param.HWImageGray_Mean;
                    tg_Param.HWTG_GetGray_EN                         = 1;
                    tg_Param.HWImageGray_INDEX++;          // 记录当前成像帧索引值，在调用处对该值清零
                    tg_Param.HWImageGray_Value_Update = 0; // 可更新图像灰度均值
                    RecHWTCQ_Param(0, 0, 0, 0);
                    tg_Param.HW_TimeCntFromExpPule_EN = 0; // 回参数完毕后，停止本次图像灰度值读取
                }
            } else {
                RecHWTCQ_Param(1, 0, 0, 0);
                tg_Param.HWTG_GetGray_EN          = 1;
                tg_Param.HWImageGray_Value_Update = 1; // 不可更新图像灰度均值
                tg_Param.HW_TimeCntFromExpPule_EN = 0; // 回参数完毕后，停止本次图像灰度值读取
            }
        }
    }
}

// 可见图像灰度分析,25-9-25
void KJImg_Analyse() {
    UINT8 index1                  = 0;
    tg_Param.KJImageSatuNum_Value = tg_Param.KJImageSatuNum[0];
    for (index1 = 1; index1 < tg_Param.KJImageSatuNum_INDEX; index1++) {
        if (tg_Param.KJImageSatuNum_Value < tg_Param.KJImageSatuNum[index1]) {
            tg_Param.KJImageSatuNum_Value = tg_Param.KJImageSatuNum[index1]; // 取饱和像元数最大值
        }
    }
    tg_Param.KJImageSatuNum_INDEX = 0;
    if ((JTGMODE_JS == tg_Param.Photo_Mode) || (JTGMODE_JS == mess_To_TG.JG_Mode)) // 监视
    {
        if (tg_Param.KJImageSatuNum_Value >= 1000) {
            tg_Param.KJimg_ValueTarget = tg_Param.KJimg_ValueTarget - KJIMG_TGVALUE_SATUNUM;
        } else if ((tg_Param.KJImageSatuNum_Value >= 0) && (tg_Param.KJImageSatuNum_Value <= 10)) {
            tg_Param.KJimg_ValueTarget = tg_Param.KJimg_ValueTarget + KJIMG_TGVALUE_SATUNUM;
        } else {
            tg_Param.KJimg_ValueTarget = tg_Param.KJimg_ValueTarget;
        }
        if (tg_Param.KJimg_ValueTarget < KJIMG_VALUETARGET_SEA) {
            tg_Param.KJimg_ValueTarget = KJIMG_VALUETARGET_SEA;
        } else if (tg_Param.KJimg_ValueTarget > KJIMG_VALUETARGET_LAND) {
            tg_Param.KJimg_ValueTarget = KJIMG_VALUETARGET_LAND;
        } else {
            tg_Param.KJimg_ValueTarget = tg_Param.KJimg_ValueTarget;
        }
        tg_Param.KJimg_ValueLow  = tg_Param.KJimg_ValueTarget - KJIMG_TGVALUE_BAND; // 可见图像调光阈值下限
        tg_Param.KJimg_ValueHigh = tg_Param.KJimg_ValueTarget + KJIMG_TGVALUE_BAND; // 可见图像调光阈值上限
    }

    tg_Param.KJImageGray_Value = tg_Param.KJImageGray[0];
    for (index1 = 1; index1 < tg_Param.KJImageGray_INDEX; index1++) {
        tg_Param.KJImageGray_Value = tg_Param.KJImageGray_Value + tg_Param.KJImageGray[index1];
    }
    // todo: 调光逻辑上除以0了
    // tg_Param.KJImageGray_Value = tg_Param.KJImageGray_Value / tg_Param.KJImageGray_INDEX;
    // lcy: 20260113
    tg_Param.KJImageGray_Value = 123;

    if ((tg_Param.KJImageGray_Value < 0) || (tg_Param.KJImageGray_Value > 4095)) // 读取图像灰度值错误
    {
        tg_Param.KJImageGray_Value_Update = 1;
    } else {
        tg_Param.KJImageGray_Value_Update = 0;
    }
    if (1 == tg_Param.KJImageGray_Value_Update) // 不可更新图像灰度均值
    {
        tg_Param.KJImageGray_Value = tg_Param.KJImageGray_Value_Last;
    } else {
        tg_Param.KJImageGray_Value_Last = tg_Param.KJImageGray_Value;
    }
    tg_Param.KJImageGray_INDEX = 0;
    if ((tg_Param.KJImageGray_Value > tg_Param.KJimg_ValueHigh) || (tg_Param.KJImageGray_Value < tg_Param.KJimg_ValueLow)) {
        tg_Param.KJTG_En_Timer++;
    } else {
        tg_Param.KJTG_En_Timer = 0;
    }
    if (tg_Param.KJTG_En_Timer >= tg_Param.KJTG_ENTIMER) {
        tg_Param.KJTG_Calc_EN  = 1;
        tg_Param.KJTG_En_Timer = tg_Param.KJTG_ENTIMER;
    } else {
        tg_Param.KJTG_Calc_EN = 0;
    }
    // 判断光照度过高过低故障
    if ((tg_Param.KJImageGray_Value > tg_Param.KJimg_ValueGZlow_cancel) && (tg_Param.KJImageGray_Value < tg_Param.KJimg_ValueGZhigh_cancel)) {
        tg_Param.KJGZLow_Timer  = 0;
        tg_Param.KJGZHigh_Timer = 0;
    } else if (tg_Param.KJImageGray_Value > tg_Param.KJimg_ValueGZhigh) {
        tg_Param.KJGZLow_Timer = 0;
        if (tg_Param.KJ_ExpTime <= KJEXPTIME_MIN) {
            tg_Param.KJGZHigh_Timer++;
        }
    } else if (tg_Param.KJImageGray_Value < tg_Param.KJimg_ValueGZlow) {
        tg_Param.KJGZHigh_Timer = 0;
        if (tg_Param.KJ_ExpTime >= KJEXPTIME_MAX) {
            tg_Param.KJGZLow_Timer++;
        }
    } else {
        if ((tg_Param.KJ_ExpTime > KJEXPTIME_MIN) && (tg_Param.KJ_ExpTime < KJEXPTIME_MAX)) {
            tg_Param.KJGZLow_Timer  = 0;
            tg_Param.KJGZHigh_Timer = 0;
        }
    }
}

// 红外图像灰度分析,25-9-21
void HWImg_Analyse() {
    UINT8 index1               = 0;
    tg_Param.HWImageGray_Value = tg_Param.HWImageGray[0];
    for (index1 = 1; index1 < tg_Param.HWImageGray_INDEX; index1++) {
        tg_Param.HWImageGray_Value = tg_Param.HWImageGray_Value + tg_Param.HWImageGray[index1];
    }

    // tg_Param.HWImageGray_Value = tg_Param.HWImageGray_Value / tg_Param.HWImageGray_INDEX;
    // lcy: 20260113
    tg_Param.HWImageGray_Value = 1234;

    if ((tg_Param.HWImageGray_Value < 10) || (tg_Param.HWImageGray_Value > 16383)) // 读取图像灰度值错误
    {
        tg_Param.HWImageGray_Value_Update = 1;
    } else {
        tg_Param.HWImageGray_Value_Update = 0;
    }
    if (1 == tg_Param.HWImageGray_Value_Update) // 不可更新图像灰度均值
    {
        tg_Param.HWImageGray_Value = tg_Param.HWImageGray_Value_Last;
    } else {
        tg_Param.HWImageGray_Value_Last = tg_Param.HWImageGray_Value;
    }
    tg_Param.HWImageGray_INDEX = 0;
    if ((tg_Param.HWImageGray_Value > tg_Param.HWimg_ValueHigh) || (tg_Param.HWImageGray_Value < tg_Param.HWimg_ValueLow)) {
        tg_Param.HWTG_En_Timer++;
    } else {
        tg_Param.HWTG_En_Timer = 0;
    }
    if (tg_Param.HWTG_En_Timer >= tg_Param.HWTG_ENTIMER) {
        tg_Param.HWTG_Calc_EN  = 1;
        tg_Param.HWTG_En_Timer = tg_Param.HWTG_ENTIMER;
    } else {
        tg_Param.HWTG_Calc_EN = 0;
    }
    // 判断光照度过高/过低故障
    if ((tg_Param.HWImageGray_Value > tg_Param.HWimg_ValueGZlow_cancel) && (tg_Param.HWImageGray_Value < tg_Param.HWimg_ValueGZhigh_cancel)) {
        tg_Param.HWGZHigh_Timer = 0;
        tg_Param.HWGZLow_Timer  = 0;
    } else if (tg_Param.HWImageGray_Value > tg_Param.HWimg_ValueGZhigh) // 判断光照度过高
    {
        tg_Param.HWGZLow_Timer = 0;
        if (tg_Param.HW_ExpTime <= HWEXPTIME_MIN) {
            tg_Param.HWGZHigh_Timer++;
        }
    } else if (tg_Param.HWImageGray_Value < tg_Param.HWimg_ValueGZlow) // 判断光照度过低
    {
        tg_Param.HWGZHigh_Timer = 0;
        if (tg_Param.HW_ExpTime >= HWEXPTIME_MAX) {
            tg_Param.HWGZLow_Timer++;
        }
    } else {
        if ((tg_Param.HW_ExpTime > HWEXPTIME_MIN) && (tg_Param.HW_ExpTime < HWEXPTIME_MAX)) {
            tg_Param.HWGZLow_Timer  = 0;
            tg_Param.HWGZHigh_Timer = 0;
        }
    }
}

// 可见曝光计算,25-10-3
/**
 * @brief 自动曝光时间和模拟增益计算函数
 * @details 根据图像灰度值与目标灰度值的偏差，自动调整曝光时间和模拟增益倍数，
 *          实现图像自动曝光控制功能
 * @return void
 * @note 函数会修改全局结构体 tg_Param 中的以下成员：
 *       - KJ_ExpTime: 曝光时间
 *       - KJ_AGain: 模拟增益档位（0-3）
 *       - KJ_AGain_mtpl: 模拟增益倍数
 *       - KJ_ExpMultiply_float: 曝光时间倍数计算值
 *       - KJ_ExpTime_float: 浮点型曝光时间
 */
void KJTCQ_CaculateExp() {
    // 定义临时变量，用于保存整型曝光时间
    INT32 KJExpTime_temp;

    // 若图像灰度值过高且曝光时间已至最小且增益为0，则锁定在最小曝光时间和零增益状态
    if ((tg_Param.KJImageGray_Value > tg_Param.KJimg_ValueGZhigh) && (tg_Param.KJ_ExpTime <= KJEXPTIME_MIN) && (tg_Param.KJ_AGain == 0)) {
        tg_Param.KJ_ExpTime    = KJEXPTIME_MIN; // 设置曝光时间为最小值
        tg_Param.KJ_AGain      = 0;             // 设置增益档位为0
        tg_Param.KJ_AGain_mtpl = 1.0;           // 设置增益倍数为1.0
    }
    // 若图像灰度值过低且曝光时间已至最大且增益为3，则锁定在最大曝光时间和最大增益状态
    else if ((tg_Param.KJImageGray_Value < tg_Param.KJimg_ValueGZlow) && (tg_Param.KJ_ExpTime >= KJEXPTIME_MAX) && (tg_Param.KJ_AGain == 3)) {
        tg_Param.KJ_ExpTime    = KJEXPTIME_MAX; // 设置曝光时间为最大值
        tg_Param.KJ_AGain      = 3;             // 设置增益档位为3
        tg_Param.KJ_AGain_mtpl = 4.2;           // 设置增益倍数为4.2
    }
    // 其他情况下进行动态曝光调整
    else {
        // 计算曝光时间倍数：当前曝光值 × 当前增益倍数 × (目标灰度/当前灰度)
        tg_Param.KJ_ExpMultiply_float = tg_Param.KJ_ExpTime * tg_Param.KJ_AGain_mtpl * (tg_Param.KJimg_ValueTarget * 1.0) / (tg_Param.KJImageGray_Value * 1.0);

        // 根据计算出的曝光倍数，选择合适的增益档位和增益倍数
        if (tg_Param.KJ_ExpMultiply_float >= 42.0) {
            // 曝光倍数 >= 42.0，设置最高增益档位3，增益倍数4.2
            tg_Param.KJ_AGain      = 3;
            tg_Param.KJ_AGain_mtpl = 4.2;
        } else if ((tg_Param.KJ_ExpMultiply_float < 42.0) && (tg_Param.KJ_ExpMultiply_float >= 20.0)) {
            // 曝光倍数在[20.0, 42.0)范围内，设置增益档位2，增益倍数2.0
            tg_Param.KJ_AGain      = 2;
            tg_Param.KJ_AGain_mtpl = 2.0;
        } else if ((tg_Param.KJ_ExpMultiply_float < 20.0) && (tg_Param.KJ_ExpMultiply_float >= 13.0)) {
            // 曝光倍数在[13.0, 20.0)范围内，设置增益档位1，增益倍数1.3
            tg_Param.KJ_AGain      = 1;
            tg_Param.KJ_AGain_mtpl = 1.3;
        } else {
            // 曝光倍数 < 13.0，设置最低增益档位0，增益倍数1.0
            tg_Param.KJ_AGain      = 0;
            tg_Param.KJ_AGain_mtpl = 1.0;
        }

        // 根据新增益倍数计算新的曝光时间（浮点数）
        tg_Param.KJ_ExpTime_float = tg_Param.KJ_ExpMultiply_float / tg_Param.KJ_AGain_mtpl;

        // 将浮点型曝光时间四舍五入转换为整型
        KJExpTime_temp = (INT32)(tg_Param.KJ_ExpTime_float + 0.5);

        // 若当前曝光时间与新曝光时间的差值超过100，则每次只减少100（平缓调整）
        if (tg_Param.KJ_ExpTime >= (KJExpTime_temp + 100)) {
            tg_Param.KJ_ExpTime = tg_Param.KJ_ExpTime - 100;
        }
        // 否则直接设置为新计算的曝光时间
        else {
            tg_Param.KJ_ExpTime = KJExpTime_temp;
        }
    }

    // 对曝光时间进行边界限制，确保不超过最大值
    if (tg_Param.KJ_ExpTime > KJEXPTIME_MAX) {
        tg_Param.KJ_ExpTime = KJEXPTIME_MAX;
    }
    // 确保曝光时间不低于最小值
    else {
        if (tg_Param.KJ_ExpTime < KJEXPTIME_MIN) {
            tg_Param.KJ_ExpTime = KJEXPTIME_MIN;
        }
    }
}

// 红外曝光计算,25-9-21
void HWTCQ_CaculateExp() {
    if (1 == tg_Param.HW_Gain) {
        tg_Param.HW_ExpTime_float = tg_Param.HW_ExpTime * (tg_Param.HWimg_ValueTarget * 1.0) / (tg_Param.HWImageGray_Value * 1.0);
        tg_Param.HW_ExpTime       = (UINT16)tg_Param.HW_ExpTime_float;
        // hy,25-9-14
        if (tg_Param.HW_ExpTime < 1900) {
            tg_Param.HW_Gain    = 0;
            tg_Param.HW_ExpTime = 4000;
        }
    } else {
        tg_Param.HW_ExpTime_float = tg_Param.HW_ExpTime * (tg_Param.HWimg_ValueTarget * 1.0) / (tg_Param.HWImageGray_Value * 1.0);
        tg_Param.HW_ExpTime       = (UINT16)tg_Param.HW_ExpTime_float;
    }
    //    HWTCQCOEF_ChsKv();
    HWTCQCOEF_ChsHy();
}

// 红外系数选择-kv,25-8-14
void HWTCQCOEF_ChsKv() {
    if (0 == tg_Param.HW_Gain) // 低增益
    {
        if (tg_Param.HW_ExpTime < 5500) {
            tg_Param.HW_ExpTime = 3500;
            tg_Param.HW_Coff    = 5;
        } else if ((tg_Param.HW_ExpTime >= 5500) && (tg_Param.HW_ExpTime < 10500)) {
            tg_Param.HW_ExpTime = 6000;
            tg_Param.HW_Coff    = 4;
        } else if ((tg_Param.HW_ExpTime >= 10500) && (tg_Param.HW_ExpTime < 14500)) {
            tg_Param.HW_ExpTime = 11000;
            tg_Param.HW_Coff    = 3;
        } else if ((tg_Param.HW_ExpTime >= 14500) && (tg_Param.HW_ExpTime < 16000)) {
            tg_Param.HW_ExpTime = 15000;
            tg_Param.HW_Coff    = 2;
        } else {
            tg_Param.HW_ExpTime = 16500;
            tg_Param.HW_Coff    = 1;
        }
    } else // 高增益
    {
        if (tg_Param.HW_ExpTime < 2500) {
            tg_Param.HW_ExpTime = 1700;
            tg_Param.HW_Coff    = 10;
        } else if ((tg_Param.HW_ExpTime >= 2500) && (tg_Param.HW_ExpTime < 4500)) {
            tg_Param.HW_ExpTime = 3000;
            tg_Param.HW_Coff    = 9;
        } else if ((tg_Param.HW_ExpTime >= 4500) && (tg_Param.HW_ExpTime < 6500)) {
            tg_Param.HW_ExpTime = 5000;
            tg_Param.HW_Coff    = 8;
        } else if ((tg_Param.HW_ExpTime >= 6500) && (tg_Param.HW_ExpTime < 13000)) {
            tg_Param.HW_ExpTime = 7000;
            tg_Param.HW_Coff    = 7;
        } else {
            tg_Param.HW_ExpTime = 16000;
            tg_Param.HW_Coff    = 6;
        }
    }
}

// 红外系数选择-hy,25-8-14
void HWTCQCOEF_ChsHy() {
    if (0 == tg_Param.HW_Gain) // 低增益
    {
        if (tg_Param.HW_ExpTime < 8000) {
            tg_Param.HW_ExpTime = 4000;
            tg_Param.HW_Coff    = 1;
        } else if ((tg_Param.HW_ExpTime >= 8000) && (tg_Param.HW_ExpTime < 13000)) {
            tg_Param.HW_ExpTime = 9000;
            tg_Param.HW_Coff    = 2;
        } else {
            tg_Param.HW_ExpTime = 16000;
            tg_Param.HW_Coff    = 3;
        }
    } else // 高增益
    {
        if (tg_Param.HW_ExpTime < 3500) {
            tg_Param.HW_ExpTime = 2000;
            tg_Param.HW_Coff    = 7;
        } else if ((tg_Param.HW_ExpTime >= 3500) && (tg_Param.HW_ExpTime < 5500)) {
            tg_Param.HW_ExpTime = 4000;
            tg_Param.HW_Coff    = 8;
        } else {
            tg_Param.HW_ExpTime = 6000;
            tg_Param.HW_Coff    = 9;
        }
    }
}

// 调光条件判断,25-9-20
void TGCondition() {
    if ((tg_Param.TG_WorkOrder == TG_CMD_Collect) || (tg_Param.TG_WorkOrder == TG_CMD_Wait)) {
        if (mess_To_TG.TargetType == 0x02) // 对海
        {
            tg_Param.KJimg_ValueTarget = KJIMG_VALUETARGET_SEA;
        } else // 对陆
        {
            tg_Param.KJimg_ValueTarget = KJIMG_VALUETARGET_LAND;
        }
        tg_Param.KJimg_ValueLow  = tg_Param.KJimg_ValueTarget - KJIMG_TGVALUE_BAND;
        tg_Param.KJimg_ValueHigh = tg_Param.KJimg_ValueTarget + KJIMG_TGVALUE_BAND;
    }
    if (mess_To_TG.KJsdtg_cnt < -30) {
        mess_To_TG.KJsdtg_cnt = -30;
    } else {
        if (mess_To_TG.KJsdtg_cnt > 30) {
            mess_To_TG.KJsdtg_cnt = 30;
        }
    }
    if (mess_To_TG.KJTG_Mode == 1) // 可见手动调光
    {
        if (tg_Param.KJsdtg_cnt_Itr != mess_To_TG.KJsdtg_cnt) {
            tg_Param.KJ_ExpTime     = tg_Param.KJ_ExpTime + (mess_To_TG.KJsdtg_cnt - tg_Param.KJsdtg_cnt_Itr) * KJEXPTIME_SDTG_ITV;
            tg_Param.KJsdtg_cnt_Itr = mess_To_TG.KJsdtg_cnt;
            if (tg_Param.KJ_ExpTime > KJEXPTIME_MAX) {
                tg_Param.KJ_ExpTime = KJEXPTIME_MAX;
            } else {
                if (tg_Param.KJ_ExpTime < KJEXPTIME_MIN) {
                    tg_Param.KJ_ExpTime = KJEXPTIME_MIN;
                }
            }
        }
    } else {
        tg_Param.KJsdtg_cnt_Itr = 0;
    }

    mess_From_TG.KJTG_Mode_back = mess_To_TG.KJTG_Mode;
    // // 红外调光模式反馈：ICD infrared_dim_mode: 1=自动, 2=手动 -> HWTG_Mode_back: 0=自动, 1=手动
    // // 仅当 infrared_dim_mode 不为 NA(0) 时才更新，避免其他参数修改时误切换调光模式
    // if (cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode != 0) {
    //     mess_From_TG.HWTG_Mode_back = (cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode == 2) ? 1 : 0;
    // }

    if (mess_To_TG.Control_Cmd == TG_CMD_GYCX) {
        tg_Param.Photo_Mode = JTGMODE_GY;
    } else if (mess_To_TG.Control_Cmd == TG_CMD_QYCX) {
        tg_Param.Photo_Mode = JTGMODE_QY;
    } else if (mess_To_TG.Control_Cmd == TG_CMD_QYJS) {
        tg_Param.Photo_Mode = JTGMODE_JS;
    } else {
        if (mess_To_TG.Control_Cmd == TG_CMD_StaticPhoto) {
            tg_Param.Photo_Mode = JTGMODE_JS;
        }
    }

    if (1 == mess_To_TG.KJImg_ReMoveMist) {
        tg_Param.KJImg_ReMoveMist = 1;
    } else {
        tg_Param.KJImg_ReMoveMist = 0;
    }

    if (1 == mess_To_TG.KJImg_EnHance) {
        tg_Param.KJImg_EnHance = 1;
    } else {
        tg_Param.KJImg_EnHance = 0;
    }

    if (1 == mess_To_TG.HWImg_EnHance) {
        tg_Param.HWImg_EnHance = 1;
    } else {
        tg_Param.HWImg_EnHance = 0;
    }

    tg_Param.HWTCQ_Ref_Switch = mess_To_TG.HWTCQ_Ref_Switch;
    tg_Param.HWImg_Ply        = mess_To_TG.HWImg_Ply;

    if (mess_To_TG.Camera_FOV_Switch == FOV_SMALL) {
        tg_Param.KJTurnMode = KJTCQ_IMAGE_VFlip;
        tg_Param.HWTurnMode = HWTCQ_IMAGE_HVFlip;
    } else {
        tg_Param.KJTurnMode = KJTCQ_IMAGE_DFlip;
        tg_Param.HWTurnMode = HWTCQ_IMAGE_VFlip;
    }
}
// 主控指令判断,25-9-7
void TG_AnalyseCmd() {
    if (mess_To_TG.Control_Cmd == TG_CMD_Collect) // 收藏
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_Collect) {
            tg_Param.TG_Collect_Allow = 1;
            tg_Param.TG_WorkOrder     = TG_CMD_Collect;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_CellBIT) // 单元自检
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_CellBIT) {
            tg_Param.TG_CellBIT_Allow = 1;
            tg_Param.TG_WorkOrder     = TG_CMD_CellBIT;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_Light) // 检光
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_Light) {
            tg_Param.TG_Light_Allow = 1;
            tg_Param.TG_WorkOrder   = TG_CMD_Light;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_HWJZ) // 红外校正
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_HWJZ) {
            tg_Param.TG_HWJZ_Allow = 1;
            tg_Param.TG_WorkOrder  = TG_CMD_HWJZ;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_Wait) // 待机
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_Wait) {
            tg_Param.TG_Wait_Allow = 1;
            tg_Param.TG_WorkOrder  = TG_CMD_Wait;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_GYCX) // 广域成像
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_GYCX) {
            tg_Param.TG_GYCX_Allow = 1;
            tg_Param.TG_WorkOrder  = TG_CMD_GYCX;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_QYCX) // 区域成像
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_QYCX) {
            tg_Param.TG_QYCX_Allow = 1;
            tg_Param.TG_WorkOrder  = TG_CMD_QYCX;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_QYJS) // 区域监视
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_QYJS) {
            tg_Param.TG_QYJS_Allow = 1;
            tg_Param.TG_WorkOrder  = TG_CMD_QYJS;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_PicLinkTestBegin) // 图像链路测试开始
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_PicLinkTestBegin) {
            tg_Param.TG_PicLinkTestBegin_Allow = 1;
            tg_Param.TG_WorkOrder              = TG_CMD_PicLinkTestBegin;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_PicLinkTestEnd) // 图像链路测试结束
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_PicLinkTestEnd) {
            tg_Param.TG_PicLinkTestEnd_Allow = 1;
            tg_Param.TG_WorkOrder            = TG_CMD_PicLinkTestEnd;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_FlyFocus) // 航空检焦
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_FlyFocus) {
            tg_Param.TG_FlyFocus_Allow = 1;
            tg_Param.TG_WorkOrder      = TG_CMD_FlyFocus;
        }
    } else if (mess_To_TG.Control_Cmd == TG_CMD_StaticPhoto) // 静态成像
    {
        if (tg_Param.TG_WorkOrder != TG_CMD_StaticPhoto) {
            tg_Param.TG_StaticPhoto_Allow = 1;
            tg_Param.TG_WorkOrder         = TG_CMD_StaticPhoto;
        }
    } else {
        if (mess_To_TG.Control_Cmd == TG_CMD_None) // 空指令
        {
            if (tg_Param.TG_WorkOrder != TG_CMD_None) {
                tg_Param.TG_None_Allow = 1;
                tg_Param.TG_WorkOrder  = TG_CMD_None;
            }
        }
    }
}

// 从FPGA接收到探测器的消息处理,25-9-25
void tcq_mess_Process() {
    // 可见探测器工作模式设置应答
    if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_WorkMode) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_WorkMode)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器触发方式设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_TrigMode) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_TrigMode)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器输出位宽设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_OutBitSet) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_OutBitSet)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器图像翻转方式设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_ImagState) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_ImagState)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag           = 1;
            tg_Param.KJComErr                = 0;
            mess_From_TG.KJImg_TurnMode_back = tg_Param.KJTurnMode;
            mess_From_TG.KJ_WorkState1       = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2       = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器曝光模式设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_ExpMode) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_ExpMode)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器曝光时间设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_ExpTimeSet) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_ExpTimeSet)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag      = 1;
            tg_Param.KJComErr           = 0;
            mess_From_TG.KJExpTime_back = tg_Param.KJ_ExpTime;
            mess_From_TG.KJ_WorkState1  = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2  = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器模拟增益设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_AGainSet) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_AGainSet)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_AGain_back = tg_Param.KJ_AGain;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器图像去雾设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_ReMoveMist) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_ReMoveMist)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag             = 1;
            tg_Param.KJComErr                  = 0;
            mess_From_TG.KJImg_ReMoveMist_back = tg_Param.KJImg_ReMoveMist;
            mess_From_TG.KJ_WorkState1         = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2         = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器图像增强设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_IMGEnHance) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_IMGEnHance)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag          = 1;
            tg_Param.KJComErr               = 0;
            mess_From_TG.KJImg_EnHance_back = tg_Param.KJImg_EnHance;
            mess_From_TG.KJ_WorkState1      = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2      = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器温度读取应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_GetTemp) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_GetTemp)) {
        if (mess_From_QNSJ.kjtcq_data[0] == tg_Param.KJTCQTemp_Pos) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJTCQ_Temp    = (INT8)(mess_From_QNSJ.kjtcq_data[1]);
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器图像灰度读取应答
    else if (tg_Param.KJTCQ_Cmd == KJTCQ_CMD_GetGrayValue) {
        if ((mess_From_QNSJ.kj_cmd_back == KJTCQ_GET_GrayMean) && (tg_Param.KJImgGray_Type == KJTCQ_GET_GrayMean)) {
            tg_Param.KJCOMCNT_Flag           = 1;
            tg_Param.KJComErr                = 0;
            tg_Param.KJImageGray_MeanL       = (UINT16)mess_From_QNSJ.kjtcq_data[0];
            tg_Param.KJImageGray_MeanH       = (UINT16)mess_From_QNSJ.kjtcq_data[1];
            tg_Param.KJImageGray_Mean        = tg_Param.KJImageGray_MeanL + (tg_Param.KJImageGray_MeanH << 8);
            mess_From_TG.KJImgGray_Mean_back = (UINT16)(tg_Param.KJImageGray_Mean / 16);
            mess_From_TG.KJ_WorkState1       = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2       = mess_From_QNSJ.kjtcq_data[3];
        } else if ((mess_From_QNSJ.kj_cmd_back == KJTCQ_GET_SatuNum) && (tg_Param.KJImgGray_Type == KJTCQ_GET_SatuNum)) {
            tg_Param.KJCOMCNT_Flag        = 1;
            tg_Param.KJComErr             = 0;
            tg_Param.KJImageSatuNum_MeanL = (UINT16)mess_From_QNSJ.kjtcq_data[0];
            tg_Param.KJImageSatuNum_MeanH = (UINT16)mess_From_QNSJ.kjtcq_data[1];
            tg_Param.KJImageSatuNum_Mean  = tg_Param.KJImageSatuNum_MeanL + (tg_Param.KJImageSatuNum_MeanH << 8);
            mess_From_TG.KJ_WorkState1    = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2    = mess_From_QNSJ.kjtcq_data[3];
        } else if ((mess_From_QNSJ.kj_cmd_back == KJTCQ_GET_GrayMeanSatuNum) && (tg_Param.KJImgGray_Type == KJTCQ_GET_GrayMeanSatuNum)) {
            tg_Param.KJCOMCNT_Flag           = 1;
            tg_Param.KJComErr                = 0;
            tg_Param.KJImageGray_MeanL       = (UINT16)mess_From_QNSJ.kjtcq_data[0];
            tg_Param.KJImageGray_MeanH       = (UINT16)mess_From_QNSJ.kjtcq_data[1];
            tg_Param.KJImageGray_Mean        = tg_Param.KJImageGray_MeanL + (tg_Param.KJImageGray_MeanH << 8);
            tg_Param.KJImageSatuNum_MeanL    = (UINT16)mess_From_QNSJ.kjtcq_data[2];
            tg_Param.KJImageSatuNum_MeanH    = (UINT16)mess_From_QNSJ.kjtcq_data[3];
            tg_Param.KJImageSatuNum_Mean     = tg_Param.KJImageSatuNum_MeanL + (tg_Param.KJImageSatuNum_MeanH << 8);
            mess_From_TG.KJImgGray_Mean_back = tg_Param.KJImageGray_Mean;
        } else {
            tg_Param.KJCOMCNT_Flag = 0;
        }
    }
    // 可见图像清晰度评价值读取应答
    else if (tg_Param.KJTCQ_Cmd == KJTCQ_CMD_GetDefiValue) {
        if (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_GetDefiValue) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见图像十字丝设置应答
    else if ((tg_Param.KJTCQ_Cmd == KJTCQ_CMD_CrossCurse) && (mess_From_QNSJ.kj_cmd_back == KJTCQ_CMD_CrossCurse)) {
        if (mess_From_QNSJ.kjtcq_data[0] == KJTCQ_CMD_Effective) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    }
    // 可见探测器空指令应答
    else if (tg_Param.KJTCQ_Cmd == TCQ_Send_NULL) {
        if (mess_From_QNSJ.kj_cmd_back == TCQ_Send_NULL) {
            tg_Param.KJCOMCNT_Flag     = 1;
            tg_Param.KJComErr          = 0;
            mess_From_TG.KJ_WorkState1 = mess_From_QNSJ.kjtcq_data[2];
            mess_From_TG.KJ_WorkState2 = mess_From_QNSJ.kjtcq_data[3];
        }
    } else {
        tg_Param.KJCOMCNT_Flag = 0;
    }

    // 红外探测器工作模式设置应答
    if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_WorkMode) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_WorkMode)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器输出图像类型设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ImgType) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ImgType)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器触发方式设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_TrigMode) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_TrigMode)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器输出位宽设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_BandWidth) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_BandWidth)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器开窗行起始设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_RowBegin) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_RowBegin)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器开窗行分辨率设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_RowResol) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_RowResol)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器列起始设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ColBegin) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ColBegin)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器列分辨率设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ColResol) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ColResol)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器开窗使能设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ImgROIEnable) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ImgROIEnable)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器图像翻转设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ImagDir) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ImagDir)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag           = 1;
            tg_Param.HWComErr                = 0;
            mess_From_TG.HWImg_TurnMode_back = tg_Param.HWTurnMode;
            mess_From_TG.HW_WorkState1       = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2       = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器温度读取应答
    else if (tg_Param.HWTCQ_Cmd == HWTCQ_CMD_GetTemp) {
        if ((tg_Param.HWTCQTemp_Pos == HWTCQ_SensorTemp) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_GetTemp)) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HWTCQ_Temp    = (INT16)((mess_From_QNSJ.hwtcq_data[0] + (mess_From_QNSJ.hwtcq_data[1] << 8))) / 10;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外图像灰度值读取应答
    else if (tg_Param.HWTCQ_Cmd == HWTCQ_CMD_GetAveGrayValue) {
        if (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_GetAveGrayValue) {
            tg_Param.HWCOMCNT_Flag           = 1;
            tg_Param.HWComErr                = 0;
            tg_Param.HWImageGray_MeanL       = (UINT16)mess_From_QNSJ.hwtcq_data[0];
            tg_Param.HWImageGray_MeanH       = (UINT16)mess_From_QNSJ.hwtcq_data[1];
            tg_Param.HWImageGray_Mean        = tg_Param.HWImageGray_MeanL + (tg_Param.HWImageGray_MeanH << 8);
            mess_From_TG.HWImgGray_Mean_back = (UINT16)(tg_Param.HWImageGray_Mean / 64);
            mess_From_TG.HW_WorkState1       = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2       = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外图像清晰度评价值读取应答
    else if (tg_Param.HWTCQ_Cmd == HWTCQ_CMD_GetDefiValue) {
        if (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_GetDefiValue) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器积分时间设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ExpTimeSet) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ExpTimeSet)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag      = 1;
            tg_Param.HWComErr           = 0;
            mess_From_TG.HWExpTime_back = tg_Param.HW_ExpTime / 100;
            mess_From_TG.HW_WorkState1  = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2  = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器积分模式、增益模式设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_IntegGainSet) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_IntegGainSet)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_Gain_back  = tg_Param.HW_Gain;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器单点校正应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_SPCorrect) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_SPCorrect)) {
        if ((mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) && (mess_From_QNSJ.hwtcq_data[1] == tg_Param.HW_Coff)) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_Coff_back  = tg_Param.HW_Coff;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器制冷机开关应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_Refrig) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_Refrig)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag        = 1;
            tg_Param.HWComErr             = 0;
            mess_From_TG.HWRef_state_back = tg_Param.HWTCQ_Ref_Switch;
            mess_From_TG.HW_WorkState1    = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2    = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器极性设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ImgPolarity) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ImgPolarity)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag      = 1;
            tg_Param.HWComErr           = 0;
            mess_From_TG.HWImg_Ply_back = tg_Param.HWImg_Ply;
            mess_From_TG.HW_WorkState1  = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2  = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器滤波增强设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_ImgPro) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_ImgPro)) {
        if ((mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) && (mess_From_QNSJ.hwtcq_data[1] == HWTCQ_DDE)) {
            tg_Param.HWCOMCNT_Flag          = 1;
            tg_Param.HWComErr               = 0;
            mess_From_TG.HWImg_EnHance_back = tg_Param.HWImg_EnHance;
            mess_From_TG.HW_WorkState1      = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2      = mess_From_QNSJ.hwtcq_data[3];
        } else if ((mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) && (mess_From_QNSJ.hwtcq_data[1] == HWTCQ_FILTER)) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        } else {
            tg_Param.HWCOMCNT_Flag = 0;
        }
    }
    // 红外探测器十字丝设置应答
    else if ((tg_Param.HWTCQ_Cmd == HWTCQ_CMD_CrsCurs) && (mess_From_QNSJ.hw_cmd_back == HWTCQ_CMD_CrsCurs)) {
        if (mess_From_QNSJ.hwtcq_data[0] == HWTCQ_CMD_Effective) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    }
    // 红外探测器空指令应答
    else if (tg_Param.HWTCQ_Cmd == TCQ_Send_NULL) {
        if (mess_From_QNSJ.hw_cmd_back == TCQ_Send_NULL) {
            tg_Param.HWCOMCNT_Flag     = 1;
            tg_Param.HWComErr          = 0;
            mess_From_TG.HW_WorkState1 = mess_From_QNSJ.hwtcq_data[2];
            mess_From_TG.HW_WorkState2 = mess_From_QNSJ.hwtcq_data[3];
        }
    } else {
        tg_Param.HWCOMCNT_Flag = 0;
    }
}
// 向可见探测器发送指令参数设置
void SendKJTCQ_Param(UINT8 Data1) {
    tg_Param.KJTCQ_Cmd        = Data1;
    tg_Param.KJCOMCNT_Flag    = 0;
    tg_Param.KJRecMsg_TimerON = 1;
    tg_Param.KJRecMsg_Timer   = 0;
}
// 接收可见探测器反馈参数设置
void RecKJTCQ_Param(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4) {
    tg_Param.KJComErr         = Data1;
    tg_Param.KJSendCmd_cnt    = Data2;
    tg_Param.KJRecMsg_TimerON = Data3;
    tg_Param.KJRecMsg_Timer   = Data4;
}
// 向红外探测器发送指令参数设置
void SendHWTCQ_Param(UINT8 Data1) {
    tg_Param.HWTCQ_Cmd        = Data1;
    tg_Param.HWCOMCNT_Flag    = 0;
    tg_Param.HWRecMsg_TimerON = 1;
    tg_Param.HWRecMsg_Timer   = 0;
}
// 接收红外探测器反馈参数设置
void RecHWTCQ_Param(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4) {
    tg_Param.HWComErr         = Data1;
    tg_Param.HWSendCmd_cnt    = Data2;
    tg_Param.HWRecMsg_TimerON = Data3;
    tg_Param.HWRecMsg_Timer   = Data4;
}
// 调光时向可见探测器发送指令参数设置
void SendKJTCQ_TGParam(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4) {
    tg_Param.SendKJTime_EN = Data1;
    tg_Param.SendKJGain_EN = Data2;
    tg_Param.SendKJRmm_EN  = Data3;
    tg_Param.SendKJEhc_EN  = Data4;
}
// 调光时向红外探测器发送指令参数设置
void SendHWTCQ_TGParam(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4, UINT8 Data5) {
    tg_Param.SendHWTime_EN   = Data1;
    tg_Param.SendHWGain_EN   = Data2;
    tg_Param.SendHWPly_EN    = Data3;
    tg_Param.SendHWEhc_EN    = Data4;
    tg_Param.SendHWFilter_EN = Data5;
}
// 调光状态位
void TG_State_Flag(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4, UINT8 Data5) {
    mess_From_TG.JianGuang      = Data1;
    mess_From_TG.HWJiaoZheng    = Data2;
    mess_From_TG.JianJiao_state = Data3;
    mess_From_TG.Photo_state    = Data4;
    mess_From_TG.SelfTest       = Data5;
    //	mess_From_TG.Tuce_state = Data6;
}
