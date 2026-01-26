#ifndef CAMERA_SIM_H
#define CAMERA_SIM_H

#include <ICD/ICDB_ENUM_STRUCT_IRRM.H>
#include <ICD/ICDB_TOPIC_STRUCT_IRRM.H>
#include <yc/YC_Controller_Constant_Define.h>
#include <yc/YC_Controller_globalVal_Ext.h>

#include <fpga_sim.h>
#include <global_vars.h>
#include <shm_interface.h>
#include <timer_period.h>
#include <udp_packet.h>
#include <udp_trans.h>
#include <udpconnect.h>

#include <atomic>
#include <thread>
#include <thread_safe_queue.hpp>

class CameraSimulator {
  public:
    CameraSimulator(int port, int port_send, std::string ip_control, int port_dst);
    ~CameraSimulator();

    // 初始化 建立与ControlSimulator的udp连接
    void init();

    // 启动模型
    void start();

    // 单步计算
    void step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output);

    // 冻结
    void freeze();

    // 关闭
    void close();

    // 设置周期性间隔
    void setPeriodicInterval(int ms) { sim::periodic_interval = ms; };

    // 拍照测试
    void testPhotoing();

    // 设置与检测仪连接 (udp进行工作模式请求判断)
    void setConnectToJCY(bool to_jcy) { sim::is_simulating = false; };

  private:
    // 模型状态
    enum ModelStatus {
        STATUS_UNKNOWN,
        STATUS_INITIALIZED,
        STATUS_RUNNING,
        STATUS_FROZEN,
        STATUS_CLOSED,
    };
    std::atomic<ModelStatus> status_; // 模型状态

    // 心跳计数
    std::atomic<uint64_t> heartbit_{0};
    std::atomic<bool>     running_hearbit;
    std::thread           thread_heartbit_;
    // 心跳线程
    void startHeartbitting();

    // UDP
    int         port_;      // udp 监听端口
    int         port_send_; // udp 发送端口
    std::string ip_contrl_; // udp 机载主控模拟器ip
    int         port_dst_;  // udp 要发送到的端口(机载主控模拟器)

    // 运行线程
    std::thread thread_main_ctrl_;     // 子线程2
    std::thread thread_other_process_; // 子线程3
    std::thread thread_periodic_send_; // 子线程4

    // =============线程函数==============
    // 子线程1 udp连接: 数据接收函数 udpEventRecv 线程一直运行 与类的生命周期一致
    void startUdpConnect();
    // 子线程2 任务线程 运行函数 : 处理act_req以及主流程控制
    void initMainControl();
    // 子线程3 任务线程 运行函数 : 其他消息处理
    void initOtherProcess();
    // 子线程4 任务线程 运行函数 : 周期发送
    void initPeriodicSend();
    // ===============END=================

    // 初始化任务线程 (不包括 udp线程、心跳线程)
    void initTaskThreads();

    // fpga 仿真
    FpgaSimulator fpga_sim_;

    // 计算系数
    const double rad_to_deg  = 180.0 / PI;        // 弧度转度
    const double mrad_to_deg = 1e-3 * 180.0 / PI; // 毫弧度转度
    const double deg_to_rad  = PI / 180.0;        // 度转弧度
    const double deg_to_mrad = 1e3 * PI / 180.0;  // 度转毫弧度

    // ======================共享内存输入输出======================
    SharedMemoryInput  shm_input_;
    SharedMemoryOutput shm_output_;

    // 共享内存输入参数对应的主要变量
    char    facility_power_supply_status_ = 0; // 设备供电状态参数 - 设备供电状态
    uint8_t operation_mode_               = 0; // 模拟器运行控制 - 控制模式

    int member_status_ = 0; // 成员状态参数 - 成员状态 FunctionalUnitStatusMsg.St_UnitStatusData.U1_MemberStatus

    // 更新共享内存输入
    void updateSharedMemoryInput();
    // 更新共享内存输出
    void updateSharedMemoryOutput();

    enum SubsysStatus {
        SUBSYS_STATUS_UNKNOWN,
        SUBSYS_STATUS_NORMAL,
        SUBSYS_STATUS_STOP,
    };

    // 子系统状态
    std::atomic<SubsysStatus> subsys_status_{SUBSYS_STATUS_UNKNOWN};

    // 从共享内存中读取上电 设置模拟器为Normal
    void setSubsysNormal(int delay_sec);
    // 从共享内存中读取下电 设置模拟器为Stop
    void setSubsysStop();
    // =========================END==============================

    // 拍照测试
    std::atomic<bool> running_photoing_test{false};
    std::thread       thread_photoing_test_;
};

#endif // CAMERA_SIM_H
