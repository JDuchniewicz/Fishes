cmake_minimum_required(VERSION 3.6)
project(fishesGenerator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(fishesGenerator ${SOURCE_FILES})