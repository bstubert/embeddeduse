# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

project(testmockcanbus)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC on)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test)
find_package(Qt5SerialBus)

add_executable(
    ${PROJECT_NAME}
    testmockcanbus.cpp
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::SerialBus Qt5::Test
)
