#include <rplidar_sdk/rplidar.h>
#include <rplidar_sdk/sl_lidar.h>
#include <rplidar_sdk/sl_lidar_driver.h>

#include <vector>

namespace Rplidar {
class Rplidar {
public:
  struct SingleData {
    double angleDeg;
    double rangeMm;
    int quality;
    SingleData(const double a, const double r, const double q) {
      angleDeg = a;
      rangeMm = r;
      quality = q;
    }
  };
  class Scan {
  public:
    Scan(std::vector<SingleData> d) { data = d; }
    SingleData operator[](const unsigned int i) const { return data[i]; }
    unsigned int size() const { return data.size(); }
    std::vector<SingleData> data;
  };

  Rplidar(const std::string port);
  ~Rplidar() {
    delete lidar;
    delete *channel;
  }

  void startScan();
  Scan getScanData(const int minQuality = 0);

private:
  sl::Result<sl::IChannel *> channel;
  sl::ILidarDriver *lidar;
};
} // namespace Rplidar