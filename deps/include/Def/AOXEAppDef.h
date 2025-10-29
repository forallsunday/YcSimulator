/*******************************************************************************
        2024-4-3, 10:58:30, 4361, ���ܽڵ㶨���, ���ù������ɣ������޸�
*******************************************************************************/
#ifndef AOXEAPPDEF_H
#define AOXEAPPDEF_H
// #include	"BasicTypes.h"

/*	����	*/
typedef enum {
    V_DOMAIN_NULL = -1,
    V_TS          = 0x0, /*	�����鱨������	*/
    V_AM          = 0x1, /*	ϵͳ������	*/
    V_PM          = 0x2, /*	����������	*/
    V_SR          = 0x3, /*	��������	*/
    V_MI          = 0x4, /*	ά���ӿ�	*/
    V_WF          = 0x5, /*	���������	*/
    V_VMS         = 0x6, /*	�ɹ�ϵͳ	*/
    V_MS          = 0x7, /*	������	*/
    V_NAS         = 0x8, /*	����ϵͳ	*/
    V_PV          = 0x9, /*	ָ�ؽӿ���	*/
    V_DC          = 0xa, /*	���ݲɼ���	*/
    V_DL          = 0xb, /*	���ϵͳ��	*/
    V_DOMAIN_MAX  = 998,
} DOMAIN_TYPE;

/*	����������	*/
typedef enum {
    V_SUBSYS_NULL     = -1,
    V_AIP             = 0x0,  /*	�鱨����	*/
    V_JAS             = 0x1,  /*	Σ������	*/
    V_TGF             = 0x2,  /*	Ŀ���ں�	*/
    V_LAS             = 0x3,  /*	ɱ��������	*/
    V_NAF             = 0x4,  /*	�����ں�	*/
    V_SYM             = 0x5,  /*	ϵͳ����	*/
    V_AOXE            = 0x6,  /*	ִ�л���	*/
    V_GSM             = 0x7,  /*	���Ĵ���	*/
    V_PHM             = 0x8,  /*	��������	*/
    V_IRR             = 0x9,  /*	�ۺϹ��	*/
    V_CRS             = 0xa,  /*	ͨ�����	*/
    V_CNI             = 0xb,  /*	ͨѶ����	*/
    V_EWJ             = 0xc,  /*	����ս����	*/
    V_ERD             = 0xd,  /*	Ԥ���״�	*/
    V_EWS             = 0xe,  /*	����ս���澯	*/
    V_SRM             = 0xf,  /*	����������	*/
    V_RDR             = 0x10, /*	�������״�	*/
    V_PMA             = 0x11, /*	��Яά���ӿ��豸	*/
    V_GMP             = 0x12, /*	����ά���ӿڰ�	*/
    V_SMS             = 0x13, /*	���������	*/
    V_FCC             = 0x14, /*	��ؽ���	*/
    V_VCA             = 0x15, /*	�ɹܼ����A	*/
    V_VCB             = 0x16, /*	�ɹܼ����B	*/
    V_TMM             = 0x17, /*	ս������	*/
    V_NAC             = 0x18, /*	��������	*/
    V_TRP             = 0x19, /*	��в��Ӧ	*/
    V_IN3             = 0x1a, /*	�ߵ�3	*/
    V_IN1             = 0x1b, /*	�ߵ�1	*/
    V_IN2             = 0x1c, /*	�ߵ�2	*/
    V_DCR             = 0x1d, /*	�һ�Ͻӿ�	*/
    V_DCL             = 0x1e, /*	���Ͻӿ�	*/
    V_MDC             = 0x1f, /*	�������ݲɼ�	*/
    V_MDE             = 0x20, /*	ά�����ݼ�¼	*/
    V_DM              = 0x21, /*	���ݹ���	*/
    V_DLS             = 0x22, /*	���ϵͳ	*/
    V_SUB_DOMAIN_TYPE = 9998,
} SUB_DOMAIN_TYPE;

/*	���ܽڵ㶨��	*/
typedef enum {
    V_NODE_JASM = 0x0961, /*	Σ��������Ԫ	*/
    V_NODE_TGFI = 0x0901, /*	�ۺ�ʶ��	*/
    V_NODE_TGFS = 0x08FF, /*	����Ŀ���ں�	*/
    V_NODE_TGFA = 0x08FE, /*	�տ�Ŀ���ں�	*/
    V_NODE_CPEG = 0x0900, /*	Эͬ��ս	*/
    V_NODE_NAFM = 0x0835, /*	�����ںϴ���Ԫ	*/
    V_NODE_SYMM = 0x17D5, /*	ϵͳ����Ԫ	*/
    V_NODE_SYMD = 0x17D6, /*	ϵͳ���ݿⵥԪ	*/
    V_NODE_APHM = 0x1BBE, /*	�ɻ�ϵͳ��������Ԫ	*/
    V_NODE_MPHL = 0x1BBD, /*	����ϵͳ�󽡿�����Ԫ	*/
    V_NODE_MPHR = 0x1BC1, /*	����ϵͳ�ҽ�������Ԫ	*/
    V_NODE_IRRM = 0x076D, /*	���׹���Ԫ	*/
    V_NODE_CRSM = 0x0A8D, /*	ͨ��������	*/
    V_NODE_CNLA = 0x0644, /*	����������	*/
    V_NODE_CNIM = 0x0641, /*	CNIϵͳ���ƹ���	*/
    V_NODE_EWJM = 0x07D1, /*	����ս���Ź���	*/
    // V_NODE_ERDM	=	0x0A29,	/*	Ԥ���״����	*/
    V_NODE_EDRM = 0x0A29, /*	Ԥ���״����	*/
    V_NODE_EWSM = 0x0709, /*	����ս�������	*/
    V_NODE_SRMM = 0x03E9, /*	�������������Ԫ	*/
    V_NODE_RDRM = 0x06A5, /*	�״����Ԫ	*/
    V_NODE_PMAM = 0x23F1, /*	��Яά���ӿڵ�Ԫ	*/
    V_NODE_GMPM = 0x23F2, /*	����ά���ӿڵ�Ԫ	*/
    V_NODE_VCAM = 0x1FA5, /*	�ɿص�ԪA	*/
    V_NODE_VCBM = 0x1FA6, /*	�ɿص�ԪB	*/
    V_NODE_VCCM = 0x1FA7, /*	�ɿص�ԪC������ߵ�ֱ����	*/
    V_NODE_IFRP = 0x0C1F, /*	�����ع滮��Ԫ	*/
    V_NODE_TMMM = 0x0C1D, /*	ս��������Ԫ	*/
    V_NODE_NACL = 0x0C81, /*	�󵼺�����Ԫ	*/
    V_NODE_NACR = 0x0C82, /*	�ҵ�������Ԫ	*/
    V_NODE_TRPM = 0x0CE5, /*	��в��Ӧ��Ԫ	*/
    V_NODE_IN1M = 0x0515, /*	�ߵ�1��Ԫ	*/
    V_NODE_IN2M = 0x0579, /*	�ߵ�2��Ԫ	*/
    V_NODE_IN3M = 0x05DD, /*	�ߵ�3��Ԫ	*/
    V_NODE_DCRM = 0x1451, /*	�һ�Ͻӿڵ�Ԫ	*/
    V_NODE_DCLM = 0x13ED, /*	���Ͻӿڵ�Ԫ	*/
    V_NODE_DCRD = 0x1452, /*	�����ܵ�Ԫ	*/
    V_NODE_DCLD = 0x13EE, /*	�����ܵ�Ԫ	*/

    V_NODE_EIPM = 0x0903, /*	����鱨�������ܺ������Ϊ�����Ӧ�ã�	*/
    V_NODE_IIPM = 0x0902, /*	ͼ���鱨�������ܺ������Ϊ�����Ӧ�ã�	*/

    V_NODE_LASM = 0x09C5, /*	ɱ��������Ԫ	*/
    V_NODE_SMET = 0x1008, /*	Ƕѵ��������	*/
    V_NODE_SMSM = 0x1005, /*	������ϵͳ����	*/
    V_NODE_FCAS = 0x106A, /*	�����ص�Ԫ	*/
    V_NODE_FCCM = 0x1069, /*	��ؽ��㵥Ԫ	*/

    V_NODE_SMU1 = 0x1006, /*	FRIU1�ӿڵ�Ԫ	*/
    V_NODE_SMU2 = 0x010A, /*	FRIU2�ӿڵ�Ԫ	*/
    V_NODE_DCLP = 0x00F1, /*	���ͼ��Ԫ	*/
    V_NODE_MNTR = 0x113E, /*	ϵͳ���ݿⵥԪ	*/
    V_NODE_ADAS = 0x213E, /*	ϵͳ���ݿⵥԪ	*/
    V_NODE_ICPM = 0x313E, /*	ϵͳ���ݿⵥԪ	*/

    V_NODE_CDLM = 0x2009, /*	C��·�˻������ң�⣩	*/
    V_NODE_KDLM = 0x200A, /*	K��·�˻������ң�⣩	*/

    // ִ�л����ڵ�id������
    V_NODE_AOXE_D = 0x17DB, /*	ִ�л���_Ŀ��	*/
    V_NODE_AOXE_S = 0x17DA, /*	ִ�л���_Դ	*/

    // cpum�ڵ�idΪ���ֶ�����
    V_NODE_CPDM = 0x17D8, /*	���Ĺ���Ԫ	*/
    V_NODE_CPUM = 0x17D9, /*	CPU����Ԫ	*/

    // IPM1��AIMP1��AIMP2��
    V_NODE_CPUMGP11 = 0x6110, // V_NODE_CPUM_AIMP1_IPM1_1��D2000/8��
    V_NODE_CPUMGP12 = 0x6111, // V_NODE_CPUM_AIMP2_IPM1_1��D2000/8��
    V_NODE_CPUMGP13 = 0x6112, // AIMP1_IPM1_2��FT2000/4��
    V_NODE_CPUMGP14 = 0x6113, // AIMP2_IPM1_2��FT2000/4��

    // IPM2��AIMP1��AIMP2��
    V_NODE_CPUMGP21 = 0x6114, // V_NODE_CPUM_AIMP1_IPM2_1��D2000/8��
    V_NODE_CPUMGP22 = 0x6115, // V_NODE_CPUM_AIMP2_IPM2_1��D2000/8��
    V_NODE_CPUMGP23 = 0x6116, // AIMP1_IPM2_2��FT2000/4��
    V_NODE_CPUMGP24 = 0x6117, // AIMP2_IPM2_2��FT2000/4��

    // IPM3��AIMP1��AIMP2��
    V_NODE_CPUMGP31 = 0x6118, // V_NODE_CPUM_AIMP1_IPM3_1��D2000/8��
    V_NODE_CPUMGP32 = 0x6119, // V_NODE_CPUM_AIMP2_IPM3_1��D2000/8��
    V_NODE_CPUMGP33 = 0x6120, // AIMP1_IPM3_2��FT2000/4��
    V_NODE_CPUMGP34 = 0x6121, // AIMP2_IPM3_2��FT2000/4��

    // IPM4��AIMP1��AIMP2��
    V_NODE_CPUMGP41 = 0x6122, // V_NODE_CPUM_AIMP1_IPM4_1��D2000/8��
    V_NODE_CPUMGP42 = 0x6123, // V_NODE_CPUM_AIMP2_IPM4_1��D2000/8��
    V_NODE_CPUMGP43 = 0x6124, // AIMP1_IPM4_2��FT2000/4��
    V_NODE_CPUMGP44 = 0x6125, // AIMP2_IPM4_2��FT2000/4��

    // IOM��AIMP1��AIMP2��
    V_NODE_CPUMGI11 = 0x6126, // V_NODE_CPUM_AIMP1_IOM11
    V_NODE_CPUMGI12 = 0x6127,
    V_NODE_CPUMGI21 = 0x6128, // V_NODE_CPUM_AIMP2_IOM11
    V_NODE_CPUMGI22 = 0x6129,

    V_NODE_CPUMSP11 = 0x6130,
    V_NODE_CPUMSP21 = 0x6131,
    V_NODE_CPUMSP31 = 0x6132,
    V_NODE_CPUMSP41 = 0x6133,

    V_NODE_CPUMPS11 = 0x6134,
    V_NODE_CPUMPS21 = 0x6135,

    V_NODE_CPUMNS11 = 0x6136,
    V_NODE_CPUMNS21 = 0x6137,

} FUNCTION_NODE_TYPE;

/*	���ȼ�����	*/
typedef enum {
    AOXETASK_HIGH_PRIORITY = 0,
    AOXETASK_ABOVE_NORMAL,
    AOXETASK_NOMAL,
    AOXETASK_BELOW_NORMAL,
    AOXETASK_IDLE,
    APPTASK_HIGH_PRIORITY,
    APPTASK_ABOVE_NORMAL,
    APPTASK_NOMAL,
    APPTASK_BELOW_NORMAL,
    APPTASK_IDLE,
    AOXETASK_ABOVE_NORMAL_1,
    AOXETASK_ABOVE_NORMAL_2,
    AOXETASK_ABOVE_NORMAL_3,
    AOXETASK_ABOVE_NORMAL_4,
    AOXETASK_ABOVE_NORMAL_5,
    AOXETASK_ABOVE_NORMAL_6,
    AOXETASK_NOMAL_1,
    AOXETASK_NOMAL_2,
    AOXETASK_NOMAL_3,
    AOXETASK_NOMAL_4,
    AOXETASK_NOMAL_5,
    AOXETASK_NOMAL_6,
    AOXETASK_NOMAL_7,
    AOXETASK_NOMAL_8,
    AOXETASK_NOMAL_9,
} PRIORITY_TYPE_DEF;

typedef struct
{
    FUNCTION_NODE_TYPE function_node_no;   /*	���ܽڵ��	*/
    char              *function_node_name; /*	���ܽڵ���	*/
} FUNCTION_NODE_TABLE;

#endif /*	AOXEAPPDEF_H	*/
