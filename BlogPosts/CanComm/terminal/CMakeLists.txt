# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(terminal)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Gui)
find_package(Qt5Qml)
find_package(Qt5Quick)
find_package(Qt5SerialBus)

add_executable(
  ${PROJECT_NAME}
  body_controller_proxy.cpp
  ecuproxy.cpp
  main.cpp
  terminalmodel.cpp
  transmission_proxy.cpp

  main.qml
  qml.qrc
)

target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Qml Qt5::Quick EmUse::ecucan)
