cmake_minimum_required(VERSION 2.8.12)

project(barras)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(barras barras.cpp)
target_link_libraries(barras ${OpenCV_LIBS})
