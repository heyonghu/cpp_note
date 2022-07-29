cmake_minimum_required(VERSION 3.22)
project(my_Server_Web)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)

add_subdirectory(lock)

add_executable(my_Server_Web ${DIR_SRCS})

target_link_libraries(my_Server_Web locker)

