cmake_minimum_required(VERSION 3.6)
project(Fishes)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c map.h action.h io.h map.c action.c io.c)
add_executable(Fishes ${SOURCE_FILES})