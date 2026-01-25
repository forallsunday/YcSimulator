// #include "CommInterface.h"
#include "model.h"

#include "cadi_shm.h"
#include "shm_interface.h"
#include "udpconnect.h"
#include "xml_api.h"
#include <camera_sim.h>
#include <read_udp_addr.hpp>

#include <sys/time.h>

#include <log_init.h>

enum status_enum /*状态集*/
{
    WAITTNG = 0,
    INIT    = 1,
    RUNNING = 2,
    FROZEN  = 3,
    STOP    = 4
};

// static void * pTSPI = NULL;
static int rtn           = -1;
static int module_status = 0;

SOCKET_PARSE socket_data;
/**********************************从此处开始修改*************************************/

// 首先使用xml配置工具依照idle配置xml文件，设置需要读取或写入的数据结构类型

/**********全局变量定义信息区域:Begin***********/
// 订阅
// 1.1.3.3 导 航 参数（HA）
// static NavigationDataHMsg g_stNavigationDataHMsg;
// 1.1.3.4 飞行导航状态参数（HA）
// static FlightNavigationStatusHMsg g_stFlightNavigationStatusHMsg;
// 1.1.3.2 设备供电状态参数
// static FacilitiesPowerSupplyStatusParasUDPMsg
// g_stFacilitiesPowerSupplyStatusParasUDPMsg; 1.1.4.28 空面目标装订参数 static
// SecAsWpnTgtMissionParasMsg g_stSecAsWpnTgtMissionParasMsg;

// 发布
// 功能单元状态
// static FunctionalUnitStatusMsg g_stFunctionalUnitStatusMsg;

// Note: 2025-10-28 LCY
// 共享内存输入输出
SharedMemoryInput  shm_input;
SharedMemoryOutput shm_output;
// 相机仿真模型
std::unique_ptr<CameraSimulator> cam_sim;

/**********全局变量定义信息区域:End***********/

/*
 * 函数名
 * usrmode_wait:模型链接之后的等待函数，需要发送模型的状态信息;
 * 函数说明
 * 仿真过程启动时，由中间件调用一次;
 */
int usrmode_wait() {
    log_info("!!!!!!!!正在进行usrmode_wait");
    /*****************************************************/
    /***需要修改模型名称'model.so'，与xml配置中的名称一致***/
    rtn = topic_init("YCSIM", "ModuleConfig.xml");
    printf("init rtn = %d\n", rtn);
    /*****************************************************/
    tcp_udp_parse_d("./ModuleConfig.xml", &socket_data);

    // 状态处理函数
    printf("usrmode_wait finished\n");

    return rtn;
}

// wait是等待任务平台连接 如果没连上 不会到init

/**
 * 函数名
 * usrmode_init :模型初始化函数;
 * 函数说明
 * 仿真过程进入初始化状态时，由中间件调用一次;
 * 函数参数
 * InitParam:模型初始化所用到的参数，当前为一个字符串需要解析;
 */
void usrmode_init() {
    // log_info("!!!!!!!!正在进行usrmode_init");

    module_status = status_enum::RUNNING;

    /* ************************************* */
    /* 1.从共享内存中获取初始化参数（如飞机高度、速度等），添加需要读取的变量，可忽略 */
    // topic_read("SecSimulatorControlMsg",&cmd,0);

    /* 2.判断创建的一些变量（如打开的动态库句柄、创建的线程等）是否为空，为空时才创建，防止重复创建，可忽略 */
    // if (xxx == NULL) {
    // }
    /* 3. 添加模型初始化逻辑 */

    /* ************************************* */
    //    printf("Usr_ModeInit data is NULL \n");

    // 初始化 log
    // log_init("camera_sim.log");
    log_init(nullptr);

    ReadUdpAddr rua;
    readUdpAddr(rua, socket_data);

    if (!cam_sim) {
        cam_sim = std::make_unique<CameraSimulator>(
            rua.port_cam_listen_ctrl, rua.ip_control, rua.port_ctrl_listen_cam);
    }

    cam_sim->init();
    // cam_sim->start();

    // 调试时设置周期发送间隔
    // cam_sim->setPeriodicInterval(2000);

    // Note: 测试直接执行拍照模式
    // cam_sim->testPhotoing();

    return;
}

/*
 * 函数名
 * step_calculate:模型运行时执行的单步函数;
 * 函数说明
 * 运行状态进入运行时，由中间件周期调用;
 */
void step_calculate() {
    // log_info("!!!!!!!!正在进行step_calculate");
    /***************************************************************************************************/
    /*
     * start
     * 填写
     * 打印订阅的消息是对模型收到数据的验证;
     * 发布消息的赋值是模拟模型的解算结果;
     */

    /* ************************************* */

    // 启动模型
    cam_sim->start();

    /* 1. 调用topic_read从共享内存中读取所需信息 */
    topic_read("FacilitiesPowerSupplyStatusParasMsg",
               &(shm_input.m_FacilitiesPowerSupplyStatusParasMsg), 0);
    topic_read("SecSimulatorControlMsg",
               &(shm_input.m_SecSimulatorControlMsg), 0);
    // topic_read("SecTgtPositionParaMsg",
    //            &(shm_input.m_SecTgtPositionParaMsg), 0);
    // 继续添加...

    /* 2. 添加模型单步运行逻辑 */
    cam_sim->step(&shm_input, &shm_output);

    /* 3. 调用topic_write将模型计算后的数据写回共享内存 */
    topic_write("FunctionalUnitStatusMsg",
                &(shm_output.m_FunctionalUnitStatusMsg), 0);
    topic_write("SecEOImageDriveMsg",
                &(shm_output.m_SecEOImageDriveMsg), 0);
    // 继续添加...

    /* ************************************* */

    return;
}

/*
 * 函数名
 * usrmode_freeze:模型冻结后执行的函数;
 * 函数说明
 * 运行状态进入冻结时，由中间件周期调用;
 */
void step_freeze() {
    /* ************************************* */
    /* 1. 添加模型暂停逻辑 */
    cam_sim->freeze();

    /* ************************************* */
    return;
}

/*
 * 函数名
 * usrmode_report:模型冻结后执行的函数;
 * 函数说明
 * 仿真过程启动后，由中间件周期调用;
 */
int  heartbit = 0;
void usrmode_report() {
    // 模型健康心跳字自增

    // 模型调用共享内存接口，将健康状态消息写入共享内存

    heartbit++;
    // 模型健康心跳字自增
    // 模型调用共享内存接口，将健康状态消息写入共享内存
}

/*
 * 函数名
 * usrmode_close: 模型关闭打开的资源;
 * 函数说明
 * 仿真过程结束时，由中间件周期调用;
 */
void usrmode_close() {
    module_status = 1;
    // g_stFunctionalUnitStatusMsg.St_UnitStatusData.U1_MemberStatus = 1;

    /* ************************************* */
    /* 1. 添加模型停止逻辑, 关闭打开的资源 */
    if (cam_sim) {
        cam_sim->close();
        cam_sim.reset();
    }

    /* ************************************* */

    printf("module stop !!\n");
    return;
}
