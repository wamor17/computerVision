cmake_minimum_required(VERSION 2.8.12)

project(ajustes)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ajustes ajustes.cpp)
target_link_libraries(ajustes ${OpenCV_LIBS})
