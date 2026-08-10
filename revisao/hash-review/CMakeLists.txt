cmake_minimum_required(VERSION 3.6)
project(hash_review C)

set(CMAKE_C_STANDARD 99)

#CRIA O EXECUTAVEL NORMAL
add_executable(
        hash_review
        src/main.c
        src/hashTable.c
)

target_include_directories(
        hash_review
        PRIVATE
        include
)

# Compila o executável de testes
add_executable(
        hash_table_tests
        tests/test_hashTable.c
        src/hashTable.c
)

# Permite encontrar hashTable.h
target_include_directories(
        hash_table_tests
        PRIVATE
        include
)

# Ativa o suporte ao CTest
enable_testing()

# Registra o executável como teste
add_test(
        NAME testes_tabela_hash
        COMMAND hash_table_tests
)