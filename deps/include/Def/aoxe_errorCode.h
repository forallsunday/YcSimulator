/* 总线通用返回值  */
/* 总线通用返回值 */
#define AOXE_BUS_SUCC                             (0)

#define AOXE_BUS_ADDR_RESOLVE_FAIL                (0xeeeeeeee)   //addressresolve失败

#define AOXE_BUS_ERR_CODE_BASE                    (-1000)       

#define AOXE_BUS_DEV_HANDLE_ERR                   (AOXE_BUS_ERR_CODE_BASE - 1)                   // 设备IO句柄错误
#define AOXE_BUS_IN_PARAM_ERR                     (AOXE_BUS_ERR_CODE_BASE - 2)                   // 输入参数错误
#define AOXE_BUS_OUT_PARAM_ERR                    (AOXE_BUS_ERR_CODE_BASE - 3)                   // 输出参数错误 
#define AOXE_BUS_DEV_ID_ERR                       (AOXE_BUS_ERR_CODE_BASE - 4)                   // 设备ID错误
#define AOXE_BUS_INIT_ERR                         (AOXE_BUS_ERR_CODE_BASE - 5)					 // 总线服务初始化错误
#define AOXE_BUS_DEV_SET_CMD_ERR                  (AOXE_BUS_ERR_CODE_BASE - 6)					 // 总线参数设置命令错误
#define AOXE_BUS_DEV_GET_CMD_ERR                  (AOXE_BUS_ERR_CODE_BASE - 7)					 // 总线参数获取命令错误
#define AOXE_BUS_MSG_LEN_OVERSIZE_ERR		      (AOXE_BUS_ERR_CODE_BASE - 8)					 // 消息长度超限错误
#define AOXE_BUS_MSG_LEN_ZERO_ERR				  (AOXE_BUS_ERR_CODE_BASE - 9)					 // 消息长度为0错误
#define AOXE_BUS_CALLBACK_FUN_REGS_ERR			  (AOXE_BUS_ERR_CODE_BASE - 10)					 // 总线服务回调函数注册错误 
#define AOXE_BUS_PAYLOAD_NULL_ERR			      (AOXE_BUS_ERR_CODE_BASE - 11)					 // 总线负载为空 
#define AOXE_BUS_NODE_ID_ERR			      	  (AOXE_BUS_ERR_CODE_BASE - 12)					 // 节点ID错误 
#define AOXE_BUS_NULL_INSTANCE_ERR			      (AOXE_BUS_ERR_CODE_BASE - 13)					 // 总线对象为空错误 
#define AOXE_BUS_SEND_ERR			     		  (AOXE_BUS_ERR_CODE_BASE - 14)					 // 发送消息错误 
#define AOXE_BUS_READ_ERR			     		  (AOXE_BUS_ERR_CODE_BASE - 15)					 // 收取消息错误 
#define AOXE_BUS_TOPIC_NUM_ZERO_ERR			      (AOXE_BUS_ERR_CODE_BASE - 16)					 // 消息数量为0错误 
#define AOXE_BUS_NO_MSG			      			  (AOXE_BUS_ERR_CODE_BASE - 17)					 // 未接收到消息     
#define AOXE_BUS_BUFF_TOO_SMALL_ERR		      	  (AOXE_BUS_ERR_CODE_BASE - 18)					 // buffer太小错误     
#define AOXE_BUS_LOCAL_DEV_OFFLINE_ERR		      (AOXE_BUS_ERR_CODE_BASE - 19)					 //本地设备未上网错误     
#define AOXE_BUS_MSGHEAD_CPY_ERR		          (AOXE_BUS_ERR_CODE_BASE - 20)					 //包头拷贝错误     
#define AOXE_BUS_SUBCLASS_NO_REALIZE		 	  (AOXE_BUS_ERR_CODE_BASE - 21)					 //子类未实现该父类函数(aoxe_ioserv)
#define AOXE_BUS_CFG_NOT_AVAILABLE				  (AOXE_BUS_ERR_CODE_BASE - 22)					 //NETXXConfig中没配置该总线上网
#define AOXE_BUS_BROADCAST_NOT_SUPPORTED	      (AOXE_BUS_ERR_CODE_BASE - 23)					 // 该总线不支持广播
#define AOXE_BUS_BOX_NUM_OVERSIZE_ERR		      (AOXE_BUS_ERR_CODE_BASE - 24)
#define AOXE_BUS_NO_CURRENT_BUS				      (AOXE_BUS_ERR_CODE_BASE - 25)					 // 当前总线无子卡初始化
#define AOXE_BUS_NO_CURRENT_BOX_ID_INSTANCE		  (AOXE_BUS_ERR_CODE_BASE - 26)		             // 无当前总线的子卡对象
#define AOXE_BUS_INVALID_BOX_ID					  (AOXE_BUS_ERR_CODE_BASE - 27)		             // 当前子卡ID错误
#define AOXE_BUS_INVALID_TOPIC_ID_FOR_CURRENT_BOX (AOXE_BUS_ERR_CODE_BASE - 28)		             // 当前主题不应该由当前子卡发送,发送失败.
#define AOXE_BUS_PERMISSION_DENIED				  (AOXE_BUS_ERR_CODE_BASE - 29)		             // 当前无权限(非GPIO上的节点无法获取日历芯片时间)
#define AOXE_BUS_PN_CREATE_PORT_FAILED			  (AOXE_BUS_ERR_CODE_BASE - 30)		             // 分区网络创建端口失败
#define AOXE_BUS_PN_STRM_INIT_FAILED			  (AOXE_BUS_ERR_CODE_BASE - 31)		             // 分区网络初始化流失败
#define AOXE_BUS_NO_SPECIFIC_CARD_ERR			  (AOXE_BUS_ERR_CODE_BASE - 32)					 //未指定子卡错误
#define AOXE_BUS_NO_PERMISSION_ERR				  (AOXE_BUS_ERR_CODE_BASE - 33)					 //无权限操作
#define AOXE_BUS_ROLE_ERR						  (AOXE_BUS_ERR_CODE_BASE - 34)					 // 角色错误，不进当前分支
#define AOXE_BUS_BM_MSG_EMPTY_ERR				  (AOXE_BUS_ERR_CODE_BASE - 35)
#define AOXE_BUS_RCV_BUF_EMPTY_ERR				  (AOXE_BUS_ERR_CODE_BASE - 36)     			 //接收缓冲区为空，退出
#define AOXE_BUS_OFFLINE_ERR					  (AOXE_BUS_ERR_CODE_BASE - 37)					 //为下线状态
#define AOXE_BUS_DRIVER_VERSION_ERR				  (AOXE_BUS_ERR_CODE_BASE - 38)					 //获取驱动版本错误
#define AOXE_BUS_BACK_UP_TIME_SOURCE			  (AOXE_BUS_ERR_CODE_BASE - 39)					 //作为备份时钟源
#define AOXE_BUS_TASK_CFG_ERR  			 		  (AOXE_BUS_ERR_CODE_BASE - 40)					 //创建总线任务时未找到任务配置错误
#define AOXE_BUS_MSG_FILTERED					  (AOXE_BUS_ERR_CODE_BASE - 41)					 //收到的消息由于bitmap无本设备而被过滤
#define AOXE_BUS_FACE_ERR						  (AOXE_BUS_ERR_CODE_BASE - 42)					 //收/发消息返回FACE错误(因为face层返回值为正，与目前判断收/发成功(>0)逻辑相悖，因此统一由该错误码表示）
#define AOXE_BUS_ADDR_ERR						  (AOXE_BUS_ERR_CODE_BASE - 43)					 //端口地址错误
#define AOXE_BUS_CHV_ERR						  (AOXE_BUS_ERR_CODE_BASE - 44)                  //通道无效


/* 路由返回值  */
#define AOXE_ROUTER_SUCC                             (0)

#define AOXE_ROUTER_ERR_CODE_BASE                    (-1500)
#define AOXE_ROUTER_TOPIC_NET_ERR                 (AOXE_ROUTER_ERR_CODE_BASE - 1)					 // 路由查询TOPIC对应的总线错误
#define AOXE_ROUTER_TOPIC_ERR                     (AOXE_ROUTER_ERR_CODE_BASE - 2)					 // 路由接收的TOPICID有错(为0)
#define AOXE_ROUTER_NODE_OFFLINE                 (AOXE_ROUTER_ERR_CODE_BASE - 3)	                 // 未找到路由表项
#define AOXE_ROUTER_IN_PARAM_ERR                  (AOXE_ROUTER_ERR_CODE_BASE - 4)	                 // 输入参数错误


#define AOXE_ROUTER_INIT_ERR                      (AOXE_ROUTER_ERR_CODE_BASE - 5)					 // 路由初始化错误

#define AOXE_ROUTER_MODULE_REDIFINED_ERR          (AOXE_ROUTER_ERR_CODE_BASE - 6)					 // 路由回调模块号重定义错误
#define AOXE_ROUTER_GET_CMD_ERR                   (AOXE_ROUTER_ERR_CODE_BASE - 7)	                 // 获取命令错误 
#define AOXE_ROUTER_NOT_SUPPORTED_MSG_TYPE_ERR    (AOXE_ROUTER_ERR_CODE_BASE - 8)	                 // 不支持的消息类型
#define AOXE_ROUTER_NOT_SUPPORTED_BROADCAST_ERR   (AOXE_ROUTER_ERR_CODE_BASE - 9)	                 // 不支持的消息类型
#define AOXE_ROUTER_CALLBACK_FUN_REGS_ERR	      (AOXE_ROUTER_ERR_CODE_BASE - 10)					 // 路由回调函数注册错误 
#define AOXE_ROUTER_PAYLOAD_NULL_ERR			  (AOXE_ROUTER_ERR_CODE_BASE - 11)					 // 路由负载为空 
#define AOXE_ROUTER_NODE_ID_ERR			      	  (AOXE_ROUTER_ERR_CODE_BASE - 12)					 // 节点ID错误 
#define AOXE_ROUTER_NULL_INSTANCE_ERR			  (AOXE_ROUTER_ERR_CODE_BASE - 13)					 // 对象为空错误

#define AOXE_ROUTER_MODULE_ID_ERR                 (AOXE_ROUTER_ERR_CODE_BASE - 14)					 // 注册中间件回调模块ID为0错误
#define AOXE_ROUTER_BUFF_TOO_SMALL_ERR		      (AOXE_ROUTER_ERR_CODE_BASE - 18)					 // buffer太小错误   
#define AOXE_ROUTER_PAYLOAD_LEN_ERR		          (AOXE_ROUTER_ERR_CODE_BASE - 19)					 // 传入长度错误
#define AOXE_ROUTER_RELAY_AGENT_NOT_MYSELF		  (AOXE_ROUTER_ERR_CODE_BASE - 20)					 // 转发节点不为本节点
#define AOXE_ROUTER_SOURCE_NODE_ID_ERR		      (AOXE_ROUTER_ERR_CODE_BASE - 21)					 // 发送时填写的本地节点号错误
#define AOXE_ROUTER_BROADCAST_NET_ERR             (AOXE_ROUTER_ERR_CODE_BASE - 22)					 // 调用广播接口未填指定总线
#define AOXE_ROUTER_NO_SECOND_BEST_AGENT		  (AOXE_ROUTER_ERR_CODE_BASE - 23)					 // 无次优转发节点
#define AOXE_ROUTER_ROUTER_CHECK_ERR			  (AOXE_ROUTER_ERR_CODE_BASE - 24)					 // 路由建立时检查错误
#define AOXE_ROUTER_BACK_UP_TOPIC_NOT_FOUND		  (AOXE_ROUTER_ERR_CODE_BASE - 25)					 // 非备份主题
#define AOXE_ROUTER_ROUTER_ITEM_INDEX_ERR		  (AOXE_ROUTER_ERR_CODE_BASE - 26)					 // 路由表项的索引错误
#define AOXE_ROUTER_ROUTER_REPLY_ERR		 	  (AOXE_ROUTER_ERR_CODE_BASE - 27)					 // 路由reply给非相邻节点错误
#define AOXE_ROUTER_FLIGHT_ID_GET_ERR		 	  (AOXE_ROUTER_ERR_CODE_BASE - 28)					 // 获取飞机型号ID失败
#define AOXE_ROUTER_FLIGHT_ID_NO_PERMISSION_ERR	  (AOXE_ROUTER_ERR_CODE_BASE - 29)					 // 没有权限设置飞机型号ID
#define AOXE_ROUTER_PUB_TOPIC_NOT_FOUND_ERR		  (AOXE_ROUTER_ERR_CODE_BASE - 30)					 // 未在表内找到发布主题
#define AOXE_ROUTER_PUB_BITMAP_NULL_ERR		 	  (AOXE_ROUTER_ERR_CODE_BASE - 31)					 // 发布主题的bitmap为空错误
#define AOXE_ROUTER_PUB_AGENT_OFFLINE_ERR		  (AOXE_ROUTER_ERR_CODE_BASE - 32)					 // 发布主题的代理节点不在线
#define AOXE_ROUTER_DATAGRAM_ERR				  (AOXE_ROUTER_ERR_CODE_BASE - 33)					 // 接收数据错误
#define AOXE_ROUTER_PERMISSION_DENIED 			  (AOXE_ROUTER_ERR_CODE_BASE - 34)					 // 无权限错误


/* 时间管理服务返回值  */
#define AOXE_TIMESERV_SUCC                             (0)

#define AOXE_TIMESERV_ERR_CODE_BASE                    (-2000)     

#define AOXE_TIMESERV_NO_PERMISSION_ERR				   (AOXE_TIMESERV_ERR_CODE_BASE - 1)     //当前节点无权操作
#define AOXE_TIMESERV_NULL_INSTANCE_ERR				   (AOXE_TIMESERV_ERR_CODE_BASE - 13)    

/* 应用错误返回值  */
#define AOXE_APPNODE_SUCC                             (0)

#define AOXE_APPNODE_ERR_CODE_BASE                    (-200)     

#define AOXE_APPNODE_NULL_FILENAME_ERR				   (AOXE_APPNODE_ERR_CODE_BASE - 56) 
#define AOXE_APPNODE_FILENAME_OVERSIZE_ERR			   (AOXE_APPNODE_ERR_CODE_BASE - 57)


/* 框架返回值 */
#define AOXE_FRAME_SUCC                             (1)

#define AOXE_FRAME_ERR_CODE_BASE                    (-2500)

#define AOXE_FRAME_INIT_ERR                        (AOXE_FRAME_ERR_CODE_BASE - 5)					 // 框架初始化错误

#define AOXE_FRAME_NODE_ID_ERR			      	    (AOXE_FRAME_ERR_CODE_BASE - 12)					 // 节点ID错误 

#define AOXE_TSS_NO_CONFIG                          (AOXE_FRAME_ERR_CODE_BASE - 15)                  // 没有TSS配置 

#define AOXE_TSS_INIT_ERR                           (AOXE_FRAME_ERR_CODE_BASE - 16)                  // TSS初始化错误 

#define AOXE_TSS_CREATE_CONN_ERR                    (AOXE_FRAME_ERR_CODE_BASE - 17)                  // TSS创建连接错误 

#define AOXE_TSS_REGISTER_CB_ERR                    (AOXE_FRAME_ERR_CODE_BASE - 18)    



/* 修改 gAoxeDebugPrintIndex的值可以进行对应打印 */
/************************ DEBUG INDEX ************************/
/************************ NETFC INDEX************************/
#define FC_GET_DATE								  (10)
#define FC_GET_LOCAL_RTC						  (11)
#define FC_GET_SYS_RTC							  (12)
#define FC_GET_MISSION_DELTA_RTC				  (13)
#define FC_GET_NORMAL_MSG_NUM                     (14)
#define FC_GET_STREAM_MSG_NUM                     (15)
#define FC_GET_VERSION                            (16)
#define FC_READ_NORM_MSG						  (17)
#define FC_READ_MNTR_MSG						  (18)
#define FC_READ_STRM_MSG						  (19)
#define FC_TIME_SERVER_RELEVANT					  (20)
#define FC_SET_DATE								  (21)
#define FC_SET_SYS_RTC							  (22)
#define FC_RELEASE_STRM_BUFF					  (23)
#define FC_SEND_NORM_MSG_ERR					  (24)
#define FC_SEND_NORM_MSG_SUCC                     (25)
#define FC_GET_STRM_BUFFER					 	  (26)
#define FC_SEND_STRM_MSG_ERR					  (27)
#define FC_SEND_STRM_MSG_SUCC					  (28)
#define FC_READ_UNICAST_MSG						  (29)
#define FC_READ_SUB_MSG							  (30)
#define FC_READ_AGENT_PUB_MSG					  (31)
#define FC_GET_TEMPERATURE						  (32)
/************************ NETFC END************************/

/************************ NETNDB INDEX************************/
#define NDB_GET_PERIOD_MSG_NUM					  (50)
#define NDB_GET_EVENT_MSG_NUM					  (51)
#define NDB_GET_VERSION					  		  (52)
#define NDB_GET_PERIOD_BIT						  (53)
#define NDB_GET_POWERUP_BIT						  (54)
#define NDB_INIT_FAIL							  (55)
#define NDB_READ_EVENT_MSG						  (56)
#define NDB_READ_PERIOD_MSG						  (57)
#define NDB_READ_STOF_MSG						  (58)
#define NDB_SEND_PERIOD_MSG_SUCC				  (59)
#define NDB_SEND_EVENT_MSG_SUCC					  (60)
/************************ NETNDB END************************/
/************************ NETPCIE INDEX************************/
#define PCIE_GET_NORM_MSG_NUM                     (75)
#define PCIE_READ_NORM_MSG   					  (76)
#define PCIE_SEND_NORM_MSG_ERR					  (77)
#define PCIE_SEND_NORM_MSG_SUCC                   (78)
#define PCIE_READ_UNICAST_MSG                 	  (79)
#define PCIE_READ_SUB_MSG                 		  (80)
#define PCIE_READ_AGENT_PUB_MSG                   (81)
#define PCIE_SEND_STRM_MSG_ERR					  (82)
#define PCIE_SEND_STRM_MSG_SUCC					  (83)
#define PCIE_GET_STRM_BUFFER					  (84)
#define PCIE_GET_STRM_MSG_NUM					  (85)
#define PCIE_READ_STRM_MSG						  (86)
#define PCIE_RELEASE_STRM_BUFF					  (87)
/************************ NETPCIE END************************/
/************************ NETTIC INDEX************************/
#define TIC_GET_LOCAL_RTC						  (100)
#define TIC_GET_SYS_RTC							  (101)
#define TIC_GET_NORMAL_MSG_NUM                    (102)
#define TIC_GET_STREAM_MSG_NUM                    (103)
#define TIC_GET_VERSION                           (104)
#define TIC_GET_PERIOD_BIT						  (105)
#define TIC_GET_POWERUP_BIT						  (106)
#define TIC_GET_TIME_SERVER_STATUS				  (107)
#define TIC_DISCARD_NORM_MSG					  (108)
#define TIC_READ_NORM_MSG					      (109)
#define TIC_READ_STRM_MSG						  (110)
#define TIC_TIME_SERVER_RELEVANT				  (111)
#define TIC_SET_SYS_RTC							  (112)
#define TIC_RELEASE_STRM_BUFF					  (113)
#define TIC_SEND_NORM_MSG_ERR					  (114)
#define TIC_SEND_NORM_MSG_SUCC                    (115)
#define TIC_GET_STRM_BUFFER					 	  (116)
#define TIC_SEND_STRM_MSG_ERR					  (117)
#define TIC_SEND_STRM_MSG_SUCC					  (118)
#define TIC_READ_UNICAST_MSG                      (119)
#define TIC_READ_SUB_MSG                          (120)
#define TIC_READ_AGENT_PUB_MSG                    (121)
/************************ NETTIC END************************/
/************************ NETPN INDEX************************/
#define PN_GET_NORMAL_MSG_NUM					  (140)
#define PN_GET_STREAM_MSG_NUM					  (141)
#define PN_READ_UNICAST_MSG						  (142)
#define PN_READ_SUB_MSG							  (143)
#define PN_READ_AGENT_PUB_MSG					  (144)
#define PN_READ_NORM_MSG						  (145)
#define PN_SEND_NORM_MSG						  (146)
/************************ NETPN END************************/
