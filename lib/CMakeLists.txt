# lib目录下的CMakeLists.txt - 管理所有静态库

# 依赖库 (通用工具、日志、UDP连接等)
add_subdirectory(deps)

# 地理定位库
add_subdirectory(geolocation)
