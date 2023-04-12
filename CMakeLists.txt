cmake_minimum_required(VERSION 3.17)
project(telemetry)

set(CMAKE_CXX_STANDARD 17)         #будет работать на MSVC 2015 update 3 и более свежих
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)      #что бы выключить стандарты вида gnu++17

set(HEADERS
  include/telemetry2/data.h
  include/telemetry2/message_telemetry_filler.h
  include/telemetry2/mode.h
  include/telemetry2/name_generator.h
  include/telemetry2/telemetry2.h
  include/telemetry2/telemetry_struct.h
)
set(SOURCES
  src/data.cpp
  src/message_telemetry_filler.cpp
  src/mode.cpp
  src/name_generator.cpp
  src/telemetry2.cpp
  src/telemetry_struct.cpp
)

add_library(telemetry2 ${HEADERS} ${SOURCES})
target_include_directories(telemetry2 PUBLIC ./include)

set(thirdparty_modules
  json-cpp
)
list(APPEND thirdparty_modules)
add_subdirectory(thirdparty)

target_link_libraries(telemetry2 json-cpp)

add_executable(telemetry_app src/telemetry_app.cpp)
target_link_libraries(telemetry_app telemetry2)
