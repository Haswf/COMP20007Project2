cmake_minimum_required(VERSION 3.10)
project(COMP20007Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(provided_files)

add_executable(COMP20007Project2
        max_heap.c
        max_heap.h
        main.c)
