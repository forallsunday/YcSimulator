/**
 * @Author: Chongyang Liu
 * @Date:   2025-09-06 20:50:29
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-09-06 20:51:14
 */
#pragma once

/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/
// #include <string>
// #include <vector>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

// -------------------- 基础结构体 -------------------- //
typedef struct EntityID {
    unsigned int   U4_EntityID;
    unsigned short U2_GenID;
} EntityID;

typedef struct Position {
    double D8_Longitude_deg_CGCS;
    double D8_Latitude_deg_CGCS;
    float  F4_AltitudeAsl_m_CGCS;
} Position;

typedef struct Timestamp {
    unsigned char  U1_Year;
    unsigned char  U1_Month;
    unsigned char  U1_Day;
    unsigned char  U1_Hour;
    unsigned char  U1_Minute;
    unsigned char  U1_Second;
    unsigned short U2_Millisecond;
} Timestamp;

// -------------------- 公共消息头 -------------------- //
typedef struct SM_MessageHeader {
    unsigned int   U4_Heartbeat;
    unsigned short U2_EffectiveLength;
    Timestamp      St_PubTime;
    Timestamp      St_GenerateTime;
} SM_MessageHeader;

// -------------------- 设备/实体信息 -------------------- //
typedef struct EntityAttribute {
    EntityID       St_EntityID;
    unsigned char  U1_EntityCamp;
    unsigned char  U1_EntityCategory;
    unsigned short U2_EntityType;
    unsigned char  U1_EntityClass;
    unsigned char  U1_EntityLive;
} EntityAttribute;

typedef struct LinearVelocity {
    float F4_VelocityNorth_mDs_NED;
    float F4_VelocityEast_mDs_NED;
    float F4_VelocityUp_mDs_NED;
} LinearVelocity;

typedef struct LinearAcceleration {
    float F4_AccelerationNorth_mDs2_NED;
    float F4_AccelerationEast_mDs2_NED;
    float F4_AccelerationUp_mDs2_NED;
} LinearAcceleration;

typedef struct Attitude {
    float F4_Psi_deg;
    float F4_Theta_deg;
    float F4_Phi_deg;
} Attitude;

typedef struct EntityPosVelAccAtt {
    Position           St_EntityPosition;
    LinearVelocity     St_EntityLinearVelocit;
    LinearAcceleration St_EntityLinearAcceleratio;
    Attitude           St_EntityAttitude;
} EntityPosVelAccAtt;

// -------------------- 消息数据 -------------------- //
typedef struct FacilitiesPowerSupplyStatusData {
    char ArrU1_FacilitiesPowerSupplyStatus[25];
} FacilitiesPowerSupplyStatusData;

typedef struct FacilitiesPowerSupplyStatusParasMsg {
    SM_MessageHeader                St_SMMessageHeader;
    FacilitiesPowerSupplyStatusData St_FacilitiesPowerSupplyStatusData;
} FacilitiesPowerSupplyStatusParasMsg;

// -------------------- 模拟器控制 -------------------- //
typedef struct SimulatorStatusControl {
    unsigned char U1_OperationMode;
} SimulatorStatusControl;

typedef struct SecSimulatorControlMsg {
    SM_MessageHeader       St_SMMessageHeader;
    SimulatorStatusControl St_SimulatorStatusControl;
} SecSimulatorControlMsg;

// -------------------- 实体TSPI -------------------- //
typedef struct SecEntityTSPIMsg {
    SM_MessageHeader   St_MessageHeader;
    EntityAttribute    St_EntityAttribute;
    EntityPosVelAccAtt St_EntityPosVelAccAtt;
} SecEntityTSPIMsg;

// -------------------- SecAllEntityTSPIMsg -------------------- //
typedef struct MessageValid {
    bool B1_MessageDataValid;
} MessageValid;

typedef struct SecEnAttrPVAA {
    SM_MessageHeader   St_MessageHeader;
    EntityAttribute    St_EntityAttribute;
    EntityPosVelAccAtt St_EntityPosVelAccAtt;
} SecEnAttrPVAA;

typedef struct SecAllEntityTSPIMsg {
    SM_MessageHeader St_SMMessageHeader;
    MessageValid     Arr_MessageValid[200];
    SecEnAttrPVAA    Arr_SecEnAttrPVAA[200];
} SecAllEntityTSPIMsg;

// -------------------- SecVFTSPIMsg -------------------- //
typedef struct SingleVFTSPI {
    EntityAttribute    VFAttribute;
    EntityPosVelAccAtt VFPosVelAccAtt;
} SingleVFTSPI;

typedef struct SecVFTSPIMsg {
    SM_MessageHeader St_SMMessageHeader;
    SingleVFTSPI     Arr_SecVFTSPI[200];
} SecVFTSPIMsg;

// -------------------- 功能单元状态 -------------------- //
typedef struct UnitStatusData {
    char          ArrI1_UnitID[20];
    char          ArrI1_UnitVersion[9];
    unsigned int  U4_UnitHeartbeat;
    unsigned char U1_MemberStatus;
} UnitStatusData;

typedef struct FunctionalUnitStatusMsg {
    SM_MessageHeader St_MessageHeader;
    UnitStatusData   St_UnitStatusData;
} FunctionalUnitStatusMsg;

// -------------------- 工作参数 -------------------- //
typedef struct DeviceAttribute {
    EntityID       St_DeviceEntityID;
    unsigned char  U1_DeviceType;
    unsigned short U2_DeviceCategory;
} DeviceAttribute;

typedef struct ElectroOpticalEquipmentStatus {
    unsigned char U1_SearchingStatus;
    unsigned char U1_WorkMode;
    unsigned char U1_InfraredBand;
} ElectroOpticalEquipmentStatus;

typedef struct ElecOptDeteWorkingParas {
    DeviceAttribute               St_DeviceAttribute;
    ElectroOpticalEquipmentStatus St_ElectroOpticalEquipmentStatus;
} ElecOptDeteWorkingParas;

typedef struct SecElecOptDeteWorkingParasMsg {
    SM_MessageHeader        St_SMMessageHeader;
    ElecOptDeteWorkingParas St_ElecOptDeteWorkingParas;
} SecElecOptDeteWorkingParasMsg;

// -------------------- 图像驱动 -------------------- //
typedef struct EOImageModePara {
    unsigned char U1_ImageMode; // 0-NA，1-区域成像，2-追踪成像，3-回放成像，4-着陆成像，5-模拟平显成像
} EOImageModePara;

typedef struct EOImageEffect {
    unsigned char U1_VideoSource; // 像源选择 0-NA，1-中波，2-长波，3-可见光
    unsigned char U1_VideoPolar;  // 视频极化 0-NA，1-黑热，2-白热（光雷仅在中波/长波下可进行视频极化）
    unsigned char U1_Contrast;    // 对比度 DAS专用，0-NA，从1开始，根据具体型号确定级数
    unsigned char U1_Gray;        // 灰度 DAS专用，0-NA，从1开始，根据具体型号确定级数
    unsigned char U1_DigitalZoom; // 数字变焦 0-NA,1-1x,2-2x,3-4x
} EOImageEffect;

typedef struct EOImageTrackPara {
    EntityID       St_EntityID;     // 追踪目标编号 同战场
    float          F4_TargetDis;    // 显示目标距离 融合距离，单位km，保留小数点后一位
    unsigned short U2_ShowEntityID; // 显示目标编号 融合ID。光雷可跟踪4个目标，优先显示跟踪状态前两位，有丢失情况，自动补齐
} EOImageTrackPara;

typedef struct EOImageShowArea {
    float F4_AZLOS_deg_BODY;      // 视线方位角 [-180,180]
    float F4_ELLOS_deg_BODY;      // 视线俯仰角 [-90,90]
    float F4_horizontalCover_deg; // 水平范围 [0,180]
    float F4_verticalCover_deg;   // 垂直范围 [0,180]
} EOImageShowArea;

typedef struct SecIRSTImageDriveMsg {
    SM_MessageHeader St_SMMessageHeader;
    EOImageModePara  St_EOImageModePara;      // 成像模式参数
    EOImageEffect    Arr_EOImageEffect[3];    // 光电图像特效
    EOImageTrackPara Arr_EOImageTrackPara[3]; // 光电追踪成像参数
    EOImageShowArea  St_EOImageShowArea;      // 显示区域参数
} SecIRSTImageDriveMsg;

typedef struct Longlat {
    double longitude;
    double latitude;
} LongLat;

// 表2：成像状态数据定义
// 标识：EOImageState
typedef struct EOImageState {
    // 传感器状态 (U1_IRSensor)
    // 数据长度: 1 Byte (Octet)
    // 0-NA，1-可见光，2-红外，3-可见+红外，4-红外+可见
    uint8_t U1_IRSensor;

    // 视频状态 (U1_TVState)
    // 数据长度: 1 Byte (Octet)
    // 视频/图像标识位：用于区域监视区分视频下传与图像下传
    // 0-NA，1-图像，2-视频
    uint8_t U1_TVState;

    // 成像模式 (U1_ImageMode)
    // 数据长度: 1 Byte (Octet)
    // 0-NA，1-广域成像，2-区域成像，3-区域监视
    uint8_t U1_ImageMode;
} EOImageState;

typedef struct EOImageParasIS {
    // 图像时间 (8 bytes)
    Timestamp St_ImageTime;

    // 图像帧序号 (4 bytes)
    uint32_t U4_ImgId;

    // 光电周期号 (2 bytes)
    uint16_t U2_EOCycleNo;

    // 条带号 (2 bytes)
    uint16_t U2_LineNo;

    // 条带内序号 (2 bytes)
    uint16_t U2_EO_LineNo;

    // 图像行数 (4 bytes)
    uint32_t U4_ImageLineNum;

    // 图像列数 (4 bytes)
    uint32_t U4_ImageColumnNum;

    // 收容宽度 (m，4 bytes)
    uint32_t U4_WideCover;

    // 视场中心俯仰 (deg，float, 4 bytes)
    float F4_ELLOS_deg_BODY;

    // 视场中心方位 (deg，float, 4 bytes)
    float F4_AZLOS_deg_BODY;

    // 视场大小俯仰 (deg，float)
    float F4_verticalCover_deg;

    // 视场大小方位 (deg，float)
    float F4_horizontalCover_deg;

    // 航向重叠率 (1 byte)
    uint8_t U1_CouseTgtCover;

    // 傍向重叠率 (1 byte)
    uint8_t U1_BesideTgtCover;

    // 像元分辨率 (m，LSB=0.01, 2 bytes)
    uint16_t U2_CurResolution;

    // 地面摄影分辨率 (m，LSB=0.01, 2 bytes)
    uint16_t U2_GroundResolution;

    // 图像中心经纬高 (20 bytes)
    Position St_ImgCenterPosition;

    // 图像左上角经纬度 (16 bytes)
    Longlat St_ImgLeftUp;

    // 图像左下角经纬度 (16 bytes)
    Longlat St_ImgLeftDown;

    // 图像右上角经纬度 (16 bytes)
    Longlat St_ImgRightUp;

    // 图像右下角经纬度 (16 bytes)
    Longlat St_ImgRightDown;

    // 照相次数 (2 bytes)
    uint16_t U2_TakeTimes;

    // 相机焦距 (mm, 2 bytes)
    uint16_t U2_FocalLength;

    // 曝光时间 (us, 2 bytes)
    uint16_t U2_ExposureTime;

    // 重要目标标识 (1 byte)
    uint8_t U1_ImpotentTag;

    // 成像中心经纬度 (16 bytes)
    Longlat St_ImgCenter;

    // 载机信息 (56 bytes)
    EntityPosVelAccAtt St_AcParas;

    // 图像任务信息 (20 bytes)
    char Seq_Mission[20];
} EOImageParasIS;

// 表 3：光电图像调节参数数据定义
// 标识：EOImageModifyPara
typedef struct EOImageModifyPara {
    // 可见光调光值 [-127, 127]
    char I1_LightValueLight;

    // 可见光调焦值 [-127, 127]
    char I1_FocusValueLight;

    // 可见光去雾：0-NA，1-ON，2-OFF
    uint8_t U1_LightMistEliminate;

    // 可见光增强：0-NA，1-ON，2-OFF
    uint8_t U1_LightEnhance_Mode;

    // 红外调光值 [-127, 127]
    char I1_LightValueInfrared;

    // 红外调焦值 [-127, 127]
    char I1_FocusValueInfrared;

    // 极化：0-NA，1-黑热，2-白热
    uint8_t U1_VideoPolar;

    // 红外增强：0-NA，1-ON，2-OFF
    uint8_t U1_InfraredEnhanceMode;

} EOImageModifyPara;

// 表 4：动目标检测成像参数数据定义
// 标识：EOTgtPara
typedef struct EOTgtPara {
    // 检测目标编号
    // 类型：EntityID（用户自定义类型）
    EntityID St_EntityID;

} EOTgtPara;

// 表 5：动目标像素坐标参数数据定义
// 标识：EOTgtPositionPara
typedef struct EOTgtPositionPara {
    // 目标左上角横向像素坐标 [10, 65535]；无有效目标时默认填 0
    // 2 字节 unsigned short
    uint16_t U2_Tgt1UpleftX;

    // 目标左上角纵向像素坐标 [10, 65535]；无有效目标时默认填 0
    uint16_t U2_Tgt1UpleftY;

    // 目标右下角横向像素坐标 [10, 65535]；无有效目标时默认填 0
    uint16_t U2_Tgt1DownrightX;

    // 目标右下角纵向像素坐标 [10, 65535]；无有效目标时默认填 0
    uint16_t U2_Tgt1DownrightY;

} EOTgtPositionPara;

/********************共享内存输入接口*********************/
typedef struct SharedMemoryInput {
    // 设备供电状态参数
    FacilitiesPowerSupplyStatusParasMsg m_FacilitiesPowerSupplyStatusParasMsg;
    // 模拟器运行控制 - 场景控制指令
    SecSimulatorControlMsg m_SecSimulatorControlMsg;
    // 实体时空位置状态 - 本机信息
    SecEntityTSPIMsg m_SecEntityTSPIMsg;
    // 实体时空位置状态 - 实体目标信息（其他模拟器）
    SecAllEntityTSPIMsg m_SecAllEntityTSPIMsg;
    // 虚拟兵力时空位置状态 - 虚拟目标信息（训练控制中设置的目标）
    SecVFTSPIMsg m_SecVFTSPIMsg;
    // 动目标像素坐标参数数据定义
    EOTgtPositionPara m_EOTgtPositionPara;
} SharedMemoryInput;
/********************共享内存输入接口:End*********************/

/********************共享内存输出接口*********************/
typedef struct SharedMemoryOutput {
    // 功能单元状态
    FunctionalUnitStatusMsg m_FunctionalUnitStatusMsg;
    // 光电探测系统参数
    SecElecOptDeteWorkingParasMsg m_SecElecOptDeteWorkingParasMsg;
    // 光电成像驱动参数
    SecIRSTImageDriveMsg m_SecIRSTImageDriveMsg;
    // 成像状态数据定义
    EOImageState m_EOImageState;
    // 光电图像参数 注释信息
    EOImageParasIS m_EOImageParasIS;
    // 光电图像调节参数数据定义
    EOImageModifyPara m_EOImageModifyPara;
    // 动目标检测成像参数数据定义
    EOTgtPara m_EOTgtPara;

} SharedMemoryOutput;
/********************共享内存输出接口:End*********************/

#pragma pack()

#ifdef __cplusplus
}
#endif
