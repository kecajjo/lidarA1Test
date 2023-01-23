#pragma once
#include "LaserScan.pb.h"
#include "subscriber.hpp"
#include <string>
#include "ros/ros.h"
#include <memory>
#include "sensor_msgs/LaserScan.h"

namespace lidar_ros {
class ProtoToRos {
public:
  ProtoToRos(const std::string &rosTopic, const std::string &zmqPort,
             const std::string &zmqTopic);

private:
  void callback(std::unique_ptr<LaserScan> scan);
  sensor_msgs::LaserScan protoMsgToRosMsg(std::unique_ptr<LaserScan> scan);
  ros::NodeHandle nh;
  ros::Publisher pub;
  zmq_helper::Subscriber<LaserScan> zmqSub;
  uint seq = 0;
};
} // namespace lidar_ros