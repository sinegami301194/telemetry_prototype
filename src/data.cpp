//кодировка=utf-8
#include <telemetry2/data.h>
#include <memory>
#include <vector>

using namespace std;
using namespace telemetry2;

DataManager::DataManager()
{
  count.push({4.3, 55.78891703716324, 37.592360619874555, 1, 5});
  count.push({4.3, 55.789520254169425, 37.59158814368159, 1, 5});
  count.push({4.3, 55.7902079101623, 37.59081566748864, 1, 5});
  count.push({4.3, 55.79117302090513, 37.589914445263524, 1, 5});
  count.push({4.3, 55.79143842216723, 37.59032214103203, 1, 5});
  count.push({4.3, 55.79161937653641, 37.59182417807389, 1, 5});
  count.push({4.3, 55.79177620297632, 37.592832688659136, 1, 5});
  count.push({4.3, 55.7918727112409, 37.594098691308695, 1, 5});
  count.push({4.3, 55.79206572705268, 37.595600728350554, 1, 5});
  count.push({4.3, 55.792222551695446, 37.597167138408494, 1, 5});
  count.push({4.3, 55.79237937570682, 37.598819379154534, 1, 5});
  count.push({4.3, 55.79223461510336, 37.59933436328318, 1, 5});
  count.push({4.3, 55.79137810385737, 37.599613313019525, 1, 5});
  count.push({4.3, 55.790774915621256, 37.59978497439573, 1, 5});
  count.push({4.3, 55.790557765569616, 37.59884083682657, 1, 5});
  count.push({4.3, 55.79041299819598, 37.598197106665765, 1, 5});
  count.push({4.3, 55.79011139777283, 37.596888188672146, 1, 5});
  count.push({4.3, 55.78974947418256, 37.5955578130065, 1, 5});
  count.push({4.3, 55.78962883223851, 37.59512865956597, 1, 5});
  count.push({4.3, 55.7892080078411, 37.59364060227749, 1, 5});
  count.push({4.3, 55.789122022879155, 37.593363411388566, 1, 5});
  count.push({4.3, 55.78881569990967, 37.592178181380746, 1, 5});
}

bool DataManager::run()
{
  m_do_continue.store(true);
  while (do_continue()) {
    spin();
  }
  return true;
}

bool DataManager::spin()
{
  feed();
  return true;
}

bool DataManager::stop()
{
  m_do_continue.store(false);
  return true;
}

bool DataManager::do_continue()
{
  return m_do_continue.load();
}

std::vector<std::shared_ptr<BaseMessage>>
DataManager::getPreparedData(MODE currentMode)
{
  switch (currentMode) {
  case MODE::TRIGGER:
    return getUsualVec();
  case MODE::RARE:
    return getUsualVec();
  case MODE::COMPLETE:
    return getUsualVec();
  default:
    break;
  }
  return {};
}

tz DataManager::parcer()
{
  tz parced = count.front();
  count.push(count.front());
  count.pop();
  return parced;
}

bool DataManager::feed()
{
  tz temp = parcer();
  std::cout<<"tz temp = parcer()"<<std::endl;

  // Формирование структуры Settings
  feedSettings();
  // Формирование структуры GPS
  feedGPS(temp.gps_speed, temp.lat, temp.lon, temp.yaw);
  return true;
}

bool DataManager::feedSettings()
{
  Settings s_b = mTF.fill();
  data->settings_buf = s_b;
  return true;
}

bool DataManager::feedGPS(double gps_speed, double lat, double lon, double yaw)
{
  GPS g_b = mTF.fill(gps_speed, lat, lon, yaw);
  data->gps_buf = g_b;
  return true;
}

std::vector<std::shared_ptr<BaseMessage>> DataManager::getUsualVec() {
  std::vector<std::shared_ptr<BaseMessage>> vec = {};
  if (data == nullptr) {
    return {};
  }
  if(data->gps_buf.has_value())
  {
    auto gps = std::make_shared<GPS>(std::move(data->gps_buf.value()));
    vec.push_back(std::move(gps));
    data->gps_buf = std::nullopt;
  }
  if(data->settings_buf.has_value())
  {
    auto settings = std::make_shared<Settings>(std::move(data->settings_buf.value()));
    vec.push_back(std::move(settings));
    data->settings_buf = std::nullopt;
  }
  return vec;
}
