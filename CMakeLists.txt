cmake_minimum_required(VERSION 3.6)
project(lidar)

## use this to globally use C++20 with in our project
set(CMAKE_CXX_STANDARD 20)
## load in pkg-config support
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

option(MACHINE "Decide if you want to build for \"laptop\" or \"rpi\"")

add_subdirectory(protobuf)

IF(${MACHINE} STREQUAL "laptop")
    add_subdirectory(laptop/src)
ELSEIF(${MACHINE} STREQUAL "rpi")
    add_subdirectory(rpi/src)
ELSE()
    message("Unknown machine target")
ENDIF()
