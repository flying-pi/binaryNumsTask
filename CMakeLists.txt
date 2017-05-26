cmake_minimum_required(VERSION 3.6)
project(binaryNums)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tree.cpp Tree.h)
add_executable(binaryNums ${SOURCE_FILES})