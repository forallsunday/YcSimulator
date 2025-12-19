#pragma once
#include <string>

#define SOCKETWRAPPER_IPPROTO_IP 0
#define SOCKETWRAPPER_IP_TOS 1

#define SOCKETWRAPPER_SOCK_STREAM 1
#define SOCKETWRAPPER_SOCK_DGRAM 2

typedef void *SocketWrapperHandle;

enum e_Platform_SocketType {
    Win32Socket,
    LinuxSocket,
    TSNSocket,
    SocketCount,
};

class SocketWrapper {
  public:
    SocketWrapper(e_Platform_SocketType socketType = e_Platform_SocketType::LinuxSocket);
    ~SocketWrapper();

    SocketWrapperHandle socket(int type);

    int close(SocketWrapperHandle s);
    int bind(SocketWrapperHandle s, unsigned int ip, unsigned short port);
    int connect(SocketWrapperHandle s, unsigned int ip, unsigned short port);
    int listen(SocketWrapperHandle s, int backlog);

    SocketWrapperHandle accept(SocketWrapperHandle s, unsigned int *farAddr, unsigned short *farPort);

    int recv(SocketWrapperHandle s, char *buf, size_t len);
    int send(SocketWrapperHandle s, const char *buf, size_t len);
    int recvfrom(SocketWrapperHandle s, char *buf, size_t len, unsigned int *farAddr, unsigned short *farPort);
    int sendto(SocketWrapperHandle s, const char *buf, size_t len, unsigned int farAddr, unsigned short farPort);
    int setsockopt(SocketWrapperHandle s, int level, int optname, void *optval, int *optlen);

  private:
    e_Platform_SocketType m_SocketType;
};
