cmake_minimum_required(VERSION 3.10.0)
project(geolocation)

if(MSVC)
  add_compile_options(/utf-8)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED 11)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" SRCS)

add_library(${PROJECT_NAME} STATIC ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/eigen3")

