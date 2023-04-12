//! @file telemetry2/mode.h
//! @brief Класс для описания режимов отписывания телеметрии
//! @author alpatikov_aa
//! @date 10.04.2023

#pragma once

#include <telemetry2/telemetry_struct.h>

#include <atomic>
#include <chrono>
#include <map>
#include <memory>
#include <vector>

//!  @addtogroup telemetry2
//!  @{
namespace telemetry2
{
//! @brief Режимы отписывания телеметрии
enum class MODE
{
  TRIGGER,  //!< 0 Одиночное отписывание по событию
  RARE,     //!< 1 Разреженное отписывание
  COMPLETE  //!< 2 Отписывание всех данных
};

//! @class ModeManager
//! @brief Класс для управления режимами отписывания телеметрии
class ModeManager
{
public:
  //! @brief Конструктор класса ModeManager
  ModeManager() = default;
  //! @brief Деструктор класса ModeManager
  ~ModeManager() = default;

  // TODO: Реализовать сложную логику переключения режимов работы, мб FSM
  //! @brief Единожды прогоняет итерацию ModeManager
  //! @retval true - функция завершена корректно.
  bool spin();
  //! @brief Отписывает телеметрию
  //! @param[in] path - путь, по которому телеметрия будет отписана
  //! @retval true - функция завершена корректно
  bool write(const std::string & path);

  //! @brief Сменить режим отписывания телеметрии
  //! @param[in] newMode - новый режим отписывания
  void changeMode(MODE newMode) { currentMode = newMode; }
  //! @brief Возвращает текущий режим работы
  //! @return Текущий режим отписывания
  MODE getMode() const { return currentMode; }
  //! @brief Получение абсолютного пути
  //! @return Абсолютный путь
  const std::string &getAbsPath() const { return absPathJSON; }
  //! @brief Проверяет, пустая ли data
  //! @retval true - data is empty
  //! @retval false - data is not empty
  bool isDataEmpty() { return data.empty(); }
  //! @brief Присвоить data значение очередного кортежа телеметрии
  //! @param[in] newData - новое значение data
  void setData(const std::vector<std::shared_ptr<BaseMessage>> newData) { data = newData; }
  //! @brief Обновить значение absPathJSON.
  //! @param[in] newAbsPathJSON - новое значение absPathJSON.
  void setAbsPath(const std::string &newAbsPathJSON) { absPathJSON = newAbsPathJSON; }

private:
  //! @brief Отписывание одиночного кортежа телеметрии
  //! @param[in] path - путь, по которому будет отписана телеметрия
  void triggerMode(const std::string& path);
  //! @brief Разреженное отписывание телеметрии
  //! @param[in] path - путь, по которому будет отписана телеметрия
  void rareMode(const std::string& path);
  //! @brief Стандартное отписывание телеметрии
  //!        (по умолчанию для комбайна)
  //! @param[in] path - путь, по которому будет отписана телеметрия
  void harvMode(const std::string& path);
  //! @brief Отписывание всех данных телеметрии
  //! @param[in] path - путь, по которому будет отписана телеметрия
  void completeMode(const std::string& path);
  //! @brief Отписывание телеметрии для зернового терминала
  //! @param[in] path - путь, по которому будет отписана телеметрия
  void grainMode(const std::string& path);
  //! @brief Выбор режима отписывания
  //!        Автоматически меняет режимы работы при необходимости
  //! @param[in] dbwSpeed - feedback от dbw по скорости
  void modeSelector(const double dbwSpeed);

  //! @brief Текущий режим работы
  std::atomic<MODE> currentMode = {MODE::COMPLETE};
  //! @brief Атомарный флаг возобновления движения комбайном
  std::atomic_bool awakeness = {false};
  //! @brief Атомарный флаг события
  std::atomic_bool event = {false};

  //! @brief Время между отписываниями изображений / серий изображений
  std::chrono::seconds photoTimeWait;
  //! @brief Время между отписываниями телеметрии (gps & settings, etc.)
  std::chrono::seconds telemetryTimeWait;
  //! @brief Абсолютный путь отписывания JSON
  std::string absPathJSON;
  //! @brief Контейнер хранения данных
  std::vector<std::shared_ptr<BaseMessage>> data;
}; // class ModeManager
}  // namespace telemetry2
//! @} End of telemetry2
