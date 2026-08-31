cmake_minimum_required(VERSION 3.6)
project(tcp_client C)

set(CMAKE_C_STANDARD 99)

# =========== CLIENT - TCP ===========
add_executable(tcp_client
        src/main.c
        src/tcp_client.c)

target_include_directories( tcp_client PRIVATE include)

# ===================================



