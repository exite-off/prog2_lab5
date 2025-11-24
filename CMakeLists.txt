cmake_minimum_required(VERSION 3.31)
project(prog2_lab3)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(.)

add_executable(prog2_lab5
        main.cpp)