#include "SocketWrapper.h"

#if defined(_WIN32)
#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

/* ================= 工具宏 ================= */

#if defined(_WIN32)
using socket_fd_t = SOCKET;
#define CLOSE_SOCKET closesocket
#else
using socket_fd_t = int;
#define CLOSE_SOCKET close
#endif

/* ================= 构造 / 析构 ================= */

SocketWrapper::SocketWrapper() {
#if defined(_WIN32)
    m_SocketType = Win32Socket;
#else
    m_SocketType = LinuxSocket;
#endif

#if defined(_WIN32)
    // Winsock 全局初始化（只做一次）
    static bool wsaInited = false;
    if (!wsaInited) {
        WSADATA wsd;
        WSAStartup(MAKEWORD(2, 2), &wsd);
        wsaInited = true;
    }
#endif
}

SocketWrapper::SocketWrapper(e_Platform_SocketType socketType)
    : m_SocketType(socketType) {
#if defined(_WIN32)
    static bool wsaInited = false;
    if (!wsaInited) {
        WSADATA wsd;
        WSAStartup(MAKEWORD(2, 2), &wsd);
        wsaInited = true;
    }
#endif
}

SocketWrapper::~SocketWrapper() {
    // 不在析构中 WSACleanup（避免多实例问题）
}

/* ================= socket ================= */

SocketWrapperHandle SocketWrapper::socket(int type) {
    int sockType = (type == SOCKETWRAPPER_SOCK_STREAM) ? SOCK_STREAM : SOCK_DGRAM;

    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
        return (SocketWrapperHandle)::socket(AF_INET, sockType, 0);
#else
        return nullptr;
#endif

    case LinuxSocket:
#if defined(__linux__)
        return (SocketWrapperHandle)(long)::socket(AF_INET, sockType, 0);
#else
        return nullptr;
#endif

    default:
        return nullptr;
    }
}

/* ================= close ================= */

int SocketWrapper::close(SocketWrapperHandle s) {
    if (!s)
        return -1;

    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
        return CLOSE_SOCKET((socket_fd_t)s);
#else
        return -1;
#endif

    case LinuxSocket:
#ifdef __GNUC__
        // LCY 修改为此 避免 析构后无法重新绑定相同的端口
        return ::close((int)(long)s);
        // return ::shutdown((int)(long)s, 2);
#else
        return -1;
#endif

    default:
        return -1;
    }
}

/* ================= bind ================= */

int SocketWrapper::bind(SocketWrapperHandle s, unsigned int ip, unsigned short port) {
    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = ip;

    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
        return ::bind((socket_fd_t)s, (sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif

    case LinuxSocket:
#if defined(__linux__)
        return ::bind((int)(long)s, (sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif

    default:
        return -1;
    }
}

/* ================= connect ================= */

int SocketWrapper::connect(SocketWrapperHandle s, unsigned int ip, unsigned short port) {
    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = ip;

    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
        return ::connect((socket_fd_t)s, (sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif

    case LinuxSocket:
#if defined(__linux__)
        return ::connect((int)(long)s, (sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif

    default:
        return -1;
    }
}

/* ================= listen ================= */

int SocketWrapper::listen(SocketWrapperHandle s, int backlog) {
    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
        return ::listen((socket_fd_t)s, backlog);
#else
        return -1;
#endif

    case LinuxSocket:
#if defined(__linux__)
        return ::listen((int)(long)s, backlog);
#else
        return -1;
#endif

    default:
        return -1;
    }
}

/* ================= accept ================= */

SocketWrapperHandle SocketWrapper::accept(
    SocketWrapperHandle s,
    unsigned int       *farAddr,
    unsigned short     *farPort) {
    sockaddr_in addr{};
#if defined(_WIN32)
    int addrLen = sizeof(addr);
#else
    socklen_t addrLen = sizeof(addr);
#endif

    switch (m_SocketType) {
    case Win32Socket:
#if defined(_WIN32)
    {
        SOCKET fd = ::accept((socket_fd_t)s, (sockaddr *)&addr, &addrLen);
        if (fd == INVALID_SOCKET)
            return nullptr;
        if (farAddr)
            *farAddr = addr.sin_addr.S_un.S_addr;
        if (farPort)
            *farPort = ntohs(addr.sin_port);
        return (SocketWrapperHandle)fd;
    }
#else
        return nullptr;
#endif

    case LinuxSocket:
#if defined(__linux__)
    {
        int fd = ::accept((int)(long)s, (sockaddr *)&addr, &addrLen);
        if (fd < 0)
            return nullptr;
        if (farAddr)
            *farAddr = addr.sin_addr.s_addr;
        if (farPort)
            *farPort = ntohs(addr.sin_port);
        return (SocketWrapperHandle)(long)fd;
    }
#else
        return nullptr;
#endif

    default:
        return nullptr;
    }
}

/* ================= recv / send ================= */

int SocketWrapper::recv(SocketWrapperHandle s, char *buf, size_t len) {
#if defined(_WIN32)
    return ::recv((socket_fd_t)s, buf, (int)len, 0);
#elif defined(__linux__)
    return ::recv((int)(long)s, buf, len, 0);
#else
    return -1;
#endif
}

int SocketWrapper::send(SocketWrapperHandle s, const char *buf, size_t len) {
#if defined(_WIN32)
    return ::send((socket_fd_t)s, buf, (int)len, 0);
#elif defined(__linux__)
    return ::send((int)(long)s, buf, len, 0);
#else
    return -1;
#endif
}

/* ================= recvfrom / sendto ================= */

int SocketWrapper::recvfrom(
    SocketWrapperHandle s,
    char               *buf,
    size_t              len,
    unsigned int       *farAddr,
    unsigned short     *farPort) {
    sockaddr_in addr{};
#if defined(_WIN32)
    int addrLen = sizeof(addr);
#else
    socklen_t addrLen = sizeof(addr);
#endif

#if defined(_WIN32)
    int ret = ::recvfrom((socket_fd_t)s, buf, (int)len, 0, (sockaddr *)&addr, &addrLen);
    if (ret >= 0) {
        if (farAddr)
            *farAddr = addr.sin_addr.S_un.S_addr;
        if (farPort)
            *farPort = ntohs(addr.sin_port);
    }
    return ret;
#elif defined(__linux__)
    int ret = ::recvfrom((int)(long)s, buf, len, 0, (sockaddr *)&addr, &addrLen);
    if (ret >= 0) {
        if (farAddr)
            *farAddr = addr.sin_addr.s_addr;
        if (farPort)
            *farPort = ntohs(addr.sin_port);
    }
    return ret;
#else
    return -1;
#endif
}

int SocketWrapper::sendto(
    SocketWrapperHandle s,
    const char         *buf,
    size_t              len,
    unsigned int        farAddr,
    unsigned short      farPort) {
    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = farAddr;
    addr.sin_port        = htons(farPort);

#if defined(_WIN32)
    return ::sendto((socket_fd_t)s, buf, (int)len, 0, (sockaddr *)&addr, sizeof(addr));
#elif defined(__linux__)
    return ::sendto((int)(long)s, buf, len, 0, (sockaddr *)&addr, sizeof(addr));
#else
    return -1;
#endif
}

/* ================= setsockopt ================= */

int SocketWrapper::setsockopt(
    SocketWrapperHandle s,
    int                 level,
    int                 optname,
    void               *optval,
    int                *optlen) {
#if defined(_WIN32)
    return ::setsockopt((socket_fd_t)s, level, optname,
                        (const char *)optval, optlen ? *optlen : 0);
#elif defined(__linux__)
    return ::setsockopt((int)(long)s, level, optname, optval,
                        optlen ? (socklen_t)*optlen : 0);
#else
    return -1;
#endif
}
