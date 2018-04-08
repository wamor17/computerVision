cmake_minimum_required(VERSION 2.8.12)

project(sum_diff)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(sum_diff sum_diff.cpp)
target_link_libraries(sum_diff ${OpenCV_LIBS})
