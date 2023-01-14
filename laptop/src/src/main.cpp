#include <string>
#include "subscriber.hpp"
#include "LaserScan.pb.h"

#define SCAN_TOPIC "LaserScan"

void callback(std::unique_ptr<LaserScan> scan){

}

int main(int argc, char **argv) {
  std::string portName = "/dev/ttyUSB0";
  if (argc > 1) {
    portName = argv[1];
  }
  Rplidar::Rplidar lidar(portName);
  auto pub = zmq_helper::Subscriber<LaserScan>("tcp://*:5555", SCAN_TOPIC, callback);

  lidar.startScan();
  sleep(1);
  auto data = lidar.getScanData(0);

  LaserScan scan;
  scan.set_size(data.size());
  for (int i = 0; i < data.size(); i++) {
    LaserScan::LaserRay* ray = scan.add_rays();
    ray->set_quality(data[i].quality);
    ray->set_angle_deg(data[i].angleDeg);
    ray->set_range_mm(data[i].rangeMm);
  }
  pub.publish(scan, PUBLISHED_TOPIC);
}