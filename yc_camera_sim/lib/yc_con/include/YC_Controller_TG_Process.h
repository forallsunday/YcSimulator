/*
 * YC_Controller_TG_Process.h
 *
 *  Created on: 2025年9月11日
 *      Author: wangx
 */

#ifndef YC_CONTROLLER_TG_PROCESS_H_
#define YC_CONTROLLER_TG_PROCESS_H_
// #ifdef __cplusplus
// extern "C" {
// #endif
// #include "ft_gpio.h"
#include "sysTypes.h"
#include <fpga_sim.h>

#pragma pack(1)
// extern UINT32	ExpSig_cnt;

//--------------可见探测器---------------------------------
#define KJTCQ_CMD_WorkMode 0xC8   // 可见探测器命令字：设置工作模式
#define KJTCQ_CMD_ImagState 0xC9  // 可见探测器命令字：设置图像翻转状态
#define KJTCQ_CMD_TrigMode 0xA3   // 可见探测器命令字：设置触发方式
#define KJTCQ_CMD_ExpTimeSet 0xAC // 可见探测器命令字：设置曝光时间
#define KJTCQ_CMD_AGainSet 0x56   // 可见探测器命令字：设置模拟增益
#define KJTCQ_CMD_ExpMode 0x5A    // 可见探测器命令字：设置曝光模式
#define KJTCQ_CMD_OutBitSet 0x57  // 可见探测器命令字：设置输出图像位宽
// #define KJTCQ_CMD_BaudSet           0x63    //可见探测器命令字：设置波特率值
// #define KJTCQ_CMD_RowBegin          0x97    //可见探测器命令字：设置开窗行开始数
// #define KJTCQ_CMD_RowResol          0x9B    //可见探测器命令字：设置开窗行分辨率
// #define KJTCQ_CMD_ColBegin          0x9D    //可见探测器命令字：设置开窗列开始数
// #define KJTCQ_CMD_ColResol          0x9E    //可见探测器命令字：设置开窗列分辨率
// #define KJTCQ_CMD_ROIEnable      	0x9F    //可见探测器命令字：设置开窗使能
#define KJTCQ_CMD_CrossCurse 0x90 // 可见探测器命令字：设置十字丝
// #define KJTCQ_CMD_Reset             0x00    //可见探测器命令字：设置探测器复位
// #define KJTCQ_CMD_Store             0x0A    //可见探测器命令字：设置存储当前设置
// #define KJTCQ_CMD_ReStore           0x0F    //可见探测器命令字：设置恢复出厂设置
#define KJTCQ_CMD_ReMoveMist 0x37 // 可见探测器命令字：图像去雾
// #define KJTCQ_CMD_ReMoveNoise		0x54	//可见探测器命令字：图像降噪
#define KJTCQ_CMD_IMGEnHance 0x5C   // 可见探测器命令字：图像增强
#define KJTCQ_CMD_GetTemp 0x36      // 可见探测器命令字：探测器温度读取
#define KJTCQ_CMD_GetGrayValue 0x39 // 可见探测器命令字：查询图像灰度值
#define KJTCQ_CMD_GetDefiValue 0x3E // 可见探测器命令字：查询清晰度评价值
// #define KJTCQ_CMD_GetWorkState      0x3A    //可见探测器命令字：查询工作状态
#define KJTCQ_WORKMODE_Pic 0x55  // 可见探测器成像模式
#define KJTCQ_WORKMODE_Test 0xAA // 可见探测器测试模式
// #define KJTCQ_PICMODE_GYCX			0x00    //可见探测器广域成像模式
// #define KJTCQ_PICMODE_QYCX			0x11    //可见探测器区域成像模式
// #define KJTCQ_PICMODE_JSCX			0x22    //可见探测器监视成像模式
#define KJTCQ_TESTMODE_JBHJ 0x55 // 可见探测器测试图像为渐变灰阶
#define KJTCQ_TESTMODE_QPG 0xAA  // 可见探测器测试图像为棋盘格
// #define KJTCQ_IMAGE_NFlip           0x00    //可见探测器图像不翻转
// #define KJTCQ_IMAGE_HFlip           0x11    //可见探测器图像水平翻转
#define KJTCQ_IMAGE_VFlip 0x22  // 可见探测器图像垂直翻转
#define KJTCQ_IMAGE_DFlip 0x33  // 可见探测器图像对角线翻转
#define KJTCQ_TRIGMODE_IN 0x55  // 可见探测器触发方式为内触发
#define KJTCQ_TRIGMODE_OUT 0xAA // 可见探测器触发方式为外触发
// #define KJTCQ_GAIN0                 0x00	//可见探测器增益0
// #define KJTCQ_GAIN1                 0x01	//可见探测器增益1
// #define KJTCQ_GAIN2                 0x02	//可见探测器增益2
// #define KJTCQ_GAIN3                 0x03	//可见探测器增益3
#define KJTCQ_EXPMODE_MANUAL 0x00 // 可见探测器曝光模式：手动
// #define	KJTCQ_EXPMODE_AUTO			0x11	//可见探测器曝光模式：自动
#define KJTCQ_IMGPRCS_CLOSED 0x00 // 可见探测器图像处理算法：关闭
#define KJTCQ_IMGPRCS_MIN 0x01    // 可见探测器图像处理算法：低档
#define KJTCQ_IMGPRCS_MID 0x02    // 可见探测器图像处理算法：中档
#define KJTCQ_IMGPRCS_MAX 0x03    // 可见探测器图像处理算法：高档
#define KJTCQ_IMG8Bit 0x08        // 可见探测器输出8bit图像
// #define KJTCQ_IMG12Bit              0x0C    //可见探测器输出12bit图像
// #define KJTCQ_BAUD_9600             0x11    //可见探测器通讯波特率，9600
// #define KJTCQ_BAUD_115200           0x22    //可见探测器通讯波特率，115200
// #define KJTCQ_BAUD_230400           0x33    //可见探测器通讯波特率，230400
// #define KJTCQ_BAUD_460800           0x44    //可见探测器通讯波特率，460800
// #define KJTCQROI_OUTPUTIMG          0x00    //可见开窗输出图像
// #define KJTCQROI_OUTPUTGRADS        0x11    //可见开窗输出清晰度评价值
#define KJTCQ_CRSCUS_EN 0x55  // 可见探测器十字丝开启
#define KJTCQ_CRSCUS_DIS 0xAA // 可见探测器十字丝关闭
// #define KJTCQ_Send55                0x55    //可见探测器参数55
// #define KJTCQ_SendAA                0xAA    //可见探测器参数AA
#define KJTCQ_TempSensor 0x11 // 读取可见探测器Sensor温度
// #define KJTCQ_TempFPGA              0x22    //读取可见探测器FPGA温度
// #define KJTCQ_TempPower             0x33    //读取可见探测器电源温度
#define KJTCQ_GET_GrayMean 0x11 // 可见探测器查询：灰度均值
// #define KJTCQ_GET_GrayMax          	0x22    //可见探测器查询：灰度最大值
// #define KJTCQ_GET_GrayMin         	0x33    //可见探测器查询：灰度最小值
#define KJTCQ_GET_SatuNum 0x44         // 可见探测器查询：饱和像元数
#define KJTCQ_GET_GrayMeanSatuNum 0x14 // 可见探测器查询：灰度均值+饱和像元数
// #define KJTCQ_LOOK_UsedTime         0xFF    //可见探测器查询：可见探测器已用时间

#define KJTCQ_CMD_Effective 0x55 // 可见探测器查询应答：命令字有效
// #define KJTCQ_CMD_NEffective        0xAA    //可见探测器查询应答：命令字无效
// #define KJTCQ_AcWorkMode            0xB1    //可见探测器查询：工作模式
// #define KJTCQ_AcTrigMode            0xB2    //可见探测器查询：触发状态
// #define KJTCQ_AcExpTime             0xB4    //可见探测器查询：曝光时间
// #define KJTCQ_AcBaud                0xB8    //可见探测器查询：波特率
// #define KJTCQ_AcPGain               0x85    //可见探测器查询：模拟增益
// #define	KJTCQ_AcExpMode				0x81	//可见探测器查询：曝光模式
// #define KJTCQ_AcOutBit              0x83    //可见探测器查询：输出图像位宽
// #define KJTCQ_AcImageState          0xBB    //可见探测器查询：图像翻转状态
// #define KJTCQ_AcRowBegin            0xD3    //可见探测器查询：开窗开始行数
// #define KJTCQ_AcRowResol            0xD6    //可见探测器查询：开窗行分辨率
// #define KJTCQ_AcColumnBegin         0xD9    //可见探测器查询：开窗开始列数
// #define KJTCQ_AcColumnResol         0xDC    //可见探测器查询：开窗列分辨率
// #define KJTCQ_AcUsedTime            0xEE    //可见探测器查询：探测器已用时间
#define TCQ_Send_NULL 0x00 // 发送空数据

//--------------红外探测器---------------------------------
// 此处定义红外探测器的指令、状态等宏定义
#define HWTCQ_CMD_WorkMode 0x80        // 红外探测器命令字：设置工作模式，成像模式或测试模式
#define HWTCQ_CMD_ImgType 0x83         // 红外探测器命令字：图像类型选择
#define HWTCQ_CMD_IntegGainSet 0x87    // 红外探测器命令字：设置积分模式及增益
#define HWTCQ_CMD_RowBegin 0x88        // 红外探测器命令字：设置开窗行开始数
#define HWTCQ_CMD_RowResol 0x89        // 红外探测器命令字：设置开窗行分辨率
#define HWTCQ_CMD_ColBegin 0x8A        // 红外探测器命令字：设置开窗列开始数
#define HWTCQ_CMD_ColResol 0x8B        // 红外探测器命令字：设置开窗列分辨率
#define HWTCQ_CMD_ImgROIEnable 0x8F    // 红外探测器命令字：设置开窗使能
#define HWTCQ_CMD_TrigMode 0x3C        // 红外探测器命令字：设置触发方式
#define HWTCQ_CMD_ExpTimeSet 0x30      // 红外探测器命令字：设置曝光时间
#define HWTCQ_CMD_GetAveGrayValue 0x36 // 红外探器器命令字：查询图像灰度均值
#define HWTCQ_CMD_GetDefiValue 0x32    // 红外探测器命令字：查询清晰度评价值
#define HWTCQ_GET_UsedTime 0x37        // 红外探测器命令字：查询累计工作时间
#define HWTCQ_CMD_CrsCurs 0x95         // 红外探测器命令字：十字丝开关
#define HWTCQ_CMD_ImgPolarity 0x98     // 红外图像极性：黑热白热
#define HWTCQ_CMD_ImagDir 0x92         // 红外探测器命令字：设置图像翻转状态
#define HWTCQ_CMD_SPCorrect 0x21       // 红外探测器命令字：单点校正
// #define HWTCQ_CMD_DPCorrect_Temp    0x23    //红外探测器命令字：两点温度校正
// #define HWTCQ_CMD_DPCorrect_Int     0x28    //红外探测器命令字：两点积分校正
// #define HWTCQ_CMD_CofSave           0x26    //红外探测器命令字：保存校正系数
#define HWTCQ_CMD_SelfTest 0x38 // 红外探测器命令字：自检
// #define HWTCQ_LOOK_TrigMode     	0x41    //红外探测器查询：触发状态
// #define HWTCQ_LOOK_ExpTime      	0x42    //红外探测器查询：曝光时间
// #define HWTCQ_LOOK_Coff         	0x43    //红外探测器查询：校正系数组
// #define HWTCQ_LOOK_RowBegin     	0x44    //红外探测器查询：开窗行起始
// #define HWTCQ_LOOK_RowResol     	0x45    //红外探测器查询：开窗行分辨率
// #define HWTCQ_LOOK_ColBegin     	0x46    //红外探测器查询：开窗列起始
// #define HWTCQ_LOOK_ColResol     	0x47    //红外探测器查询：开窗列分辨率
#define HWTCQ_CMD_GetTemp 0xA3 // 红外探测器命令字：温度读取
#define HWTCQ_CMD_ImgPro 0xCC  // 红外探测器命令字：图像处理
#define HWTCQ_CMD_Refrig 0x5F  // 红外探测器命令字：制冷机开关
// #define HWTCQ_CMD_Store             0x50    //红外探测器命令字：设置存储当前设置
// #define HWTCQ_CMD_ReStore           0x51    //红外探测器命令字：设置恢复出厂设置
#define HWTCQ_CMD_BandWidth 0xC7 // 红外探测器命令字：图像位宽

#define HWTCQ_WORKMODE_Pic 0x00  // 红外探测器成像模式
#define HWTCQ_WORKMODE_Test 0x01 // 红外探测器测试模式
#define HWTCQ_TESTTYPE_JBHJ 0x01 // 红外探测器测试图像为渐变灰阶
// #define HWTCQ_TESTTYPE_QPG          0x02    //红外探测器测试图像为棋盘格
#define HWTCQ_IMGTYPE_COR 0x00 // 红外图像类型为校正图像
#define HWTCQ_IMGTYPE_ORG 0x01 // 红外图像类型为原始图像
#define HWTCQ_INTTYPE_ITR 0x00 // 红外ITR
// #define	HWTCQ_INTTYPE_IWR			0x01	//红外IWR
#define HWTCQ_GAIN_H 0x01 // 红外高增益
#define HWTCQ_GAIN_L 0x00 // 红外低增益
// #define	HWTCQ_ROIPAR_FULLIMG		0x00	//红外开窗：全分辨率输出图像
// #define	HWTCQ_ROIPAR_INTERIMG		0x01	//红外开窗：插补输出开窗图像
// #define	HWTCQ_ROIPAR_PARTIMG		0x02	//红外开窗：不插补输出开窗图像
// #define	HWTCQ_ROIPAR_PARTGRADS		0x03	//红外开窗：仅开窗计算清晰度评价值
// #define	HWTCQ_ROIPAR_ALLGRADS		0x04	//红外开窗：计算清晰度评价区域与图像输出区域一致
// #define HWTCQ_TRIGMODE_IN           0x01    //触发方式，内触发
#define HWTCQ_TRIGMODE_OUT 0x00  // 触发方式，外触发
#define HWTCQ_CRSCURS_OFF 0x00   // 红外十字丝，关闭
#define HWTCQ_CRSCURS_ON 0x01    // 红外十字丝，开启
#define HWTCQ_PolarityWhite 0x00 // 白热
#define HWTCQ_PolarityBlack 0x01 // 黑热
// #define HWTCQ_IMAGE_NFlip           0x00    //图像不翻转
// #define HWTCQ_IMAGE_HFlip           0x01    //图像水平翻转
#define HWTCQ_IMAGE_VFlip 0x02  // 图像垂直翻转
#define HWTCQ_IMAGE_HVFlip 0x03 // 图像对角线翻转
// #define HWTCQ_ROIPAR_IMGOUTPUT		0x00	//红外开窗图像参数
// #define HWTCQ_ROIPAR_GRADS			0x01	//红外开窗清晰度评价值参数
#define HWTCQ_SensorTemp 0x00 // 机芯制冷温度
// #define HWTCQ_CircuitTemp           0x01    //电路温度
#define HWTCQ_DDE 0x01            // 红外图像DDE
#define HWTCQ_FILTER 0x00         // 红外图像滤波
#define HWTCQ_ImgPro_OFF 0x00     // 图像算法，关闭
#define HWTCQ_ImgPro_ON 0x01      // 图像算法，开启
#define HWTCQ_Refrig_ON 0x01      // 红外制冷机开启
#define HWTCQ_Refrig_OFF 0x00     // 红外制冷机关闭
#define HWTCQ_ImgBandWidth8 0x01  // 红外输出8位
#define HWTCQ_ImgBandWidth14 0x00 // 红外输出14位
#define HWTCQROI_FULLIMG 0x00     // 红外全分辨率图像
#define HWTCQROI_ITPLIMG 0x01     // 红外插补输出
// #define	HWTCQROI_NITPLIMG			0x02	//红外不插补输出
// #define	HWTCQROI_GRADS				0x03	//红外输出清晰度评价值
// #define	HWTCQROI_CSSTNT				0x04	//红外输出清晰度评价值与图像一致

#define HWTCQ_CMD_Effective 0x55 // 红外探测器查询应答：命令字有效
// #define HWTCQ_CMD_NEffective    	0xAA    //红外探测器查询应答：命令字无效
// #define HWTCQ_GRADSROI_AcRowBegin	0x6A	//红外探测器查询应答：清晰度评价值开窗起始行
// #define HWTCQ_GRADSROI_AcRowResol	0x6B	//红外探测器查询应答：清晰度评价值开窗行分辨率
// #define HWTCQ_GRADSROI_AcColBegin	0x6C	//红外探测器查询应答：清晰度评价值开窗起始列
// #define HWTCQ_GRADSROI_AcColResol	0x6D	//红外探测器查询应答：清晰度评价值开窗列分辨率
#define HWTCQ_AcSensorTemp 0xA3 // 红外探测器查询应答：机芯温度
// #define HWTCQ_AcCircuitTemp			0xA4	//红外探测器查询应答：电路温度

//-------------------------------调光用--------------------------------------------------------
// 调光常量宏定义
// 调光常量宏定义
// 可见、红外图像参数
#define KJIMG_VALUEGZLOW 4000 * 0.1           // 可见图像调光光照度过低值
#define KJIMG_VALUEGZHIGH 4000 * 0.9          // 可见图像调光光照度过高值
#define HWIMG_VALUEGZLOW 16000 * 0.1          // 红外图像调光光照度过低值
#define HWIMG_VALUEGZHIGH 16000 * 0.9         // 红外图像调光光照度过高值
#define KJIMG_VALUEGZLOW_CANCEL 4000 * 0.15   // 可见图像调光光照度过低取消值
#define KJIMG_VALUEGZHIGH_CANCEL 4000 * 0.85  // 可见图像调光光照度过高取消值
#define HWIMG_VALUEGZLOW_CANCEL 16000 * 0.15  // 红外图像调光光照度过低取消值
#define HWIMG_VALUEGZHIGH_CANCEL 16000 * 0.85 // 红外图像调光光照度过高取消值

#define KJIMG_VALUETARGET_LAND 4000 * 0.5 // 对陆成像可见图像调光目标值
#define KJIMG_VALUETARGET_SEA 4000 * 0.25 // 对海成像可见图像调光目标值
#define KJIMG_TGVALUE_BAND 500            // 可见图像调光灰度范围-判灰度均值
#define KJIMG_TGVALUE_SATUNUM 200         // 可见图像调光灰度范围-判饱和像元数
// #define	KJIMG_SDTGGRAY			100				//可见图像单次手动调光灰度变化范围
// #define	KJIMGGRAY_TOPLMT		3500			//可见图像手动调光灰度上限
// #define	KJIMGGRAY_LOWLMT		500				//可见图像手动调光灰度下限

#define HWIMG_VALUETARGET 16000 * 0.5 // 红外图像调光目标值
#define HWIMG_TGVALUE_BAND 1000       // 红外图像调光灰度范围

// #define KJ_GRAYVALUE_READ_DELAY                     20      //读可见图像灰度延迟
// #define KJ_GRADSVALUE_READ_DELAY                    20     //读可见图像梯度和延迟
// #define KJ_GRADSVALUE_CLEAR_DELAY                   5       //可见图像梯度和清零延迟
// #define HW_GRAYVALUE_READ_DELAY                     20      //读红外图像灰度延迟
// #define HW_GRADSVALUE_READ_DELAY                    20     //读红外图像梯度和延迟
// #define HW_GRADSVALUE_CLEAR_DELAY                   5       //红外图像梯度和清零延迟
#define TCQ_READPARAM_DELAYMAX 20 // 读取探测器参数延迟最大时间

// #define KJROWBEGIN_IMG              0			//可见图像开窗起始行
// #define KJROWRESOL_IMG              4096		//可见图像开窗行分辨率
// #define KJCOLUMNBEGIN_IMG           0			//可见图像开窗起始列
// #define KJCOLUMNRESOL_IMG           5120		//可见图像开窗列分辨率
// #define KJROWBEGIN_GRADS              0			//可见梯度和开窗起始行
// #define KJROWRESOL_GRADS              4096		//可见梯度和开窗行分辨率
// #define KJCOLUMNBEGIN_GRADS           0			//可见梯度和开窗起始列
// #define KJCOLUMNRESOL_GRADS           5120		//可见梯度和开窗列分辨率
#define HWROWBEGIN_IMG 82     // 红外图像开窗起始行
#define HWROWRESOL_IMG 704    // 红外图像开窗行分辨率
#define HWCOLUMNBEGIN_IMG 178 // 红外图像开窗起始列
#define HWCOLUMNRESOL_IMG 880 // 红外图像开窗列分辨率
// #define HWROWBEGIN_GRADS            0			//红外梯度和开窗起始行
// #define HWROWRESOL_GRADS            1024		//红外梯度和开窗行分辨率
// #define HWCOLUMNBEGIN_GRADS         0			//红外梯度和开窗始列
// #define HWCOLUMNRESOL_GRADS         1280		//红外梯度和开窗列分辨率

// 可见、红外曝光
#define KJEXPTIME_MAX 150 // 可见最大曝光时间
#define KJEXPTIME_MIN 5   // 可见最小曝光时间
// hy
#define HWEXPTIME_MAX 16000 // 红外最大曝光时间
#define HWEXPTIME_MIN 2000  // 红外最小曝光时间

#define KJEXPTIME_SDTG_ITV 5 // 可见手动调光单次调整值

#define GAZEPHOTO_TGNUM 6 // 监视成像调光统计图像幅数
// #define TCQ_COMNUM  			3			//探测器通讯异常发送次数3次
#define TCQCOM_ERR 1000          // 探测器通讯报故时间5s
#define TCQCOM_WAITTIME_MAX 10   // 与探测器通讯接收等待时间
#define TCQCOM_HWJZ_WAITTIME 400 // 红外校正指令等待反馈时间
// #define TCQCOM_WAITTIME			4			//与探测器通讯接收等待时间
// #define SEND_TCQTIME_JS    		20			//监视向探测器发送指令等待最长时间
#define COOLINGTIMEOVER 120000  // 红外制冷时间
#define TCQINITTIME 2400        // 等待探测器初始化时间
#define HWJZ_TIMEOUT 2000       // 红外校正超时时间
#define HWJZ_SFWZ_TIMEOUT 100   // 红外校正调焦到位超时时间
#define TGSELFTEST_TIMEOUT 1000 // 调光自检超时时间
// #define FLYFOCUS_TGTIMEOUT		1000		//实景检焦调光超时时间
#define SIG_SDWZ gpio0AIn(4) // 速度位置信号
#define XJ_SLOPEMODE_LEFT 1  // 相机左倾斜
#define XJ_SLOPEMODE_RIGHT 2 // 相机右倾斜
#define JTGMODE_GY 1         // 调光模式：广域
#define JTGMODE_QY 2         // 调光模式：区域
#define JTGMODE_JS 3         // 调光模式：监视
#define FOV_BIG 1            // 大视场
#define FOV_SMALL 0          // 小视场

// 调光用参数结构体
typedef struct Struct_TG_Param {
    // 工作模式参数
    UINT8 TG_WorkOrder; // 调光工作指令
    UINT8 Photo_Mode;   // 成像模式，1-广域成像，2-区域成像，3-区域监视
    //	UINT8	JG_Mode;				//检光模式，1-广域成像，2-区域成像，3-区域监视

    UINT8 KJTCQ_JGConfig_Flag : 1; // bit0
    UINT8 HWTCQ_JGConfig_Flag : 1; // bit1
    //	UINT8	KJTCQ_JJConfig_Flag:1	;		//bit2
    //	UINT8	KJImgGrads_Flag:1		;		//bit3 可见图像清晰度评价值更新标志位
    //	UINT8	HWImgGrads_Flag:1		;		//bit4 红外图像清晰度评价值更新标志位
    //	UINT8	TG_Condition_Update:1	;		//bit5 调光图像参数更新标志位
    //	UINT8  	HWJZ_SFWZ_State:1		;		//bit6 红外校正伺服到位信号
    //	UINT8	HWRef_state:1			;		//bit7 红外制冷机开关状态,0-关闭,1-开启
    UINT8 reserved : 6;

    UINT8 KJImg_EnHance;    // 内部可见光增强状态 0-关，1-开
    UINT8 KJImg_ReMoveMist; // 内部可见光去雾状态 0-关，1-开
    UINT8 HWImg_EnHance;    // 内部红外增强状态 0-关,1-开
    UINT8 HWImg_Filter;     // 内部红外滤波状态 0-关,1-开
    UINT8 HWTCQ_Ref_Switch; // 内部红外制冷机开关,0-关闭 ,1-开启
    UINT8 HWImg_Ply;        // 内部红外图像黑白热

    UINT8 KJTCQ_InitConfig : 1;   // bit0 可见探测器初始化配置完成标志位
    UINT8 HWTCQ_InitConfig : 1;   // bit1 红外探测器初始化配置完成标志位
    UINT8 TCQ_InitConfig_Rdy : 1; // bit2 探测器初始化配置完成标志位
    //	UINT8	HWImg_Ply:1				;		 //bit3 红外图像极性，0-白热，1-黑热
    UINT8 KJTCQ_TestConfig : 1; // bit4 可见探测器图像链路测试配置完成标志位
    UINT8 HWTCQ_TestConfig : 1; // bit5 红外探测器图像链路测试配置完成标志位
    UINT8 KJTCQ_SelfTest : 1;   // bit6可见探测器自检完成标志位
    UINT8 HWTCQ_SelfTest : 1;   // bit7红外探测器自检完成标志位
    UINT8 reserved1 : 1;

    // 控制指令切换
    UINT8 TG_Collect_Allow : 1; // bit0 首次收到收藏指令标志位
    UINT8 TG_CellBIT_Allow : 1; // bit1 首次收到自检指令标志位
    //	UINT8	TG_KJselfFocus_Allow:1		;	//bit2 首次收到可见自准直检焦指令标志位
    //	UINT8	TG_KJImgFocus_Allow:1		;	//bit3 首次收到可见图像检焦指令标志位
    //	UINT8	TG_HWselfFocus_Allow:1		;	//bit4 首次收到红外自准直检焦指令标志位
    UINT8 TG_Light_Allow : 1; // bit5 首次收到检光指令标志位
    UINT8 TG_HWJZ_Allow : 1;  // bit6 首次收到红外校正指令标志位
    UINT8 TG_Wait_Allow : 1;  // bit7 首次收到待机指令标志位
    UINT8 reserve : 3;        // 保留

    UINT8 TG_GYCX_Allow : 1;             // bit0 首次收到广域成像指令标志位
    UINT8 TG_QYCX_Allow : 1;             // bit1 首次收到区域成像指令标志位
    UINT8 TG_QYJS_Allow : 1;             // bit2 首次收到区域监视指令标志位
    UINT8 TG_PicLinkTestBegin_Allow : 1; // bit3 首次收到图像链路测试开始指令标志位
    UINT8 TG_PicLinkTestEnd_Allow : 1;   // bit4 首次收到图像链路测试结束指令标志位
    UINT8 TG_FlyFocus_Allow : 1;         // bit5 首次收到实景检焦指令标志位
    UINT8 TG_StaticPhoto_Allow : 1;      // bit6 首次收到静态成像指令标志位
    UINT8 TG_None_Allow : 1;             // bit7 首次收到空指令标志位

    // 调光控制参数
    UINT8 KJJG_Completed;           // 可见检光结束标志位
    UINT8 HWJG_Completed;           // 红外检光结束标志位
    UINT8 KJTG_GetGray_EN;          // 可见读取灰度完成标志位
    UINT8 HWTG_GetGray_EN;          // 红外读取灰度完成标志位
    UINT8 KJTG_Anal_EN;             // 可见调光分析使能
    UINT8 HWTG_Anal_EN;             // 红外调光分析使能
    UINT8 KJTG_Calc_EN;             // 可见调光计算使能
    UINT8 HWTG_Calc_EN;             // 红外调光计算使能
    UINT8 KJTG_Count;               // 可见监视成像采集灰度计数器
    UINT8 HWTG_Count;               // 红外监视成像采集灰度计数器
    UINT8 KJ_TimeCntFromExpPule_EN; // 可见距离曝光开始时刻的时间计数使能
    UINT8 HW_TimeCntFromExpPule_EN; // 红外距离曝光开始时刻的时间计数使能
    //	UINT16  KJ_TimeCntFromExpPule;          //可见距离曝光开始时刻计时
    //	UINT16  HW_TimeCntFromExpPule;          //红外距离曝光开始时刻计时
    UINT16 KJimg_ValueTarget;        // 可见图像调光目标值
    UINT16 KJimg_ValueLow;           // 可见图像调光阈值下限
    UINT16 KJimg_ValueHigh;          // 可见图像调光阈值上限
    UINT16 KJimg_ValueGZlow;         // 可见图像调光光照度过低值
    UINT16 KJimg_ValueGZhigh;        // 可见图像调光光照度过高值
    UINT16 KJimg_ValueGZlow_cancel;  // 可见图像调光光照度过低取消值
    UINT16 KJimg_ValueGZhigh_cancel; // 可见图像调光光照度过高取消值
    UINT16 HWimg_ValueTarget;        // 红外图像调光目标值
    UINT16 HWimg_ValueLow;           // 红外图像调光阈值下限
    UINT16 HWimg_ValueHigh;          // 红外图像调光阈值上限
    UINT16 HWimg_ValueGZlow;         // 红外图像调光光照度过低值
    UINT16 HWimg_ValueGZhigh;        // 红外图像调光光照度过高值
    UINT16 HWimg_ValueGZlow_cancel;  // 红外图像调光光照度过低取消值
    UINT16 HWimg_ValueGZhigh_cancel; // 红外图像调光光照度过高取消值
    UINT8  KJGZHigh_Timer;           // 可见光照度过高次数计数器
    UINT8  KJGZLow_Timer;            // 可见光照度过低次数计数器
    UINT8  HWGZHigh_Timer;           // 红外光照度过高次数计数器
    UINT8  HWGZLow_Timer;            // 红外光照度过低次数计数器
    UINT8  KJTG_ENTIMER;             // 可见图像灰度超出阈值范围需要调光的准入次数，在调光和拍照设置
    UINT8  HWTG_ENTIMER;             // 红外图像灰度超出阈值范围需要调光的准入次数，在调光和拍照设置
    UINT8  KJTG_En_Timer;            // 可见调光准入次数
    UINT8  HWTG_En_Timer;            // 红外调光准入次数

    // 工作参数
    INT32 KJ_ExpTime;       // 可见曝光时间
    float KJ_ExpTime_float; // 可见曝光时间
    //	float   KJImageSatuNum_float;	//可见饱和像元数
    UINT8 KJ_AGain;      // 可见模拟增益
    float KJ_AGain_mtpl; // 可见模拟增益
    //	INT16	KJ_ExpTime_Temp;		//可见曝光时间-实景检焦临时存储
    //	UINT16	KJ_AGain_Temp;			//可见模拟增益-实景检焦临时存储
    //	UINT16	KJsdtg_cnt_Done;		//可见手动调光次数-已发送
    UINT16 HW_ExpTime;           // 红外积分时间
    float  HW_ExpTime_float;     // 红外积分时间
    UINT8  HW_Gain;              // 红外增益
    UINT8  HW_Coff;              // 红外校正系数
    float  KJ_ExpMultiply_float; // 可见曝光倍数
    UINT16 KJ_ExpTimeL8;         // 可见曝光时间
    UINT16 KJ_ExpTimeH8;         // 可见曝光时间
    UINT16 HW_ExpTimeL8;         // 红外曝光时间
    UINT16 HW_ExpTimeH8;         // 红外曝光时间
    INT8   KJsdtg_cnt_Itr;       // 可见手动调光次数-内部用

    UINT8  CoolingTime_EN;    // 红外制冷计时器使能
    UINT32 CoolingTimeCnt;    // 红外制冷及探测器初始化计时
    UINT8  HWTCQCorrectFlag;  // 红外校正标志位
    UINT8  JiaoZheng_TimeON;  // 红外校正开始计时标志位
    UINT16 CorrectTimeCnt;    // 红外校正时间计数器
    UINT8  HWJZ_SFWZ_WaitON;  // 红外校正等待伺服到位标志位
    UINT16 HWJZ_SFWZ_WaitCnt; // 红外校正等待伺服到位计数器
    UINT8  TGZJStart_Flag;    // 调光自检开始标志位
    UINT16 TGZJTimer_cnt;     // 调光自检定时计数器
    //	UINT16	FlyFocus_TGcnt;			//实景检焦调光计时
    UINT8  KJComErr;       // 可见探测器通信内容错误标志位
    UINT16 KJComErr_Timer; // 可见探测器通信内容错误计时
    UINT8  HWComErr;       // 红外探测器通信内容错误标志位
    UINT16 HWComErr_Timer; // 红外探测器通信内容错误计时

    // 图像参数
    UINT16 KJImageGray[250];         // 可见图像灰度均值数组
    UINT16 HWImageGray[250];         // 红外图像灰度均值数组
    UINT16 KJImageSatuNum[250];      // 可见图像饱和像元数数组
    UINT16 KJImageGray_INDEX;        // 可见图像灰度索引值
    UINT16 KJImageSatuNum_INDEX;     // 可见图像饱和像元数索引值
    UINT16 HWImageGray_INDEX;        // 红外图像灰度索引值
    UINT16 KJImageGray_Mean;         // 读取可见图像灰度均值
    UINT16 KJImageGray_MeanH;        // 读取可见图像灰度均值
    UINT16 KJImageGray_MeanL;        // 读取可见图像灰度均值
    UINT16 HWImageGray_Mean;         // 读取红外图像灰度均值
    UINT16 HWImageGray_MeanH;        // 读取红外图像灰度均值
    UINT16 HWImageGray_MeanL;        // 读取红外图像灰度均值
    UINT16 KJImageSatuNum_Mean;      // 可见图像饱和像元数
    UINT16 KJImageSatuNum_MeanH;     // 可见图像饱和像元数
    UINT16 KJImageSatuNum_MeanL;     // 可见图像饱和像元数
    UINT32 KJImageGray_Value;        // 当前可见图像调光均值
    UINT16 KJImageGray_Value_Last;   // 上一帧可见图像调光均值
    UINT8  KJImageGray_Value_Update; // 可见图像调光均值更新标志位，0为可更新，1为不可更新
    UINT32 HWImageGray_Value;        // 当前红外图像调光均值
    UINT16 HWImageGray_Value_Last;   // 上一帧红外图像调光均值
    UINT8  HWImageGray_Value_Update; // 红外图像调光均值更新标志位，0为可更新，1为不可更新
    UINT32 KJImageSatuNum_Value;     // 当前可见图像饱和像元数值
    //	UINT32  KJImageGrads;           		//可见图像清晰度评价值
    //	UINT32  KJImageGradsLL;           		//可见图像清晰度评价值最低
    //	UINT32  KJImageGradsLH;           		//可见图像清晰度评价值次低
    //	UINT32  KJImageGradsHL;           		//可见图像清晰度评价值次高
    //	UINT32  KJImageGradsHH;           		//可见图像清晰度评价值最高
    //	UINT16  HWImageGrads;           		//红外图像清晰度评价值
    //	UINT16  HWImageGradsH;           		//红外图像清晰度评价值
    //	UINT16  HWImageGradsL;           		//红外图像清晰度评价值
    //	UINT16  KJROI_RowBegin;					//可见开窗行起始
    //	UINT16	KJROI_RowResol;					//可见开窗行分辨率
    //	UINT16  KJROI_ColumBegin;				//可见开窗列起始
    //	UINT16	KJROI_ColumResol;				//可见开窗列分辨率
    UINT16 HWROI_RowBegin;   // 红外开窗行起始
    UINT16 HWROI_RowResol;   // 红外开窗行分辨率
    UINT16 HWROI_ColumBegin; // 红外开窗列起始
    UINT16 HWROI_ColumResol; // 红外开窗列分辨率

    // 探测器状态和参数
    //	UINT8  	KJWorkMode;             //可见探测器工作模式
    //	UINT8  	KJImgTestMode;          //可见测试图像类型
    //	UINT8  	KJSyncMode;             //可见同步方式变量
    //	UINT8  	KJInSyncFre;            //可见内触发帧频
    UINT8 KJTurnMode; // 可见翻转方式
    //	UINT8  	KJROI_OutputType;		//可见开窗输出类型
    UINT8 KJTCQTemp_Pos;  // 可见探测器温度位置
    UINT8 KJImgGray_Type; // 可见图像灰度类型
    //	UINT8  	HWWorkMode;             //红外探测器工作模式
    //	UINT8  	HWImgTestMode;          //红外测试图像类型
    //	UINT8  	HWSyncMode;             //红外同步方式变量
    //	UINT8  	HWInSyncFre;            //红外内触发帧频
    UINT8 HWTurnMode; // 红外翻转方式
    //	UINT8	HWImg_Plty;				//红外图像极性
    UINT8 HWTCQTemp_Pos; // 红外探测器温度位置
    //	UINT8  	HWROI_OutputType;		//红外开窗输出类型

    UINT8  KJTCQ_Cmd;        // 给可见探测器发送的指令
    UINT8  HWTCQ_Cmd;        // 给红外探测器发送的指令
    UINT8  KJCOMCNT_Flag;    // 可见通讯内容标志位
    UINT8  HWCOMCNT_Flag;    // 红外通讯内容标志位
    UINT8  SendKJTime_EN;    // 监视下向可见探测器发送曝光时间等待使能
    UINT8  SendKJTime_cnt;   // 监视下向可见探测器发送曝光时间等待时间计数器
    UINT8  SendKJGain_EN;    // 监视下向可见探测器发送增益等待使能
    UINT8  SendKJGain_cnt;   // 监视下向可见探测器发送增益等待时间计数器
    UINT8  SendKJRmm_EN;     // 向可见探测器发送去雾等待使能
    UINT8  SendKJRmm_cnt;    // 向可见探测器发送去雾等待时间计数器
    UINT8  SendKJEhc_EN;     // 向可见探测器发送增强等待使能
    UINT8  SendKJEhc_cnt;    // 向可见探测器发送增强等待时间计数器
    UINT8  SendHWTime_EN;    // 监视下向红外探测器发送曝光时间等待使能
    UINT8  SendHWTime_cnt;   // 监视下向红外探测器发送曝光时间等待时间计数器
    UINT8  SendHWGain_EN;    // 监视下向红外探测器发送增益等待使能
    UINT8  SendHWGain_cnt;   // 监视下向红外探测器发送增益等待时间计数器
    UINT8  SendHWPly_EN;     // 拍照时向红外发送黑白热等待使能
    UINT8  SendHWPly_cnt;    // 拍照时向红外发送黑白热等待计数器
    UINT8  SendHWFilter_EN;  // 拍照时向红外发送滤波等待使能
    UINT8  SendHWFilter_cnt; // 拍照时向红外发送滤波等待计数器
    UINT8  SendHWEhc_EN;     // 拍照时向红外发送增强等待使能
    UINT8  SendHWEhc_cnt;    // 拍照时向红外发送增强等待计数器
    UINT16 KJSendCmd_cnt;    // 向可见发送指令次数计数器
    UINT16 HWSendCmd_cnt;    // 向红外发送指令次数计数器
    UINT8  KJRecMsg_TimerON; // 接收可见探测器反馈消息计时使能
    UINT8  KJRecMsg_Timer;   // 接收可见探测器反馈消息计时
    UINT8  HWRecMsg_TimerON; // 接收红外探测器反馈消息计时使能
    UINT8  HWRecMsg_Timer;   // 接收红外探测器反馈消息计时

    UINT8 KJJS_SDWZ_Sig; // 可见监视下速度位置信号
    UINT8 HWJS_SDWZ_Sig; // 红外监视下速度位置信号
} TG_PARAM;

// 主控写到调光
typedef struct Struct_TO_TG {
    UINT8 Control_Cmd; // 命令字
    UINT8 KJTG_Mode;   // 可见调光模式
    UINT8 JG_Mode;     // 检光模式---工作模式
    UINT8 TargetType;  // 对陆对海
    //	UINT8	HWJZ_SFWZ_State;		//不用
    //	UINT8	TG_Condition_Rec;		//调光条件
    //	UINT8	KJExpTime_Rec;			//可见曝光时间设定值
    //	UINT8	KJTCQAGain_Rec;			//可见探测器模拟增益设定值
    //	UINT8	HWExpTime_Rec;			//红外积分时间设定值
    //	UINT8	HWTCQGain_Rec;			//红外探测器增益设定值
    UINT8 XJ_SlopeMode_Rec; // 设备倾斜方式
    //	UINT16	HWROI_RowBegin_Rec;		//红外开窗行起始
    //	UINT16	HWROI_ColBegin_Rec;		//红外开窗列起始
    INT8  KJsdtg_cnt;       // 可见手动调光次数
    UINT8 KJImg_EnHance;    // 可见光增强状态 1-开，2-关
    UINT8 KJImg_ReMoveMist; // 可见光去雾状态 1-开，2-关
    UINT8 HWImg_EnHance;    // 红外增强状态 1-开,2-关
    UINT8 HWImg_Filter;     // 红外滤波状态
    UINT8 HWTCQ_Ref_Switch; // 红外制冷机开关,0-关闭 ,1-开启
    UINT8 HWImg_Ply;        // 红外图像黑白热 0：白；1：黑

    UINT8 Camera_FOV_Switch; // 大小视场切换
} MESS_TO_TG;

// 调光返回--32字节
typedef struct Struct_FROM_TG {
    // 调光工作状态字
    UINT8 JianGuang : 2;      // bit0-bit1 00-检光未开始，01-正在检光，02-检光完成
    UINT8 HWJiaoZheng : 2;    // bit2-bit3 00-校正未开始，01-正在校正，02-校正完成
    UINT8 JianJiao_state : 1; // bit4 0-检焦调光未完成，1-检焦调光完成
    //	UINT8  	FlyFocus_state:1    ;   //bit5 0-检焦未开始，01-正在检焦
    UINT8 SelfTest : 2;    // bit5-bit6 00-自检未开始，01-正在自检，02-自检完成
    UINT8 Photo_state : 1; // bit7 0-未拍照，1-拍照

    UINT8 Wait_state : 1;   // bit0	0-待机配置未开始，1-待机配置完成
    UINT8 Tuce_state : 1;   // bit1 0-停止图像链路测试，1-正在进行图像链路测试
    UINT8 TCQInit_Flag : 1; // bit2	探测器初始化，0-未完成，1-完成
    //	UINT8  	FlyFocus_TGState:2  ;   //bit3-bit4 00-调光未开始，01-正在调光，02-调光完成
    UINT8 KJImg_TurnConfig_Flag : 1; // bit3	可见翻转设置成功标志位
    UINT8 HWImg_TurnConfig_Flag : 1; // bit4	红外翻转设置成功标志位
    UINT8 reserve2 : 3;              // bit5-bit7 保留

    //	UINT8  	KJGradsCalc_state:2 ;   //bit0-bit1 00-未开始计算，01-正在计算，02-计算完成
    //	UINT8  	HWGradsCalc_state:2 ;   //bit2-bit3 00-未开始计算，01-正在计算，02-计算完成
    //	UINT8  	reserve3:4          ;   //bit4-bit7 保留

    // 补充调光需要保存的注释信息
    // 调光工作状态字1
    UINT8 KJTG_Mode_back : 1;   // bit0 0-可见自动调光,1-可见手动调光
    UINT8 HWTG_Mode_back : 1;   // bit1 0-红外自动调光,1-红外手动调光
    UINT8 Cool_state : 1;       // bit2 0-正在制冷，1-制冷到温
    UINT8 HWRef_state_back : 1; // bit3 0-制冷机关闭，1-制冷机开启
    UINT8 HWImg_Ply_back : 1;   // bit4 红外图像极性，0-白热，1-黑热
    UINT8 reserve : 3;          // 保留

    // 调光故障字
    UINT8 KJTCQ_Error : 1;       // bit0 可见探测器通讯内容异常
    UINT8 HWTCQ_Error : 1;       // bit1 红外探测器通讯内容异常
    UINT8 KJGZD_HighError : 1;   // bit2 可见光照度过高
    UINT8 KJGZD_LowError : 1;    // bit3 可见光照度过低
    UINT8 HWGZD_HighError : 1;   // bit4 红外光照度过高
    UINT8 HWGZD_LowError : 1;    // bit5 红外光照度过低
    UINT8 HW_Coolling_Error : 1; // bit6 红外探测器制冷异常
    UINT8 reserve4 : 1;          // 保留

    // 调光反馈状态
    UINT8  KJ_AGain_back;       // 反馈可见探测器模拟增益
    UINT8  HW_Gain_back;        // 反馈红外探测器增益
    UINT8  KJImg_TurnMode_back; // 可见图像翻转方式
    UINT8  HWImg_TurnMode_back; // 红外图像翻转方式
    UINT8  KJExpTime_back;      // 反馈可见探测器曝光时间
    UINT8  HWExpTime_back;      // 反馈红外探测器积分时间
    UINT8  HW_Coff_back;        // 反馈红外系数
    UINT8  TargetType;          // 气溶胶类型
    INT8   KJTCQ_Temp;          // 可见探测器温度
    INT16  HWTCQ_Temp;          // 红外探测器温度
    UINT16 KJImgGray_Mean_back; // 可见图像灰度均值
    UINT16 HWImgGray_Mean_back; // 红外图像灰度均值
    UINT8  baoliu1[6];          // 保留
    UINT8  KJ_WorkState1;       // 可见工作状态1
    UINT8  KJ_WorkState2;       // 可见工作状态2
    UINT8  HW_WorkState1;       // 红外工作状态1
    UINT8  HW_WorkState2;       // 红外工作状态2
    UINT8  HW_SelfTestState1;   // 红外自检状态1
    UINT8  HW_SelfTestState2;   // 红外自检状态1

    // 调光工作状态字2
    UINT8 KJImg_EnHance_back : 2;    // bit5 可见光增强状态 1-开，0-关
    UINT8 KJImg_ReMoveMist_back : 2; // bit6 可见光去雾状态 1-开，0-关
    UINT8 HWImg_EnHance_back : 2;    // bit7 红外增强状态 0-关,1-开
    UINT8 HWImg_Filter_back : 2;     // bit0 红外滤波状态 0-关,1-开

} MESS_FROM_TG;

// 调光变量初始化
void TG_VarInit();
// 调光参数初始化
void TGParam_Init();
// 探测器初始化
void TCQ_Configure();
// 红外制冷判断
void HWTCQ_CoolingJudge();
// 调光故障判断
void TG_ErrCheck();
// 5ms定时调光处理
void TG_5msInterrupt();
// 内部采集信号中断调光处理
void TG_NBCJInterrupt();
// 收藏调光处理
void TG_ShouCang();
// 待机调光处理
void TG_Wait();
// 红外校正调光处理
void HW_JiaoZheng();
// 准备检光调光处理
void JianGuang();
// 拍照调光处理
void TiaoGuang();
// 自检调光处理
void TG_SelfTest();
// 实景检焦调光处理
void TG_FlyFocus();
// 图像链路测试开始调光处理
void TG_TuCeStart();
// 图像链路测试结束调光处理
void TG_TuCeStop();
// 监视检光处理
void GazeJG();
// 广域检光处理
void ScanJG();
// 监视调光处理
void GazeTG();
// 广域调光处理
void ScanTG();
// 读取可见图像灰度均值
void KJImg_GetGray();
// 读取红外图像灰度均值
void HWImg_GetGray();
// 可见图像灰度分析
void KJImg_Analyse();
// 红外图像灰度分析
void HWImg_Analyse();
// 可见曝光计算
void KJTCQ_CaculateExp();
// 红外曝光计算
void HWTCQ_CaculateExp();
// 红外系数选择-kv
void HWTCQCOEF_ChsKv();
// 红外系数选择-hy
void HWTCQCOEF_ChsHy();
// 调光条件判断
void TGCondition();
// 主控指令判断
void TG_AnalyseCmd();
// 从FPGA接收到探测器的消息处理
void tcq_mess_Process();
// 向可见探测器发送指令参数设置
void SendKJTCQ_Param(UINT8 Data1);
// 接收可见探测器反馈参数设置
void RecKJTCQ_Param(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4);
// 向红外探测器发送指令参数设置
void SendHWTCQ_Param(UINT8 Data1);
// 接收红外探测器反馈参数设置
void RecHWTCQ_Param(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4);
// 调光时向可见探测器发送指令参数设置
void SendKJTCQ_TGParam(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4);
// 调光时向红外探测器发送指令参数设置
void SendHWTCQ_TGParam(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4, UINT8 Data5);
// 调光状态位
void TG_State_Flag(UINT8 Data1, UINT8 Data2, UINT8 Data3, UINT8 Data4, UINT8 Data5);

#pragma pack()

// #ifdef __cplusplus
// }
// #endif
#endif /* YC_CONTROLLER_TG_PROCESS_H_ */
