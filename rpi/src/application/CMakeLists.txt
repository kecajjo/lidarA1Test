cmake_minimum_required(VERSION 3.6)

add_executable(rpi_lidar src/main.cpp)
target_link_libraries(rpi_lidar PUBLIC rplidar_wrapper communication)
