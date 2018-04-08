cmake_minimum_required(VERSION 2.8.12)

project(create)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(create create.cpp)
target_link_libraries(create ${OpenCV_LIBS})
