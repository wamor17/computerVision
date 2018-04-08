cmake_minimum_required(VERSION 2.8.12)

project(morphology)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(morphology morphology.cpp)
target_link_libraries(morphology ${OpenCV_LIBS})
