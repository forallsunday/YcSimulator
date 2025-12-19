# -------------------------------
# toolchain-linux-aarch64-linux-cross.cmake
# Cross compile from Linux x64 to Linux ARM64
# -------------------------------

# 告诉 CMake这是交叉编译到 Linux
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Linaro 工具链路径
set(TOOLCHAIN_PATH "/home/robin/compiler/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu")

# 交叉编译器
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-linux-gnu-g++)

# 不搜索宿主系统路径（x86_64 Linux）
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH}/aarch64-linux-gnu/libc)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 如果有 sysroot
set(CMAKE_SYSROOT ${TOOLCHAIN_PATH}/aarch64-linux-gnu/libc)

# 默认开启位置无关代码（适合生成动态库）
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
