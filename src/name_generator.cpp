//кодировка=utf-8
#include <telemetry2/name_generator.h>
#include <iomanip>
#include <sstream>

using namespace telemetry2;

std::string NameGen::getName() const
{
  std::stringstream ss;
  ss << std::setw(6) << std::setfill('0') << s_count;
  return ss.str();
}

void NameGen::next()
{
  ++s_count;
}

void NameGen::nextSubSerial()
{
  ++sub_s_count;
}

void NameGen::resetSubSerialCounter()
{
  sub_s_count = 0;
}
