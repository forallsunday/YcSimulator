#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "CommInterface.h"

using namespace std;

//处理发送心跳的类
class HeartBeat
{
public:
	explicit HeartBeat(chrono::milliseconds inTime);
	
	~HeartBeat();
	
	void Start();
	
	void Stop();
	
private:
	void Send();
	
private:
	//多久发一次，单位ms
	chrono::milliseconds m_secInterval;
	//
	atomic<bool> m_stopFlag;
	//线程锁
	mutex m_mTex;
	//
	condition_variable m_conVar;
	//线程
	thread m_threadWorker;
	
	//udp报文头
	NET_DATA_PACKET_TYPE m_stUdpHeader;
	
};

