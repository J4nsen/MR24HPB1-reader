cmake_minimum_required(VERSION 3.14)

project(MR24HPB1-reader LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core SerialPort REQUIRED)

add_executable(MR24HPB1-reader
  main.cpp
  serialreader.h serialreader.cpp
  radarframe.h radarframe.cpp
)
target_link_libraries(MR24HPB1-reader Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialPort)
