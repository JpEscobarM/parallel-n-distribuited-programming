cmake_minimum_required(VERSION 3.6)
project(udp_server C)

set(CMAKE_C_STANDARD 99)

add_executable(udp_server src/main.c)

target_include_directories( udp_server PRIVATE include)
