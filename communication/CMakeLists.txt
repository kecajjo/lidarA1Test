cmake_minimum_required(VERSION 3.6)
project(communication)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(protobuf)
add_subdirectory(zmq)