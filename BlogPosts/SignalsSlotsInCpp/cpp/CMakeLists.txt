cmake_minimum_required(VERSION 3.14)

project(SignalsSlotsInCpp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME}
  main.cpp
  ClimateModel.cpp
  ClimateEcuTwin.cpp
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
