#pragma once

#include <cstddef>

/* Socket 句柄类型 */
#if defined(_WIN32)
#include <WinSock2.h>
using SocketWrapperHandle = void *; // 统一用 void* 包一层
#else
using SocketWrapperHandle = void *;
#endif

/* 平台类型 */
enum e_Platform_SocketType {
    Win32Socket = 0,
    LinuxSocket,
    TSNSocket,
    SocketCount
};

/* socket 类型 */
#define SOCKETWRAPPER_SOCK_STREAM 1
#define SOCKETWRAPPER_SOCK_DGRAM 2

class SocketWrapper {
  public:
    SocketWrapper(); // 自动判断平台
    explicit SocketWrapper(e_Platform_SocketType socketType);
    ~SocketWrapper();

    SocketWrapperHandle socket(int type);
    int                 close(SocketWrapperHandle s);

    int bind(SocketWrapperHandle s, unsigned int ip, unsigned short port);
    int connect(SocketWrapperHandle s, unsigned int ip, unsigned short port);
    int listen(SocketWrapperHandle s, int backlog);

    SocketWrapperHandle accept(
        SocketWrapperHandle s,
        unsigned int       *farAddr,
        unsigned short     *farPort);

    int recv(SocketWrapperHandle s, char *buf, size_t len);
    int send(SocketWrapperHandle s, const char *buf, size_t len);

    int recvfrom(
        SocketWrapperHandle s,
        char               *buf,
        size_t              len,
        unsigned int       *farAddr,
        unsigned short     *farPort);

    int sendto(
        SocketWrapperHandle s,
        const char         *buf,
        size_t              len,
        unsigned int        farAddr,
        unsigned short      farPort);

    int setsockopt(
        SocketWrapperHandle s,
        int                 level,
        int                 optname,
        void               *optval,
        int                *optlen);

  private:
    e_Platform_SocketType m_SocketType;
};
