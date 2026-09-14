cmake_minimum_required(VERSION 3.6)
project(mpi_transferrencia_calor C)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)

add_executable(mpi_transferrencia_calor
        main.c)

target_link_libraries(mpi_transferrencia_calor MPI::MPI_C )