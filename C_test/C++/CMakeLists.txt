cmake_minimum_required(VERSION 3.16)
project(Problems)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)

# 禁用 'dbg.h' 标头包含在代码库中的警告
add_definitions(-DDBG_MACRO_NO_WARNING) 

# 设置调试相关的编译选项
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

file(GLOB SOURCE_FILES "src/*.cpp")

foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SOURCE_FILE})
endforeach()