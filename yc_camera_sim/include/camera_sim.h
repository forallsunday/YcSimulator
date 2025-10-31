#ifndef CAMERA_SIM_H
#define CAMERA_SIM_H

#include <ICD/ICDB_ENUM_STRUCT_IRRM.H>
#include <ICD/ICDB_TOPIC_STRUCT_IRRM.H>
#include <shm_interface.h>
#include <udp_packet.h>
#include <udpconnect.h>

#include <atomic>
#include <thread>
#include <thread_safe_queue.hpp>

class CameraSimulator {
  public:
    CameraSimulator(int port, std::string ip_dst, int port_dst);
    ~CameraSimulator();

    // 初始化 建立与ControlSimulator的udp连接
    void init();

    // 单步计算
    void step(const SharedMemoryInput *shm_input, SharedMemoryOutput *shm_output);

  private:
    // 心跳计数
    uint64_t          heartbit_;
    std::atomic<bool> updatting_heartbit_;
    std::thread       heartbit_thread_;
    void              startHeartbitting();

    // 上电
    std::atomic<bool> is_powered_on_;
    std::thread       power_on_thread_;
    // int               remain_time;
    std::atomic<int> remain_time;
    void             powerOn(int delay);
    // 下电
    void powerOff();

    // 共享内存
    SharedMemoryInput  shm_input_;
    SharedMemoryOutput shm_output_;
    std::mutex         mtx_shm_; // 共享内存锁

    //
    char    *facility_power_supply_status; // 设备供电状态参数 - 设备供电状态
    uint8_t *operation_mode;               // 模拟器运行控制 - 控制模式
    // 将共享内存输入参数更新映射到本地指针
    void updateShmInputParams();

    // 计算模块
    // void compute();

    // 更新共享内存输出
    void updateShmOutput();

    // udp
    std::unique_ptr<UdpConnect> udp_;      // udp 连接 接收数据
    int                         port_;     // udp 本类监听端口
    std::string                 ip_dst_;   // udp 机载主控模拟器ip
    int                         port_dst_; // udp 要发送到的端口

    std::mutex mtx_send_; // 发送锁

    /// @brief udp 发送函数
    /// @param topic_id   主题ID    (V_TOPIC_XXX_XXX)
    /// @param msg        数据指针
    /// @param msg_len    数据长度
    void udpSend(uint32_t topic_id, uint8_t *msg, uint32_t msg_len);

    // 队列
    ThreadSafeQueue<PtrUdpPacket> queue_act_req_;
    ThreadSafeQueue<PtrUdpPacket> queue_others_;

    // 线程运行状态
    std::atomic<bool> running_act_req_;
    std::atomic<bool> running_other_process_;
    std::atomic<bool> running_periodic_send_;
    std::atomic<bool> running_subsystem_timer_;

    std::thread thread_act_req_;         // 子线程2
    std::thread thread_other_process_;   // 子线程3
    std::thread thread_periodic_send_;   // 子线程4
    std::thread thread_subsystem_timer_; // 子线程5

    // 子线程1 handler : 接受数据 分类消息 放入队列
    void dataReceive(char *data, int size);
    // 子线程2 运行函数 : 处理act_req以及主流程控制
    void startActReq();
    // 子线程3 运行函数 : 其他消息处理
    void startOtherProcess();
    // 子线程4 运行函数 : 周期发送
    void startPeriodicSend();
    // 子线程5 运行函数 : 分系统计时器
    void startSubsystemTiming();

    // 超时时间 (子线程阻塞时间)
    std::chrono::milliseconds timeout = std::chrono::milliseconds(100);

    // 功能函数
    // 得到系统RTC TODO: How? 原来为fc函数
    uint64_t getSysRTC();
};

#endif // CAMERA_SIM_H
