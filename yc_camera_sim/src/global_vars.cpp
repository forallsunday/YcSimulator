// 在原机载代码基础上新增的一些全局变量

#include <global_vars.h>

#include <yc/YC_Controller_Constant_Define.h>

#include <mutex>

namespace sim {
// 模拟器标志位
std::atomic<bool> is_simulating{false};
// thread safe queue
ThreadSafeQueue<PtrUdpPacket> queue_IRST_act_req; // 主控消息队列
ThreadSafeQueue<PtrUdpPacket> queue_others;       // 其他消息队列
// periodic send
int periodic_interval = PERIOD_TASK_TIME; // 周期性发送间隔 ms

int init_time = 30; // 初始化时间 s

// 上电次数
uint32_t electrify_amount = 0;

bool freeze_all_process = false;

// 锁
std::mutex mutex_fpga;
std::mutex mutex_shm; // 共享内存锁
} // namespace sim
