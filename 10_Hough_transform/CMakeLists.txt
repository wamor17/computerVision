cmake_minimum_required(VERSION 2.8.12)

project(hough)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hough hough.cpp)
target_link_libraries(hough ${OpenCV_LIBS})
