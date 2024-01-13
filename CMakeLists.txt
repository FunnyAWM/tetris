cmake_minimum_required(VERSION 3.27)
project(tetris)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall")
#set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(tetris
        main.cpp
        core.cpp
        game.cpp)