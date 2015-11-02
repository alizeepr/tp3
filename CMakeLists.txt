cmake_minimum_required(VERSION 3.3)
project(TP3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c tp3.h)
add_executable(TP3 ${SOURCE_FILES})
