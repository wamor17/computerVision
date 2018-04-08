cmake_minimum_required(VERSION 2.8.12)

project(vision)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(vision vision.cpp)
target_link_libraries(vision ${OpenCV_LIBS})
