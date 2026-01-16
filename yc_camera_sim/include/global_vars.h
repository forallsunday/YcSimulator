
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <thread_safe_queue.hpp>
#include <udp_packet.h>

// thread safe queue
namespace sq {
extern ThreadSafeQueue<PtrUdpPacket> sq_IRST_act_req; // 主控消息队列
extern ThreadSafeQueue<PtrUdpPacket> sq_others;       // 其他消息队列
} // namespace sq

// periodic send
namespace ps {
extern int periodic_interval;
}

// 锁
extern std::mutex mutex_fpga;

extern bool speed_locate_timer_enabled;
#endif // GLOBAL_VARS_H
