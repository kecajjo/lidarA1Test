#include "rplidar.hpp"

#include <iostream>

namespace Rplidar {

Rplidar::Rplidar(const std::string port)
    : channel(sl::createSerialPortChannel(port, 115200)) {
  lidar = *sl::createLidarDriver();
  auto res = lidar->connect(*channel);
  if (IS_FAIL(res)) {
    delete lidar;
    delete *channel;
    throw std::runtime_error("Failed to connect LIDAR");
  }
}

void Rplidar::startScan(){
  lidar->startScan(false, true);
}

Rplidar::Scan Rplidar::getScanData(const int minQuality) {
  sl_lidar_response_measurement_node_hq_t nodes[8192];
  size_t nodeCount =
      sizeof(nodes) / sizeof(sl_lidar_response_measurement_node_hq_t);
  auto res = lidar->grabScanDataHq(nodes, nodeCount);

  if (IS_FAIL(res)) {
    throw std::runtime_error("Failed to get scan data");
  }
  lidar->ascendScanData(nodes, nodeCount);
  std::vector<Rplidar::SingleData> scanVec;
  for (int i=0; i<nodeCount; i++) {
    if (nodes[i].quality >= minQuality) {
      float angleDeg = nodes[i].angle_z_q14 * 90.f / (1 << 14);
      float distanceMm = nodes[i].dist_mm_q2 / 4;
      scanVec.push_back(
          Rplidar::SingleData(angleDeg, distanceMm, nodes[i].quality));
    }
  }

  return std::move(Rplidar::Scan(scanVec));
}

} // namespace Rplidar
