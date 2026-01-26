/**
 * @Author: Chongyang Liu
 * @Date:   2025-10-26 18:28:08
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-10-26 18:29:20
 */
//////////////////////////版本信息/////////////////////////
//软件版本：ICDB3.32
//数据版本：SE_A1.1.0版
//CPU类型：X86

#ifndef ICDB_TOPIC_DESCRIPTION_IRRM_H
#define ICDB_TOPIC_DESCRIPTION_IRRM_H

/////////////////////////////////版本号/////////////////////////////////
//版本名称:SE_A1.1.0版
//版本描述:240911，刘海川拷贝SE_A1.0.0版, 新建SE_A1.1.0版。
#define ICD_VERSION  "SE_A1.1.0版"



/////////////////////////////////节点/////////////////////////////////

//标识符: IRRM 
//名  称: 光雷管理单元 
//说  明: 
#define NODE_IRRM 202


/////////////////////////////////主题/////////////////////////////////

//主题 标 识 符: A818_EO_Image
//主题 名    称: 光电原始图像
//主题 编    码: 4359
//主题 类    型: 流数据包
//主题 格式类型: 应用主题
//主题 长    度: 33
//主题 说    明: 
#define TOPIC_A818_EO_IMAGE 4359
#define TOPIC_A818_EO_IMAGE_LEN 33


//主题 标 识 符: AA_SL_sensor_correlation
//主题 名    称: 空空射击列表目标传感器关联矩阵
//主题 编    码: 1245
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 500
//主题 说    明: 这里的目标总数表示射击列表中的目标总数。
#define TOPIC_AA_SL_SENSOR_CORRELATION 1245
#define TOPIC_AA_SL_SENSOR_CORRELATION_LEN 500


//主题 标 识 符: AA_SL_target
//主题 名    称: 空空射击列表目标
//主题 编    码: 1234
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 406
//主题 说    明: 
#define TOPIC_AA_SL_TARGET 1234
#define TOPIC_AA_SL_TARGET_LEN 406


//主题 标 识 符: AA_TOI_list
//主题 名    称: 空空关注目标列表
//主题 编    码: 2907
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 300
//主题 说    明: 
#define TOPIC_AA_TOI_LIST 2907
#define TOPIC_AA_TOI_LIST_LEN 300


//主题 标 识 符: AA_track_correlate_matrix1
//主题 名    称: 空空目标关联矩阵1
//主题 编    码: 3188
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX1 3188
#define TOPIC_AA_TRACK_CORRELATE_MATRIX1_LEN 496


//主题 标 识 符: AA_track_correlate_matrix10
//主题 名    称: 空空目标关联矩阵10
//主题 编    码: 3197
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX10 3197
#define TOPIC_AA_TRACK_CORRELATE_MATRIX10_LEN 496


//主题 标 识 符: AA_track_correlate_matrix11
//主题 名    称: 空空目标关联矩阵11
//主题 编    码: 3560
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX11 3560
#define TOPIC_AA_TRACK_CORRELATE_MATRIX11_LEN 496


//主题 标 识 符: AA_track_correlate_matrix12
//主题 名    称: 空空目标关联矩阵12
//主题 编    码: 3561
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX12 3561
#define TOPIC_AA_TRACK_CORRELATE_MATRIX12_LEN 496


//主题 标 识 符: AA_track_correlate_matrix13
//主题 名    称: 空空目标关联矩阵13
//主题 编    码: 3562
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX13 3562
#define TOPIC_AA_TRACK_CORRELATE_MATRIX13_LEN 496


//主题 标 识 符: AA_track_correlate_matrix14
//主题 名    称: 空空目标关联矩阵14
//主题 编    码: 3563
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX14 3563
#define TOPIC_AA_TRACK_CORRELATE_MATRIX14_LEN 496


//主题 标 识 符: AA_track_correlate_matrix15
//主题 名    称: 空空目标关联矩阵15
//主题 编    码: 3564
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX15 3564
#define TOPIC_AA_TRACK_CORRELATE_MATRIX15_LEN 496


//主题 标 识 符: AA_track_correlate_matrix16
//主题 名    称: 空空目标关联矩阵16
//主题 编    码: 3565
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX16 3565
#define TOPIC_AA_TRACK_CORRELATE_MATRIX16_LEN 496


//主题 标 识 符: AA_track_correlate_matrix17
//主题 名    称: 空空目标关联矩阵17
//主题 编    码: 3566
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX17 3566
#define TOPIC_AA_TRACK_CORRELATE_MATRIX17_LEN 496


//主题 标 识 符: AA_track_correlate_matrix18
//主题 名    称: 空空目标关联矩阵18
//主题 编    码: 3567
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX18 3567
#define TOPIC_AA_TRACK_CORRELATE_MATRIX18_LEN 496


//主题 标 识 符: AA_track_correlate_matrix19
//主题 名    称: 空空目标关联矩阵19
//主题 编    码: 3568
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX19 3568
#define TOPIC_AA_TRACK_CORRELATE_MATRIX19_LEN 496


//主题 标 识 符: AA_track_correlate_matrix2
//主题 名    称: 空空目标关联矩阵2
//主题 编    码: 3189
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX2 3189
#define TOPIC_AA_TRACK_CORRELATE_MATRIX2_LEN 496


//主题 标 识 符: AA_track_correlate_matrix20
//主题 名    称: 空空目标关联矩阵20
//主题 编    码: 3569
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX20 3569
#define TOPIC_AA_TRACK_CORRELATE_MATRIX20_LEN 496


//主题 标 识 符: AA_track_correlate_matrix3
//主题 名    称: 空空目标关联矩阵3
//主题 编    码: 3190
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX3 3190
#define TOPIC_AA_TRACK_CORRELATE_MATRIX3_LEN 496


//主题 标 识 符: AA_track_correlate_matrix4
//主题 名    称: 空空目标关联矩阵4
//主题 编    码: 3191
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX4 3191
#define TOPIC_AA_TRACK_CORRELATE_MATRIX4_LEN 496


//主题 标 识 符: AA_track_correlate_matrix5
//主题 名    称: 空空目标关联矩阵5
//主题 编    码: 3192
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX5 3192
#define TOPIC_AA_TRACK_CORRELATE_MATRIX5_LEN 496


//主题 标 识 符: AA_track_correlate_matrix6
//主题 名    称: 空空目标关联矩阵6
//主题 编    码: 3193
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX6 3193
#define TOPIC_AA_TRACK_CORRELATE_MATRIX6_LEN 496


//主题 标 识 符: AA_track_correlate_matrix7
//主题 名    称: 空空目标关联矩阵7
//主题 编    码: 3194
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX7 3194
#define TOPIC_AA_TRACK_CORRELATE_MATRIX7_LEN 496


//主题 标 识 符: AA_track_correlate_matrix8
//主题 名    称: 空空目标关联矩阵8
//主题 编    码: 3195
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX8 3195
#define TOPIC_AA_TRACK_CORRELATE_MATRIX8_LEN 496


//主题 标 识 符: AA_track_correlate_matrix9
//主题 名    称: 空空目标关联矩阵9
//主题 编    码: 3196
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AA_TRACK_CORRELATE_MATRIX9 3196
#define TOPIC_AA_TRACK_CORRELATE_MATRIX9_LEN 496


//主题 标 识 符: absolute_nav_data_fused
//主题 名    称: 绝对导航融合飞行参数
//主题 编    码: 421
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 145
//主题 说    明: 
#define TOPIC_ABSOLUTE_NAV_DATA_FUSED 421
#define TOPIC_ABSOLUTE_NAV_DATA_FUSED_LEN 145


//主题 标 识 符: AC_Data_FCS_USIM
//主题 名    称: 飞机参数_飞控机电参数
//主题 编    码: 1251
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 64
//主题 说    明: 
#define TOPIC_AC_DATA_FCS_USIM 1251
#define TOPIC_AC_DATA_FCS_USIM_LEN 64


//主题 标 识 符: ARINC615a_LOAD_NORMAL_OMP
//主题 名    称: ARINC615a_LOAD_NORMAL_OMP
//主题 编    码: 4016
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 490
//主题 说    明: 
#define TOPIC_ARINC615A_LOAD_NORMAL_OMP 4016
#define TOPIC_ARINC615A_LOAD_NORMAL_OMP_LEN 490


//主题 标 识 符: ARINC615a_LOAD_STREAM_OMP
//主题 名    称: ARINC615a_LOAD_STREAM_OMP
//主题 编    码: 4017
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 490
//主题 说    明: 
#define TOPIC_ARINC615A_LOAD_STREAM_OMP 4017
#define TOPIC_ARINC615A_LOAD_STREAM_OMP_LEN 490


//主题 标 识 符: AS_SL_correlate_matrix
//主题 名    称: 空面射击列表目标关联矩阵
//主题 编    码: 2944
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 这里的目标总数表示所有包中的目标总数。
#define TOPIC_AS_SL_CORRELATE_MATRIX 2944
#define TOPIC_AS_SL_CORRELATE_MATRIX_LEN 496


//主题 标 识 符: burst_paras
//主题 名    称: 猝发测距参数
//主题 编    码: 1970
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 20
//主题 说    明: 
#define TOPIC_BURST_PARAS 1970
#define TOPIC_BURST_PARAS_LEN 20


//主题 标 识 符: data_load_msg_IRRM
//主题 名    称: 数据加载通知_IRRM
//主题 编    码: 3452
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 6
//主题 说    明: 
#define TOPIC_DATA_LOAD_MSG_IRRM 3452
#define TOPIC_DATA_LOAD_MSG_IRRM_LEN 6


//主题 标 识 符: DataBaseInfo
//主题 名    称: 数据库信息
//主题 编    码: 2092
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 95
//主题 说    明: 
#define TOPIC_DATABASEINFO 2092
#define TOPIC_DATABASEINFO_LEN 95


//主题 标 识 符: DCD_act_req_report
//主题 名    称: DCD_活动请求通告
//主题 编    码: 1220
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 7
//主题 说    明: 各子域发送该主题，以确认收到活动请求。活动请求通告是向发出请求的子域通告活动的执行结果，是该活动的终结状态消息。
#define TOPIC_DCD_ACT_REQ_REPORT 1220
#define TOPIC_DCD_ACT_REQ_REPORT_LEN 7


//主题 标 识 符: file_load_state_report
//主题 名    称: 文件加载状态报告
//主题 编    码: 451
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 16
//主题 说    明: 
#define TOPIC_FILE_LOAD_STATE_REPORT 451
#define TOPIC_FILE_LOAD_STATE_REPORT_LEN 16


//主题 标 识 符: General_Video
//主题 名    称: 视频流_通用主题
//主题 编    码: 1038
//主题 类    型: 视频
//主题 格式类型: 应用主题
//主题 长    度: 15
//主题 说    明: 
#define TOPIC_GENERAL_VIDEO 1038
#define TOPIC_GENERAL_VIDEO_LEN 15


//主题 标 识 符: HOTAS_Report_Calibration_para
//主题 名    称: HOTAS_报告_校准参数
//主题 编    码: 3403
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 20
//主题 说    明: 
#define TOPIC_HOTAS_REPORT_CALIBRATION_PARA 3403
#define TOPIC_HOTAS_REPORT_CALIBRATION_PARA_LEN 20


//主题 标 识 符: HW_config_info_report
//主题 名    称: 硬件配置信息报告
//主题 编    码: 391
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 500
//主题 说    明: 本主题包括了子系统的硬件配置信息。该主题提供了必要的信息用于校验软件（OFP和MDF）和硬件的匹配性。该主题也提供了一种记录硬件配置数据的机制。
#define TOPIC_HW_CONFIG_INFO_REPORT 391
#define TOPIC_HW_CONFIG_INFO_REPORT_LEN 500


//主题 标 识 符: ID_data_transmit_state
//主题 名    称: 情报数据传输状态
//主题 编    码: 4526
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 10
//主题 说    明: 
#define TOPIC_ID_DATA_TRANSMIT_STATE 4526
#define TOPIC_ID_DATA_TRANSMIT_STATE_LEN 10


//主题 标 识 符: INS1_nav_data
//主题 名    称: INS1导航数据
//主题 编    码: 393
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 228
//主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//               其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//               卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               每一类数据时标信号之后的数据为其对应的该类数据。且惯导1转发飞管A、C通道大气数据。
#define TOPIC_INS1_NAV_DATA 393
#define TOPIC_INS1_NAV_DATA_LEN 228


//主题 标 识 符: INS1_NAV_data_5ms
//主题 名    称: INS1导航数据_5ms
//主题 编    码: 2115
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 48
//主题 说    明: 
#define TOPIC_INS1_NAV_DATA_5MS 2115
#define TOPIC_INS1_NAV_DATA_5MS_LEN 48


//主题 标 识 符: INS1_operational_paras
//主题 名    称: INS1工作参数报告
//主题 编    码: 388
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 25
//主题 说    明: 
#define TOPIC_INS1_OPERATIONAL_PARAS 388
#define TOPIC_INS1_OPERATIONAL_PARAS_LEN 25


//主题 标 识 符: INS2_nav_data
//主题 名    称: INS2导航数据
//主题 编    码: 399
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 228
//主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//               其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//               卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               每一类数据时标信号之后的数据为其对应的该类数据。且惯导2转发飞管B、D通道大气数据。
#define TOPIC_INS2_NAV_DATA 399
#define TOPIC_INS2_NAV_DATA_LEN 228


//主题 标 识 符: INS2_NAV_data_5ms
//主题 名    称: INS2导航数据_5ms
//主题 编    码: 2116
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 48
//主题 说    明: 
#define TOPIC_INS2_NAV_DATA_5MS 2116
#define TOPIC_INS2_NAV_DATA_5MS_LEN 48


//主题 标 识 符: INS2_operational_paras
//主题 名    称: INS2工作参数报告
//主题 编    码: 389
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 25
//主题 说    明: 
#define TOPIC_INS2_OPERATIONAL_PARAS 389
#define TOPIC_INS2_OPERATIONAL_PARAS_LEN 25


//主题 标 识 符: INS3_nav_data
//主题 名    称: INS3导航数据
//主题 编    码: 4195
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 228
//主题 说    明: 该消息包含INS输出的组合、纯惯、纯卫星导航、大气飞行参数。
//               其中组合、纯惯这两种导航飞行参数都被分为A、B两类（组合A、组合B、纯惯A、纯惯B），A类主要包括了加速度、速度、角速率、姿态、航向等飞行参数，以及这些参数的导出参数。B类主要为位置、高度、磁差等飞行参数。A类参数的数据更新周期为10ms，与本消息的刷新周期相同；B类参数的数据更新周期为10ms。故所有使用这些参数的"客户"单元在使用这些参数时应当关注在消息中为每一类数据定义的"数据生成时间"（采用系统的任务时间）。
//               卫星接收机产生原始飞行参数更新周期为1s，需要INS对其进行插值计算，插值后卫星导航飞行参数的更新周期为100ms，为本消息更新周期的10倍。故卫星导航飞行参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               INS转发在飞管网络中收到的大气数据，飞管网络中大气数据的刷新周期为15ms，为本消息的更新周期1.5倍。故大气数据导航参数也有其特有的时标来表示其数据时刻（采用系统的任务时间）。
//               每一类数据时标信号之后的数据为其对应的该类数据。且惯导2转发飞管B、D通道大气数据。
#define TOPIC_INS3_NAV_DATA 4195
#define TOPIC_INS3_NAV_DATA_LEN 228


//主题 标 识 符: INS3_NAV_data_5ms
//主题 名    称: INS3导航数据_5ms
//主题 编    码: 4196
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 48
//主题 说    明: 
#define TOPIC_INS3_NAV_DATA_5MS 4196
#define TOPIC_INS3_NAV_DATA_5MS_LEN 48


//主题 标 识 符: INS3_operational_paras
//主题 名    称: INS3工作参数报告
//主题 编    码: 4193
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 25
//主题 说    明: 
#define TOPIC_INS3_OPERATIONAL_PARAS 4193
#define TOPIC_INS3_OPERATIONAL_PARAS_LEN 25


//主题 标 识 符: IR_AA_search_report
//主题 名    称: 红外点迹目标报告
//主题 编    码: 1018
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 303
//主题 说    明: 
#define TOPIC_IR_AA_SEARCH_REPORT 1018
#define TOPIC_IR_AA_SEARCH_REPORT_LEN 303


//主题 标 识 符: IR_AA_track_report
//主题 名    称: IR空空跟踪目标报告
//主题 编    码: 1280
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 
#define TOPIC_IR_AA_TRACK_REPORT 1280
#define TOPIC_IR_AA_TRACK_REPORT_LEN 496


//主题 标 识 符: IR_LOS_ground_alt
//主题 名    称: 光雷LOS地形高度请求
//主题 编    码: 3319
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 20
//主题 说    明: 
#define TOPIC_IR_LOS_GROUND_ALT 3319
#define TOPIC_IR_LOS_GROUND_ALT_LEN 20


//主题 标 识 符: IR_LOS_map_ground_alt
//主题 名    称: 光雷LOS地面交点地形高度
//主题 编    码: 3321
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 20
//主题 说    明: 
#define TOPIC_IR_LOS_MAP_GROUND_ALT 3321
#define TOPIC_IR_LOS_MAP_GROUND_ALT_LEN 20


//主题 标 识 符: IR_nav_data
//主题 名    称: 光电IMU导航数据
//主题 编    码: 4489
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 20
//主题 说    明: 
#define TOPIC_IR_NAV_DATA 4489
#define TOPIC_IR_NAV_DATA_LEN 20


//主题 标 识 符: IR_surface_track_report
//主题 名    称: IR面目标参数报告
//主题 编    码: 1021
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 71
//主题 说    明: 
#define TOPIC_IR_SURFACE_TRACK_REPORT 1021
#define TOPIC_IR_SURFACE_TRACK_REPORT_LEN 71


//主题 标 识 符: IRST_act_req
//主题 名    称: IRST活动请求
//主题 编    码: 1017
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 60
//主题 说    明: 
#define TOPIC_IRST_ACT_REQ 1017
#define TOPIC_IRST_ACT_REQ_LEN 60


//主题 标 识 符: IRST_act_req_report
//主题 名    称: IRST_活动请求通告
//主题 编    码: 1104
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 7
//主题 说    明: 各子域发送该主题，以确认收到活动请求。活动请求通告是向发出请求的子域通告活动的执行结果，是该活动的终结状态消息。
#define TOPIC_IRST_ACT_REQ_REPORT 1104
#define TOPIC_IRST_ACT_REQ_REPORT_LEN 7


//主题 标 识 符: IRST_cooperation_tgt_report_I
//主题 名    称: 光雷协同目标参数报告_I
//主题 编    码: 3797
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 332
//主题 说    明: 
#define TOPIC_IRST_COOPERATION_TGT_REPORT_I 3797
#define TOPIC_IRST_COOPERATION_TGT_REPORT_I_LEN 332


//主题 标 识 符: IRST_cooperation_tgt_report_IFDL
//主题 名    称: 光雷协同目标参数报告_IFDL
//主题 编    码: 3798
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 450
//主题 说    明: 
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL 3798
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL_LEN 450


//主题 标 识 符: IRST_cooperation_tgt_report_IFDL1
//主题 名    称: 光雷协同目标参数报告_IFDL1
//主题 编    码: 3799
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 450
//主题 说    明: 
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL1 3799
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL1_LEN 450


//主题 标 识 符: IRST_cooperation_tgt_report_IFDL2
//主题 名    称: 光雷协同目标参数报告_IFDL2
//主题 编    码: 3800
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 450
//主题 说    明: 
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL2 3800
#define TOPIC_IRST_COOPERATION_TGT_REPORT_IFDL2_LEN 450


//主题 标 识 符: IRST_LOS
//主题 名    称: IRST传感器LOS参数
//主题 编    码: 1013
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 10
//主题 说    明: 
#define TOPIC_IRST_LOS 1013
#define TOPIC_IRST_LOS_LEN 10


//主题 标 识 符: IRST_operational_paras
//主题 名    称: IRST工作参数报告
//主题 编    码: 1011
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 100
//主题 说    明: 
#define TOPIC_IRST_OPERATIONAL_PARAS 1011
#define TOPIC_IRST_OPERATIONAL_PARAS_LEN 100


//主题 标 识 符: IRST_pixel_paras
//主题 名    称: IRST像元参数
//主题 编    码: 2900
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 50
//主题 说    明: 
#define TOPIC_IRST_PIXEL_PARAS 2900
#define TOPIC_IRST_PIXEL_PARAS_LEN 50


//主题 标 识 符: IRST_tgt_dot_correlation_data_report
//主题 名    称: IRST点迹协同目标关联数据报告
//主题 编    码: 3886
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 200
//主题 说    明: 
#define TOPIC_IRST_TGT_DOT_CORRELATION_DATA_REPORT 3886
#define TOPIC_IRST_TGT_DOT_CORRELATION_DATA_REPORT_LEN 200


//主题 标 识 符: link_member_nav_info_IFDL
//主题 名    称: 机间数据链编队成员导航信息
//主题 编    码: 2003
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL 2003
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL1
//主题 名    称: 机间数据链编队成员导航信息1
//主题 编    码: 3381
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL1 3381
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL1_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL2
//主题 名    称: 机间数据链编队成员导航信息2
//主题 编    码: 3382
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL2 3382
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL2_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL3
//主题 名    称: 机间数据链编队成员导航信息3
//主题 编    码: 4442
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL3 4442
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL3_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL4
//主题 名    称: 机间数据链编队成员导航信息4
//主题 编    码: 4443
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL4 4443
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL4_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL5
//主题 名    称: 机间数据链编队成员导航信息5
//主题 编    码: 4444
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL5 4444
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL5_LEN 45


//主题 标 识 符: link_member_nav_info_IFDL6
//主题 名    称: 机间数据链编队成员导航信息6
//主题 编    码: 4445
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 45
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL6 4445
#define TOPIC_LINK_MEMBER_NAV_INFO_IFDL6_LEN 45


//主题 标 识 符: link_net_nav_info_IFDL
//主题 名    称: 机间数据链网内成员导航信息
//主题 编    码: 4320
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_NET_NAV_INFO_IFDL 4320
#define TOPIC_LINK_NET_NAV_INFO_IFDL_LEN 496


//主题 标 识 符: link_net_nav_info_IFDL1
//主题 名    称: 机间数据链网内成员导航信息1
//主题 编    码: 4321
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 编队成员发送的位置和姿态消息
#define TOPIC_LINK_NET_NAV_INFO_IFDL1 4321
#define TOPIC_LINK_NET_NAV_INFO_IFDL1_LEN 496


//主题 标 识 符: list_knob_cmd
//主题 名    称: 俯仰滚轮指令
//主题 编    码: 3209
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 8
//主题 说    明: 
#define TOPIC_LIST_KNOB_CMD 3209
#define TOPIC_LIST_KNOB_CMD_LEN 8


//主题 标 识 符: load_int_check_report
//主题 名    称: 加载综合校验报告
//主题 编    码: 3412
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 303
//主题 说    明: 用于对各功能子域/单元反馈的文件校验结果进行判断后，统一发布综合数据校验结果信息；同时也用于画面加载状态及倒计时显示。
#define TOPIC_LOAD_INT_CHECK_REPORT 3412
#define TOPIC_LOAD_INT_CHECK_REPORT_LEN 303


//主题 标 识 符: LOAD_operational_paras_OMP
//主题 名    称: 软件加载工作参数报告_OMP
//主题 编    码: 3834
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 490
//主题 说    明: 利用空位新增任务系统运行模态信号，表征当前是否需要切换到维护加载态执行软件在线加载。
#define TOPIC_LOAD_OPERATIONAL_PARAS_OMP 3834
#define TOPIC_LOAD_OPERATIONAL_PARAS_OMP_LEN 490


//主题 标 识 符: LSR_calibrate_paras
//主题 名    称: 激光校轴参数
//主题 编    码: 2030
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 10
//主题 说    明: 
#define TOPIC_LSR_CALIBRATE_PARAS 2030
#define TOPIC_LSR_CALIBRATE_PARAS_LEN 10


//主题 标 识 符: mission_event_report
//主题 名    称: 战术任务事件报告
//主题 编    码: 412
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 32
//主题 说    明: 
#define TOPIC_MISSION_EVENT_REPORT 412
#define TOPIC_MISSION_EVENT_REPORT_LEN 32


//主题 标 识 符: NAV_paras
//主题 名    称: 导航参数报告
//主题 编    码: 439
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 
#define TOPIC_NAV_PARAS 439
#define TOPIC_NAV_PARAS_LEN 496


//主题 标 识 符: NAV_state
//主题 名    称: 导航状态报告
//主题 编    码: 436
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 100
//主题 说    明: 
#define TOPIC_NAV_STATE 436
#define TOPIC_NAV_STATE_LEN 100


//主题 标 识 符: NORMAL_Image_818
//主题 名    称: 通用原始图像
//主题 编    码: 4367
//主题 类    型: 流数据包
//主题 格式类型: 应用主题
//主题 长    度: 490
//主题 说    明: 
#define TOPIC_NORMAL_IMAGE_818 4367
#define TOPIC_NORMAL_IMAGE_818_LEN 490


//主题 标 识 符: PHM_Data_Event_MS_SUB
//主题 名    称: 健康管理_Event数据_MS_SUB
//主题 编    码: 2066
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 99
//主题 说    明: 
#define TOPIC_PHM_DATA_EVENT_MS_SUB 2066
#define TOPIC_PHM_DATA_EVENT_MS_SUB_LEN 99


//主题 标 识 符: PHM_Data_HMC_MS_SUB
//主题 名    称: 健康管理_HMC数据_MS_SUB
//主题 编    码: 2065
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 59
//主题 说    明: 
#define TOPIC_PHM_DATA_HMC_MS_SUB 2065
#define TOPIC_PHM_DATA_HMC_MS_SUB_LEN 59


//主题 标 识 符: PHM_Data_Raw_IRST
//主题 名    称: 健康管理_Raw数据_IRST
//主题 编    码: 2076
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 110
//主题 说    明: 
#define TOPIC_PHM_DATA_RAW_IRST 2076
#define TOPIC_PHM_DATA_RAW_IRST_LEN 110


//主题 标 识 符: PHM_report
//主题 名    称: 健康管理报告
//主题 编    码: 704
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 
#define TOPIC_PHM_REPORT 704
#define TOPIC_PHM_REPORT_LEN 496


//主题 标 识 符: Reconnaised_area_IR_2GCS_Event
//主题 名    称: 侦察覆盖区域参数_IR
//主题 编    码: 4558
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 95
//主题 说    明: 
#define TOPIC_RECONNAISED_AREA_IR_2GCS_EVENT 4558
#define TOPIC_RECONNAISED_AREA_IR_2GCS_EVENT_LEN 95


//主题 标 识 符: Reconnaised_area_TV_2GCS_Event
//主题 名    称: 侦察覆盖区域参数_TV
//主题 编    码: 4557
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 95
//主题 说    明: 
#define TOPIC_RECONNAISED_AREA_TV_2GCS_EVENT 4557
#define TOPIC_RECONNAISED_AREA_TV_2GCS_EVENT_LEN 95


//主题 标 识 符: slave_paras
//主题 名    称: 随动控制参数
//主题 编    码: 1015
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 200
//主题 说    明: 
#define TOPIC_SLAVE_PARAS 1015
#define TOPIC_SLAVE_PARAS_LEN 200


//主题 标 识 符: special_maint_data
//主题 名    称: 特殊维护数据
//主题 编    码: 955
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 170
//主题 说    明: 
#define TOPIC_SPECIAL_MAINT_DATA 955
#define TOPIC_SPECIAL_MAINT_DATA_LEN 170


//主题 标 识 符: SPI_paras
//主题 名    称: 系统关注点信息
//主题 编    码: 3037
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 30
//主题 说    明: 
#define TOPIC_SPI_PARAS 3037
#define TOPIC_SPI_PARAS_LEN 30


//主题 标 识 符: stream_data_file
//主题 名    称: 流数据_文件
//主题 编    码: 462
//主题 类    型: 流数据包
//主题 格式类型: 应用主题
//主题 长    度: 46
//主题 说    明: 
#define TOPIC_STREAM_DATA_FILE 462
#define TOPIC_STREAM_DATA_FILE_LEN 46


//主题 标 识 符: SW_config_info_report
//主题 名    称: 软件配置信息报告
//主题 编    码: 390
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 190
//主题 说    明: 本主题包括了子系统/子域的软件配置信息，同时，加载到子系统内部的配置库信息也作为软件配置信息上报。该主题提供了必要的信息用于校验软件（OFP和MDF）和硬件的匹配性。该主题也提供了一种记录软件和数据库配置信息的机制。
#define TOPIC_SW_CONFIG_INFO_REPORT 390
#define TOPIC_SW_CONFIG_INFO_REPORT_LEN 190


//主题 标 识 符: SW_load_state_report_OMP
//主题 名    称: 软件加载状态报告_OMP
//主题 编    码: 2064
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 40
//主题 说    明: 
#define TOPIC_SW_LOAD_STATE_REPORT_OMP 2064
#define TOPIC_SW_LOAD_STATE_REPORT_OMP_LEN 40


//主题 标 识 符: SYM_operational_paras
//主题 名    称: 系统管理工作参数报告
//主题 编    码: 485
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 496
//主题 说    明: 利用空位新增任务系统运行模态信号，表征当前是否需要切换到维护加载态执行软件在线加载。
#define TOPIC_SYM_OPERATIONAL_PARAS 485
#define TOPIC_SYM_OPERATIONAL_PARAS_LEN 496


//主题 标 识 符: SYM_security_state_report
//主题 名    称: 系统管理安全状态报告
//主题 编    码: 478
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 190
//主题 说    明: 
#define TOPIC_SYM_SECURITY_STATE_REPORT 478
#define TOPIC_SYM_SECURITY_STATE_REPORT_LEN 190


//主题 标 识 符: SYM_time_config_state_report
//主题 名    称: 系统管理时间配置状态报告
//主题 编    码: 481
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 6
//主题 说    明: 
#define TOPIC_SYM_TIME_CONFIG_STATE_REPORT 481
#define TOPIC_SYM_TIME_CONFIG_STATE_REPORT_LEN 6


//主题 标 识 符: SYM_time_report
//主题 名    称: 系统管理时间信息报告
//主题 编    码: 483
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 16
//主题 说    明: 
#define TOPIC_SYM_TIME_REPORT 483
#define TOPIC_SYM_TIME_REPORT_LEN 16


//主题 标 识 符: TDC_cursor_rate
//主题 名    称: TDC光标速率
//主题 编    码: 1016
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 5
//主题 说    明: 
#define TOPIC_TDC_CURSOR_RATE 1016
#define TOPIC_TDC_CURSOR_RATE_LEN 5


//主题 标 识 符: TDC_location
//主题 名    称: TDC光标位置参数
//主题 编    码: 1014
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 5
//主题 说    明: 
#define TOPIC_TDC_LOCATION 1014
#define TOPIC_TDC_LOCATION_LEN 5


//主题 标 识 符: VMS1394_STOF
//主题 名    称: VMS1394_STOF包
//主题 编    码: 61743
//主题 类    型: 数据块
//主题 格式类型: 飞控类型
//主题 长    度: 9
//主题 说    明: STOF主题定义不包含STOF包的1394头、1394数据CRC、垂直奇偶校验部分。
//               STOF包是由VMC发送的帧开始包，用于本地总线同步，并广播系统内的公共信息。VMC每15.0ms ± 150μs发送一个STOF包。
//               远程节点仅接收STOF包，不发送STOF包。
#define TOPIC_VMS1394_STOF 61743
#define TOPIC_VMS1394_STOF_LEN 9


//主题 标 识 符: work_state_report
//主题 名    称: 工作状态报告
//主题 编    码: 385
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 6
//主题 说    明: 当子系统/子域初始化完成、工作模式、工作状态信号的值发生改变、或系统请求修改工作模式、工作状态时，将该主题作为事件消息发送至任务系统健康管理子域和系统管理子域。另外当子系统执行BIT时，以160ms周期组播自检测进度。
#define TOPIC_WORK_STATE_REPORT 385
#define TOPIC_WORK_STATE_REPORT_LEN 6


//主题 标 识 符: work_state_report_OMP
//主题 名    称: 工作状态报告_OMP
//主题 编    码: 3832
//主题 类    型: 数据块
//主题 格式类型: 应用主题
//主题 长    度: 6
//主题 说    明: 当子系统/子域初始化完成、工作模式、工作状态信号的值发生改变、或系统请求修改工作模式、工作状态时，将该主题作为事件消息发送至任务系统健康管理子域和系统管理子域。另外当子系统执行BIT时，以160ms周期组播自检测进度。
#define TOPIC_WORK_STATE_REPORT_OMP 3832
#define TOPIC_WORK_STATE_REPORT_OMP_LEN 6

#endif