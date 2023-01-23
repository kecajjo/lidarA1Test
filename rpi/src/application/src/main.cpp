#include "LaserScan.pb.h"
#include "publisher.hpp"
#include "rplidar.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

#define PUBLISHED_TOPIC "LaserScan"

int main(int argc, char **argv) {
  std::string portName = "/dev/ttyUSB0";
  if (argc > 1) {
    portName = argv[1];
  }
  Rplidar::Rplidar lidar(portName);
  auto pub = zmq_helper::Publisher<LaserScan>("tcp://*:5555");

  while (1) {
    lidar.startScan();
    sleep(0.1);
    auto data = lidar.getScanData(0);

    LaserScan scan;
    scan.set_size(data.size());
    for (int i = 0; i < data.size(); i++) {
      LaserScan::LaserRay *ray = scan.add_rays();
      ray->set_quality(data[i].quality);
      ray->set_angle_deg(data[i].angleDeg);
      ray->set_range_mm(data[i].rangeMm);
    }
    pub.publish(scan, PUBLISHED_TOPIC);
  }
}