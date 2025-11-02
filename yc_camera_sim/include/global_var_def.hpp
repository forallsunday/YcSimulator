#pragma once

#include <ICD/ICDB_TOPIC_STRUCT_IRRM.H>

//---------------------------------外部消息定义----------------------------------------

// 接收的消息，需要使用其参数
typedef struct MsgRecvAll {
    SYM_OPERATIONAL_PARAS   m_SYM_OPERATIONAL_PARAS;   // 系统管理工作参数报告
    SYM_TIME_REPORT         m_SYM_TIME_REPORT;         // 系统管理时间信息报告
    INS1_OPERATIONAL_PARAS  m_INS1_OPERATIONAL_PARAS;  // INS1工作参数报告
    INS2_OPERATIONAL_PARAS  m_INS2_OPERATIONAL_PARAS;  // INS2工作参数报告
    INS3_OPERATIONAL_PARAS  m_INS3_OPERATIONAL_PARAS;  // INS3工作参数报告
    INS1_NAV_DATA           m_INS1_NAV_DATA;           // INS1导航数据
    INS2_NAV_DATA           m_INS2_NAV_DATA;           // INS2导航数据
    INS3_NAV_DATA           m_INS3_NAV_DATA;           // INS3导航数据
    ABSOLUTE_NAV_DATA_FUSED m_ABSOLUTE_NAV_DATA_FUSED; // 绝对导航融合飞行参数
    NAV_PARAS               m_NAV_PARAS;               // 导航参数报告
    MISSION_EVENT_REPORT    m_MISSION_EVENT_REPORT;    // 战术任务事件报告
} MsgRecvAll;

// 发送的消息
typedef struct MsgSendAll {
    IRST_ACT_REQ_REPORT            m_IRST_ACT_REQ_REPORT;            // IRST_活动请求通告1
    WORK_STATE_REPORT              m_WORK_STATE_REPORT;              // 工作状态报告2 (包含上电次数)
    IRST_OPERATIONAL_PARAS         m_IRST_OPERATIONAL_PARAS;         // IRST工作参数报告6
    IRST_OPERATIONAL_PARAS         m_IRST_OPERATIONAL_PARAS_temp;    // IRST工作参数报告6——用于比较与上一次是否一致，不一致则上报
    HW_CONFIG_INFO_REPORT          m_HW_CONFIG_INFO_REPORT;          // 硬件配置信息报告4
    SW_CONFIG_INFO_REPORT          m_SW_CONFIG_INFO_REPORT;          // 软件配置信息报告5
    PHM_DATA_RAW_IRST              m_PHM_DATA_RAW_IRST;              // 健康管理_Raw数据_IRST7
    PHM_DATA_EVENT_MS_SUB          m_PHM_DATA_EVENT_MS_SUB;          // 健康管理_Event数据_MS_SUB8
    PHM_DATA_HMC_MS_SUB            m_PHM_DATA_HMC_MS_SUB;            // 健康管理_HMC数据_MS_SUB9
    DATABASEINFO                   m_DATABASEINFO;                   // 数据库信息3
    IRST_PIXEL_PARAS               m_IRST_PIXEL_PARAS;               // IRST像元参数10
    IRST_LOS                       m_IRST_LOS;                       // 上报los数据
    IR_NAV_DATA                    m_IR_NAV_DATA;                    // 光电IMU导航数据
    RECONNAISED_AREA_IR_2GCS_EVENT m_RECONNAISED_AREA_IR_2GCS_EVENT; // 侦察覆盖区域参数_IR,红外注释信息
    RECONNAISED_AREA_TV_2GCS_EVENT m_RECONNAISED_AREA_TV_2GCS_EVENT; // 侦察覆盖区域参数_TV,可见注释信息
} MsgSendAll;

//---------------------------------外部消息定义------------------END----------------------