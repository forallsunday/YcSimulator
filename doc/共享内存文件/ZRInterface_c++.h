#ifndef ZRInterface_c++_H_
#define ZRInterface_c++_H_

/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

#pragma pack(1)

typedef struct EntityID
{
    unsigned int U4_EntityID; // @ID(0)
    unsigned short U2_GenID; // @ID(1)
} EntityID; // @Extensibility(EXTENSIBLE)

typedef struct Timestamp
{
    unsigned char U1_Year; // @ID(0)
    unsigned char U1_Month; // @ID(1)
    unsigned char U1_Day; // @ID(2)
    unsigned char U1_Hour; // @ID(3)
    unsigned char U1_Minute; // @ID(4)
    unsigned char U1_Second; // @ID(5)
    unsigned short U2_Millisecond; // @ID(6)
} Timestamp; // @Extensibility(EXTENSIBLE)

typedef struct MessageHeader
{
    Timestamp St_PubTime; // @ID(0)
    Timestamp St_GenerateTime; // @ID(1)
    unsigned int U4_Heartbeat; // @ID(2)
} MessageHeader; // @Extensibility(EXTENSIBLE)

typedef struct DeviceAttribute
{
    EntityID St_DeviceEntityID; // @ID(0)
    unsigned char U1_DeviceType; // @ID(1)
    unsigned short U2_DeviceCategory; // @ID(2)
} DeviceAttribute; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData1
{
    EntityID St_ReceiveEntityID; // @ID(0)
    unsigned int U4_MessageLength; // @ID(1)
    char S_LinkData[1000]; // @ID(2)
} AALinkData1; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData2
{
    EntityID E4_ReceiveEntityID; // @ID(0)
    unsigned short U2_Spare; // @ID(1)
    unsigned int U4_MessageLength; // @ID(2)
    char S_LinkData[2000]; // @ID(3)
} AALinkData2; // @Extensibility(EXTENSIBLE)

typedef struct CGFSingleMunitionInfo
{
    unsigned int U4_MunitionCode; // @ID(0)
    char S_MunitionName[16]; // @ID(1)
    unsigned char U1_MunitionType; // @ID(2)
    unsigned char U1_MunitionAmount; // @ID(3)
} CGFSingleMunitionInfo; // @Extensibility(EXTENSIBLE)

typedef struct MemberID
{
    unsigned int U4_MemberID; // @ID(0)
} MemberID; // @Extensibility(EXTENSIBLE)

typedef struct SceneID
{
    unsigned short U2_SceneID; // @ID(0)
} SceneID; // @Extensibility(EXTENSIBLE)

typedef struct MemberAttribute
{
    MemberID St_MemberID; // @ID(0)
    unsigned char U1_MemberCategory; // @ID(1)
    unsigned short U2_MemberType; // @ID(2)
    SceneID St_MemberSceneID; // @ID(3)
    unsigned char U1_MemberStatus; // @ID(4)
    EntityID St_EntityID; // @ID(5)
    unsigned char U1_EntityCamp; // @ID(6)
} MemberAttribute; // @Extensibility(EXTENSIBLE)

typedef struct Position
{
    double D8_Longitude_deg_CGCS; // @ID(0)
    double D8_Latitude_deg_CGCS; // @ID(1)
    float F4_AltitudeAsl_m_CGCS; // @ID(2)
} Position; // @Extensibility(EXTENSIBLE)

typedef struct InitFlightParas
{
    Position St_FlightPosition; // @ID(0)
    float F4_Psi_deg; // @ID(1)
    float F4_Mach; // @ID(2)
    float F4_RunwayHsl_m; // @ID(3)
    unsigned int U4_OnboardFuel_kg; // @ID(4)
    unsigned char U1_LGHPos; // @ID(5)
    unsigned char U1_TrimMode; // @ID(6)
} InitFlightParas; // @Extensibility(EXTENSIBLE)

typedef struct AIStartParas
{
    unsigned char U1_AIMode; // @ID(0)
} AIStartParas; // @Extensibility(EXTENSIBLE)

typedef struct AIMemberInitFlightParas
{
    MemberAttribute St_MemberAttribute; // @ID(0)
    InitFlightParas St_InitFlightParas; // @ID(1)
} AIMemberInitFlightParas; // @Extensibility(EXTENSIBLE)

typedef struct SARImagePosition
{
    double D8_Longitude_deg_CGCS; // @ID(0)
    double D8_Latitude_deg_CGCS; // @ID(1)
} SARImagePosition; // @Extensibility(EXTENSIBLE)

typedef struct JamStatus
{
    EntityID Arr_JammedEntityID[32]; // @ID(0)
    unsigned char U1_JamMode; // @ID(1)
    unsigned char U1_JamType; // @ID(2)
    float F4_JamPower_W; // @ID(3)
} JamStatus; // @Extensibility(EXTENSIBLE)

typedef struct NoiseJam
{
    unsigned char U1_NoiseJamType; // @ID(0)
    float F4_NoiseJamBandwidth_MHz; // @ID(1)
} NoiseJam; // @Extensibility(EXTENSIBLE)

typedef struct DragJam
{
    float F4_DragVel_mDs; // @ID(0)
    float F4_DragDis_m; // @ID(1)
} DragJam; // @Extensibility(EXTENSIBLE)

typedef struct FalseJam
{
    unsigned char U1_FalseNum; // @ID(0)
    float ArrF4_FalseTimeDelayGap_s[4]; // @ID(1)
} FalseJam; // @Extensibility(EXTENSIBLE)

typedef struct ActiveJamWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    JamStatus St_JamStatus; // @ID(1)
    NoiseJam St_NoiseJam; // @ID(2)
    DragJam St_DragJam; // @ID(3)
    FalseJam St_FalseJam; // @ID(4)
} ActiveJamWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct Longlat
{
    double D8_Longitude_deg_CGCS; // @ID(0)
    double D8_Latitude_deg_CGCS; // @ID(1)
} Longlat; // @Extensibility(EXTENSIBLE)

typedef struct WindParas
{
    unsigned short U2_GustTopHeight_m; // @ID(0)
    unsigned short U2_GustBaseHeight_m; // @ID(1)
    float F4_GustVelocity_mDs; // @ID(2)
    float F4_GustDirection_deg; // @ID(3)
} WindParas; // @Extensibility(EXTENSIBLE)

typedef struct AtmosphericReport
{
    EntityID St_ReceiverID; // @ID(0)
    float F4_Atmospheric_Pressure_kPa; // @ID(1)
    float F4_Atmospheric_Temperature_C; // @ID(2)
    float F4_Huidity_rh; // @ID(3)
    float F4_Atmospheric_Density_kgDm3; // @ID(4)
    float F4_WindVelocityNorth_mDs_NED; // @ID(5)
    float F4_WindVelocityEast_mDs_NED; // @ID(6)
    float F4_WindVelocityUp_mDs_NED; // @ID(7)
    float F4_Atmospheric_Transmittance_LW; // @ID(8)
    float F4_Atmospheric_Transmittance_MW; // @ID(9)
    float F4_Atmospheric_Transmittance_L1; // @ID(10)
    float F4_Atmospheric_Transmittance_L2; // @ID(11)
} AtmosphericReport; // @Extensibility(EXTENSIBLE)

typedef struct AFFight_Mission_Param
{
    EntityID St_TGTEntityID; // @ID(0)
    char S_MunitionSchemeName[32]; // @ID(1)
    CGFSingleMunitionInfo Arr_MunitionLis[10]; // @ID(2)
} AFFight_Mission_Param; // @Extensibility(EXTENSIBLE)

typedef struct Evading_Mission_Param
{
    bool B1_IsPassiveJam; // @ID(0)
} Evading_Mission_Param; // @Extensibility(EXTENSIBLE)

typedef struct ElecJam_Mission_Param
{
    EntityID St_TGTEntityID[16]; // @ID(0)
    char S_JamType1[20]; // @ID(1)
    char S_JamType2[20]; // @ID(2)
    char S_JamType3[20]; // @ID(3)
} ElecJam_Mission_Param; // @Extensibility(EXTENSIBLE)

typedef struct GroundAirDenf_Mission_Param
{
    bool spare; // @ID(0)
} GroundAirDenf_Mission_Param; // @Extensibility(EXTENSIBLE)

typedef struct CGFPath
{
    unsigned char Path_Flag; // @ID(0)
    unsigned char Path_Num; // @ID(1)
    Position P20_Position; // @ID(2)
    float F4_GroundSpeed; // @ID(3)
} CGFPath; // @Extensibility(EXTENSIBLE)

typedef struct CGFMissionSetting
{
    char Arr_MissionName[20]; // @ID(0)
    AFFight_Mission_Param St_AFFight_Mission; // @ID(1)
    Evading_Mission_Param St_Evading_Mission; // @ID(2)
    ElecJam_Mission_Param St_ElecJam_Mission; // @ID(3)
    GroundAirDenf_Mission_Param St_GroundAirDenf_Mission; // @ID(4)
} CGFMissionSetting; // @Extensibility(EXTENSIBLE)

typedef struct EntityAttribute
{
    EntityID St_EntityID; // @ID(0)
    unsigned char U1_EntityCamp; // @ID(1)
    unsigned char U1_EntityCategory; // @ID(2)
    unsigned short U2_EntityType; // @ID(3)
    unsigned char U1_EntityClass; // @ID(4)
    unsigned char U1_EntityLive; // @ID(5)
} EntityAttribute; // @Extensibility(EXTENSIBLE)

typedef struct CGFForceManageSetting
{
    unsigned char U1_EntityOperation; // @ID(0)
} CGFForceManageSetting; // @Extensibility(EXTENSIBLE)

typedef struct CGFRealTimeInterveneInfo
{
    unsigned char Arr_ManageFlag[5]; // @ID(0)
    Position Str_Position; // @ID(1)
    float F4_GroundSpeed; // @ID(2)
    bool B1_FuelFrozen; // @ID(3)
    std::vector<CGFPath> Seq_CGFPath; // @ID(4) /* maximum length = (100) */
    CGFMissionSetting St_CGFMissionSetting; // @ID(5)
} CGFRealTimeInterveneInfo; // @Extensibility(EXTENSIBLE)

typedef struct RefuelingOrder
{
    unsigned char U1_TubeCmd; // @ID(0)
    unsigned char U1_PermitRefuel; // @ID(1)
    EntityID St_JointFlightID; // @ID(2)
} RefuelingOrder; // @Extensibility(EXTENSIBLE)

typedef struct RefuelingFlightCmd
{
    RefuelingOrder St_LeftRefuelingOrder; // @ID(0)
    RefuelingOrder St_MidRefuelingOrder; // @ID(1)
    RefuelingOrder St_RightRefuelingOrder; // @ID(2)
} RefuelingFlightCmd; // @Extensibility(EXTENSIBLE)

typedef struct RefuelingParas
{
    double D8_DyCapture; // @ID(0)
    double D8_DzCapture; // @ID(1)
    bool B1_BowWaveOn; // @ID(2)
    bool B1_VoetexOn; // @ID(3)
    double D8_VoetexGainPlane; // @ID(4)
    double D8_VoetexGainTube; // @ID(5)
    double D8_BowwaveGain; // @ID(6)
} RefuelingParas; // @Extensibility(EXTENSIBLE)

typedef struct EntityControlAttribute
{
    EntityID St_EntityID; // @ID(0)
} EntityControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct UDP_MessageHeader
{
    unsigned int U4_Heartbeat; // @ID(0)
    unsigned int U4_MessageID; // @ID(1)
    unsigned int U4_SourceID; // @ID(2)
    unsigned int U4_DestinationID; // @ID(3)
    unsigned int U4_DataLen; // @ID(4)
    Timestamp St_PubTime; // @ID(5)
    Timestamp St_GenerateTime; // @ID(6)
} UDP_MessageHeader; // @Extensibility(EXTENSIBLE)

typedef struct CameraRTStatus
{
    bool B1_CameraRTVisible[20]; // @ID(0)
    bool B1_CameraRTInfrared[20]; // @ID(1)
} CameraRTStatus; // @Extensibility(EXTENSIBLE)

typedef struct CoEngagementReq
{
    EntityID St_SimulatorID; // @ID(0)
    unsigned int U4_MessageLength; // @ID(1)
    unsigned char ArrU1_CoEngagementData[50]; // @ID(2)
} CoEngagementReq; // @Extensibility(EXTENSIBLE)

typedef struct MaintMsgHeader
{
    char S_ProtocolVersion[8]; // @ID(0)
    Timestamp T8_PubTime; // @ID(1)
    unsigned int U4_Heartbeat; // @ID(2)
} MaintMsgHeader; // @Extensibility(EXTENSIBLE)

typedef struct AreaAttribute
{
    unsigned char U1_HostArea; // @ID(0)
    char S_TrainingTerminalID[16]; // @ID(1)
    unsigned long long U8_MemberID; // @ID(2)
    unsigned char U1_DomaimID; // @ID(3)
} AreaAttribute; // @Extensibility(EXTENSIBLE)

typedef struct MaintDeviceAttribute
{
    unsigned char U1_DeviceCategory; // @ID(0)
} MaintDeviceAttribute; // @Extensibility(EXTENSIBLE)

typedef struct CockpitDeviceStatus
{
    unsigned char U1_CockpitFailure[40]; // @ID(0)
} CockpitDeviceStatus; // @Extensibility(EXTENSIBLE)

typedef struct ComputerAttribute
{
    unsigned char U1_ComputerID; // @ID(0)
} ComputerAttribute; // @Extensibility(EXTENSIBLE)

typedef struct ComputerControl
{
    unsigned char U1_ComputerControl; // @ID(0)
} ComputerControl; // @Extensibility(EXTENSIBLE)

typedef struct StComputerAttrControl
{
    ComputerAttribute St_ComputerAttribute; // @ID(0)
    ComputerControl St_ComputerControl; // @ID(1)
} StComputerAttrControl; // @Extensibility(EXTENSIBLE)

typedef struct ComputerStatus
{
    unsigned char U1_ComputerPower; // @ID(0)
    unsigned char U1_ComputerFailure; // @ID(1)
    unsigned char U1_ComputerTemp; // @ID(2)
    unsigned char U1_CPUUsage; // @ID(3)
    unsigned char U1_MemoryUsage; // @ID(4)
    unsigned char U1_NetUsage; // @ID(5)
} ComputerStatus; // @Extensibility(EXTENSIBLE)

typedef struct StComputerAttrStatus
{
    ComputerAttribute St_ComputerAttribute; // @ID(0)
    ComputerStatus St_ComputerStatus; // @ID(1)
} StComputerAttrStatus; // @Extensibility(EXTENSIBLE)

typedef struct ContainerManage
{
    unsigned char U1_SoftwareID; // @ID(0)
    unsigned char U1_DomaimID; // @ID(1)
    unsigned short U2_MemberType; // @ID(2)
    unsigned long long U8_MemberID; // @ID(3)
    unsigned short U2_SceneID; // @ID(4)
    unsigned char U1_MemberFlightConfig; // @ID(5)
    unsigned short U2_PODID; // @ID(6)
    char S_TrainingTerminalID[16]; // @ID(7)
} ContainerManage; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareControl
{
    unsigned char U1_SoftwareControl; // @ID(0)
} SoftwareControl; // @Extensibility(EXTENSIBLE)

typedef struct MunitionID
{
    unsigned int U4_MunitionID; // @ID(0)
} MunitionID; // @Extensibility(EXTENSIBLE)

typedef struct SingleDataInAcmi
{
    double D8_plon; // @ID(0)
    double D8_plat; // @ID(1)
    double D8_palt; // @ID(2)
    double D8_pVx; // @ID(3)
    double D8_pVy; // @ID(4)
    double D8_pVz; // @ID(5)
    double D8_zl_t_lon; // @ID(6)
    double D8_zl_t_lat; // @ID(7)
    double D8_zl_t_alt; // @ID(8)
    double D8_zl_t_Vx; // @ID(9)
    double D8_zl_t_Vy; // @ID(10)
    double D8_zl_t_Vz; // @ID(11)
    unsigned char U1_iPK; // @ID(12)
    double D8_t_lon_true; // @ID(13)
    double D8_t_lat_true; // @ID(14)
    double D8_t_alt_true; // @ID(15)
    double D8_t_Vx_true; // @ID(16)
    double D8_t_Vy_true; // @ID(17)
    double D8_t_Vz_true; // @ID(18)
    double D8_AE; // @ID(19)
    double D8_VE; // @ID(20)
    double D8_DE; // @ID(21)
    unsigned char U1_AEV; // @ID(22)
    unsigned char U1_VEV; // @ID(23)
    unsigned char U1_DEV; // @ID(24)
    unsigned char U1_AM; // @ID(25)
    double D8_rcs; // @ID(26)
    double D8_tHPO; // @ID(27)
    unsigned char U1_tspiValid; // @ID(28)
    unsigned char U1_T_Rcs; // @ID(29)
    unsigned char U1_DR; // @ID(30)
    unsigned char U1_LF; // @ID(31)
    double D8_HPO; // @ID(32)
    unsigned char cre; // @ID(33)
    unsigned char U1_DataPeriodFlag; // @ID(34)
    MunitionID St_MunitionID; // @ID(35)
    EntityID St_LaunchEntityID; // @ID(36)
    float F4_Psi_deg; // @ID(37)
    float F4_Theta_deg; // @ID(38)
    float F4_Phi_deg; // @ID(39)
} SingleDataInAcmi; // @Extensibility(EXTENSIBLE)

typedef struct SingleDataOutAcmi
{
    double D8_time; // @ID(0)
    double D8_m_lon; // @ID(1)
    double D8_m_lat; // @ID(2)
    double D8_m_alt; // @ID(3)
    double D8_m_vx; // @ID(4)
    double D8_m_vy; // @ID(5)
    double D8_m_vz; // @ID(6)
    double D8_theta; // @ID(7)
    double D8_psi; // @ID(8)
    double D8_fai; // @ID(9)
    double D8_mtdist; // @ID(10)
    unsigned char U1_bengine; // @ID(11)
    unsigned char U1_catched; // @ID(12)
    unsigned char U1_active; // @ID(13)
    unsigned char U1_CDJ_flag; // @ID(14)
    unsigned char U1_GL_flag; // @ID(15)
    unsigned char U1_noCatchedRes; // @ID(16)
    unsigned char U1_JL_flag; // @ID(17)
    unsigned char U1_SD_flag; // @ID(18)
    unsigned char U1_JD_flag; // @ID(19)
    double D8_SD_error; // @ID(20)
    double D8_JD_error; // @ID(21)
    unsigned char U1_aerial_Flag; // @ID(22)
    unsigned int U4_VER; // @ID(23)
    unsigned int U4_VER_DATE; // @ID(24)
    MunitionID St_MunitionID; // @ID(25)
    EntityID St_LaunchEntityID; // @ID(26)
} SingleDataOutAcmi; // @Extensibility(EXTENSIBLE)

typedef struct EMVReport
{
    EntityID E4_EMVCalI; // @ID(0)
    char U1_EMVComplexLevel; // @ID(1)
} EMVReport; // @Extensibility(EXTENSIBLE)

typedef struct LinearVelocity
{
    float F4_VelocityNorth_mDs_NED; // @ID(0)
    float F4_VelocityEast_mDs_NED; // @ID(1)
    float F4_VelocityUp_mDs_NED; // @ID(2)
} LinearVelocity; // @Extensibility(EXTENSIBLE)

typedef struct LinearAcceleration
{
    float F4_AccelerationNorth_mDs2_NED; // @ID(0)
    float F4_AccelerationEast_mDs2_NED; // @ID(1)
    float F4_AccelerationUp_mDs2_NED; // @ID(2)
} LinearAcceleration; // @Extensibility(EXTENSIBLE)

typedef struct Attitude
{
    float F4_Psi_deg; // @ID(0)
    float F4_Theta_deg; // @ID(1)
    float F4_Phi_deg; // @ID(2)
} Attitude; // @Extensibility(EXTENSIBLE)

typedef struct EntityPosVelAccAtt
{
    Position St_EntityPosition; // @ID(0)
    LinearVelocity St_EntityLinearVelocit; // @ID(1)
    LinearAcceleration St_EntityLinearAcceleratio; // @ID(2)
    Attitude St_EntityAttitude; // @ID(3)
} EntityPosVelAccAtt; // @Extensibility(EXTENSIBLE)

typedef struct ElectroOpticalEquipmentStatus
{
    unsigned char U1_SearchingStatus; // @ID(0)
    unsigned char U1_WorkMode; // @ID(1)
    unsigned char U1_InfraredBand; // @ID(2)
} ElectroOpticalEquipmentStatus; // @Extensibility(EXTENSIBLE)

typedef struct ElecOptDeteWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    ElectroOpticalEquipmentStatus St_ElectroOpticalEquipmentStatus; // @ID(1)
} ElecOptDeteWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct ElecPara
{
    unsigned short U2_EWtgtNo; // @ID(0)
    unsigned char U1_RadiationUpdate; // @ID(1)
    unsigned char U1_EWStgtSource; // @ID(2)
    unsigned short U2_EWSIdentCon; // @ID(3)
    unsigned short U1_TargetClass; // @ID(4)
    unsigned char U1_RadiateAttribute; // @ID(5)
    unsigned char U1_tgtECMEDState; // @ID(6)
    unsigned char U1_JamEffec; // @ID(7)
    unsigned char U1_RepeatedFRType; // @ID(8)
    unsigned char U1_VisitNum; // @ID(9)
    unsigned char U1_LoopEm; // @ID(10)
    unsigned char U1_MoveTrend; // @ID(11)
    unsigned int U4_PW[8]; // @ID(12)
    unsigned int U4_PRI[8]; // @ID(13)
    unsigned int U4_FR[8]; // @ID(14)
    unsigned int U4_MainBeamDwell[3]; // @ID(15)
    unsigned int U4_LoopIntercal[2]; // @ID(16)
    unsigned char U1_tgtState; // @ID(17)
    unsigned char U1_FRAttribute; // @ID(18)
    unsigned char U1_RFAttribute; // @ID(19)
    unsigned char U1_PWAttribute; // @ID(20)
    unsigned char U1_PulseChar; // @ID(21)
    unsigned char U1_CPItrackTime; // @ID(22)
    unsigned char U1_CPItrackNum; // @ID(23)
    unsigned char U1_TrackTime; // @ID(24)
    unsigned char U1_validAZ; // @ID(25)
    unsigned char U1_ValidEL; // @ID(26)
    int U4_tgtAZgeo; // @ID(27)
    int U4_tgtELgeo; // @ID(28)
    int U4_tgtAZbody; // @ID(29)
    int U4_tgtELbody; // @ID(30)
    unsigned int U4_tgtDistance; // @ID(31)
} ElecPara; // @Extensibility(EXTENSIBLE)

typedef struct EmbedID
{
    unsigned short U2_EmbedID; // @ID(0)
} EmbedID; // @Extensibility(EXTENSIBLE)

typedef struct EmbedIDControlAttribute
{
    EmbedID St_EmbedID; // @ID(0)
} EmbedIDControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct SceneControlAttribute
{
    SceneID St_SceneID; // @ID(0)
} SceneControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct SingleVCEmbedID
{
    EntityControlAttribute St_EntityID; // @ID(0)
    EmbedIDControlAttribute St_EmbedID; // @ID(1)
} SingleVCEmbedID; // @Extensibility(EXTENSIBLE)

typedef struct VirtualAppearance
{
    float ArrF4_Surface_deg[20]; // @ID(0)
    unsigned char ArrU1_EngineStatus[4]; // @ID(1)
    unsigned char ArrU1_EngineOnFire[4]; // @ID(2)
    unsigned char U1_RefuelingProbe; // @ID(3)
    float F4_Probe_X; // @ID(4)
    float F4_Probe_Z; // @ID(5)
    float F4_Probe_Y; // @ID(6)
    unsigned char U1_Luneburg; // @ID(7)
    unsigned char U1_DragChuteStatus; // @ID(8)
    unsigned char U1_Configuration; // @ID(9)
    unsigned short ArrU2_StoreType[40]; // @ID(10)
    unsigned char ArrU1_StoreNumber[40]; // @ID(11)
    unsigned char ArrU1_LghStatus[4]; // @ID(12)
    unsigned char U1_LandingLightStatus; // @ID(13)
    unsigned char U1_TaxingLightStatus; // @ID(14)
    unsigned char U1_NavLightStatus; // @ID(15)
    unsigned char U1_FormLightStatus; // @ID(16)
    unsigned char U1_AntiColLightStatus; // @ID(17)
    unsigned char U1_AirRefuelLightStatus; // @ID(18)
    unsigned char ArrU1_LGLightStatus[4]; // @ID(19)
    unsigned char U1_ExLightMode; // @ID(20)
} VirtualAppearance; // @Extensibility(EXTENSIBLE)

typedef struct ExtraFightData
{
    float F4_Airspeed; // @ID(0)
    float F4_Mach; // @ID(1)
    float F4_SceneHeight; // @ID(2)
    float F4_TrueAoa; // @ID(3)
    float F4_NormalOverload; // @ID(4)
    float F4_SatAltitude; // @ID(5)
    float F4_RadAltitude; // @ID(6)
    float F4_ClimbRate; // @ID(7)
    short Arr_ThrottlePos[5]; // @ID(8)
} ExtraFightData; // @Extensibility(EXTENSIBLE)

typedef struct MemberControlAttribute
{
    MemberID St_MemberID; // @ID(0)
} MemberControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct EntityIDSetting
{
    EntityID St_EntityID; // @ID(0)
} EntityIDSetting; // @Extensibility(EXTENSIBLE)

typedef struct SingleEntityIRIntensityReport
{
    EntityID St_TargetEntityID; // @ID(0)
    float F4_IRIntesity_WDsr; // @ID(1)
} SingleEntityIRIntensityReport; // @Extensibility(EXTENSIBLE)

typedef struct SingleMunitionIRIntensityReport
{
    MunitionID St_TargetMunitionID; // @ID(0)
    float F4_IRIntesity_WDsr; // @ID(1)
} SingleMunitionIRIntensityReport; // @Extensibility(EXTENSIBLE)

typedef struct SingleEntityRCSReport
{
    EntityID St_TargetEntityID; // @ID(0)
    float F4_TargetRCS_m2; // @ID(1)
} SingleEntityRCSReport; // @Extensibility(EXTENSIBLE)

typedef struct SingleMunitionRCSReport
{
    MunitionID St_TargetMunitionID; // @ID(0)
    float F4_TargetRCS_m2; // @ID(1)
} SingleMunitionRCSReport; // @Extensibility(EXTENSIBLE)

typedef struct AreaElementSetting
{
    Longlat St_Pos_RectangleEN; // @ID(0)
    Longlat St_Pos_RectangleES; // @ID(1)
    Longlat St_Pos_RectangleWS; // @ID(2)
    Longlat St_Pos_RectangleWN; // @ID(3)
} AreaElementSetting; // @Extensibility(EXTENSIBLE)

typedef struct AtmosphericElementSetting
{
    WindParas Arr_MissionPlanData[10]; // @ID(0)
    float F4_WindShearVelocity_mDs; // @ID(1)
    float F4_WindShearDirection_deg; // @ID(2)
    unsigned char U1_TurbulenceLevel; // @ID(3)
} AtmosphericElementSetting; // @Extensibility(EXTENSIBLE)

typedef struct NatureElementSetting
{
    unsigned long long U4_Visibility_m; // @ID(0)
    unsigned short U2_LowCloudTopHeight_m; // @ID(1)
    unsigned short U2_LowCloudBaseHeight_m; // @ID(2)
    unsigned char U1_LowCloudLevel; // @ID(3)
    unsigned char U1_LowCloudType; // @ID(4)
    unsigned short U2_MidCloudTopHeight_m; // @ID(5)
    unsigned short U2_MidCloudBaseHeight_m; // @ID(6)
    unsigned char U1_MidCloudLevel; // @ID(7)
    unsigned char U1_MidCloudType; // @ID(8)
    unsigned short U2_HighCloudTopHeight_m; // @ID(9)
    unsigned short U2_HighCloudBaseHeight_m; // @ID(10)
    unsigned char U1_HighCloudLevel; // @ID(11)
    unsigned char U1_HighCloudType; // @ID(12)
    unsigned char U1_WeatherType; // @ID(13)
    unsigned char U1_WeatherIntensity; // @ID(14)
    unsigned char U1_SeaCondition; // @ID(15)
    unsigned char U1_StarAmount; // @ID(16)
    unsigned char U1_StarBright; // @ID(17)
    unsigned char U1_RunwayCondition; // @ID(18)
    unsigned char U1_RunwayLight; // @ID(19)
} NatureElementSetting; // @Extensibility(EXTENSIBLE)

typedef struct ElectromagneticElementSetting
{
    unsigned char U1_ElectroRadIntensity; // @ID(0)
} ElectromagneticElementSetting; // @Extensibility(EXTENSIBLE)

typedef struct SM_MessageHeader
{
    unsigned int U4_Heartbeat; // @ID(0)
    unsigned short U2_EffectiveLength; // @ID(1)
    Timestamp St_PubTime; // @ID(2)
    Timestamp St_GenerateTime; // @ID(3)
} SM_MessageHeader; // @Extensibility(EXTENSIBLE)

typedef struct FacilitiesPowerSupplyStatusData
{
    char ArrU1_FacilitiesPowerSupplyStatus[25]; // @ID(0)
} FacilitiesPowerSupplyStatusData; // @Extensibility(EXTENSIBLE)

typedef struct FlightNavigationStatus_S
{
    unsigned short U2_RAHeight_m; // @ID(0)
    unsigned char U1_RAOtherStatus[1]; // @ID(1)
    unsigned char U1_RAStatusWord[5]; // @ID(2)
    unsigned char U1_RAFailWord1[8]; // @ID(3)
    unsigned char U1_RAFailWord2[8]; // @ID(4)
    unsigned char U1_FAHRS100AssStatus; // @ID(5)
    unsigned char U1_FAHRS100WorkMode; // @ID(6)
    unsigned char U1_FAHRS100WorkStatus; // @ID(7)
    unsigned char U1_FAHRS100AligRemainTime_s; // @ID(8)
} FlightNavigationStatus_S; // @Extensibility(EXTENSIBLE)

typedef struct UnitStatusData
{
    char ArrI1_UnitID[20]; // @ID(0)
    char ArrI1_UnitVersion[9]; // @ID(1)
    unsigned int U4_UnitHeartbeat; // @ID(2)
    unsigned char U1_MemberStatus; // @ID(3)
} UnitStatusData; // @Extensibility(EXTENSIBLE)

typedef struct GeographyReport
{
    EntityID St_ReceiverID; // @ID(0)
    unsigned char U1_GeographyType; // @ID(1)
} GeographyReport; // @Extensibility(EXTENSIBLE)

typedef struct IFFEmitFlag
{
    unsigned char U1_IFFIEmitStatus; // @ID(0)
    unsigned char U1_IFFREmitStatus; // @ID(1)
    unsigned short U2_Spare; // @ID(2)
} IFFEmitFlag; // @Extensibility(EXTENSIBLE)

typedef struct IFFIParas
{
    EntityID E4_IFFREntityID; // @ID(0)
    unsigned char U1_IFFIMode; // @ID(1)
} IFFIParas; // @Extensibility(EXTENSIBLE)

typedef struct IFFRParas
{
    unsigned char U1_IFFRBatchMode; // @ID(0)
    unsigned char U1_IFFRSpecialMode; // @ID(1)
    unsigned char U1_Spare; // @ID(2)
    EntityID E4_IFFIEntityID; // @ID(3)
} IFFRParas; // @Extensibility(EXTENSIBLE)

typedef struct EntityIRIntensityReport
{
    EntityID St_IRIntensityCalEntityID; // @ID(0)
    std::vector<SingleEntityIRIntensityReport> Seq_EntityIRIntensityReport; // @ID(1) /* maximum length = (2000) */
    std::vector<SingleMunitionIRIntensityReport> Seq_MunitionIRIntensityReport; // @ID(2) /* maximum length = (2000) */
} EntityIRIntensityReport; // @Extensibility(EXTENSIBLE)

typedef struct MunitionIRIntensityReport
{
    MunitionID St_IRIntensityCalMunitionID; // @ID(0)
    std::vector<SingleEntityIRIntensityReport> Seq_EntityIRIntensityReport; // @ID(1) /* maximum length = (2000) */
    std::vector<SingleMunitionIRIntensityReport> Seq_MunitionIRIntensityReport; // @ID(2) /* maximum length = (2000) */
} MunitionIRIntensityReport; // @Extensibility(EXTENSIBLE)

typedef struct ImageRTCommand
{
    unsigned char U1_VedioChannelControl; // @ID(0)
    unsigned char U1_CameraMode; // @ID(1)
} ImageRTCommand; // @Extensibility(EXTENSIBLE)

typedef struct Range
{
    float F4_Center_deg; // @ID(0)
    float F4_Coverage_deg; // @ID(1)
} Range; // @Extensibility(EXTENSIBLE)

typedef struct PilotName
{
    char ArrI1_PilotName[4]; // @ID(0)
} PilotName; // @Extensibility(EXTENSIBLE)

typedef struct LVCModeSwitch
{
    unsigned short U2_SceneID; // @ID(0)
    unsigned char U1_LVCMode; // @ID(1)
} LVCModeSwitch; // @Extensibility(EXTENSIBLE)

typedef struct LaserParas
{
    float U1_RadiatingStatus; // @ID(0)
    float F4_Wavelength_um; // @ID(1)
    bool F4_RadiationIntensity_WDsr; // @ID(2)
} LaserParas; // @Extensibility(EXTENSIBLE)

typedef struct LaserDesignatedTarget
{
    EntityID St_DesignatedTargetID; // @ID(0)
} LaserDesignatedTarget; // @Extensibility(EXTENSIBLE)

typedef struct LaserWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    LaserParas St_LaserParas; // @ID(1)
    LaserDesignatedTarget Arr_LaserDesignatedTarget[4]; // @ID(2)
} LaserWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct LinkComEmitStatus
{
    unsigned char U1_LinkComEmitStatus; // @ID(0)
} LinkComEmitStatus; // @Extensibility(EXTENSIBLE)

typedef struct LivePlaneAttribute
{
    unsigned short U2_LivePlaneID; // @ID(0)
    unsigned short U2_EmbedID; // @ID(1)
    unsigned int U4_IFDLProSendID; // @ID(2)
    unsigned int U4_A3ProSendID; // @ID(3)
} LivePlaneAttribute; // @Extensibility(EXTENSIBLE)

typedef struct LivePlaneControlAttribute
{
    unsigned char U1_OperationCommand; // @ID(0)
} LivePlaneControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct MalfunctionSetting_01
{
    unsigned char U1_FaultSetting; // @ID(0)
    unsigned char U1_SubSystemCode; // @ID(1)
    unsigned short U2_SpecialSituationCode; // @ID(2)
} MalfunctionSetting_01; // @Extensibility(EXTENSIBLE)

typedef struct EntityCampSetting
{
    unsigned char U1_EntityCamp; // @ID(0)
} EntityCampSetting; // @Extensibility(EXTENSIBLE)

typedef struct MemberInitFlightParas
{
    EntityControlAttribute St_EntityID; // @ID(0)
    InitFlightParas St_InitFlightParas; // @ID(1)
} MemberInitFlightParas; // @Extensibility(EXTENSIBLE)

typedef struct MalfunctionSetting
{
    bool ArrB1_FCSFault[600]; // @ID(0)
    bool ArrB1_USIMFault[600]; // @ID(1)
    bool ArrB1_MSFault[600]; // @ID(2)
    bool ArrB1_CCSFault[100]; // @ID(3)
    bool ArrB1_GCSFault[100]; // @ID(4)
    bool ArrB1_SpecialFault[600]; // @ID(5)
} MalfunctionSetting; // @Extensibility(EXTENSIBLE)

typedef struct SimulatorModeSetting
{
    bool B1_ReviveOnPlace; // @ID(0)
    bool B1_GodMode; // @ID(1)
    bool B1_TransparentSituation; // @ID(2)
} SimulatorModeSetting; // @Extensibility(EXTENSIBLE)

typedef struct SimulationSetting
{
    unsigned short ArrU2_GenSimSetting[30]; // @ID(0)
    unsigned short ArrU2_ModelSimSetting[30]; // @ID(1)
} SimulationSetting; // @Extensibility(EXTENSIBLE)

typedef struct StoreSetting
{
    unsigned short Arr_StoreType[40]; // @ID(0)
    unsigned char Arr_StoreNumber[40]; // @ID(1)
} StoreSetting; // @Extensibility(EXTENSIBLE)

typedef struct MemberStoreSettingParas
{
    EntityControlAttribute St_EntityID; // @ID(0)
    StoreSetting St_StoreSetting; // @ID(1)
} MemberStoreSettingParas; // @Extensibility(EXTENSIBLE)

typedef struct MslGuidanceInfoIFDL
{
    EntityID St_EntityID; // @ID(0)
    bool B1_VaildGuide; // @ID(1)
    unsigned int U4_MessageLength; // @ID(2)
    unsigned short U2_PlaneType; // @ID(3)
    unsigned char U1_MslNum; // @ID(4)
    unsigned char U1_MslType[6]; // @ID(5)
    unsigned char U1_StoreStationID[6]; // @ID(6)
    unsigned char U1_MslGuidanceDataIFDL[1500]; // @ID(7)
} MslGuidanceInfoIFDL; // @Extensibility(EXTENSIBLE)

typedef struct MslGuidanceLinkReportIFDL
{
    EntityID St_EntityID; // @ID(0)
    unsigned int U4_MessageLength; // @ID(1)
    unsigned short U2_PlaneType; // @ID(2)
    unsigned char U1_MslNum; // @ID(3)
    unsigned char U1_MslType[14]; // @ID(4)
    unsigned char U1_StoreStationID[14]; // @ID(5)
    unsigned char U1_MSLLinkDataIFDL[1500]; // @ID(6)
} MslGuidanceLinkReportIFDL; // @Extensibility(EXTENSIBLE)

typedef struct MunitionDisplay
{
    MunitionID St_MunitionID; // @ID(0)
    float F4_DistanceMslTarget; // @ID(1)
    float F4_WpnVelTotal; // @ID(2)
    unsigned char U1_TargetDestructionResult; // @ID(3)
} MunitionDisplay; // @Extensibility(EXTENSIBLE)

typedef struct MunitionKillNotify
{
    MunitionID St_MunitionID; // @ID(0)
    EntityID St_TargetID; // @ID(1)
    unsigned char U1_HitResult; // @ID(2)
    unsigned char U1_EndReason; // @ID(3)
} MunitionKillNotify; // @Extensibility(EXTENSIBLE)

typedef struct MunitionRadarSeekerStatus
{
    unsigned char U1_RadiatingStatus; // @ID(0)
    float F4_OperatingRF_MHz; // @ID(1)
} MunitionRadarSeekerStatus; // @Extensibility(EXTENSIBLE)

typedef struct MunitionRadarSeekerTrackTarget
{
    EntityID St_TrackTargetID; // @ID(0)
    unsigned char U1_TrackLevel; // @ID(1)
    EntityID St_GuidanceEntityID; // @ID(2)
} MunitionRadarSeekerTrackTarget; // @Extensibility(EXTENSIBLE)

typedef struct MunitionIRSeekerStatus
{
    unsigned char U1_SearchingStatus; // @ID(0)
    unsigned char U1_InfraredBand; // @ID(1)
} MunitionIRSeekerStatus; // @Extensibility(EXTENSIBLE)

typedef struct MunitionIRTrackTarget
{
    EntityID St_TrackTargetID; // @ID(0)
    unsigned char U1_TrackLevel; // @ID(1)
} MunitionIRTrackTarget; // @Extensibility(EXTENSIBLE)

typedef struct MunitionAttribute
{
    MunitionID St_MunitionID; // @ID(0)
    EntityID St_LaunchEntityID; // @ID(1)
    unsigned char U1_GuideType; // @ID(2)
    unsigned char U1_WeaponClass; // @ID(3)
    unsigned short U2_MunitionType; // @ID(4)
} MunitionAttribute; // @Extensibility(EXTENSIBLE)

typedef struct MunitionTSPI
{
    MunitionAttribute St_MunitionAttribute; // @ID(0)
    EntityPosVelAccAtt St_EntityPosVelAccAtt; // @ID(1)
} MunitionTSPI; // @Extensibility(EXTENSIBLE)

typedef struct MunitionEngineStatus
{
    unsigned char U1_MunitionEngineStatus; // @ID(0)
} MunitionEngineStatus; // @Extensibility(EXTENSIBLE)

typedef struct MunitionSeekerStatus
{
    MunitionRadarSeekerStatus St_MunitionRadarSeekerStatus; // @ID(0)
    MunitionRadarSeekerTrackTarget St_MunitionRadarSeekerTrackTarget; // @ID(1)
    MunitionIRSeekerStatus St_MunitionIRSeekerStatus; // @ID(2)
    MunitionIRTrackTarget St_MunitionIRTrackTarget; // @ID(3)
} MunitionSeekerStatus; // @Extensibility(EXTENSIBLE)

typedef struct MunitionWorkingParas
{
    MunitionAttribute St_MunitionAttribute; // @ID(0)
    MunitionEngineStatus St_MunitionEngineStatus; // @ID(1)
    MunitionSeekerStatus St_MunitionSeekerStatus; // @ID(2)
} MunitionWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct NatureReport
{
    EntityID St_ReceiverEntityID; // @ID(0)
    unsigned long long U4_Visibility_m; // @ID(1)
    unsigned short U2_LowCloudTopHeight_m; // @ID(2)
    unsigned short U2_LowCloudBaseHeight_m; // @ID(3)
    unsigned char U1_LowCloudLevel; // @ID(4)
    unsigned char U1_LowCloudType; // @ID(5)
    unsigned short U2_MidCloudTopHeight_m; // @ID(6)
    unsigned short U2_MidCloudBaseHeight_m; // @ID(7)
    unsigned char U1_MidCloudLevel; // @ID(8)
    unsigned char U1_MidCloudType; // @ID(9)
    unsigned short U2_HighCloudTopHeight_m; // @ID(10)
    unsigned short U2_HighCloudBaseHeight_m; // @ID(11)
    unsigned char U1_HighCloudLevel; // @ID(12)
    unsigned char U1_HighCloudType; // @ID(13)
    unsigned char U1_WeatherType; // @ID(14)
    unsigned char U1_WeatherIntensity; // @ID(15)
    unsigned char U1_SeaCondition; // @ID(16)
    unsigned char U1_Season; // @ID(17)
    unsigned char U1_StarAmount; // @ID(18)
    unsigned char U1_StarBright; // @ID(19)
    unsigned char U1_RunwayCondition; // @ID(20)
    unsigned char U1_RunwayLight; // @ID(21)
} NatureReport; // @Extensibility(EXTENSIBLE)

typedef struct NavigationData_S
{
    double D8_Longitude_deg_CGCS; // @ID(0)
    double D8_Latitude_deg_CGCS; // @ID(1)
    float F4_Altitude_m; // @ID(2)
    double D8_VelocityNorth_mDs_NED; // @ID(3)
    double D8_VelocityEast_mDs_NED; // @ID(4)
    double D8_VelocityUp_mDs_NED; // @ID(5)
    float F4_OverloadX_G_NED; // @ID(6)
    float F4_OverloadY_G_NED; // @ID(7)
    float F4_OverloadZ_G_NED; // @ID(8)
    float F4_AccelerationX_mDs2_NED; // @ID(9)
    float F4_AccelerationY_mDs2_NED; // @ID(10)
    float F4_AccelerationZ_mDs2_NED; // @ID(11)
    float F4_AzimuthAngle_deg; // @ID(12)
    float F4_Psi_deg; // @ID(13)
    float F4_Theta_deg; // @ID(14)
    float F4_Phi_deg; // @ID(15)
    double D8_AngleVelocityX_degDs_BODY; // @ID(16)
    double D8_AngleVelocityY_degDs_BODY; // @ID(17)
    double D8_AngleVelocityZ_degDs_BODY; // @ID(18)
    float F4_TrueStaticPressure_kgDm2; // @ID(19)
    float F4_TrueAttackAngle_deg; // @ID(20)
    float F4_TrueSideslipAngle_deg; // @ID(21)
    float F4_TrueAirspeed_mDs; // @ID(22)
    float F4_AdsAltitude_m; // @ID(23)
    float F4_RelativeAdsAltitude_m; // @ID(24)
    float F4_Mach; // @ID(25)
    float F4_CalculateAirspeed_mDs; // @ID(26)
    float F4_VerticalSpeed_mDs; // @ID(27)
    float F4_PressureRate; // @ID(28)
    float F4_DensityRate; // @ID(29)
    float F4_AdsTotalTemprature_C; // @ID(30)
    float F4_AdsStaticTemprature_C; // @ID(31)
    bool F4_LiveFlag; // @ID(32)
    float F4_Gama_deg; // @ID(33)
    double D8_PhaiVelocity_degDs; // @ID(34)
    double D8_ThetaVelocity_degDs; // @ID(35)
    double D8_PesaiVelocity_degDs; // @ID(36)
    float F4_VelocityX_mDs2_BODY; // @ID(37)
    float F4_VelocityY_mDs2_BODY; // @ID(38)
    float F4_VelocityZ_mDs2_BODY; // @ID(39)
    double D8_AccelerationX_mDs2_BODY; // @ID(40)
    double D8_AccelerationY_mDs2_BODY; // @ID(41)
    double D8_AccelerationZ_mDs2_BODY; // @ID(42)
    float F4_WindVelocity_mDs_BODY; // @ID(43)
    float F4_WindDirection_deg_BODY; // @ID(44)
    float F4_WindVelocityX_mDs_NED; // @ID(45)
    float F4_WindVelocityY_mDs_NED; // @ID(46)
    float F4_WindVelocityZ_mDs_NED; // @ID(47)
    double D8_phaidot_deg; // @ID(48)
    double D8_thetadot_deg; // @ID(49)
    double D8_pesaidot_deg; // @ID(50)
    unsigned char U1_RAVMCCMD[2]; // @ID(51)
    unsigned char U1_WOW; // @ID(52)
    unsigned char U1_FAHRSAimCmd; // @ID(53)
    unsigned char U1_FAHRSConsBDMILCmd; // @ID(54)
    unsigned char U1_FAHRSConsNavModeCmd; // @ID(55)
    bool B1_FAHRSINSValid; // @ID(56)
    bool B1_FAHRSSATValid; // @ID(57)
    bool B1_FAHRSADSValid; // @ID(58)
    bool B1_FAHRSWOW; // @ID(59)
    bool B1_FAHRSANMBDJValid; // @ID(60)
    bool B1_FAHRSANMBDMValid; // @ID(61)
    bool B1_FAHRSANMGPSValid; // @ID(62)
} NavigationData_S; // @Extensibility(EXTENSIBLE)

typedef struct NewSceneCreate
{
    unsigned short U2_SceneID; // @ID(0)
} NewSceneCreate; // @Extensibility(EXTENSIBLE)

typedef struct SceneStatus
{
    unsigned char U1_SceneStatus; // @ID(0)
} SceneStatus; // @Extensibility(EXTENSIBLE)

typedef struct SceneInfo
{
    SceneID S2_SceneID; // @ID(0)
    char U1_SceneName[20]; // @ID(1)
    char U2_InstructorName[16]; // @ID(2)
    unsigned short U2_MemberAmount; // @ID(3)
    unsigned char U1_SceneType; // @ID(4)
    SceneStatus S1_SceneStatus; // @ID(5)
} SceneInfo; // @Extensibility(EXTENSIBLE)

typedef struct TgtParasValidity
{
    bool B1_ValidityTgtDistance; // @ID(0)
    bool B1_ValidityTgtAz; // @ID(1)
    bool B1_ValidityTgtEl; // @ID(2)
    bool B1_ValidityTgtVelocity; // @ID(3)
} TgtParasValidity; // @Extensibility(EXTENSIBLE)

typedef struct TgtPrecision
{
    unsigned char U1_RangePrecision; // @ID(0)
    unsigned char U1_VelocityPrecision; // @ID(1)
    unsigned char U1_AngularPrecision; // @ID(2)
    unsigned char U1_TgtDataManualInputLable; // @ID(3)
} TgtPrecision; // @Extensibility(EXTENSIBLE)

typedef struct ChaffJam
{
    unsigned short U2_ChaffNum; // @ID(0)
    bool B1_ChaffStatus; // @ID(1)
} ChaffJam; // @Extensibility(EXTENSIBLE)

typedef struct InfraredJam
{
    bool B1_InfraredStatus; // @ID(0)
    float F4_InfraredIntensity_kWDsr; // @ID(1)
    Range St_InfraredWaveRange; // @ID(2)
} InfraredJam; // @Extensibility(EXTENSIBLE)

typedef struct DecoyJam
{
    bool B1_DecoyStatus; // @ID(0)
    float F4_DecoyDis_m; // @ID(1)
    float F4_DecoyRF_Mhz; // @ID(2)
} DecoyJam; // @Extensibility(EXTENSIBLE)

typedef struct PassiveJamWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    ChaffJam St_ChaffJam; // @ID(1)
    InfraredJam St_InfraredJam; // @ID(2)
    DecoyJam St_DecoyJam; // @ID(3)
} PassiveJamWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct PowerAttribute
{
    unsigned char U1_PowerCategory; // @ID(0)
} PowerAttribute; // @Extensibility(EXTENSIBLE)

typedef struct PowerControl
{
    unsigned char U1_PowerControl; // @ID(0)
} PowerControl; // @Extensibility(EXTENSIBLE)

typedef struct PowerStatus
{
    unsigned char U1_PowerStatus; // @ID(0)
    unsigned char U1_PowerFailure; // @ID(1)
    unsigned char U1_FailureType; // @ID(2)
} PowerStatus; // @Extensibility(EXTENSIBLE)

typedef struct EntityRCSReport
{
    EntityID St_RCSCalEntityID; // @ID(0)
    std::vector<SingleEntityRCSReport> Seq_EntityRCSReport; // @ID(1) /* maximum length = (2000) */
    std::vector<SingleMunitionRCSReport> Seq_MunitionRCSReport; // @ID(2) /* maximum length = (2000) */
} EntityRCSReport; // @Extensibility(EXTENSIBLE)

typedef struct MunitionRCSReport
{
    MunitionID St_RCSCalMunitionID; // @ID(0)
    std::vector<SingleEntityRCSReport> Seq_EntityRCSReport; // @ID(1) /* maximum length = (2000) */
    std::vector<SingleMunitionRCSReport> Seq_MunitionRCSReport; // @ID(2) /* maximum length = (2000) */
} MunitionRCSReport; // @Extensibility(EXTENSIBLE)

typedef struct SARImageControl
{
    unsigned char U1_ImageRefreshCount; // @ID(0)
    unsigned char U1_ImageOffFlag; // @ID(1)
    unsigned char U1_ImageSaveCount; // @ID(2)
    unsigned char U1_ImageDeleteCount; // @ID(3)
    unsigned char U1_ImageReviewStatus; // @ID(4)
    unsigned char U1_ImageViewing; // @ID(5)
} SARImageControl; // @Extensibility(EXTENSIBLE)

typedef struct SARImageControlPara
{
    SARImagePosition St_SARImageCenterPosition; // @ID(0)
    float F4_SARImageResolution_m; // @ID(1)
    float F4_SARImageGenerateTime; // @ID(2)
    unsigned char U1_ImageIndexID; // @ID(3)
    float F4_ViewingNorth_deg; // @ID(4)
} SARImageControlPara; // @Extensibility(EXTENSIBLE)

typedef struct ExpandPara
{
    unsigned short U2_ExpPositionX; // @ID(0)
    unsigned short U2_ExpPositionY; // @ID(1)
    unsigned char U1_ExpActive; // @ID(2)
    unsigned char U1_ExpNumber; // @ID(3)
    double D8_Longitude_deg_CGCS; // @ID(4)
    double D8_Latitude_deg_CGCS; // @ID(5)
} ExpandPara; // @Extensibility(EXTENSIBLE)

typedef struct ZoomPara
{
    unsigned short U2_ZoomPositionX; // @ID(0)
    unsigned short U2_ZoomPositionY; // @ID(1)
    double D8_Longitude_deg_CGCS; // @ID(2)
    double D8_Latitude_deg_CGCS; // @ID(3)
} ZoomPara; // @Extensibility(EXTENSIBLE)

typedef struct SARImageEffect
{
    unsigned char U1_ResolutionDegrade; // @ID(0)
    unsigned char U1_Contrast; // @ID(1)
    unsigned char U1_Gian; // @ID(2)
} SARImageEffect; // @Extensibility(EXTENSIBLE)

typedef struct RadarScanDrive
{
    double D8_AZCenter_deg; // @ID(0)
    double D8_ELCenter_deg; // @ID(1)
    double D8_AZCover_deg; // @ID(2)
    double D8_ELCover_deg; // @ID(3)
} RadarScanDrive; // @Extensibility(EXTENSIBLE)

typedef struct RadarImageControl
{
    unsigned char U1_ImageGenerate; // @ID(0)
    unsigned char U1_ImageFreeze; // @ID(1)
    unsigned char U1_RadarASWorkMode; // @ID(2)
} RadarImageControl; // @Extensibility(EXTENSIBLE)

typedef struct RadarImageGeneral
{
    RadarScanDrive St_ScanField_BODY; // @ID(0)
    RadarScanDrive St_ScanField_NED; // @ID(1)
    RadarScanDrive St_BeamPara_BODY; // @ID(2)
    float F4_RangeScale_km; // @ID(3)
    ExpandPara St_ExpandPara; // @ID(4)
} RadarImageGeneral; // @Extensibility(EXTENSIBLE)

typedef struct RBMImageEffect
{
    unsigned char U2_DisguiseColorFlag; // @ID(0)
    unsigned char U1_Gian; // @ID(1)
} RBMImageEffect; // @Extensibility(EXTENSIBLE)

typedef struct ISARImagePara
{
    unsigned char U1_ImageGenerate; // @ID(0)
    EntityID St_EntityID; // @ID(1)
} ISARImagePara; // @Extensibility(EXTENSIBLE)

typedef struct SARImagePara
{
    SARImageControl St_SARImageControl; // @ID(0)
    SARImageControlPara St_SARImageControlPara; // @ID(1)
    ExpandPara St_ExpandPara; // @ID(2)
    ZoomPara St_ZoomPara; // @ID(3)
    SARImageEffect St_SARImageEffect; // @ID(4)
} SARImagePara; // @Extensibility(EXTENSIBLE)

typedef struct EffectImagePara
{
    unsigned short U2_ClearSufaceHeight_m; // @ID(0)
} EffectImagePara; // @Extensibility(EXTENSIBLE)

typedef struct RadarStatus
{
    unsigned char U1_RadiatingStatus; // @ID(0)
    unsigned char U1_LPIMode; // @ID(1)
    unsigned short U1_MaskTyp; // @ID(2)
    unsigned char U1_Polarization; // @ID(3)
    unsigned char U1_WorkMode; // @ID(4)
    float F4_OperatingRF_MHz; // @ID(5)
    float F4_RadiatingPower_W; // @ID(6)
} RadarStatus; // @Extensibility(EXTENSIBLE)

typedef struct RadarScanParas
{
    unsigned char U1_StableMode; // @ID(0)
    Range St_AzimuthRange; // @ID(1)
    Range St_ElevationRange; // @ID(2)
    float F4_DetectRange_m; // @ID(3)
} RadarScanParas; // @Extensibility(EXTENSIBLE)

typedef struct RadarGuidanceStatus
{
    unsigned char U1_GuidanceStatus; // @ID(0)
    float F4_GuidanceRange_m; // @ID(1)
} RadarGuidanceStatus; // @Extensibility(EXTENSIBLE)

typedef struct RadarTrackTarget
{
    EntityID St_TrackTargetID; // @ID(0)
    unsigned char U1_TrackLevel; // @ID(1)
    unsigned char U1_VehicleID; // @ID(2)
} RadarTrackTarget; // @Extensibility(EXTENSIBLE)

typedef struct RadarWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    RadarStatus St_RadarStatus; // @ID(1)
    RadarScanParas Arr_RadarScanParas[5]; // @ID(2)
    RadarGuidanceStatus St_RadarGuidanceStatus; // @ID(3)
    RadarTrackTarget Arr_RadarTrackTarget[32]; // @ID(4)
} RadarWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SceneStatusControl
{
    unsigned char U1_ControlCMD; // @ID(0)
} SceneStatusControl; // @Extensibility(EXTENSIBLE)

typedef struct CustomAirportAttribute
{
    Position St_RunwayPosition; // @ID(0)
    float F4_RunwayCourse_deg; // @ID(1)
    unsigned short F4_RunwayWidth_m; // @ID(2)
    unsigned short F4_RunwayLength_m; // @ID(3)
} CustomAirportAttribute; // @Extensibility(EXTENSIBLE)

typedef struct SingleCustomAirportSetting
{
    EntityControlAttribute St_EntityControlAttribute; // @ID(0)
    CustomAirportAttribute St_CustomAirportSetting; // @ID(1)
} SingleCustomAirportSetting; // @Extensibility(EXTENSIBLE)

typedef struct RangeControlAttribute
{
    bool B1_RangeControl; // @ID(0)
} RangeControlAttribute; // @Extensibility(EXTENSIBLE)

typedef struct EnvAttributeParas
{
    AreaElementSetting St_AreaElementSetting; // @ID(0)
    AtmosphericElementSetting St_AtmosphericElement; // @ID(1)
    NatureElementSetting St_NatureElement; // @ID(2)
    ElectromagneticElementSetting St_ElectromagneticElementSetting; // @ID(3)
} EnvAttributeParas; // @Extensibility(EXTENSIBLE)

typedef struct InitFormationList
{
    unsigned char U1_LinkDataType; // @ID(0)
    unsigned char U1_BelongCamp; // @ID(1)
    unsigned char U1_LinkTeamNo; // @ID(2)
    EntityID St_MasterEntityID; // @ID(3)
    EntityID St_JointMasterEntityID; // @ID(4)
    unsigned char Arr_MemberNo[400]; // @ID(5)
    EntityID Arr_EntityID[400]; // @ID(6)
    PilotName Arr_PilotName[400]; // @ID(7)
} InitFormationList; // @Extensibility(EXTENSIBLE)

typedef struct TimeElementSetting
{
    unsigned char U1_Month; // @ID(0)
    unsigned char U1_Day; // @ID(1)
    unsigned char U1_Hour; // @ID(2)
    unsigned char U1_Minute; // @ID(3)
    unsigned char U1_TimeSpeed; // @ID(4)
} TimeElementSetting; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData1JIDSMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData1 St_AALinkData1; // @ID(2)
} AALinkData1JIDSMsg; // @Extensibility(EXTENSIBLE)

typedef struct MessageValid
{
    bool B1_MessageDataValid; // @ID(0)
} MessageValid; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData1VUMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData1 St_AALinkData1; // @ID(2)
} AALinkData1VUMsg; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData2IFDLMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData2 St_AALinkData2; // @ID(2)
} AALinkData2IFDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct AALinkData2WCDLMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData2 St_AALinkData2; // @ID(2)
} AALinkData2WCDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecActiveJamWorkingParas
{
    MessageHeader St_MessageHeader; // @ID(0)
    ActiveJamWorkingParas St_ActiveJamWorkingParas; // @ID(1)
} SecActiveJamWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SecEnAttrVApp
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    VirtualAppearance St_VirtualAppearance; // @ID(2)
} SecEnAttrVApp; // @Extensibility(EXTENSIBLE)

typedef struct SecEnAttrPVAA
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    EntityPosVelAccAtt St_EntityPosVelAccAtt; // @ID(2)
} SecEnAttrPVAA; // @Extensibility(EXTENSIBLE)

typedef struct IFFEmitFlagParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFEmitFlag St_IFFEmitFlag; // @ID(2)
} IFFEmitFlagParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct IFFIntgParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFIParas St_IFFIParas; // @ID(2)
} IFFIntgParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct IFFRespParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFRParas St_IFFRParas; // @ID(2)
} IFFRespParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecLaserWorkingParas
{
    MessageHeader St_MessageHeader; // @ID(0)
    LaserWorkingParas St_LaserWorkingParas; // @ID(1)
} SecLaserWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct LinkComEmitStatusParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    LinkComEmitStatus St_LinkComEmitStatus; // @ID(2)
} LinkComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionTSPI
{
    MunitionAttribute St_MunitionAttribute; // @ID(0)
    EntityPosVelAccAtt St_EntityPosVelAccAtt; // @ID(1)
    MessageHeader St_MessageHeader; // @ID(2)
} SecMunitionTSPI; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionWorkingParas
{
    MunitionAttribute St_MunitionAttribute; // @ID(0)
    MunitionEngineStatus St_MunitionEngineStatus; // @ID(1)
    MunitionSeekerStatus St_MunitionSeekerStatus; // @ID(2)
    MessageHeader St_MessageHeader; // @ID(3)
} SecMunitionWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SecPassiveJamWorkingParas
{
    MessageHeader St_MessageHeader; // @ID(0)
    PassiveJamWorkingParas St_PassiveJamWorkingParas; // @ID(1)
} SecPassiveJamWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarWorkingParas
{
    MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} SecRadarWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct TacanParas
{
    unsigned char U1_TacanStatus; // @ID(0)
    unsigned char U1_TacanEmitStatus; // @ID(1)
    unsigned char U1_TacanBand; // @ID(2)
    unsigned char U1_TacanOperationMode; // @ID(3)
    unsigned short U2_TacanChannel; // @ID(4)
    unsigned short U2_Spare; // @ID(5)
} TacanParas; // @Extensibility(EXTENSIBLE)

typedef struct SecTacanWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    TacanParas St_TacanParas; // @ID(2)
} SecTacanWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VoiceComEmitStatus
{
    unsigned char U1_VoiceComEmitStatus; // @ID(0)
} VoiceComEmitStatus; // @Extensibility(EXTENSIBLE)

typedef struct VoiceComEmitStatusParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    VoiceComEmitStatus St_VoiceComEmitStatus; // @ID(2)
} VoiceComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct EOImageShowArea
{
    float F4_AZLOS_deg_BODY; // @ID(0)
    float F4_ELLOS_deg_BODY; // @ID(1)
    float F4_horizontalCover_deg; // @ID(2)
    float F4_verticalCover_deg; // @ID(3)
} EOImageShowArea; // @Extensibility(EXTENSIBLE)

typedef struct EOImageModePara
{
    unsigned char U1_ImageMode; // @ID(0)
} EOImageModePara; // @Extensibility(EXTENSIBLE)

typedef struct EOImageEffect
{
    unsigned char U1_VideoSource; // @ID(0)
    unsigned char U1_VideoPolar; // @ID(1)
    unsigned char U1_Contrast; // @ID(2)
    unsigned char U1_Gray; // @ID(3)
    unsigned char U1_DigitalZoom; // @ID(4)
} EOImageEffect; // @Extensibility(EXTENSIBLE)

typedef struct EOImageTrackPara
{
    EntityID St_EntityID; // @ID(0)
    float F4_TargetDis; // @ID(1)
    unsigned short U2_ShowEntityID; // @ID(2)
} EOImageTrackPara; // @Extensibility(EXTENSIBLE)

typedef struct DatalinkKeepAlive
{
    unsigned char U1_CNISubsysMode; // @ID(0)
    unsigned char U1_VULinkFcnState; // @ID(1)
    unsigned char U1_VULinkEMStatus; // @ID(2)
    unsigned char U1_JIDSLinkFcnState; // @ID(3)
    unsigned char U1_JIDSLinkEMStatus; // @ID(4)
    unsigned char U1_IFDLLinkFcnState; // @ID(5)
    unsigned char U1_IFDLLinkEMStatus; // @ID(6)
    unsigned char U1_WCDLLinkFcnState; // @ID(7)
    unsigned char U1_WCDLLinkEMStatus; // @ID(8)
    unsigned char U1_SATLinkFcnState; // @ID(9)
    unsigned char U1_SATLinkEMStatus; // @ID(10)
    unsigned char U1_CNIPowerMode; // @ID(11)
} DatalinkKeepAlive; // @Extensibility(EXTENSIBLE)

typedef struct EOImageState
{
    unsigned char U1_IRSensor; // @ID(0)
    unsigned char U1_TVState; // @ID(1)
    unsigned char U1_ImageMode; // @ID(2)
    unsigned char U1_Channel; // @ID(3)
} EOImageState; // @Extensibility(EXTENSIBLE)

typedef struct EOImageParasIS
{
    Timestamp St_ImageTime; // @ID(0)
    unsigned int U4_ImgId; // @ID(1)
    unsigned short U2_EOCycleNo; // @ID(2)
    unsigned short U2_LineNo; // @ID(3)
    unsigned short U2_EO_LineNo; // @ID(4)
    unsigned int U4_WideCover; // @ID(5)
    float F4_ELLOS_deg_BODY; // @ID(6)
    float F4_AZLOS_deg_BODY; // @ID(7)
    float F4_verticalCover_deg; // @ID(8)
    float F4_horizontalCover_deg; // @ID(9)
    unsigned char U1_CouseTgtCover; // @ID(10)
    unsigned char U1_BesideTgtCover; // @ID(11)
    unsigned short U2_CurResolution; // @ID(12)
    unsigned short U2_GroundResolution; // @ID(13)
    Position St_ImgCenterPosition; // @ID(14)
    Longlat St_ImgLeftUp; // @ID(15)
    Longlat St_ImgLeftDown; // @ID(16)
    Longlat St_ImgRightUp; // @ID(17)
    Longlat St_ImgRightDown; // @ID(18)
    unsigned short U2_TakeTimes; // @ID(19)
    unsigned short U2_FocalLength; // @ID(20)
    unsigned short U2_ExposureTime; // @ID(21)
    unsigned char U1_ImpotentTag; // @ID(22)
    Longlat St_ImgCenter; // @ID(23)
    EntityPosVelAccAtt St_AcParas; // @ID(24)
    std::vector<char> Seq_Mission; // @ID(25) /* maximum length = (20) */
} EOImageParasIS; // @Extensibility(EXTENSIBLE)

typedef struct EOImageModifyPara
{
    unsigned char I1_LightValueLight; // @ID(0)
    unsigned char I1_FocusValueLight; // @ID(1)
    unsigned char U1_LightMistEliminate; // @ID(2)
    unsigned char U1_LightEnhance_Mode; // @ID(3)
    unsigned char I1_LightValueInfrared; // @ID(4)
    unsigned char I1_FocusValueInfrared; // @ID(5)
    unsigned char U1_VideoPolar; // @ID(6)
    unsigned char U1_InfraredEnhanceMode; // @ID(7)
} EOImageModifyPara; // @Extensibility(EXTENSIBLE)

typedef struct EOTgtPara
{
    EntityID St_EntityID; // @ID(0)
} EOTgtPara; // @Extensibility(EXTENSIBLE)

typedef struct TeamMemberInfo
{
    unsigned char U1_LinkTeamNo; // @ID(0)
    unsigned char U1_IsSelf; // @ID(1)
    unsigned char U1_MemberNo; // @ID(2)
    unsigned short U2_MemberNetID; // @ID(3)
    EntityID St_EntityID; // @ID(4)
} TeamMemberInfo; // @Extensibility(EXTENSIBLE)

typedef struct EOImagePlaybackPara
{
    unsigned char U1_ImagePlaybackFlag; // @ID(0)
    EntityID St_EntityID; // @ID(1)
} EOImagePlaybackPara; // @Extensibility(EXTENSIBLE)

typedef struct PL10SeekerParas
{
    unsigned char U1_StoreStationId; // @ID(0)
    unsigned char U1_StoreWpnTypes; // @ID(1)
    bool B1_NtsWeapon; // @ID(2)
    unsigned char U1_IrOperateCmd; // @ID(3)
    unsigned char U1_IrSlavedModel; // @ID(4)
    unsigned char U1_CatchedAllowed; // @ID(5)
    bool B1_ValiditySrmAoc; // @ID(6)
    unsigned char U1_SrmAocValue; // @ID(7)
} PL10SeekerParas; // @Extensibility(EXTENSIBLE)

typedef struct SimType
{
    unsigned short U2_EntityType; // @ID(0)
} SimType; // @Extensibility(EXTENSIBLE)

typedef struct GuideParas
{
    bool B1_ValidGuide; // @ID(0)
    EntityID St_RdrLockIdLatest; // @ID(1)
} GuideParas; // @Extensibility(EXTENSIBLE)

typedef struct PL10AGuideParas
{
    unsigned long long U8_DataGenratedTime; // @ID(0)
    unsigned char U1_StoreWpnTypes; // @ID(1)
    unsigned char U1_StoreStationId; // @ID(2)
    unsigned char U1_TargetPhysicsSize; // @ID(3)
    bool B1_TakeTurnsFlag; // @ID(4)
    bool B1_ValidityAboveGroundHeight; // @ID(5)
    unsigned char U1_GuidanceMemId; // @ID(6)
    unsigned char U1_TargetRcsType; // @ID(7)
    bool B1_IfTakeTurns; // @ID(8)
    unsigned char U1_AxisSign; // @ID(9)
    unsigned char U1_ValidityTgtAngle; // @ID(10)
    unsigned char U1_ValidityTgtVelocity; // @ID(11)
    unsigned char U1_ValidityTgtDistance; // @ID(12)
    float F4_TgtAngleError; // @ID(13)
    float F4_TgtVelocityError; // @ID(14)
    short I2_TgtDistanceError; // @ID(15)
    short I2_FusedTgtId; // @ID(16)
    unsigned char U1_TargetTrackState; // @ID(17)
    unsigned char U1_LaunchMode; // @ID(18)
    unsigned short U2_TerrainAltitude; // @ID(19)
    float F4_AcPositionDataLat; // @ID(20)
    float F4_AcPositionDataLon; // @ID(21)
    float F4_AcPositionDataAlt; // @ID(22)
    float F4_AcVelocityCGCS2000X; // @ID(23)
    float F4_AcVelocityCGCS2000Y; // @ID(24)
    float F4_AcVelocityCGCS2000Z; // @ID(25)
    float F4_TgtLongitude; // @ID(26)
    float F4_TgtLatitude; // @ID(27)
    float F4_TgtAltitude; // @ID(28)
    float F4_TgtVelocityCGCS2000X; // @ID(29)
    float F4_TgtVelocityCGCS2000Y; // @ID(30)
    float F4_TgtVelocityCGCS2000Z; // @ID(31)
    EntityID E4_CgfTgtId; // @ID(32)
} PL10AGuideParas; // @Extensibility(EXTENSIBLE)

typedef struct PL10TgtSetParas
{
    float F4_MissileSeekerAzimuth; // @ID(0)
    float F4_MissileSeekerPitch; // @ID(1)
} PL10TgtSetParas; // @Extensibility(EXTENSIBLE)

typedef struct PL15MslMissionParas
{
    unsigned char U1_CoordinateBulidNum; // @ID(0)
} PL15MslMissionParas; // @Extensibility(EXTENSIBLE)

typedef struct PL15MslCountParas
{
    LinearVelocity St_Vel; // @ID(0)
    float F4_PosN; // @ID(1)
    float F4_PosU; // @ID(2)
    float F4_PosE; // @ID(3)
    float F4_BullsEyeLon; // @ID(4)
    float F4_BullsEyeLat; // @ID(5)
} PL15MslCountParas; // @Extensibility(EXTENSIBLE)

typedef struct PL15GuideParas
{
    unsigned long long U8_DataGenratedTime; // @ID(0)
    unsigned char U1_StoreWpnTypes; // @ID(1)
    unsigned char U1_StoreStationId; // @ID(2)
    unsigned char U1_TargetPhysicsSize; // @ID(3)
    unsigned char U1_TgtPhysicsSizeCrediable; // @ID(4)
    unsigned char U1_RangePrecise; // @ID(5)
    unsigned char U1_VelocityPrecise; // @ID(6)
    unsigned char U1_AngularPrecise; // @ID(7)
    unsigned char U1_TgtMaualInputFlag; // @ID(8)
    unsigned char U1_ValidityTgtDistance; // @ID(9)
    unsigned char U1_ValidityTgtAz; // @ID(10)
    unsigned char U1_ValidityTgtEl; // @ID(11)
    unsigned char U1_ValidityTgtVelocity; // @ID(12)
    unsigned char U1_TargetRcsType; // @ID(13)
    unsigned char U1_TgtSizeCrediableDegree; // @ID(14)
    unsigned char U1_GroupTgtAttackSign; // @ID(15)
    unsigned char U1_AxisSign; // @ID(16)
    float F4_AcInertiaPositionNorth; // @ID(17)
    float F4_AcInertiaPositionUp; // @ID(18)
    float F4_AcInertiaPositionEast; // @ID(19)
    float F4_AcInertiaVelNorth; // @ID(20)
    float F4_AcInertiaVelUp; // @ID(21)
    float F4_AcInertiaVelEast; // @ID(22)
    float F4_TgtInertiaPositionNorth; // @ID(23)
    float F4_TgtInertiaPositionUp; // @ID(24)
    float F4_TgtInertiaPositionEast; // @ID(25)
    float F4_TgtInertiaVelNorth; // @ID(26)
    float F4_TgtInertiaVelUp; // @ID(27)
    float F4_TgtInertiaVelEast; // @ID(28)
    unsigned char U1_SwitchGuidanceFlag; // @ID(29)
    unsigned char U1_LandState; // @ID(30)
    short I2_FusedTgtId; // @ID(31)
    EntityID St_CgfTgtId; // @ID(32)
    unsigned char U1_GudanceMemID; // @ID(33)
    unsigned char U1_TakeTurnsFlag; // @ID(34)
    unsigned char U1_IfTakeTurns; // @ID(35)
} PL15GuideParas; // @Extensibility(EXTENSIBLE)

typedef struct PL15TgtSetParas
{
    TgtParasValidity St_TgtParasValidity; // @ID(0)
    TgtPrecision St_TgtPrecision; // @ID(1)
    unsigned char U1_BallisticTrajectoryType; // @ID(2)
    unsigned char U1_TgtRcsType; // @ID(3)
    unsigned char U1_PL15AttackMode; // @ID(4)
    bool B1_IsBullsEye; // @ID(5)
    unsigned short U2_FusedTgtId; // @ID(6)
    short I2_RcsConfidence; // @ID(7)
    float F4_TgtRcsValue; // @ID(8)
    float F4_AllowedInterceptRange; // @ID(9)
    LinearVelocity St_AcTgtRelativeVel; // @ID(10)
    float F4_ACTgtRelativeGeoPosN; // @ID(11)
    float F4_ACTgtRelativeGeoPosU; // @ID(12)
    float F4_ACTgtRelativeGeoPosE; // @ID(13)
    Position St_TgtPos; // @ID(14)
    float F4_BallisticTrajectoryAS; // @ID(15)
    float F4_BallisticTrajectoryBS; // @ID(16)
    float F4_BullsEyeLon; // @ID(17)
    float F4_BullsEyeLat; // @ID(18)
} PL15TgtSetParas; // @Extensibility(EXTENSIBLE)

typedef struct PL16GuideParas
{
    unsigned long long U8_DataGenratedTime; // @ID(0)
    unsigned char U1_StoreWpnTypes; // @ID(1)
    unsigned char U1_StoreStationId; // @ID(2)
    unsigned char U1_TargetPhysicsSize; // @ID(3)
    bool B1_TakeTurnsFlag; // @ID(4)
    bool B1_ValidityAboveGroundHeight; // @ID(5)
    unsigned char U1_GuidanceMemId; // @ID(6)
    unsigned char U1_TargetRcsType; // @ID(7)
    bool B1_IfTakeTurns; // @ID(8)
    unsigned char U1_AxisSign; // @ID(9)
    unsigned char U1_ValidityTgtAngle; // @ID(10)
    unsigned char U1_ValidityTgtVelocity; // @ID(11)
    unsigned char U1_ValidityTgtDistance; // @ID(12)
    float F4_TgtAngleError; // @ID(13)
    short I2_TgtVelocityError; // @ID(14)
    short I2_TgtDistanceError; // @ID(15)
    short I2_FusedTgtId; // @ID(16)
    short I2_TerrainAltitude; // @ID(17)
    float F4_AcPositionDataLat; // @ID(18)
    float F4_AcPositionDataLon; // @ID(19)
    float F4_AcPositionDataAlt; // @ID(20)
    float F4_AcVelocityCGCS2000X; // @ID(21)
    float F4_AcVelocityCGCS2000Y; // @ID(22)
    float F4_AcVelocityCGCS2000Z; // @ID(23)
    float F4_TgtLongitude; // @ID(24)
    float F4_TgtLatitude; // @ID(25)
    float F4_TgtAltitude; // @ID(26)
    float F4_TgtVelocityCGCS2000X; // @ID(27)
    float F4_TgtVelocityCGCS2000Y; // @ID(28)
    float F4_TgtVelocityCGCS2000Z; // @ID(29)
    bool B1_ChangeTgtFlag; // @ID(30)
    short I2_PL16LaunchMode; // @ID(31)
    EntityID St_CgfTgtId; // @ID(32)
} PL16GuideParas; // @Extensibility(EXTENSIBLE)

typedef struct PL16TgtSetParas
{
    TgtParasValidity T4_TgtParasValidity; // @ID(0)
    unsigned char U1_BallisticTrajectoryType; // @ID(1)
    unsigned char U1_TgtRcsType; // @ID(2)
    unsigned char U1_PL16AttackMode; // @ID(3)
    bool B1_GuidanceFault; // @ID(4)
    unsigned short U2_FusedTgtId; // @ID(5)
    short I2_RcsConfidence; // @ID(6)
    float F4_TgtRcsValue; // @ID(7)
    float F4_AllowedInterceptRange; // @ID(8)
    Position P20_TGT_POS; // @ID(9)
    float F4_TgtVelocityCGCS2000_X; // @ID(10)
    float F4_TgtVelocityCGCS2000_Y; // @ID(11)
    float F4_TgtVelocityVGVS2000_Z; // @ID(12)
    float F4_BallisticTrajectoryAS; // @ID(13)
    float F4_BallisticTrajectoryBS; // @ID(14)
    unsigned char U1_LandState; // @ID(15)
    bool B1_ValidityAboveGroundHeight; // @ID(16)
    float F4_TgtDistanceError; // @ID(17)
    float F4_TgtVelocityError; // @ID(18)
    float F4_TgtAngleError; // @ID(19)
    float F4_AboveGroundHeight; // @ID(20)
} PL16TgtSetParas; // @Extensibility(EXTENSIBLE)

typedef struct RadarImageDrive
{
    RadarImageControl St_RadarImageControl; // @ID(0)
    RadarImageGeneral St_RadarImageGeneral; // @ID(1)
    RBMImageEffect St_RBMImageEffect; // @ID(2)
    ISARImagePara St_ISARImagePara; // @ID(3)
    SARImagePara St_SARImagePara; // @ID(4)
    EffectImagePara St_EffectImagePara; // @ID(5)
} RadarImageDrive; // @Extensibility(EXTENSIBLE)

typedef struct ATRTarget
{
    unsigned char U1_ConfidenceOrder; // @ID(0)
    SARImagePosition St_TargetPosition; // @ID(1)
} ATRTarget; // @Extensibility(EXTENSIBLE)

typedef struct SARViewState
{
    unsigned char U1_ViewState; // @ID(0)
    unsigned char U1_ViewPage; // @ID(1)
    unsigned char U1_ViewNo; // @ID(2)
} SARViewState; // @Extensibility(EXTENSIBLE)

typedef struct JamTaskAssignment
{
    unsigned int U4_MemberID; // @ID(0)
    unsigned short U2_FusedTgtID; // @ID(1)
    unsigned short U2_EWtgtNo; // @ID(2)
    unsigned char U1_ECMModality; // @ID(3)
    unsigned int U4_SuportPlane; // @ID(4)
    unsigned char U1_SuportEnable; // @ID(5)
} JamTaskAssignment; // @Extensibility(EXTENSIBLE)

typedef struct AttackTaskAssignment
{
    unsigned int U4_MemberID; // @ID(0)
    unsigned short U2_FusedTgtID; // @ID(1)
    unsigned char U1_EOBNum; // @ID(2)
    unsigned char U1_AttackMode; // @ID(3)
} AttackTaskAssignment; // @Extensibility(EXTENSIBLE)

typedef struct DetecTaskAssignment
{
    unsigned char U1_TgtRCSSet; // @ID(0)
    unsigned char U1_DetecMode; // @ID(1)
    unsigned char U1_FormDetecMode; // @ID(2)
    unsigned int U4_FormDetecLAlt; // @ID(3)
    unsigned int U4_FormDetecHAlt; // @ID(4)
    unsigned int U4_FormDetecStartLon; // @ID(5)
    unsigned int U4_FormDetecStartLat; // @ID(6)
    unsigned int U4_FormDetecEndLon; // @ID(7)
    unsigned int U4_FormDetecEndLat; // @ID(8)
} DetecTaskAssignment; // @Extensibility(EXTENSIBLE)

typedef struct SimFormationOperation
{
    EntityID E4_ReceiveEntityID; // @ID(0)
    EntityID E4_OperationEntityID; // @ID(1)
    unsigned char U1_OperationCMD; // @ID(2)
    unsigned char U1_NewMemberNo; // @ID(3)
    unsigned short U2_AudioChannel; // @ID(4)
    JamTaskAssignment St_JamTaskAssignment; // @ID(5)
    AttackTaskAssignment St_AttackTaskAssignment; // @ID(6)
    DetecTaskAssignment St_DetecTaskAssignment; // @ID(7)
} SimFormationOperation; // @Extensibility(EXTENSIBLE)

typedef struct SimulatorStatusControl
{
    unsigned char U1_OperationMode; // @ID(0)
} SimulatorStatusControl; // @Extensibility(EXTENSIBLE)

typedef struct SingleStoresLoadInventory
{
    unsigned char U1_StoreStationID; // @ID(0)
    bool B1_MunitionExist; // @ID(1)
    unsigned short U2_MunitionType; // @ID(2)
} SingleStoresLoadInventory; // @Extensibility(EXTENSIBLE)

typedef struct StoresInventory
{
    unsigned char U1_Configuration; // @ID(0)
    SingleStoresLoadInventory Arr_SingleStoresLoadInventory[200]; // @ID(1)
} StoresInventory; // @Extensibility(EXTENSIBLE)

typedef struct EOTgtPositionPara
{
    unsigned short U2_Tgt1UpleftX; // @ID(0)
    unsigned short U2_Tgt1UpleftY; // @ID(1)
    unsigned short U2_Tgt1DownrightX; // @ID(2)
    unsigned short U2_Tgt1DownrightY; // @ID(3)
} EOTgtPositionPara; // @Extensibility(EXTENSIBLE)

typedef struct LCAppearance
{
    unsigned char U1_EngineStatus; // @ID(0)
    unsigned char U1_Configuration; // @ID(1)
    unsigned char U1_LghStatus; // @ID(2)
} LCAppearance; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFAppearance
{
    EntityAttribute VFAttribute; // @ID(0)
    LCAppearance VRFAppearance; // @ID(1)
} SingleVFAppearance; // @Extensibility(EXTENSIBLE)

typedef struct ElecTargetPara
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    unsigned char AAASflag; // @ID(1)
    ElecPara Arr_ElecTarget[8]; // @ID(2)
} ElecTargetPara; // @Extensibility(EXTENSIBLE)

typedef struct VehiclePosVelAtt
{
    Position St_EntityPosition; // @ID(0)
    LinearVelocity St_EntityLinearVelocity; // @ID(1)
    float F4_Psi_deg; // @ID(2)
} VehiclePosVelAtt; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFGroundMovingTSPI
{
    EntityAttribute St_EntityAttribute; // @ID(0)
    VehiclePosVelAtt St_VehiclePosVelAtt; // @ID(1)
} SingleVFGroundMovingTSPI; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFIFFEmitFlagParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    IFFEmitFlag VFIFFEmitFlag; // @ID(1)
} SingleVFIFFEmitFlagParas; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFIFFIntgParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    IFFIParas VFIFFIParas; // @ID(1)
} SingleVFIFFIntgParas; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFIFFRespParas
{
    DeviceAttribute St_VFDeviceAttribute; // @ID(0)
    IFFRParas St_VFIFFRParas; // @ID(1)
} SingleVFIFFRespParas; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFLinkComEmitStatusParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    LinkComEmitStatus VFLinkComEmitStatu; // @ID(1)
} SingleVFLinkComEmitStatusParas; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFRadarWorkingParas
{
    RadarWorkingParas St_RadarWorkingParas; // @ID(0)
} SingleVFRadarWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SimAALinkData
{
    unsigned char U1_EntityCategory; // @ID(0)
    unsigned short U1_EntityType; // @ID(1)
    unsigned short U2_OnboardFuel_kg; // @ID(2)
    unsigned char U1_HideStatus; // @ID(3)
    unsigned char U1_EMLevel; // @ID(4)
    unsigned char U1_EMLevelOverrideState; // @ID(5)
    unsigned char U1_RDRSubmode; // @ID(6)
    unsigned char U1_RealSSVValidity; // @ID(7)
    Range St_ScanAzimuthRange; // @ID(8)
    unsigned char F4_RangeScale; // @ID(9)
    unsigned char U1_MidiumMissileQuantity; // @ID(10)
    unsigned char U1_ShortMissileQuantity; // @ID(11)
    unsigned char U1_GunQuantity; // @ID(12)
    unsigned char U1_BombQuantity; // @ID(13)
    unsigned char U1_AntiRadiationQuantity; // @ID(14)
    unsigned char U1_AntiShipQuantity; // @ID(15)
    unsigned char U1_B3JamTargetNumber; // @ID(16)
    unsigned char U1_B12JamTargetNumber; // @ID(17)
    unsigned char U1_B3PodJamTargetNumber; // @ID(18)
    unsigned char U1_HPJamTargetNumber; // @ID(19)
    unsigned char U1_RadarFRmode; // @ID(20)
    unsigned short U2_RadarFRgroup; // @ID(21)
    unsigned short U2_DetectEntityTotal; // @ID(22)
    EntityID E4_DetectEntityID[100]; // @ID(23)
    unsigned char Arr_DetectEntitySource[100]; // @ID(24)
    unsigned char U1_PlatformState[20]; // @ID(25)
    int Arr_TGTBearing_mrad[100]; // @ID(26)
    int Arr_TGTPitch_mrad[100]; // @ID(27)
    unsigned int Arr_TGTDistance_m[100]; // @ID(28)
} SimAALinkData; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFSimAALinkParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    SimAALinkData VFSimAALinkData; // @ID(1)
} SingleVFSimAALinkParas; // @Extensibility(EXTENSIBLE)

typedef struct SimOperationReport
{
    EntityID St_ReceiveEntityID; // @ID(0)
    EntityID St_OperationEntityID; // @ID(1)
    unsigned char U1_ReportStatus; // @ID(2)
} SimOperationReport; // @Extensibility(EXTENSIBLE)

typedef struct SingleSimOperationReport
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    SimOperationReport St_SimOperationReport; // @ID(1)
} SingleSimOperationReport; // @Extensibility(EXTENSIBLE)

typedef struct StationaryEntityPos
{
    Position St_EntityPosition; // @ID(0)
    float F4_Psi_deg; // @ID(1)
} StationaryEntityPos; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFStationaryEntityPos
{
    EntityAttribute St_EntityAttribute; // @ID(0)
    StationaryEntityPos St_StationaryEntityPos; // @ID(1)
} SingleVFStationaryEntityPos; // @Extensibility(EXTENSIBLE)

typedef struct VehicleAttribute
{
    EntityID St_EntityID; // @ID(0)
    unsigned char U1_EntityCamp; // @ID(1)
    unsigned char U1_EntityCategory; // @ID(2)
    unsigned short U1_EntityType; // @ID(3)
    unsigned char U1_EntityClass; // @ID(4)
    unsigned char U1_VehicleType; // @ID(5)
    unsigned char U1_VehicleID; // @ID(6)
    unsigned char U1_VehicleLive; // @ID(7)
} VehicleAttribute; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFSurfaceTSPI
{
    VehicleAttribute St_VehicleAttribute; // @ID(0)
    VehiclePosVelAtt St_VehiclePosVelAtt; // @ID(1)
} SingleVFSurfaceTSPI; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFTSPI
{
    EntityAttribute VFAttribute; // @ID(0)
    EntityPosVelAccAtt VFPosVelAccAtt; // @ID(1)
} SingleVFTSPI; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFTacanWorkingParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    TacanParas VFTacanParas; // @ID(1)
} SingleVFTacanWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFVoiceComEmitStatusParas
{
    DeviceAttribute VFDeviceAttribute; // @ID(0)
    VoiceComEmitStatus VFVoiceComEmitStatu; // @ID(1)
} SingleVFVoiceComEmitStatusParas; // @Extensibility(EXTENSIBLE)

typedef struct AirBorneUnitStatusData
{
    char ArrI1_AirBorneUnitID[20]; // @ID(0)
    char ArrI1_AirBorneUnitVersion[24]; // @ID(1)
    unsigned int U4_AirBorneUnitHeartbeat; // @ID(2)
    unsigned char U1_MemberStatus; // @ID(3)
} AirBorneUnitStatusData; // @Extensibility(EXTENSIBLE)

typedef struct TubeParas
{
    float F4_TubePosX_m_BODY[26]; // @ID(0)
    float F4_TubePosY_m_BODY[26]; // @ID(1)
    float F4_TubePosZ_m_BODY[26]; // @ID(2)
    Attitude Arr_TubeAttitude[26]; // @ID(3)
} TubeParas; // @Extensibility(EXTENSIBLE)

typedef struct JointData
{
    EntityID St_JointEntityID; // @ID(0)
    unsigned char U1_IsJoint; // @ID(1)
} JointData; // @Extensibility(EXTENSIBLE)

typedef struct RefuelingLightData
{
    unsigned char U1_RefuelingLightStatus[10]; // @ID(0)
} RefuelingLightData; // @Extensibility(EXTENSIBLE)

typedef struct WakeInfluence
{
    EntityID St_InfluencedSimulatorID; // @ID(0)
    float F4_WakeInfluenceX_mDs_NED; // @ID(1)
    float F4_WakeInfluenceY_mDs_NED; // @ID(2)
    float F4_WakeInfluenceZ_mDs_NED; // @ID(3)
} WakeInfluence; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareAttribute
{
    unsigned char U1_SoftwareID; // @ID(0)
    unsigned char U1_ExecutionUnit; // @ID(1)
    unsigned short U2_MemberType; // @ID(2)
    unsigned short U2_SceneID; // @ID(3)
    unsigned long long U8_MemberID; // @ID(4)
} SoftwareAttribute; // @Extensibility(EXTENSIBLE)

typedef struct StSoftwareAttrControl
{
    SoftwareAttribute St_SoftwareAttribute; // @ID(0)
    SoftwareControl St_SoftwareControl; // @ID(1)
} StSoftwareAttrControl; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareRunningStatus
{
    char S1_SoftwareVersion[9]; // @ID(0)
    unsigned char U1_SoftwareRunningStatus; // @ID(1)
} SoftwareRunningStatus; // @Extensibility(EXTENSIBLE)

typedef struct StSoftwareAttrStatus
{
    SoftwareAttribute St_SoftwareAttribute; // @ID(0)
    SoftwareRunningStatus St_SoftwareRunningStatus; // @ID(1)
} StSoftwareAttrStatus; // @Extensibility(EXTENSIBLE)

typedef struct TerrainData
{
    float F4_TerrainHeight_CGCS; // @ID(0)
} TerrainData; // @Extensibility(EXTENSIBLE)

typedef struct TrainingTerminalAttribute
{
    unsigned short U2_MemberType; // @ID(0)
    unsigned char U1_TrainingTerminalType; // @ID(1)
    unsigned char U1_TrainingTerminalStatus; // @ID(2)
} TrainingTerminalAttribute; // @Extensibility(EXTENSIBLE)

typedef struct UAVAttribute
{
    MemberID U4_MemeberID; // @ID(0)
    unsigned short U2_MemberType; // @ID(1)
    unsigned char U1_MemberFlightConfig; // @ID(2)
} UAVAttribute; // @Extensibility(EXTENSIBLE)

typedef struct UPSStatus
{
    unsigned char U1_UPSMode; // @ID(0)
    unsigned char U1_UPSCapacity_pct; // @ID(1)
    unsigned char U1_UPSFailure; // @ID(2)
    unsigned char U1_UPSFailureType; // @ID(3)
} UPSStatus; // @Extensibility(EXTENSIBLE)

typedef struct CGFAttackEntityID
{
    EntityID St_EntityID; // @ID(0)
    unsigned short Arr_MunitionType[10]; // @ID(1)
} CGFAttackEntityID; // @Extensibility(EXTENSIBLE)

typedef struct VFAttackTargetList
{
    EntityID St_CGFEntityID; // @ID(0)
    CGFAttackEntityID Arr_CGFEntityID[200]; // @ID(1)
} VFAttackTargetList; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFEntityExtralFlightData
{
    EntityAttribute VFAttribute; // @ID(0)
    ExtraFightData VFExtraFightData; // @ID(1)
} SingleVFEntityExtralFlightData; // @Extensibility(EXTENSIBLE)

typedef struct VisiblelightVedioData
{
    unsigned int U4_MessageLength; // @ID(0)
    char S_VedioData[1000]; // @ID(1)
} VisiblelightVedioData; // @Extensibility(EXTENSIBLE)

typedef struct VisualDisplay
{
    unsigned char U1_PowerFailure; // @ID(0)
    unsigned char U1_FanFailure; // @ID(1)
    unsigned char U1_DisplayEnvStatus; // @ID(2)
    unsigned char U1_CockpitEnvStatus; // @ID(3)
    unsigned char U1_ACStatus; // @ID(4)
} VisualDisplay; // @Extensibility(EXTENSIBLE)

typedef struct AIMemberAttributeStatusMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberAttribute St_MemberAttribute; // @ID(1)
} AIMemberAttributeStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct AIMemberInitFlightSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    AIStartParas St_AIStartParas; // @ID(1)
    std::vector<AIMemberInitFlightParas> Arr_AIMemberInitFlightParas; // @ID(2) /* maximum length = (200) */
} AIMemberInitFlightSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct ActiveJamWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    ActiveJamWorkingParas St_ActiveJamWorkingParas; // @ID(1)
} ActiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct AtmosphericServiceMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    AtmosphericReport St_AtmosphericReport; // @ID(1)
} AtmosphericServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct CGFForceManageSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    CGFForceManageSetting St_CGFForceManageSetting; // @ID(2)
    CGFRealTimeInterveneInfo St_CGFRealTimeInterveneInfo; // @ID(3)
} CGFForceManageSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct CGFRefuelFlightBehaviorSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityID St_EntityID; // @ID(1)
    RefuelingFlightCmd St_RefuelingFlightCmd; // @ID(2)
    RefuelingParas St_RefuelingParas; // @ID(3)
} CGFRefuelFlightBehaviorSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct CGFWarBehaviorSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    int ArrI4_CGFWarBehaviorSetting[100]; // @ID(2)
} CGFWarBehaviorSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct CameraRTStatusMsg
{
    UDP_MessageHeader St_MessageHeader; // @ID(0)
    CameraRTStatus St_CameraRTStatus; // @ID(1)
} CameraRTStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct CoEngagementRequestMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    CoEngagementReq St_CoEngagementReq; // @ID(1)
} CoEngagementRequestMsg; // @Extensibility(EXTENSIBLE)

typedef struct CockpitStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    CockpitDeviceStatus St_CockpitDeviceStatus; // @ID(3)
} CockpitStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct ComputerControlCMDMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    std::vector<StComputerAttrControl> Seq_StComputerAttrControl; // @ID(3) /* maximum length = (255) */
} ComputerControlCMDMsg; // @Extensibility(EXTENSIBLE)

typedef struct ComputerGroupStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    std::vector<StComputerAttrStatus> Seq_StComputerAttrStatus; // @ID(3) /* maximum length = (255) */
} ComputerGroupStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct ContainerControlMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    ContainerManage St_ContainerManage; // @ID(1)
    SoftwareControl St_SoftwareControl; // @ID(2)
} ContainerControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct DataInAcmiMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SingleDataInAcmi Arr_SingleDataInAcmi[6]; // @ID(1)
} DataInAcmiMsg; // @Extensibility(EXTENSIBLE)

typedef struct DataOutAcmiMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SingleDataOutAcmi Arr_SingleDataOutAcmi[6]; // @ID(1)
} DataOutAcmiMsg; // @Extensibility(EXTENSIBLE)

typedef struct EMVReportMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EMVReport St_EMVReport; // @ID(1)
} EMVReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct EOTrackingEntityPara
{
    EntityID St_TrackingEntityID; // @ID(0)
} EOTrackingEntityPara; // @Extensibility(EXTENSIBLE)

typedef struct ElecOptDefWorkingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    ElectroOpticalEquipmentStatus St_ElectroOpticalEquipmentStatus; // @ID(1)
} ElecOptDefWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct ElecOptDeteWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    ElecOptDeteWorkingParas St_ElecOptDeteWorkingParas; // @ID(1)
} ElecOptDeteWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct EmbedIDSetFeedbackMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneControlAttribute St_SceneID; // @ID(1)
    std::vector<SingleVCEmbedID> Seq_SingleVCEmbedID; // @ID(2) /* maximum length = (200) */
} EmbedIDSetFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct EmbedIDSetMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneControlAttribute St_SceneID; // @ID(1)
    std::vector<SingleVCEmbedID> Seq_SingleVCEmbedID; // @ID(2) /* maximum length = (200) */
} EmbedIDSetMsg; // @Extensibility(EXTENSIBLE)

typedef struct EntityAppearanceMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    VirtualAppearance St_VirtualAppearance; // @ID(2)
} EntityAppearanceMsg; // @Extensibility(EXTENSIBLE)

typedef struct EntityExtralFlightDataMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    ExtraFightData St_ExtraFightData; // @ID(2)
} EntityExtralFlightDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct EntityIDChangeFeedbackMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberControlAttribute St_MemberID; // @ID(1)
    EntityControlAttribute St_EntityID; // @ID(2)
} EntityIDChangeFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct EntityIDChangeMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberControlAttribute St_MemberID; // @ID(1)
    EntityIDSetting St_EntityID; // @ID(2)
} EntityIDChangeMsg; // @Extensibility(EXTENSIBLE)

typedef struct EntityTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    EntityPosVelAccAtt St_EntityPosVelAccAtt; // @ID(2)
} EntityTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct FacilitiesPowerSupplyStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    FacilitiesPowerSupplyStatusData St_FacilitiesPowerSupplyStatusData; // @ID(1)
} FacilitiesPowerSupplyStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct FacilitiesPowerSupplyStatusParasUDPMsg
{
    UDP_MessageHeader St_UDPMessageHeader; // @ID(0)
    FacilitiesPowerSupplyStatusData St_FacilitiesPowerSupplyStatusData; // @ID(1)
} FacilitiesPowerSupplyStatusParasUDPMsg; // @Extensibility(EXTENSIBLE)

typedef struct FaultClear
{
    bool ArrB1_FaultClear[200]; // @ID(0)
} FaultClear; // @Extensibility(EXTENSIBLE)

typedef struct FlightNavigationStatusMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    FlightNavigationStatus_S St_FlightNavigationStatusMsg; // @ID(1)
} FlightNavigationStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct FunctionalUnitStatusMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    UnitStatusData St_UnitStatusData; // @ID(1)
} FunctionalUnitStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct GeographyServiceMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    GeographyReport St_GeographyReport; // @ID(1)
} GeographyServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct IRIntensityEntityReportMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityIRIntensityReport St_EntityIRIntensityReport; // @ID(1)
} IRIntensityEntityReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct IRIntensityMunitionReportMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionIRIntensityReport St_MunitionIRIntensityReport; // @ID(1)
} IRIntensityMunitionReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct IRTrackTarget
{
    EntityID St_TrackTargetID; // @ID(0)
    unsigned char U1_TrackLevel; // @ID(1)
} IRTrackTarget; // @Extensibility(EXTENSIBLE)

typedef struct ImageRTCommandMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    ImageRTCommand St_ImageRTCommand; // @ID(1)
} ImageRTCommandMsg; // @Extensibility(EXTENSIBLE)

typedef struct LVCModeSwitchMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    LVCModeSwitch St_LVCModeSwitch; // @ID(1)
} LVCModeSwitchMsg; // @Extensibility(EXTENSIBLE)

typedef struct LVCProtocolMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneControlAttribute St_SceneID; // @ID(1)
    unsigned char NetProtocol; // @ID(2)
} LVCProtocolMsg; // @Extensibility(EXTENSIBLE)

typedef struct LaserWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    LaserWorkingParas St_LaserWorkingParas; // @ID(1)
} LaserWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct LivePlaneOperationMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    LivePlaneAttribute St_LivePlaneAttribute; // @ID(1)
    LivePlaneControlAttribute St_LivePlaneControlAttribute; // @ID(2)
    MemberID St_MemberID; // @ID(3)
} LivePlaneOperationMsg; // @Extensibility(EXTENSIBLE)

typedef struct Member01MalfunctionSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    MalfunctionSetting_01 St_MalfunctionSetting_01; // @ID(2)
} Member01MalfunctionSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberAttributeStatusMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberAttribute St_MemberAttribute; // @ID(1)
} MemberAttributeStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberCampSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    EntityCampSetting St_EntityCamp; // @ID(2)
} MemberCampSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberInitFlightSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MemberInitFlightParas> Seq_MemberInitFlightParas; // @ID(1) /* maximum length = (200) */
} MemberInitFlightSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberMalfunctionClearMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityID E4_EntityID; // @ID(1)
    bool Arr_FaultClear[200]; // @ID(2)
} MemberMalfunctionClearMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberMalfunctionFeedbackMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityAttribute; // @ID(1)
    bool Arr_FaultFeedback[200]; // @ID(2)
} MemberMalfunctionFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberMalfunctionSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    MalfunctionSetting St_MalfunctionSetting; // @ID(2)
} MemberMalfunctionSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberModeSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    SimulatorModeSetting St_SimulatorModeSetting; // @ID(2)
} MemberModeSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberSimulationSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    SimulationSetting St_SimulationSetting; // @ID(2)
} MemberSimulationSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MemberStoreSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MemberStoreSettingParas> Seq_MemberStoreSetting; // @ID(1) /* maximum length = (200) */
} MemberStoreSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct MissionPlanDataMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    short ArrI2_MissionPlanData[50]; // @ID(2)
} MissionPlanDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI1Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI2Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI3Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI4Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI5Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI6Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI7Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoGuidanceI8Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} MunitionCoGuidanceI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI1Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI2Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI3Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI4Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI5Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI6Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI7Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionCoLinkReportI8Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} MunitionCoLinkReportI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionDisplayMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionDisplay St_MunitionDisplay; // @ID(1)
} MunitionDisplayMsg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionKillNotifyMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionKillNotify St_MunitionKillNotify; // @ID(1)
} MunitionKillNotifyMsg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionTSPI St_MunitionTSPI; // @ID(1)
} MunitionTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct MunitionWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionWorkingParas St_MunitionWorkingParas; // @ID(1)
} MunitionWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct NatureServiceMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    NatureReport St_NatureReport; // @ID(1)
} NatureServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct NavigationDataMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    NavigationData_S St_NavigationData; // @ID(1)
} NavigationDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct NewContainerControlMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    NewSceneCreate St_NewSceneCreate; // @ID(1)
} NewContainerControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct OnlineSceneMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneInfo St_SceneInfo; // @ID(1)
    std::vector<MemberAttribute> Seq_MemberAttribute; // @ID(2) /* maximum length = (200) */
} OnlineSceneMsg; // @Extensibility(EXTENSIBLE)

typedef struct PassiveJamWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    PassiveJamWorkingParas St_PassiveJamWorkingParas; // @ID(1)
} PassiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct PowerControlCMDMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    PowerAttribute St_PowerAttribute; // @ID(3)
    PowerControl St_PowerControl; // @ID(4)
} PowerControlCMDMsg; // @Extensibility(EXTENSIBLE)

typedef struct PowerGroupStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    PowerAttribute St_PowerAttribute[10]; // @ID(3)
    ComputerAttribute St_ComputerAttribute[10]; // @ID(4)
    PowerStatus St_PowerStatus[10]; // @ID(5)
} PowerGroupStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct RCSEntityReportMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityRCSReport St_EntityRCSReport; // @ID(1)
} RCSEntityReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct RCSMunitionReportMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MunitionRCSReport St_MunitionRCSReport; // @ID(1)
} RCSMunitionReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct RadarWorkingParas1Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} RadarWorkingParas1Msg; // @Extensibility(EXTENSIBLE)

typedef struct RadarWorkingParas2Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} RadarWorkingParas2Msg; // @Extensibility(EXTENSIBLE)

typedef struct RadarWorkingParas3Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} RadarWorkingParas3Msg; // @Extensibility(EXTENSIBLE)

typedef struct RadarWorkingParas4Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} RadarWorkingParas4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SceneChangeFeedbackMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneControlAttribute St_SceneID; // @ID(1)
    MemberControlAttribute St_MemberID; // @ID(2)
    EntityControlAttribute St_EntityID; // @ID(3)
    EntityCampSetting St_EntityCamp; // @ID(4)
} SceneChangeFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneControlMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneStatusControl St_SceneStatusControl; // @ID(1)
} SceneControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneCustomAirportSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    CGFForceManageSetting St_CGFForceManageSetting; // @ID(1)
    std::vector<SingleCustomAirportSetting> Seq_CustomAirportSetting; // @ID(2) /* maximum length = (20) */
} SceneCustomAirportSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneEnvSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    RangeControlAttribute St_RangeControlAttribute; // @ID(1)
    std::vector<EnvAttributeParas> Seq_EnvAttributeParas; // @ID(2) /* maximum length = (50) */
} SceneEnvSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneIDSetting
{
    SceneID St_SceneID; // @ID(0)
} SceneIDSetting; // @Extensibility(EXTENSIBLE)

typedef struct SceneInitFormationSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<InitFormationList> Seq_InitFormationList; // @ID(1) /* maximum length = (200) */
} SceneInitFormationSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneMemberCampFeedbackMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    EntityCampSetting St_EntityCamp; // @ID(2)
} SceneMemberCampFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneStatusMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SceneStatus St_SceneStatus; // @ID(1)
} SceneStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneSwitchMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberControlAttribute St_MemberControlAttribute; // @ID(1)
    SceneControlAttribute St_SceneControlAttribute; // @ID(2)
    EntityIDSetting St_EntityIDSetting; // @ID(3)
    EntityCampSetting St_EntityCampSetting; // @ID(4)
} SceneSwitchMsg; // @Extensibility(EXTENSIBLE)

typedef struct SceneTimeSettingMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    TimeElementSetting St_TimeElementSetting; // @ID(1)
} SceneTimeSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAALinkData1JIDSMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData1 St_AALinkData1; // @ID(2)
} SecAALinkData1JIDSMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAALinkData1VUMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData1 St_AALinkData1; // @ID(2)
} SecAALinkData1VUMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAALinkData2IFDLMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData2 St_AALinkData2; // @ID(2)
} SecAALinkData2IFDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAALinkData2WCDLMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    AALinkData2 St_AALinkData2; // @ID(2)
} SecAALinkData2WCDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecActiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    ActiveJamWorkingParas St_ActiveJamWorkingParas; // @ID(1)
} SecActiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllAALinkData1JIDSMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    AALinkData1JIDSMsg Arr_AALinkData1[200]; // @ID(1)
    MessageValid Arr_MessageValid[200]; // @ID(2)
} SecAllAALinkData1JIDSMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllAALinkData1VUMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    AALinkData1VUMsg Arr_AALinkData1[200]; // @ID(1)
    MessageValid Arr_MessageValid[200]; // @ID(2)
} SecAllAALinkData1VUMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllAALinkData2IFDLMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    AALinkData2IFDLMsg Arr_AALinkData2[200]; // @ID(1)
    MessageValid Arr_MessageValid[200]; // @ID(2)
} SecAllAALinkData2IFDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllAALinkData2WCDLMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    AALinkData2WCDLMsg Arr_AALinkData2[200]; // @ID(1)
    MessageValid Arr_MessageValid[200]; // @ID(2)
} SecAllAALinkData2WCDLMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllActiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecActiveJamWorkingParas Arr_ActiveJamWorkingParas[200]; // @ID(2)
} SecAllActiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllCoEngagementRequestMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    CoEngagementReq Arr_CoEngagementReq[10]; // @ID(2)
    MessageHeader Arr_MessageHeader[10]; // @ID(3)
} SecAllCoEngagementRequestMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllEntityAppearanceMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecEnAttrVApp Arr_SecEnAttrVApp[200]; // @ID(2)
} SecAllEntityAppearanceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllEntityTSPIMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecEnAttrPVAA Arr_SecEnAttrPVAA[200]; // @ID(2)
} SecAllEntityTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllIFFEmitFlagParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid St_MessageValid[200]; // @ID(1)
    IFFEmitFlagParasMsg Arr_SecALLIFFEmitFlagParasMsg[200]; // @ID(2)
} SecAllIFFEmitFlagParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllIFFIntgParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    IFFIntgParasMsg Arr_IFFIntgParas[200]; // @ID(2)
} SecAllIFFIntgParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllIFFRespParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    IFFRespParasMsg Arr_IFFRespParas[200]; // @ID(2)
} SecAllIFFRespParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllLaserWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecLaserWorkingParas Arr_SecLaserWorkingParas[200]; // @ID(2)
} SecAllLaserWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllLinkComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid St_MessageValid[200]; // @ID(1)
    LinkComEmitStatusParasMsg Arr_SecAllLinkComEmitStatusParasMsg[200]; // @ID(2)
} SecAllLinkComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI1Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI2Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI3Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI4Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI5Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI6Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI7Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoGuidanceI8Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceInfoIFDL Arr_MslGuidanceInfoIFDL[10]; // @ID(3)
} SecAllMunitionCoGuidanceI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI1Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI2Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI3Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI4Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI5Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI6Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI7Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionCoLinkReportI8Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[10]; // @ID(1)
    MessageHeader Arr_MessageHeader[10]; // @ID(2)
    MslGuidanceLinkReportIFDL Arr_MslGuidanceLinkReportIFDL[10]; // @ID(3)
} SecAllMunitionCoLinkReportI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionKillNotifyMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    MunitionKillNotify Arr_MunitionKillNotify[200]; // @ID(2)
    MessageHeader Arr_MessageHeader[200]; // @ID(3)
} SecAllMunitionKillNotifyMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionTSPIMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecMunitionTSPI Arr_MunitionTSPI[200]; // @ID(2)
} SecAllMunitionTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllMunitionWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecMunitionWorkingParas Arr_MunitionWorkingParas[200]; // @ID(2)
} SecAllMunitionWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllPassiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecPassiveJamWorkingParas St_SecPassiveJamWorkingParas[200]; // @ID(2)
} SecAllPassiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllRadarWorkingParas1Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecRadarWorkingParas Arr_RadarWorkingParas[200]; // @ID(2)
} SecAllRadarWorkingParas1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllRadarWorkingParas2Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecRadarWorkingParas Arr_RadarWorkingParas[200]; // @ID(2)
} SecAllRadarWorkingParas2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllRadarWorkingParas3Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecRadarWorkingParas Arr_RadarWorkingParas[200]; // @ID(2)
} SecAllRadarWorkingParas3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllRadarWorkingParas4Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SecRadarWorkingParas Arr_RadarWorkingParas[200]; // @ID(2)
} SecAllRadarWorkingParas4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllTacanWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SecTacanWorkingParasMsg Arr_SecTacanParas[200]; // @ID(1)
    MessageValid Arr_MessageValid[200]; // @ID(2)
} SecAllTacanWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAllVoiceComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid St_MessageValid[200]; // @ID(1)
    VoiceComEmitStatusParasMsg Arr_SecAllVoiceComEmitStatusParasMsg[200]; // @ID(2)
} SecAllVoiceComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecAtmosphericServiceMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    AtmosphericReport St_AtmosphericReport; // @ID(1)
} SecAtmosphericServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecCGFRefuelFlightBehaviorSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityID St_EntityID; // @ID(1)
    RefuelingFlightCmd St_RefuelingFlightCmd; // @ID(2)
    RefuelingParas St_RefuelingParas; // @ID(3)
} SecCGFRefuelFlightBehaviorSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecClientControlMsg
{
    UDP_MessageHeader St_UDPMessageHeader; // @ID(0)
    unsigned char U1_ControlCMD; // @ID(1)
    unsigned int U4_MemberID; // @ID(2)
} SecClientControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecCoEngagementRequestMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    CoEngagementReq St_CoEngagementReq; // @ID(1)
} SecCoEngagementRequestMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecDASImageDriveMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EOImageShowArea St_EOImageShowArea; // @ID(1)
    EOImageModePara St_EOImageModePara; // @ID(2)
    EOImageEffect St_EOImageEffect; // @ID(3)
    EOImageTrackPara St_EOImageTrackPara; // @ID(4)
} SecDASImageDriveMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecDataInAcmiMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleDataInAcmi Arr_SingleDataInAcmi[6]; // @ID(1)
} SecDataInAcmiMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecDataOutAcmiMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleDataOutAcmi Arr_SingleDataOutAcmi[6]; // @ID(1)
} SecDataOutAcmiMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecDatalinkKeepAliveMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DatalinkKeepAlive St_DatalinkKeepAlive; // @ID(1)
} SecDatalinkKeepAliveMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecEMVReportMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EMVReport St_EMVReport; // @ID(1)
} SecEMVReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecEOImageDriveMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EOImageState St_EOImageState; // @ID(1)
    EOImageShowArea St_EOImageShowArea; // @ID(2)
    EOImageParasIS St_EOImageParasIS; // @ID(3)
    EOImageModifyPara St_EOImageModifyPara; // @ID(4)
    EOTgtPara Arr_EOTgtPara[5]; // @ID(5)
} SecEOImageDriveMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecElecOptDeteWorkingParas
{
    MessageHeader St_MessageHeader; // @ID(0)
    ElecOptDeteWorkingParas St_ElecOptDeteWorkingParas; // @ID(1)
} SecElecOptDeteWorkingParas; // @Extensibility(EXTENSIBLE)

typedef struct SecElecOptDeteWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    ElecOptDeteWorkingParas St_ElecOptDeteWorkingParas; // @ID(1)
} SecElecOptDeteWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecEntityAppearanceMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    VirtualAppearance St_VirtualAppearance; // @ID(2)
} SecEntityAppearanceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecEntityExtralFlightDataMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    ExtraFightData St_ExtraFightData; // @ID(2)
} SecEntityExtralFlightDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecEntityTSPIMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    EntityPosVelAccAtt St_EntityPosVelAccAtt; // @ID(2)
} SecEntityTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecGeographyServiceMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    GeographyReport St_GeographyReport; // @ID(1)
} SecGeographyServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIFDLlinkTeamMemberListMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    TeamMemberInfo Arr_LinkTeamMemberList[48]; // @ID(1)
} SecIFDLlinkTeamMemberListMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIFFEmitFlagParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFEmitFlag St_IFFEmitFlag; // @ID(2)
} SecIFFEmitFlagParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIFFIntgParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFIParas St_IFFIParas; // @ID(2)
} SecIFFIntgParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIFFRespParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    IFFRParas St_IFFIParas; // @ID(2)
} SecIFFRespParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIRIntensityEntityReportMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityID M4_IRIntensityCalEntityID; // @ID(1)
    SingleEntityIRIntensityReport Arr_EntityIRIntensityReport[200]; // @ID(2)
    SingleMunitionIRIntensityReport Arr_MunitionIRIntensityReport[200]; // @ID(3)
} SecIRIntensityEntityReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIRIntensityMunitionReportMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MunitionID M4_IRIntensityCalMunitionID; // @ID(1)
    SingleEntityIRIntensityReport Arr_EntityIRIntensityReport[200]; // @ID(2)
    SingleMunitionIRIntensityReport Arr_MunitionIRIntensityReport[200]; // @ID(3)
} SecIRIntensityMunitionReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIRSTImageDriveMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EOImageModePara St_EOImageModePara; // @ID(1)
    EOImageEffect St_EOImageEffect; // @ID(2)
    EOImageTrackPara Arr_EOImageTrackPara[2]; // @ID(3)
    EOImagePlaybackPara Arr_EOImagePlaybackPara[8]; // @ID(4)
} SecIRSTImageDriveMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecIrOperateCommandMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    PL10SeekerParas Arr_PL10SeekerParas[11]; // @ID(1)
} SecIrOperateCommandMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecLaserWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    LaserWorkingParas St_LaserWorkingParas; // @ID(1)
} SecLaserWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecLinkComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    LinkComEmitStatus St_LinkComEmitStatus; // @ID(2)
} SecLinkComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMember01MalfunctionSettingMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MalfunctionSetting_01 St_MalfunctionSetting_01; // @ID(1)
} SecMember01MalfunctionSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberAttributeStatusMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MemberAttribute St_MemberAttribute; // @ID(1)
} SecMemberAttributeStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberCampSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityControlAttribute St_EntityID; // @ID(1)
    EntityCampSetting St_EntityCamp; // @ID(2)
} SecMemberCampSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberInitFlightSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MemberInitFlightParas St_MemberInitFlightParas; // @ID(1)
    SimType St_SimType; // @ID(2)
} SecMemberInitFlightSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberMalfunctionClearMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    bool Arr_FaultClear[200]; // @ID(1)
} SecMemberMalfunctionClearMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberMalfunctionFeedbackMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    bool Arr_FaultFeedback[200]; // @ID(1)
} SecMemberMalfunctionFeedbackMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberMalfunctionSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MalfunctionSetting St_MalfunctionSetting; // @ID(1)
} SecMemberMalfunctionSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberModeSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SimulatorModeSetting St_SimulatorModeSetting; // @ID(1)
} SecMemberModeSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberSimulationSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SimulationSetting St_SimulationSetting; // @ID(1)
} SecMemberSimulationSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMemberStoreSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    StoreSetting St_StoreSetting; // @ID(1)
} SecMemberStoreSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMissionPlanDataMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EntityAttribute St_EntityAttribute; // @ID(1)
    short ArrI2_MissionPlanData[50]; // @ID(2)
} SecMissionPlanDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI1Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI2Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI3Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI4Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI5Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI6Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI7Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoGuidanceI8Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MslGuidanceInfoIFDL St_MslGuidanceInfoIFDL; // @ID(1)
} SecMunitionCoGuidanceI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI1Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI2Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI3Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI4Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI5Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI5Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI6Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI6Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI7Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI7Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionCoLinkReportI8Msg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MslGuidanceLinkReportIFDL St_MslGuidanceLinkReportIFDL; // @ID(1)
} SecMunitionCoLinkReportI8Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionDisplayMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MunitionDisplay St_MunitionDisplay; // @ID(1)
} SecMunitionDisplayMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionKillNotifyMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MunitionKillNotify St_MunitionKillNotify; // @ID(1)
} SecMunitionKillNotifyMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionTSPIMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MunitionTSPI St_MunitionTSPIMsg; // @ID(1)
} SecMunitionTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecMunitionWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MunitionWorkingParas St_MunitionWorkingParas; // @ID(1)
} SecMunitionWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecNatureServiceMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    NatureReport St_NatureReport; // @ID(1)
} SecNatureServiceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL10AGuideMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    GuideParas St_GuideParas; // @ID(1)
    PL10AGuideParas Arr_PL10AGuideParas[10]; // @ID(2)
} SecPL10AGuideMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL10TgtSetParasMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    PL10TgtSetParas Arr_PL10TgtSetParas[10]; // @ID(1)
} SecPL10TgtSetParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL15AlignMissionParasMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    PL15MslMissionParas Arr_PL15MslMissionParas[14]; // @ID(1)
    PL15MslCountParas Arr_PL15MslCountParas[14]; // @ID(2)
} SecPL15AlignMissionParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL15GuideMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    GuideParas St_GuideParas; // @ID(1)
    PL15GuideParas Arr_PL15GuideParas[14]; // @ID(2)
} SecPL15GuideMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL15TgtMissionParasMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    PL15TgtSetParas Arr_PL15TgtSetParas[14]; // @ID(1)
} SecPL15TgtMissionParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL16GuideMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    GuideParas St_GuideParas; // @ID(1)
    PL16GuideParas Arr_PL16GuideParas[14]; // @ID(2)
} SecPL16GuideMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPL16TgtMissionParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    PL16TgtSetParas Arr_PL16TgtSetParas[14]; // @ID(1)
} SecPL16TgtMissionParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecPassiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    PassiveJamWorkingParas St_PassiveJamWorkingParas; // @ID(1)
} SecPassiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecRCSEntityReportMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    EntityID M4_RCSCalEntityID; // @ID(1)
    SingleEntityRCSReport Arr_EntityRCSReport[200]; // @ID(2)
    SingleMunitionRCSReport Arr_MunitionRCSReport[200]; // @ID(3)
} SecRCSEntityReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecRCSMunitionReportMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MunitionID M4_RCSCalMunitionID; // @ID(1)
    SingleEntityRCSReport Arr_EntityRCSReport[200]; // @ID(2)
    SingleMunitionRCSReport Arr_MunitionRCSReport[200]; // @ID(3)
} SecRCSMunitionReportMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecRDRNoiseJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    JamStatus St_JamStatus; // @ID(2)
    NoiseJam St_NoiseJam; // @ID(3)
} SecRDRNoiseJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarImageDriveMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    RadarImageDrive St_RadarImageDrive; // @ID(1)
} SecRadarImageDriveMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarWorkingParas1Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} SecRadarWorkingParas1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarWorkingParas2Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} SecRadarWorkingParas2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarWorkingParas3Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} SecRadarWorkingParas3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecRadarWorkingParas4Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    RadarWorkingParas St_RadarWorkingParas; // @ID(1)
} SecRadarWorkingParas4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecSARATRTargetMsg
{
    SM_MessageHeader St_SMMessageHead; // @ID(0)
    ATRTarget St_ATRTarget[18]; // @ID(1)
} SecSARATRTargetMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSARATRViewMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SARViewState St_SARViewState; // @ID(1)
} SecSARATRViewMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSceneCustomAirportSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    CGFForceManageSetting St_CGFForceManageSetting; // @ID(1)
    SingleCustomAirportSetting Arr_CustomAirportSetting[20]; // @ID(2)
} SecSceneCustomAirportSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSceneEnvSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    RangeControlAttribute St_RangeControlAttribute; // @ID(1)
    EnvAttributeParas Arr_EnvAttributeParas[50]; // @ID(2)
} SecSceneEnvSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSceneInitFormationSettingMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    InitFormationList Arr_InitFormationList[200]; // @ID(1)
} SecSceneInitFormationSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSceneTimeSettingMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    TimeElementSetting St_TimeElementSetting; // @ID(1)
} SecSceneTimeSettingMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSimFormationOperationMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    SimFormationOperation St_SimFormationOperation; // @ID(2)
} SecSimFormationOperationMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecSimulatorControlMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SimulatorStatusControl St_SimulatorStatusControl; // @ID(1)
} SecSimulatorControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecStoresInventoryMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    StoresInventory St_StoresInventory; // @ID(1)
} SecStoresInventoryMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecTgtPositionParaMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    EOTgtPositionPara Arr_EOTgtPositionPara[5]; // @ID(1)
} SecTgtPositionParaMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFActiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    ActiveJamWorkingParas Arr_ActiveJamWorkingParas[200]; // @ID(1)
} SecVFActiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFAppearanceMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleVFAppearance Arr_SingleVFAppearance[200]; // @ID(1)
} SecVFAppearanceMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFElecTargetParaMsg
{
    SM_MessageHeader St_SMmessageHeader; // @ID(0)
    MessageHeader St_MessageHeader; // @ID(1)
    ElecTargetPara Arr_VFElecTargetPara[200]; // @ID(2)
} SecVFElecTargetParaMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFGroundMovingTSPIMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleVFGroundMovingTSPI Arr_SecVFGroundMovingTSPI[200]; // @ID(1)
} SecVFGroundMovingTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFIFFEmitFlagParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SingleVFIFFEmitFlagParas Arr_SecVFIFFEmitFlagParasMsg[200]; // @ID(2)
} SecVFIFFEmitFlagParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFIFFIntgParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SingleVFIFFIntgParas Arr_VFIFFIntgParas[200]; // @ID(2)
} SecVFIFFIntgParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFIFFRespParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SingleVFIFFRespParas Arr_VFIFFRespParas[200]; // @ID(2)
} SecVFIFFRespParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFLaserWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    LaserWorkingParas Arr_LaserWorkingParas[200]; // @ID(1)
} SecVFLaserWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFLinkComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SingleVFLinkComEmitStatusParas Arr_VFLinkComEmitStatusParas[200]; // @ID(2)
} SecVFLinkComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFMunitionKillNotifyMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MunitionKillNotify Arr_VFMunitionKillNotify[200]; // @ID(1)
} SecVFMunitionKillNotifyMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFMunitionTSPIMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MunitionTSPI Arr_VFMunitionTSPI[200]; // @ID(1)
} SecVFMunitionTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFMunitionWorkingParasMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    MunitionWorkingParas Arr_VFMunitionWorkingParas[200]; // @ID(1)
} SecVFMunitionWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFPassiveJamWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    PassiveJamWorkingParas St_PassiveJamWorkingParas[200]; // @ID(1)
} SecVFPassiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFRadarWorkingParas1Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFRadarWorkingParas Arr_SecVFRadarWorkingParas[200]; // @ID(1)
} SecVFRadarWorkingParas1Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFRadarWorkingParas2Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFRadarWorkingParas Arr_SecVFRadarWorkingParas[200]; // @ID(1)
} SecVFRadarWorkingParas2Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFRadarWorkingParas3Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFRadarWorkingParas Arr_SecVFRadarWorkingParas[200]; // @ID(1)
} SecVFRadarWorkingParas3Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFRadarWorkingParas4Msg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFRadarWorkingParas Arr_SecVFRadarWorkingParas[200]; // @ID(1)
} SecVFRadarWorkingParas4Msg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFSimAALinkParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageHeader St_messageheader; // @ID(1)
    SingleVFSimAALinkParas Arr_VFSimAALinkParas[200]; // @ID(2)
} SecVFSimAALinkParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFSimAALinkReportParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageHeader St_MessageHeader; // @ID(1)
    SingleSimOperationReport Arr_SingleSimOperationReport[200]; // @ID(2)
} SecVFSimAALinkReportParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFStationaryEntityPosMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFStationaryEntityPos Arr_SecVFStationaryEntityPos[200]; // @ID(1)
} SecVFStationaryEntityPosMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFSurfaceTSPIMsg
{
    SM_MessageHeader St_MessageHeader; // @ID(0)
    SingleVFSurfaceTSPI Arr_SecVFSurfaceTSPI[200]; // @ID(1)
} SecVFSurfaceTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFTSPIMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleVFTSPI Arr_SecVFTSPI[200]; // @ID(1)
} SecVFTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFTacanWorkingParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    SingleVFTacanWorkingParas Arr_SingleVFTacanWorkingParas[200]; // @ID(1)
} SecVFTacanWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVFVoiceComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    MessageValid Arr_MessageValid[200]; // @ID(1)
    SingleVFVoiceComEmitStatusParas Arr_VFVoiceComEmitStatusParas[200]; // @ID(2)
} SecVFVoiceComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SecVoiceComEmitStatusParasMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    VoiceComEmitStatus St_VoiceComEmitStatus; // @ID(2)
} SecVoiceComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct SimFormationOperationMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    SimFormationOperation St_SimFormationOperation; // @ID(2)
} SimFormationOperationMsg; // @Extensibility(EXTENSIBLE)

typedef struct SimulatorControlMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    MemberControlAttribute St_MemberID; // @ID(1)
    SimulatorStatusControl St_SimulatorStatusControl; // @ID(2)
} SimulatorControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct SingleAirBorneFunctionalUnitStatusMsg
{
    UDP_MessageHeader St_MessageHeader; // @ID(0)
    AirBorneUnitStatusData St_AirBorneUnitStatusData; // @ID(1)
} SingleAirBorneFunctionalUnitStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct SingleVFRefuelingParas
{
    DeviceAttribute St_DeviceAttribute; // @ID(0)
    TubeParas Arr_TubeParas[3]; // @ID(1)
    JointData Arr_JointData[3]; // @ID(2)
    RefuelingLightData Arr_RefuelingLightData[3]; // @ID(3)
    WakeInfluence Arr_WakeInfluence[3]; // @ID(4)
} SingleVFRefuelingParas; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareControlCMDMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    std::vector<StSoftwareAttrControl> Seq_StSoftwareAttrControl; // @ID(2) /* maximum length = (255) */
} SoftwareControlCMDMsg; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareGroupStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    std::vector<StSoftwareAttrStatus> Seq_StSoftwareAttrStatus; // @ID(2) /* maximum length = (2000) */
} SoftwareGroupStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct SoftwareStatusMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    SoftwareAttribute St_SoftwareAttribute; // @ID(1)
    SoftwareRunningStatus St_SoftwareRunningStatus; // @ID(2)
} SoftwareStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct TacanWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    DeviceAttribute St_DeviceAttribute; // @ID(1)
    TacanParas St_TacanParas; // @ID(2)
} TacanWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct TerrainDataMsg
{
    SM_MessageHeader St_SMMessageHeader; // @ID(0)
    TerrainData St_TerrainData; // @ID(1)
} TerrainDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct TrainingTerminalStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    TrainingTerminalAttribute St_TrainingTerminalAttribute; // @ID(2)
} TrainingTerminalStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct TubePutStatus
{
    unsigned char U1_TubePutStatus; // @ID(0)
} TubePutStatus; // @Extensibility(EXTENSIBLE)

typedef struct UAVControlMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    UAVAttribute St_UAVAttribute; // @ID(1)
    SoftwareControl St_SoftwareControl; // @ID(2)
} UAVControlMsg; // @Extensibility(EXTENSIBLE)

typedef struct UPSRunningStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    UPSStatus St_UPSStatus; // @ID(3)
} UPSRunningStatusMsg; // @Extensibility(EXTENSIBLE)

typedef struct VCMemberInitFlightParas
{
    EntityAttribute St_EntityAttribute; // @ID(0)
    InitFlightParas St_InitFlightParas; // @ID(1)
} VCMemberInitFlightParas; // @Extensibility(EXTENSIBLE)

typedef struct VFActiveJamWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<ActiveJamWorkingParas> St_ActiveJamWorkingParas; // @ID(1) /* maximum length = (200) */
} VFActiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFAppearanceMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFAppearance> Seq_VFAppearance; // @ID(1) /* maximum length = (200) */
} VFAppearanceMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFAttackTargetListMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<VFAttackTargetList> Seq_VFAttackTargetList; // @ID(1) /* maximum length = (200) */
} VFAttackTargetListMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFElecOptDeteWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<ElecOptDeteWorkingParas> St_ElecOptDeteWorkingParas; // @ID(1) /* maximum length = (200) */
} VFElecOptDeteWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFElecTargetParaMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<ElecTargetPara> Seq_ElecTargetPara; // @ID(1) /* maximum length = (200) */
} VFElecTargetParaMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFEntityExtralFlightDataMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFEntityExtralFlightData> Seq_VFEntityExtralFlightData; // @ID(1) /* maximum length = (200) */
} VFEntityExtralFlightDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFGroundMovingTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFGroundMovingTSPI> Seq_VFGroundMovingTSPI; // @ID(1) /* maximum length = (2000) */
} VFGroundMovingTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFIFFEmitFlagParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFIFFEmitFlagParas> St_SingleVFIFFEmitFlagParas; // @ID(1) /* maximum length = (200) */
} VFIFFEmitFlagParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFIFFIntgParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFIFFIntgParas> St_SingleVFIFFIntgParas; // @ID(1) /* maximum length = (200) */
} VFIFFIntgParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFIFFRespParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFIFFRespParas> St_SingleVFIFFRespParas; // @ID(1) /* maximum length = (200) */
} VFIFFRespParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFLaserWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<LaserWorkingParas> St_LaserWorkingParas; // @ID(1) /* maximum length = (200) */
} VFLaserWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFLinkComEmitStatusParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFLinkComEmitStatusParas> St_SingleVFLinkComEmitStatusParas; // @ID(1) /* maximum length = (200) */
} VFLinkComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFMunitionDisplayMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MunitionDisplay> Seq_VFWeaponDisplay; // @ID(1) /* maximum length = (200) */
} VFMunitionDisplayMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFMunitionKillNotifyMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MunitionKillNotify> Seq_VFMunitionKillNotify; // @ID(1) /* maximum length = (200) */
} VFMunitionKillNotifyMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFMunitionTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MunitionTSPI> Seq_VFMunitionTSPI; // @ID(1) /* maximum length = (200) */
} VFMunitionTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFMunitionWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<MunitionWorkingParas> Seq_VFMunitionWorkingParas; // @ID(1) /* maximum length = (200) */
} VFMunitionWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFPassiveJamWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<PassiveJamWorkingParas> St_PassiveJamWorking; // @ID(1) /* maximum length = (200) */
} VFPassiveJamWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFRadarWorkingParas1Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFRadarWorkingParas> Seq_VFRadarWorkingParas; // @ID(1) /* maximum length = (200) */
} VFRadarWorkingParas1Msg; // @Extensibility(EXTENSIBLE)

typedef struct VFRadarWorkingParas2Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFRadarWorkingParas> Seq_VFRadarWorkingParas; // @ID(1) /* maximum length = (200) */
} VFRadarWorkingParas2Msg; // @Extensibility(EXTENSIBLE)

typedef struct VFRadarWorkingParas3Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFRadarWorkingParas> Seq_VFRadarWorkingParas; // @ID(1) /* maximum length = (200) */
} VFRadarWorkingParas3Msg; // @Extensibility(EXTENSIBLE)

typedef struct VFRadarWorkingParas4Msg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFRadarWorkingParas> Seq_VFRadarWorkingParas; // @ID(1) /* maximum length = (200) */
} VFRadarWorkingParas4Msg; // @Extensibility(EXTENSIBLE)

typedef struct VFSimAALinkParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFSimAALinkParas> Seq_VFSimAALinkParas; // @ID(1) /* maximum length = (200) */
} VFSimAALinkParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFSimAALinkReportParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleSimOperationReport> seq_SimOperationReport; // @ID(1) /* maximum length = (200) */
} VFSimAALinkReportParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFStationaryEntityPosMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFStationaryEntityPos> Seq_VFStationaryEntityPos; // @ID(1) /* maximum length = (2000) */
} VFStationaryEntityPosMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFSurfaceTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFSurfaceTSPI> Seq_VFSurfaceTSPI; // @ID(1) /* maximum length = (2000) */
} VFSurfaceTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFTSPIMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFTSPI> Seq_VFTSPI; // @ID(1) /* maximum length = (200) */
} VFTSPIMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFTacanWorkingParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFTacanWorkingParas> Seq_VFTacanWorkingParas; // @ID(1) /* maximum length = (200) */
} VFTacanWorkingParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VFVoiceComEmitStatusParasMsg
{
    MessageHeader St_MessageHeader; // @ID(0)
    std::vector<SingleVFVoiceComEmitStatusParas> St_SingleVFVoiceComEmitStatusParas; // @ID(1) /* maximum length = (200) */
} VFVoiceComEmitStatusParasMsg; // @Extensibility(EXTENSIBLE)

typedef struct VisiblelightVedioDataMsg
{
    UDP_MessageHeader St_MessageHeader; // @ID(0)
    VisiblelightVedioData St_VisiblelightVedioData; // @ID(1)
} VisiblelightVedioDataMsg; // @Extensibility(EXTENSIBLE)

typedef struct VisualDisplayStatusMsg
{
    MaintMsgHeader St_MessageHeader; // @ID(0)
    AreaAttribute St_AreaAttribute; // @ID(1)
    MaintDeviceAttribute St_MaintDeviceAttribute; // @ID(2)
    VisualDisplay St_VisualDisplay; // @ID(3)
} VisualDisplayStatusMsg; // @Extensibility(EXTENSIBLE)




#ifdef __cplusplus
}
#endif
#endif