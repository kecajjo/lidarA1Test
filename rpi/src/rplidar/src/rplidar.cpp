#include "rplidar.hpp"

namespace Rplidar {

Rplidar::Rplidar(const std::string port)
    : channel(sl::createSerialPortChannel("/dev/ttyUSB0", 115200)) {
  lidar = *sl::createLidarDriver();
  auto res = lidar->connect(*channel);
  if (!SL_IS_OK(res)) {
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
  for (const auto& node : nodes) {
    if (node.quality >= minQuality) {
      float angleDeg = node.angle_z_q14 * 90.f / (1 << 14);
      float distanceMm = node.dist_mm_q2 / 4;
      scanVec.push_back(
          Rplidar::SingleData(angleDeg, distanceMm, node.quality));
    }
  }

  return std::move(Rplidar::Scan(scanVec));
}

} // namespace Rplidar
