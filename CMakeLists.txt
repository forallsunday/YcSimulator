cmake_minimum_required(VERSION 3.10.0)

project(ycSim)

set(CMAKE_CXX_STANDARD 11)

# 输出的文件 (在这里设置位置 确保编译的库正确复制到指定位置)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(INCLUDE_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/deps/include")
set(INCLUDE_DEPS ${INCLUDE_DEPS_ROOT} "${INCLUDE_DEPS_ROOT}/ICD" "${INCLUDE_DEPS_ROOT}/Def")

# 库: 相机仿真模型
set(LIB_NAME "ycSim") # 库输出名字
set(INCLUDE_YCSIM "${CMAKE_CURRENT_SOURCE_DIR}/yc_sim/include")
aux_source_directory("deps/src" SRCS_DEPS)
aux_source_directory("yc_sim/src" SRCS_YCSIM)
add_library(${LIB_NAME} SHARED ${SRCS_YCSIM} ${SRCS_DEPS})
target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DEPS} ${INCLUDE_YCSIM}) # 注意这个PUBLIC
# 共享内存静态库 包含头文件目录
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cadi_user/include)
# 添加库搜索路径
target_link_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cadi_user/lib)
# 链接库
target_link_libraries(${LIB_NAME} PRIVATE cadi_user rt)

# install
set_target_properties(${LIB_NAME} PROPERTIES DEBUG_POSTFIX "d" RELEASE_POSTFIX "")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")
install(TARGETS ${LIB_NAME})

# 可执行文件: 机载主控模拟器
set(EXE_NAME "YcControl")
set(INCLUDE_YCCTRL "${CMAKE_CURRENT_SOURCE_DIR}/yc_control/include")
aux_source_directory("yc_control/src" SRCS_YCCTRL)
add_executable(${EXE_NAME} ${SRCS_YCCTRL} ${SRCS_DEPS})
target_include_directories(${EXE_NAME} PRIVATE ${INCLUDE_DEPS} ${INCLUDE_YCCTRL})
target_link_libraries(${EXE_NAME} PRIVATE pthread)
