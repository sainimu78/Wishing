cmake_minimum_required(VERSION 3.20)
project(ECS_Cpp LANGUAGES CXX)

# 强制使用 Clang 编译器
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Require Clang compiler")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

# 优化选项配置
add_compile_options(
    -O3
    -march=native
    -mtune=native
    -ffast-math
    -flto=thin
    -mavx2
    -fstrict-aliasing
    -Wall
    -Wextra
    -Wpedantic
)

add_link_options(
    -flto=thin
    -fuse-ld=lld
)

add_executable(ECS_Cpp
    Main.cpp
)