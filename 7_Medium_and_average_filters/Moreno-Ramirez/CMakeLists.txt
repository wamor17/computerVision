cmake_minimum_required(VERSION 2.8.12)

project(smoothing)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(smoothing smoothing.cpp)
target_link_libraries(smoothing ${OpenCV_LIBS})
