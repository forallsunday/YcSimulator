cmake_minimum_required(VERSION 3.10.0)

project(YcSim)

set(CMAKE_CXX_STANDARD 14)

# 输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}")

# 共用文件静态库 (包含 deps 和 geolocation)
add_subdirectory("lib")

# ==================================================
# 静态库: CameraSimulator
# ==================================================
# yc设备主控代码静态库
# 相机仿真库
set(CAMSIM_NAME "cam_sim")
aux_source_directory("yc_camera_sim/src" SRCS_CAMSIM)
aux_source_directory("yc_camera_sim/src/yc" SRCS_CAMSIM_YC)
add_library(${CAMSIM_NAME} STATIC ${SRCS_CAMSIM} ${SRCS_CAMSIM_YC})
set_target_properties(${CAMSIM_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
set(INCLUDE_CAMSIM 
"${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/include" 
"${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/include/yc")
target_include_directories(${CAMSIM_NAME} PUBLIC ${INCLUDE_CAMSIM})
target_link_libraries(${CAMSIM_NAME} PUBLIC deps)

# ==================================================
# 库: 相机仿真模型 
# ==================================================
# 如果是linux-arm平台，则编译ycSim
if(${TARGET_PLATFORM} STREQUAL "linux-aarch64")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(LIB_NAME "ycSim")
  # 使用静态库
  add_library(${LIB_NAME} SHARED "${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/model.cpp")
  target_link_libraries(${LIB_NAME} PUBLIC ${CAMSIM_NAME})
  # 链接共享内存库
  target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/cadi_user/include)
  target_link_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/cadi_user/lib)
  target_link_libraries(${LIB_NAME} PRIVATE cadi_user rt)
endif()

# ==================================================
# 可执行文件: 机载主控模拟器
# ==================================================
set(EXE_NAME "YcControl")

set(INCLUDE_YCCTRL "${CMAKE_CURRENT_SOURCE_DIR}/yc_control_sim/include")
aux_source_directory("yc_control_sim/src" SRCS_YCCTRL)

add_executable(${EXE_NAME} ${SRCS_YCCTRL})
target_include_directories(${EXE_NAME} PRIVATE ${INCLUDE_YCCTRL})
# YcControl 需要 deps 库来获取 Def/ 头文件
target_link_libraries(${EXE_NAME} PRIVATE deps pthread)

# ==================================================
# 复制文件
# ==================================================
# 要复制的文件路径
set(XML_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ModuleConfig.xml")
if(EXISTS "${XML_CONFIG_FILE}")
  add_custom_command(
    TARGET ${EXE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${XML_CONFIG_FILE}"
    "${CMAKE_CURRENT_SOURCE_DIR}/bin/ModuleConfig.xml"
    COMMENT "Copying ModuleConfig.xml to bin directory")
endif()

set(XML_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/UDPNodeConfig_A.xml")
if(EXISTS "${XML_CONFIG_FILE}")
  add_custom_command(
    TARGET ${EXE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${XML_CONFIG_FILE}"
    "${CMAKE_CURRENT_SOURCE_DIR}/bin/UDPNodeConfig_A.xml"
    COMMENT "Copying UDPNodeConfig_A.xml to bin directory")
endif()

set(libycSim_FILE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/libycSim.so")
message(${libycSim_FILE})
if(EXISTS "${libycSim_FILE}")
  add_custom_command(
    TARGET ${LIB_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${libycSim_FILE}"
    "${CMAKE_CURRENT_SOURCE_DIR}/debug/libycSim.so"
    COMMENT "Copying libycSim.so to debug directory")
endif()

# ==================================================
# 可执行文件: 测试发送UDP包
# ==================================================
set(TEST_EXE_NAME "TestUdpSend")
add_executable(${TEST_EXE_NAME} "./yc_test_send_udp_packet/main.cpp")
target_link_libraries(${TEST_EXE_NAME} PRIVATE ${CAMSIM_NAME})
target_link_libraries(${TEST_EXE_NAME} PUBLIC pthread)
