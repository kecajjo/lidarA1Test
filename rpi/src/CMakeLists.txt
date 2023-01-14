cmake_minimum_required(VERSION 3.6)
project(rpi_lidar)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(communication)
add_subdirectory(rplidar)
add_subdirectory(application)
