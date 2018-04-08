cmake_minimum_required(VERSION 2.8.12)

project(examen)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(examen examen.cpp)
target_link_libraries(examen ${OpenCV_LIBS})
