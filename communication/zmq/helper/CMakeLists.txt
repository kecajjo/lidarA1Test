cmake_minimum_required(VERSION 3.6)
project(zmqHelper)

find_package(PkgConfig REQUIRED)

# finding ZeroMq
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(
  ZeroMQ_INCLUDE_DIR
  NAMES zmq.hpp
  PATHS ${PC_ZeroMQ_INCLUDE_DIRS})

find_library(
  ZeroMQ_LIBRARY
  NAMES zmq
  PATHS ${PC_ZeroMQ_LIBRARY_DIRS})

add_library(zmqHelper src/zmqHelper.cpp)
# add the include directory to our compile directives
target_include_directories(zmqHelper PUBLIC inc/ ${ZeroMQ_INCLUDE_DIR})
# at the 0mq library to our link directive
target_link_libraries(zmqHelper PUBLIC ${ZeroMQ_LIBRARY})
