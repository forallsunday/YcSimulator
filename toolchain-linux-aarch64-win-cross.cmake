# 告诉 CMake这是交叉编译到 Linux
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Linaro 工具链路径
set(TOOLCHAIN_PATH "d:/cross_compile/compiler/gcc-linaro-7.3.1-2018.05-i686-mingw32_aarch64-linux-gnu")

# 交叉编译器
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-linux-gnu-gcc.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-linux-gnu-g++.exe)

# 不搜索 Windows 系统路径
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH}/aarch64-linux-gnu/libc)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 如果有 sysroot
set(CMAKE_SYSROOT ${TOOLCHAIN_PATH}/aarch64-linux-gnu/libc)
