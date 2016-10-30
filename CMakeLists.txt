cmake_minimum_required(VERSION 3.6)
project(timsort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11 -Wall -Wextra")

set(SOURCE_FILES main.cpp timsort.h parameters.h runs.h stackRuns.h sortingAlgorithms.h tests.h)
add_executable(timsort ${SOURCE_FILES})
