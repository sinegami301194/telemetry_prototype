//кодировка=utf-8
#include <telemetry2/name_generator.h>
#include <telemetry2/telemetry2.h>

#include <chrono>
#include <thread>
#include <utility>

using namespace std;
using namespace telemetry2;

Telemetry::Telemetry() {
  data.setInitialSettings(settings);
  mode.setAbsPath(settings.dirPath_);
}

bool Telemetry::run()
{
  while (doProceed()) {
    std::cout<< "LOG: Cycle is going on" <<std::endl;
    spin();
  }
  return true;
}

bool Telemetry::spin()
{
  mode.spin();
  data.spin();
  if (mode.getAbsPath().empty()) {
      return false;
  }

  mode.setData(data.getPreparedData(mode.getMode()));
  if(mode.isDataEmpty()) {
    return false;
  }
  string suffix = "/" + NameGen::instance().getName();
  NameGen::instance().next();
  string path = mode.getAbsPath() + suffix;
  mode.write(path);

  std::this_thread::sleep_for(2000ms);
  return true;
}

bool Telemetry::stop()
{
  bDoProceed.store(false);
  return true;
}

/* **************       TelemetryAPP      ************** */
TelemetryAPP::TelemetryAPP()
{
  run();
}

void TelemetryAPP::run()
{
  telemetry.run();
}
