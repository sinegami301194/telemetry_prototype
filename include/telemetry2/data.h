//! @file telemetry2/data.h
//! @brief Класс для хранения и работы с данными
//! @author alpatikov_aa
//! @date 10.04.2023

#pragma once

#include <telemetry2/message_telemetry_filler.h>
#include <queue>

//!  @addtogroup telemetry2
//!  @{
namespace telemetry2
{
//! @struct Data
//! @brief Структура для хранения кортежа телеметрии
//!        (Буферов для хранения данных)
struct Data
{
  //! @brief Данные GPS
  std::optional<GPS> gps_buf;
  //! @brief Данные с настройками
  std::optional<Settings> settings_buf;
};

struct tz
{
  //! @brief Скорость по GPS
  double gps_speed = 0;
  //! @brief Широта, nord
  double lat = 0;
  //! @brief Долгота, east
  double lon = 0;
  //! @brief Рысканье
  double yaw = 0;
  //! @brief Заданная скорость
  double reference_speed = 5;
};

//! @class DataManager
//! @brief Модуль работы с данными
class DataManager
{
public:
  //! @brief Конструктор класса DataManager
  DataManager();
  //! @brief Деструктор класса DataManager
  ~DataManager() = default;

  tz parcer();
  //! @brief Запускает работу DataManager.
  //! @retval true - функция завершена.
  bool run();
  //! @brief Прокрутить 1 раз.
  //! @retval true - функция завершена корректно.
  //! @retval false - данные от shooterClient пришли пустыми.
  bool spin();
  //! @brief Запрос на остановку DataManager. Останавливает run.
  //! @retval true - функция завершена корректно.
  bool stop();
  //! @brief Проверка состояния m_do_continue
  //! @retval true - продолжать работу
  //! @retval false - завершить работу
  bool do_continue();
  //! @brief Вернуть подготовленные данные
  //! @param[in] currentMode - текущий режим работы
  //! @return Возвращает контейнер с подготовленными данными
  std::vector<std::shared_ptr<BaseMessage>> getPreparedData(MODE currentMode);

  //! @brief "Кормление" модулей телеметрии
  //! @retval true - функция завершена корректно.
  bool feed();

  //! @brief Установка начальных настроек
  //! @param[in] newInitSet - новые начальные настройки
  void setInitialSettings(const InitialSettings& newInitSet) { initialSettings = newInitSet; }

private:
  //! @brief "Кормление" Data данными Settings
  //! @retval true - функция завершена корректно.
  bool feedSettings();

  //! @brief "Кормление" Data данными GPS
  //! @retval true - функция завершена корректно.
  bool feedGPS(double gps_speed, double lat, double lon, double yaw);

  //! @brief "Кормление" Data данными изображениями
  //! @retval true - функция завершена корректно.
  bool feedImage();
  //! @brief Подготовка изображения
  //! @param[in] ptrImageFrame - фрейм с изображением
  //! @param[in] cam_type - тип камеры
  //! @retval true - функция завершена корректно.
  bool prepareImage();
  //! @brief Получить контейнер с данными "по-умолчанию".
  //! @return контейнер с данными "по-умолчанию".
  std::vector<std::shared_ptr<BaseMessage>> getUsualVec();

  //! @brief Контейнер для хранения кортежа телеметрии
  std::shared_ptr<Data> data = std::make_shared<Data>();
  //! @brief Экземпляр класса для формирования и заполнения структур телеметрии
  MessageTelemetryFiller mTF;
  //! @brief Стартовые настройки телеметрии
  InitialSettings initialSettings;
  //! @brief Атомарный флаг статуса работы
  std::atomic_bool m_do_continue;
  static inline std::queue<tz> count{};
}; // class DataManager
}  // namespace telemetry2
//! @} End of telemetry2
