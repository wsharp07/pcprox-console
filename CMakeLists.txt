cmake_minimum_required(VERSION 3.6)
project(pcprox-console)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp syslogger.cpp syslogger.h)
add_executable(pcprox-console ${SOURCE_FILES})