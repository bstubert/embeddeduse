# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(ecucan)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core)
find_package(Qt5SerialBus)

add_library(
    ${PROJECT_NAME} STATIC
    canbus.cpp
    canbus.h
    canbusrouter.cpp
    canbusrouter.h
    ecubase.cpp
    ecubase.h
    can_frame_cache.cpp
    can_frame_cache.h
)

add_library(EmUse::ecucan ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::SerialBus)


