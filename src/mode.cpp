//кодировка=utf-8
#include <telemetry2/mode.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace telemetry2;

bool ModeManager::spin()
{
  currentMode = MODE::COMPLETE;
  return true;
}
bool ModeManager::write(const string& path)
{
  switch(currentMode)
  {
    case MODE::TRIGGER :
      triggerMode(path);
      break;
    case MODE::COMPLETE:
      completeMode(path);
      break;
    default : break;
  }
  return true;
}

void ModeManager::triggerMode(const std::string &path)
{
  if (event) {
    harvMode(path);
    event = false;
  }
}


void ModeManager::harvMode(const std::string &path)
{
  for (size_t i = 0; i < data.size(); i++) {
      data[i]->write(path);
      data[i].reset();
  }
  std::this_thread::sleep_for(2000ms);
}

void ModeManager::completeMode(const std::string& path)
{
  harvMode(path);
}

void ModeManager::grainMode(const std::string &path)
{
  harvMode(path);
}

