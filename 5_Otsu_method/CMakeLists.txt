cmake_minimum_required(VERSION 2.8.12)

project(otsu)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(otsu otsu.cpp)
target_link_libraries(otsu ${OpenCV_LIBS})
