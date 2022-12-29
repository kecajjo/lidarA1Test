#include "rplidar.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char **argv) {
  std::string portName = "/dev/ttyUSB0";
  if (argc > 1) {
    portName = argv[1];
  }
  Rplidar::Rplidar lidar(portName);
  lidar.startScan();
  sleep(1);
  auto data = lidar.getScanData(1);
  for (int i = 0; i < data.size(); i++) {
    std::cout << "deg: " << data[i].angleDeg << " m: " << data[i].rangeMm/1000
              << " quality:" << data[i].quality << std::endl;
  }
}