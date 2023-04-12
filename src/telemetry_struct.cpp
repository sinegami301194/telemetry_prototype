//кодировка=utf-8
#include <telemetry2/telemetry_struct.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace telemetry2;

std::string telemetry2::fillNumZero(const int x)
{
  char s[4] = {};
  sprintf(s, "%02d", x);
  return {s};
}

BaseMessage::BaseMessage() {}
BaseMessage::~BaseMessage() {}
bool BaseMessage::write(const std::string& absPath_part) const
{
  return false;
}

bool BaseMessage::fillTheSameFields(Json::Value& data) const
{
  data["device_id"] = this->jIH.device_id;
  data["type"] = this->type;
  return true;
}

bool GPS::write(const std::string& absPath_part) const
{
  Json::Value gpsData;
  fillTheSameFields(gpsData);
  gpsData["gps_speed"] = this->gps_speed;
  gpsData["lat"] = this->lat;
  gpsData["lon"] = this->lon;
  gpsData["yaw"] = this->yaw;
  ofstream o(absPath_part + ".gps.json");
  o << gpsData << endl;
  return true;
}

bool Settings::write(const std::string& absPath_part) const
{
  Json::Value settingsData;
  fillTheSameFields(settingsData);
  settingsData["reference_speed"] = this->reference_speed;
  ofstream o(static_cast<std::string>(absPath_part + ".settings.json"));
  o << settingsData << endl;
  return true;
}
