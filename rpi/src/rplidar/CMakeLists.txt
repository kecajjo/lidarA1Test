cmake_minimum_required(VERSION 3.6)
project(rpi_comunication)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#dirty hack as rplidar doesnt have cmake target
find_library(
  LIDAR_SDK_LIB
  NAMES sl_lidar_sdk
  PATH_SUFFIXES rplidar_sdk
  )

# ##############################################################################
add_executable(rplidar_wrapper src/rplidar.cpp)
target_include_directories(rplidar_wrapper PUBLIC inc/)
target_link_libraries(rplidar_wrapper PUBLIC ${LIDAR_SDK_LIB} Threads::Threads)
