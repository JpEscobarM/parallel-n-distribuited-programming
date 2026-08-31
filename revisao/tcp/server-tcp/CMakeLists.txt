cmake_minimum_required(VERSION 3.6)
project(tcp_server C)

set(CMAKE_C_STANDARD 99)



# =========== CLIENT - TCP ===========
add_executable(tcp_server
        src/main.c
        src/tcp_server.c)

target_include_directories( tcp_server PRIVATE include)

# ===================================

