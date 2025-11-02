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
    unsigned char U1_ImageMode;
} EOImageModePara;

typedef struct EOImageEffect {
    unsigned char U1_VideoSource;
    unsigned char U1_VideoPolar;
    unsigned char U1_Contrast;
    unsigned char U1_Gray;
    unsigned char U1_DigitalZoom;
} EOImageEffect;

typedef struct EOImageTrackPara {
    EntityID       St_EntityID;
    float          F4_TargetDis;
    unsigned short U2_ShowEntityID;
} EOImageTrackPara;

typedef struct EOImageShowArea {
    float F4_AZLOS_deg_BODY;
    float F4_ELLOS_deg_BODY;
    float F4_horizontalCover_deg;
    float F4_verticalCover_deg;
} EOImageShowArea;

typedef struct SecIRSTImageDriveMsg {
    SM_MessageHeader St_SMMessageHeader;
    EOImageModePara  St_EOImageModePara;
    EOImageEffect    Arr_EOImageEffect[3];
    EOImageTrackPara Arr_EOImageTrackPara[3];
    EOImageShowArea  St_EOImageShowArea;
} SecIRSTImageDriveMsg;

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
} SharedMemoryOutput;
/********************共享内存输出接口:End*********************/

#pragma pack()

#ifdef __cplusplus
}
#endif
