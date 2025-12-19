/**
 * @Author: Chongyang Liu
 * @Date:   2025-10-14 11:18:22
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-10-25 22:28:23
 */
//////////////////////////版本信息/////////////////////////
// 软件版本：ICDB3.32
// 数据版本：SE_A1.1.0版
// CPU类型：X86

#ifndef ICDB_ENUM_STRUCT_IRRM_H
#define ICDB_ENUM_STRUCT_IRRM_H

/////////////////////////////////枚举结构定义/////////////////////////////////

// 标识符: A818_ImageBitDepth
// 名  称: 图像位深
// 字  数: 3
// 说  明: 1、8、12、16、32等
typedef enum {
    V_A818_IMAGEBITDEPTH_NA     = 0, //
    V_A818_IMAGEBITDEPTH_BYTE8  = 1, // 8位
    V_A818_IMAGEBITDEPTH_BYTE12 = 2, // 12位
    V_A818_IMAGEBITDEPTH_BYTE16 = 3, // 16位
} A818_IMAGEBITDEPTH;

// 标识符: A818_SideViewDirection
// 名  称: 雷达侧视方向
// 字  数: 2
// 说  明: 雷达专用，表示雷达侧视方向。条带SAR模式或SAR-GMTI模式下：1=左侧视、2=右侧视；其它模式填0
typedef enum {
    V_A818_SIDEVIEWDIRECTION_NA    = 0, //
    V_A818_SIDEVIEWDIRECTION_LEFT  = 1, // 左侧视
    V_A818_SIDEVIEWDIRECTION_RIGHT = 2, // 右侧视
} A818_SIDEVIEWDIRECTION;

// 标识符: above_ground_height_type
// 名  称: 地形相对高度类型
// 字  数: 8
// 说  明: 0：表示地形高度采用DTED来源；
//         1：表示无线电测相对地形高度；
//         2：表示采用装订气压高度作为地形高度。
typedef enum {
    V_ABOVE_GROUND_HEIGHT_TYPE_DTED  = 0, // 数字地形高程
    V_ABOVE_GROUND_HEIGHT_TYPE_RADIO = 1, // 无线电测高
    V_ABOVE_GROUND_HEIGHT_TYPE_BARO  = 2, // 装订气压高度
    V_ABOVE_GROUND_HEIGHT_TYPE_INIT  = 3, // 初始位置高度
} ABOVE_GROUND_HEIGHT_TYPE;

// 标识符: AC_ID
// 名  称: 飞机ID
// 字  数: 4
// 说  明: 0 歼-20飞机01状态01-05架
//         1 歼-20飞机01状态06架起
//         2 歼-20飞机02状态，不装航炮
//         3 歼-20飞机02状态，装航炮
//         4 歼-20双座机，配装涡扇-10C
//         5 歼-20双座机，配装涡扇-15
//         6 歼-20A飞机，配装涡扇-10C
//         7 歼-20A飞机，配装涡扇-15
typedef enum {
    V_AC_ID_INVALID   = 0, // 无效
    V_AC_ID_STA01     = 1, // 01状态无航炮
    V_AC_ID_STA02     = 2, // 02状态无航炮
    V_AC_ID_STA02_GUN = 3, // 02状态有航炮
    V_AC_ID_ISC_WS10C = 4, // 双座-涡扇10C发动机
    V_AC_ID_ISC_WS15  = 5, // 双座-涡扇15发动机
    V_AC_ID_A_WS10C   = 6, // 20A-涡扇10C发动机
    V_AC_ID_A_WS15    = 7, // 20A-涡扇15发动机
} AC_ID;

// 标识符: act_refused_reason
// 名  称: 拒绝请求原因
// 字  数: 8
// 说  明: 仅当活动状态等于NACK的时候，该信号有效：
//         1.无效的参数：活动请求所包含的附加参数无效或不存在。
//         2.无效的活动：活动请求的类型无效，或者不能被执行。
//         3.无效的请求方：接收方不能识别发起请求的子域。例如请求子域ID无效。
//         4.辐射限制：受传感器计划或飞行员控制的影响，传感器不允许辐射，因而不能执行所请求的活动。
//         5.时间限制：受传感器本身限制，在请求的时间内不能完成所请求的活动；或者因为在请求的时间范围内，该活动不被允许。
//         6.安全因素：因安全因素不能完成所请求的活动。例如地面不允许辐射，当前状态不允许开舱，不允许激光发射，不允许发射干扰弹等。
//         7.无法执行：活动执行方因故障、或者非操作状态等不能完成所请求的活动。例如设备处于测试状态，但要求设备进行目标测量等。
typedef enum {
    V_ACT_REFUSED_REASON_NA                = 0, //
    V_ACT_REFUSED_REASON_INVALID_PARA      = 1, // 无效的参数
    V_ACT_REFUSED_REASON_INVALID_ACTIVITY  = 2, // 无效的活动
    V_ACT_REFUSED_REASON_INVALID_REQUESTER = 3, // 无效的请求者
    V_ACT_REFUSED_REASON_EMCON_CONSTRAINT  = 4, // 辐射限制
    V_ACT_REFUSED_REASON_TIME_LIMIT        = 5, // 时间限制
    V_ACT_REFUSED_REASON_SAFETY_LIMITATION = 6, // 安全因素
    V_ACT_REFUSED_REASON_CANNOT_PERFORM    = 7, // 无法执行
} ACT_REFUSED_REASON;

// 标识符: activity_state
// 名  称: 活动状态
// 字  数: 8
// 说  明: NACK：活动未能开始时，需要发送。不论是因为错误的请求，还是请求不能执行，在拒绝请求原因信号中进行详细说明。
//         CANCELLED：当活动被取消，或者已经开始但被中止。可能是因为系统资源丢失，或者系统进入不能运行该请求的状态。
//         COMPLETED：活动正常完成，并从活动清单中已清除。
//         ECHO：表示收到活动请求。
typedef enum {
    V_ACTIVITY_STATE_NA        = 0, //
    V_ACTIVITY_STATE_NACK      = 1, // 拒绝
    V_ACTIVITY_STATE_CANCELLED = 2, // 已取消
    V_ACTIVITY_STATE_COMPLETED = 3, // 已完成
    V_ACTIVITY_STATE_ECHO      = 4, // 应答
} ACTIVITY_STATE;

// 标识符: ADS_data_channel_state
// 名  称: 大气数据通道选择状态
// 字  数: 8
// 说  明:
typedef enum {
    V_ADS_DATA_CHANNEL_STATE_NA        = 0, //
    V_ADS_DATA_CHANNEL_STATE_CHANNEL_A = 1, //
    V_ADS_DATA_CHANNEL_STATE_CHANNEL_B = 2, //
    V_ADS_DATA_CHANNEL_STATE_CHANNEL_C = 3, //
    V_ADS_DATA_CHANNEL_STATE_CHANNEL_D = 4, //
} ADS_DATA_CHANNEL_STATE;

// 标识符: align_done_state
// 名  称: 对准完成状态
// 字  数: 8
// 说  明:
typedef enum {
    V_ALIGN_DONE_STATE_NA               = 0, //
    V_ALIGN_DONE_STATE_FAST_NAV_RDY     = 1, // 快速对准完成
    V_ALIGN_DONE_STATE_DEGRADED_NAV_RDY = 2, // 降级罗经对准完成
    V_ALIGN_DONE_STATE_GC_NAV_RDY       = 3, // 罗经对准完成
    V_ALIGN_DONE_STATE_ALIGN_PAUSE      = 4, // 对准暂停
    V_ALIGN_DONE_STATE_ALIGN_FAILED     = 5, // 对准失败
    V_ALIGN_DONE_STATE_TRANSFER_RDY     = 6, // 传递对准完成
    V_ALIGN_DONE_STATE_FLIT_RDY         = 7, // 空中对准完成
} ALIGN_DONE_STATE;

// 标识符: angular_precision
// 名  称: 角度精度
// 字  数: 8
// 说  明: 载机对目标的测角误差小于等于0.25度时，角度精度为精
//         载机对目标的测角误差小于等于1度且大于0.25度时，角度精度为粗
//         载机对目标的测角误差小于等于3度且大于1度时，角度精度为极粗
//         载机对目标的测角误差大于3度时，角度精度为无效
typedef enum {
    V_ANGULAR_PRECISION_NA          = 0, //
    V_ANGULAR_PRECISION_PRECISE     = 1, // 精
    V_ANGULAR_PRECISION_COARSE      = 2, // 粗
    V_ANGULAR_PRECISION_VERY_COARSE = 3, // 极粗
    V_ANGULAR_PRECISION_INVALID     = 4, // 无效
} ANGULAR_PRECISION;

// 标识符: app_state
// 名  称: 应用软件状态
// 字  数: 8
// 说  明: 正常运行时，应用软件状态仅为正常工作或非正常工作；
//         仅在飞管系统进入OFP加载模式后，SYMM将所有功能单元的应用软件状态置为SW_LOAD，触发各子系统进入维护加载态。
//         若任务系统处于正常运行态时，但某子系统或子系统某模块运行在软件加载态，则对应子系统状态置为SW_load。
typedef enum {
    V_APP_STATE_NA       = 0, // 无意义
    V_APP_STATE_NORMAL   = 1, // 正常工作
    V_APP_STATE_IMPROPER = 2, // 非正常工作
    V_APP_STATE_SW_LOAD  = 9, // 软件加载态
} APP_STATE;

// 标识符: apr_phase
// 名  称: 进场着陆阶段
// 字  数: 8
// 说  明: 进场着陆的各个阶段
typedef enum {
    V_APR_PHASE_NA  = 0, //
    V_APR_PHASE_FAF = 1, // FAF阶段
    V_APR_PHASE_RWY = 2, // RWY阶段
} APR_PHASE;

// 标识符: APR_sensor_selected
// 名  称: 进场着陆传感器选择
// 字  数: 8
// 说  明:
typedef enum {
    V_APR_SENSOR_SELECTED_NA    = 0, //
    V_APR_SENSOR_SELECTED_MLS   = 1, // 微波
    V_APR_SENSOR_SELECTED_ILS   = 2, // 仪表
    V_APR_SENSOR_SELECTED_TACAN = 3, // 塔康
    V_APR_SENSOR_SELECTED_SCA   = 4, // 自主
} APR_SENSOR_SELECTED;

// 标识符: area_radius
// 名  称: 区域半径
// 字  数: 8
// 说  明:
typedef enum {
    V_AREA_RADIUS_LEVEL0 = 0, // 0米
    V_AREA_RADIUS_LEVEL1 = 1, // 100米
    V_AREA_RADIUS_LEVEL2 = 2, // 200米
    V_AREA_RADIUS_LEVEL3 = 3, // 300米
    V_AREA_RADIUS_LEVEL4 = 4, // 500米
    V_AREA_RADIUS_LEVEL5 = 5, // 1000米
    V_AREA_RADIUS_LEVEL6 = 6, // 2000米
    V_AREA_RADIUS_LEVEL7 = 7, // 3000米
    V_AREA_RADIUS_LEVEL8 = 8, // 5000米
    V_AREA_RADIUS_LEVEL9 = 9, // 10000米
} AREA_RADIUS;

// 标识符: Area_validity
// 名  称: 区域有效性
// 字  数: 8
// 说  明:
typedef enum {
    V_AREA_VALIDITY_INVALID = 0, // 无效
    V_AREA_VALIDITY_VALID   = 1, // 有效
} AREA_VALIDITY;

// 标识符: AREA1_CHG
// 名  称: 区域1修改标识
// 字  数: 2
// 说  明:
typedef enum {
    V_AREA1_CHG_NO     = 0, // 不修改
    V_AREA1_CHG_YES    = 1, // 修改
    V_AREA1_CHG_DELETE = 2, // 删除
} AREA1_CHG;

// 标识符: AREA2_CHG
// 名  称: 区域2修改标识
// 字  数: 2
// 说  明:
typedef enum {
    V_AREA2_CHG_NO     = 0, // 不修改
    V_AREA2_CHG_YES    = 1, // 修改
    V_AREA2_CHG_DELETE = 2, // 删除
} AREA2_CHG;

// 标识符: AREA3_CHG
// 名  称: 区域3修改标识
// 字  数: 2
// 说  明:
typedef enum {
    V_AREA3_CHG_NO     = 0, // 不修改
    V_AREA3_CHG_YES    = 1, // 修改
    V_AREA3_CHG_DELETE = 2, // 删除
} AREA3_CHG;

// 标识符: attack_state
// 名  称: 目标攻击态势
// 字  数: 8
// 说  明: 前向：迎头
//         后向：尾后
typedef enum {
    V_ATTACK_STATE_NA    = 0, //
    V_ATTACK_STATE_FRONT = 1, // 前向
    V_ATTACK_STATE_REAR  = 2, // 后向
} ATTACK_STATE;

// 标识符: AV1394_net_state
// 名  称: 航电1394网络状态
// 字  数: 8
// 说  明:
typedef enum {
    V_AV1394_NET_STATE_NA       = 0, // 未知或无意义
    V_AV1394_NET_STATE_OFF_LINE = 1, // 通信断
    V_AV1394_NET_STATE_ON_LINE  = 2, // 在网
} AV1394_NET_STATE;

// 标识符: AZ_HEIGHT_CHG
// 名  称: 方位优先高度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_AZ_HEIGHT_CHG_NO  = 0, // 不修改
    V_AZ_HEIGHT_CHG_YES = 1, // 修改
} AZ_HEIGHT_CHG;

// 标识符: BDS_C_P_cmd
// 名  称: BD C引P 指令
// 字  数: 8
// 说  明:
typedef enum {
    V_BDS_C_P_CMD_INVALID = 0, // 军码捕获
    V_BDS_C_P_CMD_VALID   = 1, // 民码引导军码
} BDS_C_P_CMD;

// 标识符: bingo_envlope_set_type
// 名  称: bingo剖面设置方式
// 字  数: 8
// 说  明:
typedef enum {
    V_BINGO_ENVLOPE_SET_TYPE_AUTO   = 0, // 自动
    V_BINGO_ENVLOPE_SET_TYPE_MANUAL = 1, // 手动
} BINGO_ENVLOPE_SET_TYPE;

// 标识符: bit_mode
// 名  称: 自检测模式
// 字  数: 8
// 说  明: 只有IBIT和MBIT可以作为命令下发
typedef enum {
    V_BIT_MODE_NA   = 0, //
    V_BIT_MODE_POB  = 1, // 上电自检测
    V_BIT_MODE_IBIT = 2, // 启动自检测
    V_BIT_MODE_CBIT = 3, // 周期自检测
    V_BIT_MODE_MBIT = 4, // 维护自检测
} BIT_MODE;

// 标识符: block_id
// 名  称: 分块ID
// 字  数: 8
// 说  明:
typedef enum {
    V_BLOCK_ID_NA         = 0, //
    V_BLOCK_ID_LEFT_UP    = 1, // 上左
    V_BLOCK_ID_UP         = 2, // 上
    V_BLOCK_ID_RIGHT_UP   = 3, // 上右
    V_BLOCK_ID_LEFT_MID   = 4, // 中左
    V_BLOCK_ID_MID        = 5, // 中
    V_BLOCK_ID_RIGHT_MID  = 6, // 中右
    V_BLOCK_ID_LEFT_DOWN  = 7, // 下左
    V_BLOCK_ID_DOWN       = 8, // 下
    V_BLOCK_ID_RIGHT_DOWN = 9, // 下右
} BLOCK_ID;

// 标识符: burst_tgt_flag
// 名  称: 猝发目标标志
// 字  数: 8
// 说  明:
typedef enum {
    V_BURST_TGT_FLAG_NONE           = 0, // 非猝发目标
    V_BURST_TGT_FLAG_IRST_BURST     = 1, // 光雷猝发探测目标
    V_BURST_TGT_FLAG_HG_BURST       = 2, // 电子战HG猝发探测目标
    V_BURST_TGT_FLAG_ESM_BURST      = 3, // 电子战ESM猝发探测目标
    V_BURST_TGT_FLAG_IRST_HG_BURST  = 4, // 光雷加电子战HG猝发探测目标
    V_BURST_TGT_FLAG_IRST_ESM_BURST = 5, // 光雷加电子战ESM猝发探测目标
} BURST_TGT_FLAG;

// 标识符: calibrate_data_validity
// 名  称: 光轴偏差参数有效性
// 字  数: 8
// 说  明:
typedef enum {
    V_CALIBRATE_DATA_VALIDITY_NO  = 0, // 无效
    V_CALIBRATE_DATA_VALIDITY_YES = 1, // 有效
} CALIBRATE_DATA_VALIDITY;

// 标识符: calibrate_mode_state
// 名  称: 校轴模式状态
// 字  数: 8
// 说  明:
typedef enum {
    V_CALIBRATE_MODE_STATE_OFF = 0, // 非校轴模式
    V_CALIBRATE_MODE_STATE_ON  = 1, // 校轴模式
} CALIBRATE_MODE_STATE;

// 标识符: cap_phase
// 名  称: 战斗巡逻阶段
// 字  数: 8
// 说  明:
typedef enum {
    V_CAP_PHASE_NA      = 0, // 无意义
    V_CAP_PHASE_ACQUIRE = 1, // 捕获阶段
    V_CAP_PHASE_CAP     = 2, // 巡逻阶段
    V_CAP_PHASE_OFFCAP  = 3, // 脱离阶段
} CAP_PHASE;

// 标识符: CDI_types
// 名  称: 航线偏差指引类型
// 字  数: 8
// 说  明: 航线偏差指引类型，表示航线偏差指示符根据何种传感器数据指示。
typedef enum {
    V_CDI_TYPES_NA    = 0, //
    V_CDI_TYPES_STPT  = 1, // 航路类型
    V_CDI_TYPES_TACAN = 2, // 塔康类型
    V_CDI_TYPES_MLS   = 3, // 微波着陆类型
    V_CDI_TYPES_ILS   = 4, // 仪表着陆类型
    V_CDI_TYPES_PTOP  = 5, // 对点飞行类型
} CDI_TYPES;

// 标识符: Conflict_TDC_Control
// 名  称: 冲突控制权_TDC
// 字  数: 8
// 说  明:
typedef enum {
    V_CONFLICT_TDC_CONTROL_NA        = 0, //
    V_CONFLICT_TDC_CONTROL_FRONTSEAT = 1, // 前舱
    V_CONFLICT_TDC_CONTROL_BACKSEAT  = 2, // 后舱
} CONFLICT_TDC_CONTROL;

// 标识符: cool_state
// 名  称: 制冷状态
// 字  数: 2
// 说  明:
typedef enum {
    V_COOL_STATE_NA        = 0, //
    V_COOL_STATE_COOLING   = 1, // 正在制冷
    V_COOL_STATE_COOLED    = 2, // 制冷好
    V_COOL_STATE_COOL_FAIL = 3, // 制冷故障
} COOL_STATE;

// 标识符: cpeg_tgt_flag
// 名  称: CPEG目标状态
// 字  数: 8
// 说  明:
typedef enum {
    V_CPEG_TGT_FLAG_NONE           = 0, // 非CPEG目标
    V_CPEG_TGT_FLAG_CPEG_MHT       = 1, // MHT定位中
    V_CPEG_TGT_FLAG_CPEG_SUCCEED   = 2, // 协同成功
    V_CPEG_TGT_FLAG_CPEG_MHT_FAIL  = 3, // MHT协同失败
    V_CPEG_TGT_FLAG_CPEG_BACK_FAIL = 4, // 反馈协同失败
} CPEG_TGT_FLAG;

// 标识符: cruise_mode
// 名  称: 巡航方式
// 字  数: 8
// 说  明: 巡航的方式
typedef enum {
    V_CRUISE_MODE_NA           = 0, //
    V_CRUISE_MODE_MAXDISTANCE  = 1, // 最大航程
    V_CRUISE_MODE_MAXENDURANCE = 2, // 最大航时
    V_CRUISE_MODE_CAP          = 3, // 战斗巡逻
} CRUISE_MODE;

// 标识符: cue_mission_state
// 名  称: 提示任务执行状态
// 字  数: 8
// 说  明:
typedef enum {
    V_CUE_MISSION_STATE_NA       = 0, //
    V_CUE_MISSION_STATE_TAKING   = 1, // 正在执行
    V_CUE_MISSION_STATE_COMPLETE = 2, // 已完成
    V_CUE_MISSION_STATE_CANCEL   = 3, // 已取消
    V_CUE_MISSION_STATE_INTERUPT = 4, // 中断
} CUE_MISSION_STATE;

// 标识符: cue_way_set
// 名  称: 提示搜索方式
// 字  数: 8
// 说  明:
typedef enum {
    V_CUE_WAY_SET_NA             = 0, //
    V_CUE_WAY_SET_CUE_MANUAL     = 1, // 提示搜索_手动
    V_CUE_WAY_SET_BURST          = 2, // 猝发测距
    V_CUE_WAY_SET_SECTOR         = 3, // 扇区扫描
    V_CUE_WAY_SET_CUE_AUTO       = 4, // 提示搜索_自动
    V_CUE_WAY_SET_BURST_MANUAL   = 5, // 猝发测距_手动
    V_CUE_WAY_SET_CUE_COOPERTIVE = 6, // 编队协同提示搜索
} CUE_WAY_SET;

// 标识符: D_HEIGHT_CHG
// 名  称: 距离优先高度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_D_HEIGHT_CHG_NO  = 0, // 不修改
    V_D_HEIGHT_CHG_YES = 1, // 修改
} D_HEIGHT_CHG;

// 标识符: data_load_status
// 名  称: 数据加载状态
// 字  数: 8
// 说  明:
typedef enum {
    V_DATA_LOAD_STATUS_NA       = 0, // 无意义
    V_DATA_LOAD_STATUS_WAITTING = 1, // 等待加载
    V_DATA_LOAD_STATUS_LOADING  = 2, // 加载中
    V_DATA_LOAD_STATUS_LOAD_FIN = 3, // 加载结束
} DATA_LOAD_STATUS;

// 标识符: data_monitor_above_below
// 名  称: 数据监控数值范围
// 字  数: 8
// 说  明: 数据监控数值范围
typedef enum {
    V_DATA_MONITOR_ABOVE_BELOW_NA         = 0, //
    V_DATA_MONITOR_ABOVE_BELOW_DATA_ABOVE = 1, // 高于
    V_DATA_MONITOR_ABOVE_BELOW_DATA_BELOW = 2, // 低于
} DATA_MONITOR_ABOVE_BELOW;

// 标识符: data_monitor_type
// 名  称: 数据监控类型
// 字  数: 8
// 说  明: 导航事件：数据监控类型
typedef enum {
    V_DATA_MONITOR_TYPE_NA                            = 0, //
    V_DATA_MONITOR_TYPE_AC_GROUND_SPEED               = 1, // 载机地速
    V_DATA_MONITOR_TYPE_AC_CAL_AIR_SPEED              = 2, // 载机校准空速
    V_DATA_MONITOR_TYPE_AC_PRESSURE_INERTIAL_ALT      = 3, // 载机惯性气压高度
    V_DATA_MONITOR_TYPE_AC_BARO_PRESSURE_INERTIAL_ALT = 4, // 载机惯性气压参考高度
} DATA_MONITOR_TYPE;

// 标识符: datalink_contribute_flag
// 名  称: 链路贡献标识
// 字  数: 8
// 说  明: 按位定义各链路对射击列表目标的贡献，如：
//         VU有贡献，值=1；
//         VU和IFDL都有三维目标贡献，值=1+4。
typedef enum {
    V_DATALINK_CONTRIBUTE_FLAG_NO       = 0,  // 无贡献
    V_DATALINK_CONTRIBUTE_FLAG_VU       = 1,  // VU链有贡献
    V_DATALINK_CONTRIBUTE_FLAG_JIDS     = 2,  // JIDS链有贡献
    V_DATALINK_CONTRIBUTE_FLAG_IFDL_3D  = 4,  // IFDL链有3维目标贡献
    V_DATALINK_CONTRIBUTE_FLAG_IFDL_2D  = 8,  // IFDL链有2维目标贡献
    V_DATALINK_CONTRIBUTE_FLAG_SAT_LINK = 16, // 卫通链有贡献
    V_DATALINK_CONTRIBUTE_FLAG_ADS_B_IN = 32, // ADS_B_IN有贡献
} DATALINK_CONTRIBUTE_FLAG;

// 标识符: desired_command_types
// 名  称: 期望指令类型
// 字  数: 8
// 说  明:
typedef enum {
    V_DESIRED_COMMAND_TYPES_NA           = 0, // 空
    V_DESIRED_COMMAND_TYPES_DLINK        = 1, // 数据链命令
    V_DESIRED_COMMAND_TYPES_TOT          = 2, // 到达时间
    V_DESIRED_COMMAND_TYPES_MAXDISTANCE  = 3, // 最大航程
    V_DESIRED_COMMAND_TYPES_MAXENDURANCE = 4, // 最大航时
    V_DESIRED_COMMAND_TYPES_BINGO        = 5, // 经济返航
} DESIRED_COMMAND_TYPES;

// 标识符: Destroy_Key_cmd1
// 名  称: 毁钥指令1
// 字  数: 8
// 说  明: "仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
//
typedef enum {
    V_DESTROY_KEY_CMD1_INVALID = 0,   // 无效
    V_DESTROY_KEY_CMD1_VALID   = 165, // 有效
} DESTROY_KEY_CMD1;

// 标识符: Destroy_Key_cmd2_
// 名  称: 毁钥指令2_
// 字  数: 8
// 说  明: "仅当毁钥指令1为0xA5，毁钥指令2为0x5A持续300ms时，认为毁钥指令有效"
//
typedef enum {
    V_DESTROY_KEY_CMD2__INVALID = 0,  // 无效
    V_DESTROY_KEY_CMD2__VALID   = 90, // 有效
} DESTROY_KEY_CMD2_;

// 标识符: development_company
// 名  称: 研制厂家
// 字  数: 8
// 说  明: 以此来区分三个厂家
typedef enum {
    V_DEVELOPMENT_COMPANY_NA      = 0, //
    V_DEVELOPMENT_COMPANY_AVIC613 = 1, // 613所
    V_DEVELOPMENT_COMPANY_CIOMP   = 2, // 长光所
    V_DEVELOPMENT_COMPANY_CTOTC   = 3, // 长春通视
} DEVELOPMENT_COMPANY;

// 标识符: device_work_mode
// 名  称: 设备工作模式
// 字  数: 8
// 说  明: 共用，对于侦察雷达表示雷达成像模式；对于综合光电表示相机工作模式。
typedef enum {
    V_DEVICE_WORK_MODE_NA            = 0,  //
    V_DEVICE_WORK_MODE_WIDE_IMAGING  = 1,  // 广域成像
    V_DEVICE_WORK_MODE_ZONE_4KM      = 2,  // 4KM区域成像
    V_DEVICE_WORK_MODE_ZONE_10KM     = 3,  // 10KM区域成像
    V_DEVICE_WORK_MODE_ZONE_20KM     = 4,  // 20KM区域成像
    V_DEVICE_WORK_MODE_ZONE_SLV      = 5,  // 区域监视
    V_DEVICE_WORK_MODE_FCS_SAR_DOT1  = 6,  // 聚束SAR0.1
    V_DEVICE_WORK_MODE_FCS_SAR_DOT2  = 7,  // 聚束SAR0.2
    V_DEVICE_WORK_MODE_FCS_SAR_DOT3  = 8,  // 聚束SAR0.3
    V_DEVICE_WORK_MODE_TRIP_SAR_DOT3 = 9,  // 条带SAR0.3
    V_DEVICE_WORK_MODE_TRIP_SAR_DOT5 = 10, // 条带SAR0.5
    V_DEVICE_WORK_MODE_SAR_GMTI_5    = 11, // SAR-GMTI5米
    V_DEVICE_WORK_MODE_SAR_GMTI_10   = 12, // SAR-GMTI10米
    V_DEVICE_WORK_MODE_ISAR          = 13, // ISAR
} DEVICE_WORK_MODE;

// 标识符: dim_CHG
// 名  称: 调光修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_DIM_CHG_NO  = 0, // 不修改
    V_DIM_CHG_YES = 1, // 修改
} DIM_CHG;

// 标识符: dipper_operational_mod
// 名  称: 北斗工作模式
// 字  数: 8
// 说  明:
typedef enum {
    V_DIPPER_OPERATIONAL_MOD_NA            = 0, //
    V_DIPPER_OPERATIONAL_MOD_ARMY_CODE     = 1, // 军码
    V_DIPPER_OPERATIONAL_MOD_CIVILIAN_CODE = 2, // 民码
} DIPPER_OPERATIONAL_MOD;

// 标识符: el_chg_tag
// 名  称: 俯仰修改标识
// 字  数: 8
// 说  明:
typedef enum {
    V_EL_CHG_TAG_NA                 = 0, //
    V_EL_CHG_TAG_VOLUM1_CHG         = 1, // 主区修改
    V_EL_CHG_TAG_VOLUM2_CHG         = 2, // 辅区修改
    V_EL_CHG_TAG_DISGUISE_VOLUM_CHG = 3, // 伪装区修改
    V_EL_CHG_TAG_WA_EL_CHG          = 4, // 气象区修改
} EL_CHG_TAG;

// 标识符: EM_level
// 名  称: 辐射等级
// 字  数: 8
// 说  明: 辐射级别控制参数。等级1配置为全静默等级，等级5配置为无限制辐射等级，中间级别可根据任务配置。
typedef enum {
    V_EM_LEVEL_NA     = 0, //
    V_EM_LEVEL_EMCON1 = 1, // 辐射级别1
    V_EM_LEVEL_EMCON2 = 2, // 辐射级别2
    V_EM_LEVEL_EMCON3 = 3, // 辐射级别3
    V_EM_LEVEL_EMCON4 = 4, // 辐射级别4
    V_EM_LEVEL_EMCON5 = 5, // 辐射级别5
} EM_LEVEL;

// 标识符: EnableMark_AP_PreGLS
// 名  称: 允许标志_自动驾驶预备GLS
// 字  数: 8
// 说  明:
typedef enum {
    V_ENABLEMARK_AP_PREGLS_DISABLE = 0, // 不允许
    V_ENABLEMARK_AP_PREGLS_ENABLE  = 1, // 允许
} ENABLEMARK_AP_PREGLS;

// 标识符: EnableMark_AT_TOT
// 名  称: 允许标志_自动油门定时到达
// 字  数: 8
// 说  明:
typedef enum {
    V_ENABLEMARK_AT_TOT_DISABLE = 0, // 不允许
    V_ENABLEMARK_AT_TOT_ENABLE  = 1, // 允许
} ENABLEMARK_AT_TOT;

// 标识符: END_ANGLE_CHG
// 名  称: 结束角度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_END_ANGLE_CHG_NO  = 0, // 不修改
    V_END_ANGLE_CHG_YES = 1, // 修改
} END_ANGLE_CHG;

// 标识符: ENHANCE_CHG
// 名  称: 增强修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_ENHANCE_CHG_NO  = 0, // 不修改
    V_ENHANCE_CHG_YES = 1, // 修改
} ENHANCE_CHG;

// 标识符: environmnet_type
// 名  称: 环境类型
// 字  数: 8
// 说  明:
typedef enum {
    V_ENVIRONMNET_TYPE_NA       = 0, //
    V_ENVIRONMNET_TYPE_AUTO     = 1, // 自动
    V_ENVIRONMNET_TYPE_SEA      = 2, // 海洋
    V_ENVIRONMNET_TYPE_DESERT   = 3, // 沙漠
    V_ENVIRONMNET_TYPE_CITY     = 4, // 城市
    V_ENVIRONMNET_TYPE_MONTAIN  = 5, // 山区
    V_ENVIRONMNET_TYPE_GRASS    = 6, // 草原
    V_ENVIRONMNET_TYPE_SNOW     = 7, // 雪原
    V_ENVIRONMNET_TYPE_HIGHLAND = 8, // 高原
    V_ENVIRONMNET_TYPE_FOREST   = 9, // 森林
} ENVIRONMNET_TYPE;

// 标识符: ET_tgt_ID
// 名  称: ET_目标ID
// 字  数: 8
// 说  明: 未匹配上	0
//         目标训练ID	1～180
//         保留	181-253
//         评估分系统	254
//         广播                        255
// typedef enum
//{
// }ET_TGT_ID;

// 标识符: faf_turn_dir_mode
// 名  称: 进场定位转弯方向模式
// 字  数: 8
// 说  明:
typedef enum {
    V_FAF_TURN_DIR_MODE_LEFT  = 0, // 左转弯
    V_FAF_TURN_DIR_MODE_RIGHT = 1, // 右转弯
    V_FAF_TURN_DIR_MODE_AUTO  = 2, // 自动
} FAF_TURN_DIR_MODE;

// 标识符: fast_climb_mode
// 名  称: 最速爬升模式
// 字  数: 8
// 说  明:
typedef enum {
    V_FAST_CLIMB_MODE_OFF               = 0, // 关
    V_FAST_CLIMB_MODE_MODE_ALT          = 1, // 输入高度模式
    V_FAST_CLIMB_MODE_MODE_ALT_VELOCITY = 2, // 输入高度速度模式
    V_FAST_CLIMB_MODE_MODE_NONE         = 3, // 无输入高度速度模式
} FAST_CLIMB_MODE;

// 标识符: fast_climb_strategy
// 名  称: 最速爬升策略
// 字  数: 8
// 说  明:
typedef enum {
    V_FAST_CLIMB_STRATEGY_EQUAL_MA         = 0, // 等马赫爬升
    V_FAST_CLIMB_STRATEGY_EQUAL_TRUE_SPEED = 1, // 等真速爬升
    V_FAST_CLIMB_STRATEGY_EQUAL_SEP        = 2, // 等SEP线爬升
    V_FAST_CLIMB_STRATEGY_ACCELERATION     = 3, // 匀加速爬升
    V_FAST_CLIMB_STRATEGY_ACC_EM           = 4, // 先水平加速再等马赫爬升
} FAST_CLIMB_STRATEGY;

// 标识符: FC_net_state
// 名  称: FC网络状态
// 字  数: 8
// 说  明:
typedef enum {
    V_FC_NET_STATE_NA       = 0, // 未知或无意义
    V_FC_NET_STATE_OFF_LINE = 1, // 通信断
    V_FC_NET_STATE_ON_LINE  = 2, // 在网
} FC_NET_STATE;

// 标识符: fly_plan
// 名  称: 飞行计划号
// 字  数: 8
// 说  明: 飞行计划，包括A~K（I除外）计划、标记点、波塞点、标定点、初始位置、最近机场、机场
typedef enum {
    V_FLY_PLAN_DEFAULT         = 0,   // 缺省
    V_FLY_PLAN_PLAN_1          = 1,   // 飞行计划1
    V_FLY_PLAN_PLAN_2          = 2,   // 飞行计划2
    V_FLY_PLAN_PLAN_3          = 3,   // 飞行计划3
    V_FLY_PLAN_PLAN_4          = 4,   // 飞行计划4
    V_FLY_PLAN_PLAN_5          = 5,   // 飞行计划5
    V_FLY_PLAN_PLAN_6          = 6,   // 飞行计划6
    V_FLY_PLAN_PLAN_7          = 7,   // 飞行计划7
    V_FLY_PLAN_PLAN_8          = 8,   // 飞行计划8
    V_FLY_PLAN_PLAN_9          = 9,   // 飞行计划9
    V_FLY_PLAN_PLAN_10         = 10,  // 飞行计划10
    V_FLY_PLAN_PLAN_11         = 11,  // 飞行计划11
    V_FLY_PLAN_PLAN_12         = 12,  // 飞行计划12
    V_FLY_PLAN_PLAN_13         = 13,  // 飞行计划13
    V_FLY_PLAN_PLAN_14         = 14,  // 飞行计划14
    V_FLY_PLAN_PLAN_15         = 15,  // 飞行计划15
    V_FLY_PLAN_PLAN_16         = 16,  // 飞行计划16
    V_FLY_PLAN_PLAN_17         = 17,  // 飞行计划17
    V_FLY_PLAN_PLAN_18         = 18,  // 飞行计划18
    V_FLY_PLAN_PLAN_19         = 19,  // 飞行计划19
    V_FLY_PLAN_PLAN_20         = 20,  // 飞行计划20
    V_FLY_PLAN_PLAN_21         = 21,  // 飞行计划21
    V_FLY_PLAN_PLAN_22         = 22,  // 飞行计划22
    V_FLY_PLAN_PLAN_23         = 23,  // 飞行计划23
    V_FLY_PLAN_PLAN_24         = 24,  // 飞行计划24
    V_FLY_PLAN_PLAN_25         = 25,  // 飞行计划25
    V_FLY_PLAN_PLAN_26         = 26,  // 飞行计划26
    V_FLY_PLAN_PLAN_27         = 27,  // 飞行计划27
    V_FLY_PLAN_PLAN_28         = 28,  // 飞行计划28
    V_FLY_PLAN_PLAN_29         = 29,  // 飞行计划29
    V_FLY_PLAN_PLAN_30         = 30,  // 飞行计划30
    V_FLY_PLAN_PLAN_31         = 31,  // 飞行计划31
    V_FLY_PLAN_PLAN_32         = 32,  // 飞行计划32
    V_FLY_PLAN_PLAN_33         = 33,  // 飞行计划33
    V_FLY_PLAN_PLAN_34         = 34,  // 飞行计划34
    V_FLY_PLAN_PLAN_35         = 35,  // 飞行计划35
    V_FLY_PLAN_PLAN_36         = 36,  // 飞行计划36
    V_FLY_PLAN_PLAN_37         = 37,  // 飞行计划37
    V_FLY_PLAN_PLAN_38         = 38,  // 飞行计划38
    V_FLY_PLAN_PLAN_39         = 39,  // 飞行计划39
    V_FLY_PLAN_PLAN_40         = 40,  // 飞行计划40
    V_FLY_PLAN_PLAN_41         = 41,  // 飞行计划41
    V_FLY_PLAN_PLAN_42         = 42,  // 飞行计划42
    V_FLY_PLAN_PLAN_43         = 43,  // 飞行计划43
    V_FLY_PLAN_PLAN_44         = 44,  // 飞行计划44
    V_FLY_PLAN_PLAN_45         = 45,  // 飞行计划45
    V_FLY_PLAN_PLAN_46         = 46,  // 飞行计划46
    V_FLY_PLAN_PLAN_47         = 47,  // 飞行计划47
    V_FLY_PLAN_PLAN_48         = 48,  // 飞行计划48
    V_FLY_PLAN_PLAN_49         = 49,  // 飞行计划49
    V_FLY_PLAN_PLAN_50         = 50,  // 飞行计划50
    V_FLY_PLAN_PLAN_51         = 51,  // 飞行计划51
    V_FLY_PLAN_PLAN_52         = 52,  // 飞行计划52
    V_FLY_PLAN_PLAN_53         = 53,  // 飞行计划53
    V_FLY_PLAN_PLAN_54         = 54,  // 飞行计划54
    V_FLY_PLAN_PLAN_55         = 55,  // 飞行计划55
    V_FLY_PLAN_PLAN_56         = 56,  // 飞行计划56
    V_FLY_PLAN_PLAN_57         = 57,  // 飞行计划57
    V_FLY_PLAN_PLAN_58         = 58,  // 飞行计划58
    V_FLY_PLAN_PLAN_59         = 59,  // 飞行计划59
    V_FLY_PLAN_PLAN_60         = 60,  // 飞行计划60
    V_FLY_PLAN_PLAN_61         = 61,  // 飞行计划61
    V_FLY_PLAN_PLAN_62         = 62,  // 飞行计划62
    V_FLY_PLAN_PLAN_63         = 63,  // 飞行计划63
    V_FLY_PLAN_PLAN_64         = 64,  // 飞行计划64
    V_FLY_PLAN_MARK            = 100, // 标记点
    V_FLY_PLAN_BULLSEYE        = 101, // 波塞点
    V_FLY_PLAN_DESIGNATED      = 102, // 标定点
    V_FLY_PLAN_INITIALIZATION  = 103, // 初始位置
    V_FLY_PLAN_NEAR_AIRPORT    = 104, // 最近机场
    V_FLY_PLAN_AIRPORT         = 105, // 机场
    V_FLY_PLAN_IFRP_EXTRA_PLAN = 110, // 重规划临时生成计划
} FLY_PLAN;

// 标识符: focus_CHG
// 名  称: 调焦修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_FOCUS_CHG_NO  = 0, // 不修改
    V_FOCUS_CHG_YES = 1, // 修改
} FOCUS_CHG;

// 标识符: Force_BD_J_cmd_
// 名  称: 强制BD军指令_
// 字  数: 8
// 说  明:
typedef enum {
    V_FORCE_BD_J_CMD__INVALID = 0, // 强制BD军码
    V_FORCE_BD_J_CMD__VALID   = 1, // 取消强制BD军码
} FORCE_BD_J_CMD_;

// 标识符: fused_layer_show_lable
// 名  称: 融合图层显示标识
// 字  数: 32
// 说  明: 枚举值未全部列出，按bit定义某传感器的贡献与否，若为传感器贡献组合，则其值填为各单传感器的枚举值之和。如雷达+电子战，则值为1+2=3。
typedef enum {
    V_FUSED_LAYER_SHOW_LABLE_NA       = 0,      // 无意义
    V_FUSED_LAYER_SHOW_LABLE_RDR      = 1,      // 雷达
    V_FUSED_LAYER_SHOW_LABLE_EWS      = 2,      // 电子战
    V_FUSED_LAYER_SHOW_LABLE_IRST     = 4,      // 光雷
    V_FUSED_LAYER_SHOW_LABLE_ADS_B_IN = 8,      // ADS_B_IN
    V_FUSED_LAYER_SHOW_LABLE_SAT_LINK = 16,     // 卫通链
    V_FUSED_LAYER_SHOW_LABLE_VU       = 32,     // VU链
    V_FUSED_LAYER_SHOW_LABLE_JIDS     = 64,     // JIDS
    V_FUSED_LAYER_SHOW_LABLE_IFDL     = 128,    // IFDL
    V_FUSED_LAYER_SHOW_LABLE_IBS      = 256,    // 侦察卫星接入
    V_FUSED_LAYER_SHOW_LABLE_ADI_IN   = 512,    // ADI_IN
    V_FUSED_LAYER_SHOW_LABLE_L_CSM    = 1024,   // L通侦
    V_FUSED_LAYER_SHOW_LABLE_DAS      = 2048,   // DAS
    V_FUSED_LAYER_SHOW_LABLE_EWS2     = 4096,   // 选装电子战
    V_FUSED_LAYER_SHOW_LABLE_EO_IR    = 8192,   // 综合光电红外图像
    V_FUSED_LAYER_SHOW_LABLE_EO_LIGHT = 16384,  // 综合光电可见光图像
    V_FUSED_LAYER_SHOW_LABLE_RDR_PIC  = 32768,  // 雷达图像
    V_FUSED_LAYER_SHOW_LABLE_AIS      = 65536,  // AIS目标
    V_FUSED_LAYER_SHOW_LABLE_LOADING  = 131072, // 加载目标
} FUSED_LAYER_SHOW_LABLE;

// 标识符: general_act_req
// 名  称: 通用活动请求
// 字  数: 32
// 说  明:
typedef enum {
    V_GENERAL_ACT_REQ_NA               = 0,    //
    V_GENERAL_ACT_REQ_MODE_SWITCH      = 1,    // 工作模式请求
    V_GENERAL_ACT_REQ_BIT_OPERATION    = 2,    // 执行BIT请求
    V_GENERAL_ACT_REQ_MFL_OPERATION    = 3,    // MFL操作请求——清除mfc
    V_GENERAL_ACT_REQ_DATA_REQ         = 4,    // 子域数据请求
    V_GENERAL_ACT_REQ_ICP1_MODE_SWITCH = 11,   // ICP1工作模式请求
    V_GENERAL_ACT_REQ_ICP2_MODE_SWITCH = 22,   // ICP2工作模式请求
    V_GENERAL_ACT_REQ_UNIQUE_ACT       = 9999, // 特殊活动请求
} GENERAL_ACT_REQ;

// 标识符: GNSS_inertial_ADS_alt_state
// 名  称: 惯性卫星大气高度通道组合状态
// 字  数: 8
// 说  明:
typedef enum {
    V_GNSS_INERTIAL_ADS_ALT_STATE_NA             = 0, //
    V_GNSS_INERTIAL_ADS_ALT_STATE_GNSS_INERTIAL  = 1, // 惯性卫星组合
    V_GNSS_INERTIAL_ADS_ALT_STATE_ADS_INERTIAL   = 2, // 惯性大气组合
    V_GNSS_INERTIAL_ADS_ALT_STATE_NON_HYBRID     = 3, // 非组合
    V_GNSS_INERTIAL_ADS_ALT_STATE_ADS_AU_INERIAL = 4, // AU修正大气
} GNSS_INERTIAL_ADS_ALT_STATE;

// 标识符: GNSS_Reset_CMD
// 名  称: 接收机重启指令
// 字  数: 8
// 说  明:
typedef enum {
    V_GNSS_RESET_CMD_INVALID = 0,   // 无效
    V_GNSS_RESET_CMD_VALID   = 170, // 重启
} GNSS_RESET_CMD;

// 标识符: GS_state
// 名  称: 地速状态
// 字  数: 8
// 说  明:
typedef enum {
    V_GS_STATE_NA  = 0, //
    V_GS_STATE_GS1 = 1, // GS<5km/h
    V_GS_STATE_GS2 = 2, // 5km/h<=GS<50km/h
    V_GS_STATE_GS3 = 3, // GS>=50km/h
} GS_STATE;

// 标识符: guidance_onoff_state
// 名  称: 制导开关状态
// 字  数: 8
// 说  明:
typedef enum {
    V_GUIDANCE_ONOFF_STATE_NA           = 0, // 无意义
    V_GUIDANCE_ONOFF_STATE_GUIDANCE_ON  = 1, // 制导开
    V_GUIDANCE_ONOFF_STATE_GUIDANCE_OFF = 2, // 制导关
} GUIDANCE_ONOFF_STATE;

// 标识符: guidance_tgt_flag
// 名  称: 制导目标标志
// 字  数: 8
// 说  明:
typedef enum {
    V_GUIDANCE_TGT_FLAG_NONE                 = 0, // 非制导目标
    V_GUIDANCE_TGT_FLAG_GUIDANCE             = 1, // 制导目标
    V_GUIDANCE_TGT_FLAG_GUIDANCE_EXTRAPOLATE = 2, // 制导外推目标
} GUIDANCE_TGT_FLAG;

// 标识符: head_tail
// 名  称: 迎头尾后
// 字  数: 8
// 说  明: 描述风速的迎头尾后方向：
//         =Head，表示迎头风向
//         =Tail，表尾后风向
typedef enum {
    V_HEAD_TAIL_HEAD = 0, //
    V_HEAD_TAIL_TAIL = 1, //
} HEAD_TAIL;

// 标识符: HEIGHT_CHG
// 名  称: 高度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_HEIGHT_CHG_NO  = 0, // 不修改
    V_HEIGHT_CHG_YES = 1, // 修改
} HEIGHT_CHG;

// 标识符: IC_invalid_state
// 名  称: IC失效状态
// 字  数: 8
// 说  明: 用于表征卫星军码IC的失效状态。其中：
//         “正常有效”指IC失效的日期与当前的日期差大于8周；
//         “邻近失效”指IC失效的日期与当前的日期差在8周内；
//         “失效”指IC失效的日期超过了当前的日期。
typedef enum {
    V_IC_INVALID_STATE_NA           = 0, // 未知
    V_IC_INVALID_STATE_VALID        = 1, // 正常有效
    V_IC_INVALID_STATE_NEAR_INVALID = 2, // 邻近失效
    V_IC_INVALID_STATE_INVALID      = 3, // 失效
} IC_INVALID_STATE;

// 标识符: ID_data_trans_flag
// 名  称: 情报数据传输标识
// 字  数: 8
// 说  明: 按照顺序，第一维代表通道1，第二维代表通道2，以此类推。如果只存在一个通道，则填第一维即可。
typedef enum {
    V_ID_DATA_TRANS_FLAG_NO  = 0, // 否
    V_ID_DATA_TRANS_FLAG_YES = 1, // 是
} ID_DATA_TRANS_FLAG;

// 标识符: IMG_MODE_CHG
// 名  称: 成像方式修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_IMG_MODE_CHG_NO  = 0, // 不修改
    V_IMG_MODE_CHG_YES = 1, // 修改
} IMG_MODE_CHG;

// 标识符: infrared_correct_state
// 名  称: 红外校正状态
// 字  数: 8
// 说  明:
typedef enum {
    V_INFRARED_CORRECT_STATE_NA        = 0, //
    V_INFRARED_CORRECT_STATE_ING       = 1, // 校正中
    V_INFRARED_CORRECT_STATE_COMPLETED = 2, // 校正成功
    V_INFRARED_CORRECT_STATE_FAIL      = 3, // 校正失败
} INFRARED_CORRECT_STATE;

// 标识符: infrared_dim_mode
// 名  称: 红外调光模式
// 字  数: 8
// 说  明:
typedef enum {
    V_INFRARED_DIM_MODE_NA     = 0, //
    V_INFRARED_DIM_MODE_AUTO   = 1, // 自动
    V_INFRARED_DIM_MODE_MANUAL = 2, // 手动
} INFRARED_DIM_MODE;

// 标识符: infrared_enhance_mode
// 名  称: 红外增强状态
// 字  数: 8
// 说  明:
typedef enum {
    V_INFRARED_ENHANCE_MODE_NA  = 0, //
    V_INFRARED_ENHANCE_MODE_ON  = 1, // 开
    V_INFRARED_ENHANCE_MODE_OFF = 2, // 关
} INFRARED_ENHANCE_MODE;

// 标识符: infrared_focus_mode
// 名  称: 红外调焦模式
// 字  数: 8
// 说  明:
typedef enum {
    V_INFRARED_FOCUS_MODE_NA     = 0, //
    V_INFRARED_FOCUS_MODE_AUTO   = 1, // 自动
    V_INFRARED_FOCUS_MODE_MANUAL = 2, // 手动
} INFRARED_FOCUS_MODE;

// 标识符: init_location_ctrl_type
// 名  称: 初始位置控制方式
// 字  数: 8
// 说  明:
typedef enum {
    V_INIT_LOCATION_CTRL_TYPE_NA            = 0, //
    V_INIT_LOCATION_CTRL_TYPE_SATELLITE_IN  = 1, // 内置卫星
    V_INIT_LOCATION_CTRL_TYPE_VMC_SATELLITE = 2, // VMC转发卫星
    V_INIT_LOCATION_CTRL_TYPE_VMC_INPUT     = 3, // VMC人工装订
} INIT_LOCATION_CTRL_TYPE;

// 标识符: INS_ALIGNMENT_WAY_
// 名  称: 惯导对准方式
// 字  数: 8
// 说  明:
typedef enum {
    V_INS_ALIGNMENT_WAY__A = 0, // 无效（默认）
    V_INS_ALIGNMENT_WAY__B = 1, // 正常罗经对准
    V_INS_ALIGNMENT_WAY__C = 2, // 快速对准
    V_INS_ALIGNMENT_WAY__D = 3, // 空中对准
    V_INS_ALIGNMENT_WAY__E = 4, // 降级对准
} INS_ALIGNMENT_WAY_;

// 标识符: INS_cmd_Aim_cmd
// 名  称: VMC惯导对准指令
// 字  数: 8
// 说  明:
typedef enum {
    V_INS_CMD_AIM_CMD_NA    = 0, // 无效
    V_INS_CMD_AIM_CMD_GC    = 1, // 正常罗经对准
    V_INS_CMD_AIM_CMD_FAST  = 2, // 快速对准
    V_INS_CMD_AIM_CMD_AGAIN = 3, // 地面重新正常罗经对准
} INS_CMD_AIM_CMD;

// 标识符: INS_operation_mode_req
// 名  称: 惯导工作方式请求
// 字  数: 8
// 说  明:
typedef enum {
    V_INS_OPERATION_MODE_REQ_NA            = 0, //
    V_INS_OPERATION_MODE_REQ_HYBRID_NAV    = 1, // 组合导航
    V_INS_OPERATION_MODE_REQ_PURE_INS      = 2, // 纯惯
    V_INS_OPERATION_MODE_REQ_SATELLITE_NAV = 3, // 卫星导航
} INS_OPERATION_MODE_REQ;

// 标识符: INS_operation_mode_state
// 名  称: 惯导当前工作方式
// 字  数: 8
// 说  明:
typedef enum {
    V_INS_OPERATION_MODE_STATE_NA            = 0, //
    V_INS_OPERATION_MODE_STATE_HYBRID_NAV    = 1, // 组合导航
    V_INS_OPERATION_MODE_STATE_PURE_INS      = 2, // 纯惯
    V_INS_OPERATION_MODE_STATE_SATELLITE_NAV = 3, // 卫星导航
} INS_OPERATION_MODE_STATE;

// 标识符: INS_SAT_type_req
// 名  称: 惯导卫星选择请求
// 字  数: 8
// 说  明: 自动（优先级：BD军、BD民、GPS、内置、转发）
//         此条请求本来为任务系统向惯导发活动请求后，惯导回报相关请求，现阶段，惯导不响应任务系统的命令（以1394为主），目前按惯导当前工作状态填值；
//         报送状态时：
//         如果VMC的1394命令中，"惯导航强选指令"为自主，则上报1-AUTO 自动；
typedef enum {
    V_INS_SAT_TYPE_REQ_NA     = 0, //
    V_INS_SAT_TYPE_REQ_AUTO   = 1, // 自动
    V_INS_SAT_TYPE_REQ_BD_JUN = 2, // 北斗军码
    V_INS_SAT_TYPE_REQ_BD_MIN = 3, // 北斗民码
    V_INS_SAT_TYPE_REQ_GPS    = 4, // GPS
    V_INS_SAT_TYPE_REQ_VMC    = 5, // VMC转发
} INS_SAT_TYPE_REQ;

// 标识符: INS_sub_mode_req
// 名  称: 惯导子模式请求
// 字  数: 8
// 说  明:
typedef enum {
    V_INS_SUB_MODE_REQ_NA       = 0, //
    V_INS_SUB_MODE_REQ_STBY     = 1, // 准备
    V_INS_SUB_MODE_REQ_FAST     = 2, // 快对
    V_INS_SUB_MODE_REQ_GC       = 3, // 罗经
    V_INS_SUB_MODE_REQ_NAV      = 4, // 导航
    V_INS_SUB_MODE_REQ_FLIT     = 5, // 空中对准
    V_INS_SUB_MODE_REQ_TRANSFER = 6, // 传递对准
} INS_SUB_MODE_REQ;

// 标识符: INS_sub_mode_state
// 名  称: 惯导当前子模式
// 字  数: 8
// 说  明: 惯导向任务系统上报当前工作模式；
//         目前无6-传递对准模式；
//         增加7-对准失败模式；
//         初始化上报0；
//         其余按当前工作模式上报；
typedef enum {
    V_INS_SUB_MODE_STATE_NA       = 0, //
    V_INS_SUB_MODE_STATE_STBY     = 1, // 准备
    V_INS_SUB_MODE_STATE_FAST     = 2, // 快对
    V_INS_SUB_MODE_STATE_GC       = 3, // 罗经
    V_INS_SUB_MODE_STATE_NAV      = 4, // 导航
    V_INS_SUB_MODE_STATE_FLIT     = 5, // 空中对准
    V_INS_SUB_MODE_STATE_TRANSFER = 6, // 传递对准
    V_INS_SUB_MODE_STATE_FAIL     = 7, // 对准失败
} INS_SUB_MODE_STATE;

// 标识符: Integ_NAV_Forced_Selec_Mode
// 名  称: 惯导组合导航强选指令
// 字  数: 8
// 说  明:
typedef enum {
    V_INTEG_NAV_FORCED_SELEC_MODE_AUTO            = 0, // 自主（默认）
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_GNSSINERTAL = 1, // 惯性/卫导（内嵌）
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_VMC         = 2, // 惯性/VMC综合卫星组合
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_HAOMIBO     = 3, // 惯性/毫米波修正
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_VIEW        = 5, // 惯性/视觉组合
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_CNE         = 6, // 惯性/天文组合
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_DIJING      = 7, // 惯性/地景组合
    V_INTEG_NAV_FORCED_SELEC_MODE_INS_ADS         = 8, // 惯性/大气组合
} INTEG_NAV_FORCED_SELEC_MODE;

// 标识符: Integrated_NAV_Work_State_
// 名  称: 组合通道工作状态字
// 字  数: 8
// 说  明:
typedef enum {
    V_INTEGRATED_NAV_WORK_STATE__A = 0,  // 无效（默认）
    V_INTEGRATED_NAV_WORK_STATE__B = 1,  // 惯性/RTK BDS组合
    V_INTEGRATED_NAV_WORK_STATE__C = 2,  // 惯性/RTD BDS组合
    V_INTEGRATED_NAV_WORK_STATE__D = 3,  // 惯性/单点BDS组合
    V_INTEGRATED_NAV_WORK_STATE__E = 4,  // 惯性/RTD GPS组合
    V_INTEGRATED_NAV_WORK_STATE__F = 5,  // 惯性/单点 GPS组合
    V_INTEGRATED_NAV_WORK_STATE__G = 6,  // 惯性/ VMC综合卫星组合
    V_INTEGRATED_NAV_WORK_STATE__H = 7,  // 惯性/毫米波组合
    V_INTEGRATED_NAV_WORK_STATE__I = 8,  // 惯性/飞行辅助引导设备组合
    V_INTEGRATED_NAV_WORK_STATE__J = 9,  // 惯性/SBAS BDS组合
    V_INTEGRATED_NAV_WORK_STATE__K = 10, // 惯性/天文组合
    V_INTEGRATED_NAV_WORK_STATE__L = 11, // 惯性/地景组合
    V_INTEGRATED_NAV_WORK_STATE__M = 12, // 惯性/精定修正
    V_INTEGRATED_NAV_WORK_STATE__N = 13, // 惯性/大气组合
    V_INTEGRATED_NAV_WORK_STATE__O = 14, // 纯惯性（断开修正）
} INTEGRATED_NAV_WORK_STATE_;

// 标识符: IR_IMG_FLAG
// 名  称: 光电成像状态
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_IMG_FLAG_NA         = 0, // 无意义
    V_IR_IMG_FLAG_OVER_BONDS = 1, // 超界
    V_IR_IMG_FLAG_NORMAL     = 2, // 正常
} IR_IMG_FLAG;

// 标识符: IR_IMG_MODE
// 名  称: 光电成像方式
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_IMG_MODE_NA        = 0, // 无意义
    V_IR_IMG_MODE_ONCE      = 1, // 单次
    V_IR_IMG_MODE_CONTINUES = 2, // 连续
} IR_IMG_MODE;

// 标识符: IR_INS_ALIGN_STATE
// 名  称: 光电惯导对准状态
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_INS_ALIGN_STATE_NA        = 0, //
    V_IR_INS_ALIGN_STATE_MISALIGN  = 1, // 未对准
    V_IR_INS_ALIGN_STATE_ALIGN_ING = 2, // 对准中
    V_IR_INS_ALIGN_STATE_SUCCESS   = 3, // 对准成功
    V_IR_INS_ALIGN_STATE_OVERTIME  = 4, // 对准超时
} IR_INS_ALIGN_STATE;

// 标识符: IR_LOCATION_MARK
// 名  称: 光电地理定位标志
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_LOCATION_MARK_NA         = 0, //
    V_IR_LOCATION_MARK_FLIGHT_INS = 1, // 机载惯导
    V_IR_LOCATION_MARK_IR_INS     = 2, // 光电惯导
} IR_LOCATION_MARK;

// 标识符: IR_pole_type
// 名  称: 极化类型
// 字  数: 1
// 说  明:
typedef enum {
    V_IR_POLE_TYPE_WHITE = 0, // 白热
    V_IR_POLE_TYPE_BLACK = 1, // 黑热
} IR_POLE_TYPE;

// 标识符: IR_scan_work_state
// 名  称: IRST扫描工作状态
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_SCAN_WORK_STATE_NA             = 0, // 未知
    V_IR_SCAN_WORK_STATE_NORMAL         = 1, // 正常
    V_IR_SCAN_WORK_STATE_DEGRADE        = 2, // 降级
    V_IR_SCAN_WORK_STATE_SEVERE_DEGRADE = 3, // 严重降级
} IR_SCAN_WORK_STATE;

// 标识符: IR_SENSOR
// 名  称: 光电传感器状态
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_SENSOR_NA       = 0, //
    V_IR_SENSOR_LIGHT    = 1, // 可见光
    V_IR_SENSOR_INFRARED = 2, // 红外
    V_IR_SENSOR_LANDI    = 3, // 可见+红外
    V_IR_SENSOR_IANDL    = 4, // 红外+可见
} IR_SENSOR;

// 标识符: ir_tgt_track_flag
// 名  称: IR目标航迹标识
// 字  数: 8
// 说  明:
typedef enum {
    V_IR_TGT_TRACK_FLAG_NA    = 0, //
    V_IR_TGT_TRACK_FLAG_DOT   = 1, // 点迹
    V_IR_TGT_TRACK_FLAG_TRACK = 2, // 航迹
} IR_TGT_TRACK_FLAG;

// 标识符: IR_WIDE_IMAGE_DIRECTION
// 名  称: 光电广域成像扫描方向
// 字  数: 3
// 说  明:
typedef enum {
    V_IR_WIDE_IMAGE_DIRECTION_NA    = 0, // 无意义
    V_IR_WIDE_IMAGE_DIRECTION_LEFT  = 1, // 左侧
    V_IR_WIDE_IMAGE_DIRECTION_RIGHT = 2, // 右侧
} IR_WIDE_IMAGE_DIRECTION;

// 标识符: IR_WIDE_IMAGE_MODE
// 名  称: 光电广域成像子模式
// 字  数: 3
// 说  明:
typedef enum {
    V_IR_WIDE_IMAGE_MODE_NA       = 0, // 无意义
    V_IR_WIDE_IMAGE_MODE_AZ_PRIO  = 1, // 方位优先
    V_IR_WIDE_IMAGE_MODE_DIS_PRIO = 2, // 距离优先
} IR_WIDE_IMAGE_MODE;

// 标识符: irst_form_mode
// 名  称: IRST成像模式
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_FORM_MODE_NA        = 0, //
    V_IRST_FORM_MODE_WIDE_IMAG = 1, // 广域成像
    V_IRST_FORM_MODE_AREA_IMAG = 2, // 区域成像
    V_IRST_FORM_MODE_AREA_MONI = 3, // 区域监视
    V_IRST_FORM_MODE_CUE       = 4, // 提示搜索
} IRST_FORM_MODE;

// 标识符: irst_INS_valid
// 名  称: IRST载机姿态有效标志
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_INS_VALID_INVALID = 0, // 无效
    V_IRST_INS_VALID_VALID   = 1, // 有效
} IRST_INS_VALID;

// 标识符: irst_tgt_acq_mode
// 名  称: IRST目标获取方式
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_TGT_ACQ_MODE_NA   = 0, //
    V_IRST_TGT_ACQ_MODE_GAZE = 1, // 凝视
    V_IRST_TGT_ACQ_MODE_SCAN = 2, // 扫描
} IRST_TGT_ACQ_MODE;

// 标识符: IRST_Video_BAND
// 名  称: IRST_区域监视视频带宽
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_VIDEO_BAND_NA         = 0, //
    V_IRST_VIDEO_BAND__BAND_LOW  = 1, // 暂定1.6M（精确大小待定）
    V_IRST_VIDEO_BAND__BAND_MID  = 2, // 暂定3.2M（精确大小待定）
    V_IRST_VIDEO_BAND__BAND_HIGH = 3, // 暂定4.8M（精确大小待定）
} IRST_VIDEO_BAND;

// 标识符: irst_work_mode
// 名  称: IRST工作模式_不管
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_WORK_MODE_NA   = 0, //
    V_IRST_WORK_MODE_AA   = 1, //
    V_IRST_WORK_MODE_AS   = 2, //
    V_IRST_WORK_MODE_DGFT = 3, //
    V_IRST_WORK_MODE_STBY = 4, //
} IRST_WORK_MODE;

// 标识符: irst_work_state
// 名  称: IRST工作状态
// 字  数: 8
// 说  明:
typedef enum {
    V_IRST_WORK_STATE_NA       = 0, //
    V_IRST_WORK_STATE_INIT     = 1, // 初始化
    V_IRST_WORK_STATE_COLLECT  = 2, // 收藏
    V_IRST_WORK_STATE_PREPARE  = 3, // 准备中
    V_IRST_WORK_STATE_STBY     = 4, // 待机
    V_IRST_WORK_STATE_TAKE_PIC = 5, // 拍照
    V_IRST_WORK_STATE_BIT      = 6, // 自检测

    V_IRST_WORK_STATE_NB_JT = 0xAA, // 静态拍照-内部使用

} IRST_WORK_STATE;

// 标识符: jam_tgt_memory_flag
// 名  称: 干扰源目标外推标志
// 字  数: 8
// 说  明:
typedef enum {
    V_JAM_TGT_MEMORY_FLAG_NONE            = 0, // 非干扰源目标
    V_JAM_TGT_MEMORY_FLAG_JAM             = 1, // 干扰源目标
    V_JAM_TGT_MEMORY_FLAG_JAM_EXTRAPOLATE = 2, // 干扰源外推目标
} JAM_TGT_MEMORY_FLAG;

// 标识符: jamed_distance_enable_tgt_flag
// 名  称: 使用雷达受干扰距离目标标志
// 字  数: 8
// 说  明:
typedef enum {
    V_JAMED_DISTANCE_ENABLE_TGT_FLAG_NONE   = 0, // 未使用雷达受干扰距离
    V_JAMED_DISTANCE_ENABLE_TGT_FLAG_ENABLE = 1, // 使用雷达受干扰距离
} JAMED_DISTANCE_ENABLE_TGT_FLAG;

// 标识符: LAND_STATE
// 名  称: 地形标识
// 字  数: 8
// 说  明:
typedef enum {
    V_LAND_STATE_LAND  = 0, // 陆地
    V_LAND_STATE_WATER = 1, // 水面
} LAND_STATE;

// 标识符: laser_range_memory_flag
// 名  称: 激光测距外推标识
// 字  数: 8
// 说  明:
typedef enum {
    V_LASER_RANGE_MEMORY_FLAG_NA     = 0, //
    V_LASER_RANGE_MEMORY_FLAG_NORMAL = 1, // 正常测距
    V_LASER_RANGE_MEMORY_FLAG_MEMORY = 2, // 测距外推
} LASER_RANGE_MEMORY_FLAG;

// 标识符: LATI_CHG
// 名  称: 纬度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_LATI_CHG_NO  = 0, // 不修改
    V_LATI_CHG_YES = 1, // 修改
} LATI_CHG;

// 标识符: left_right
// 名  称: 左侧右侧
// 字  数: 8
// 说  明: 描述风速的相对机身左右方向：
//         =LEFT，表示左侧风向
//         =RIGHT，表右侧风向
typedef enum {
    V_LEFT_RIGHT_LEFT  = 0, //
    V_LEFT_RIGHT_RIGHT = 1, //
} LEFT_RIGHT;

// 标识符: LENGTH_CHG
// 名  称: 区域边长修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_LENGTH_CHG_NO  = 0, // 不修改
    V_LENGTH_CHG_YES = 1, // 修改
} LENGTH_CHG;

// 标识符: light_dim_mode
// 名  称: 可见光调光模式
// 字  数: 8
// 说  明:
typedef enum {
    V_LIGHT_DIM_MODE_NA     = 0, //
    V_LIGHT_DIM_MODE_AUTO   = 1, // 自动
    V_LIGHT_DIM_MODE_MANUAL = 2, // 手动
} LIGHT_DIM_MODE;

// 标识符: light_enhance_mode
// 名  称: 可见光增强状态
// 字  数: 8
// 说  明:
typedef enum {
    V_LIGHT_ENHANCE_MODE_NA  = 0, //
    V_LIGHT_ENHANCE_MODE_ON  = 1, // 开
    V_LIGHT_ENHANCE_MODE_OFF = 2, // 关
} LIGHT_ENHANCE_MODE;

// 标识符: light_focus_mode
// 名  称: 可见光调焦模式
// 字  数: 8
// 说  明:
typedef enum {
    V_LIGHT_FOCUS_MODE_NA     = 0, //
    V_LIGHT_FOCUS_MODE_AUTO   = 1, // 自动
    V_LIGHT_FOCUS_MODE_MANUAL = 2, // 手动
} LIGHT_FOCUS_MODE;

// 标识符: light_mist_eliminate_state
// 名  称: 可见光去雾状态
// 字  数: 8
// 说  明:
typedef enum {
    V_LIGHT_MIST_ELIMINATE_STATE_NA  = 0, //
    V_LIGHT_MIST_ELIMINATE_STATE_ON  = 1, // 开
    V_LIGHT_MIST_ELIMINATE_STATE_OFF = 2, // 关
} LIGHT_MIST_ELIMINATE_STATE;

// 标识符: link_message_tr_flag
// 名  称: 消息收发标识
// 字  数: 8
// 说  明:
typedef enum {
    V_LINK_MESSAGE_TR_FLAG_NA       = 0, //
    V_LINK_MESSAGE_TR_FLAG_TRANSMIT = 1, // 发送
    V_LINK_MESSAGE_TR_FLAG_RECEIVE  = 2, // 接收
} LINK_MESSAGE_TR_FLAG;

// 标识符: link_message_tr_route
// 名  称: 消息收发链路
// 字  数: 8
// 说  明:
typedef enum {
    V_LINK_MESSAGE_TR_ROUTE_NA       = 0, //
    V_LINK_MESSAGE_TR_ROUTE_VU_LINK  = 1, // VU链
    V_LINK_MESSAGE_TR_ROUTE_JIDS     = 2, // JIDS链
    V_LINK_MESSAGE_TR_ROUTE_IFDL     = 3, // IFDL链
    V_LINK_MESSAGE_TR_ROUTE_ET       = 4, // 训练链
    V_LINK_MESSAGE_TR_ROUTE_SAT_LINK = 5, // 卫通链
    V_LINK_MESSAGE_TR_ROUTE_WCDL     = 6, // 全向链
} LINK_MESSAGE_TR_ROUTE;

// 标识符: load_fail_reason
// 名  称: 加载失败原因
// 字  数: 8
// 说  明:
typedef enum {
    V_LOAD_FAIL_REASON_NA                = 0,  //
    V_LOAD_FAIL_REASON_CRC_ERROR         = 1,  // CRC校验错误
    V_LOAD_FAIL_REASON_FILE_VOLUME_ERROR = 2,  // 文件长度不一致
    V_LOAD_FAIL_REASON_PARAS_ERROR       = 3,  // 参数非法
    V_LOAD_FAIL_REASON_DESTINATION_FAIL  = 4,  // 部分节点加载失败
    V_LOAD_FAIL_REASON_TERMINAL_OFF      = 5,  // 加载终端离线
    V_LOAD_FAIL_REASON_OVER_TIME_LIMIT   = 6,  // 超时未反馈
    V_LOAD_FAIL_REASON_NFS_READ_FAIL     = 7,  // 网络文件系统读取失败
    V_LOAD_FAIL_REASON_LOAD_NACK         = 8,  // 拒绝加载
    V_LOAD_FAIL_REASON_OTHER             = 99, // 其他
} LOAD_FAIL_REASON;

// 标识符: load_state
// 名  称: 加载状态
// 字  数: 8
// 说  明:
typedef enum {
    V_LOAD_STATE_NA              = 0,  // 无意义
    V_LOAD_STATE_TRANSFERABLE    = 1,  // 等待加载
    V_LOAD_STATE_TRANSFERRING    = 2,  // 正在加载
    V_LOAD_STATE_TRANSFERRED     = 3,  // 加载成功
    V_LOAD_STATE_FAILTRANSFERRED = 4,  // 加载失败
    V_LOAD_STATE_NONTRANSFERABLE = 5,  // 限制加载
    V_LOAD_STATE_MD5CHECKERROR   = 6,  // MD5校验失败
    V_LOAD_STATE_FILEBURNING     = 7,  // 文件固化中
    V_LOAD_STATE_NOTTRANSFERRED  = 10, // 未加载
} LOAD_STATE;

// 标识符: loading_type
// 名  称: 加载类型
// 字  数: 8
// 说  明: 描述文件/数据在的场景类型：
//         1=在任务系统正常模式下进行的战术任务数据加载；
//         2=在任务系统维护模式下进行的维护配置数据加载；
typedef enum {
    V_LOADING_TYPE_NA             = 0, // 无意义
    V_LOADING_TYPE_TAC_DATA_LOAD  = 1, // 战术任务数据加载
    V_LOADING_TYPE_MAINT_CFG_LOAD = 2, // 维护配置数据加载
    V_LOADING_TYPE_SOFTWARE_LOAD  = 4, // 软件加载
} LOADING_TYPE;

// 标识符: location_presise
// 名  称: 定位精度
// 字  数: 3
// 说  明:
typedef enum {
    V_LOCATION_PRESISE_NA     = 0, //
    V_LOCATION_PRESISE_LOW    = 1, // 精度低
    V_LOCATION_PRESISE_CONMON = 2, // 精度中
    V_LOCATION_PRESISE_HIGH   = 3, // 精度高
} LOCATION_PRESISE;

// 标识符: location_source
// 名  称: 位置来源
// 字  数: 8
// 说  明:
typedef enum {
    V_LOCATION_SOURCE_NA           = 0, //
    V_LOCATION_SOURCE_GPS          = 1, //
    V_LOCATION_SOURCE_GLONASS      = 2, //
    V_LOCATION_SOURCE_INS          = 3, //
    V_LOCATION_SOURCE_HYBRID       = 4, // 组合定位
    V_LOCATION_SOURCE_TACAN        = 5, //
    V_LOCATION_SOURCE_BD           = 6, // 北斗
    V_LOCATION_SOURCE_RELATIVE_NAV = 7, // 相对导航
} LOCATION_SOURCE;

// 标识符: LONG_CHG
// 名  称: 经度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_LONG_CHG_NO  = 0, // 不修改
    V_LONG_CHG_YES = 1, // 修改
} LONG_CHG;

// 标识符: LSR_test_state
// 名  称: 激光测试状态
// 字  数: 8
// 说  明:
typedef enum {
    V_LSR_TEST_STATE_OFF = 0, // 激光辐射停止
    V_LSR_TEST_STATE_ON  = 1, // 激光辐射启动
} LSR_TEST_STATE;

// 标识符: main_plan_on_off
// 名  称: 主计划开关
// 字  数: 8
// 说  明:
typedef enum {
    V_MAIN_PLAN_ON_OFF_OFF = 0, // 关
    V_MAIN_PLAN_ON_OFF_ON  = 1, // 开
} MAIN_PLAN_ON_OFF;

// 标识符: member_mission_event
// 名  称: 编队成员任务事件
// 字  数: 8
// 说  明:
typedef enum {
    V_MEMBER_MISSION_EVENT_NA           = 0, //
    V_MEMBER_MISSION_EVENT_MSL_LAUNCH   = 1, // 发射导弹
    V_MEMBER_MISSION_EVENT_GUN_START    = 2, // 航炮射击启动
    V_MEMBER_MISSION_EVENT_GUN_STOP     = 3, // 航炮射击停止
    V_MEMBER_MISSION_EVENT_FLARE_LAUNCH = 4, // 投放红外干扰弹
    V_MEMBER_MISSION_EVENT_FLARE_STOP   = 5, // 停止投放红外干扰弹
    V_MEMBER_MISSION_EVENT_LASER_START  = 6, // 启动激光测距
    V_MEMBER_MISSION_EVENT_LASER_STOP   = 7, // 停止激光测距
} MEMBER_MISSION_EVENT;

// 标识符: MFL_operation
// 名  称: MFL操作类型
// 字  数: 8
// 说  明:
typedef enum {
    V_MFL_OPERATION_NA     = 0, // 无意义
    V_MFL_OPERATION_REQ    = 1, // 请求传输MFL
    V_MFL_OPERATION_DELETE = 2, // 清除MFL
} MFL_OPERATION;

// 标识符: mission_event_type
// 名  称: 任务事件类型
// 字  数: 8
// 说  明:
typedef enum {
    V_MISSION_EVENT_TYPE_NA                  = 0, //
    V_MISSION_EVENT_TYPE_NAV_EVENT           = 1, // 导航事件
    V_MISSION_EVENT_TYPE_SITUATION_EVENT     = 2, // 态势事件
    V_MISSION_EVENT_TYPE_TIME_EVENT          = 3, // 时间事件
    V_MISSION_EVENT_TYPE_STATE_CHANGE_EVENT  = 4, // 状态转换事件
    V_MISSION_EVENT_TYPE_OWN_SHIP_MS_EVENT   = 5, // 本机任务事件
    V_MISSION_EVENT_TYPE_MEMBE_SHIP_MS_EVENT = 6, // 编队成员任务事件
} MISSION_EVENT_TYPE;

// 标识符: mission_main_mode
// 名  称: 任务主模式
// 字  数: 8
// 说  明:
typedef enum {
    V_MISSION_MAIN_MODE_NA   = 0, //
    V_MISSION_MAIN_MODE_NAV  = 1, // 导航
    V_MISSION_MAIN_MODE_AA1  = 2, // 空空1
    V_MISSION_MAIN_MODE_AA2  = 3, // 空空2
    V_MISSION_MAIN_MODE_DGFT = 4, // 格斗
    V_MISSION_MAIN_MODE_AS   = 5, // 空面
} MISSION_MAIN_MODE;

// 标识符: mist_eliminate_CHG
// 名  称: 可见光去雾修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_MIST_ELIMINATE_CHG_NO  = 0, // 不修改
    V_MIST_ELIMINATE_CHG_YES = 1, // 修改
} MIST_ELIMINATE_CHG;

// 标识符: MS_phase
// 名  称: 任务阶段
// 字  数: 8
// 说  明:
typedef enum {
    V_MS_PHASE_NA           = 0, //
    V_MS_PHASE_PREPARE      = 1, // 准备阶段
    V_MS_PHASE_TAXI_TAKEOFF = 2, // 滑行起飞阶段
    V_MS_PHASE_NAVIGATION   = 3, // 导航阶段
    V_MS_PHASE_AA1          = 4, // 空空阶段
    V_MS_PHASE_DGFT         = 5, // 格斗阶段
    V_MS_PHASE_AS           = 6, // 空面阶段
    V_MS_PHASE_APR          = 7, // 进场着陆阶段
    V_MS_PHASE_MAINT        = 8, // 地面维护阶段
    V_MS_PHASE_AIR_FUEL     = 9, // 空中加油阶段
} MS_PHASE;

// 标识符: ms_sw_match_result
// 名  称: 任务系统软件匹配状态
// 字  数: 8
// 说  明:
typedef enum {
    V_MS_SW_MATCH_RESULT_NA       = 0, // 无意义或保持
    V_MS_SW_MATCH_RESULT_MATCH    = 1, // 匹配
    V_MS_SW_MATCH_RESULT_MISMATCH = 2, // 不匹配
} MS_SW_MATCH_RESULT;

// 标识符: ms_sys_main_mode
// 名  称: 任务系统运行模态
// 字  数: 8
// 说  明: 描述任务系统的运行模态，
//         分为正常运行态和维护加载态，正常运行时为NORMAL
//         仅当飞管系统进入OFP加载模式后，任务系统启动进入维护加载态，由该信号触发。
typedef enum {
    V_MS_SYS_MAIN_MODE_NA      = 0,  // 无意义或保持
    V_MS_SYS_MAIN_MODE_NORMAL  = 1,  // 正常运行态
    V_MS_SYS_MAIN_MODE_SW_LOAD = 99, // 维护加载态
} MS_SYS_MAIN_MODE;

// 标识符: nav_event_type
// 名  称: 导航事件类型
// 字  数: 8
// 说  明:
typedef enum {
    V_NAV_EVENT_TYPE_NA                    = 0, //
    V_NAV_EVENT_TYPE_ARRIVAL_POINT         = 1, // 到达某点(一次 )
    V_NAV_EVENT_TYPE_ENTER_AREA            = 2, // 进入某区
    V_NAV_EVENT_TYPE_EXIT_AREA             = 3, // 退出某区
    V_NAV_EVENT_TYPE_DEPARTURE_COURSE_ONCE = 4, // 偏离航线(一次)
    V_NAV_EVENT_TYPE_DEPARTURE_COURSE_MULT = 5, // 偏离航线(多次)
    V_NAV_EVENT_TYPE_ARRIVAL_POINT_MULT    = 6, // 到达某点（多次）
    V_NAV_EVENT_TYPE_DATA_MONITOR          = 7, // 数据监控
} NAV_EVENT_TYPE;

// 标识符: nav_submode
// 名  称: 导航子模式
// 字  数: 8
// 说  明: 导航的子模式
typedef enum {
    V_NAV_SUBMODE_NA      = 0, //
    V_NAV_SUBMODE_TACNAV  = 1, // 战术导航
    V_NAV_SUBMODE_CRUISE  = 2, // 巡航
    V_NAV_SUBMODE_RETURN  = 3, // 返航
    V_NAV_SUBMODE_APR     = 4, // 进场
    V_NAV_SUBMODE_APR_EYE = 5, // 目视航线
} NAV_SUBMODE;

// 标识符: non_uniform_correct_state
// 名  称: 非均匀校正状态
// 字  数: 8
// 说  明:
typedef enum {
    V_NON_UNIFORM_CORRECT_STATE_NA        = 0, //
    V_NON_UNIFORM_CORRECT_STATE_ING       = 1, // 校正中
    V_NON_UNIFORM_CORRECT_STATE_COMPLETED = 2, // 校正成功
    V_NON_UNIFORM_CORRECT_STATE_FAIL      = 3, // 校正失败
} NON_UNIFORM_CORRECT_STATE;

// 标识符: off_state_YES_NO
// 名  称: 关机状态_是_否
// 字  数: 8
// 说  明:
typedef enum {
    V_OFF_STATE_YES_NO_NA       = 0, // 无意义或非关机状态
    V_OFF_STATE_YES_NO_POWEROFF = 1, // 关机
} OFF_STATE_YES_NO;

// 标识符: onboard_mission_event
// 名  称: 本机任务事件
// 字  数: 8
// 说  明:
typedef enum {
    V_ONBOARD_MISSION_EVENT_NA           = 0, //
    V_ONBOARD_MISSION_EVENT_MSL_LAUNCH   = 1, // 发射导弹
    V_ONBOARD_MISSION_EVENT_GUN_START    = 2, // 航炮射击启动
    V_ONBOARD_MISSION_EVENT_GUN_STOP     = 3, // 航炮射击停止
    V_ONBOARD_MISSION_EVENT_FLARE_LAUNCH = 4, // 投放红外干扰弹
    V_ONBOARD_MISSION_EVENT_FLARE_STOP   = 5, // 停止投放红外干扰弹
    V_ONBOARD_MISSION_EVENT_LASER_START  = 6, // 启动激光测距
    V_ONBOARD_MISSION_EVENT_LASER_STOP   = 7, // 停止激光测距
} ONBOARD_MISSION_EVENT;

// 标识符: own_SL_tgt
// 名  称: 本机射击列表目标序号
// 字  数: 8
// 说  明: 射击列表目标的排序：
//         NTS目标排名第一，其它目标顺序排序。
//         若值为0，表示该目标不是射击列表目标。
typedef enum {
    V_OWN_SL_TGT_NA   = 0, // 不在射击列表内
    V_OWN_SL_TGT_SL_1 = 1, // NTS目标
    V_OWN_SL_TGT_SL_2 = 2, // 射击列表2号目标
    V_OWN_SL_TGT_SL_3 = 3, // 射击列表3号目标
    V_OWN_SL_TGT_SL_4 = 4, // 射击列表4号目标
    V_OWN_SL_TGT_SL_5 = 5, // 射击列表5号目标
    V_OWN_SL_TGT_SL_6 = 6, // 射击列表6号目标
    V_OWN_SL_TGT_SL_7 = 7, // 射击列表7号目标
    V_OWN_SL_TGT_SL_8 = 8, // 射击列表8号目标
} OWN_SL_TGT;

// 标识符: Payload_Factory
// 名  称: 载荷厂家
// 字  数: 4
// 说  明:
typedef enum {
    V_PAYLOAD_FACTORY_NA         = 0, //
    V_PAYLOAD_FACTORY_EO_613     = 1, // 613所
    V_PAYLOAD_FACTORY_EO_CGS     = 2, // 长光所
    V_PAYLOAD_FACTORY_EO_CCTS    = 3, // 长春通视
    V_PAYLOAD_FACTORY_RDR_CAS    = 4, // 空天院
    V_PAYLOAD_FACTORY_RDR_CETC14 = 5, // 中电14所
} PAYLOAD_FACTORY;

// 标识符: Payload_type
// 名  称: 载荷类型
// 字  数: 4
// 说  明: 载荷类型（雷达置3，光电按照枚举值定义分类填写）
typedef enum {
    V_PAYLOAD_TYPE_NA               = 0, //
    V_PAYLOAD_TYPE_IRST_IMG_CCD     = 1, // EO_可见光
    V_PAYLOAD_TYPE_IRST_IMG_IR      = 2, // EO_红外
    V_PAYLOAD_TYPE_RDR              = 3, // 侦察雷达
    V_PAYLOAD_TYPE_IR_VIDEO_IMG_IR  = 4, // 区域监视单帧红外
    V_PAYLOAD_TYPE_IR_VIDEO_IMG_CCD = 5, // 区域监视单帧可见光
    V_PAYLOAD_TYPE_IR_VIDEO_FRZ_IR  = 6, // 区域监视冻结帧红外
    V_PAYLOAD_TYPE_IR_VIDEO_RRZ_CCD = 7, // 区域监视冻结帧可见光
    V_PAYLOAD_TYPE_IR_VIDEO         = 8, // 区域监视视频
} PAYLOAD_TYPE;

// 标识符: pixel_data_type
// 名  称: 像素数据类型
// 字  数: 8
// 说  明:
typedef enum {
    V_PIXEL_DATA_TYPE_NA             = 0, //
    V_PIXEL_DATA_TYPE_UNSIGNED_BYTE  = 1, //
    V_PIXEL_DATA_TYPE_BYTE           = 2, //
    V_PIXEL_DATA_TYPE_UNSIGNED_SHORT = 3, //
    V_PIXEL_DATA_TYPE_SHORT          = 4, //
} PIXEL_DATA_TYPE;

// 标识符: pixel_format
// 名  称: 像素格式
// 字  数: 8
// 说  明:
typedef enum {
    V_PIXEL_FORMAT_NA        = 0, //
    V_PIXEL_FORMAT_GRAY      = 1, // 灰度
    V_PIXEL_FORMAT_GREEN     = 2, // 纯绿
    V_PIXEL_FORMAT_BLUE      = 3, // 纯蓝
    V_PIXEL_FORMAT_RED       = 4, // 纯红
    V_PIXEL_FORMAT_RGB       = 5, // 红绿蓝
    V_PIXEL_FORMAT_RGB_ALPHA = 6, // 红绿蓝ALPHA
} PIXEL_FORMAT;

// 标识符: PowOff_CMD_State
// 名  称: 下电指令状态
// 字  数: 8
// 说  明:
typedef enum {
    V_POWOFF_CMD_STATE_NA        = 0, //
    V_POWOFF_CMD_STATE_POWER_OFF = 1, // 下电
    V_POWOFF_CMD_STATE_POWER_ON  = 2, // 上电
} POWOFF_CMD_STATE;

// 标识符: prepare_state
// 名  称: 准备状态
// 字  数: 8
// 说  明:
typedef enum {
    V_PREPARE_STATE_NA       = 0, //
    V_PREPARE_STATE_NORMAL   = 1, // 正常
    V_PREPARE_STATE_TIME_OUT = 2, // 超时
    V_PREPARE_STATE_FAIL     = 3, // 失败
} PREPARE_STATE;

// 标识符: prepare_state_dim
// 名  称: 检调光状态
// 字  数: 8
// 说  明:
typedef enum {
    V_PREPARE_STATE_DIM_NA      = 0, //
    V_PREPARE_STATE_DIM_DIM_ING = 1, // 调光中
    V_PREPARE_STATE_DIM_SUCCESS = 2, // 成功
    V_PREPARE_STATE_DIM_FAIL    = 3, // 失败
} PREPARE_STATE_DIM;

// 标识符: prepare_state_focus
// 名  称: 检调焦状态
// 字  数: 8
// 说  明:
typedef enum {
    V_PREPARE_STATE_FOCUS_NA       = 0, //
    V_PREPARE_STATE_FOCUS_FOCUSING = 1, // 调焦中
    V_PREPARE_STATE_FOCUS_SUCCESS  = 2, // 成功
    V_PREPARE_STATE_FOCUS_FAIL     = 3, // 失败
} PREPARE_STATE_FOCUS;

// 标识符: primary_ins
// 名  称: 主惯导来源
// 字  数: 8
// 说  明:
typedef enum {
    V_PRIMARY_INS_NA   = 0, // 无意义
    V_PRIMARY_INS_INS1 = 1, // 惯导1
    V_PRIMARY_INS_INS2 = 2, // 惯导2
    V_PRIMARY_INS_INS3 = 3, // 惯导3
} PRIMARY_INS;

// 标识符: primary_secondary
// 名  称: 主备状态
// 字  数: 8
// 说  明: 主备状态标志
typedef enum {
    V_PRIMARY_SECONDARY_NA        = 0, // 未知
    V_PRIMARY_SECONDARY_SECONDARY = 1, // 备
    V_PRIMARY_SECONDARY_PRIMARY   = 2, // 主
} PRIMARY_SECONDARY;

// 标识符: primary_secondary_recommend_type
// 名  称: 主备推荐方式
// 字  数: 8
// 说  明:
typedef enum {
    V_PRIMARY_SECONDARY_RECOMMEND_TYPE_NA     = 0, // 无意义
    V_PRIMARY_SECONDARY_RECOMMEND_TYPE_AUTO   = 1, // 自动
    V_PRIMARY_SECONDARY_RECOMMEND_TYPE_MANUAL = 2, // 人工
} PRIMARY_SECONDARY_RECOMMEND_TYPE;

// 标识符: PRM_invalid_state
// 名  称: PRM失效状态
// 字  数: 8
// 说  明: 用于表征卫星军码PRM的失效状态。其中：
//         “正常有效”指PRM失效的日期与当前的日期差大于8周；
//         “邻近失效”指PRM失效的日期与当前的日期差在8周内；
//         “失效”指PRM失效的日期超过了当前的日期。
typedef enum {
    V_PRM_INVALID_STATE_NA           = 0, // 未知
    V_PRM_INVALID_STATE_VALID        = 1, // 正常有效
    V_PRM_INVALID_STATE_NEAR_INVALID = 2, // 邻近失效
    V_PRM_INVALID_STATE_INVALID      = 3, // 失效
} PRM_INVALID_STATE;

// 标识符: range_precison
// 名  称: 距离精度
// 字  数: 8
// 说  明: 载机对目标的测距误差小于等于200m时，距离精度为精
//         载机对目标的测距误差小于等于2000m且大于200m时，距离精度为粗
//         载机对目标的测距误差小于等于4000m且大于2000m时，距离精度为极粗
//         载机对目标的测距误差大于4000m时，距离精度为无效
typedef enum {
    V_RANGE_PRECISON_NA          = 0, //
    V_RANGE_PRECISON_PRECISE     = 1, // 精
    V_RANGE_PRECISON_COARSE      = 2, // 粗
    V_RANGE_PRECISON_VERY_COARSE = 3, // 极粗
    V_RANGE_PRECISON_INVALID     = 4, // 无效
} RANGE_PRECISON;

// 标识符: range_source
// 名  称: 距离获取方式
// 字  数: 8
// 说  明:
typedef enum {
    V_RANGE_SOURCE_NA        = 0, //
    V_RANGE_SOURCE_LASER     = 1, // 激光测距
    V_RANGE_SOURCE_COL_IRST  = 2, // 协同IRST定位
    V_RANGE_SOURCE_LASER_COL = 3, // 激光协同定位距离融合
} RANGE_SOURCE;

// 标识符: RDR_AA_Control
// 名  称: 雷达_空空权限
// 字  数: 8
// 说  明:
typedef enum {
    V_RDR_AA_CONTROL_NA        = 0, //
    V_RDR_AA_CONTROL_FRONTSEAT = 1, // 前舱
    V_RDR_AA_CONTROL_BACKSEAT  = 2, // 后舱
} RDR_AA_CONTROL;

// 标识符: RDR_AS_Control
// 名  称: 雷达_空面权限
// 字  数: 8
// 说  明:
typedef enum {
    V_RDR_AS_CONTROL_NA        = 0, //
    V_RDR_AS_CONTROL_FRONTSEAT = 1, // 前舱
    V_RDR_AS_CONTROL_BACKSEAT  = 2, // 后舱
} RDR_AS_CONTROL;

// 标识符: return_mode
// 名  称: 返航方式
// 字  数: 8
// 说  明: 返航的方式
typedef enum {
    V_RETURN_MODE_NA     = 0, //
    V_RETURN_MODE_NORMAL = 1, // 正常返航
    V_RETURN_MODE_BINGO  = 2, // 经济返航
} RETURN_MODE;

// 标识符: RNG_CHG
// 名  称: 量程修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_RNG_CHG_NO  = 0, // 不修改
    V_RNG_CHG_YES = 1, // 修改
} RNG_CHG;

// 标识符: RNG_DIRECTION_CHG
// 名  称: 扫描方向修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_RNG_DIRECTION_CHG_NO  = 0, // 不修改
    V_RNG_DIRECTION_CHG_YES = 1, // 修改
} RNG_DIRECTION_CHG;

// 标识符: RNG_LOW_CHG
// 名  称: 近界距离修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_RNG_LOW_CHG_NO  = 0, // 不修改
    V_RNG_LOW_CHG_YES = 1, // 修改
} RNG_LOW_CHG;

// 标识符: RNG_UP_CHG
// 名  称: 远界距离修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_RNG_UP_CHG_NO  = 0, // 不修改
    V_RNG_UP_CHG_YES = 1, // 修改
} RNG_UP_CHG;

// 标识符: router_point_types
// 名  称: 航线点类型
// 字  数: 8
// 说  明: 航线点类型，包括了航路点的“常规、塔康、机场、参考”点类型，及攻击投放计划中的“投放、目标”点类型。协同点和标记点引入飞行计划后作为常规点。
typedef enum {
    V_ROUTER_POINT_TYPES_NA      = 0, //
    V_ROUTER_POINT_TYPES_NORMAL  = 1, // 常规点
    V_ROUTER_POINT_TYPES_TACAN   = 2, // 塔康点
    V_ROUTER_POINT_TYPES_AIRPORT = 3, // 机场点
    V_ROUTER_POINT_TYPES_INITIAL = 4, // 参考点
    V_ROUTER_POINT_TYPES_RELEASE = 5, // 投放点
    V_ROUTER_POINT_TYPES_TARGET  = 6, // 目标点
} ROUTER_POINT_TYPES;

// 标识符: sat_anti_cheat_identify
// 名  称: 卫星防欺骗识别状态
// 字  数: 8
// 说  明:
typedef enum {
    V_SAT_ANTI_CHEAT_IDENTIFY_CHEAT_NO_IDENTIFY = 0, // 未识别欺骗
    V_SAT_ANTI_CHEAT_IDENTIFY_CHEAT_IDENTIFY    = 1, // 识别欺骗
} SAT_ANTI_CHEAT_IDENTIFY;

// 标识符: SAT_select_state
// 名  称: 惯导当前选择卫星
// 字  数: 8
// 说  明:
typedef enum {
    V_SAT_SELECT_STATE_NA      = 0, //
    V_SAT_SELECT_STATE_BD3_JUN = 2, // BD3军码
    V_SAT_SELECT_STATE_BD3_MIN = 3, // BD3民码
    V_SAT_SELECT_STATE_GPS     = 4, // GPS
    V_SAT_SELECT_STATE_VMC     = 5, // VMC转发
} SAT_SELECT_STATE;

// 标识符: satellite_use_state
// 名  称: 卫星使用状态
// 字  数: 8
// 说  明: 此信号用于表征卫星的使用状态。
typedef enum {
    V_SATELLITE_USE_STATE_NA                      = 0, // 未知状态
    V_SATELLITE_USE_STATE_MC_USED                 = 1, // 使用军码
    V_SATELLITE_USE_STATE_MC_INVALID_CC_AVAILABLE = 2, // 军码无效可用民码
    V_SATELLITE_USE_STATE_MC_INVALID_CC_USED      = 3, // 军码无效使用民码
    V_SATELLITE_USE_STATE_MC_CC_INVALID           = 4, // 军码民码均无效
} SATELLITE_USE_STATE;

// 标识符: scan_direct_tag
// 名  称: 扫描方向标志
// 字  数: 1
// 说  明: 顺航向从左到右为正扫，反之为反扫。光电专用
typedef enum {
    V_SCAN_DIRECT_TAG_FORWARD_DIRECT1 = 0, // 正扫
    V_SCAN_DIRECT_TAG_REVERSE1        = 1, // 反扫
} SCAN_DIRECT_TAG;

// 标识符: secret_level
// 名  称: 密级
// 字  数: 8
// 说  明: 目前只有非密/秘密两种密级，后续可能会增加更多的密级
typedef enum {
    V_SECRET_LEVEL_UNCLASSIFIED = 0, // 非密
    V_SECRET_LEVEL_SECRET       = 1, // 秘密
    V_SECRET_LEVEL_HIGHSECRET   = 2, // 机密
    V_SECRET_LEVEL_TOPSECRET    = 3, // 绝密
} SECRET_LEVEL;

// 标识符: security_code_validity
// 名  称: 系统安全_密码有效性
// 字  数: 8
// 说  明:
typedef enum {
    V_SECURITY_CODE_VALIDITY_NA      = 0, //
    V_SECURITY_CODE_VALIDITY_INVALID = 1, // 无效
    V_SECURITY_CODE_VALIDITY_VALID   = 2, // 有效
} SECURITY_CODE_VALIDITY;

// 标识符: security_ID_validity
// 名  称: 系统安全_用户名有效性
// 字  数: 8
// 说  明:
typedef enum {
    V_SECURITY_ID_VALIDITY_NA      = 0, //
    V_SECURITY_ID_VALIDITY_INVALID = 1, // 无效
    V_SECURITY_ID_VALIDITY_VALID   = 2, // 有效
} SECURITY_ID_VALIDITY;

// 标识符: security_level
// 名  称: 系统安全_密级
// 字  数: 8
// 说  明: 目前只有非密/秘密两种密级，后续可能会增加更多的密级
typedef enum {
    V_SECURITY_LEVEL_UNCLASSIFIED    = 0,  // 非密
    V_SECURITY_LEVEL_SECRET          = 1,  // 秘密
    V_SECURITY_LEVEL_HIGHSECRET      = 2,  // 机密
    V_SECURITY_LEVEL_TOPSECRET       = 3,  // 绝密
    V_SECURITY_LEVEL_PRE_UNCLASSIFED = 10, // 预备非密
    V_SECURITY_LEVEL_PRE_SECRET      = 11, // 预备秘密
} SECURITY_LEVEL;

// 标识符: security_State_Subsystem
// 名  称: 子系统保密状态
// 字  数: 8
// 说  明:
typedef enum {
    V_SECURITY_STATE_SUBSYSTEM_NO_SEC    = 0, // 非密
    V_SECURITY_STATE_SUBSYSTEM_SEC       = 1, // 秘密
    V_SECURITY_STATE_SUBSYSTEM_POWER_OFF = 2, // 关机
    V_SECURITY_STATE_SUBSYSTEM_UNKNOW    = 3, // 未知
    V_SECURITY_STATE_SUBSYSTEM_ING       = 4, // 切换中
} SECURITY_STATE_SUBSYSTEM;

// 标识符: sendstate_818_eots
// 名  称: 情报数据818总线发送状态_EOTS
// 字  数: 8
// 说  明:
typedef enum {
    V_SENDSTATE_818_EOTS_NA       = 0, //
    V_SENDSTATE_818_EOTS_SEND     = 1, // 已发送
    V_SENDSTATE_818_EOTS_NOT_SEND = 2, // 未发送
} SENDSTATE_818_EOTS;

// 标识符: situation_event_type
// 名  称: 态势事件类型
// 字  数: 8
// 说  明:
typedef enum {
    V_SITUATION_EVENT_TYPE_NA              = 0, //
    V_SITUATION_EVENT_TYPE_NEW_TGT_APPEAR  = 1, // 新目标出现
    V_SITUATION_EVENT_TYPE_TGT_DISAPPEAR   = 2, // 目标消失
    V_SITUATION_EVENT_TYPE_TGT_SEARCHING   = 3, // 敌搜索
    V_SITUATION_EVENT_TYPE_TGT_TRACKING    = 4, // 敌跟踪
    V_SITUATION_EVENT_TYPE_TGT_JAMMING     = 5, // 敌干扰
    V_SITUATION_EVENT_TYPE_LASER_WARNING   = 6, // 激光告警
    V_SITUATION_EVENT_TYPE_MISSILE_WARNING = 7, // 导弹告警
} SITUATION_EVENT_TYPE;

// 标识符: slave_main_sensor
// 名  称: 随动主传感器
// 字  数: 8
// 说  明:
typedef enum {
    V_SLAVE_MAIN_SENSOR_NA     = 0, //
    V_SLAVE_MAIN_SENSOR_HMD    = 1, // 头显
    V_SLAVE_MAIN_SENSOR_CURSOR = 2, // 光标
    V_SLAVE_MAIN_SENSOR_RDR    = 3, // 雷达
    V_SLAVE_MAIN_SENSOR_IRST   = 4, // IRST
    V_SLAVE_MAIN_SENSOR_TGT    = 5, // 目标
    V_SLAVE_MAIN_SENSOR_LOS    = 6, // LOS
} SLAVE_MAIN_SENSOR;

// 标识符: sp_change_mode
// 名  称: 操纵点切换方式
// 字  数: 8
// 说  明:
typedef enum {
    V_SP_CHANGE_MODE_AUTO   = 0, // 自动
    V_SP_CHANGE_MODE_MANUAL = 1, // 手动
} SP_CHANGE_MODE;

// 标识符: special_maint_data_type
// 名  称: 特殊维护参数类型
// 字  数: 8
// 说  明:
typedef enum {
    V_SPECIAL_MAINT_DATA_TYPE_NA               = 0,  //
    V_SPECIAL_MAINT_DATA_TYPE_INS1_CAL_DATA    = 1,  // INS1校准参数
    V_SPECIAL_MAINT_DATA_TYPE_INS1_MISC_DATA   = 2,  // INS1杂散参数
    V_SPECIAL_MAINT_DATA_TYPE_INS2_CAL_DATA    = 3,  // INS2校准参数
    V_SPECIAL_MAINT_DATA_TYPE_INS2_MISC_DATA   = 4,  // INS2杂散参数
    V_SPECIAL_MAINT_DATA_TYPE_FAHRS_CAL_DATA   = 5,  // FAHRS校准参数
    V_SPECIAL_MAINT_DATA_TYPE_HUD_CAL_DATA     = 6,  // HUD校准参数
    V_SPECIAL_MAINT_DATA_TYPE_RDR_CAL_DATA     = 7,  // RDR校准参数
    V_SPECIAL_MAINT_DATA_TYPE_CNI_CAL_DATA     = 8,  // CNI机间链校准参数
    V_SPECIAL_MAINT_DATA_TYPE_DAS_CAL_DATA     = 9,  // DAS校准参数
    V_SPECIAL_MAINT_DATA_TYPE_EWS_CAL_DATA     = 10, // EWS校准参数
    V_SPECIAL_MAINT_DATA_TYPE_IRST_CAL_DATA    = 11, // IRST校准参数
    V_SPECIAL_MAINT_DATA_TYPE_CNI_SAT_CAL_DATA = 12, // CNI卫通链校准参数
    V_SPECIAL_MAINT_DATA_TYPE_FCC_GUN_CAL_DATA = 13, // FCC航炮校准参数
    V_SPECIAL_MAINT_DATA_TYPE_INS3_CAL_DATA    = 15, // 惯导3校准参数
    V_SPECIAL_MAINT_DATA_TYPE_INS3_MISC_DATA   = 16, // 惯导3杂散参数
    V_SPECIAL_MAINT_DATA_TYPE_EWJ_CAL_DATA     = 17, // EWJ校准参数
    V_SPECIAL_MAINT_DATA_TYPE_CRSM_CAL_DATA    = 18, // CRSM校准参数
    V_SPECIAL_MAINT_DATA_TYPE_EDR_CAL_DATA     = 19, // EDR校准参数
} SPECIAL_MAINT_DATA_TYPE;

// 标识符: START_ANGLE_CHG
// 名  称: 起始角度修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_START_ANGLE_CHG_NO  = 0, // 不修改
    V_START_ANGLE_CHG_YES = 1, // 修改
} START_ANGLE_CHG;

// 标识符: state_change_event_type
// 名  称: 状态转换事件类型
// 字  数: 8
// 说  明:
typedef enum {
    V_STATE_CHANGE_EVENT_TYPE_NA               = 0, //
    V_STATE_CHANGE_EVENT_TYPE_MAIN_MODE_CHANGE = 1, // 主模式转换
    V_STATE_CHANGE_EVENT_TYPE_MSN_PHASE_CHANGE = 2, // 任务阶段转换
    V_STATE_CHANGE_EVENT_TYPE_EM_LEVEL_CHANGE  = 3, // 辐射等级转换
} STATE_CHANGE_EVENT_TYPE;

// 标识符: SUB_MODE_CHG
// 名  称: 广域成像子模式修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_SUB_MODE_CHG_NO  = 0, // 不修改
    V_SUB_MODE_CHG_YES = 1, // 修改
} SUB_MODE_CHG;

// 标识符: subdomain_ID
// 名  称: 功能单元ID
// 字  数: 32
// 说  明:
typedef enum {
    V_SUBDOMAIN_ID_NA         = 0,    //
    V_SUBDOMAIN_ID_ALL        = 1,    //
    V_SUBDOMAIN_ID_SRM        = 1000, // 传感器管理子域
    V_SUBDOMAIN_ID_SRMM       = 1001, // 传感器任务管理
    V_SUBDOMAIN_ID_SRS        = 1200, // 传感器模拟子域
    V_SUBDOMAIN_ID_EWSS       = 1202, // EWS模拟单元
    V_SUBDOMAIN_ID_DASS       = 1203, // DAS模拟单元
    V_SUBDOMAIN_ID_RDSS       = 1204, // RDR模拟单元
    V_SUBDOMAIN_ID_IN1        = 1300, // 惯导1子域
    V_SUBDOMAIN_ID_IN1M       = 1301, // 惯导1单元
    V_SUBDOMAIN_ID_IN2        = 1400, // 惯导2子域
    V_SUBDOMAIN_ID_IN2M       = 1401, // 惯导2单元
    V_SUBDOMAIN_ID_IN3        = 1500, // 惯导3子域
    V_SUBDOMAIN_ID_IN3M       = 1501, // 惯导3单元
    V_SUBDOMAIN_ID_CNI        = 1600, // 通信导航识别子域
    V_SUBDOMAIN_ID_CNIM       = 1601, // CNI系统控制管理
    V_SUBDOMAIN_ID_CNAM       = 1602, // ACU控制管理
    V_SUBDOMAIN_ID_CNRM       = 1603, // CNI射频前端控制管理
    V_SUBDOMAIN_ID_CNLA       = 1604, // 数据链代理
    V_SUBDOMAIN_ID_ETTM       = 1608, // 嵌训端机管理
    V_SUBDOMAIN_ID_VRSM       = 1609, // 语音管理单元
    V_SUBDOMAIN_ID_RDR        = 1700, // 雷达子域
    V_SUBDOMAIN_ID_RDRM       = 1701, // 雷达管理单元
    V_SUBDOMAIN_ID_RDDP       = 1702, // 雷达数据预处理单元
    V_SUBDOMAIN_ID_RDMP       = 1705, // 雷达图像后处理单元
    V_SUBDOMAIN_ID_RDCD       = 1706, // 雷达调度管理
    V_SUBDOMAIN_ID_EWS        = 1800, // 电子战干扰子域
    V_SUBDOMAIN_ID_EWSM       = 1801, // 电子战管理控制
    V_SUBDOMAIN_ID_EWFT       = 1802, // 电子战融合跟踪
    V_SUBDOMAIN_ID_EWRP       = 1803, // 电子战告警处理
    V_SUBDOMAIN_ID_EWEP       = 1804, // 电子战ESM处理
    V_SUBDOMAIN_ID_EWRM       = 1805, // 电子战接口与干扰
    V_SUBDOMAIN_ID_B3PM       = 1806, // B3吊舱管理单元
    V_SUBDOMAIN_ID_IRR        = 1900, // 综合光电子域
    V_SUBDOMAIN_ID_IRRM       = 1901, // 综合光电管理单元
    V_SUBDOMAIN_ID_IRVP       = 1902, // 光雷视频处理单元
    V_SUBDOMAIN_ID_EWJ        = 2000, // 电子战干扰子域
    V_SUBDOMAIN_ID_EWJM       = 2001, // 电子战干扰管理单元
    V_SUBDOMAIN_ID_DAIP       = 2002, // DAS图像处理单元
    V_SUBDOMAIN_ID_NAF        = 2100, // 导航融合子域
    V_SUBDOMAIN_ID_NAFM       = 2101, // 导航融合管理处理
    V_SUBDOMAIN_ID_IMF        = 2200, // 图像融合子域
    V_SUBDOMAIN_ID_IMFM       = 2201, // 图像融合
    V_SUBDOMAIN_ID_TGF        = 2300, // 目标融合子域
    V_SUBDOMAIN_ID_TGFA       = 2302, // 空空目标融合
    V_SUBDOMAIN_ID_TGFS       = 2303, // 空面目标融合
    V_SUBDOMAIN_ID_CPEG       = 2304, // 协同作战单元
    V_SUBDOMAIN_ID_TGFI       = 2305, // 综合识别单元
    V_SUBDOMAIN_ID_IIPM       = 2306, // 图像情报处理单元
    V_SUBDOMAIN_ID_EIPM       = 2307, // 电磁情报处理单元
    V_SUBDOMAIN_ID_JAS        = 2400, // 危险评估子域
    V_SUBDOMAIN_ID_JASM       = 2401, // 危险评估单元
    V_SUBDOMAIN_ID_LAS        = 2500, // 杀伤评估子域
    V_SUBDOMAIN_ID_LASM       = 2501, // 杀伤评估单元
    V_SUBDOMAIN_ID_ERD        = 2600, // 预警雷达
    V_SUBDOMAIN_ID_ERDM       = 2601, // 预警雷达管理单元
    V_SUBDOMAIN_ID_CRS        = 2700, // 通信侦察
    V_SUBDOMAIN_ID_CRSM       = 2701, // 通信侦察管理单元
    V_SUBDOMAIN_ID_HNM        = 2800, // 异构网络管理
    V_SUBDOMAIN_ID_NAIS       = 2801, // 网络应用接口单元
    V_SUBDOMAIN_ID_HNMS       = 2802, // 网络管理单元
    V_SUBDOMAIN_ID_HNCS       = 2803, // 网络控制单元
    V_SUBDOMAIN_ID_NDTS       = 2804, // 网络数据传输单元
    V_SUBDOMAIN_ID_MLTP       = 2805, // 多链目标数据处理单元
    V_SUBDOMAIN_ID_NTRM       = 2806, // 网络时基管理单元
    V_SUBDOMAIN_ID_NSSS       = 2807, // 网络安全单元
    V_SUBDOMAIN_ID_TMM        = 3100, // 战术管理子域
    V_SUBDOMAIN_ID_TMMM       = 3101, // 战术管理处理
    V_SUBDOMAIN_ID_ETMM       = 3102, // 训练任务管理
    V_SUBDOMAIN_ID_IFRP       = 3103, // 任务重规划
    V_SUBDOMAIN_ID_NAC        = 3200, // 导航管理子域
    V_SUBDOMAIN_ID_NACL       = 3201, // 左导航管理单元
    V_SUBDOMAIN_ID_NACR       = 3202, // 右导航管理单元
    V_SUBDOMAIN_ID_TRP        = 3300, // 威胁响应子域
    V_SUBDOMAIN_ID_TRPM       = 3301, // 威胁响应单元
    V_SUBDOMAIN_ID_TRCM       = 3302, // 无源干扰单元
    V_SUBDOMAIN_ID_FTM        = 3400, // 编队战术任务管理子域
    V_SUBDOMAIN_ID_G11M       = 3401, // 攻11协同管理控制
    V_SUBDOMAIN_ID_SMS        = 4100, // 悬挂物管理子域
    V_SUBDOMAIN_ID_SMSM       = 4101, // 悬挂物系统管理
    V_SUBDOMAIN_ID_SMU1       = 4102, // FRIU1接口单元
    V_SUBDOMAIN_ID_SMU2       = 4103, // FRIU2接口单元
    V_SUBDOMAIN_ID_SMET       = 4104, // 嵌训武器模拟
    V_SUBDOMAIN_ID_FCC        = 4200, // 火控解算子域
    V_SUBDOMAIN_ID_FCCM       = 4201, // 火控解算单元
    V_SUBDOMAIN_ID_FCAS       = 4202, // 空面火控单元
    V_SUBDOMAIN_ID_DCL        = 5100, // 左显控子域
    V_SUBDOMAIN_ID_DCLM       = 5101, // 左显控主控单元
    V_SUBDOMAIN_ID_DCLD       = 5102, // 左显控数管单元
    V_SUBDOMAIN_ID_DCLP       = 5103, // 左显控地图单元
    V_SUBDOMAIN_ID_DCLX       = 5104, // 左显控显示单元
    V_SUBDOMAIN_ID_DLPV       = 5105, // 左显控飞控健康管理单元
    V_SUBDOMAIN_ID_DLPU       = 5106, // 左显控机电健康管理单元
    V_SUBDOMAIN_ID_DLEM       = 5107, // 左显控高程服务单元
    V_SUBDOMAIN_ID_DCR        = 5200, // 右显控子域
    V_SUBDOMAIN_ID_DCRM       = 5201, // 右显控主控单元
    V_SUBDOMAIN_ID_DCRD       = 5202, // 右显控数管单元
    V_SUBDOMAIN_ID_DCRP       = 5203, // 右显控地图单元
    V_SUBDOMAIN_ID_DCRX       = 5204, // 右显控显示单元
    V_SUBDOMAIN_ID_DRPV       = 5205, // 右显控飞控健康管理单元
    V_SUBDOMAIN_ID_DRPU       = 5206, // 右显控机电健康管理单元
    V_SUBDOMAIN_ID_DREM       = 5207, // 右显控高程服务单元
    V_SUBDOMAIN_ID_DCB        = 5300, // 后显控子域
    V_SUBDOMAIN_ID_DCBM       = 5301, // 后显控主控单元
    V_SUBDOMAIN_ID_DCBP       = 5302, // 后显控地图单元
    V_SUBDOMAIN_ID_DBXL       = 5303, // 后显控左显示单元
    V_SUBDOMAIN_ID_DBXR       = 5304, // 后显控右显示单元
    V_SUBDOMAIN_ID_DCBD       = 5305, // 后显控数管单元
    V_SUBDOMAIN_ID_DCA        = 5400, // 辅显子域
    V_SUBDOMAIN_ID_DCAM       = 5401, // 辅显单元
    V_SUBDOMAIN_ID_HUD        = 5500, // 平显子域
    V_SUBDOMAIN_ID_HUDM       = 5501, // 平显单元
    V_SUBDOMAIN_ID_HMD        = 5600, // 头显子域
    V_SUBDOMAIN_ID_HMDM       = 5601, // 头显单元
    V_SUBDOMAIN_ID_UFP        = 5700, // 正显子域
    V_SUBDOMAIN_ID_UFCP       = 5701, // 正显单元
    V_SUBDOMAIN_ID_MFD        = 5800, // 主显子域
    V_SUBDOMAIN_ID_FMFD       = 5801, // 前舱大屏显示器
    V_SUBDOMAIN_ID_BMFD       = 5802, // 后舱大屏显示器
    V_SUBDOMAIN_ID_CLC        = 5900, // 座舱照明控制子域
    V_SUBDOMAIN_ID_FCLM       = 5901, // 前舱照明控制器
    V_SUBDOMAIN_ID_BCLM       = 5902, // 后舱照明控制器
    V_SUBDOMAIN_ID_TSD        = 6000, // 战术情景显示器子域
    V_SUBDOMAIN_ID_TSDM       = 6001, // 战术情景显示单元
    V_SUBDOMAIN_ID_SYM        = 6100, // 系统管理子域
    V_SUBDOMAIN_ID_SYMM       = 6101, // 系统管理单元
    V_SUBDOMAIN_ID_SYMD       = 6102, // 系统数据库单元
    V_SUBDOMAIN_ID_SYOS       = 6103, // 执行环境处理单元
    V_SUBDOMAIN_ID_CPDM       = 6104, // 核心管理单元
    V_SUBDOMAIN_ID_CPUM       = 6105, // CPU管理单元
    V_SUBDOMAIN_ID_ICP        = 6200, // 综合核心处理机子域
    V_SUBDOMAIN_ID_PHM        = 7100, // 健康管理子域
    V_SUBDOMAIN_ID_MPHL       = 7101, // 任务系统左健康管理单元
    V_SUBDOMAIN_ID_APHM       = 7102, // 飞机系统健康管理单元
    V_SUBDOMAIN_ID_VPHM       = 7103, // 飞控系统健康管理单元
    V_SUBDOMAIN_ID_UPHM       = 7104, // 机电系统健康管理单元
    V_SUBDOMAIN_ID_MPHR       = 7105, // 任务系统右健康管理单元
    V_SUBDOMAIN_ID_VMS        = 8100, // 飞管系统子域
    V_SUBDOMAIN_ID_VCAM       = 8101, // 飞管计算机A
    V_SUBDOMAIN_ID_VCBM       = 8102, // 飞管计算机B
    V_SUBDOMAIN_ID_VCCM       = 8103, // 飞管计算机C
    V_SUBDOMAIN_ID_BFCC       = 8104, // 飞管计算机D
    V_SUBDOMAIN_ID_SEAT       = 8105, // 弹射座椅单元
    V_SUBDOMAIN_ID_AGC        = 8200, // 地形防撞子域
    V_SUBDOMAIN_ID_CDLM       = 8201, // C链端机
    V_SUBDOMAIN_ID_KDLM       = 8202, // K链端机
    V_SUBDOMAIN_ID_DCD        = 9100, // 数据管理子域
    V_SUBDOMAIN_ID_ISRM       = 9102, // 防护型综合记录器
    V_SUBDOMAIN_ID_MDEM       = 9103, // 维护数据卡
    V_SUBDOMAIN_ID_TDEM       = 9104, // 战术数据卡
    V_SUBDOMAIN_ID_MAINTEQUIP = 9200, // 维护接口子域
    V_SUBDOMAIN_ID_PMA        = 9201, // PMA接口单元
    V_SUBDOMAIN_ID_GMP        = 9202, // GMP接口单元
} SUBDOMAIN_ID;

// 标识符: subsys_main_mode
// 名  称: 工作模式
// 字  数: 8
// 说  明: 描述系统的工作模式；
//         初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
typedef enum {
    V_SUBSYS_MAIN_MODE_NA        = 0, // 无意义或保持
    V_SUBSYS_MAIN_MODE_INI       = 1, // 初始化
    V_SUBSYS_MAIN_MODE_LOW_POWER = 2, // 省电模式
    V_SUBSYS_MAIN_MODE_STBY      = 3, // 待机模式
    V_SUBSYS_MAIN_MODE_NORMAL    = 4, // 正常模式
    V_SUBSYS_MAIN_MODE_BACKUP    = 5, // 备份模式
    V_SUBSYS_MAIN_MODE_TEST      = 6, // 测试模式、维护模式（自检）
    V_SUBSYS_MAIN_MODE_STOP      = 7, // 停止/可关机模式
    V_SUBSYS_MAIN_MODE_EMERGENCY = 8, // 应急模式
    V_SUBSYS_MAIN_MODE_SW_LOAD   = 9, // 软件加载
} SUBSYS_MAIN_MODE;

// 标识符: subsys_main_oper_mode
// 名  称: 子系统工作模式
// 字  数: 8
// 说  明: 描述系统的工作模式；
//         初始化模式是各子系统初始启动时自有的一种工作模式，不能作为命令下发
typedef enum {
    V_SUBSYS_MAIN_OPER_MODE_NA         = 0, //
    V_SUBSYS_MAIN_OPER_MODE_INI        = 1, // 初始化
    V_SUBSYS_MAIN_OPER_MODE_LOW_POWER  = 2, // 省电模式
    V_SUBSYS_MAIN_OPER_MODE_STBY       = 3, // 待机模式
    V_SUBSYS_MAIN_OPER_MODE_NORMAL     = 4, // 正常模式
    V_SUBSYS_MAIN_OPER_MODE_BACKUP     = 5, // 备份模式
    V_SUBSYS_MAIN_OPER_MODE_TEST       = 6, // 测试模式
    V_SUBSYS_MAIN_OPER_MODE_STOP       = 7, // 停止/可关机模式-下电
    V_SUBSYS_MAIN_OPER_MODE_SW_LOAD    = 8, // 软件加载
    V_SUBSYS_MAIN_OPER_MODE_SW_RESTART = 9, // 软件复位
} SUBSYS_MAIN_OPER_MODE;

// 标识符: subsys_work_state
// 名  称: 工作状态
// 字  数: 8
// 说  明: 子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
//         20190620，雷达/ICP省电模式设计，新增地面省电状态，BY 3649。
//         20190918，新增故障信息记录状态，用于ICP信息记录到MMM中，BY 3649。
//         20250515，增加应急状态，表示ICP处于28V供电的一个工作状态。
typedef enum {
    V_SUBSYS_WORK_STATE_NA               = 0,  // 未知
    V_SUBSYS_WORK_STATE_NORMAL           = 1,  // 正常
    V_SUBSYS_WORK_STATE_BIT              = 2,  // 自检测
    V_SUBSYS_WORK_STATE_DEGRADE          = 3,  // 降级
    V_SUBSYS_WORK_STATE_FAIL             = 4,  // 失效
    V_SUBSYS_WORK_STATE_OFF              = 5,  // 关闭
    V_SUBSYS_WORK_STATE_OFFLINE          = 6,  // 总线断
    V_SUBSYS_WORK_STATE_STOP             = 7,  // 功能停止
    V_SUBSYS_WORK_STATE_GND_LOW_POWER    = 8,  // 地面省电
    V_SUBSYS_WORK_STATE_FAIL_INFO_RECORD = 19, // 故障信息记录
    V_SUBSYS_WORK_STATE_RECONFIG         = 20, // 重构
    V_SUBSYS_WORK_STATE_EMERGENCY        = 30, // 应急
} SUBSYS_WORK_STATE;

// 标识符: SYN_MODE
// 名  称: 前后舱同步/异步模式
// 字  数: 8
// 说  明:
typedef enum {
    V_SYN_MODE_NA   = 0, //
    V_SYN_MODE_SYN  = 1, // 同步模式
    V_SYN_MODE_ASYN = 2, // 异步模式
} SYN_MODE;

// 标识符: tacan_paras_mode
// 名  称: 塔康参数控制方式
// 字  数: 8
// 说  明:
typedef enum {
    V_TACAN_PARAS_MODE_AUTO   = 0, // 自动
    V_TACAN_PARAS_MODE_MANUAL = 1, // 手动
} TACAN_PARAS_MODE;

// 标识符: target_class
// 名  称: 目标类型
// 字  数: 8
// 说  明: 注：ALL 普查，仅图像情报使用
typedef enum {
    V_TARGET_CLASS_NA                     = 0,   //
    V_TARGET_CLASS_AIRCRAFT               = 1,   // 飞机
    V_TARGET_CLASS_MSL                    = 2,   // 导弹
    V_TARGET_CLASS_UNKOWN                 = 3,   // 未知
    V_TARGET_CLASS_GROUND_IMMOVABLE       = 4,   // 地面固定
    V_TARGET_CLASS_WARSHIP                = 5,   // 舰船
    V_TARGET_CLASS_SATELLITE              = 6,   // 卫星
    V_TARGET_CLASS_BALLOON                = 7,   // 气球
    V_TARGET_CLASS_GROUND_MOVABLE         = 8,   // 地面移动
    V_TARGET_CLASS_SUBMERGENCE_BOAT       = 9,   // 潜艇
    V_TARGET_CLASS_HELICOPTER             = 10,  // 直升机
    V_TARGET_CLASS_POLITLESS_AIRCRAFT     = 11,  // 无人机
    V_TARGET_CLASS_VEHICLE                = 12,  // 车辆
    V_TARGET_CLASS_EXPEDIENCE             = 13,  // 便携、背负
    V_TARGET_CLASS_AIRSHIP                = 14,  // 飞船载
    V_TARGET_CLASS_FIGHTER                = 15,  // 战斗机
    V_TARGET_CLASS_BOMBER                 = 16,  // 轰炸机
    V_TARGET_CLASS_AIR_RAD                = 17,  // 预警机
    V_TARGET_CLASS_CRU_MSL                = 18,  // 巡航导弹
    V_TARGET_CLASS_SUPPORT                = 19,  // 支援机
    V_TARGET_CLASS_TANKER                 = 20,  // 加油机
    V_TARGET_CLASS_CIVIL                  = 21,  // 民机
    V_TARGET_CLASS_RECON                  = 22,  // 侦察机
    V_TARGET_CLASS_CARGO                  = 23,  // 运输机
    V_TARGET_CLASS_SAM_SITE               = 24,  // 导弹阵地
    V_TARGET_CLASS_AAA_SITE               = 25,  // 高炮阵地
    V_TARGET_CLASS_EW_SITE                = 26,  // 电子战阵地
    V_TARGET_CLASS_EOB                    = 27,  // EOB目标
    V_TARGET_CLASS_CARRIER                = 28,  // 航母
    V_TARGET_CLASS_COMBATANT              = 29,  // 战斗舰
    V_TARGET_CLASS_COMMERCIAL             = 30,  // 商船
    V_TARGET_CLASS_TANK                   = 31,  // 坦克群
    V_TARGET_CLASS_AC_WALL                = 32,  // 飞机遮蔽库
    V_TARGET_CLASS_RUNWAY                 = 33,  // 跑道
    V_TARGET_CLASS_BUILDING               = 34,  // 建筑
    V_TARGET_CLASS_SITE                   = 35,  // 技术兵阵地
    V_TARGET_CLASS_STATIC_AC              = 36,  // 停机坪上的飞机
    V_TARGET_CLASS_STATIC_CAR             = 37,  // 静止车辆
    V_TARGET_CLASS_STATIC_SHIP            = 38,  // 停泊舰船
    V_TARGET_CLASS_MOVE_CAR               = 39,  // 运动车辆
    V_TARGET_CLASS_MOVE_SHIP              = 40,  // 运动舰船
    V_TARGET_CLASS_BRIGE                  = 41,  // 桥梁
    V_TARGET_CLASS_GROUND_RADAR           = 42,  // 地基雷达
    V_TARGET_CLASS_OTHER                  = 43,  // 其它
    V_TARGET_CLASS_BCN                    = 44,  // 信标
    V_TARGET_CLASS_AIRBORNE_WARNING       = 45,  // 机载预警
    V_TARGET_CLASS_GROUND_ALERT           = 46,  // 地面警戒
    V_TARGET_CLASS_GROUND_GUIDANCE        = 47,  // 地面制导
    V_TARGET_CLASS_SHIPBORNE_WARNING      = 48,  // 舰载预警
    V_TARGET_CLASS_SHIPBORNE_GUIDANCE     = 49,  // 舰载制导
    V_TARGET_CLASS_MISSILE_LAUNCH_VEHICLE = 50,  // 导弹发射车
    V_TARGET_CLASS_AIRPORT                = 100, // 机场
    V_TARGET_CLASS_PORT                   = 101, // 港口
    V_TARGET_CLASS_ALL                    = 255, // 普查
} TARGET_CLASS;

// 标识符: target_jam_state
// 名  称: 目标干扰状态
// 字  数: 8
// 说  明: 表示目标干扰状态。
typedef enum {
    V_TARGET_JAM_STATE_NA      = 0, // 未干扰
    V_TARGET_JAM_STATE_JAMMING = 1, // 干扰
} TARGET_JAM_STATE;

// 标识符: target_physics_size
// 名  称: 目标物理尺寸
// 字  数: 8
// 说  明: 目标机身长度范围大于25m为大尺寸目标
//         目标机身长度范围为(10,25]m为中尺寸目标
//         目标机身长度范围为(3,10]m为小尺寸目标
//         目标机身长度范围为(0,3]m为超小尺寸目标
typedef enum {
    V_TARGET_PHYSICS_SIZE_NA        = 0, // 未知
    V_TARGET_PHYSICS_SIZE_SMALL     = 1, // 小尺寸
    V_TARGET_PHYSICS_SIZE_MID       = 2, // 中尺寸
    V_TARGET_PHYSICS_SIZE_BIG       = 3, // 大尺寸
    V_TARGET_PHYSICS_SIZE_MIN_SMALL = 4, // 超小尺寸
    V_TARGET_PHYSICS_SIZE_AUTO      = 5, // 自动
} TARGET_PHYSICS_SIZE;

// 标识符: target_rcs_type_2GCS
// 名  称: 目标RCS类型_宽带下传
// 字  数: 4
// 说  明: 目标RCS范围>19平米为大目标
//         目标RCS范围为[1,19]平米为中目标
//         目标RCS范围为[0.1,1)平米为小目标
//         目标RCS范围为(0,0.1)平米为隐身目标
typedef enum {
    V_TARGET_RCS_TYPE_2GCS_NA         = 0, // 未知
    V_TARGET_RCS_TYPE_2GCS_SMALL_SIZE = 1, // 小目标
    V_TARGET_RCS_TYPE_2GCS_MID_SIZE   = 2, // 中目标
    V_TARGET_RCS_TYPE_2GCS_BIG_SIZE   = 3, // 大目标
    V_TARGET_RCS_TYPE_2GCS_MIN_SIZE   = 4, // 隐身目标
    V_TARGET_RCS_TYPE_2GCS_AUTO       = 5, // 自动
} TARGET_RCS_TYPE_2GCS;

// 标识符: target_special_tag
// 名  称: 目标特殊标识
// 字  数: 8
// 说  明:
typedef enum {
    V_TARGET_SPECIAL_TAG_NA         = 0,  //
    V_TARGET_SPECIAL_TAG_HPT        = 1,  // 最高优先级
    V_TARGET_SPECIAL_TAG_SPT        = 2,  // 次优先级
    V_TARGET_SPECIAL_TAG_NORMAL     = 3,  // 一般目标
    V_TARGET_SPECIAL_TAG_NTS        = 4,  // NTS目标
    V_TARGET_SPECIAL_TAG_SL_NOT_NTS = 5,  // 射击列表非NTS目标
    V_TARGET_SPECIAL_TAG_SPI        = 6,  // 系统关注点
    V_TARGET_SPECIAL_TAG_CO_LCTION  = 7,  // 协同定位目标
    V_TARGET_SPECIAL_TAG_CO_ATTACK  = 8,  // 协同攻击目标
    V_TARGET_SPECIAL_TAG_SURROGATE  = 9,  // 代理目标
    V_TARGET_SPECIAL_TAG_DEAD       = 10, // 已击毁目标
    V_TARGET_SPECIAL_TAG_MSL_ATTACK = 11, // 飞行中导弹攻击目标
} TARGET_SPECIAL_TAG;

// 标识符: target_track_state
// 名  称: 目标跟踪状态
// 字  数: 8
// 说  明: 20230522:更改11-STT_DOT描述为“点迹截获进SAM”。
//         20230608：新增“12-TRACK_SHOOTLIST-火控级跟踪”。
typedef enum {
    V_TARGET_TRACK_STATE_NA              = 0,  //
    V_TARGET_TRACK_STATE_TRACK           = 1,  // 跟踪
    V_TARGET_TRACK_STATE_MEMERY          = 2,  // 记忆外推
    V_TARGET_TRACK_STATE_STT             = 3,  // 单目标跟踪
    V_TARGET_TRACK_STATE_TAS             = 4,  // 搜索加跟踪
    V_TARGET_TRACK_STATE_JAM             = 5,  // 跟踪干扰源
    V_TARGET_TRACK_STATE_MTT             = 6,  // 多目标跟踪
    V_TARGET_TRACK_STATE_CALC            = 7,  // 计算插值（无采样的计算插值）
    V_TARGET_TRACK_STATE_STT_DOT         = 11, // 点迹截获进SAM
    V_TARGET_TRACK_STATE_TRACK_SHOOTLIST = 12, // 火控级跟踪
} TARGET_TRACK_STATE;

// 标识符: target_track_unstable_state
// 名  称: 目标跟踪不稳定状态
// 字  数: 8
// 说  明: 跟踪目标上报不稳定情况，快出框架角时上报火控更改下发AOC判断状态
typedef enum {
    V_TARGET_TRACK_UNSTABLE_STATE_NA               = 0, // NA
    V_TARGET_TRACK_UNSTABLE_STATE_STABLE           = 1, // 稳定
    V_TARGET_TRACK_UNSTABLE_STATE_ALMOST_OUT_FRAME = 2, // 快出框架角
} TARGET_TRACK_UNSTABLE_STATE;

// 标识符: TDC_Rate_Control_B
// 名  称: TDC移动速率控制_后舱
// 字  数: 8
// 说  明:
typedef enum {
    V_TDC_RATE_CONTROL_B_NA       = 0, //
    V_TDC_RATE_CONTROL_B_SLOWEST  = 1, // 慢
    V_TDC_RATE_CONTROL_B_SLOWER   = 2, // 较慢
    V_TDC_RATE_CONTROL_B_NORMAL   = 3, // 中
    V_TDC_RATE_CONTROL_B_QUICKER  = 4, // 较快
    V_TDC_RATE_CONTROL_B_QUICKEST = 5, // 快
} TDC_RATE_CONTROL_B;

// 标识符: TDC_Rate_Control_F
// 名  称: TDC移动速率控制_前舱
// 字  数: 8
// 说  明:
typedef enum {
    V_TDC_RATE_CONTROL_F_NA       = 0, //
    V_TDC_RATE_CONTROL_F_SLOWEST  = 1, // 慢
    V_TDC_RATE_CONTROL_F_SLOWER   = 2, // 较慢
    V_TDC_RATE_CONTROL_F_NORMAL   = 3, // 中
    V_TDC_RATE_CONTROL_F_QUICKER  = 4, // 较快
    V_TDC_RATE_CONTROL_F_QUICKEST = 5, // 快
} TDC_RATE_CONTROL_F;

// 标识符: tgt_attribute
// 名  称: 目标属性
// 字  数: 8
// 说  明:
typedef enum {
    V_TGT_ATTRIBUTE_NA         = 0, // 无报告
    V_TGT_ATTRIBUTE_FOE        = 1, // 敌方
    V_TGT_ATTRIBUTE_OUR        = 2, // 我方
    V_TGT_ATTRIBUTE_FRIEND     = 3, // 友方
    V_TGT_ATTRIBUTE_NEUTRAL    = 4, // 中立
    V_TGT_ATTRIBUTE_UNKOWN     = 5, // 未知/未决
    V_TGT_ATTRIBUTE_SUSPICIOUS = 6, // 可疑
    V_TGT_ATTRIBUTE_CIVIL      = 7, // 民用
} TGT_ATTRIBUTE;

// 标识符: tgt_in_SL
// 名  称: 目标与射击列表关联
// 字  数: 8
// 说  明: 表明目标在射击列表内的位置。
typedef enum {
    V_TGT_IN_SL_NA   = 0, // 不在射击列表内
    V_TGT_IN_SL_SL_1 = 1, // NTS目标
    V_TGT_IN_SL_SL_2 = 2, // 射击列表2号目标
    V_TGT_IN_SL_SL_3 = 3, // 射击列表3号目标
    V_TGT_IN_SL_SL_4 = 4, // 射击列表4号目标
    V_TGT_IN_SL_SL_5 = 5, // 射击列表5号目标
    V_TGT_IN_SL_SL_6 = 6, // 射击列表6号目标
    V_TGT_IN_SL_SL_7 = 7, // 射击列表7号目标
    V_TGT_IN_SL_SL_8 = 8, // 射击列表8号目标
} TGT_IN_SL;

// 标识符: tgt_model
// 名  称: 平台型号
// 字  数: 16
// 说  明: 各型号的定义在ICD文件中用表格形式明确。
//         定义如下：
//         95-J20
//         121-歼20ISC
//         122-J20A
//         150-攻-11
//
typedef enum {
    V_TGT_MODEL_NA = 0, //
} TGT_MODEL;

// 标识符: tgt_source
// 名  称: 目标来源
// 字  数: 8
// 说  明:
typedef enum {
    V_TGT_SOURCE_NA      = 0,  // 无意义
    V_TGT_SOURCE_RDR_AA  = 1,  // 雷达空空目标
    V_TGT_SOURCE_RDR_AS  = 2,  // 雷达空面目标
    V_TGT_SOURCE_EW_AA   = 3,  // 电子战空空目标
    V_TGT_SOURCE_EW_AS   = 4,  // 电子战空面目标
    V_TGT_SOURCE_IRST_AA = 5,  // 光雷空空目标
    V_TGT_SOURCE_IRST_AS = 6,  // 光雷空面目标
    V_TGT_SOURCE_DAS_AA  = 7,  // DAS空空目标
    V_TGT_SOURCE_DAS_AS  = 8,  // DAS空面目标
    V_TGT_SOURCE_LINK_AA = 9,  // 数据链空空目标
    V_TGT_SOURCE_LINK_AS = 10, // 数据链空面目标
} TGT_SOURCE;

// 标识符: TGT_TRACK_ID
// 名  称: 动目标ID
// 字  数: 4
// 说  明:
typedef enum {
    V_TGT_TRACK_ID_NA  = 0, //
    V_TGT_TRACK_ID_ID1 = 1, //
    V_TGT_TRACK_ID_ID2 = 2, //
    V_TGT_TRACK_ID_ID3 = 3, //
    V_TGT_TRACK_ID_ID4 = 4, //
    V_TGT_TRACK_ID_ID5 = 5, //
} TGT_TRACK_ID;

// 标识符: TGT_TRACK_STATE
// 名  称: 图像跟踪状态
// 字  数: 8
// 说  明:
typedef enum {
    V_TGT_TRACK_STATE_NA          = 0, //
    V_TGT_TRACK_STATE_TRACK_ING   = 1, // 跟踪中
    V_TGT_TRACK_STATE_NOT_TRACKED = 2, // 未跟踪
    V_TGT_TRACK_STATE_MATCH_ING   = 3, // 匹配中
} TGT_TRACK_STATE;

// 标识符: tgt_type
// 名  称: 平台类型
// 字  数: 8
// 说  明: 各类型的定义在ICD文件中用表格形式明确。
//         根据平台环境类别确定平台类型定义
typedef enum {
    V_TGT_TYPE_NA = 0, //
} TGT_TYPE;

// 标识符: threat_rank
// 名  称: 目标威胁等级
// 字  数: 8
// 说  明: 极低	[0.0,0.2]	不具备空空攻击能力的目标，如：运输机、预警机、轰炸机、侦察机等
//         低	[0.2,0.4]	具备作战能力的目标，距离较远
//         中	[0.4,0.6]	具备作战能力，距离较近
//         高	[0.6,0.9]	目标有能力发动攻击
//         极高	[0.9,2.0]	目标有攻击能力，且具有较明显的攻击意图
//         方括号中为威胁度计算值；
typedef enum {
    V_THREAT_RANK_NA        = 0, //
    V_THREAT_RANK_SUPER_HI  = 1, // 极高
    V_THREAT_RANK_HIGH      = 2, // 高
    V_THREAT_RANK_MIDDLE    = 3, // 中
    V_THREAT_RANK_LOW       = 4, // 低
    V_THREAT_RANK_SUPER_LOW = 5, // 极低
} THREAT_RANK;

// 标识符: time_calendar_sync_type
// 名  称: 时间_日历时间授时同步方式
// 字  数: 8
// 说  明:
typedef enum {
    V_TIME_CALENDAR_SYNC_TYPE_NA        = 0, // 空
    V_TIME_CALENDAR_SYNC_TYPE_MANUAL    = 1, // 人工修改
    V_TIME_CALENDAR_SYNC_TYPE_SATELLITE = 2, // 卫星时间
    V_TIME_CALENDAR_SYNC_TYPE_IFDL      = 3, // IFDL网络时间
    V_TIME_CALENDAR_SYNC_TYPE_JIDS      = 4, // JIDS网络时间
    V_TIME_CALENDAR_SYNC_TYPE_INNER     = 5, // 机内时间
} TIME_CALENDAR_SYNC_TYPE;

// 标识符: time_event_type
// 名  称: 时间事件类型
// 字  数: 8
// 说  明:
typedef enum {
    V_TIME_EVENT_TYPE_NA              = 0, //
    V_TIME_EVENT_TYPE_ARRIVAL_TIME    = 1, // 到达某时刻
    V_TIME_EVENT_TYPE_STATUS_DURATION = 2, // 状态持续时间
    V_TIME_EVENT_TYPE_TIMING_TINE     = 3, // 到达计时时刻
} TIME_EVENT_TYPE;

// 标识符: time_mission_sync_type
// 名  称: 时间_任务时间授时同步方式
// 字  数: 8
// 说  明:
typedef enum {
    V_TIME_MISSION_SYNC_TYPE_NA        = 0, // 空
    V_TIME_MISSION_SYNC_TYPE_MANUAL    = 1, // 人工修改
    V_TIME_MISSION_SYNC_TYPE_SATELLITE = 2, // 卫星时间
    V_TIME_MISSION_SYNC_TYPE_IFDL      = 3, // IFDL网络时间
    V_TIME_MISSION_SYNC_TYPE_JIDS      = 4, // JIDS网络时间
    V_TIME_MISSION_SYNC_TYPE_INNER     = 5, // 机内时间
} TIME_MISSION_SYNC_TYPE;

// 标识符: time_stopwatch_state
// 名  称: 时间_秒表计时状态
// 字  数: 8
// 说  明: 秒表计时的状态：
//         正在正计时
//         正在倒计时
//         正计时暂停
//         倒计时暂停
//         秒表非激活（T=0）
//         秒表非激活（T>0）
typedef enum {
    V_TIME_STOPWATCH_STATE_INIT             = 0, // 秒表非激活（T=0）
    V_TIME_STOPWATCH_STATE_DEASIL_TIMING    = 1, // 正在正计时
    V_TIME_STOPWATCH_STATE_COUNT_DOWN       = 2, // 正在倒计时
    V_TIME_STOPWATCH_STATE_DEASIL_PAUSED    = 3, // 正计时暂停
    V_TIME_STOPWATCH_STATE_COUNT_DOWN_PAUSE = 4, // 倒计时暂停
    V_TIME_STOPWATCH_STATE_SETED            = 5, // 秒表非激活（T>0）
} TIME_STOPWATCH_STATE;

// 标识符: TOI_rank
// 名  称: 目标关注等级
// 字  数: 8
// 说  明:
typedef enum {
    V_TOI_RANK_RANK_0 = 0, // 普通协同跟踪目标
    V_TOI_RANK_RANK_1 = 1, // 协同机NTS目标
    V_TOI_RANK_RANK_2 = 2, // 协同机制导中目标
} TOI_RANK;

// 标识符: transitmit_type
// 名  称: 传输方式_3bit
// 字  数: 3
// 说  明: 载荷默认填0, AIMP根据实时传输模式填1或2（例如：用于地面图像实时显示或对于断网后指定图像的传输）
typedef enum {
    V_TRANSITMIT_TYPE_NA              = 0, //
    V_TRANSITMIT_TYPE_GND_READBACK    = 1, // 地面回读
    V_TRANSITMIT_TYPE_TRANSIT_IN_TIME = 2, // 实时传输
    V_TRANSITMIT_TYPE_TRANSIT_CHOOSE  = 3, // 检索传输
} TRANSITMIT_TYPE;

// 标识符: translate_state
// 名  称: 传输状态
// 字  数: 8
// 说  明:
typedef enum {
    V_TRANSLATE_STATE_NA              = 0,  // 无意义
    V_TRANSLATE_STATE_TRANSFERABLE    = 1,  // 等待传输
    V_TRANSLATE_STATE_TRANSFERRING    = 2,  // 正在传输
    V_TRANSLATE_STATE_TRANSFERRED     = 3,  // 传输成功
    V_TRANSLATE_STATE_FAILTRANSFERRED = 4,  // 传输失败
    V_TRANSLATE_STATE_NONTRANSFERABLE = 5,  // 限制传输
    V_TRANSLATE_STATE_MD5CHECKERROR   = 6,  // MD5校验失败
    V_TRANSLATE_STATE_NOTTRANSFERRED  = 10, // 未传输
} TRANSLATE_STATE;

// 标识符: Transom_mist_eliminate_state
// 名  称: 光窗去雾状态
// 字  数: 8
// 说  明:
typedef enum {
    V_TRANSOM_MIST_ELIMINATE_STATE_NA  = 0, //
    V_TRANSOM_MIST_ELIMINATE_STATE_ON  = 1, // 开
    V_TRANSOM_MIST_ELIMINATE_STATE_OFF = 2, // 关
} TRANSOM_MIST_ELIMINATE_STATE;

// 标识符: troop_tgt_property
// 名  称: 群目标特征
// 字  数: 8
// 说  明:
typedef enum {
    V_TROOP_TGT_PROPERTY_NA     = 0, //
    V_TROOP_TGT_PROPERTY_UNKOWN = 1, // 未知
    V_TROOP_TGT_PROPERTY_SINGLE = 2, // 单目标
    V_TROOP_TGT_PROPERTY_TROOP  = 3, // 群目标
} TROOP_TGT_PROPERTY;

// 标识符: true_virtual_flag
// 名  称: 真实虚拟目标标识
// 字  数: 8
// 说  明:
typedef enum {
    V_TRUE_VIRTUAL_FLAG_NA      = 0, //
    V_TRUE_VIRTUAL_FLAG_TRUE    = 1, // 真实目标
    V_TRUE_VIRTUAL_FLAG_VIRTUAL = 2, // 虚拟目标
} TRUE_VIRTUAL_FLAG;

// 标识符: unique_act_req_IRS
// 名  称: 特殊活动请求_IRST
// 字  数: 8
// 说  明:
typedef enum {
    V_UNIQUE_ACT_REQ_IRS_NA                    = 0,  //
    V_UNIQUE_ACT_REQ_IRS_IR_STATE_SET          = 1,  // 修改光电工作状态———按状态转换图
    V_UNIQUE_ACT_REQ_IRS_IMAGE_MODE_CHG        = 2,  // 成像模式修改——收藏、待机、拍照可接收，只有准备中、拍照有动作，其他保存参数
    V_UNIQUE_ACT_REQ_IRS_IRST_WIDE_IMAGE_CNTL  = 3,  // 修改广域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    V_UNIQUE_ACT_REQ_IRS_IRST_AREA_IMAGE_CNTL  = 4,  // 修改区域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    V_UNIQUE_ACT_REQ_IRS_IRST_WIDE_MONI_CNTL   = 5,  // 修改区域监视参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    V_UNIQUE_ACT_REQ_IRS_LIGHT_IMA_PARS_UPDATE = 6,  // 可见光成像参数修改——收藏、待机、拍照，直接转发
    V_UNIQUE_ACT_REQ_IRS_INFRA_IMA_PARS_UPDATE = 7,  // 红外成像参数修改——收藏、待机、拍照，直接转发
    V_UNIQUE_ACT_REQ_IRS_SENSOR_SET            = 8,  // 成像传感器控制——所有模式
    V_UNIQUE_ACT_REQ_IRS_SCENE_TYPE_CHANGE     = 10, // 修改场景类型——只有收藏可修改场景
    V_UNIQUE_ACT_REQ_IRS_WINDOW_FOG_REMOVE     = 12, // 光窗去雾——收藏状态
    V_UNIQUE_ACT_REQ_IRS_ENTER_TGT_TRACK       = 27, // 进入图像跟踪——只有拍照、区域监视
    V_UNIQUE_ACT_REQ_IRS_EXIT_TGT_TRACK        = 28, // 退出图像跟踪——只有拍照、区域监视
    V_UNIQUE_ACT_REQ_IRS_IMU_ALIGN             = 40, // IMU对准
    V_UNIQUE_ACT_REQ_IRS_INFRA_CORRECT         = 41, // 红外校正——只有待机
    V_UNIQUE_ACT_REQ_IRS_FROZEN                = 42, // 冻结——拍照、区域监视
    V_UNIQUE_ACT_REQ_IRS_VIDEO_BAND_SET        = 43, // 视频带宽设置——所有模式

    V_UNIQUE_ACT_REQ_IRS_BIG_VIEW   = 101, // 大视场，短焦
    V_UNIQUE_ACT_REQ_IRS_SMALL_VIEW = 102, // 小视场，长焦

    V_UNIQUE_ACT_REQ_IRS_IRST_MODE_UPDATA = 21, // 修改IRST工作模式——现在没有
    V_UNIQUE_ACT_REQ_IRS_POLAR_SET        = 22, // 黑白热设置？——没有改指令
    V_UNIQUE_ACT_REQ_IRS_SENSOR_PLAN      = 25, // 传感器计划（确认）
    V_UNIQUE_ACT_REQ_IRS_CONTRAST_INCRESE = 26, // 进入提示搜索
    V_UNIQUE_ACT_REQ_IRS_TGT_CUE_ON       = 35, // 提示搜索开
    V_UNIQUE_ACT_REQ_IRS_TGT_CUE_OFF      = 36, // 提示搜索关
    V_UNIQUE_ACT_REQ_IRS_DESIG_NTS        = 33, // 确定NTS目标——暂时不管
    V_UNIQUE_ACT_REQ_IRS_CAL_DATA_REQ     = 34, // 校准参数请求
    V_UNIQUE_ACT_REQ_IRS_SENSOR_PLAN_SSV  = 51, // 传感器计划_系统扫描区
    V_UNIQUE_ACT_REQ_IRS_SENSOR_PLAN_IRST = 52, // 传感器计划_光雷计划
} UNIQUE_ACT_REQ_IRS;

// 标识符: user_type
// 名  称: 用户类型
// 字  数: 8
// 说  明:
typedef enum {
    V_USER_TYPE_NA              = 0,  //
    V_USER_TYPE_SYSTEM_USER     = 1,  // 系统用户
    V_USER_TYPE_AIRCREW_USER    = 2,  // 空勤用户
    V_USER_TYPE_GROUNDCREW_USER = 3,  // 地勤用户
    V_USER_TYPE_SYS_SUPER_USER  = 11, // 系统超级用户
    V_USER_TYPE_AG_SUPER_USER   = 12, // 空地勤超级用户
} USER_TYPE;

// 标识符: valid_AC_weight_VMS
// 名  称: 有效性_飞机重量_VMS
// 字  数: 8
// 说  明:
typedef enum {
    V_VALID_AC_WEIGHT_VMS_INVALID = 0, // 无效
    V_VALID_AC_WEIGHT_VMS_VALID   = 1, // 有效
    V_VALID_AC_WEIGHT_VMS_DEG     = 2, // 降级
} VALID_AC_WEIGHT_VMS;

// 标识符: velocity_precision
// 名  称: 速度精度
// 字  数: 8
// 说  明: 载机对目标的测速误差小于等于25m/s时，速度精度为精
//         载机对目标的测速误差小于等于50m/s且大于25m/s时，速度精度为粗
//         载机对目标的测速误差小于等于150m/s且大于50m/s时，速度精度为极粗
//         载机对目标的测速误差大于150m/s时，速度精度为无效
typedef enum {
    V_VELOCITY_PRECISION_NA          = 0, //
    V_VELOCITY_PRECISION_PRECISE     = 1, // 精
    V_VELOCITY_PRECISION_COARSE      = 2, // 粗
    V_VELOCITY_PRECISION_VERY_COARSE = 3, // 极粗
    V_VELOCITY_PRECISION_INVALID     = 4, // 无效
} VELOCITY_PRECISION;

// 标识符: version_type
// 名  称: 版本类型
// 字  数: 8
// 说  明: 描述各子系统上报的软件版本的类型
typedef enum {
    V_VERSION_TYPE_NA       = 0,  // 未知
    V_VERSION_TYPE_APP      = 1,  // 应用程序
    V_VERSION_TYPE_BOOT     = 2,  // 驱动程序
    V_VERSION_TYPE_LAB      = 3,  // 数据库
    V_VERSION_TYPE_FPGA     = 4,  //
    V_VERSION_TYPE_BASELINE = 5,  // 基线
    V_VERSION_TYPE_OTHER    = 99, // 其他
} VERSION_TYPE;

// 标识符: video_polar
// 名  称: 视频极化
// 字  数: 8
// 说  明:
typedef enum {
    V_VIDEO_POLAR_NA   = 0, //
    V_VIDEO_POLAR_BHOT = 1, // 黑热
    V_VIDEO_POLAR_WHOT = 2, // 白热
} VIDEO_POLAR;

// 标识符: video_polar_CHG
// 名  称: 视频极化修改标识
// 字  数: 1
// 说  明:
typedef enum {
    V_VIDEO_POLAR_CHG_NO  = 0, // 不修改
    V_VIDEO_POLAR_CHG_YES = 1, // 修改
} VIDEO_POLAR_CHG;

// 标识符: VMS_AC_ID
// 名  称: VMS_飞机ID
// 字  数: 4
// 说  明: 0 歼-20飞机01状态01-05架
//         1 歼-20飞机01状态06架起
//         2 歼-20飞机02状态，不装航炮
//         3 歼-20飞机02状态，装航炮
//         4 歼-20双座机，配装涡扇-10C
//         5 歼-20双座机，配装涡扇-15
//         6 歼-20A飞机，配装涡扇-10C
//         7 歼-20A飞机，配装涡扇-15
typedef enum {
    V_VMS_AC_ID_INVALID   = 0, // 无效
    V_VMS_AC_ID_STA01     = 1, // 01状态无航炮
    V_VMS_AC_ID_STA02     = 2, // 02状态无航炮
    V_VMS_AC_ID_STA02_GUN = 3, // 02状态有航炮
    V_VMS_AC_ID_ISC_WS10C = 4, // 双座-涡扇10C发动机
    V_VMS_AC_ID_ISC_WS15  = 5, // 双座-涡扇15发动机
    V_VMS_AC_ID_A_WS10C   = 6, // 20A-涡扇10C发动机
    V_VMS_AC_ID_A_WS15    = 7, // 20A-涡扇15发动机
} VMS_AC_ID;

// 标识符: VMS_AP_Alt_Display
// 名  称: VMS_当前高度保持值显示
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_ALT_DISPLAY_NA      = 0, // 不显示
    V_VMS_AP_ALT_DISPLAY_DISPLAY = 1, // 显示
} VMS_AP_ALT_DISPLAY;

// 标识符: VMS_AP_CSS
// 名  称: VMS_自动驾驶悬挂
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_CSS_NA  = 0, // 无意义
    V_VMS_AP_CSS_CSS = 1, // 悬挂
} VMS_AP_CSS;

// 标识符: VMS_AP_DEGRADED
// 名  称: VMS_自动驾驶降级
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_DEGRADED_NA       = 0, //
    V_VMS_AP_DEGRADED_DEGRADED = 1, // 降级
} VMS_AP_DEGRADED;

// 标识符: VMS_AP_ENGAGE
// 名  称: VMS_自动驾驶接通
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_ENGAGE_NA     = 0, // 无意义
    V_VMS_AP_ENGAGE_ENGAGE = 1, // 接通
} VMS_AP_ENGAGE;

// 标识符: VMS_AP_Fail_CUT
// 名  称: VMS_自动驾驶故障切除
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_FAIL_CUT_NA       = 0, // 无意义
    V_VMS_AP_FAIL_CUT_FAIL_CUT = 1, // 故障切除
} VMS_AP_FAIL_CUT;

// 标识符: VMS_AP_State_lat
// 名  称: VMS_自动驾驶横向状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_AP_STATE_LAT_NA          = 0, //
    V_VMS_AP_STATE_LAT_ATT         = 1, //
    V_VMS_AP_STATE_LAT_TRACK       = 2, //
    V_VMS_AP_STATE_LAT_TACAN       = 3, //
    V_VMS_AP_STATE_LAT_LOC_FAF     = 4, //
    V_VMS_AP_STATE_LAT_LOC_RWY_SCA = 5, //
    V_VMS_AP_STATE_LAT_LOC_RWY_MLS = 6, //
    V_VMS_AP_STATE_LAT_ARMED_TRACK = 8, //
    V_VMS_AP_STATE_LAT_AUTONAV     = 9, //
} VMS_AP_STATE_LAT;

// 标识符: VMS_AP_State_long
// 名  称: VMS_自动驾驶纵向状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_AP_STATE_LONG_NA           = 0, // 无意义
    V_VMS_AP_STATE_LONG_ATT          = 1, // 姿态保持
    V_VMS_AP_STATE_LONG_ALT          = 2, // 高度保持
    V_VMS_AP_STATE_LONG_GLS          = 3, // 下滑道保持
    V_VMS_AP_STATE_LONG_ARMED_ALT    = 4, // ARMED高度保持
    V_VMS_AP_STATE_LONG_ARMED_GLS    = 5, // ARMED下滑道保持
    V_VMS_AP_STATE_LONG_PREGLS       = 6, // 预备下滑道保持
    V_VMS_AP_STATE_LONG_ARMED_PREGLS = 7, // ARMED预备下滑道保持
    V_VMS_AP_STATE_LONG_TF           = 8, // 地形跟随
    V_VMS_AP_STATE_LONG_ARMED_TF     = 9, // 预备地形跟随
} VMS_AP_STATE_LONG;

// 标识符: VMS_AP_Trk_Display
// 名  称: VMS_当前航迹保持值显示
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AP_TRK_DISPLAY_NA      = 0, // 不显示
    V_VMS_AP_TRK_DISPLAY_DISPLAY = 1, // 显示
} VMS_AP_TRK_DISPLAY;

// 标识符: VMS_apParaDataBlock_Valid
// 名  称: 自动驾驶参数数据包有效性
// 字  数: 8
// 说  明: 该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中自动驾驶高度、航迹保持值参数的总有效性。
typedef enum {
    V_VMS_APPARADATABLOCK_VALID_INVALID = 0, //
    V_VMS_APPARADATABLOCK_VALID_VALID   = 1, //
} VMS_APPARADATABLOCK_VALID;

// 标识符: VMS_apStateDataBlock_Valid
// 名  称: 自动驾驶状态数据包有效性
// 字  数: 8
// 说  明: 该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中"VMS_自动驾驶状态"参数的总有效性。
typedef enum {
    V_VMS_APSTATEDATABLOCK_VALID_INVALID = 0, //
    V_VMS_APSTATEDATABLOCK_VALID_VALID   = 1, //
} VMS_APSTATEDATABLOCK_VALID;

// 标识符: VMS_AT_CSS
// 名  称: VMS_自动油门悬挂
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AT_CSS_NA  = 0, // 无意义
    V_VMS_AT_CSS_CSS = 1, // 悬挂
} VMS_AT_CSS;

// 标识符: VMS_AT_DEGRADED
// 名  称: VMS_自动油门降级
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AT_DEGRADED_NA       = 0, //
    V_VMS_AT_DEGRADED_DEGRADED = 1, // 降级
} VMS_AT_DEGRADED;

// 标识符: VMS_AT_Display
// 名  称: VMS_当前自动油门值显示
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AT_DISPLAY_NA      = 0, // 不显示
    V_VMS_AT_DISPLAY_DISPLAY = 1, // 显示
} VMS_AT_DISPLAY;

// 标识符: VMS_AT_ECO
// 名  称: VMS_当前自动油门省油标志
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_AT_ECO_ACC = 0, // 精确
    V_VMS_AT_ECO_ECO = 1, // 省油
} VMS_AT_ECO;

// 标识符: VMS_AT_State
// 名  称: VMS_自动油门接通状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_AT_STATE_NA  = 0, // 无意义
    V_VMS_AT_STATE_CAS = 1, // 表速保持
    V_VMS_AT_STATE_MA  = 2, // 马赫保持
    V_VMS_AT_STATE_TOT = 3, // 定时到达
} VMS_AT_STATE;

// 标识符: VMS_control_manage_mode
// 名  称: 飞管系统控制管理模式
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_CONTROL_MANAGE_MODE_NOT_CMM = 0, // 非控制管理模式
    V_VMS_CONTROL_MANAGE_MODE_IN_CMM  = 1, // 控制管理模式
} VMS_CONTROL_MANAGE_MODE;

// 标识符: VMS_Cur_fly_status
// 名  称: VMS_当前所处飞行阶段
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_CUR_FLY_STATUS_NA  = 0, //
    V_VMS_CUR_FLY_STATUS_NAV = 1, // 导航
    V_VMS_CUR_FLY_STATUS_FAF = 2, // 进场
    V_VMS_CUR_FLY_STATUS_RWY = 3, // 着陆
} VMS_CUR_FLY_STATUS;

// 标识符: VMS_CY_State
// 名  称: VMS_冲压状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_CY_STATE_NA    = 0, // 无意义
    V_VMS_CY_STATE_OPEN  = 1, // 全开
    V_VMS_CY_STATE_CLOSE = 2, // 全关
    V_VMS_CY_STATE_WB    = 3, // 未到位
} VMS_CY_STATE;

// 标识符: VMS_data_destroy_signal
// 名  称: VMS_销密记录信号
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_DATA_DESTROY_SIGNAL_FALSE = 0, // 不销密
    V_VMS_DATA_DESTROY_SIGNAL_TRUE  = 1, // 销密
} VMS_DATA_DESTROY_SIGNAL;

// 标识符: VMS_elecPower_DCDC1
// 名  称: VMS_供电_DCDC1
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_DCDC1_NA   = 0, // NA
    V_VMS_ELECPOWER_DCDC1_NOR  = 1, // 正常
    V_VMS_ELECPOWER_DCDC1_FAIL = 2, // 故障
} VMS_ELECPOWER_DCDC1;

// 标识符: VMS_elecPower_DCDC2
// 名  称: VMS_供电_DCDC2
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_DCDC2_NA   = 0, // NA
    V_VMS_ELECPOWER_DCDC2_NOR  = 1, // 正常
    V_VMS_ELECPOWER_DCDC2_FAIL = 2, // 故障
} VMS_ELECPOWER_DCDC2;

// 标识符: VMS_elecPower_DCDC3
// 名  称: VMS_供电_DCDC3
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_DCDC3_NA   = 0, // NA
    V_VMS_ELECPOWER_DCDC3_NOR  = 1, // 正常
    V_VMS_ELECPOWER_DCDC3_FAIL = 2, // 故障
} VMS_ELECPOWER_DCDC3;

// 标识符: VMS_elecPower_DCDC4
// 名  称: VMS_供电_DCDC4
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_DCDC4_NA   = 0, // NA
    V_VMS_ELECPOWER_DCDC4_NOR  = 1, // 正常
    V_VMS_ELECPOWER_DCDC4_FAIL = 2, // 故障
} VMS_ELECPOWER_DCDC4;

// 标识符: VMS_elecPower_GDS
// 名  称: VMS_供电_地面电源状态
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_GDS_NA      = 0, // NA
    V_VMS_ELECPOWER_GDS_VALID   = 1, // 工作
    V_VMS_ELECPOWER_GDS_INVALID = 2, // 不工作
} VMS_ELECPOWER_GDS;

// 标识符: VMS_elecPower_GenAsiss
// 名  称: VMS_供电_直发状态_辅
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_GENASISS_NA      = 0, // NA
    V_VMS_ELECPOWER_GENASISS_VALID   = 1, // 工作
    V_VMS_ELECPOWER_GENASISS_INVALID = 2, // 不工作
} VMS_ELECPOWER_GENASISS;

// 标识符: VMS_elecPower_GenL
// 名  称: VMS_供电_直发状态_左
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_GENL_NA      = 0, // NA
    V_VMS_ELECPOWER_GENL_VALID   = 1, // 工作
    V_VMS_ELECPOWER_GENL_INVALID = 2, // 不工作
} VMS_ELECPOWER_GENL;

// 标识符: VMS_elecPower_GenR
// 名  称: VMS_供电_直发状态_右
// 字  数: 2
// 说  明:
typedef enum {
    V_VMS_ELECPOWER_GENR_NA      = 0, // NA
    V_VMS_ELECPOWER_GENR_VALID   = 1, // 工作
    V_VMS_ELECPOWER_GENR_INVALID = 2, // 不工作
} VMS_ELECPOWER_GENR;

// 标识符: VMS_fcskeyDataBlock_Valid
// 名  称: 飞控关键参数数据包有效性
// 字  数: 8
// 说  明: 该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_飞控关键参数"中除"VMS_自动驾驶状态"及自动驾驶高度、航迹保持值参数以外的所有参数的总有效性。
typedef enum {
    V_VMS_FCSKEYDATABLOCK_VALID_INVALID = 0, //
    V_VMS_FCSKEYDATABLOCK_VALID_VALID   = 1, //
} VMS_FCSKEYDATABLOCK_VALID;

// 标识符: VMS_LC_State
// 名  称: VMS_液冷状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LC_STATE_NA    = 0, // 无意义
    V_VMS_LC_STATE_NOR   = 1, // 正常
    V_VMS_LC_STATE_START = 2, // 启动中
    V_VMS_LC_STATE_DEG   = 3, // 降级
    V_VMS_LC_STATE_CLOSE = 4, // 关闭
} VMS_LC_STATE;

// 标识符: VMS_LDCstate
// 名  称: VMS_液冷供液状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LDCSTATE_INVALID  = 0, // 无效
    V_VMS_LDCSTATE_EXIST    = 1, // 有供液
    V_VMS_LDCSTATE_NO_EXIST = 2, // 无供液
} VMS_LDCSTATE;

// 标识符: VMS_LEng_Afterburn
// 名  称: VMS_左发加力
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_LENG_AFTERBURN_OFF = 0, // 非加力
    V_VMS_LENG_AFTERBURN_ON  = 1, // 加力
} VMS_LENG_AFTERBURN;

// 标识符: VMS_LEng_Mode
// 名  称: VMS_左发_工作模式
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LENG_MODE_NA    = 0, // 无效
    V_VMS_LENG_MODE_TRAIN = 1, // 训练
    V_VMS_LENG_MODE_CMBT  = 2, // 战斗
    V_VMS_LENG_MODE_ZT    = 3, // 增推
    V_VMS_LENG_MODE_CMBTA = 4, // 战斗A
    V_VMS_LENG_MODE_ZTA   = 5, // 增推A
} VMS_LENG_MODE;

// 标识符: VMS_LGState_H
// 名  称: VMS_起落架状态_前
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LGSTATE_H_NA = 0, // 未知
    V_VMS_LGSTATE_H_DN = 1, // 放下
    V_VMS_LGSTATE_H_UP = 2, // 收起
} VMS_LGSTATE_H;

// 标识符: VMS_LGState_L
// 名  称: VMS_起落架状态_左
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LGSTATE_L_NA = 0, // 未知
    V_VMS_LGSTATE_L_DN = 1, // 放下
    V_VMS_LGSTATE_L_UP = 2, // 收起
} VMS_LGSTATE_L;

// 标识符: VMS_LGState_M
// 名  称: VMS_起落架系统_主
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LGSTATE_M_NA = 0, // 未知
    V_VMS_LGSTATE_M_DN = 1, // 放下
    V_VMS_LGSTATE_M_UP = 2, // 收起
} VMS_LGSTATE_M;

// 标识符: VMS_LGState_R
// 名  称: VMS_起落架状态_右
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_LGSTATE_R_NA = 0, // 未知
    V_VMS_LGSTATE_R_DN = 1, // 放下
    V_VMS_LGSTATE_R_UP = 2, // 收起
} VMS_LGSTATE_R;

// 标识符: VMS_PULLUP_CSS
// 名  称: VMS_防撞拉起悬挂状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_PULLUP_CSS_NA  = 0, // 无意义
    V_VMS_PULLUP_CSS_CSS = 1, // 悬挂
} VMS_PULLUP_CSS;

// 标识符: VMS_PULLUP_DEGRADED
// 名  称: VMS_防撞拉起降级状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_PULLUP_DEGRADED_NA       = 0, //
    V_VMS_PULLUP_DEGRADED_DEGRADED = 1, // 降级
} VMS_PULLUP_DEGRADED;

// 标识符: VMS_PULLUP_ENGAGE
// 名  称: VMS_防撞拉起接通状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_PULLUP_ENGAGE_NA     = 0, // 无意义
    V_VMS_PULLUP_ENGAGE_ENGAGE = 1, // 接通
} VMS_PULLUP_ENGAGE;

// 标识符: VMS_PULLUP_FAULT
// 名  称: VMS_防撞拉起故障状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_PULLUP_FAULT_NA    = 0, //
    V_VMS_PULLUP_FAULT_FAULT = 1, // 故障
} VMS_PULLUP_FAULT;

// 标识符: VMS_REng_Afterburn
// 名  称: VMS_右发加力
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_RENG_AFTERBURN_OFF = 0, // 非加力
    V_VMS_RENG_AFTERBURN_ON  = 1, // 加力
} VMS_RENG_AFTERBURN;

// 标识符: VMS_REng_Mode
// 名  称: VMS_右发_工作模式
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_RENG_MODE_NA    = 0, // 无效
    V_VMS_RENG_MODE_TRAIN = 1, // 训练
    V_VMS_RENG_MODE_CMBT  = 2, // 战斗
    V_VMS_RENG_MODE_ZT    = 3, // 增推
    V_VMS_RENG_MODE_CMBTA = 4, // 战斗A
    V_VMS_RENG_MODE_ZTA   = 5, // 增推A
} VMS_RENG_MODE;

// 标识符: VMS_Sensors_of_LOC
// 名  称: VMS_进场着陆阶段所选传感器
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_SENSORS_OF_LOC_NA    = 0, //
    V_VMS_SENSORS_OF_LOC_MLS   = 1, // 微波
    V_VMS_SENSORS_OF_LOC_ILS   = 2, // 仪表
    V_VMS_SENSORS_OF_LOC_TACAN = 3, // 塔康
    V_VMS_SENSORS_OF_LOC_SCA   = 4, // 自主
} VMS_SENSORS_OF_LOC;

// 标识符: VMS_TF_ALT_twinkle
// 名  称: VMS_地形跟随相对高度闪烁标识
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_TF_ALT_TWINKLE_NO  = 0, // 不闪烁
    V_VMS_TF_ALT_TWINKLE_YES = 1, // 闪烁
} VMS_TF_ALT_TWINKLE;

// 标识符: VMS_TSSB_B
// 名  称: VMS_弹射手柄启动_后
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_TSSB_B_NA  = 0, // 无意义
    V_VMS_TSSB_B_OFF = 1, // 未启动
    V_VMS_TSSB_B_ON  = 2, // 启动
} VMS_TSSB_B;

// 标识符: VMS_TSSB_F
// 名  称: VMS_弹射手柄启动_前
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_TSSB_F_NA  = 0, // 无意义
    V_VMS_TSSB_F_OFF = 1, // 未启动
    V_VMS_TSSB_F_ON  = 2, // 启动
} VMS_TSSB_F;

// 标识符: VMS_usimkeyDataBlock_Valid
// 名  称: 机电关键参数数据包有效性
// 字  数: 8
// 说  明: 该信号表示了转发飞管数据的主题"AC_Data_FCS_USIM"中的信号组"VMS_机电关键参数_发动机"、"VMS_机电关键参数_燃油"、"VMS_机电关键参数_供电"、"VMS_机电关键参数_机电综合"中所有参数的总有效性。
typedef enum {
    V_VMS_USIMKEYDATABLOCK_VALID_INVALID = 0, //
    V_VMS_USIMKEYDATABLOCK_VALID_VALID   = 1, //
} VMS_USIMKEYDATABLOCK_VALID;

// 标识符: VMS_valid_fuel_use
// 名  称: VMS_有效性_余油_可用油量
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_VALID_FUEL_USE_INVALID = 0, // 无效
    V_VMS_VALID_FUEL_USE_VALID   = 1, // 有效性
    V_VMS_VALID_FUEL_USE_DEG     = 2, // 精度降级
} VMS_VALID_FUEL_USE;

// 标识符: VMS_valid_LDCTemp
// 名  称: VMS_有效性_液冷温度
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_VALID_LDCTEMP_INVALID = 0, // 无效
    V_VMS_VALID_LDCTEMP_NOR     = 1, // 正常
    V_VMS_VALID_LDCTEMP_WARN    = 2, // 偏热
    V_VMS_VALID_LDCTEMP_ALERT   = 3, // 超温
} VMS_VALID_LDCTEMP;

// 标识符: VMS_valid_LEng_N2
// 名  称: VMS_有效性_左发_N2
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_LENG_N2_INVALID = 0, // 无效
    V_VMS_VALID_LENG_N2_VALID   = 1, // 有效
} VMS_VALID_LENG_N2;

// 标识符: VMS_valid_LEng_T1
// 名  称: VMS_有效性_左发_T1
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_LENG_T1_INVALID = 0, // 无效
    V_VMS_VALID_LENG_T1_VALID   = 1, // 有效
} VMS_VALID_LENG_T1;

// 标识符: VMS_valid_LEng_T4
// 名  称: VMS_有效性_左发_T4
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_LENG_T4_INVALID = 0, // 无效
    V_VMS_VALID_LENG_T4_VALID   = 1, // 有效
} VMS_VALID_LENG_T4;

// 标识符: VMS_valid_LEng_Thor
// 名  称: VMS_有效性_左发油门角度
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_LENG_THOR_INVALID = 0, // 无效
    V_VMS_VALID_LENG_THOR_VALID   = 1, // 有效
} VMS_VALID_LENG_THOR;

// 标识符: VMS_valid_REng_N2
// 名  称: VMS_有效性_右发_N2
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_RENG_N2_INVALID = 0, // 无效
    V_VMS_VALID_RENG_N2_VALID   = 1, // 有效
} VMS_VALID_RENG_N2;

// 标识符: VMS_valid_REng_T1
// 名  称: VMS_有效性_右发_T1
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_RENG_T1_INVALID = 0, // 无效
    V_VMS_VALID_RENG_T1_VALID   = 1, // 有效
} VMS_VALID_RENG_T1;

// 标识符: VMS_valid_REng_T4
// 名  称: VMS_有效性_右发_T4
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_RENG_T4_INVALID = 0, // 无效
    V_VMS_VALID_RENG_T4_VALID   = 1, // 有效
} VMS_VALID_RENG_T4;

// 标识符: VMS_valid_REng_Thor
// 名  称: VMS_有效性_右发油门角度
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_VALID_RENG_THOR_INVALID = 0, // 无效
    V_VMS_VALID_RENG_THOR_VALID   = 1, // 有效
} VMS_VALID_RENG_THOR;

// 标识符: VMS_warning_LEng_AfterburnOFF
// 名  称: VMS_左发加力未接通
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_WARNING_LENG_AFTERBURNOFF_NORMAL  = 0, // 正常
    V_VMS_WARNING_LENG_AFTERBURNOFF_ANOMALY = 1, // 故障
} VMS_WARNING_LENG_AFTERBURNOFF;

// 标识符: VMS_warning_REng_AfterburnOFF
// 名  称: VMS_右发加力未接通
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS_WARNING_RENG_AFTERBURNOFF_NORMAL  = 0, // 正常
    V_VMS_WARNING_RENG_AFTERBURNOFF_ANOMALY = 1, // 故障
} VMS_WARNING_RENG_AFTERBURNOFF;

// 标识符: VMS_WC_State
// 名  称: VMS_风冷状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_WC_STATE_NA    = 0, // 无意义
    V_VMS_WC_STATE_NOR   = 1, // 正常
    V_VMS_WC_STATE_CLOSE = 2, // 关闭
    V_VMS_WC_STATE_RAM   = 3, // 冲压
} VMS_WC_STATE;

// 标识符: VMS_WOW_Front
// 名  称: VMS_轮载状态_前
// 字  数: 1
// 说  明: 前轮载状态
typedef enum {
    V_VMS_WOW_FRONT_AIR = 0, // 空中
    V_VMS_WOW_FRONT_GND = 1, // 地面
} VMS_WOW_FRONT;

// 标识符: VMS_WOW_Left
// 名  称: VMS_轮载状态_左
// 字  数: 1
// 说  明: 左轮载状态
typedef enum {
    V_VMS_WOW_LEFT_AIR = 0, // 空中
    V_VMS_WOW_LEFT_GND = 1, // 地面
} VMS_WOW_LEFT;

// 标识符: VMS_WOW_Main
// 名  称: VMS_轮载状态_主
// 字  数: 1
// 说  明: 主轮载状态
typedef enum {
    V_VMS_WOW_MAIN_AIR = 0, // 空中
    V_VMS_WOW_MAIN_GND = 1, // 地面
} VMS_WOW_MAIN;

// 标识符: VMS_WOW_Right
// 名  称: VMS_轮载状态_右
// 字  数: 1
// 说  明: 右轮载状态
typedef enum {
    V_VMS_WOW_RIGHT_AIR = 0, // 空中
    V_VMS_WOW_RIGHT_GND = 1, // 地面
} VMS_WOW_RIGHT;

// 标识符: VMS_ZYLJ_B
// 名  称: VMS_座椅离机_后
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_ZYLJ_B_NA    = 0, // 无意义
    V_VMS_ZYLJ_B_NAR   = 1, // 正常
    V_VMS_ZYLJ_B_LEAVE = 2, // 离机
} VMS_ZYLJ_B;

// 标识符: VMS_ZYLJ_F
// 名  称: VMS_座椅离机_前
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS_ZYLJ_F_NA    = 0, // 无意义
    V_VMS_ZYLJ_F_NAR   = 1, // 正常
    V_VMS_ZYLJ_F_LEAVE = 2, // 离机
} VMS_ZYLJ_F;

// 标识符: VMS1394_AC_CFG_ID
// 名  称: VMS1394_飞机构型识别ID
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_AC_CFG_ID_INVALID = 0, // 无效
    V_VMS1394_AC_CFG_ID_HA      = 4, // HA飞机
    V_VMS1394_AC_CFG_ID_SE      = 5, // SE飞机
    V_VMS1394_AC_CFG_ID_XA_603  = 6, // 603所使用
    V_VMS1394_AC_CFG_ID_SY_601  = 7, // 20A-涡扇15发动机
} VMS1394_AC_CFG_ID;

// 标识符: VMS1394_AC_ID
// 名  称: VMS1394_飞机ID
// 字  数: 5
// 说  明: 主机所自行定义使用，目前预留置0
typedef enum {
    V_VMS1394_AC_ID_INVALID = 0, // 无效
} VMS1394_AC_ID;

// 标识符: VMS1394_AC_Type_ID
// 名  称: VMS1394_飞机构型
// 字  数: 16
// 说  明:
typedef enum {
    V_VMS1394_AC_TYPE_ID_NA            = 0, //
    V_VMS1394_AC_TYPE_ID_RECON         = 1, // 侦察
    V_VMS1394_AC_TYPE_ID_EARLY_WARNING = 2, // 预警
} VMS1394_AC_TYPE_ID;

// 标识符: VMS1394_BUS_ID
// 名  称: VMS1394_BUS_ID
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_BUS_ID_BUS1 = 1, // 总线1
    V_VMS1394_BUS_ID_BUS2 = 2, // 总线2
    V_VMS1394_BUS_ID_BUS3 = 4, // 总线3
} VMS1394_BUS_ID;

// 标识符: VMS1394_CHMAINT_MODE
// 名  称: VMS1394_单通道维护模式
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CHMAINT_MODE_INVALID = 0, // 无效
    V_VMS1394_CHMAINT_MODE_VALID   = 1, // 有效
} VMS1394_CHMAINT_MODE;

// 标识符: VMS1394_CPU1_LCV
// 名  称: VMS1394_有效性_本通道CPU1
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CPU1_LCV_INVALID = 0, // 无效
    V_VMS1394_CPU1_LCV_VALID   = 1, // 有效
} VMS1394_CPU1_LCV;

// 标识符: VMS1394_CPU2_LCV
// 名  称: VMS1394_有效性_本通道CPU2
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CPU2_LCV_INVALID = 0, // 无效
    V_VMS1394_CPU2_LCV_VALID   = 1, // 有效
} VMS1394_CPU2_LCV;

// 标识符: VMS1394_CPU2_MON
// 名  称: VMS1394_通道内监控_CPU2
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CPU2_MON_INVALID = 0, // 无效
    V_VMS1394_CPU2_MON_VALID   = 1, // 有效
} VMS1394_CPU2_MON;

// 标识符: VMS1394_CPU3_LCV
// 名  称: VMS1394_有效性_本通道CPU3
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CPU3_LCV_INVALID = 0, // 无效
    V_VMS1394_CPU3_LCV_VALID   = 1, // 有效
} VMS1394_CPU3_LCV;

// 标识符: VMS1394_CPU4_LCV
// 名  称: VMS1394_有效性_本通道CPU4
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CPU4_LCV_INVALID = 0, // 无效
    V_VMS1394_CPU4_LCV_VALID   = 1, // 有效
} VMS1394_CPU4_LCV;

// 标识符: VMS1394_CTRL_MODE
// 名  称: VMS1394_控制管理模式
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_CTRL_MODE_INVALID = 0, // 无效
    V_VMS1394_CTRL_MODE_VALID   = 1, // 有效
} VMS1394_CTRL_MODE;

// 标识符: VMS1394_DIF_TEST
// 名  称: VMS1394_DIF测试位
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_DIF_TEST_STOP = 0, // DIF停止
    V_VMS1394_DIF_TEST_RUN  = 1, // 正常运行
} VMS1394_DIF_TEST;

// 标识符: VMS1394_fly_status
// 名  称: VMS1394_飞行阶段
// 字  数: 16
// 说  明:
typedef enum {
    V_VMS1394_FLY_STATUS_PARK_STANDBY         = 0,  // 驻停待命
    V_VMS1394_FLY_STATUS_TAKEOFF_ROLL         = 1,  // 起飞滑跑
    V_VMS1394_FLY_STATUS_TAKEOFF_OBSTACLE     = 2,  // 起飞越障
    V_VMS1394_FLY_STATUS_INITIAL_CLIMB        = 3,  // 初始爬升
    V_VMS1394_FLY_STATUS_MISSION_VOYAGE       = 4,  // 任务航行
    V_VMS1394_FLY_STATUS_PROCEDURE_APPROACH   = 5,  // 程序进场
    V_VMS1394_FLY_STATUS_APPROACH_POSITIONING = 6,  // 进近定位
    V_VMS1394_FLY_STATUS_FINAL_GLIDE          = 7,  // 五边下滑
    V_VMS1394_FLY_STATUS_LANDING_FLAREOUT     = 8,  // 着陆拉平
    V_VMS1394_FLY_STATUS_DECELERATION_ROLLING = 9,  // 减速滑跑
    V_VMS1394_FLY_STATUS_TAXI_IN_THE_RUNWAY   = 10, // 驶入跑道
    V_VMS1394_FLY_STATUS_TAXI_BACK_TO_HANGAR  = 11, // 驶回机库
} VMS1394_FLY_STATUS;

// 标识符: VMS1394_GND_CHAIN_SAFE
// 名  称: VMS1394_地面连锁安全
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_GND_CHAIN_SAFE_DANGER = 0, // 危险
    V_VMS1394_GND_CHAIN_SAFE_SAFE   = 1, // 安全
} VMS1394_GND_CHAIN_SAFE;

// 标识符: VMS1394_GSE
// 名  称: VMS1394_GSE
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_GSE_INVALID = 0, // 无效
    V_VMS1394_GSE_VALID   = 1, // 有效
} VMS1394_GSE;

// 标识符: VMS1394_LRU_ID
// 名  称: VMS1394_LRU_ID
// 字  数: 2
// 说  明: A通道：bit26~bit27  1 0
//         B通道：bit26~bit27  0 1
//         C通道：bit26~bit27  1 0
typedef enum {
    V_VMS1394_LRU_ID_CHA = 0, // A通道
    V_VMS1394_LRU_ID_CHB = 1, // B通道
    V_VMS1394_LRU_ID_CHC = 2, // C通道
} VMS1394_LRU_ID;

// 标识符: VMS1394_MWE_silence_status
// 名  称: VMS1394_毫米波静默状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_MWE_SILENCE_STATUS_NO_SILENCE = 0, // 非静默
    V_VMS1394_MWE_SILENCE_STATUS_SILENCE    = 1, // 静默
} VMS1394_MWE_SILENCE_STATUS;

// 标识符: VMS1394_OFP_LOAD
// 名  称: VMS1394_OFP加载
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_OFP_LOAD_INVALID = 0, // 无效
    V_VMS1394_OFP_LOAD_VALID   = 1, // 有效
} VMS1394_OFP_LOAD;

// 标识符: VMS1394_OFPLOAD_IN_PROGRESS
// 名  称: VMS1394_OFPLOAD_IN_PROGRESS
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_OFPLOAD_IN_PROGRESS_INVALID = 0, // 无效
    V_VMS1394_OFPLOAD_IN_PROGRESS_VALID   = 1, // 有效
} VMS1394_OFPLOAD_IN_PROGRESS;

// 标识符: VMS1394_PBIT_IN_PROGRESS
// 名  称: VMS1394_PBIT_IN_PROGRESS
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_PBIT_IN_PROGRESS_INVALID = 0, // 无效
    V_VMS1394_PBIT_IN_PROGRESS_VALID   = 1, // 有效
} VMS1394_PBIT_IN_PROGRESS;

// 标识符: VMS1394_PBIT_MODE
// 名  称: VMS1394_PBIT模式
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_PBIT_MODE_INVALID = 0, // 无效
    V_VMS1394_PBIT_MODE_VALID   = 1, // 有效
} VMS1394_PBIT_MODE;

// 标识符: VMS1394_PBIT_MODE_R
// 名  称: VMS1394_MBIT模式_只读
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_PBIT_MODE_R_INVALID = 0, // 无效
    V_VMS1394_PBIT_MODE_R_VALID   = 1, // 有效
} VMS1394_PBIT_MODE_R;

// 标识符: VMS1394_PBIT_MODE_RW
// 名  称: VMS1394_MBIT模式_读写
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_PBIT_MODE_RW_INVALID = 0, // 无效
    V_VMS1394_PBIT_MODE_RW_VALID   = 1, // 有效
} VMS1394_PBIT_MODE_RW;

// 标识符: VMS1394_PUBIT_MODE
// 名  称: VMS1394_上电初始化模式
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_PUBIT_MODE_INVALID = 0, // 无效
    V_VMS1394_PUBIT_MODE_VALID   = 1, // 有效
} VMS1394_PUBIT_MODE;

// 标识符: VMS1394_RA1_silence_status
// 名  称: VMS1394_高度表静默1状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_RA1_SILENCE_STATUS_NO_SILENCE = 0, // 非静默
    V_VMS1394_RA1_SILENCE_STATUS_SILENCE    = 1, // 静默
} VMS1394_RA1_SILENCE_STATUS;

// 标识符: VMS1394_RA2_silence_status
// 名  称: VMS1394_高度表静默2状态
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_RA2_SILENCE_STATUS_NO_SILENCE = 0, // 非静默
    V_VMS1394_RA2_SILENCE_STATUS_SILENCE    = 1, // 静默
} VMS1394_RA2_SILENCE_STATUS;

// 标识符: VMS1394_SCO
// 名  称: VMS1394_单通道工作标志
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_SCO_INVALID = 0, // 无效
    V_VMS1394_SCO_VALID   = 1, // 有效
} VMS1394_SCO;

// 标识符: VMS1394_STOP_FAULT_RECORD
// 名  称: VMS1394_停止故障记录标志
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_STOP_FAULT_RECORD_INVALID = 0, // 无效
    V_VMS1394_STOP_FAULT_RECORD_VALID   = 1, // 有效
} VMS1394_STOP_FAULT_RECORD;

// 标识符: VMS1394_tag_IFDL_PowerLimit
// 名  称: VMS1394_机间链天线限功率标志
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS1394_TAG_IFDL_POWERLIMIT_NOT_LIMIT = 0, // 不限制
    V_VMS1394_TAG_IFDL_POWERLIMIT_LIMIT     = 1, // 限制
} VMS1394_TAG_IFDL_POWERLIMIT;

// 标识符: VMS1394_tag_LAIU_PowerLimit
// 名  称: VMS1394_L波段天线限功率标志
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS1394_TAG_LAIU_POWERLIMIT_NOT_LIMIT = 0, // 不限制
    V_VMS1394_TAG_LAIU_POWERLIMIT_LIMIT     = 1, // 限制
} VMS1394_TAG_LAIU_POWERLIMIT;

// 标识符: VMS1394_validity_IFDL_PowerLimit
// 名  称: VMS1394_有效性_机间链天线限功率
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS1394_VALIDITY_IFDL_POWERLIMIT_INVALID = 0, // 无效
    V_VMS1394_VALIDITY_IFDL_POWERLIMIT_VALID   = 1, // 有效
} VMS1394_VALIDITY_IFDL_POWERLIMIT;

// 标识符: VMS1394_validity_LAIU_PowerLimit
// 名  称: VMS1394_有效性_L波段天线限功率
// 字  数: 8
// 说  明:
typedef enum {
    V_VMS1394_VALIDITY_LAIU_POWERLIMIT_INVALID = 0, // 无效
    V_VMS1394_VALIDITY_LAIU_POWERLIMIT_VALID   = 1, // 有效
} VMS1394_VALIDITY_LAIU_POWERLIMIT;

// 标识符: VMS1394_VMC_A_CHV
// 名  称: VMS1394_有效性_A通道
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_VMC_A_CHV_INVALID = 0, // 无效
    V_VMS1394_VMC_A_CHV_VALID   = 1, // 有效
} VMS1394_VMC_A_CHV;

// 标识符: VMS1394_VMC_B_CHV
// 名  称: VMS1394_有效性_B通道
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_VMC_B_CHV_INVALID = 0, // 无效
    V_VMS1394_VMC_B_CHV_VALID   = 1, // 有效
} VMS1394_VMC_B_CHV;

// 标识符: VMS1394_VMC_C_CHV
// 名  称: VMS1394_有效性_C通道
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_VMC_C_CHV_INVALID = 0, // 无效
    V_VMS1394_VMC_C_CHV_VALID   = 1, // 有效
} VMS1394_VMC_C_CHV;

// 标识符: VMS1394_VMC_DPV
// 名  称: VMS1394_本通道CPU_DPV
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_VMC_DPV_INVALID = 0, // 无效
    V_VMS1394_VMC_DPV_VALID   = 1, // 有效
} VMS1394_VMC_DPV;

// 标识符: VMS1394_WOW
// 名  称: VMS1394_轮载
// 字  数: 1
// 说  明:
typedef enum {
    V_VMS1394_WOW_AIR = 0, // 空中
    V_VMS1394_WOW_GND = 1, // 地面
} VMS1394_WOW;

// 标识符: VMS1394_YKZ_CDL_DOWN_WROKSTATUS
// 名  称: VMS1394_遥控帧_C链下行工作状态
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_YKZ_CDL_DOWN_WROKSTATUS_NA      = 0, // NA
    V_VMS1394_YKZ_CDL_DOWN_WROKSTATUS_SILENCE = 1, // 静默
    V_VMS1394_YKZ_CDL_DOWN_WROKSTATUS_H_POWER = 2, // 大功率
    V_VMS1394_YKZ_CDL_DOWN_WROKSTATUS_L_POWER = 3, // 小功率
} VMS1394_YKZ_CDL_DOWN_WROKSTATUS;

// 标识符: VMS1394_YKZ_KaDL_DOWN_WROKSTATUS
// 名  称: VMS1394_遥控帧_Ka链下行工作状态
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_YKZ_KADL_DOWN_WROKSTATUS_NA      = 0, // NA
    V_VMS1394_YKZ_KADL_DOWN_WROKSTATUS_SILENCE = 1, // 静默
    V_VMS1394_YKZ_KADL_DOWN_WROKSTATUS_WORK    = 2, // 工作
} VMS1394_YKZ_KADL_DOWN_WROKSTATUS;

// 标识符: VMS1394_YKZ_KuDL_DOWN_WROKSTATUS
// 名  称: VMS1394_遥控帧_Ku链下行工作状态
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_YKZ_KUDL_DOWN_WROKSTATUS_NA      = 0, // NA
    V_VMS1394_YKZ_KUDL_DOWN_WROKSTATUS_SILENCE = 1, // 静默
    V_VMS1394_YKZ_KUDL_DOWN_WROKSTATUS_WORK    = 2, // 工作
} VMS1394_YKZ_KUDL_DOWN_WROKSTATUS;

// 标识符: VMS1394_YKZ_LDL_DOWN_WROKSTATUS
// 名  称: VMS1394_遥控帧_L链下行工作状态
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_YKZ_LDL_DOWN_WROKSTATUS_NA      = 0, // NA
    V_VMS1394_YKZ_LDL_DOWN_WROKSTATUS_SILENCE = 1, // 静默
    V_VMS1394_YKZ_LDL_DOWN_WROKSTATUS_H_POWER = 2, // 大功率
    V_VMS1394_YKZ_LDL_DOWN_WROKSTATUS_L_POWER = 3, // 小功率
} VMS1394_YKZ_LDL_DOWN_WROKSTATUS;

// 标识符: VMS1394_YKZ_SDL_DOWN_WROKSTATUS
// 名  称: VMS1394_遥控帧_S链下行工作状态
// 字  数: 3
// 说  明:
typedef enum {
    V_VMS1394_YKZ_SDL_DOWN_WROKSTATUS_NA      = 0, // NA
    V_VMS1394_YKZ_SDL_DOWN_WROKSTATUS_SILENCE = 1, // 静默
    V_VMS1394_YKZ_SDL_DOWN_WROKSTATUS_WORK    = 2, // 工作
} VMS1394_YKZ_SDL_DOWN_WROKSTATUS;

// 标识符: VS1394_net_state
// 名  称: 飞管1394网络状态
// 字  数: 8
// 说  明:
typedef enum {
    V_VS1394_NET_STATE_NA       = 0, // 未知或无意义
    V_VS1394_NET_STATE_OFF_LINE = 1, // 通信断
    V_VS1394_NET_STATE_ON_LINE  = 2, // 在网
} VS1394_NET_STATE;

// 标识符: wind_data_source
// 名  称: 风速风向数据源
// 字  数: 8
// 说  明: 描述风速风向的数据来源：
//         =INS，表示风速风向来自于惯导；
//         =DCS，表述风速风向来自于与人工通过显控修改。
typedef enum {
    V_WIND_DATA_SOURCE_INS = 0, //
    V_WIND_DATA_SOURCE_DCS = 1, //
} WIND_DATA_SOURCE;

// 标识符: WOW_main
// 名  称: 轮载状态_主
// 字  数: 8
// 说  明:
typedef enum {
    V_WOW_MAIN_NA      = 0, // 无意义
    V_WOW_MAIN_WOW_GND = 1, // 地面
    V_WOW_MAIN_WOW_AIR = 2, // 空中
} WOW_MAIN;

// 标识符: WU_main
// 名  称: 起落架状态_主
// 字  数: 8
// 说  明:
typedef enum {
    V_WU_MAIN_NA    = 0, // 无意义
    V_WU_MAIN_WU_DN = 1, // 放下
    V_WU_MAIN_WU_UP = 2, // 收起
} WU_MAIN;

#endif
