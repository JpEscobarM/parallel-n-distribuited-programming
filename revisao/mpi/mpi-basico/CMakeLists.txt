cmake_minimum_required(VERSION 3.6)
project(mpi C)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)

add_executable(mpi
        src/main.c
)

target_include_directories( mpi PRIVATE include)

target_link_libraries(mpi MPI::MPI_C )
