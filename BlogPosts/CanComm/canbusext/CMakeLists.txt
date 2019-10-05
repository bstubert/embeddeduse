# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(canbusext)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core)
find_package(Qt5SerialBus)

add_library(
    ${PROJECT_NAME} STATIC
    canbusext.h
    j1939_broadcast_frames.h
    j1939_frame.cpp
)

add_library(EmUse::CanBusExt ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE .)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::SerialBus)


