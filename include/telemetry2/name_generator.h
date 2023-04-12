//! @file telemetry2/name_generator.h
//! @brief Класс для генерации имен файлов (JSON + Image)
//! @author alpatikov_i
//! @date 12.07.2021

#pragma once

#include <string>
#include <ios>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>

//!  @addtogroup telemetry2
//!  @{
namespace telemetry2
{
//! @class NameGen
//! @brief Класс для генерации имен файлов (JSON + Image)
class NameGen
{
private:
  //! @brief Конструктор класса NameGen
  NameGen() = default;

public:
  //! @brief Получить имя
  //! @return имя в формате строки
  std::string getName() const;

  //! @brief Получить порядковый номер
  //! @return Порядковый номер в формате строки
  const std::string getSubSCount() { return std::to_string(sub_s_count); }
  //! @brief Инкрементно увеличить основной счетчик
  void next();
  //! @brief Инкрементно увеличить дополнительный счетчик.
  //!        Используется только в режиме серии
  void nextSubSerial();
  //! @brief Сбросить дополнительный счетчик
  void resetSubSerialCounter();

  //! @brief Метод получения синглтона
  //! @return экземпляр синглтона
  static NameGen& instance()
  {
    static NameGen ng;
    return ng;
  }

private:
  //! @brief Основной счётчик
  int64_t s_count = 0;
  //! @brief Дополнительный счётчик
  int64_t sub_s_count = 0;
};
} // namespace telemetry2
//! @} End of telemetry2
