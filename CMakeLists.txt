cmake_minimum_required(VERSION 3.10.0)

project(YcSim)

set(CMAKE_CXX_STANDARD 14)

# 输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TARGET_PLATFORM}/$<CONFIG>")

# 共用的
set(INCLUDE_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/deps/include")
set(INCLUDE_DEPS ${INCLUDE_DEPS_ROOT} "${INCLUDE_DEPS_ROOT}/ICD" "${INCLUDE_DEPS_ROOT}/Def")
aux_source_directory("deps/src" SRCS_DEPS)

# ==================================================
# 库: 相机仿真模型
# ==================================================
set(INCLUDE_YCSIM
  "${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/include/yc")
aux_source_directory("yc_camera_sim/src" SRCS_YCSIM)
aux_source_directory("yc_camera_sim/src/yc" SRCS_YC)

# 如果不是linux-x64平台，则编译ycSim
if(NOT ${TARGET_PLATFORM} STREQUAL "linux-x64")
  set(LIB_NAME "ycSim")

  add_library(${LIB_NAME} SHARED "${CMAKE_CURRENT_SOURCE_DIR}/yc_camera_sim/model.cpp"
    ${SRCS_YCSIM} ${SRCS_YC} ${SRCS_DEPS})
  target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DEPS} ${INCLUDE_YCSIM})
  target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cadi_user/include)
  target_link_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cadi_user/lib)
  target_link_libraries(${LIB_NAME} PRIVATE cadi_user rt)

  # Debug/Release 后缀（libycSimd.so / libycSim.so） set_target_properties(${LIB_NAME} PROPERTIES
  # DEBUG_POSTFIX "d" RELEASE_POSTFIX "")

  # # 安装路径 set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install") install(TARGETS
  # ${LIB_NAME})
endif()

# ==================================================
# 可执行文件: 机载主控模拟器
# ==================================================
set(EXE_NAME "YcControl")

set(INCLUDE_YCCTRL "${CMAKE_CURRENT_SOURCE_DIR}/yc_control_sim/include")
aux_source_directory("yc_control_sim/src" SRCS_YCCTRL)

add_executable(${EXE_NAME} ${SRCS_YCCTRL} ${SRCS_DEPS})
target_include_directories(${EXE_NAME} PRIVATE ${INCLUDE_DEPS} ${INCLUDE_YCCTRL})
target_link_libraries(${EXE_NAME} PRIVATE pthread)

# Debug/Release 后缀（YcControld / YcControl） set_target_properties(${EXE_NAME} PROPERTIES
# DEBUG_POSTFIX "d" RELEASE_POSTFIX "")

# ==================================================
# 复制配置文件
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

# ==================================================
# 可执行文件: 测试发送UDP包
# ==================================================
set(TEST_EXE_NAME "TestUdpSend")
add_executable(${TEST_EXE_NAME} "./yc_test_send_udp_packet/main.cpp" ${SRCS_YCSIM} ${SRCS_YC} ${SRCS_DEPS})
target_include_directories(${TEST_EXE_NAME} PUBLIC ${INCLUDE_DEPS} ${INCLUDE_YCSIM})
target_link_libraries(${TEST_EXE_NAME} PUBLIC pthread)
