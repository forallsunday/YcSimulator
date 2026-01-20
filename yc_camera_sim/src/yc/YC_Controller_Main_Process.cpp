/*
 * YC_Controller_Process.c
 *
 *  Created on: 2025年5月16日
 *      Author: wangx
 */

#include "YC_Controller_Main_Process.h"
#include "YC_Controller_Constant_Define.h"
// #include "YC_Controller_FC_Trans.h"
// #include "pciConfigLib.h"
/*标准头文件*/
// #include <periodtasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <timer.h> // 天脉的头文件
#include <unistd.h>

/*非标准头文件*/
#include "AppTopicIdDef.h"
#include "YC_Controller_Computer.h"
#include "YC_Controller_FPGA_Mess.h"
// #include "YC_Controller_FPGA_Trans.h"
#include "YC_Controller_HMC_Process.h"
#include "YC_Controller_Mess_Process.h"
#include "YC_Controller_TG_Process.h"
#include "YC_Controller_globalVal_Ext.h"
#include "YC_Controller_init.h"
// #include "acClock.h"
// #include "fcUsrVos.h"
// #include "ficType.h"
// #include "ft_gpio.h"
// #include "ioFcApi.h"
// #include "ioFcCfg.h"
// #include "semYc.h"

#include <global_vars.h>
#include <log_def.h>
#include <udp_trans.h>
#include <utils.h>

#include <chrono>

bool running_main_ctrl;
bool running_other_process;
bool running_periodic_send;

bool freeze_all_process = false;

using namespace std::chrono_literals;

// act_req消息处理及主流程控制
void main_Control_And_Mess_Process_Act_req_task() {
    //	static UINT64 time_start = 0;
    //	static UINT64 time_end = 0;

    PtrUdpPacket p_packet;
    while (running_main_ctrl) {
        if (freeze_all_process) {
            std::this_thread::sleep_for(5ms);
            continue;
        }

        if (sim::queue_IRST_act_req.tryPop(p_packet)) {
            localUpdate(cmd_From_FC.current_IRST_ACT_REQ, p_packet.get());
            // 发送消息——回复响应ECHO
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_ECHO, V_ACT_REFUSED_REASON_NA);
            act_req_mess_Process(); // 活动请求指令判断
        }

        // sleep_ms(2000);

        // 如果收到FPGA中断，或者5ms时间到，正常流程，每5ms处理主控工作流程、计算
        if (flag_Fpga_Interrupt == 1) {
            make_Mess_To_PCS_DATA(0); // 给pos发送数据

            // ACoreOs_clock_get_timestamp(&time_start);
            // 工作流程控制，在这里根据指令开展判断、执行工作、回复IRST_ACT_REQ_REPORT
            // 先处理所有从fpga收到的分系统消息
            fpga_Mess_Process();

            //			ACoreOs_clock_get_timestamp(&time);
            //			logMsg("time start:%d\n",time,2,3,4,5,6);
            // 工作流程控制----总控，需要在各流程中执行：
            // 1.参数计算，并更新参数缓存
            // 2.构建向fpga发送的消息结构体，更新参数信息——统一构建所有内部消息
            Work_Control();
            // ACoreOs_clock_get_timestamp(&time_end);
            // logMsg("time:%d\n",time_start,2,3,4,5,6);
            // logMsg("time:%d\n",time_end,2,3,4,5,6);
            // logMsg("time:%d\n",(time_end - time_start),2,3,4,5,6);

            //			ACoreOs_clock_get_timestamp(&time);
            //			logMsg("time end:%d\n",time,2,3,4,5,6);
            // TEST--------------------------------------------------------------------------------------
            //			test_forFpga();
            //			test_forTXCL_ZZXX();//注释信息测试
            //			printf("zt818  Len:%d; total Len:%d\n",sizeof(A818_EO_IMAGE), sizeof(Mess_To_TXCL_ZSXX));//132,360
            //			make_Mess_To_TXCL_ZSXX();
            // TEST--------------------------------------------------------------------------------------

            // 标志位清零
            flag_Fpga_Interrupt = 0;
        }

        // 如果fpga掉线,错误处理，异常流程，
        // if (ACoreOs_atomic32_get(&flag_Fpga_down_times) > 5) // 如果掉线超过五次，进行异常处理
        // {
        //     logMsg("========fpga down!!!!\r\n", 1, 2, 3, 4, 5, 6);
        //     ACoreOs_atomic32_set(&flag_Fpga_down_times, 5);
        //     //			flag_Fpga_down_times = 5;//重新置位
        // 异常流程处理,基本不可能出现这种情况

        //			//解互斥锁
        //			unLockBinarySem(bSemId_flag_Fpga_down_times);
        // }
        //		else
        //		{
        //			//解互斥锁
        //			unLockBinarySem(bSemId_flag_Fpga_down_times);
        //		}
        // usleep(SHORT_MSG_SLEEP_TIME); // 延时
        sleep_us(SHORT_MSG_SLEEP_TIME);
    }
}

// 其他消息处理
void fc_Mess_Process_Others_task() {
    // MESS_NODE *p_MESS_NODE; // 节点
    int          i = 0;
    PtrUdpPacket p_packet;
    auto         timeout = std::chrono::milliseconds(5);

    while (running_other_process) {
        if (freeze_all_process) {
            std::this_thread::sleep_for(5ms);
            continue;
        }

        if (sim::queue_IRST_act_req.waitForAndPop(p_packet, timeout)) {
            // 判断消息类型，此处处理所有其他类型消息，逐一在case中添加
            // switch (p_MESS_NODE->mess_typeId) {
            switch (p_packet->topicId) {

            case V_TOPIC_SYMM_SYM_OPERATIONAL_PARAS: // 系统管理工作参数报告
                localUpdate(temp_mess_FromFc_SYM_OPERATIONAL_PARAS, p_packet.get());

                for (i = 0; i < 150; i++) // 遍历消息中的所有节点
                {
                    // 以下几个节点，发送工作参数报告消息
                    if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_IIPM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_IIPM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_IIPM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_IIPM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_DCLD) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_DCLD != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_DCLD = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_DCLD = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_TMMM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_TMMM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_TMMM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_TMMM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_DCRM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_DCRM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_DCRM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_DCRM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_DCLM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_DCLM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_DCLM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_DCLM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_DCRD) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_DCRD != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_DCRD = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_DCRD = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_SRMM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_SRMM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告
                            //						vnode_APP_STATE.app_state_V_NODE_SRMM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_SRMM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    }
                    // 以下几个节点，发送工作状态报告消息、健康管理_HMC数据_MS_SUB、健康管理_Event数据_MS_SUB
                    else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_MPHL) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_MPHL != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            send_Mess_WORK_STATE_REPORT(0, 0); // 工作状态报告,参数为bit百分比
                            //						send_Mess_PHM_DATA_EVENT_MS_SUB();//健康管理_Event数据_MS_SUB
                            //						send_Mess_PHM_DATA_HMC_MS_SUB();//健康管理_HMC数据_MS_SUB
                            //						vnode_APP_STATE.app_state_V_NODE_MPHL = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_MPHL = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    } else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_MPHR) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_MPHR != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            send_Mess_WORK_STATE_REPORT(0, 0); // 工作状态报告,参数为bit百分比
                            //						send_Mess_PHM_DATA_EVENT_MS_SUB();//健康管理_Event数据_MS_SUB
                            //						send_Mess_PHM_DATA_HMC_MS_SUB();//健康管理_HMC数据_MS_SUB
                            //						vnode_APP_STATE.app_state_V_NODE_MPHR = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_MPHR = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    }
                    // 发送工作状态报告、软件配置项、硬件配置项消息
                    else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_SYMM) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_SYMM != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            send_Mess_WORK_STATE_REPORT(0, 0); // 工作状态报告,参数为bit百分比
                            send_Mess_HW_CONFIG_INFO_REPORT(); // 硬件配置信息报告
                            send_Mess_SW_CONFIG_INFO_REPORT(); // 软件配置信息报告
                            //						vnode_APP_STATE.app_state_V_NODE_SYMM = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_SYMM = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    }
                    // 发送数据库信息
                    else if (temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].subdomain_ID == V_NODE_SYMD) {
                        // 应用状态由非正常变成正常，则发送工作参数报告消息（首次也要发）
                        if (vnode_APP_STATE.app_state_V_NODE_SYMD != V_APP_STATE_NORMAL && temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state == V_APP_STATE_NORMAL) {
                            send_Mess_DATABASEINFO(); // 数据库信息
                            //						vnode_APP_STATE.app_state_V_NODE_SYMD = V_APP_STATE_NORMAL;
                        }
                        vnode_APP_STATE.app_state_V_NODE_SYMD = static_cast<APP_STATE>(temp_mess_FromFc_SYM_OPERATIONAL_PARAS.sys_network_state[i].app_state);
                    }
                }
                break;

            default:
                break;
            }
            // usleep(SHORT_MSG_SLEEP_TIME); // 延时
        }
    }
}

// 周期消息发送处理
void fc_Mess_Send_Period_task() {
    using namespace std::chrono;
    using clock = std::chrono::steady_clock;

    static int a               = 0;
    static int upload_pack_num = 1; // 当前上报的第几包

    while (running_periodic_send) {
        if (freeze_all_process) {
            std::this_thread::sleep_for(5ms);
            continue;
        }
        // 当前时间
        auto next = clock::now();
        next += milliseconds(sim::periodic_interval);

        // {
        //     // !!! 20251230 测试时直接上报
        //     send_Mess_WORK_STATE_REPORT(0, 10000);
        //     send_Mess_IRST_OPERATIONAL_PARAS();
        // }

        //		logMsg("period task second:%d\n",a,2,3,4,5,6);
        a++;

        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) // 周期发送IRST_LOS消息
        {
            send_Mess_IRST_LOS(1); // 上报los数据
        }
        send_Mess_IR_NAV_DATA(); // 周期上报光电IMU导航数据

        if (a % 3 == 0) // 周期回复消息
        {
            fc_Send_Message(V_TOPIC_JT_PHOTO, (UINT8 *)&nbMess_jt_Photo, sizeof(MESS_FROMFC_JT_PHOTO));
            send_Mess_ToFC_ID_DATA_TRANSMIT_STATE(main_Control_State_Param.trans_state); // 818通道传输图像标识:1s报一次
        }

        // 健康管理------------------------------------------------------------------------------------------------------------------------
        if (a % 50 == 0 && main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_INIT) // 不在初始化状态下，每18s检查一次故障
        {
            nb_HMC_DATA_SET();
        }
        // 如果有需要上报的hmc , 可以注释掉
        if (nb_HMC_DATA.hmc_count_upload != 0) {
            send_Mess_PHM_DATA_HMC_MS_SUB(upload_pack_num); // 从1开始
            upload_pack_num++;                              // 发送下一包
            if (upload_pack_num > nb_HMC_DATA.pack_count)   // 如果已经发送完成
            {
                // 上报完成后清零
                nb_HMC_DATA.hmc_count_upload = 0; // 需要上报的HMC个数
                nb_HMC_DATA.pack_count       = 0; // 需要上报的HMC包数
                upload_pack_num              = 1;
            }
        }
        // 健康管理------------------------------------------------------------------------------------------------------------------------

        // 工作参数有变化就上报
        auto cmp_IRST_OPERATIONAL_PARAS =
            [](const IRST_OPERATIONAL_PARAS &a, const IRST_OPERATIONAL_PARAS &b) -> bool {
            constexpr size_t offset = sizeof(MSG_PUBLISH_TIME_TYPE_DEF);
            constexpr size_t size   = sizeof(IRST_OPERATIONAL_PARAS) - offset;
            return memcmp(
                       reinterpret_cast<const uint8_t *>(&a) + offset,
                       reinterpret_cast<const uint8_t *>(&b) + offset,
                       size) == 0;
        };
        // 比较后不一样的话
        bool is_equal = cmp_IRST_OPERATIONAL_PARAS(
            temp_mess_ToFC_IRST_OPERATIONAL_PARAS, mess_ToFC_IRST_OPERATIONAL_PARAS);
        // INFO_LOG_IN_FUNC("IRST_OPERATIONAL_PARAS is equal: %d", is_equal);
        if (!is_equal) {
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            memcpy(&temp_mess_ToFC_IRST_OPERATIONAL_PARAS, &mess_ToFC_IRST_OPERATIONAL_PARAS, sizeof(IRST_OPERATIONAL_PARAS));
        }

        // ACoreOs_periodtask_wait_period(); // 周期任务必要函数，不可删除！！！释放

        // Note: 模拟器持续发送 WORK_STATE_REPORT 消息 发送的为一个较大值 这样启动剩余时间和自检率不会更新
        send_Mess_WORK_STATE_REPORT(1e7, 1e7); // 工作状态报告,参数为bit百分比

        std::this_thread::sleep_until(next);
    }
}

// lcy: 在fpga仿真中实现
// 接收到fpage中断的响应函数0A2,//0A_3为曝光同步信号，高有效，持续4ms
void isr_Fpga_Mess(UINT32 vector, void *context, LONG param) {
    //	static UINT64 time_start = 0;
    //	static UINT64 time_end = 0;
    // int Int0A;
    //	ACoreOs_clock_get_timestamp(&time_start);
    // Int0A = *(volatile unsigned int *)(FT_GPIO0_BASE + GPIO_INTSTATUS); // gpio中断状态

    // if (Int0A & (1 << 2)) // 判断中断管脚,0A2
    // {
    //     // 读fpag
    //     fpga_Recv(&mess_From_TJ, OFFSET_FROM_FPGA_TJ, sizeof(Mess_From_TJ));             // 读调焦
    //     fpga_Recv(&mess_From_KJ, OFFSET_FROM_FPGA_KJ, sizeof(Mess_From_KJ));             // 从框架收
    //     fpga_Recv(&temp_mess_From_TXCL, OFFSET_FROM_FPGA_IMAGE, sizeof(Mess_From_TXCL)); // 从图像处理收
    //     if (temp_mess_From_TXCL.head1 == 0xEB) {
    //         memcpy(&mess_From_TXCL, &temp_mess_From_TXCL, sizeof(Mess_From_TXCL));
    //     }
    //     fpga_Recv(&mess_From_DY, OFFSET_FROM_FPGA_DY, sizeof(Mess_From_DY));              // 从电源收
    //     fpga_Recv(&mess_From_GCWK, OFFSET_FROM_FPGA_CK, sizeof(MESS_From_GCWK));          // 从光窗温控收
    //     fpga_Recv(&mess_From_PCS_DATA, OFFSET_FROM_FPGA_PCS, sizeof(Mess_From_PCS_DATA)); // 从PCS收
    //     fpga_Recv(&mess_From_JLY, OFFSET_FROM_FPGA_JLY, sizeof(MESS_From_JLY));           // 向记录仪发
    //     fpga_Recv(&mess_From_QNSJ, OFFSET_FROM_FPGA_QNSJ, sizeof(MESS_From_QNSJ));        // 向球内数据发
    //     fpga_Recv(&mess_From_FPGA, OFFSET_FROM_FPGA_ZKFPGA, sizeof(MESS_From_FPGA));      // 向FPGA发

    //     // 写fpga
    //     fpga_Send(&mess_To_TJ, OFFSET_TO_FPGA_TJ, sizeof(Mess_To_TJ));                      // 写调焦
    //     fpga_Send(&mess_To_KJ, OFFSET_TO_FPGA_KJ, sizeof(Mess_To_KJ));                      // 向框架发
    //     fpga_Send(&mess_To_TXCL_CMD, OFFSET_TO_FPGA_TXCL_CMD, sizeof(Mess_To_TXCL_CMD));    // 向图像处理指令
    //     fpga_Send(&mess_To_TXCL_ZSXX, OFFSET_TO_FPGA_TXCL_ZSXX, sizeof(Mess_To_TXCL_ZSXX)); // 图像处理-注释信息
    //     fpga_Send(&mess_To_DY, OFFSET_TO_FPGA_DY, sizeof(Mess_To_DY));                      // 向电源发
    //     fpga_Send(&mess_To_GCWK, OFFSET_TO_FPGA_CK, sizeof(MESS_To_GCWK));                  // 向光窗温控发
    //     fpga_Send(&mess_TO_PCS_DATA, OFFSET_TO_FPGA_PCS, sizeof(Mess_TO_PCS_DATA));         // 向惯导发-数据包
    //     fpga_Send(&mess_To_JLY, OFFSET_TO_FPGA_JLY, sizeof(MESS_To_JLY));                   // 向记录仪发
    //     fpga_Send(&mess_To_QNSJ, OFFSET_TO_FPGA_QNSJ, sizeof(MESS_To_QNSJ));                // 向球内数据发
    //     fpga_Send(&mess_To_FPGA, OFFSET_TO_FPGA_ZKFPGA, sizeof(MESS_To_FPGA));              // 向FPGA发

    //     TG_5msInterrupt(); // 调光用

    //     //------------设置标志位------------------------
    //     // 中断响应标志位
    //     flag_Fpga_Interrupt = 1;
    //     // fpga掉线次数清零

    //     flag_Fpga_down_times = 0;
    //     //------------设置标志位---------------------------------

    //     *(volatile unsigned int *)(FT_GPIO0_BASE + GPIO_PORTA_EOI) |= (1 << 2);
    // }

    // if (Int0A & (1 << 3)) // 判断中断管脚,0A3,如果曝光信号来了
    // {
    //     flag_Fpga_bg = 1;   // 曝光信号到达
    //     TG_NBCJInterrupt(); // 内部采集信号中断调光处理
    //     *(volatile unsigned int *)(FT_GPIO0_BASE + GPIO_PORTA_EOI) |= (1 << 3);
    // }

    // //	ACoreOs_clock_get_timestamp(&time_end);
    // //	logMsg("time:%d\n",(time_end - time_start),2,3,4,5,6);
    // // 清空中断标志
    // //	*(volatile unsigned int *)(FT_GPIO0_BASE + GPIO_PORTA_EOI) = 0xff;
    // //	*(volatile unsigned int *)(FT_GPIO1_BASE + GPIO_PORTA_EOI) = 0xff;
}

// 5ms定时器响应函数，用于统计fpga掉线次数
void timer_service_func_5ms() {
    //	logMsg("timer_service_func_5ms!!!!\r\n",1,2,3,4,5,6);//中断里只能用logMsg
    // 加互斥锁
    //	lockBinarySem(bSemId_flag_Fpga_down_times);
    //	flag_Fpga_down_times++;//统计fpga未触发次数//fpga掉线次数累加
    // ACoreOs_atomic32_inc(&flag_Fpga_down_times);
    // lcy:
    flag_Fpga_down_times.fetch_add(1, std::memory_order_relaxed);
    // 解互斥锁
    //	unLockBinarySem(bSemId_flag_Fpga_down_times);
}

// 处理活动请求指令
// 能直接响应的指令在此函数中响应处理；不能直接响应的指令记录到cmd_From_FC中，后在Work_Control中处理
void act_req_mess_Process() {
    // 通用活动请求，不记录参数
    switch (cmd_From_FC.current_IRST_ACT_REQ.general_act_req) {
    case V_GENERAL_ACT_REQ_MODE_SWITCH: // 工作模式请求
        //		V_SUBSYS_MAIN_OPER_MODE_LOW_POWER = 2,		//省电模式--不响应
        //		V_SUBSYS_MAIN_OPER_MODE_STBY = 3,			//待机模式————只有拍照能响应，按正常待机处理1
        //		V_SUBSYS_MAIN_OPER_MODE_NORMAL = 4,			//正常模式--切换1——所有模式
        //		V_SUBSYS_MAIN_OPER_MODE_BACKUP = 5,			//备份模式--不响应
        //		V_SUBSYS_MAIN_OPER_MODE_TEST = 6,			//测试模式————先不管
        //		V_SUBSYS_MAIN_OPER_MODE_STOP = 7,			//停止/可关机模式-下电——回到NA，所有模式可响应1
        //		V_SUBSYS_MAIN_OPER_MODE_SW_LOAD = 8,		//软件加载——只有在收藏状态能响应？
        //		V_SUBSYS_MAIN_OPER_MODE_SW_RESTART = 9,		//软件复位——————回初始化？
        // 待机模式，只有收藏、拍照能响应，与跟特殊工作请求的"待机"逻辑一样
        if (V_SUBSYS_MAIN_OPER_MODE_STBY == cmd_From_FC.current_IRST_ACT_REQ.general_act_req_paras.subsys_main_oper_mode) {
            // 如果不在收藏、拍照模式，回复fc无法响应
            if (main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_TAKE_PIC && main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_COLLECT && main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_NA) {
                // 回复无法响应
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            } else // 如果可以响应，置标志位。在收藏、拍照过程中判断该怎样进入待机
            {
                clean_cmd_From_FC();
                cmd_From_FC.general_cmd_MODE_SWITCH = 1;
                // 记录参数
                cmd_From_FC.subsys_main_oper_mode = V_SUBSYS_MAIN_OPER_MODE_STBY;
            }
        }

        // Note: lcy 正常模式和STOP在共享内存中判断
        // 正常
        else if (V_SUBSYS_MAIN_OPER_MODE_NORMAL == cmd_From_FC.current_IRST_ACT_REQ.general_act_req_paras.subsys_main_oper_mode) {
            // 非仿真状态下, 执行设备逻辑
            if (!sim::is_simulating) {
                update_Work_State(V_SUBSYS_WORK_STATE_NORMAL); // 更新相机工作状态
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);   // 任何模式都可切入正常模式，直接切即可
                make_Mess_IRST_OPERATIONAL_PARAS();            // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS();            // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            }

        }
        // 停止/可关机模式——-下电——回到NA，所有模式可响应，在所有模式中判断该怎样进入关机
        else if (V_SUBSYS_MAIN_OPER_MODE_STOP == cmd_From_FC.current_IRST_ACT_REQ.general_act_req_paras.subsys_main_oper_mode) {
            // 非仿真状态下, 执行设备逻辑
            if (!sim::is_simulating) {
                clean_cmd_From_FC();                     // 清除指令记录
                cmd_From_FC.general_cmd_MODE_SWITCH = 1; // 可以执行的指令置为1
                // 记录参数
                cmd_From_FC.subsys_main_oper_mode = V_SUBSYS_MAIN_OPER_MODE_STOP;
            }
        }
        // Note: lcy ---------END---------------

        // 如果是测试模式（维护测试）,只切模式，不进行自检操作
        else if (V_SUBSYS_MAIN_OPER_MODE_TEST == cmd_From_FC.current_IRST_ACT_REQ.general_act_req_paras.subsys_main_oper_mode) {
            // 如果不在地面，回复fc无法响应
            if (temp_mess_FromFc_MISSION_EVENT_REPORT.WOW_main != V_WOW_MAIN_WOW_GND || V_IRST_WORK_STATE_COLLECT != cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
                // 回复无法响应
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            } else // 如果可以响应
            {
                update_Main_Mode(V_SUBSYS_MAIN_MODE_TEST); // 进入测试模式+

                //				clean_cmd_From_FC();
                //				cmd_From_FC.irst_cmd_STATE_SET = 1;//修改工作状态指令
                //				cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_BIT;
                //				update_Main_Mode(V_SUBSYS_MAIN_MODE_TEST);//

                // 回复执行完成
                send_Mess_WORK_STATE_REPORT(0, 0);  // 工作状态报告,参数为bit百分比
                make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            }
        }

        else {
            // 其他情况均回复无法响应
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

    case V_GENERAL_ACT_REQ_BIT_OPERATION: // 执行BIT请求——————只有收藏可以响应,		跟特殊工作请求的自检测逻辑一样：收藏可响应
        // 如果在收藏模式
        if (main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_TEST) {
            update_Work_State(V_SUBSYS_WORK_STATE_BIT);
            clean_cmd_From_FC();                       // 清除指令记录
            cmd_From_FC.general_cmd_BIT_OPERATION = 1; // 可以执行的指令置为1
            cmd_From_FC.bit_mode                  = (BIT_MODE)cmd_From_FC.current_IRST_ACT_REQ.general_act_req_paras.bit_mode;
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

    case V_GENERAL_ACT_REQ_MFL_OPERATION: // MFL操作请求——清除hmc记录————测试模式响应
        // 如果在测试模式且收藏模式
        if (main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_TEST && temp_mess_FromFc_MISSION_EVENT_REPORT.WOW_main != V_WOW_MAIN_WOW_AIR) // 轮载状态不在空中可以响应
        {
            // 清除mfl记录
            nb_HMC_DATA_CLEAR();
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

    case V_GENERAL_ACT_REQ_DATA_REQ: // 子域数据请求——不响应
        // 回复无法响应——无效活动
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_ACTIVITY);
        break;

    case V_GENERAL_ACT_REQ_ICP1_MODE_SWITCH: // ICP1工作模式请求——不响应
        // 回复无法响应——无效活动
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_ACTIVITY);
        break;

    case V_GENERAL_ACT_REQ_ICP2_MODE_SWITCH: // ICP2工作模式请求——不响应
        // 回复无法响应——无效活动
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_ACTIVITY);
        break;

    case V_GENERAL_ACT_REQ_UNIQUE_ACT: // 特殊活动请求
        act_req_IRST_Process();
        break;

    default:
        break;
    }
}

// 特殊活动请求指令处理，需要记录参数
void act_req_IRST_Process() {
    int i = 0;
    // 特殊活动请求——16个
    switch (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_IRS) {
    // 1.修改光电工作状态（后续在workcontrol中处理）———按状态转换图——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_IR_STATE_SET:
        // 收藏：准备中、待机、自检可响应
        if (V_IRST_WORK_STATE_COLLECT == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_PREPARE || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_BIT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {
                // 拷贝置待处理指令
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                         // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_COLLECT; // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                            // 任何模式都可切入正常模式，直接切即可
            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }
        }
        // 准备中（准备）：收藏、待机可响应
        else if (V_IRST_WORK_STATE_PREPARE == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            if ((main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY)                                                                                                             // 在收藏或待机
                && ((cmd_From_FC.irst_cmd_param_irst_form_mode == 1 && cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity == 1)                                                                                                                                      // 广域成像模式有效，且参数有值
                    || (cmd_From_FC.irst_cmd_param_irst_form_mode == 2 && (cmd_From_FC.irst_cmd_param_area_image_paras_validity[0] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[1] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[2] == 1)) // 区域成像模式有效，且参数有值
                    || (cmd_From_FC.irst_cmd_param_irst_form_mode == 3 && cmd_From_FC.irst_cmd_param_area_monitor_paras_validity == 1)))                                                                                                                                  // 区域监视模式有效，且参数有值
            {
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                         // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_PREPARE; // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                            // 任何模式都可切入正常模式，直接切即可
            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }

        }
        // 待机：收藏（执行准备）、拍照可响应
        else if (V_IRST_WORK_STATE_STBY == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
                // 拷贝置待处理指令
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                                                                                                                                                                                                                  // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_STBY;                                                                                                                                                                                             // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                                                                                                                                                                                                                     // 任何模式都可切入正常模式，直接切即可
            } else if ((main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT)                                                                                                                                                                                   // 在收藏
                       && ((cmd_From_FC.irst_cmd_param_irst_form_mode == 1 && cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity == 1)                                                                                                                                      // 广域成像模式有效，且参数有值
                           || (cmd_From_FC.irst_cmd_param_irst_form_mode == 2 && (cmd_From_FC.irst_cmd_param_area_image_paras_validity[0] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[1] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[2] == 1)) // 区域成像模式有效，且参数有值
                           || (cmd_From_FC.irst_cmd_param_irst_form_mode == 3 && cmd_From_FC.irst_cmd_param_area_monitor_paras_validity == 1)))                                                                                                                                  // 区域监视模式有效，且参数有值
            {
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                      // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_STBY; // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                         // 任何模式都可切入正常模式，直接切即可
            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }

        }
        // 拍照：待机可响应
        else if (V_IRST_WORK_STATE_TAKE_PIC == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
                main_Control_State_Param.takeTimes++; // 拍照次数累加
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                          // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_TAKE_PIC; // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                             // 任何模式都可切入正常模式，直接切即可
            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }

        }
        // 自检测：收藏可响应
        else if (V_IRST_WORK_STATE_BIT == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT) {
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1; // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_BIT;
                //				update_Main_Mode(V_SUBSYS_MAIN_MODE_TEST);//
            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }

        }
        // 静态拍照-内部使用，收藏、待机可响应
        else if (V_IRST_WORK_STATE_NB_JT == cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_work_state) {
            // 待机和收藏可以进入
            if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {

                // 拷贝置待处理指令
                clean_cmd_From_FC();
                cmd_From_FC.irst_cmd_STATE_SET             = 1;                       // 修改工作状态指令
                cmd_From_FC.irst_cmd_param_irst_work_state = V_IRST_WORK_STATE_NB_JT; // 记录参数
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);                          // 任何模式都可切入正常模式，直接切即可

            } else {
                // 回复无法响应——无效参数
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            }
        }
        // 其他指令回复无效
        else {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }

        break;
        // 2.成像模式修改——收藏、待机、拍照可接收，只有准备中、拍照有动作，其他保存参数——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_IMAGE_MODE_CHG:
        // 如果在收藏、待机模式，记录参数即可
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
            // 记录参数：成像模式
            cmd_From_FC.irst_cmd_param_irst_form_mode = (IRST_FORM_MODE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_form_mode;
            update_Irst_Mode((IRST_FORM_MODE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_form_mode);

            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        }
        // 如果在拍照中，将指令放入待处理指令，并记录参数
        else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
            main_Control_State_Param.takeTimes++; // 拍照次数累加
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_IMAGE_MODE_CHG = 1; // 修改成像模式指令
            // 记录参数：成像模式
            cmd_From_FC.irst_cmd_param_irst_form_mode = (IRST_FORM_MODE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.irst_form_mode;
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 3.修改广域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_IRST_WIDE_IMAGE_CNTL:
        // 如果在收藏、待机模式，记录参数即可
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
            // 记录参数：广域成像参数
            // 按照参数修改有效标识进行判断
            wide_Image_Paras_Set();
            cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity = 1; // 参数有效性赋值为1

            // 给计算函数用的参数赋值
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_lowline        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_lowline * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = (IR_WIDE_IMAGE_DIRECTION)cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = (IR_WIDE_IMAGE_MODE)cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.AZ_area_altitude        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.AZ_area_altitude * 0.5;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.D_area_altitude * 0.5;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_upline         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_upline * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_start_angle     = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_start_angle * 0.1;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE          = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_IMAGE_RANGE * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_end_angle       = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_end_angle * 0.1;
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        }
        // 如果在拍照中，将指令放入待处理指令，并记录参数
        else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_WIDE_IMAGE_CNTL = 1; // 修改广域成像参数
            // 记录参数：广域成像参数
            // 按照参数修改有效标识进行判断
            wide_Image_Paras_Set();
            cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity = 1; // 参数有效性赋值为1

            // 给计算函数用的参数赋值
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_lowline        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_lowline * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = (IR_WIDE_IMAGE_DIRECTION)cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_WIDE_IMAGE_MODE      = (IR_WIDE_IMAGE_MODE)cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.AZ_area_altitude        = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.AZ_area_altitude * 0.5;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.D_area_altitude         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.D_area_altitude * 0.5;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_range_upline         = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_upline * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_start_angle     = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_start_angle * 0.1;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_IMAGE_RANGE          = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_IMAGE_RANGE * 0.01;
            param_Compute_Input_Fromfc.comp_IR_wide_image_paras.IR_scan_end_angle       = cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_end_angle * 0.1;

        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 4.修改区域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_IRST_AREA_IMAGE_CNTL:
        // 获取区域号
        i = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num - 1;
        // 如果在收藏、待机模式，记录参数即可
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
            // 名  称:成像方式修改标识，独立于三个区域参数，单独赋值
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.IMG_MODE_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE           = (IR_IMG_MODE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
            }

            // 如果是区域1
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 1) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_YES) // 如果是修改
                {
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(1);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;

                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_DELETE) // 如果是删除
                {
                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 0;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 0;
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                }
            }
            // 如果是区域2
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 2) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_YES) // 如果是修改
                {
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(2);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;

                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_DELETE) // 如果是删除
                {
                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 0;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 0;
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                }
            }
            // 如果是区域3
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 3) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_YES) // 如果是修改
                {
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(3);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_DELETE) // 如果是删除
                {
                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 0;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 0;
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                }
            }

        }
        // 如果在拍照中，将指令放入待处理指令，并记录参数
        else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
            clean_cmd_From_FC();
            // 名  称:成像方式修改标识，独立于三个区域参数，单独赋值
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.IMG_MODE_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_image_paras[0].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                cmd_From_FC.irst_cmd_param_area_image_paras[1].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                cmd_From_FC.irst_cmd_param_area_image_paras[2].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
                param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE           = (IR_IMG_MODE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
            }

            // 如果是区域1
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 1) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_YES) // 如果是修改
                {
                    cmd_From_FC.irst_cmd_AREA_IMAGE_CNTL = 1; // 修改区域成像参数
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(1);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA1_CHG == V_AREA1_CHG_DELETE) // 如果是删除
                {
                    // 回复无法响应——无效参数
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
                }
            }
            // 如果是区域2
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 2) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_YES) // 如果是修改
                {
                    cmd_From_FC.irst_cmd_AREA_IMAGE_CNTL = 1; // 修改区域成像参数
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(2);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA2_CHG == V_AREA2_CHG_DELETE) // 如果是删除
                {
                    // 回复无法响应——无效参数
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
                }
            }
            // 如果是区域3
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num == 3) {
                // 区域有效性
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_NO) // 如果是不修改
                {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_YES) // 如果是修改
                {
                    cmd_From_FC.irst_cmd_AREA_IMAGE_CNTL = 1; // 修改区域成像参数
                    // 记录参数：区域成像参数//如果下传的区域编号为1，则将缓存的第一个区域参数赋值，以此类推，一共只缓存三组区域编号（暂定编号为1，2，3）
                    area_Image_Paras_Set(3);
                    // 给计算函数用的参数赋值
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].latitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._latitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].longitude      = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._longitude * 0.00001;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].altitude       = cmd_From_FC.irst_cmd_param_area_image_paras[i].center_point_pos._altitude * 0.01;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].AREA_num       = cmd_From_FC.irst_cmd_param_area_image_paras[i].AREA_num;
                    param_Compute_Input_Fromfc.comp_area_image_paras[i].IR_AREA_LENGTH = cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_AREA_LENGTH;
                    param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE                   = (IR_IMG_MODE)cmd_From_FC.irst_cmd_param_area_image_paras[i].IR_IMG_MODE;

                    // 代表0，1，2三个区域的有效性，1：有效，0：无效
                    cmd_From_FC.irst_cmd_param_area_image_paras_validity[i]      = 1;
                    param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] = 1;

                }
                // 区域有效性
                else if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.AREA3_CHG == V_AREA3_CHG_DELETE) // 如果是删除
                {
                    // 回复无法响应——无效参数
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
                }
            }

        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 5.修改区域监视参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_IRST_WIDE_MONI_CNTL:
        // 如果在收藏、待机模式，记录参数即可
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY) {
            // 记录参数：区域监视范围参数
            // 名  称:高度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.HEIGHT_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._altitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._altitude;
            }
            // 名  称:纬度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.LATI_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._latitude;
            }
            // 名  称:经度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.LONG_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._longitude;
            }

            cmd_From_FC.irst_cmd_param_area_monitor_paras_validity = 1; // 参数有效性赋值为1

            // 给计算函数用的参数赋值
            param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude  = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude * 0.00001;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude * 0.00001;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude  = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._altitude * 0.01;

            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        }
        // 如果在拍照中，将指令放入待处理指令，并记录参数
        else if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_WIDE_MONI_CNTL = 1; // 修改区域监视参数
            // 记录参数：区域监视范围参数
            // 名  称:高度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.HEIGHT_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._altitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._altitude;
            }
            // 名  称:纬度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.LATI_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._latitude;
            }
            // 名  称:经度修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.area_monitor_paras_mark.LONG_CHG == 1) {
                cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_monitor_paras.center_point_pos._longitude;
            }
            cmd_From_FC.irst_cmd_param_area_monitor_paras_validity = 1; // 参数有效性赋值为1

            // 给计算函数用的参数赋值
            param_Compute_Input_Fromfc.comp_area_monitor_paras.latitude  = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._latitude * 0.00001;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.longitude = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._longitude * 0.00001;
            param_Compute_Input_Fromfc.comp_area_monitor_paras.altitude  = cmd_From_FC.irst_cmd_param_area_monitor_paras.center_point_pos._altitude * 0.01;
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 6.可见光成像参数修改——收藏、待机、拍照，——————————调光、调焦执行
    case V_UNIQUE_ACT_REQ_IRS_LIGHT_IMA_PARS_UPDATE:
        // 如果在收藏、待机、拍照模式，后续work_control中判断是否有该指令，调光按照新参数执行响应
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE = 1; // 可见光成像参数修改
            // 记录参数：可见光成像参数
            // 名  称:增强修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.image_paras_mark.ENHANCE_CHG == 1) {
                cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_enhance_mode = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_enhance_mode;
            }
            // 名  称:可见光去雾修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.image_paras_mark.mist_eliminate_CHG == 1) {
                cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_mist_eliminate_state = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_mist_eliminate_state;
            }
            // 名  称:调焦修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.image_paras_mark.focus_CHG == 1) {
                // 如果是自动调焦，只改变调焦工作模式
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_focus_mode == V_LIGHT_FOCUS_MODE_AUTO) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_focus_mode = V_LIGHT_FOCUS_MODE_AUTO;
                }
                // 如果是手动调焦，值为0，则用上一次的调焦值，否则用新的调焦值
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_focus_mode == V_LIGHT_FOCUS_MODE_MANUAL) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_focus_mode = V_LIGHT_FOCUS_MODE_MANUAL;
                    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.focus_value != 0) {
                        cmd_From_FC.irst_cmd_param_IR_image_paras_light.focus_value = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.focus_value;
                    }
                }
                // 如果是NA
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_focus_mode == V_LIGHT_FOCUS_MODE_NA) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_focus_mode = V_LIGHT_FOCUS_MODE_MANUAL;
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.focus_value      = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.focus_value;
                }
            }
            // 名  称:调光修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.image_paras_mark.dim_CHG == 1) {
                // 如果是自动，只改变调光工作模式
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_dim_mode == V_LIGHT_DIM_MODE_AUTO) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_dim_mode = V_LIGHT_DIM_MODE_AUTO;
                }
                // 如果是手动，值为0，则用上一次的调光值，否则用新的调光值
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_dim_mode == V_LIGHT_DIM_MODE_MANUAL) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_dim_mode = V_LIGHT_DIM_MODE_MANUAL;
                    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_value != 0) {
                        cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_value = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_value;
                    }
                }
                // 如果是NA
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_dim_mode == V_LIGHT_DIM_MODE_NA) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_dim_mode = V_LIGHT_DIM_MODE_MANUAL;
                    cmd_From_FC.irst_cmd_param_IR_image_paras_light.light_value    = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_light.light_value;
                }
            }
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 7.红外成像参数修改——收藏、待机、拍照，——————————调光、调焦执行
    case V_UNIQUE_ACT_REQ_IRS_INFRA_IMA_PARS_UPDATE:
        // 如果在收藏、待机、拍照模式，后续work_control中判断是否有该指令，调光按照新参数执行响应
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE = 1; // 红外成像参数修改
            // 记录参数：红外成像参数
            // 名  称:视频极化修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.image_infra_mark.video_polar_CHG == 1) {
                cmd_From_FC.irst_cmd_param_IR_image_paras_infra.video_polar = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.video_polar;
            }
            // 名  称:增强修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.image_infra_mark.ENHANCE_CHG == 1) {
                cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_enhance_mode = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_enhance_mode;
            }
            // 名  称:调焦修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.image_infra_mark.focus_CHG == 1) {
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_focus_mode == V_LIGHT_FOCUS_MODE_AUTO) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_focus_mode = V_LIGHT_FOCUS_MODE_AUTO;
                }
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_focus_mode == V_LIGHT_FOCUS_MODE_MANUAL) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_focus_mode = V_LIGHT_FOCUS_MODE_MANUAL;
                    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.focus_value != 0) {
                        cmd_From_FC.irst_cmd_param_IR_image_paras_infra.focus_value = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.focus_value;
                    }
                }
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_focus_mode == V_LIGHT_FOCUS_MODE_NA) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_focus_mode = V_LIGHT_FOCUS_MODE_MANUAL;
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.focus_value         = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.focus_value;
                }
            }
            // 名  称:调光修改标识
            if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.image_infra_mark.dim_CHG == 1) {
                // 如果是自动，只改变调光工作模式
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_dim_mode == V_LIGHT_DIM_MODE_AUTO) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode = V_LIGHT_DIM_MODE_AUTO;
                }
                // 如果是手动，值为0，则用上一次的调光值，否则用新的调光值
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_dim_mode == V_LIGHT_DIM_MODE_MANUAL) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode = V_LIGHT_DIM_MODE_MANUAL;
                    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.light_value != 0) {
                        cmd_From_FC.irst_cmd_param_IR_image_paras_infra.light_value = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.light_value;
                    }
                }
                // 如果是NA
                if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.infrared_dim_mode == V_LIGHT_DIM_MODE_NA) {
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.infrared_dim_mode = V_LIGHT_DIM_MODE_MANUAL;
                    cmd_From_FC.irst_cmd_param_IR_image_paras_infra.light_value       = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_image_paras_infra.light_value;
                }
            }
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 8.成像传感器控制，收藏、待机、拍照————————————图像处理执行
    case V_UNIQUE_ACT_REQ_IRS_SENSOR_SET:
        // 如果在收藏、待机、拍照模式，后续work_control中按照新参数执行响应
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {

            cmd_From_FC.irst_cmd_SENSOR_SET = 1;
            // 记录参数：光电传感器状态
            cmd_From_FC.irst_cmd_param_IR_SENSOR = (IR_SENSOR)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_SENSOR;
            // 回复执行完成
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
        // 9.修改场景类型——只有收藏可修改场景——————————调光执行，总体要求所有情况都可以修改场景类型
    case V_UNIQUE_ACT_REQ_IRS_SCENE_TYPE_CHANGE:
        // 如果在收藏模式
        //		if(main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT)
        //		{
        // 记录参数：环境类型
        cmd_From_FC.irst_cmd_param_environmnet_type = (ENVIRONMNET_TYPE)cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.environmnet_type;
        // 回复执行完成
        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        //		}
        //		else//其他状态，不可响应
        //		{
        //			//回复无法响应——无效参数
        //			send_Mess_IRST_ACT_REQ_REPORT( V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        //		}
        break;

        // 10.光窗去雾——收藏状态——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_WINDOW_FOG_REMOVE:
        // 如果在收藏模式
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT) {
            // 记录参数：光窗去雾状态
            cmd_From_FC.irst_cmd_param_IR_Transom_paras.Transom_mist_eliminate_state = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.Transom_mist_eliminate_state;
            // 回复执行完成
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 11.进入图像跟踪——只有拍照且区域监视——————主控执行
    case V_UNIQUE_ACT_REQ_IRS_ENTER_TGT_TRACK:
        // 如果在拍照且区域监视
        if ((main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC && main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_ENTER_TGT_TRACK = 1; // 进入图像跟踪
            // 记录参数：图像跟踪
            cmd_From_FC.irst_cmd_param_IR_TGT_TRACK_INFO = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_TGT_TRACK_INFO;

            // 给计算函数用的参数赋值
            param_Compute_Input_Fromfc.comp_IR_TGT_TRACK_INFO = cmd_From_FC.irst_cmd_param_IR_TGT_TRACK_INFO;
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 12.退出图像跟踪——只有拍照且区域监视
    case V_UNIQUE_ACT_REQ_IRS_EXIT_TGT_TRACK:
        // 如果在拍照且区域监视
        if ((main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC && main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI && (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_TRACK_ING || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_MATCH_ING)) || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_EXIT_TGT_TRACK = 1; // 退出图像跟踪，无参数
        } else                                       // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 13.IMU对准，待机和收藏可响应
    case V_UNIQUE_ACT_REQ_IRS_IMU_ALIGN:
        // 如果在待机和收藏
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_IMU_ALIGN = 1; // IMU对准，无参数
        } else                                  // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 14.红外校正——只有待机、收藏，响应后，回准备中（重新准备）
    case V_UNIQUE_ACT_REQ_IRS_INFRA_CORRECT:
        // 如果在待机或收藏
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_INFRA_CORRECT = 1; // 红外校正，无参数
        } else                                      // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 15.冻结——拍照、区域监视
    case V_UNIQUE_ACT_REQ_IRS_FROZEN:
        // 如果在拍照且区域监视
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC && main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
            clean_cmd_From_FC();
            cmd_From_FC.irst_cmd_FROZEN = 1; // 冻结，无参数

            make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-构造
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

        // 16.视频带宽设置——收藏、待机
    case V_UNIQUE_ACT_REQ_IRS_VIDEO_BAND_SET:
        // 如果在收藏、待机、拍照模式，后续work_control中按照新参数执行响应
        if (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_COLLECT || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_STBY
            //				||main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_TAKE_PIC
            || main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_NB_JT) {

            cmd_From_FC.irst_cmd_VIDEO_BAND_SET = 1;
            // 记录参数：视频带宽
            cmd_From_FC.irst_cmd_param_IRST_Video_BAND = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IRST_Video_BAND;
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;

    case V_UNIQUE_ACT_REQ_IRS_BIG_VIEW: // 大视场，短焦。只要不在初始化和自检测就可以响应
        if (main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_INIT && main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_BIT) {

            cmd_From_FC.irst_cmd_VIEW_STATE = 1; // 大视场
            make_Mess_IRST_OPERATIONAL_PARAS();  // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();  // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
    case V_UNIQUE_ACT_REQ_IRS_SMALL_VIEW: // 小视场，长焦。只要不在初始化和自检测就可以响应
        if (main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_INIT && main_Control_State_Param.irst_work_state != V_IRST_WORK_STATE_BIT) {

            cmd_From_FC.irst_cmd_VIEW_STATE = 0; // 小视场
            make_Mess_IRST_OPERATIONAL_PARAS();  // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();  // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        } else // 其他状态，不可响应
        {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
        }
        break;
    default:
        // 回复无法响应——无效活动
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_ACTIVITY);
        break;
    }
}

// 广域成像参数获取及设置
void wide_Image_Paras_Set() {
    // 名  称:扫描方向修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.RNG_DIRECTION_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_DIRECTION = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_WIDE_IMAGE_DIRECTION;
    }
    // 名  称:距离优先高度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.D_HEIGHT_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.D_area_altitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.D_area_altitude;
    }
    // 名  称:方位优先高度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.AZ_HEIGHT_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.AZ_area_altitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.AZ_area_altitude;
    }
    // 名  称:结束角度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.END_ANGLE_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_end_angle = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_scan_end_angle;
    }
    // 名  称:起始角度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.START_ANGLE_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_scan_start_angle = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_scan_start_angle;
    }
    // 名  称:量程修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.RNG_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_IMAGE_RANGE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_IMAGE_RANGE;
    }
    // 名  称:远界距离修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.RNG_UP_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_upline = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_range_upline;
    }
    // 名  称:近界距离修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.RNG_LOW_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_range_lowline = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_range_lowline;
    }
    // 名  称:广域成像子模式修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.wide_image_paras_mark.SUB_MODE_CHG == 1) {
        cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.IR_wide_image_paras_req.IR_WIDE_IMAGE_MODE;
    }
}

// 区域成像参数获取及设置
void area_Image_Paras_Set(int AREA_num) {
    // 名  称:成像方式修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.IMG_MODE_CHG == 1) {
        cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].IR_IMG_MODE = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_IMG_MODE;
    }
    // 名  称:区域边长修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.LENGTH_CHG == 1) {
        cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].IR_AREA_LENGTH = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.IR_AREA_LENGTH;
    }
    // 名  称:高度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.HEIGHT_CHG == 1) {
        cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].center_point_pos._altitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.center_point_pos._altitude;
    }
    // 名  称:纬度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.LATI_CHG == 1) {
        cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].center_point_pos._latitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.center_point_pos._latitude;
    }
    // 名  称:经度修改标识
    if (cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.area_image_paras_mark.LONG_CHG == 1) {
        cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].center_point_pos._longitude = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.center_point_pos._longitude;
    }
    // 区域编号
    cmd_From_FC.irst_cmd_param_area_image_paras[AREA_num - 1].AREA_num = cmd_From_FC.current_IRST_ACT_REQ.unique_act_req_paras_IRST.area_image_paras_req.AREA_num;
}

// 更新相机工作状态
void update_Work_State(INT8 state) {
    static INT8 state_last = 0;                                         // 上一次状态
    if (state != -1)                                                    //-1代表取消故障
        main_Control_State_Param.work_state = (SUBSYS_WORK_STATE)state; // 相机工作状态，上报的工作状态。subsys_work_state子系统可自行上报的工作状态有：正常，自检测，降级，失效，功能停止；
    else
        main_Control_State_Param.work_state = (SUBSYS_WORK_STATE)state_last; // 恢复原来的状态

    // 如果不是降级或者失效
    if (main_Control_State_Param.work_state != V_SUBSYS_WORK_STATE_DEGRADE || main_Control_State_Param.work_state != V_SUBSYS_WORK_STATE_FAIL)
        state_last = main_Control_State_Param.work_state;
}
// 更新相机工作模式
void update_Main_Mode(SUBSYS_MAIN_MODE mode) {
    main_Control_State_Param.main_mode = mode; // 相机工作模式，上报的工作模式。
}
// 更新IRST工作状态
void update_Irst_State(IRST_WORK_STATE irst_state) {
    main_Control_State_Param.irst_work_state = irst_state; // IRST工作状态:初始化、收藏、准备中
}
// 更新IRST成像模式
void update_Irst_Mode(IRST_FORM_MODE irst_mode) {
    main_Control_State_Param.irst_form_mode = irst_mode; // IRST成像模式:广域成像、区域成像、区域监视
}

// 工作流程控制----------------
// 工作流程控制----总控
void Work_Control() {
    switch (main_Control_State_Param.irst_work_state) {
    case V_IRST_WORK_STATE_INIT: // 初始化1
        init_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_COLLECT: // 收藏1
        collect_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_PREPARE: // 准备中1
        prepare_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_STBY: // 待机1
        wait_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_TAKE_PIC: // 拍照1
        photo_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_BIT: // 自检测1
        check_Model_WorkControl();
        break;

    case V_IRST_WORK_STATE_NA: // 未知，说明已经下电
        na_down_WorkControl();
        break;

    case V_IRST_WORK_STATE_NB_JT: // 静态成像-内部使用
        nb_jtphoto_WorkControl();
        break;

    default:
        break;
    }

    HWTCQ_CoolingJudge(); // 红外制冷判断
    TG_ErrCheck();        // 调光故障判断

    // // Note: lcy 一些值直接置位
    // mess_From_TG.Cool_state = 1;
}

// 工作流程控制----初始化-50s
void init_Model_WorkControl() {
    int           percent;          // 自检进度百分比
    static UINT16 step         = 0; // 函数内流程控制
    static UINT16 cnt_wait     = 0; // 子流程等待时间计时
    static UINT16 cnt_wait_cmd = 0; // 子流程指令执行等待时间计时
    // 计数器累加，记录有几个5ms
    cnt_wait++;

    // 判断收到的各种指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1) // 在这只能收到关机
    {
        cnt_wait_cmd++;
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP) // 如果是关机
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2) || cnt_wait_cmd > 600) // 3s超时
            {
                make_Mess_To_DY(0, 0, 0, 0, 0); // 电源分系统通信，关闭所有电源
                // 设置系统状态位
                update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
                update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
                update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
                update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }
        return;
    }

    // 设置系统状态位
    update_Work_State(V_SUBSYS_WORK_STATE_BIT);   // 工作状态置为BIT
    update_Main_Mode(V_SUBSYS_MAIN_MODE_INI);     // 更新相机工作模式
    update_Irst_State(V_IRST_WORK_STATE_INIT);    // 更新IRST工作状态
    update_Irst_Mode(V_IRST_FORM_MODE_WIDE_IMAG); // 更新IRST成像模式：默认广域

    // // 上报工作进度，每1s上报一次，总共50s
    // if (cnt_wait % 200 == 0) {
    //     percent = (cnt_wait * 10000.0) / ((1000 / MAIN_PERIOD_TIME) * INIT_TIME);

    //     if (cnt_wait < 2000)
    //         main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_DIM_ING;

    //     if (cnt_wait > 2000)
    //         main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_SUCCESS;

    //     if (cnt_wait > 2000 && cnt_wait < 4000)
    //         main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_ING; // 校正中

    //     if (cnt_wait > 4000)
    //         main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_COMPLETED; // 校正完成

    //     if (cnt_wait > 4000 && cnt_wait < 6000)
    //         main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_FOCUSING;

    //     if (cnt_wait > 6000)
    //         main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_SUCCESS;

    //     send_Mess_WORK_STATE_REPORT(INIT_TIME - cnt_wait / 200, percent); // 上报工作状态更新，自检进度更新
    //     make_Mess_IRST_OPERATIONAL_PARAS();
    // }

    // ! 没有意义 init 置位 一瞬间就好
    // // Note: lcy 上报工作进度，每1s上报一次, 按照上电时间重新计算
    // float beta = sim::init_time / INIT_TIME;
    // if (cnt_wait % 200 == 0) {
    //     percent = (cnt_wait * 10000.0) / ((1000 / MAIN_PERIOD_TIME) * INIT_TIME) / beta;

    //     if (cnt_wait < 2000 * beta)
    //         main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_DIM_ING;

    //     if (cnt_wait > 2000 * beta)
    //         main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_SUCCESS;

    //     if (cnt_wait > 2000 * beta && cnt_wait < 4000 * beta)
    //         main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_ING; // 校正中

    //     if (cnt_wait > 4000 * beta)
    //         main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_COMPLETED; // 校正完成

    //     if (cnt_wait > 4000 * beta && cnt_wait < 6000 * beta)
    //         main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_FOCUSING;

    //     if (cnt_wait > 6000 * beta)
    //         main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_SUCCESS;

    //     uint32_t remain_time = std::max(0, sim::init_time - cnt_wait / 200);
    //     send_Mess_WORK_STATE_REPORT(remain_time, percent); // 上报工作状态更新，自检进度更新
    //     make_Mess_IRST_OPERATIONAL_PARAS();
    // }

    // Note: 模拟器中直接将状态置位完成
    if (cnt_wait % 200 == 0) {

        main_Control_State_Param.tg_state        = V_PREPARE_STATE_DIM_SUCCESS;
        main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_COMPLETED; // 校正完成
        main_Control_State_Param.tj_state        = V_PREPARE_STATE_FOCUS_SUCCESS;

        send_Mess_WORK_STATE_REPORT(0, 10000); // 上报工作状态更新，自检进度更新
        make_Mess_IRST_OPERATIONAL_PARAS();
    }

    switch (step) {
    case 0:
        param_Init();                   // 参数初始化
        make_Mess_To_DY(3, 1, 1, 1, 1); // 电源分系统通信，打开所有电源
        // 如果电源返回上电成功
        {
            if ((mess_From_DY.state_szgd == 1 && mess_From_DY.state_glgd == 1 && mess_From_DY.state_rkbjgd == 1 && mess_From_DY.state_rkgcgd == 1) || cnt_wait > 4) {
                step = 1; // 进入下一步
            }
        }
        break;

    case 1:              // 配置可见、红外探测器参数
        TCQ_Configure(); // 25-8-15,sc

        mess_From_TG.TCQInit_Flag = 1;

        if (mess_From_TG.TCQInit_Flag == 1) // 25-8-15sc
        {
            step = 2; // 满足条件进入下一步
        }

        break;

    case 2:
        // 向各分系统发送自检命令
        cnt_wait_cmd++;
        make_Mess_To_KJ(KJ_CMD_CHECK, KJ_CMD_KF_MODE_STOP);   // 框架自检
        make_Mess_To_TJ(TJ_CMD_CellBIT, TJ_CMD_VIEW_DEFAULT); // 调焦自检
        make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                  // 图像处理：空指令

        if (cnt_wait_cmd > 2) // 发送两拍
        {
            step         = 3; // 进入下一步
            cnt_wait_cmd = 0;
        }
        break;

    case 3:
        // 等待分系统自检完成，收到所有分系统（框架、调焦、惯导）
        // 如果自检完成，进入下一步
        if (mess_From_KJ.status_sub == 2 && mess_From_TJ.status1_zjzt == 0 && mess_From_PCS_DATA.status_gdgzms != 4) {
            step = 4;
        }
        // 如果超时，进入下一步
        // if (cnt_wait > (1000 / MAIN_PERIOD_TIME) * INIT_TIME) // 超时判定：12min出状态，进入待机——最终版本12分钟，调试过程中为50s
        // Note: 模拟器超时判定3s
        if (cnt_wait > 3 * 1000 / MAIN_PERIOD_TIME) {
            step = 4;
        }

        break;

    case 4:
        // 进入收藏状态
        step                              = 0;
        cnt_wait                          = 0;
        main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_SUCCESS; // 调焦完成
        // 进入收藏状态
        update_Work_State(V_SUBSYS_WORK_STATE_NORMAL); // 工作状态置为正常
        update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);   // 更新相机工作模式
        update_Irst_State(V_IRST_WORK_STATE_COLLECT);  // 更新IRST工作状态
        //		update_Irst_Mode(V_IRST_FORM_MODE_NA);//更新IRST成像模式

        // 上电自检结束后，收集故障信息
        nb_HMC_DATA_SET(); // HMC信息获取函数

        // 向飞机报送相关信息
        send_Mess_WORK_STATE_REPORT(0, 10000); // 上报工作状态更新，完成初始化
        send_Mess_SW_CONFIG_INFO_REPORT();     // 软件配置信息报告
        send_Mess_HW_CONFIG_INFO_REPORT();     // 硬件配置信息报告
        make_Mess_IRST_OPERATIONAL_PARAS();    // 上报工作参数
        send_Mess_DATABASEINFO();              // 数据库信息
        send_Mess_IRST_PIXEL_PARAS();          // IRST像元参数

        break;

    default:
        break;
    }
}

// 工作流程控制----收藏
void collect_Model_WorkControl() {
    static UINT16 step         = 0; // 函数内流程控制
    static UINT16 cnt_wait     = 0; // 子流程等待时间计时
    static UINT16 cnt_wait_cmd = 0; // 子流程指令执行等待时间计时

    // 计数器累加，记录有几个5ms
    cnt_wait++;

    // 判断收到的各种指令
    // 如果收到1.	（通用）工作模式请求指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1) {
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP) // 如果是关机
        {
            // 收藏状态可以直接切关机
            make_Mess_To_DY(0, 0, 0, 0, 0); // 电源分系统通信，关闭所有电源
            // 设置系统状态位
            update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
            update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
            update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
            update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            step = 0;
        }
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STBY) // 如果是待机，直接进入
        {
            // 设置系统状态位，大状态进待机，子状态在收藏
            update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL); // 更新相机工作模式
            // // lcy: 20260112
            // update_Main_Mode(V_SUBSYS_MAIN_MODE_STBY);    // 更新相机工作模式
            update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            step = 0;
        }
        return;
    }

    // Note: 模拟器中不存在地面自检测，无意义
    // 如果收到2.	（通用）执行BIT请求指令
    if (cmd_From_FC.general_cmd_BIT_OPERATION == 1) {
        if (cmd_From_FC.bit_mode == V_BIT_MODE_MBIT || cmd_From_FC.bit_mode == V_BIT_MODE_IBIT) {
            // 设置系统状态位
            update_Main_Mode(V_SUBSYS_MAIN_MODE_TEST); // 更新相机工作模式
            update_Irst_State(V_IRST_WORK_STATE_BIT);  // 更新IRST工作状态

            clean_cmd_From_FC(); // 清理指令
            step = 0;
        } else {
            // 回复无法响应——无效参数
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
            cmd_From_FC.general_cmd_BIT_OPERATION = 0;
        }

        return;
    }

    // 如果收到4.	修改光电工作状态：准备、待机、自检
    if (cmd_From_FC.irst_cmd_STATE_SET == 1) // 修改工作状态
    {
        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_PREPARE || cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_STBY) // 如果是准备中或待机
        {
            // 设置系统状态
            update_Irst_State(V_IRST_WORK_STATE_PREPARE); // 更新IRST工作状态
            send_Mess_WORK_STATE_REPORT(0, 0);            // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS();           // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();           // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            step = 0;
        }

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_BIT) // 如果是自检
        {
            // 设置系统状态
            update_Irst_State(V_IRST_WORK_STATE_BIT); // 更新IRST工作状态
            send_Mess_WORK_STATE_REPORT(0, 0);        // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS();       // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();       // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            step = 0;
        }

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_NB_JT) // 如果是内部静态成像
        {
            // 设置系统状态
            update_Irst_State(V_IRST_WORK_STATE_NB_JT); // 更新IRST工作状态
            update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式
            send_Mess_WORK_STATE_REPORT(0, 0);          // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS();         // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();         // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            step = 0;
        }
        return;
    }

    // 如果收到9.	可见光成像参数修改	//如果收到10.	红外成像参数修改
    if (cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE == 1 || cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE == 1) {
        cnt_wait_cmd++;
        if (cnt_wait_cmd > 4) {
            // 调焦参数已经处理完，差调光参数
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            return;
        }
    }

    // 如果收到11.	IMU对准
    if (cmd_From_FC.irst_cmd_IMU_ALIGN == 1) {
        make_Mess_To_PCS_DATA(1);

        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送

        // 回复执行完成
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);

        clean_cmd_From_FC(); // 清理指令
        return;
    }

    // 8.成像传感器控制——收藏、待机、拍照
    if (cmd_From_FC.irst_cmd_SENSOR_SET == 1) {
        cnt_wait_cmd++;
        make_Mess_To_TXCL_CMD(TX_CMD_SENSOR_SET);
        if (cnt_wait_cmd > 2) {
            cmd_From_FC.irst_cmd_SENSOR_SET = 0;
            cnt_wait_cmd                    = 0;
        }
        clean_cmd_From_FC(); // 清理指令
        return;
    }
    // 16.视频带宽设置
    if (cmd_From_FC.irst_cmd_VIDEO_BAND_SET == 1) {
        make_Mess_To_TXCL_CMD(TX_CMD_VIDEO_BAND_SET);
        return;
    }

    // 如果收到10.	红外校正
    if (cmd_From_FC.irst_cmd_INFRA_CORRECT == 1) {

        update_Irst_State(V_IRST_WORK_STATE_PREPARE); // 更新IRST工作状态
        send_Mess_WORK_STATE_REPORT(0, 0);            // 上报工作状态更新
        make_Mess_IRST_OPERATIONAL_PARAS();           // 上报工作参数

        return;
    }

    switch (step) {
    case 0:
        // 向各分系统发送“收藏”、“停止工作”指令，控制伺服、调焦到特定位置
        make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP); // 框架：停止工作
        // todo: 大小视场需要判定吗？
        make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦：收藏
        make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP);                         // 图像处理：停传
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

        // 等待伺服、框架等分系统到位
        if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait > 200) || cnt_wait > 600) {
            make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
            step = 1;
        }
        break;

    case 1:
        // 与各分系统保持通信
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP);                      // 框架：待机
        make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦：收藏
        make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP);                         // 图像处理：停传
        make_Mess_To_GCWK();                                                    // 光窗温控1
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1
        make_Mess_IRST_OPERATIONAL_PARAS();                                     // 上报工作参数
        make_Mess_To_JLY(JLY_CMD_None);                                         // 记录仪:空指令
        // 调光用
        make_Mess_To_TG(TG_CMD_Collect, JTGMODE_GY);
        TG_AnalyseCmd(); // 调光指令判断
        TG_ShouCang();   // 调光收藏

        param_Over_Range_Judge(); // 参数超限判断

        break;

    default:
        break;
    }
}

// 工作流程控制----准备中
// 除“修改光电工作状态”外，不响应任何特殊活动请求指令，可响应工作状态“收藏”、“下电”指令。且不能在非均匀性校正中响应
// 在该函数中要判断进入的条件，如果是从“收藏”、“待机”状态发送“准备”进入，则执行如下的step1——step6
// 在该函数中要判断进入的条件，如果是从“待机”状态发送“红外校正”进入，则只执行非均匀性校正过程（jiaozheng_WorkControl()）
void prepare_Model_WorkControl() {
    static UINT16 step            = 0;                 // 函数内流程控制
    static UINT16 cnt_wait        = 0;                 // 子流程等待时间计时
    static UINT16 cnt_wait_cmd    = 0;                 // 子流程指令执行等待时间计时
    static UINT8  flag_zzxx_valid = FPGA_ZSXX_INVALID; // 注释信息有效标志

    // 计数器累加，记录有几个5ms
    cnt_wait++;
    // 判断收到的各种指令
    // 如果收到1.	（通用）工作模式请求指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1 && step != 4) // 不在非均匀性校正中
    {
        // 处理完成最后一帧注释信息
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc
        cnt_wait_cmd++;
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP && flag_Fpga_bg == 0) // 如果是关机
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) // 3s超时
            {
                make_Mess_To_DY(0, 0, 0, 0, 0); // 电源分系统通信，关闭所有电源

                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
                // 设置系统状态位
                update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
                update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
                update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
                update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }

        return;
    }
    // 如果收到2.	修改光电工作状态：收藏——（非红外校正中可响应）
    if (cmd_From_FC.irst_cmd_STATE_SET == 1 && step != 4) // 不在非均匀性校正中,不在曝光中
    {
        // 处理完成最后一帧注释信息
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc
        cnt_wait_cmd++;
        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_COLLECT && flag_Fpga_bg == 0) // 如果是收藏
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) // 超时3s
            {
                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关

                // 设置系统状态位
                update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }

        return;
    }

    // 如果在待机、收藏收到红外校正进入准备中
    if (cmd_From_FC.irst_cmd_INFRA_CORRECT == 1) {
        step = 4; // 直接跳到红外校正
    }

    // Note: 流程
    switch (step) {
        // step1:检光------------------------------------------------------------------
        // 场景参数
        // 广域：按照广域成像参数执行摆扫，并成像，执行5s
        // 区域成像、区域监视：按照区域成像的中心点经纬高参数提取左右倾斜方向，方位按80°，俯仰摆扫角度以距离50km为中心摆扫/凝视，执行5s
    case 0:
        // ## 检光-子流程1：计算初始位置
        log_once("[准备] step=%d, 检光-子流程1:计算初始位置", step);
        main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_DIM_ING;
        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        make_Mess_To_JLY(JLY_CMD_OPEN);     // 记录仪:开
        // 如果成像模式是广域搜索
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == 1) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_GY); // 图像处理

            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) {
                // 如果是距离优先
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_ZB_JTG();
            } else {
                // 如果是方位优先
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_ZB_JTG();
            }
        }
        // 如果成像模式是区域成像
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 2) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_QY); // 图像处理

            // 计算函数，提取左右倾斜方向
            comp_QY_Photo_ZB_JTG();
        }
        // 如果成像模式是区域监视
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 3) {
            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_VIEW); // 图像处理
            comp_QY_Video_ZB_JTG();
            // 3.区域监视--按照准备计算出的经纬高进行成像
            comp_QY_Video_ZB();
        }

        step++;
        cnt_wait = 0;
        break;
    case 1:
        // ## 检光-子流程2：预置
        log_once("[准备] step=%d, 检光-子流程2:预置", step);
        make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                    // 框架：准备
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga停拍

        // 调光用
        make_Mess_To_TG(TG_CMD_Light, main_Control_State_Param.irst_form_mode);
        TG_AnalyseCmd(); // 调光指令判断
        JianGuang();     // 检光
        log_once("(检光) 预置阶段, 可见曝光时间:%d, 红外曝光时间:%d", tg_Param.KJ_ExpTime, tg_Param.HW_ExpTime);

        if ((2 == mess_From_KJ.status_sub && mess_From_TG.JianGuang == 1 /*调光判断*/ && cnt_wait > 2) || (cnt_wait > 2000)) // 最长1s伺服到位
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

    case 2:
        // ## 检光-子流程3：成像
        log_once("[准备] step=%d, 检光-子流程3:成像", step);
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc

        // 如果成像模式是广域搜索
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == 1) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 0; // 第一次调用标志
            // 如果当前为位置信号，新获取的为速度信号，说明刚进入速度信号，进行换向	//0A_4为位置/速度信号；高电平为位置；低电平为速度
            if (param_Compute_Input_Fromfpga.flag_Speed_OR_Locate == 1 && gpio0AIn(4) == 0) {
                param_Compute_Input_Fromfpga.flag_First_Into_Speed = 1; // 刚进入速度信号标志
            }
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate = gpio0AIn(4); // 更新速度位置信号

            make_Mess_To_KJ(KJ_CMD_SCAN, KJ_CMD_KF_MODE_YZJ);                    // 框架：摆扫
            make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                   // 调焦：空指令
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_GY_PHOTO, flag_zzxx_valid); // fpga：开始拍照

            // 计算
            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_ZB_JTG();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_ZB_JTG();
            }
            JianGuang(); // 检光
        }
        // 如果成像模式是区域成像
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 2) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 0; // 第一次调用标志
            // 如果当前为位置信号，新获取的为速度信号，说明刚进入速度信号，进行换向
            if (param_Compute_Input_Fromfpga.flag_Speed_OR_Locate == 1 && gpio0AIn(4) == 0) {
                param_Compute_Input_Fromfpga.flag_First_Into_Speed = 1; // 刚进入速度信号标志
            }
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate = gpio0AIn(4); // 更新速度位置信号

            make_Mess_To_KJ(KJ_CMD_SCAN, KJ_CMD_KF_MODE_YZJ);                    // 框架：摆扫
            make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                   // 调焦：区域成像
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_QY_PHOTO, flag_zzxx_valid); // fpga：开始拍照，区域成像

            // 计算函数，提取左右倾斜方向
            comp_QY_Photo_ZB_JTG();

            JianGuang(); // 检光

        }
        // 如果成像模式是区域监视
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 3) {
            make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                  // 框架：摆扫
            make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                   // 调焦：区域监视
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_QY_VIDEO, flag_zzxx_valid); // fpga：开始拍照，区域成像

            // 计算函数
            // 3.区域监视--按照准备计算出的经纬高进行成像
            comp_QY_Video_ZB();

            JianGuang(); // 检光
        }
        if ((mess_From_TG.JianGuang == 2 /*调光判断*/ || cnt_wait > 3000) && flag_Fpga_bg == 0) // 持续15s
        {
            // Note: mess_From_TG.JianGuang = 2 这样没有经过调光 直接置为2
            log_once("(检光) 成像阶段, 可见曝光时间:%d, 红外曝光时间:%d", tg_Param.KJ_ExpTime, tg_Param.HW_ExpTime);
            make_Mess_To_JLY(JLY_CMD_None); // 记录仪:空指令
            step++;                         // 进入下一阶段
            cnt_wait = 0;
        }
        break;
    case 3:
        // ## 检光-子流程4：停拍
        log_once("[准备] step=%d, 检光-子流程4:停拍", step);
        make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                    // 框架：准备
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga：停止工作

        main_Control_State_Param.tg_state = V_PREPARE_STATE_DIM_SUCCESS;
        make_Mess_IRST_OPERATIONAL_PARAS();                                   // 上报工作参数
        if ((mess_From_KJ.status_sub == 2 && cnt_wait > 2) || cnt_wait > 400) // 发两次
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

        // step2：非均匀性校正jiaozheng_WorkControl()------------------------------------------------------------------
    case 4:
        log_once("[准备] step=%d, 非均匀性校正", step);
        main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_ING; // 校正中
        if (cnt_wait % 32 == 0) {
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        }
        if (1 == jiaozheng_WorkControl(1) || cnt_wait > 8000) // 预留40s时间进行非均匀校正过程配置
        {
            log_once("(非均匀性校正) 完成");
            step++;
            cnt_wait                                   = 0;
            param_Compute_Input_Fromfpga.flag_First_TJ = 1; // 第一次标志置为1

            jiaozheng_WorkControl(0);                                                      // 非均匀性校正复位函数
            main_Control_State_Param.jiaozheng_state = V_INFRARED_CORRECT_STATE_COMPLETED; // 校正完成
            make_Mess_IRST_OPERATIONAL_PARAS();                                            // 上报工作参数
            // 如果在待机收到红外校正进入准备中
            if (cmd_From_FC.irst_cmd_INFRA_CORRECT == 1) {
                clean_cmd_From_FC(); // 清理指令
                step     = 12;
                cnt_wait = 0;

                make_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-构造
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            }
        }
        break;

        // step3:检焦：小视场长焦------------------------------------------------------------------
        // 广域：
        // 侧向（距离优先）：只考虑左右倾，方位按85°，俯仰按照距离32km计算
        // 前向（方位优先）：右侧前，方位右侧倾角30°（前为0），前向俯仰角按距离32km计算

        // 区域成像、区域监视：先用经纬高算左右，方位按85°，俯仰按照距离32km计算

        // 计算完成后，切入地理跟踪模式，开始成像；等待调焦返回检焦完成
        // 最长超时：1min
    case 5:
        // ## 检焦-子流程1：计算初始位置
        log_once("[准备] step=%d, 检焦-子流程1:计算初始位置", step);
        main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_FOCUSING;
        make_Mess_IRST_OPERATIONAL_PARAS();                      // 上报工作参数
        make_Mess_To_TJ(TJ_CMD_FlyFocus_Pre, TJ_CMD_VIEW_SMALL); // 调焦：小视场切换、调焦电机动
        make_Mess_To_TXCL_CMD(TX_CMD_SHOW_JJMS);                 // 图像处理

        // 如果成像模式是广域搜索
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == 1) {
            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_ZB_JTJ();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_ZB_JTJ();
            }
        }
        // 如果成像模式是区域成像
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 2) {
            // 计算函数，提取左右倾斜方向
            comp_QY_Photo_ZB_JTJ();

        }
        // 如果成像模式是区域监视
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 3) {
            comp_QY_Video_ZB_JTJ();
        }

        if (cnt_wait > 4) // 发4次
        {
            step++;
            cnt_wait                                   = 0;
            param_Compute_Input_Fromfpga.flag_First_TJ = 0; // 调焦第一次标志置为0
        }
        break;
    case 6:
        log_once("[准备] step=%d, 航空实景检焦准备", step);
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc

        // 3.区域监视--按照准备计算出的经纬高进行成像
        comp_QY_Video_ZB();
        make_Mess_To_TJ(TJ_CMD_FlyFocus_Pre, TJ_CMD_VIEW_SMALL);                // 调焦：实景检焦
        make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                     // 框架:凝视
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_JTJ_PHOTO, FPGA_ZSXX_INVALID); // fpga：30HZ//测试用监视成像todo

        // 各分系统都到位
        if ((mess_From_TJ.status1_djdw_kj == 1 && mess_From_TJ.status2_bbj_dw == 1 && mess_From_TJ.status1_djdw_hw == 1 && mess_From_KJ.status_sub == 2) || cnt_wait > 2400) // 6s超时
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }

        break;
    case 7:
        // ## 检焦-子流程2:调光准备
        log_once("[准备] step=%d, 检焦-子流程2:调光准备", step);
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc
        // 调光用
        make_Mess_To_TG(TG_CMD_FlyFocus, V_IRST_FORM_MODE_AREA_MONI);
        TG_AnalyseCmd(); // 调光指令判断
        TG_FlyFocus();   // 实景检焦调光处理,25-8-12

        // 各分系统都到位
        if ((mess_From_TG.JianJiao_state == 1 || cnt_wait > 1200) && flag_Fpga_bg == 0) {
            // 发送清晰度评价值查询指令
            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetDefiValue, KJTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
            tg_Param.KJTCQ_Cmd = KJTCQ_CMD_GetDefiValue;
            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetDefiValue, HWTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
            tg_Param.HWTCQ_Cmd = HWTCQ_CMD_GetDefiValue;

            // 调焦测试用
            //	KJImg_GetGrads();
            //	HWImg_GetGrads();
            // printf("h:%f; p:%f; r:%f\n",param_Compute_Input_Fromfpga.true_heading*180/3.1415926, param_Compute_Input_Fromfpga.pitch*180/3.1415926, param_Compute_Input_Fromfpga.roll*180/3.1415926);//132,360

            // 调焦测试用
            cnt_wait_cmd++;                                                         // 保证调光清晰度值已经回报完成
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga：停止工作

            if (cnt_wait_cmd > 3) // 6s超时
            {
                step++; // 进入下一阶段
                cnt_wait     = 0;
                cnt_wait_cmd = 0;
            }
        }
        break;

    case 8:
        // ## 检焦-子流程3:根据经纬高计算伺服指向，并执行区域监视
        log_once("[准备] step=%d, 检焦-子流程3:根据经纬高计算伺服指向，并执行区域监视", step);
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc

        // 3.区域监视--按照准备计算出的经纬高进行成像
        comp_QY_Video_ZB();

        make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                   // 框架:凝视
        make_Mess_To_TJ(TJ_CMD_FlyFocus, TJ_CMD_VIEW_SMALL);                  // 调焦：实景检焦
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_JTJ_PHOTO, flag_zzxx_valid); // fpga：开始拍照，区域监视//测试用

        if ((mess_From_TJ.status2_realtime_jj == 1 || cnt_wait > 12000) && flag_Fpga_bg == 0) // 持续1min
        {

            step++; // 进入下一阶段
            cnt_wait = 0;
        }

        break;

    case 9:
        // ## 检焦-子流程4：停拍
        log_once("[准备] step=%d, 检焦-子流程4:停拍", step);
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP);                      // 框架：停止工作
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_SMALL);                        // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga：停止工作
        main_Control_State_Param.tj_state = V_PREPARE_STATE_FOCUS_SUCCESS;
        if (cnt_wait % 32 == 0) {
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        }
        if (cnt_wait > 2) // 发两次
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

        // step5:根据成像模式参数，控制控制伺服指向特定位置------------------------------------------------------------------------------
    case 10:
        // ## 预置子流程1：计算初始位置
        log_once("[准备] step=%d, 预置子流程1:计算初始位置", step);
        // 如果成像模式是广域搜索
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == 1) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_Normal();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_Normal();
            }
        }
        // 如果成像模式是区域成像
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 2) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            // 计算函数，区域成像正常，根据收到的三组区域成像参数进行计算
            comp_QY_Photo_Normal();

        }
        // 如果成像模式是区域监视
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 3) {
            // 区域监视--按照正常下发参数进行成像
            comp_QY_Video_Normal();
        }

        step++;
        cnt_wait = 0;
        break;
    case 11:
        // ## 预置子流程2：预置
        log_once("[准备] step=%d, 预置子流程2:预置", step);
        make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                    // 框架：准备
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga停拍

        if ((2 == mess_From_KJ.status_sub && cnt_wait > 200) || cnt_wait > 600) // 最长1s伺服到位
        {
            make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
            step++;                          // 进入下一阶段
            cnt_wait = 0;
        }
        break;

        // step7：进入待机状态------------------------------------------------------------------
    case 12:
        log_once("[准备] step=%d, 进入待机状态", step);
        step     = 0;
        cnt_wait = 0;
        // 进入待机状态
        update_Irst_State(V_IRST_WORK_STATE_STBY); // 更新IRST工作状态

        // 向飞机报送相关信息
        send_Mess_WORK_STATE_REPORT(0, 10000); // 上报工作状态更新，完成初始化
        make_Mess_IRST_OPERATIONAL_PARAS();    // 上报工作参数

        break;

    default:
        break;
    }
}

// 工作流程控制----待机
void wait_Model_WorkControl() {
    static UINT16 cnt_wait_cmd = 0; // 子流程指令执行等待时间计时
    static UINT16 step         = 0;

    // 判断收到的各种指令
    // 如果收到1.	（通用）工作模式请求指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1) {
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP) // 如果是关机
        {

            make_Mess_To_DY(0, 0, 0, 0, 0); // 电源分系统通信，关闭所有电源
            // 设置系统状态位
            update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
            update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
            update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
            update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            step         = 0;
        }

        return;
    }

    // 如果收到2.	修改光电工作状态：收藏、准备、拍照
    if (cmd_From_FC.irst_cmd_STATE_SET == 1) // 修改工作状态
    {

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_COLLECT) // 如果是收藏
        {
            // 设置系统状态位，子状态在收藏
            update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            step         = 0;
        }

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_PREPARE) // 如果是准备中
        {
            // 设置系统状态位
            update_Irst_State(V_IRST_WORK_STATE_PREPARE); // 更新IRST工作状态

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            step         = 0;
        }

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_TAKE_PIC) // 如果是拍照
        {
            // 设置系统状态位
            update_Irst_State(V_IRST_WORK_STATE_TAKE_PIC);               // 更新IRST工作状态
            update_Irst_Mode(cmd_From_FC.irst_cmd_param_irst_form_mode); // 更新IRST成像模式——根据当前收到的最新指令执行

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            step         = 0;
        }

        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_NB_JT) // 如果是内部静态成像
        {
            // 设置系统状态
            update_Irst_State(V_IRST_WORK_STATE_NB_JT); // 更新IRST工作状态
            update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式
            send_Mess_WORK_STATE_REPORT(0, 0);          // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS();         // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS();         // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            step         = 0;
        }

        return;
    }

    // 如果收到9.	可见光成像参数修改	//如果收到10.	红外成像参数修改
    if (cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE == 1 || cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE == 1) {
        cnt_wait_cmd++;
        if (cnt_wait_cmd > 4) {
            // 调焦参数已经处理完，差调光参数
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
            return;
        }
    }

    // 如果收到9.	IMU对准
    if (cmd_From_FC.irst_cmd_IMU_ALIGN == 1) {
        make_Mess_To_PCS_DATA(1);
        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
        // 回复执行完成
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        clean_cmd_From_FC(); // 清理指令
        cnt_wait_cmd = 0;
        return;
    }

    // 如果收到10.	红外校正
    if (cmd_From_FC.irst_cmd_INFRA_CORRECT == 1) {

        update_Irst_State(V_IRST_WORK_STATE_PREPARE); // 更新IRST工作状态
        send_Mess_WORK_STATE_REPORT(0, 0);            // 上报工作状态更新
        make_Mess_IRST_OPERATIONAL_PARAS();           // 上报工作参数

        cnt_wait_cmd = 0;

        return;
    }

    // 8.成像传感器控制——收藏、待机、拍照
    if (cmd_From_FC.irst_cmd_SENSOR_SET == 1) {
        cnt_wait_cmd++;
        make_Mess_To_TXCL_CMD(TX_CMD_SENSOR_SET);
        if (cnt_wait_cmd > 2) {
            cmd_From_FC.irst_cmd_SENSOR_SET = 0;
            cnt_wait_cmd                    = 0;
        }
        clean_cmd_From_FC(); // 清理指令
        return;
    }
    // 16.视频带宽设置
    if (cmd_From_FC.irst_cmd_VIDEO_BAND_SET == 1) {
        make_Mess_To_TXCL_CMD(TX_CMD_VIDEO_BAND_SET);
        return;
    }

    switch (step) {

    case 0:
        // // 20251128增加保存帧序号功能
        // my_flash_write(FLASH_ADDR + sizeof(MESS_FROMFC_HWINFO_FLASH), (void *)(&(main_Control_State_Param.totalNo)), sizeof(UINT32)); // 写回flash
        step = 1;

        // printf("flashwrite:%d\n", *(UINT32 *)(FLASH_ADDR + sizeof(MESS_FROMFC_HWINFO_FLASH)));
        break;

    case 1:
        // 调用计算函数
        log_once("[待机] step=%d, 调用计算函数", step);
        // 如果成像模式是广域搜索
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == 1) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_Normal();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_Normal();
            }
        }
        // 如果成像模式是区域成像
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 2) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号

            // 计算函数，区域成像正常，根据收到的三组区域成像参数进行计算
            comp_QY_Photo_Normal();

        }
        // 如果成像模式是区域监视
        else if (cmd_From_FC.irst_cmd_param_irst_form_mode == 3) {
            // 区域监视--按照正常下发参数进行成像
            comp_QY_Video_Normal();
        }
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP);                      // 框架：待机状态下要发准备
        make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga停拍
        make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP);                         // 图像处理：停传
        make_Mess_To_JLY(JLY_CMD_None);                                         // 记录仪:空指令

        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

        // 调光用
        make_Mess_To_TG(TG_CMD_Wait, JTGMODE_GY);
        TG_AnalyseCmd(); // 调光指令判断
        TG_Wait();       // 待机调光处理

        param_Over_Range_Judge(); // 参数超限判断

        break;
    }
}

// 工作流程控制----拍照
// step1：根据成像模式，开展计算
// step2：执行控制成像
// step3：如果收到成像模式切换或工作参数修改，根据新参数重新计算伺服指向（成像模式回NA）
// step4：计算完成并且伺服按照新位置到位后，执行成像
void photo_Model_WorkControl() {
    static UINT16 step            = 0;                 // 函数内流程控制
    static UINT16 cnt_wait        = 0;                 // 子流程等待时间计时
    static UINT16 cnt_wait_cmd    = 0;                 // 子流程指令执行等待时间计时
    static UINT8  flag_zzxx_valid = FPGA_ZSXX_INVALID; // 注释信息有效标志
    static UINT8  track_State     = 0;                 // 跟踪状态

    // 计数器累加，记录有几个5ms
    cnt_wait++;

    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

    // 判断收到的各种指令
    // 如果收到1.	（通用）工作模式请求指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1 && step == 7) {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        cnt_wait_cmd++;
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP && flag_Fpga_bg == 0) // 如果是关机
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                    // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                 // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) {
                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
                make_Mess_To_DY(0, 0, 0, 0, 0);  // 电源分系统通信，关闭所有电源
                // 设置系统状态位
                update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
                update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
                update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
                update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

                send_Mess_IRST_OPERATIONAL_PARAS();                             // IRST工作参数报告-发送
                main_Control_State_Param.trans_state = V_ID_DATA_TRANS_FLAG_NO; // 传图状态，初始化为否
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STBY && flag_Fpga_bg == 0) // 如果是待机
        {
            make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                  // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                 // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1
            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) {
                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
                // 设置系统状态,通用控制请求的待机，子状态回收藏
                update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);  // 更新相机工作模式
                update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

                send_Mess_WORK_STATE_REPORT(0, 0);                              // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS();                             // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS();                             // IRST工作参数报告-发送
                main_Control_State_Param.trans_state = V_ID_DATA_TRANS_FLAG_NO; // 传图状态，初始化为否

                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }

        return;
    }

    // 如果收到2.	修改光电工作状态：待机
    if (cmd_From_FC.irst_cmd_STATE_SET == 1 && step == 7) // 修改工作状态
    {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        cnt_wait_cmd++;
        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_STBY && flag_Fpga_bg == 0) // 如果是待机
        {
            make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                  // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                    // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1
            make_Mess_To_TXCL_CMD(TX_CMD_STOP_TRACK);                             // 图像处理：停止跟踪
            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) {
                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
                // 设置系统状态位，子状态在收藏
                update_Irst_State(V_IRST_WORK_STATE_STBY); // 更新IRST工作状态

                send_Mess_WORK_STATE_REPORT(0, 0);                              // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS();                             // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS();                             // IRST工作参数报告-发送
                main_Control_State_Param.trans_state = V_ID_DATA_TRANS_FLAG_NO; // 传图状态，初始化为否
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }

        return;
    }

    // 如果收到3.	成像模式修改
    if (cmd_From_FC.irst_cmd_IMAGE_MODE_CHG == 1 && step == 7) {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        // 如果收到的模式与当前一致，直接回复完成
        if (cmd_From_FC.irst_cmd_param_irst_form_mode == main_Control_State_Param.irst_form_mode) {
            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
            cnt_wait_cmd = 0;
        }
        if (cmd_From_FC.irst_cmd_param_irst_form_mode != main_Control_State_Param.irst_form_mode && flag_Fpga_bg == 0) // 如果是新的成像模式，判断该模式的参数是否有效，无效回复拒绝，有效先停止当前工作，重新执行新的
        {
            cnt_wait_cmd++;
            // 如果参数有效
            if ((cmd_From_FC.irst_cmd_param_irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG && cmd_From_FC.irst_cmd_param_IR_wide_image_paras_validity == 1) || (cmd_From_FC.irst_cmd_param_irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG && (cmd_From_FC.irst_cmd_param_area_image_paras_validity[0] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[1] == 1 || cmd_From_FC.irst_cmd_param_area_image_paras_validity[2] == 1)) || (cmd_From_FC.irst_cmd_param_irst_form_mode == V_IRST_FORM_MODE_AREA_MONI && cmd_From_FC.irst_cmd_param_area_monitor_paras_validity == 1)) {

                make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                    // 框架停止工作
                make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                    // 调焦待机
                make_Mess_To_TG(TG_CMD_Wait, 0);                                      // 向调光发（写结构体）待机，停拍
                TG_AnalyseCmd();                                                      // 调光指令判断
                TG_Wait();                                                            // 调光待机
                make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

                // 等待伺服、框架等分系统到位
                if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 5) || cnt_wait_cmd > 600) {

                    // 设置系统状态位
                    update_Irst_Mode(cmd_From_FC.irst_cmd_param_irst_form_mode); // 更新IRST成像模式

                    send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                    clean_cmd_From_FC();       // 清理指令
                    clean_cmd_ImageInfo_Num(); // 重置图像序号
                    cnt_wait_cmd = 0;

                    // 重新开始新的拍照
                    step     = 0;
                    cnt_wait = 0;

                    make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP); // 图像处理：停传
                }
            } else {
                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_INVALID_PARA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
            }
        }

        return;
    }

    // 如果收到4.	修改广域成像参数
    if (cmd_From_FC.irst_cmd_WIDE_IMAGE_CNTL == 1 && step == 7) {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        // 如果当前在广域成像模式，则重新拍照
        if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG && flag_Fpga_bg == 0) {
            cnt_wait_cmd++;
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP); // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT); // 调焦收藏
            make_Mess_To_TG(TG_CMD_Wait, 0);                   // 向调光发（写结构体）待机，停拍
            TG_AnalyseCmd();                                   // 调光指令判断
            TG_Wait();                                         // 调光待机

            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 5) || cnt_wait_cmd > 600) {

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;

                // 重新开始新的拍照
                step     = 0;
                cnt_wait = 0;

                make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP); // 图像处理：停传
            }

        } else // 如果不在广域搜索，缓存参数即可
        {
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
        }

        return;
    }

    // 如果收到5.	修改区域成像参数
    if (cmd_From_FC.irst_cmd_AREA_IMAGE_CNTL == 1 && step == 7) {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        // 如果当前在区域成像模式，则重新拍照
        if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG && flag_Fpga_bg == 0) {
            cnt_wait_cmd++;
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP); // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT); // 调焦待机
            make_Mess_To_TG(TG_CMD_Wait, 0);                   // 向调光发（写结构体）待机，停拍
            TG_AnalyseCmd();                                   // 调光指令判断
            TG_Wait();                                         // 调光待机

            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 5) || cnt_wait_cmd > 600) {

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;

                // 重新开始新的拍照
                step     = 0;
                cnt_wait = 0;

                make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS_STOP); // 图像处理：停传
            }

        } else // 如果不在区域成像，缓存参数即可
        {
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
        }

        return;
    }
    // 如果收到6.	修改区域监视参数
    if (cmd_From_FC.irst_cmd_WIDE_MONI_CNTL == 1 && step == 7) {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);
        // 如果当前在区域监视模式，则重新拍照
        if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI && flag_Fpga_bg == 0) {
            cnt_wait_cmd++;
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                    // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                    // 调焦待机
            make_Mess_To_TG(TG_CMD_Wait, 0);                                      // 向调光发（写结构体）待机，停拍
            TG_AnalyseCmd();                                                      // 调光指令判断
            TG_Wait();                                                            // 调光待机
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 5) || cnt_wait_cmd > 600) {

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC();       // 清理指令
                clean_cmd_ImageInfo_Num(); // 重置图像序号
                cnt_wait_cmd = 0;

                // 重新开始新的拍照
                step     = 0;
                cnt_wait = 0;
            }

        } else // 如果不在区域监视，缓存参数即可
        {
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
        }

        return;
    }

    // 如果收到9.	可见光成像参数修改	//如果收到10.	红外成像参数修改
    if ((cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE == 1 || cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE == 1)) {

        // 调焦参数已经处理完，差调光参数
        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
        // 回复执行完成
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE = 0;
        cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE = 0;
    }

    switch (step) {

    // 成像过程中的检焦-小准备
    case 0:
        // 检焦-子流程1：计算初始位置
        log_once("[拍照] step=0, 检焦-子流程1:计算初始位置");
        make_Mess_IRST_OPERATIONAL_PARAS();                        // 上报工作参数
        make_Mess_To_TJ(TJ_CMD_FlyFocus_Pre, TJ_CMD_VIEW_DEFAULT); // 调焦：根据指令
        make_Mess_To_TXCL_CMD(TX_CMD_SHOW_JJMS);                   // 图像处理
        make_Mess_To_JLY(JLY_CMD_OPEN);                            // 记录仪:开

        // 如果成像模式是广域搜索
        if (main_Control_State_Param.irst_form_mode == 1) {
            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_Normal();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_Normal();
            }
        }
        // 如果成像模式是区域成像
        else if (main_Control_State_Param.irst_form_mode == 2) {
            // 计算函数，提取左右倾斜方向
            comp_QY_Photo_Normal();

        }
        // 如果成像模式是区域监视
        else if (main_Control_State_Param.irst_form_mode == 3) {
            comp_QY_Video_Normal();
        }

        if (cnt_wait > 40) // 发4次.200ms保证记录仪打开
        {
            step++;
            cnt_wait                                   = 0;
            param_Compute_Input_Fromfpga.flag_First_TJ = 0; // 调焦第一次标志置为0
        }
        break;
    case 1:
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        log_once("[拍照] step=1, 检焦-子流程1:区域监视--按照准备计算出的经纬高进行成像");
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc
        // 3.区域监视--按照准备计算出的经纬高进行成像
        comp_QY_Video_ZB();
        make_Mess_To_TJ(TJ_CMD_FlyFocus_Pre, TJ_CMD_VIEW_DEFAULT);              // 调焦：实景检焦
        make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                     // 框架:凝视
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_JTJ_PHOTO, FPGA_ZSXX_INVALID); // fpga：30HZ//测试用监视成像todo

        // 各分系统都到位
        if ((mess_From_TJ.status1_djdw_kj == 1 && mess_From_TJ.status2_bbj_dw == 1 && mess_From_TJ.status1_djdw_hw == 1 && mess_From_KJ.status_sub == 2) || cnt_wait > 2400) // 6s超时
        {
            make_Mess_To_JLY(JLY_CMD_None); // 记录仪:空指令
            step++;                         // 进入下一阶段
            cnt_wait = 0;
        }

        break;
    case 2:
        // 检焦-子流程2:调光准备
        log_once("[拍照] step=2, 检焦-子流程2:调光准备");
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc
        // 调光用
        make_Mess_To_TG(TG_CMD_FlyFocus, V_IRST_FORM_MODE_AREA_MONI);
        TG_AnalyseCmd(); // 调光指令判断
        TG_FlyFocus();   // 实景检焦调光处理,25-8-12

        // 各分系统都到位
        if ((mess_From_TG.JianJiao_state == 1 || cnt_wait > 1200) && flag_Fpga_bg == 0) {
            // 发送清晰度评价值查询指令
            make_Mess_To_QNSJ_KJTCQ(KJTCQ_CMD_GetDefiValue, KJTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
            tg_Param.KJTCQ_Cmd = KJTCQ_CMD_GetDefiValue;
            make_Mess_To_QNSJ_HWTCQ(HWTCQ_CMD_GetDefiValue, HWTCQ_CMD_GetDefiValue, TCQ_Send_NULL);
            tg_Param.HWTCQ_Cmd = HWTCQ_CMD_GetDefiValue;

            // 调焦测试用
            //	KJImg_GetGrads();
            //	HWImg_GetGrads();
            // printf("h:%f; p:%f; r:%f\n",param_Compute_Input_Fromfpga.true_heading*180/3.1415926, param_Compute_Input_Fromfpga.pitch*180/3.1415926, param_Compute_Input_Fromfpga.roll*180/3.1415926);//132,360

            // 调焦测试用
            cnt_wait_cmd++;                                                         // 保证调光清晰度值已经回报完成
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga：停止工作

            if (cnt_wait_cmd > 3) // 6s超时
            {
                step++; // 进入下一阶段
                cnt_wait     = 0;
                cnt_wait_cmd = 0;
            }
        }
        break;

    case 3:
        // 检焦-子流程3:根据经纬高计算伺服指向，并执行区域监视
        log_once("[拍照] step=3, 检焦-子流程3:根据经纬高计算伺服指向，并执行区域监视");
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 0); // 不需要发送fc

        // 3.区域监视--按照准备计算出的经纬高进行成像
        comp_QY_Video_ZB();

        make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                   // 框架:凝视
        make_Mess_To_TJ(TJ_CMD_FlyFocus, TJ_CMD_VIEW_DEFAULT);                // 调焦：实景检焦
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_JTJ_PHOTO, flag_zzxx_valid); // fpga：开始拍照，区域监视//测试用

        if ((mess_From_TJ.status2_realtime_jj == 1 || cnt_wait > 12000) && flag_Fpga_bg == 0) // 持续1min
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }

        break;

    case 4:
        // 检焦-子流程4：停拍
        log_once("[拍照] step=4, 检焦-子流程4:停拍");
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP);                      // 框架：待机
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga：停止工作

        make_Mess_To_TG(TG_CMD_Wait, 0); // 向调光发（写结构体）待机，停拍
        TG_AnalyseCmd();                 // 调光指令判断
        TG_Wait();                       // 调光待机

        if (cnt_wait > 140) // 延时700ms，确保在路上的图和注释信息都发完
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

    case 5:
        // 正式成像-子流程1：计算初始位置
        log_once("[拍照] step=5, 正式成像-子流程1:计算初始位置");
        flag_Fpga_bg = 0; // 曝光信号置零
        // 如果成像模式是广域搜索
        if (main_Control_State_Param.irst_form_mode == 1) {
            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_GY);                                                                 // 图像处理：图像模式1
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1;                                          // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1;                                          // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0;                                          // 非刚进入速度信号
            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_Normal();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_Normal();
            }
        }
        // 如果成像模式是区域成像
        else if (main_Control_State_Param.irst_form_mode == 2) {
            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_QY);                        // 图像处理：图像模式1
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
            param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号
            // 计算函数
            comp_QY_Photo_Normal();
        }
        // 如果成像模式是区域监视
        else if (main_Control_State_Param.irst_form_mode == 3) {
            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_VIEW); // 图像处理：图像模式2
            //			make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_GY);//图像处理：图像模式1
            comp_QY_Video_Normal();
        }

        step++;
        cnt_wait = 0;
        break;
    case 6:
        // 子流程2：预置
        log_once("[拍照] step=6, 子流程2:预置");
        make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                  // 框架：准备
        make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                    // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // fpga停拍

        // 如果成像模式是广域搜索
        if (main_Control_State_Param.irst_form_mode == 1) {
            make_Mess_To_TG(TG_CMD_GYCX, main_Control_State_Param.irst_form_mode);
        }
        // 如果成像模式是区域成像
        else if (main_Control_State_Param.irst_form_mode == 2) {
            make_Mess_To_TG(TG_CMD_QYCX, main_Control_State_Param.irst_form_mode);
        }
        // 如果成像模式是区域监视
        else if (main_Control_State_Param.irst_form_mode == 3) {
            make_Mess_To_TG(TG_CMD_QYJS, main_Control_State_Param.irst_form_mode);
        }
        TG_AnalyseCmd();                                                 // 调光指令判断
        TiaoGuang();                                                     // 拍照调光处理
        main_Control_State_Param.trans_state = V_ID_DATA_TRANS_FLAG_YES; // 传图状态，是

        if ((2 == mess_From_KJ.status_sub && mess_From_TJ.state == 2 && mess_From_TG.Photo_state == 1 && cnt_wait > 217) || cnt_wait > 300) // 留1s以上，保证传图状态已经发出
        {
            make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS); // 图像处理：传输图像

            step++; // 进入下一阶段
            cnt_wait        = 0;
            flag_zzxx_valid = FPGA_ZSXX_VALID; // 注释信息有效标志:无效
        }
        break;

    case 7:
        // 子流程3：成像
        log_once("[拍照] step=7, 子流程3:成像");
        // 如果成像模式是广域搜索
        if (main_Control_State_Param.irst_form_mode == 1) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 0; // 第一次调用标志
            // 如果当前为位置信号，新获取的为速度信号，说明刚进入速度信号，进行换向	//0A_4为位置/速度信号；高电平为位置；低电平为速度
            if (param_Compute_Input_Fromfpga.flag_Speed_OR_Locate == 1 && gpio0AIn(4) == 0) {
                param_Compute_Input_Fromfpga.flag_First_Into_Speed = 1; // 刚进入速度信号标志
                // 名  称:光电周期号，在外面速度位置信号换向时累加
                // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
                main_Control_State_Param.cycleNo++;

                // 名  称:条带号，在外面速度位置信号换向时累加
                //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
                main_Control_State_Param.lineNo++;
                // 名  称:条带内序号，换向清零
                //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
                main_Control_State_Param.in_lineNo = 0;
            }
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate = gpio0AIn(4); // 更新速度位置信号

            make_Mess_To_KJ(KJ_CMD_SCAN, KJ_CMD_KF_MODE_YZJ);                    // 框架：摆扫
            make_Mess_To_TJ(TJ_CMD_GYCX, TJ_CMD_VIEW_DEFAULT);                   // 调焦：广域
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_GY_PHOTO, flag_zzxx_valid); // fpga：开始拍照
            make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                                 // 图像处理空指令

            // 调光用
            make_Mess_To_TG(TG_CMD_GYCX, main_Control_State_Param.irst_form_mode);
            TG_AnalyseCmd(); // 调光指令判断
            TiaoGuang();     // 拍照调光处理

            // 计算
            if (V_IR_WIDE_IMAGE_MODE_DIS_PRIO == cmd_From_FC.irst_cmd_param_IR_wide_image_paras.IR_WIDE_IMAGE_MODE) // 如果是距离优先
            {
                // 距离近界、距离远界、扫描方向、目标区域高度，四个参数有效
                comp_GY_Dis_Normal();
            } else // 如果是方位优先
            {
                // 量程、扫描起始角、扫描结束角、目标区域高度，四个参数有效
                comp_GY_Az_Normal();
            }
        }

        // 如果成像模式是区域成像
        else if (main_Control_State_Param.irst_form_mode == 2) {
            param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 0; // 第一次调用标志
            // 如果当前为位置信号，新获取的为速度信号，说明刚进入速度信号，进行换向
            if (param_Compute_Input_Fromfpga.flag_Speed_OR_Locate == 1 && gpio0AIn(4) == 0) {
                param_Compute_Input_Fromfpga.flag_First_Into_Speed = 1; // 刚进入速度信号标志

                // 如果完成该区域，重置条带号，并累加周期号
                if (main_Control_State_Param.lineNo == param_Compute_Output.qy_td_total_num) {
                    main_Control_State_Param.lineNo = 0;
                    //					main_Control_State_Param.cycleNo++;
                }

                // 名  称:条带号，在外面速度位置信号换向时累加
                //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
                main_Control_State_Param.lineNo++;

                // 名  称:条带内序号，换向清零
                //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
                main_Control_State_Param.in_lineNo = 0;
            }
            param_Compute_Input_Fromfpga.flag_Speed_OR_Locate = gpio0AIn(4); // 更新速度位置信号

            make_Mess_To_KJ(KJ_CMD_SCAN, KJ_CMD_KF_MODE_YZJ);                    // 框架：摆扫
            make_Mess_To_TJ(TJ_CMD_QYCX, TJ_CMD_VIEW_DEFAULT);                   // 调焦：区域成像
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_QY_PHOTO, flag_zzxx_valid); // fpga：开始拍照，区域成像
            make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                                 // 图像处理空指令

            // 调光用
            make_Mess_To_TG(TG_CMD_QYCX, main_Control_State_Param.irst_form_mode);
            TG_AnalyseCmd(); // 调光指令判断
            TiaoGuang();     // 拍照调光处理

            // 计算函数
            comp_QY_Photo_Normal();

            // 如果是单次成像并且成像完成，回待机
            if ((param_Compute_Input_Fromfc.comp_IR_AREA_IMA_MODE == V_IR_IMG_MODE_ONCE && 1 == param_Compute_Output.QYCX_Over_flag) && flag_Fpga_bg == 0) {
                cnt_wait_cmd++;

                make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                    // 框架停止工作
                make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                 // 调焦收藏
                make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, flag_zzxx_valid); // 向FPGA发1

                // 等待伺服、框架等分系统到位
                if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2) || cnt_wait_cmd > 600) {
                    // 设置系统状态位
                    update_Irst_State(V_IRST_WORK_STATE_STBY); // 更新IRST工作状态

                    send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                    clean_cmd_From_FC();       // 清理指令
                    clean_cmd_ImageInfo_Num(); // 重置图像序号
                    cnt_wait_cmd                        = 0;
                    step                                = 0;
                    cnt_wait                            = 0;
                    param_Compute_Output.QYCX_Over_flag = 0; // 扫描完成标志清零
                }
            }

        }
        // 如果成像模式是区域监视
        else if (main_Control_State_Param.irst_form_mode == 3) {
            make_Mess_To_TJ(TJ_CMD_QYJS, TJ_CMD_VIEW_DEFAULT);                   // 调焦：区域监视
            make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_QY_VIDEO, flag_zzxx_valid); // fpga：开始拍照，区域成像
            make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                                 // 图像处理空指令
            // 调光用
            make_Mess_To_TG(TG_CMD_QYJS, main_Control_State_Param.irst_form_mode);
            TG_AnalyseCmd(); // 调光指令判断
            TiaoGuang();     // 拍照调光处理

            // 如果是区域监视模式
            if (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NOT_TRACKED || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NA || cmd_From_FC.irst_cmd_EXIT_TGT_TRACK == 1) // 如果不是自动跟踪中
            {
                // 计算函数
                // 3.区域监视--按照准备计算出的经纬高进行成像
                comp_QY_Video_Normal();
                make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
                make_Mess_To_TXCL_CMD(TX_CMD_STOP_TRACK);           // 图像处理指令消息：停止跟踪
            } else                                                  // 如果在跟踪中
            {
                // 跟踪状态改变需要上报
                if (track_State != main_Control_State_Param.track_state) {
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    track_State = main_Control_State_Param.track_state;
                }

                // 一直发跟踪
                make_Mess_To_KJ(KJ_CMD_TRACK, KJ_CMD_KF_MODE_STOP); // 框架：跟踪
            }

            if (cmd_From_FC.irst_cmd_ENTER_TGT_TRACK == 1) // 如果收到自动跟踪指令
            {
                cnt_wait_cmd++;

                if (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_TRACK_ING || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_MATCH_ING) // 如果是自动跟踪中
                    make_Mess_To_KJ(KJ_CMD_TRACK, KJ_CMD_KF_MODE_STOP);                                                                                         // 框架：凝视
                else
                    make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
                make_Mess_To_TXCL_CMD(TX_CMD_TRACK);                    // 图像处理指令消息：跟踪，图像处理根据图像模式自行判断

                if (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_TRACK_ING || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_MATCH_ING || cnt_wait_cmd > 84) // 如果回报稳定跟踪
                {
                    send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    if (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_TRACK_ING || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_MATCH_ING) {
                        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                        // 回复执行完成
                        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                    } else {
                        // 回复执行完成
                        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_NACK, V_ACT_REFUSED_REASON_NA);
                    }
                    cmd_From_FC.irst_cmd_ENTER_TGT_TRACK = 0;
                    cnt_wait_cmd                         = 0;
                }
            }

            if (cmd_From_FC.irst_cmd_EXIT_TGT_TRACK == 1) // 如果收到退出自动跟踪指令，回之前工作状态
            {
                cnt_wait_cmd++;

                make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
                make_Mess_To_TXCL_CMD(TX_CMD_STOP_TRACK);           // 图像处理指令消息停止跟踪
                // 如果已经停止跟踪
                if ((main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NOT_TRACKED || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NA) && cnt_wait_cmd > 20) {
                    make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视

                    // 设置系统状态位
                    update_Irst_State(V_IRST_WORK_STATE_TAKE_PIC); // 回监视
                    update_Irst_Mode(V_IRST_FORM_MODE_AREA_MONI);  // 更新IRST成像模式

                    send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                    send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                    // 回复执行完成
                    send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                    cmd_From_FC.irst_cmd_EXIT_TGT_TRACK = 0;
                    cnt_wait_cmd                        = 0;
                }
            }
        }

        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 1, 1);

        // 8.成像传感器控制——收藏、待机、拍照
        if (cmd_From_FC.irst_cmd_SENSOR_SET == 1) {
            cnt_wait_cmd++;
            make_Mess_To_TXCL_CMD(TX_CMD_SENSOR_SET);
            if (cnt_wait_cmd > 2) {
                cmd_From_FC.irst_cmd_SENSOR_SET = 0;
                cnt_wait_cmd                    = 0;
            }
        }

        break;
    }
}

// 工作流程控制----自检测
void check_Model_WorkControl() {
    int           percent;          // 自检进度百分比
    static UINT16 step         = 0; // 函数内流程控制
    static UINT16 cnt_wait     = 0; // 子流程等待时间计时
    static UINT16 cnt_wait_cmd = 0; // 子流程指令执行等待时间计时

    static UINT16 cnt_wait_report = 0; // 上报进度用

    // 计数器累加，记录有几个5ms
    cnt_wait++;
    cnt_wait_report++; // 上报进度用
    // 判断收到的各种指令
    // 如果收到1.	（通用）工作模式请求指令
    if (cmd_From_FC.general_cmd_MODE_SWITCH == 1) {
        cnt_wait_cmd++;
        if (cmd_From_FC.subsys_main_oper_mode == V_SUBSYS_MAIN_OPER_MODE_STOP) // 如果是关机
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2) || cnt_wait_cmd > 600) {
                make_Mess_To_DY(0, 0, 0, 0, 0); // 电源分系统通信，关闭所有电源
                // 设置系统状态位
                update_Work_State(V_SUBSYS_WORK_STATE_OFF); // 更新相机工作状态
                update_Main_Mode(V_SUBSYS_MAIN_MODE_STOP);  // 更新相机工作模式
                update_Irst_State(V_IRST_WORK_STATE_NA);    // 更新IRST工作状态
                update_Irst_Mode(V_IRST_FORM_MODE_NA);      // 更新IRST成像模式

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }
        return;
    }

    // 如果收到2.	修改光电工作状态：收藏
    if (cmd_From_FC.irst_cmd_STATE_SET == 1) {
        cnt_wait_cmd++;
        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_COLLECT) // 如果是收藏
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1

            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2) || cnt_wait_cmd > 600) // 超时3s
            {
                // 设置系统状态位
                update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }

        return;
    }

    // 自检过程中，实时判断功能单元自检中发生新故障或原故障消失，子系统上报HMC与伴随数据,已经在定时器中完成

    // 上报工作进度，每1s上报一次
    if (cnt_wait_report % 200 == 0) {
        percent = (cnt_wait_report * 10000.0) / ((1000 / MAIN_PERIOD_TIME) * 45);
        send_Mess_WORK_STATE_REPORT(0, percent); // 上报工作状态更新，自检进度更新
    }

    switch (step) {
    case 0:                                                   // 向各分系统发送“分系统自检”指令
        make_Mess_To_KJ(KJ_CMD_CHECK, KJ_CMD_KF_MODE_STOP);   // 框架自检
        make_Mess_To_TJ(TJ_CMD_CellBIT, TJ_CMD_VIEW_DEFAULT); // 调焦自检
        make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                  // 图像处理：空指令
        make_Mess_To_TG(TG_CMD_CellBIT, 0);                   // 向调光发（写结构体）
        TG_AnalyseCmd();                                      // 调光指令判断
        TG_SelfTest();                                        // 自检调光处理

        if (cnt_wait > 20) {
            step     = 1;
            cnt_wait = 0;
        }
        break;

    case 1: // 等待分系统回报
        if ((mess_From_KJ.status_sub == 2 && mess_From_TJ.status1_zjzt == 0 && mess_From_PCS_DATA.status_gdgzms != 4) || cnt_wait > (1000 / MAIN_PERIOD_TIME) * 20) {
            step     = 2;
            cnt_wait = 0;
        }
        break;

    case 2: // 子流程1：计算初始位置

        param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 1; // 第一次调用标志
        param_Compute_Input_Fromfpga.flag_Speed_OR_Locate         = 1; // 速度位置信号置为位置
        param_Compute_Input_Fromfpga.flag_First_Into_Speed        = 0; // 非刚进入速度信号
        // 5.维护自检，执行广域成像——距离优先，右倾成像
        comp_GY_Dis_WHZJ();

        step++;
        cnt_wait = 0;
        break;
    case 3:                                                                     // 子流程2：预置
        make_Mess_To_KJ(KJ_CMD_ZHNBEI, KJ_CMD_KF_MODE_STOP);                    // 框架：准备
        make_Mess_To_TJ(TJ_CMD_Wait, TJ_CMD_VIEW_DEFAULT);                      // 调焦：待机
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // fpga停拍

        if ((2 == mess_From_KJ.status_sub && mess_From_TJ.state == 2 && cnt_wait > 2) || cnt_wait > 200) // 最长1s伺服到位
        {
            step++; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

    case 4: // 子流程3：成像

        param_Compute_Input_Fromfpga.flag_GYQYPhoto_FIRST_Compute = 0; // 第一次调用标志
        // 如果当前为位置信号，新获取的为速度信号，说明刚进入速度信号，进行换向	//0A_4为位置/速度信号；高电平为位置；低电平为速度
        if (param_Compute_Input_Fromfpga.flag_Speed_OR_Locate == 1 && gpio0AIn(4) == 0) {
            param_Compute_Input_Fromfpga.flag_First_Into_Speed = 1; // 刚进入速度信号标志
        }
        param_Compute_Input_Fromfpga.flag_Speed_OR_Locate = gpio0AIn(4); // 更新速度位置信号

        make_Mess_To_KJ(KJ_CMD_SCAN, KJ_CMD_KF_MODE_YZJ);                      // 框架：摆扫
        make_Mess_To_TJ(TJ_CMD_GYCX, TJ_CMD_VIEW_DEFAULT);                     // 调焦：广域
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_GY_PHOTO, FPGA_ZSXX_INVALID); // fpga：开始拍照

        // 调光用
        make_Mess_To_TG(TG_CMD_GYCX, main_Control_State_Param.irst_form_mode);
        TG_AnalyseCmd(); // 调光指令判断
        TiaoGuang();     // 拍照调光处理

        // 5.维护自检，执行广域成像——距离优先，右倾成像
        comp_GY_Dis_WHZJ();

        // 超时判定：自检过程总共20s（包括图像链路测试）20s时间到，回到收藏状态
        if (cnt_wait > (1000 / MAIN_PERIOD_TIME) * 20) {
            step            = 0;
            cnt_wait        = 0;
            cnt_wait_report = 0;
            cnt_wait_cmd    = 0;
            // 进入收藏状态
            update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);   // 工作模式回正常
            update_Work_State(V_SUBSYS_WORK_STATE_NORMAL); // 工作模式回正常
            update_Irst_State(V_IRST_WORK_STATE_COLLECT);  // 更新IRST工作状态

            // 向飞机报送相关信息
            send_Mess_WORK_STATE_REPORT(0, 10000); // 上报工作状态更新，完成初始化
            make_Mess_IRST_OPERATIONAL_PARAS();    // 上报工作参数
            send_Mess_WORK_STATE_REPORT(0, 10000); // 上报工作状态更新，自检进度更新
            send_Mess_IRST_OPERATIONAL_PARAS();    // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令

            return;
        }
        break;

    default:
        break;
    }
}
// 工作流程控制----下电
void na_down_WorkControl() {
    if (main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_NORMAL) // 如果被切到正常，说明该上电了
    {
        update_Work_State(V_SUBSYS_WORK_STATE_NORMAL); // 更新相机工作状态
        update_Main_Mode(V_SUBSYS_MAIN_MODE_INI);      // 更新相机工作模式
        update_Irst_State(V_IRST_WORK_STATE_INIT);     // 更新IRST工作状态
        update_Irst_Mode(V_IRST_FORM_MODE_NA);         // 更新IRST成像模式
    }
}
// 工作流程控制----静态成像-内部使用
void nb_jtphoto_WorkControl() {
    static UINT16 step            = 0;                 // 函数内流程控制
    static UINT16 cnt_wait        = 0;                 // 子流程等待时间计时
    static UINT16 cnt_wait_cmd    = 0;                 // 子流程指令执行等待时间计时
    static UINT8  flag_zzxx_valid = FPGA_ZSXX_INVALID; // 注释信息有效标志

    cnt_wait++;

    // 判断收到的各种指令
    // 如果收到2.	修改光电工作状态：收藏
    if (cmd_From_FC.irst_cmd_STATE_SET == 1) // 修改工作状态
    {
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 1); // 不需要发送fc
        cnt_wait_cmd++;
        if (cmd_From_FC.irst_cmd_param_irst_work_state == V_IRST_WORK_STATE_COLLECT && flag_Fpga_bg == 0) // 如果是收藏
        {
            make_Mess_To_KJ(KJ_CMD_STOP, KJ_CMD_KF_MODE_STOP);                      // 框架停止工作
            make_Mess_To_TJ(TJ_CMD_Collect, TJ_CMD_VIEW_DEFAULT);                   // 调焦收藏
            make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1
            // 等待伺服、框架等分系统到位
            if ((mess_From_KJ.status_sub == 2 && mess_From_KJ.status_work == 0 && mess_From_TJ.state == 2 && cnt_wait_cmd > 200) || cnt_wait_cmd > 600) // 超时3s
            {
                make_Mess_To_JLY(JLY_CMD_CLOSE); // 记录仪:关，确保图发送完毕，延迟发送记录仪关
                // 设置系统状态位
                update_Irst_State(V_IRST_WORK_STATE_COLLECT); // 更新IRST工作状态

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
                cnt_wait_cmd = 0;
                step         = 0;
                cnt_wait     = 0;
            }
        }
        return;
    }
    // 如果收到9.	可见光成像参数修改	//如果收到10.	红外成像参数修改
    if (cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE == 1 || cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE == 1) {

        // 调焦参数已经处理完，差调光参数
        make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
        // 回复执行完成
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
        clean_cmd_From_FC(); // 清理指令
        cnt_wait_cmd = 0;

        return;
    }

    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数

    switch (step) {

    case 0:                                                                     // 设置参数
        make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_GY);                                 // 图像处理：图像模式1
        make_Mess_To_TJ(TJ_CMD_StaticPhoto, TJ_CMD_VIEW_DEFAULT);               // 调焦消息构建1
        make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                     // 框架，凝视
        make_Mess_To_FPGA(FPGA_STOP_PHOTO, FPGA_STOP_PHOTO, FPGA_ZSXX_INVALID); // 向FPGA发1
        make_Mess_To_JLY(JLY_CMD_OPEN);                                         // 记录仪:开

        if (cnt_wait > 3) {
            step++;
        }
        break;
    case 1:
        make_Mess_To_TXCL_CMD(TX_CMD_IMAGE_TRANS); // 图像处理：传输图像
        step++;
        break;
    case 2:                             // 成像
        make_Mess_To_JLY(JLY_CMD_None); // 记录仪:空指令
        // 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
        photoing_Control(&flag_zzxx_valid, 0, 1); // 不需要发送fc

        make_Mess_To_TJ(TJ_CMD_StaticPhoto, TJ_CMD_VIEW_DEFAULT);            // 调焦：静态成像监视
        make_Mess_To_FPGA(FPGA_START_PHOTO, FPGA_JT_PHOTO, flag_zzxx_valid); // fpga：开始拍照，区域成像
        make_Mess_To_TXCL_CMD(TX_CMD_EMPTY);                                 // 图像处理空指令
        // 调光用
        make_Mess_To_TG(TG_CMD_StaticPhoto, main_Control_State_Param.irst_form_mode);
        TG_AnalyseCmd();                                                                                                                           // 调光指令判断
        TiaoGuang();                                                                                                                               // 拍照调光处理
        if (main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NOT_TRACKED || main_Control_State_Param.track_state == V_TGT_TRACK_STATE_NA) // 如果不是自动跟踪中
        {
            make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
        } else {
            make_Mess_To_KJ(KJ_CMD_TRACK, KJ_CMD_KF_MODE_STOP); // 框架：跟踪
        }
        if (cmd_From_FC.irst_cmd_ENTER_TGT_TRACK == 1) // 如果收到自动跟踪指令
        {
            cnt_wait_cmd++; // 等待几个周期,需要10帧图像

            if (cnt_wait_cmd < 84) // 如果没到10帧
            {
                // 一直发跟踪
                make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
                make_Mess_To_TXCL_CMD(TX_CMD_TRACK);                // 图像处理指令消息：跟踪，图像处理根据图像模式自行判断
            }
            // 持续10帧还没回报稳定跟踪，需要回到原状态
            else {
                make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC); // 框架：凝视
                make_Mess_To_TXCL_CMD(TX_CMD_STOP_TRACK);           // 图像处理指令消息：跟踪，图像处理根据图像模式自行判断
                send_Mess_WORK_STATE_REPORT(0, 0);                  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS();                 // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS();                 // IRST工作参数报告-发送
                cnt_wait_cmd = 0;
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
            }

            if (cmd_From_FC.irst_cmd_ENTER_TGT_TRACK == 1) // 如果回报稳定跟踪
            {
                make_Mess_To_KJ(KJ_CMD_TRACK, KJ_CMD_KF_MODE_STOP); // 框架：跟踪

                send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
                make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
                send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
                cnt_wait_cmd = 0;
                // 回复执行完成
                send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
                clean_cmd_From_FC(); // 清理指令
            }
        }

        if (cmd_From_FC.irst_cmd_EXIT_TGT_TRACK == 1) // 如果收到退出自动跟踪指令，回之前工作状态
        {

            make_Mess_To_KJ(KJ_CMD_WATCH, KJ_CMD_KF_MODE_OWBC);                   // 框架：凝视
            make_Mess_To_TXCL_CMD(TX_CMD_STOP_TRACK);                             // 图像处理指令消息停止跟踪
            main_Control_State_Param.track_state = V_TGT_TRACK_STATE_NOT_TRACKED; // 未跟踪

            // 设置系统状态位
            update_Irst_State(V_IRST_WORK_STATE_TAKE_PIC); // 回待机
            update_Irst_Mode(V_IRST_FORM_MODE_AREA_MONI);  // 更新IRST成像模式

            send_Mess_WORK_STATE_REPORT(0, 0);  // 上报工作状态更新
            make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
            send_Mess_IRST_OPERATIONAL_PARAS(); // IRST工作参数报告-发送
            // 回复执行完成
            send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
            clean_cmd_From_FC(); // 清理指令
        }

        break;
    default:
        break;
    }
}
// 参数超限判断
void param_Over_Range_Judge() {
    int i = 0;
    // 实时计算超限情况
    // 广域，待定
    // 区域成像
    for (i = 0; i < 3; i++) {
        if (param_Compute_Input_Fromfc.comp_area_image_paras_validity[i] == V_AREA_VALIDITY_VALID) {
            comp_QY_over(i); // 有效性计算
        } else {
            param_Compute_Output.real_area_image_paras[i].IR_IMG_FLAG = V_IR_IMG_FLAG_NA;
        }
    }
    // 区域监视
    if (cmd_From_FC.irst_cmd_param_area_monitor_paras_validity == 1) {
        comp_QY_Video_Normal(); // 有效性计算
    } else {
        param_Compute_Output.real_area_monitor_paras.IR_IMG_FLAG = V_IR_IMG_FLAG_NA;
    }

    make_Mess_IRST_OPERATIONAL_PARAS(); // 上报工作参数
    //	send_Mess_IRST_OPERATIONAL_PARAS();//IRST工作参数报告-发送
}

// 红外校正
// 在“待机”状态中允许执行，响应“校正”指令，相机工作状态置为“准备中”，回报状态在“准备状态参数”中填写
UINT8 jiaozheng_WorkControl(UINT8 rst_n) {
    static UINT16 step     = 0; // 函数内流程控制
    static UINT16 cnt_wait = 0; // 子流程等待时间计时

    // 计数器累加，记录有几个5ms
    cnt_wait++;
    if (rst_n == 0) // 内部step，cnt_wait 复位
    {
        step     = 0;
        cnt_wait = 0;
        return 0;
    }

    switch (step) {

    case 0:
        // 给调焦非均匀性校正指令，等调焦回复到位
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP); // 框架：待机
        make_Mess_To_TJ(TJ_CMD_HWJZ, TJ_CMD_VIEW_DEFAULT); // 调焦：非均匀性校正

        if ((1 == mess_From_TJ.status2_jzb_dw /*&& mess_From_KJ.status_sub == 2*/ && cnt_wait > 200) || cnt_wait > 2400) // 调焦到位超时 3s
        {
            step     = 1; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

    case 1:
        // 给调光校正指令，等调光返回执行完成
        // 调光
        make_Mess_To_TG(TG_CMD_HWJZ, JTGMODE_GY); // 调光
        TG_AnalyseCmd();                          // 调光指令判断
        HW_JiaoZheng();
        make_Mess_To_TJ(TJ_CMD_HWJZ, TJ_CMD_VIEW_DEFAULT); // 调焦：非均匀性校正

        if (mess_From_TG.HWJiaoZheng == 2 || cnt_wait > 3000) // 执行完成
        {
            step     = 2; // 进入下一阶段
            cnt_wait = 0;
        }
        break;

    case 2:
        // 等调焦回复到位
        if (0 == mess_From_TJ.status2_jzb_dw) // 调焦反馈挡板回到非校正位置后
        {
            make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT); // 调焦：空指令，非均匀性校正停止
            step     = 3;                                      // 进入下一阶段
            cnt_wait = 0;
        }
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP); // 框架：待机
        if (cnt_wait > 600)                                // 调焦到位超时 3s
        {
            step     = 3; // 进入下一阶段
            cnt_wait = 0;
        }

        break;
    case 3:
        // 结束非均匀性校正，等待外部重置
        make_Mess_To_TJ(TJ_CMD_None, TJ_CMD_VIEW_DEFAULT); // 调焦：空指令
        make_Mess_To_KJ(KJ_CMD_WAIT, KJ_CMD_KF_MODE_STOP); // 框架：待机
        step++;
    default:
        break;
    }

    if (step > 3)
        return 1;
    else
        return 0;
}

// 图像处理注释信息发送标志位、fc注释信息发送、帧号累加等
void photoing_Control(UINT8 *toTxcl_zzxx_valid, UINT8 fcSend_Flag, UINT8 numup_Flag) {
    static UINT16 cnt_wait = 0; // 子流程等待时间计时
    if (flag_Fpga_bg == 1)      // 曝光信号到达，延时20ms发送有效注释信息
    {
        cnt_wait++;
        *toTxcl_zzxx_valid = FPGA_ZSXX_INVALID; // 注释信息有效标志:无效
        if (cnt_wait == 4)                      // 延时20ms发送有效注释信息
        {
            if (numup_Flag == 1) // 如果需要累加序号
            {
                // 累加条带号、帧号
                // 名  称:图像帧序号
                main_Control_State_Param.totalNo = main_Control_State_Param.totalNo + 1;
                // 如果在监视模式
                if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
                    // 名  称:光电周期号
                    // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
                    main_Control_State_Param.cycleNo++;
                    // 名  称:条带号
                    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
                    main_Control_State_Param.lineNo = 1;
                    // 名  称:条带内序号
                    //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
                    main_Control_State_Param.in_lineNo = 1;
                }
                // 如果在广域模式
                if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG) {
                    // 名  称:光电周期号，在外面速度位置信号换向时累加
                    // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
                    //					main_Control_State_Param.cycleNo;

                    // 名  称:条带号，在外面速度位置信号换向时累加
                    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
                    //					main_Control_State_Param.lineNo;

                    // 名  称:条带内序号
                    //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
                    main_Control_State_Param.in_lineNo++;
                }
                // 如果在区域成像模式
                if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
                    // 名  称:光电周期号,计算赋值
                    // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
                    main_Control_State_Param.cycleNo = param_Compute_Output.qy_zq_num;

                    // 名  称:条带号，在外面速度位置信号换向时累加
                    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
                    //					main_Control_State_Param.lineNo;

                    // 名  称:条带内序号
                    //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
                    main_Control_State_Param.in_lineNo++;
                }
            }

            make_Mess_To_TXCL_ZSXX_Time_Pos();    // 记录pos信息、时间信息
            make_Mess_To_TXCL_ZSXX();             // 本周期发送注释信息
            *toTxcl_zzxx_valid = FPGA_ZSXX_VALID; // 注释信息有效标志:有效

            // logMsg("-totalNo:%d----lineNo:%d----cycleNo:%d----in_lineNo:%d--frameNum:%d--\n",
            //        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMG_ID,
            //        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_LineNo,
            //        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_CycleNo,
            //        mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_LineNo, mess_To_FPGA.frames_Num, 6);

            log_once("图像帧序号:%d, 条带号:%d, 周期号:%d, 条带内序号:%d, 条带帧数:%d",
                     mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.IMG_ID,
                     mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_LineNo,
                     mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_CycleNo,
                     mess_To_TXCL_ZSXX.to_Txcl_image_paras_transit.A818_EO_LineNo,
                     mess_To_FPGA.frames_Num);
            log_once("框架曝光时刻俯仰角:%.3f, 框架曝光时刻方位角:%.3f",
                     0.0001f * mess_From_KJ.exposure_pitch_frame,
                     0.0001f * mess_From_KJ.exposure_direction_frame);
        }
        if (cnt_wait == 5) // 25ms延时，发送fc注释信息
        {
            if (fcSend_Flag == 1) {
                // 如果是广域或区域成像
                if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_WIDE_IMAG || main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_IMAG) {
                    // 如果是可见光
                    if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LIGHT) {
                        send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT(); // 上报可见注释信息
                    }
                    // 如果是红外
                    if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_INFRARED) {
                        send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT(); // 上报红外注释信息
                    }
                    if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LANDI || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_IANDL || cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_NA) {
                        send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT(); // 上报红外注释信息
                        send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT(); // 上报可见注释信息
                    }
                }
                // 如果是区域监视
                if (main_Control_State_Param.irst_form_mode == V_IRST_FORM_MODE_AREA_MONI) {
                    // 如果是可见光单独
                    if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LIGHT) {
                        send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT(); // 上报可见注释信息
                        if (main_Control_State_Param.cycleNo % 24 == 1) {
                            send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT_VIEW(); // 上报可见注释信息——监视模式单帧
                        }
                    }
                    // 如果是红外单独
                    else if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_INFRARED) {
                        send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT(); // 上报红外注释信息
                        if (main_Control_State_Param.cycleNo % 24 == 1) {
                            send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT_VIEW(); // 上报红外注释信息——监视模式单帧
                        }
                    }
                    // 如果是可见+红外
                    else if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_LANDI) {
                        send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT(); // 上报可见注释信息
                        if (main_Control_State_Param.cycleNo % 24 == 1) {
                            send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT_VIEW(); // 上报可见注释信息——监视模式单帧
                            send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT_VIEW(); // 上报红外注释信息——监视模式单帧
                        }
                    }
                    // 如果是红外+可见
                    else if (cmd_From_FC.irst_cmd_param_IR_SENSOR == V_IR_SENSOR_IANDL) {
                        send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT(); // 上报红外注释信息
                        if (main_Control_State_Param.cycleNo % 24 == 1) {
                            send_Mess_RECONNAISED_AREA_TV_2GCS_EVENT_VIEW(); // 上报可见注释信息——监视模式单帧
                            send_Mess_RECONNAISED_AREA_IR_2GCS_EVENT_VIEW(); // 上报红外注释信息——监视模式单帧
                        }
                    }
                }
            }
            cnt_wait     = 0; // 重置计时
            flag_Fpga_bg = 0; // 取消曝光信号

            //			logMsg("---update_counter:%d--------cycleNo:%d-------totalNo:%d---------\n",
            //					mess_ToFC_RECONNAISED_AREA_TV_2GCS_EVENT.update_counter,main_Control_State_Param.cycleNo,main_Control_State_Param.totalNo,4,5,6);
        }
    } else {
        *toTxcl_zzxx_valid = FPGA_ZSXX_INVALID; // 注释信息有效标志:无效
    }
}

// 其他基础工具函数
void clean_cmd_From_FC() // 重置指令缓存
{
    // 通用活动请求7个指令
    cmd_From_FC.general_cmd_MODE_SWITCH   = 0; // 工作模式请求
    cmd_From_FC.general_cmd_BIT_OPERATION = 0; // 执行BIT请求
    //	cmd_From_FC.general_cmd_MFL_OPERATION = 0;		//MFL操作请求——清除mfc
    //	cmd_From_FC.general_cmd_DATA_REQ = 0;			//子域数据请求
    //	cmd_From_FC.general_cmd_ICP1_MODE_SWITCH = 0;	//ICP1工作模式请求
    //	cmd_From_FC.general_cmd_ICP2_MODE_SWITCH = 0;	//ICP2工作模式请求
    //	cmd_From_FC.general_cmd_UNIQUE_ACT = 0;			//特殊活动请求
    //	cmd_From_FC.general_cmd_baoliu = 0;				//保留

    // 特殊活动请求16个指令
    cmd_From_FC.irst_cmd_STATE_SET             = 0; // 修改光电工作状态———按状态转换图
    cmd_From_FC.irst_cmd_IMAGE_MODE_CHG        = 0; // 成像模式修改——收藏、待机、拍照可接收，只有准备中、拍照有动作，其他保存参数
    cmd_From_FC.irst_cmd_WIDE_IMAGE_CNTL       = 0; // 修改广域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    cmd_From_FC.irst_cmd_AREA_IMAGE_CNTL       = 0; // 修改区域成像参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    cmd_From_FC.irst_cmd_WIDE_MONI_CNTL        = 0; // 修改区域监视参数——收藏、待机、拍照，只有准备中、拍照有动作，其他保存参数
    cmd_From_FC.irst_cmd_LIGHT_IMA_PARS_UPDATE = 0; // 可见光成像参数修改——收藏、待机、拍照，直接转发
    cmd_From_FC.irst_cmd_INFRA_IMA_PARS_UPDATE = 0; // 红外成像参数修改——收藏、待机、拍照，直接转发
    cmd_From_FC.irst_cmd_SENSOR_SET            = 0; // 成像传感器控制——所有模式
    //	cmd_From_FC.irst_cmd_SCENE_TYPE_CHANGE = 0;		//修改场景类型——只有收藏可修改场景
    //	cmd_From_FC.irst_cmd_WINDOW_FOG_REMOVE = 0;		//光窗去雾——收藏状态
    cmd_From_FC.irst_cmd_ENTER_TGT_TRACK = 0; // 进入图像跟踪——只有拍照、区域监视
    cmd_From_FC.irst_cmd_EXIT_TGT_TRACK  = 0; // 退出图像跟踪——只有拍照、区域监视
    cmd_From_FC.irst_cmd_IMU_ALIGN       = 0; // IMU对准
    cmd_From_FC.irst_cmd_INFRA_CORRECT   = 0; // 红外校正——只有待机
    cmd_From_FC.irst_cmd_FROZEN          = 0; // 冻结——拍照、区域监视
    cmd_From_FC.irst_cmd_VIDEO_BAND_SET  = 0; // 视频带宽设置——所有模式
}

// 重置图像序号
void clean_cmd_ImageInfo_Num() {
    // 图像号清零
    // 名  称:光电周期号
    // 说  明:完成一次规定收容宽度的摆扫定义为一个周期（从1开始），（区域监视每张图片为一个周期）
    main_Control_State_Param.cycleNo = 0;

    // 名  称:条带号
    //        光电：在一次区域成像（一个周期内），一次摆扫（左到右或右到左），叫做一个条带号。区域监视使用固定值01
    main_Control_State_Param.lineNo = 0;

    // 名  称:条带内序号
    //        表示一次摆扫左到右或右到左）过程每张图片的编号（从1开始），区域监视使用固定值01
    main_Control_State_Param.in_lineNo = 0;
}

void switchSubsysOperMode(SUBSYS_MAIN_OPER_MODE mode) {
    // Note: lcy 正常模式和STOP在共享内存中判断
    // 正常
    if (V_SUBSYS_MAIN_OPER_MODE_NORMAL == mode) {
        update_Work_State(V_SUBSYS_WORK_STATE_NORMAL); // 更新相机工作状态
        update_Main_Mode(V_SUBSYS_MAIN_MODE_NORMAL);   // 任何模式都可切入正常模式，直接切即可
        make_Mess_IRST_OPERATIONAL_PARAS();            // 上报工作参数
        send_Mess_IRST_OPERATIONAL_PARAS();            // IRST工作参数报告-发送
        // 回复执行完成
        send_Mess_IRST_ACT_REQ_REPORT(V_ACTIVITY_STATE_COMPLETED, V_ACT_REFUSED_REASON_NA);
    }
    // 停止/可关机模式——-下电——回到NA，所有模式可响应，在所有模式中判断该怎样进入关机
    else if (V_SUBSYS_MAIN_OPER_MODE_STOP == mode) {
        clean_cmd_From_FC();                     // 清除指令记录
        cmd_From_FC.general_cmd_MODE_SWITCH = 1; // 可以执行的指令置为1
        // 记录参数
        cmd_From_FC.subsys_main_oper_mode = V_SUBSYS_MAIN_OPER_MODE_STOP;
    }
    // Note: lcy ---------END---------------
}

bool ycAlreadyNormal() {
    return (main_Control_State_Param.work_state == V_SUBSYS_WORK_STATE_NORMAL &&
            main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_NORMAL);
}

bool ycInitializing() {
    // 如果这两个有一个还是init状态，就认为还在初始化
    return (main_Control_State_Param.irst_work_state == V_IRST_WORK_STATE_INIT ||
            main_Control_State_Param.main_mode == V_SUBSYS_MAIN_MODE_INI);
}
