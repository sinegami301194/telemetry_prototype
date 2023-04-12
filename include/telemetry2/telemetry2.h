//! @file telemetry2/telemetry_app.h
//! @brief Класс для отписывания телеметрии + приложение
//!        Ссылка на руководство по добавлению новой телеметрии:
//!        https://confluence.cognitivepilot.com/pages/viewpage.action?pageId=85035312
//! @author alpatikov_i
//! @date 10.10.2022

#pragma once

#include <telemetry2/data.h>

#include <iosfwd>
#include <string>
#include <variant>
#include <unordered_map>

//!  @addtogroup telemetry2
//!  @{

namespace telemetry2
{
//! @class Telemetry
//! @brief Среда работы модуля телеметрии. Управляет конфигурацией и времением жизни.
class Telemetry
{
public:
  //! @brief Конструктор класса Telemetry.
  //!        Если произошли ошибки в инициализации - exception
  Telemetry();
  //! @brief Деструктор класса Telemetry.
  ~Telemetry() = default;

  //! @brief Проверка состояния bDoProceed
  //! @retval true - продолжать работу
  //! @retval false - завершить работу
  bool doProceed() const {return bDoProceed.load();}

  //! @brief Запускает непрерывную работу модуля. Аналог функции spin() в ROS.
  //! @retval true - функция завершена.
  bool run();

  //! @brief Прокрутить 1 раз.
  //! @retval true - функция завершена корректно.
  //! @retval false - данные от shooterClient пришли пустыми.
  bool spin();

  //! @brief Запрос на остановку DataManager. Останавливает run.
  //! @retval true - функция завершена корректно.
  bool stop();

  //! @brief Предоставляет доступ к private InitialSettings
  //! @return Начальные настройки
  const InitialSettings & getInitialSettings() const { return settings; }

private:
  //! @brief Флаг продолжения работы
  std::atomic_bool bDoProceed{true};
  //! @brief Модуль работы с данными
  DataManager data;
  //! @brief Стартовые настройки телеметрии
  InitialSettings settings;
  //! @brief Модуль управления режимами отписывания телеметрии
  ModeManager mode;
};


//! @class TelemetryAPP
//! @brief Приложение для кручения телеметрии
class TelemetryAPP
{
public:
  //! @brief конструктор telemetry_app
  TelemetryAPP();

  //! @brief Запускает работу TelemetryAPP.
  void run();

private:
  //! @brief Предварительная инициализация системы
  Telemetry telemetry;
};
} // namespace telemetry2
//! @} End of telemetry2
