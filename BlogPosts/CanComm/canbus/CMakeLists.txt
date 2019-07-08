# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(canbus)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core)
find_package(Qt5SerialBus)

add_library(
    ${PROJECT_NAME} MODULE
    main.cpp
    mocksocketcandevice.cpp
    mocksocketcandevice.h
)

#add_library(EmUse::mockcan ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::SerialBus)


