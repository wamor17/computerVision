cmake_minimum_required(VERSION 2.8.12)

project(testSerial)

ADD_EXECUTABLE(testSerial testSerial.cpp)
TARGET_LINK_LIBRARIES(testSerial serial)
SET(CMAKE_CXX_FLAGS "-pthread")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(testSerial ${OpenCV_LIBS})
