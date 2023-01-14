cmake_minimum_required(VERSION 3.6)
project(laptop_lidar)

set(CMAKE_CXX_STANDARD 20)

add_executable(laptop_lidar src/main.cpp)
target_link_libraries(laptop_lidar PUBLIC communication)
