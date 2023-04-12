//! @file telemetry2/telemetry_struct.h
//! @brief Файл для определения структур, испульзуемых в telemetry
//! @author alpatikov_aa
//! @date 10.04.2023

#pragma once

#include <chrono>
#include <string>

#include <json/json.h>

//!  @addtogroup telemetry2
//!  @{

namespace telemetry2
{
//! @brief Дополнение однозначных чисел впереди стоящими нулями (0x).
//! @param[in] x - однозначное число
//! @retval Строка в формате (0x)
std::string fillNumZero(const int x);

//! @struct InitialSettings
//! @brief Стартовые настройки телеметрии
struct InitialSettings
{
  //! @brief количество картинок в серии
  int framesNumber = 3;
  //! @brief минимальное количество времени между подряд идущими изображениями, [c]
  std::chrono::seconds minInterval = std::chrono::seconds(0);
  //! @brief максимальное время для записи серии, [c]
  std::chrono::seconds maxInterval = std::chrono::seconds(3);
  //! @brief Имя левой камеры
  std::string photoLeftDeviceName = "leftImage";
  //! @brief Имя правой камеры
  std::string photoRightDeviceName = "rightImage";
  //! @brief Имя камеры зернового терминала
  std::string photoGrainDeviceName = "grainImage";
  //! @brief Флаг для записи серии картинок в серии
  bool photoEnableSerial = false;
  //! @brief Флаг включения таймера изображений
  bool enableTimer = true;
  //! @brief Флаг включения таймера телеметрии
  bool telemetryEnableTimer = true;
  //! @brief Имя GPS устройства
  std::string photoGnssName = "GpsdCapture";
  //! @brief Директория для отписывания телеметрии
  std::string dirPath_ = "/testdata/record/temp";
  //! @brief Поддиректория для отписывания телеметрии
  std::string shotsSubdir_ = "photos";
  //! @brief Время между отписываниями изображений / серий изображений, [c]
  std::chrono::seconds photoTimeWait = std::chrono::seconds(60);
  //! @brief Время между отписываниями телеметрии (gps & dbw & settings), [c]
  std::chrono::seconds telemetryTimeWait{4};
  //! @brief Расширение отписываемого изображения
  std::string image_type = "jpg";
  //! @brief Степень сжатия изображения в JPG
  int jpg_compression = 80;
  //! @brief Флаг, сигнализирующий о смене состояния PhotoShootState
  bool photoTimeFlag = false;
  //! @brief Флаг, сигнализирующий о смене состояния TelemetryShootState
  bool telemetryTimeFlag = false;
};

//! @brief Тип камеры
enum class CamType
{
  Left,    //!< 0 Левая камера
  Right    //!< 1 Правая камера
};

//! @struct JsonInfoHeader
//! @brief Структура для вынесения повторяющихся полей device_id
struct JsonInfoHeader
{
  //! @brief Конструктор JsonInfoHeader
  JsonInfoHeader() {}
  //! @brief Конструктор JsonInfoHeader
  //! @param[in] device_id - идентификационный номер девайса
  JsonInfoHeader(const std::string &device_id)
    : device_id(device_id)
  {}
  //! @brief Идентификационный номер девайса
  std::string device_id;
};

//! @struct BaseMessage
//! @brief Базовая структура
struct BaseMessage
{
  //! @brief Конструктор BaseMessage
  BaseMessage();
  //! @brief Деструктор BaseMessage
  virtual ~BaseMessage();
  //! @brief Сериализация базовой структуры в JSON-файл, заглушка для определения у наследников
  //! @param[in] absPath_part - путь для отписывания телеметрии
  //! @retval false - сериализация не проводится
  virtual bool write(const std::string& absPath_part) const;
  //! @brief Сериализация повторяющихся полей в JSON-файл
  //! @param[in] imageData - отписываемая информация
  //! @retval true - сериализация прошла успешно
  bool fillTheSameFields(Json::Value& data) const;

  //! @brief Тип телеметрии
  std::string type;
  //! @brief Экземпляр структуры для повторяющихся полей
  JsonInfoHeader jIH;
};

//! @struct GPS
//! @brief Структура GPS данных
struct GPS : BaseMessage
{
  //! @brief Конструктор GPS
  GPS() = delete;
  //! @brief Конструктор GPS
  //! @param[in] gps_speed - скорость по GPS
  //! @param[in] lat - широта
  //! @param[in] lon - долгота
  //! @param[in] yaw - рысканье
  //! @param[in] newJIH - экземпляр структуры для повторяющихся полей
  GPS(double gps_speed, double lat, double lon, double yaw,
      const JsonInfoHeader &newJIH)
    : gps_speed(gps_speed)
    , lat(lat)
    , lon(lon)
    , yaw(yaw)
  {
    jIH = newJIH;
    type = "gps";
  }
  //! @brief Деструктор GPS
  virtual ~GPS() override = default;

  //! @brief Скорость по GPS
  double gps_speed;
  //! @brief Широта, nord
  double lat;
  //! @brief Долгота, east
  double lon;
  //! @brief Рысканье
  double yaw;

  //! @brief Сериализация GPS структуры в JSON файл
  //! @param[in] absPath_part - путь для отписывания телеметрии
  //! @retval true - сериализация завершилась
  bool write(const std::string& absPath_part) const override;
};


//! @struct Settings
//! @brief Структура данных настроек комбайна
struct Settings : BaseMessage
{
  //!
  //! @brief Конструктор Settings
  Settings() = delete;
  //! @brief Конструктор Settings
  //! @param[in] reference_speed - заданная скорость
  //! @param[in] newJIH - экземпляр структуры для повторяющихся полей
  Settings(double reference_speed, const JsonInfoHeader &newJIH)
    : reference_speed(reference_speed)
  {
    jIH = newJIH;
    type = "settings";
  }
  //! @brief Деструктор Settings
  virtual ~Settings() override = default;
  //! @brief Заданная скорость
  double reference_speed;

  //! @brief Сериализация Settings структуры в JSON файл
  //! @param[in] absPath_part - путь для отписывания телеметрии
  //! @retval true - сериализация завершилась
  bool write(const std::string& absPath_part) const override;
};
} // telemetry2
//! @} End of telemetry2
