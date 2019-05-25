cmake_minimum_required(VERSION 3.10)
project(COMP20007Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(COMP20007Project2
        p2b.c
        p2b.h
        )
target_link_libraries(COMP20007Project2 m)