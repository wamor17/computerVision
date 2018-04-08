cmake_minimum_required(VERSION 2.8.12)

project(chess)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(chess chess.cpp)
target_link_libraries(chess ${OpenCV_LIBS})
