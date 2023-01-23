#include "protoToRos.hh"

#define SCAN_TOPIC "LaserScan"

int main(int argc, char **argv) {
  ros::init(argc, argv, "protobuf_to_ros");
  lidar_ros::ProtoToRos p(SCAN_TOPIC, "tcp://192.168.0.157:5555", SCAN_TOPIC);
  while (ros::ok()) {
     ros::spinOnce();
  }
}