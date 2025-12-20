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
    CameraSimulator(int port, std::string ip_control, int port_dst);
    ~CameraSimulator();

    // 初始化 建立与ControlSimulator的udp连接
    void init();

    // 单步计算
    void step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output);

    // 上电 delay: 上电延迟时间 单位: s
    void powerOn(int delay);
    // 冻结
    void freeze();
    // 下电
    void powerOff();

    // 设置周期性间隔
    void setPeriodicInterval(int ms) { this->periodic_interval = ms; };

  private:
    // 上电状态
    enum PowerStatus {
        POWER_UNKNOWN,
        POWER_ON,
        POWER_CHECKING,
        POWER_FREEZE,
        POWER_OFF,
    };
    std::atomic<PowerStatus> power_status_;

    // 上电参数
    std::thread      thread_power_on_;
    std::atomic<int> remain_time;

    // 锁
    std::mutex mtx_shm_;  // 共享内存锁
    std::mutex mtx_send_; // 发送锁

    // 共享内存
    SharedMemoryInput  shm_input_;
    SharedMemoryOutput shm_output_;

    // 将共享内存输入参数映射到本地(指针指向共享内存输入对应的位置)
    void pointShmInputParams();

    // 共享内存输入参数映射对应的主要变量
    char    *facility_power_supply_status_; // 设备供电状态参数 - 设备供电状态
    uint8_t *operation_mode_;               // 模拟器运行控制 - 控制模式

    // 更新共享内存输出
    void updateShmOutput();

    // todo: 计算模块
    // void compute();

    // UDP
    std::unique_ptr<UdpConnect> udp_;       // udp 连接 接收数据
    int                         port_;      // udp 监听端口
    std::string                 ip_contrl_; // udp 机载主控模拟器ip
    int                         port_dst_;  // udp 要发送到的端口(机载主控模拟器)

    /// @brief 接收数据 分类消息 放入队列 (对应原 fc_EventRecv_task )
    /// @param data udp包的指针
    /// @param size udp包的数据长度
    void udpEventRecv(char *data, int size);

    // 发送udp包到机载主控移植
    int sendPacket(const UdpPacket *ptr_pkt);

    /// @brief udp 发送msg函数
    /// @param topic_id   主题ID    (V_TOPIC_XXX_XXX)
    /// @param msg        msg数据指针
    /// @param size_msg   msg的数据长度
    void udpSendMsg(uint32_t topic_id, uint8_t *msg, uint32_t size_msg);

    // 发送udp消息到机载移植
    template <typename T>
    void udpSendMsg(uint32_t topic_id, T *msg) {
        udpSendMsg(topic_id, (uint8_t *)msg, sizeof(T));
    };

    // 周期性发送间隔 ms
    int periodic_interval = PERIOD_TASK_TIME;

    // 运行状态
    std::atomic<bool> running_subsystem_timer_;

    std::thread thread_main_ctrl_;       // 子线程2
    std::thread thread_other_process_;   // 子线程3
    std::thread thread_periodic_send_;   // 子线程4
    std::thread thread_subsystem_timer_; // 子线程5

    // 心跳计数
    std::atomic<uint64_t> heartbit_{0};
    std::atomic<bool>     running_hearbit;
    std::thread           thread_heartbit_;

    // 心跳线程
    void startHeartbitting();
    // 子线程1 udp连接: 数据接收函数 udpEventRecv 线程一直运行 与类的生命周期一致
    void startUdpConnect();
    // 子线程2 任务线程 运行函数 : 处理act_req以及主流程控制
    void startMainControl();
    // 子线程3 任务线程 运行函数 : 其他消息处理
    void startOtherProcess();
    // 子线程4 任务线程 运行函数 : 周期发送
    void startPeriodicSend();
    // 子线程5 任务线程 运行函数 : 5ms计时器
    void startTimer5ms();
    // 子线程6? 任务线程 运行函数 : 分系统计时器
    void startSubsystemTiming();

    // 开始所有任务线程 (不包括 udp线程、心跳线程)
    void startTaskThreads();

    // 5ms 计时器
    TimerPeriod timer_5ms_;

    // fpga 
    FpgaSimulator fpga_sim;

    // 超时时间 (子线程阻塞时间)
    std::chrono::milliseconds timeout = std::chrono::milliseconds(10);
};

#endif // CAMERA_SIM_H
