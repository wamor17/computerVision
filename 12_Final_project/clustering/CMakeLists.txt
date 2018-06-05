cmake_minimum_required(VERSION 2.8.12)

project(clustering)

add_executable(clustering clustering.cpp)
target_link_libraries(clustering serial)
set(CMAKE_CXX_FLAGS "-pthread")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(clustering ${OpenCV_LIBS})
