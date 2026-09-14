cmake_minimum_required(VERSION 3.6)
project(transferrencia_calor C)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)

add_executable(transferrencia_calor_sequencial
        sequencial-transferencia-calor.c)

add_executable(transferrencia_calor_mpi
        mpi-transferencia-calor.c)


target_link_libraries(transferrencia_calor_mpi MPI::MPI_C )