
**更新日期：2025-10-28**

## 定义概念

### UDP
- 可使用由611提供的接口
```cpp 
  // 参数：ip地址、端口、发送端口、数据接收函数的句柄，
  UdpConnect udp_connect("153.15.2.21", 10086, 3888, &data_receive_handle);
```
- 该类内部是开一个子线程持续进行接收
- 发送接口如下：
```cpp
    // 参数：数据缓冲区，数据长度，目标ip，目标端口
    // 本机向任意ip发送时，固定使用构造函数中的发送端口
    int SendData(const char* buf, int data_len, const char* ip_dst, int port_dst);
```
- 在调试阶段，udp地址暂时需手动指定。我们在`yc_udp_config.xml`中定义，由`yc_udp_xml_api.hpp`中的函数解析。

### ICP：理解为地面站软件
- 相当于模拟载机，与我们收发消息
- ICP server 有一个ip地址和端口，我们建立UDP从其接收数据
- 每一个功能节点(即`V_NODE_XXX`)都有一个对应的ip地址和端口，发送消息时，需根据该节点发送到对应的ip地址和端口。
- UDPNodeConfig.xml文件中包括ICP所有的ip端口
- ModuleConfig.xml文件从UDPNodeConfig.xml取所用ip端口。但没有主控模拟器和相机仿真器的ip端口。

### YcControl：可执行文件 - 机载主控模拟器
- docker2 中 独立运行
- 功能：ICP 和 相机仿真模型 中间 透传
- 功能实现代码：在control_sim.h中定义 class `ControlSimulator`

### libycSim.so：库文件 - 相机仿真模型
- docker1 中 由611中间件midware(一个可执行文件)调用
- 功能：与机载主控模拟器udp通信功能、共享内存读写功能、相机仿真功能。
- 中间件调用命令：`./midware  –mod 动态库名称 –rate 模型运行周期（单位：ms）` 。例如：`./midware  –mod libycSim.so –rate 10`
- 功能实现代码：在camera_sim.h中定义 class `CameraSimulator`
- 对外接口在 **`model.h`**
  - **`model.h`**：头文件
  - 说明：611提供的模型模板，库的运行模式，运行流程主要执行以下接口：
    - `user_wait` : 从ModuleConfig.xml文件中解析共享内存定义和ICP的若干ip端口
    - `usrmode_init` : 初始化模型，即我们写的`CameraSimulator`
    - `step_calculate` : 周期计算(对应midware命令-rate)，过程为：读取共享内存`topic_read`、计算结果、写入共享内存`topic_write`
    - `usrmode_close` : 关闭模型



## 类的设计

### `ControlSimulator`
- 功能：透传
- 定义：UdpAddress`结构体 包含ip和端口
- 类内变量：
  - 存储icp不同节点的icp和端口 `std::map<std::string, UdpAddress>` icp_map
- 说明: 
  - 初始化：建立与ICP的UDP连接`udp_icp`接收数据、建立与相机仿真的UDP连接`udp_camera`接收数据
  - 共有2个子线程(一个UDP是一个子线程)
  - `udp_icp`中所有UDP在接收后立刻发送给相机仿真
  - `udp_camera`在接收后需对消息分类，再通过查找icp_map中对应的节点，发送给到指定ip和端口

### `CameraSimulator`
- 功能: 负责相机仿真
- 类内变量：
  1. 所有接收消息对应的结构体
  2. 所有发送消息对应的结构体
  3. 共享内存输入输出的结构体
  4. 仿真计算参数
  5. 仿真计算结果
  6. 队列act_req
  7. 队列others
  8. 心跳数heartbit 
- 说明: 设置5个子线程
  - 初始化：建立与机载主控模拟器的UDP连接
  - 子线程1：接收消息并分类，将act_req和others消息放入对应队列中。
  - 子线程2：处理队列act_req(但无分系统通信)，发送消息。
  - 子线程3：处理队列others，发送消息。
  - 子线程4：定时器周期间隔5ms，更新并发送消息(发送内容: 状态、LOS、载荷IMU等)
  - 子线程5：分系统定时器，周期根据图像帧频。在相关发送消息中更新伺服数据，用来替代分系统回应。
  - 主线程：
    1. 仿真的输入通过 `set`设置相关类内变量(共享内存结构体相关输入)
    2. 解析接收icd和共享内存输入，更新相关类内变量(仿真计算参数)
    3. 计算，更新相关类内变量(仿真计算结果)
    4. 仿真的输出通过 `get`获取相关类内变量(共享内存结构体相关输出)

## 问题
1. 与611确认 共享内存与UDP中存在相同的参数，如载机位置，来源于哪个？
答：它们相同时刻应该是一样的。共享内存会快一些，UDP会有传输的时间。

2. UDP接收中有拍照指令时，是否需要计算，这与共享内存计算是否冲突？
答：UDP仍然计算。
