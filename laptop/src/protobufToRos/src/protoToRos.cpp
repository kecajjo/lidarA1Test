#include "protoToRos.hh"
#include "sensor_msgs/LaserScan.h"
#include <cmath>
#include <functional>

namespace lidar_ros {
namespace {
double degToRad(double deg) { return deg * M_PI / 180; }
} // namespace
ProtoToRos::ProtoToRos(const std::string &rosTopic, const std::string &zmqPort,
                       const std::string &zmqTopic)
    : pub(nh.advertise<sensor_msgs::LaserScan>(rosTopic, 1000)), zmqSub(zmqPort, zmqTopic,
             std::bind(&ProtoToRos::callback, this, std::placeholders::_1)) {
}

void ProtoToRos::callback(std::unique_ptr<LaserScan> scan) {
  auto msg = protoMsgToRosMsg(std::move(scan));
  msg.header.frame_id = "map";
  msg.header.seq = seq;
  ++seq;
  msg.header.stamp = ros::Time::now();
  pub.publish(msg);
}

sensor_msgs::LaserScan
ProtoToRos::protoMsgToRosMsg(std::unique_ptr<LaserScan> scan) {
  sensor_msgs::LaserScan msg;
  int size = scan->rays_size();
  msg.angle_min = degToRad(scan->rays(0).angle_deg());
  msg.angle_max = degToRad(scan->rays(size - 1).angle_deg());
  msg.angle_increment = abs(degToRad(scan->rays(size - 1).angle_deg() -
                                      scan->rays(0).angle_deg())) /
                         size;
  msg.range_min = 0.1;
  msg.range_max = 3;
  std::cout << size << std::endl;
  std::cout << msg.angle_min << std::endl;
  std::cout << msg.angle_max << std::endl;
  std::cout << msg.angle_increment << std::endl;

  return msg;
}
}; // namespace lidar_ros