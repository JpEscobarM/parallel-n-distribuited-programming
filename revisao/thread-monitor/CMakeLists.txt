cmake_minimum_required(VERSION 3.16)
project(thread_monitor C)

set(CMAKE_C_STANDARD 99)


add_executable(thread_monitor   main.c
                                src/leilao.c
                                src/monitor.c)

target_include_directories(thread_monitor PRIVATE include)

find_package(Threads REQUIRED)

target_link_libraries(thread_monitor Threads::Threads)