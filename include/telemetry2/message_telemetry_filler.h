//! @file telemetry2/message_telemetry_filler.h
//! @brief Класс для формирования и заполнения структур телеметрии
//! @author alpatikov_aa
//! @date 10.04.2023

#pragma once

#include <telemetry2/mode.h>
#include <string>

//!  @addtogroup telemetry2
//!  @{
namespace telemetry2
{
//! @class MessageTelemetryFiller
//! @brief Класс для формирования и заполнения структур телеметрии
class MessageTelemetryFiller
{
public:
  //! @brief Конструктор класса MessageTelemetryFiller
  MessageTelemetryFiller();

  //! @brief Заполнение структуры GPS.
  //! @return заполненная структура типа GPS
  GPS fill(double gps_speed, double lat, double lon, double yaw) const;

  //! @brief Заполнение структуры Settings.
  //! @return заполненная структура типа Settings
  Settings fill() const;

  //! @brief Получение года.
  //! @return год в int
  int getYear() const { return year; }

  //! @brief Получение месяца.
  //! @return месяц в int
  int getMonth() const { return month; }

  //! @brief Получение дня.
  //! @return день в int
  int getDay() const { return day; }

  //! @brief Получение абсолютного пути.
  //! @return абсолютный путь в формате строки
  const std::string &getAbsPath() const { return absPathJSON; }

  //! @brief Получение DeviceId.
  //! @return device id в формате строки
  std::string getDeviceId() const;

  //! @brief Получение имени фрейма.
  //! @return имя фрейма в формате строки
  const std::string &getFrameName() const { return frameName; }

  //! @brief Обновить значение year.
  //! @param[in] new_year - новое значение year.
  void setYear(const int new_year) { year = new_year; }

  //! @brief Обновить значение month.
  //! @param[in] new_month - новое значение month.
  void setMonth(const int new_month) { month = new_month; }

  //! @brief Обновить значение day.
  //! @param[in] new_day - новое значение day.
  void setDay(const int new_day) { day = new_day; }


  //! @brief Обновить значение absPathJSON.
  //! @param[in] newAbsPathJSON - новое значение absPathJSON.
  void setAbsPath(const std::string &newAbsPathJSON) { absPathJSON = newAbsPathJSON; }

  //! @brief Обновить значение frameName.
  //! @param[in] newFrameName - новое значение frameName.
  void setFrameName(const std::string &newFrameName) { frameName = newFrameName; }

  //! @brief Проверка состояния комбайна на остановку.
  //! @param[in] new_dbw_speed - значение скорости по dbw.
  //! @retval true - комбайн стоит.
  //! @retval false - комбайн в движении
  static bool isHarvesterStopped(const double new_dbw_speed);

private:
  int year;  //!< @brief год
  int month; //!< @brief месяц
  int day;   //!< @brief день
  std::string absPathJSON; //!< @brief абсолютный путь
  std::string frameName;   //!< @brief имя фрейма
};
}  // namespace telemetry2
//! @} End of telemetry2
