#include "SocketWrapper.h"
// #include "Tsn_Api.h"

#ifdef _MSC_VER
#include <WS2tcpip.h>
#include <WinSock2.h>
#endif

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef _MSC_VER
#ifdef FWW_MEMLEAK_CHECK
#include "../MemLeakCheck/MemLeakCheck.h"
#endif
#endif

#ifdef __GNUC__
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

SocketWrapper::SocketWrapper(e_Platform_SocketType socketType) : m_SocketType(socketType) {
}

SocketWrapper::~SocketWrapper() {
}

SocketWrapperHandle SocketWrapper::socket(int type) {
    int sockType = type == SOCKETWRAPPER_SOCK_STREAM ? SOCK_STREAM : SOCK_DGRAM;
    switch (m_SocketType) {
    case Win32Socket: {
#ifdef _MSC_VER
        WSADATA wsd;
        WSAStartup(MAKEWORD(2, 2), &wsd);
        return (SocketWrapperHandle)::socket(AF_INET, sockType, 0);
#else
        return nullptr;
#endif
    }
    case LinuxSocket:
#ifdef __GNUC__
        return (SocketWrapperHandle)::socket(AF_INET, sockType, 0);
#else
        return nullptr;
#endif
    case TSNSocket:
        //    {
        //        int ret = tsnSocket(AF_INET, sockType, 0);
        //        if(ret > 0)
        //        {
        //            return (SocketWrapperHandle)ret;
        //        }
        //        else
        //        {
        //            return nullptr;
        //        }
        //    }
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return nullptr;
}

int SocketWrapper::close(SocketWrapperHandle s) {
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::closesocket((SOCKET)s);
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
    case TSNSocket:
        //        return tsnClose((int)(long)s);
        break;
    case SocketCount:
        break;
    default:
        break;
    }

    return 0;
}

int SocketWrapper::bind(SocketWrapperHandle s, unsigned int ip, unsigned short port) {
    sockaddr_in localAddr;
    localAddr.sin_family      = AF_INET;
    localAddr.sin_port        = htons(port);
    localAddr.sin_addr.s_addr = INADDR_ANY;
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::bind((SOCKET)s, (const struct sockaddr *)&localAddr, sizeof(localAddr));
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::bind((int)(long)s, (const struct sockaddr *)&localAddr, sizeof(localAddr));
#else
        return -1;
#endif
    case TSNSocket:
        //        return tsnBind((int)(long)s, (const struct tsnSockaddr*)&localAddr, sizeof(localAddr));
        break;
    case SocketCount:
        break;
    default:
        break;
    }

    return 0;
}

int SocketWrapper::connect(SocketWrapperHandle s, unsigned int ip, unsigned short port) {
    sockaddr_in farAddr;
    farAddr.sin_family      = AF_INET;
    farAddr.sin_port        = htons(port);
    farAddr.sin_addr.s_addr = ip;
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::connect((SOCKET)s, (const struct sockaddr *)&farAddr, sizeof(farAddr));
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::connect((int)(long)s, (const struct sockaddr *)&farAddr, sizeof(farAddr));
#else
        return -1;
#endif
    case TSNSocket:
        //        return tsnConnect((int)(long)s, (const struct tsnSockaddr*)&farAddr, sizeof(farAddr));
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::listen(SocketWrapperHandle s, int backlog) {
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::listen((SOCKET)s, backlog);
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::listen((int)(long)s, backlog);
#else
        return -1;
#endif
    case TSNSocket:
        //        return tsnListen((int)(long)s, backlog);
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

SocketWrapperHandle SocketWrapper::accept(SocketWrapperHandle s, unsigned int *farAddr, unsigned short *farPort) {
    sockaddr_in addr;
    int         addrLen = sizeof(addr);
    switch (m_SocketType) {
    case Win32Socket: {
#ifdef _MSC_VER
        SOCKET socket = ::accept((SOCKET)s, (struct sockaddr *)&addr, &addrLen);
        if (socket == INVALID_SOCKET) {
            return nullptr;
        }
        *farAddr = addr.sin_addr.S_un.S_addr;
        *farPort = htons(addr.sin_port);
        return (SocketWrapperHandle)socket;
#else
        return nullptr;
#endif
    }
    case LinuxSocket:
#ifdef __GNUC__
    {
        int socket = ::accept((int)(long)s, (struct sockaddr *)&addr, (unsigned int *)&addrLen);
        if (socket == -1) {
            return nullptr;
        }
        *farAddr = addr.sin_addr.s_addr;
        *farPort = htons(addr.sin_port);
        return (void *)(long)socket;
    }
#else
#endif
    case TSNSocket:
        //	{
        //            int socket = tsnAccept((int)(long)s, (struct tsnSockaddr*)&addr, &addrLen);
        //			if (socket == -1)
        //			{
        //				return nullptr;
        //			}
        //			*farAddr = addr.sin_addr.s_addr;
        //			*farPort = htons(addr.sin_port);
        //			return (SocketWrapperHandle)socket;
        //	}
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::recv(SocketWrapperHandle s, char *buf, int len) {
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::recv((SOCKET)s, buf, len, 0);
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::recv((int)(long)s, buf, len, 0);
#else
        return -1;
#endif
    case TSNSocket:
        //        return tsnRecv((int)(long)s, buf, len);
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::send(SocketWrapperHandle s, const char *buf, int len) {
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::send((SOCKET)s, buf, len, 0);
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::send((int)(long)s, buf, len, 0);
#else
        return -1;
#endif
    case TSNSocket:
        //        return tsnSend((int)(long)s, buf, len);
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::recvfrom(SocketWrapperHandle s, char *buf, int len, unsigned int *farAddr, unsigned short *farPort) {
    sockaddr_in addr;
    int         addrLen = sizeof(addr);
    int         ret;
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        ret      = ::recvfrom((SOCKET)s, buf, len, 0, (struct sockaddr *)&addr, &addrLen);
        *farAddr = addr.sin_addr.S_un.S_addr;
        *farPort = htons(addr.sin_port);
        return ret;
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        ret      = ::recvfrom((int)(long)s, buf, len, 0, (struct sockaddr *)&addr, (unsigned int *)&addrLen);
        *farAddr = addr.sin_addr.s_addr;
        *farPort = htons(addr.sin_port);
        // 接收到数据

        return ret;
#else
        return -1;
#endif
    case TSNSocket:
        //        ret = tsnRecvFrom((int)(long)s, buf, len, (struct tsnSockaddr*)&addr, addrLen);
        //		*farAddr = addr.sin_addr.s_addr;
        //		*farPort = htons(addr.sin_port);
        //		return ret;
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::sendto(SocketWrapperHandle s, const char *buf, int len, unsigned int farAddr, unsigned short farPort) {
    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = farAddr;
    addr.sin_port        = htons(farPort);
    switch (m_SocketType) {
    case Win32Socket:
#ifdef _MSC_VER
        return ::sendto((SOCKET)s, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif
    case LinuxSocket:
#ifdef __GNUC__
        return ::sendto((int)(long)s, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
#else
        return -1;
#endif
    case TSNSocket:
        //        return ::tsnSendto((int)(long)s, buf, len, (struct tsnSockaddr*)&addr, sizeof(addr));
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}

int SocketWrapper::setsockopt(SocketWrapperHandle s, int level, int optname, void *optval, int *optlen) {
    switch (m_SocketType) {
    case Win32Socket:
        return 0;
    case LinuxSocket:
        return 0;
        // return ::setsockopt((int)(long)s, level, optname, optval, (socklen_t)*optlen);
    case TSNSocket:
        //        return ::tsnSetOption((int)(long)s, level, optname, optval, optlen);
        break;
    case SocketCount:
        break;
    default:
        break;
    }
    return 0;
}
