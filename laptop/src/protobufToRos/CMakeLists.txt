cmake_minimum_required(VERSION 3.6)
project(protobuf_to_ros)
set(CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED roscpp sensor_msgs)
catkin_package(INCLUDE_DIRS inc CATKIN_DEPENDS sensor_msgs)

add_subdirectory(communication)
# add_executable(protobuf_to_ros src/main.cpp src/protoToRos.cpp)
# target_include_directories(protobuf_to_ros PUBLIC inc/ ${catkin_INCLUDE_DIRS})
# target_link_libraries(protobuf_to_ros PUBLIC communication ${catkin_LIBRARIES})
