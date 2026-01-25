
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <atomic>
#include <thread_safe_queue.hpp>
#include <udp_packet.h>

// thread safe queue
namespace sim {
// 模拟器标志位
extern std::atomic<bool> is_simulating;
// 消息队列
extern ThreadSafeQueue<PtrUdpPacket> queue_IRST_act_req; // 主控消息队列
extern ThreadSafeQueue<PtrUdpPacket> queue_others;       // 其他消息队列

extern int periodic_interval; // 周期性发送间隔 ms

// extern int init_time;         // 初始化时间 s

// extern uint32_t electrify_amount;

extern bool freeze_all_process; // 冻结使 主控流程和fpga仿真中的所有while循环中空跑

// 锁
extern std::mutex mutex_fpga;
extern std::mutex mutex_shm; // 共享内存锁
} // namespace sim

#endif // GLOBAL_VARS_H
