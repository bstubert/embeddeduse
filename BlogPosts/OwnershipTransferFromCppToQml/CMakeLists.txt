# Copyright (C) 2020, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(OwnershipTransferFromCppToQml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_VERBOSE_MAKEFILE true)

find_package(Qt5Gui)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    Customer.h
    CustomerManager.h
    qml.qrc
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Gui Qt5::Qml Qt5::Quick
)

