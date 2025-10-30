/**
 * @Author: Chongyang Liu
 * @Date:   2025-09-06 20:50:29
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-09-06 20:51:14
 */
#pragma once

/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/
// #include <string>
// #include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

// -------------------- �����ṹ�� -------------------- //
typedef struct EntityID {
    unsigned int U4_EntityID;
    unsigned short U2_GenID;
} EntityID;

typedef struct Position {
    double D8_Longitude_deg_CGCS;
    double D8_Latitude_deg_CGCS;
    float F4_AltitudeAsl_m_CGCS;
} Position;

typedef struct Timestamp {
    unsigned char U1_Year;
    unsigned char U1_Month;
    unsigned char U1_Day;
    unsigned char U1_Hour;
    unsigned char U1_Minute;
    unsigned char U1_Second;
    unsigned short U2_Millisecond;
} Timestamp;

// -------------------- ������Ϣͷ -------------------- //
typedef struct SM_MessageHeader {
    unsigned int U4_Heartbeat;
    unsigned short U2_EffectiveLength;
    Timestamp St_PubTime;
    Timestamp St_GenerateTime;
} SM_MessageHeader;

// -------------------- �豸/ʵ����Ϣ -------------------- //
typedef struct EntityAttribute {
    EntityID St_EntityID;
    unsigned char U1_EntityCamp;
    unsigned char U1_EntityCategory;
    unsigned short U2_EntityType;
    unsigned char U1_EntityClass;
    unsigned char U1_EntityLive;
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
    Position St_EntityPosition;
    LinearVelocity St_EntityLinearVelocit;
    LinearAcceleration St_EntityLinearAcceleratio;
    Attitude St_EntityAttitude;
} EntityPosVelAccAtt;

// -------------------- ��Ϣ���� -------------------- //
typedef struct FacilitiesPowerSupplyStatusData {
    char ArrU1_FacilitiesPowerSupplyStatus[25];
} FacilitiesPowerSupplyStatusData;

typedef struct FacilitiesPowerSupplyStatusParasMsg {
    SM_MessageHeader St_SMMessageHeader;
    FacilitiesPowerSupplyStatusData St_FacilitiesPowerSupplyStatusData;
} FacilitiesPowerSupplyStatusParasMsg;

// -------------------- ģ�������� -------------------- //
typedef struct SimulatorStatusControl {
    unsigned char U1_OperationMode;
} SimulatorStatusControl;

typedef struct SecSimulatorControlMsg {
    SM_MessageHeader St_SMMessageHeader;
    SimulatorStatusControl St_SimulatorStatusControl;
} SecSimulatorControlMsg;

// -------------------- ʵ��TSPI -------------------- //
typedef struct SecEntityTSPIMsg {
    SM_MessageHeader St_MessageHeader;
    EntityAttribute St_EntityAttribute;
    EntityPosVelAccAtt St_EntityPosVelAccAtt;
} SecEntityTSPIMsg;

// -------------------- SecAllEntityTSPIMsg -------------------- //
typedef struct MessageValid {
    bool B1_MessageDataValid;
} MessageValid;

typedef struct SecEnAttrPVAA {
    SM_MessageHeader St_MessageHeader;
    EntityAttribute St_EntityAttribute;
    EntityPosVelAccAtt St_EntityPosVelAccAtt;
} SecEnAttrPVAA;

typedef struct SecAllEntityTSPIMsg {
    SM_MessageHeader St_SMMessageHeader;
    MessageValid Arr_MessageValid[200];
    SecEnAttrPVAA Arr_SecEnAttrPVAA[200];
} SecAllEntityTSPIMsg;

// -------------------- SecVFTSPIMsg -------------------- //
typedef struct SingleVFTSPI {
    EntityAttribute VFAttribute;
    EntityPosVelAccAtt VFPosVelAccAtt;
} SingleVFTSPI;

typedef struct SecVFTSPIMsg {
    SM_MessageHeader St_SMMessageHeader;
    SingleVFTSPI Arr_SecVFTSPI[200];
} SecVFTSPIMsg;

// -------------------- ���ܵ�Ԫ״̬ -------------------- //
typedef struct UnitStatusData {
    char ArrI1_UnitID[20];
    char ArrI1_UnitVersion[9];
    unsigned int U4_UnitHeartbeat;
    unsigned char U1_MemberStatus;
} UnitStatusData;

typedef struct FunctionalUnitStatusMsg {
    SM_MessageHeader St_MessageHeader;
    UnitStatusData St_UnitStatusData;
} FunctionalUnitStatusMsg;

// -------------------- �������� -------------------- //
typedef struct DeviceAttribute {
    EntityID St_DeviceEntityID;
    unsigned char U1_DeviceType;
    unsigned short U2_DeviceCategory;
} DeviceAttribute;

typedef struct ElectroOpticalEquipmentStatus {
    unsigned char U1_SearchingStatus;
    unsigned char U1_WorkMode;
    unsigned char U1_InfraredBand;
} ElectroOpticalEquipmentStatus;

typedef struct ElecOptDeteWorkingParas {
    DeviceAttribute St_DeviceAttribute;
    ElectroOpticalEquipmentStatus St_ElectroOpticalEquipmentStatus;
} ElecOptDeteWorkingParas;

typedef struct SecElecOptDeteWorkingParasMsg {
    SM_MessageHeader St_SMMessageHeader;
    ElecOptDeteWorkingParas St_ElecOptDeteWorkingParas;
} SecElecOptDeteWorkingParasMsg;

// -------------------- ͼ������ -------------------- //
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
    EntityID St_EntityID;
    float F4_TargetDis;
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
    EOImageModePara St_EOImageModePara;
    EOImageEffect Arr_EOImageEffect[3];
    EOImageTrackPara Arr_EOImageTrackPara[3];
    EOImageShowArea St_EOImageShowArea;
} SecIRSTImageDriveMsg;

/********************�����ڴ�����ӿ�*********************/
typedef struct SharedMemoryInput {
    // �豸����״̬����
    FacilitiesPowerSupplyStatusParasMsg facilities_power_supply_status_paras_msg;
    // ģ�������п��� - ��������ָ��
    SecSimulatorControlMsg sec_simulator_control_msg;
    // ʵ��ʱ��λ��״̬ - ������Ϣ
    SecEntityTSPIMsg sec_entity_tspi_msg;
    // ʵ��ʱ��λ��״̬ - ʵ��Ŀ����Ϣ������ģ������
    SecAllEntityTSPIMsg sec_all_entity_tspi_msg;
    // �������ʱ��λ��״̬ - ����Ŀ����Ϣ��ѵ�����������õ�Ŀ�꣩
    SecVFTSPIMsg sec_vft_spi_msg;
} SharedMemoryInput;
/********************�����ڴ�����ӿ�:End*********************/

/********************�����ڴ�����ӿ�*********************/
typedef struct SharedMemoryOutput {
    // ���ܵ�Ԫ״̬
    FunctionalUnitStatusMsg functional_unit_status_msg;
    // ���̽��ϵͳ����
    SecElecOptDeteWorkingParasMsg sec_elec_opt_dete_working_paras_msg;
    // ��������������
    SecIRSTImageDriveMsg sec_irst_image_drive_msg;
} SharedMemoryOutput;
/********************�����ڴ�����ӿ�:End*********************/

#pragma pack()

#ifdef __cplusplus
}
#endif
