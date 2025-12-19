#include "udpconnect.h"

#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

// #include "logger_wrapper.h"
#define MAX_EVENTS 50

/*
 * @brief:设置fd为非阻塞
 * @params[in]:
 *	fd:文件描述符
 * @return:
 *    文件属性
 */
int setnonbloking(int fd) {
    int oldflags = fcntl(fd, F_GETFL);
    if (oldflags < 0) {
        printf("fcntl get faliled\n");

        return -1;
    }
    int newflags = oldflags | O_NONBLOCK;
    if (fcntl(fd, F_SETFL, newflags) < 0) {
        printf("fcntl set faliled\n");

        return -1;
    }
    return oldflags;
}

/*
 * @brief:添加或删除fd到epoll结构
 * @params[in]:
 *	epfd:创建的epoll描述符
 *	fd:文件描述符
 *	flag:判断是添加还是删除
 * @return:
 *    无
 */
void add_del_fd(int epfd, int fd, int flag) {
    struct epoll_event ev;
    ev.data.fd = fd;
    if (flag == 1) {
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
        setnonbloking(fd);
        assert(setnonbloking(fd) != -1);
    } else {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    }
}

UdpConnect::UdpConnect(std::string ip, int port, int port_send, DataHandlFunc dataFunc)
    : ip_(ip),
      port_(port),
      port_send(port_send),
      start_receive(false),
      dataHandlFunc_(std::move(dataFunc)),
      pSocketWrapper_(nullptr),
      socketWrapperHandle_(nullptr),
      socketWrapperHandle_send(nullptr) {
}

UdpConnect::~UdpConnect() {
    this->Close();
}

bool UdpConnect::Init() {
    bool bResult(false);
    this->pSocketWrapper_      = new SocketWrapper();
    this->socketWrapperHandle_ = this->pSocketWrapper_->socket(SOCKETWRAPPER_SOCK_DGRAM);
    if (nullptr == this->socketWrapperHandle_) {
        return bResult;
    }

    int nRes = this->pSocketWrapper_->bind(this->socketWrapperHandle_, inet_addr(ip_.c_str()), port_);
    if (nRes < 0) {
        printf("UDP Recv Bind Failed\n");
        return bResult;
    }

    this->socketWrapperHandle_send = this->pSocketWrapper_->socket(SOCKETWRAPPER_SOCK_DGRAM);
    if (nullptr == this->socketWrapperHandle_send) {
        printf("UDP Send Bind Failed\n");
        return bResult;
    }

    // nRes = this->pSocketWrapper_->bind(this->socketWrapperHandle_send, inet_addr(ip_.c_str()), port_send);
    // if (nRes < 0) {
    //     return bResult;
    // }

    // ✅ 若 port_send_ > 0，则绑定固定端口；否则不绑定（使用系统分配的随机端口）
    if (port_send > 0) {
        nRes = this->pSocketWrapper_->bind(this->socketWrapperHandle_send, inet_addr(ip_.c_str()), port_send);
        if (nRes < 0) {
            printf("UDP Send Bind Failed (port=%d)\n", port_send);
            return bResult;
        }
    } else {
        printf("UDP Send using system-assigned port (no bind)\n");
    }

    this->start_receive = true;

    epfd_ = epoll_create(MAX_EVENTS);
    if (epfd_ == -1) {
        printf("epoll create failed error = %d\n", errno);
        return false;
    }

    // 添加 fd once
    add_del_fd(epfd_, (int)(long)(this->socketWrapperHandle_), 1);

    // 启动成员线程（捕获 this 安全）
    recv_thread_ = std::thread([this]() {
        char           buf[2048];
        unsigned int   farAddr = 0;
        unsigned short farPort = 0;

        struct epoll_event events[MAX_EVENTS];

        while (this->start_receive) {
            int numEvents = epoll_wait(this->epfd_, events, MAX_EVENTS, 10);
            if (numEvents == -1) {
                if (errno == EINTR)
                    continue;
                printf("epoll wait failed\n");
                break;
            }

            for (int i = 0; i < numEvents; ++i) {
                int sockfd = events[i].data.fd;
                if (sockfd == (int)(long)(this->socketWrapperHandle_)) {
                    int nResult = this->pSocketWrapper_->recvfrom(
                        this->socketWrapperHandle_, buf, sizeof(buf), &farAddr, &farPort);

                    if (nResult > 0) {
                        // 传入实际接收长度
                        this->dataHandlFunc_(buf, nResult);
                    }
                }
            }
        }
    });

    return true;
}

int UdpConnect::SendData(const char *buf, size_t size, const char *ip_dst, int port_dst) {
    if (this->socketWrapperHandle_send == nullptr) {
        return -1;
    }

    return this->pSocketWrapper_->sendto(socketWrapperHandle_send, buf, size, inet_addr(ip_dst), port_dst);
}

void UdpConnect::Close() {
    // 1. 停止循环
    if (!start_receive)
        return;

    start_receive = false;

    // 2. 移除 epoll fd
    if (epfd_ != -1 && socketWrapperHandle_) {
        epoll_ctl(epfd_, EPOLL_CTL_DEL, (int)(long)socketWrapperHandle_, nullptr);
    }

    // 3. 关闭 recv socket
    if (socketWrapperHandle_) {
        pSocketWrapper_->close(socketWrapperHandle_);
        socketWrapperHandle_ = nullptr;
    }

    // 4. join recv thread
    if (recv_thread_.joinable())
        recv_thread_.join();

    // 5. 关闭 epoll fd
    if (epfd_ != -1) {
        close(epfd_);
        epfd_ = -1;
    }

    // 6. 关闭发送 socket
    if (socketWrapperHandle_send) {
        pSocketWrapper_->close(socketWrapperHandle_send);
        socketWrapperHandle_send = nullptr;
    }

    // 7. 释放 SocketWrapper
    if (pSocketWrapper_) {
        delete pSocketWrapper_;
        pSocketWrapper_ = nullptr;
    }

    printf("[UdpConnect] Closed\n");
}
