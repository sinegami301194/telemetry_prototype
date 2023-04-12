//кодировка=utf-8
#include <telemetry2/message_telemetry_filler.h>

using namespace std;
using namespace telemetry2;

MessageTelemetryFiller::MessageTelemetryFiller()
    : year(-1), month(-1), day(-1) {}

std::string MessageTelemetryFiller::getDeviceId() const
{
  std::string t = "car";
  return t;
}
GPS MessageTelemetryFiller::fill(double gps_speed, double lat, double lon, double yaw) const
{
  std::string t = this->getDeviceId();
  JsonInfoHeader jIH{t};
  GPS gpsTelemetry{gps_speed, lat, lon, yaw, jIH};
  return gpsTelemetry;
}

Settings MessageTelemetryFiller::fill() const
{
  std::string t = this->getDeviceId();
  JsonInfoHeader jIH{t};
  Settings s{5, jIH};
  return s;
}

bool MessageTelemetryFiller::isHarvesterStopped(const double new_dbw_speed)
{
  if (abs(new_dbw_speed) < numeric_limits<double>::epsilon()) {
    return true;
  }
  return false;
}
