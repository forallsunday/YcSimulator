#include <global_vars.h>

// thread safe queue
namespace sq {
extern ThreadSafeQueue<PtrUdpPacket> sq_IRST_act_req; // 主控消息队列
extern ThreadSafeQueue<PtrUdpPacket> sq_others;       // 其他消息队列
} // namespace sq