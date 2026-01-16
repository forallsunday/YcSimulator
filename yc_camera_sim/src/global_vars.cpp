// 在原机载代码基础上新增的一些全局变量
#include <global_vars.h>

#include <mutex>

// thread safe queue
namespace sq {
ThreadSafeQueue<PtrUdpPacket> sq_IRST_act_req; // 主控消息队列
ThreadSafeQueue<PtrUdpPacket> sq_others;       // 其他消息队列
} // namespace sq

// periodic send
namespace ps {
int periodic_interval;
}

// 锁
std::mutex mutex_fpga;