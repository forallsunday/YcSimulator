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

#include <iostream>
#include <thread>

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
      isStartRecv_(false),
      dataHandlFunc_(std::move(dataFunc)),
      pSocketWrapper_(nullptr),
      socketWrapperHandle_(nullptr),
      socketWrapperHandle_send(nullptr) {
}

bool UdpConnect::Init() {
    bool bResult(false);
    this->pSocketWrapper_ = new SocketWrapper();
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

    isStartRecv_ = true;
    // 开启线程接收数据
    std::thread recvThread([&]() {
        char buf[2048] = {0};

        unsigned int farAddr = 0;
        unsigned short farPort = 0;
        int nResult = 0;

        struct epoll_event events[MAX_EVENTS];
        int epfd = epoll_create(MAX_EVENTS);
        if (epfd == -1) {
            printf("epoll create failed erro = %d\n", errno);
        }
        add_del_fd(epfd, (int)(long)(this->socketWrapperHandle_), 1);
        // printf("while num is %d\n", (int)(long)(this->socketWrapperHandle_));
        struct sockaddr_in udp_client_addr;
        memset(&udp_client_addr, 0, sizeof(udp_client_addr));
        socklen_t len = sizeof(udp_client_addr);

        while (isStartRecv_) {
            // int numEvents = epoll_wait(epfd, events, MAX_EVENTS, 0);
            // timeout 时间设置为10ms 即收到事件立即执行 不然就等待10ms
            int numEvents = epoll_wait(epfd, events, MAX_EVENTS, 10);
            if (numEvents == -1) {
                printf("epoll wait failed\n");
                break;
            }

            for (int i = 0; i < numEvents; i++) {
                int sockfd = events[i].data.fd;
                if (sockfd == (int)(long)(this->socketWrapperHandle_)) {
                    nResult = this->pSocketWrapper_->recvfrom(this->socketWrapperHandle_, buf, sizeof(buf), &farAddr, &farPort);

                    if (nResult >= 0) {
                        dataHandlFunc_(buf, sizeof(buf));
                    }
                }
                add_del_fd(epfd, (int)(long)(this->socketWrapperHandle_), 0);
                add_del_fd(epfd, (int)(long)(this->socketWrapperHandle_), 1);
            }

            // std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
    recvThread.detach();

    return true;
}

int UdpConnect::SendData(const char* buf, int data_len, const char* ip_dst, int port_dst) {
    if (this->socketWrapperHandle_send == nullptr) {
        return -1;
    }

    return this->pSocketWrapper_->sendto(socketWrapperHandle_send, buf, data_len, inet_addr(ip_dst), port_dst);
}

// 是否变成更安全的关闭方式
void UdpConnect::Close() {
    if (this->socketWrapperHandle_ == nullptr) {
        return;
    }
    isStartRecv_ = false;
    this->pSocketWrapper_->close(socketWrapperHandle_);
}

#if 0
#include <QNetworkDatagram>
UdpConnect::UdpConnect(std::string ip,int port,DataHandlFunc dataFunc):ip_(ip),port_(port),dataHandlFunc_(std::move(dataFunc))
{

}

bool UdpConnect::Init()
{
    bool bResult(false);

    this->pUdpSocket_ = new  QUdpSocket();
    QHostAddress  addr;
    addr.setAddress(ip_.c_str());
    if(! this->pUdpSocket_->bind(addr,port_))
    {
        return bResult;
    }

    connect(this->pUdpSocket_, &QUdpSocket::readyRead,
            this, &UdpConnect::readPendingDatagrams);


    return  bResult;
}

int UdpConnect::SendData(const char *buf, int bufLen, const char * destIp, int destPort)
{
    QHostAddress  addr;
    addr.setAddress(destIp);
    return  pUdpSocket_->writeDatagram(buf,bufLen,addr,destPort);
}

//接收函数
void UdpConnect::readPendingDatagrams()
{

    while (pUdpSocket_->hasPendingDatagrams()) {

        QNetworkDatagram datagram =  pUdpSocket_->receiveDatagram();

        processTheDatagram(datagram);
    }
}

void UdpConnect::processTheDatagram(QNetworkDatagram datagram)
{
    //解析数据
    char* buf =   datagram.data().data();
    int dataLen =   datagram.data().length();

    if(buf == nullptr || dataLen<1 ){
        return;
    }
    dataHandlFunc_(buf,dataLen);
}

void UdpConnect::Close()
{

}


//void Server::initSocket()
//{
//    udpSocket = new QUdpSocket(this);
//    udpSocket->bind(QHostAddress::LocalHost, 7755);

//    connect(udpSocket, &QUdpSocket::readyRead,
//            this, &Server::readPendingDatagrams);
//}

//void Server::readPendingDatagrams()
//{
//    while (udpSocket->hasPendingDatagrams()) {
//        QNetworkDatagram datagram = udpSocket->receiveDatagram();
//        processTheDatagram(datagram);
//    }
//}

#endif
