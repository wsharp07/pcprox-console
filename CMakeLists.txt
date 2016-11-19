cmake_minimum_required(VERSION 3.5)
project(pcprox-console)

# Set properties
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include .h files
include_directories(lib/hidapi)
include_directories(lib/pcProxAPI)
include_directories(include)

# Include external .so
link_directories(lib/pcProxAPI)

# Find external hidapi lib
find_library(HIDAPI_LIB NAMES hidapi-hidraw PATHS /usr/lib/x86_64-linux-gnu)
if(NOT HIDAPI_LIB)
    message(FATAL_ERROR "hidapi library not found. are you sure you installed the package?")
endif()

# Include all source files
file(GLOB SOURCES "src/*.cpp")

# Define executable
add_executable(pcprox-console ${SOURCES})

# Link external libs
target_link_libraries (pcprox-console pcProxAPI ${HIDAPI_LIB})
