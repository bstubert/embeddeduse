# Copyright (C) 2020, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(SimpleApp)

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

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../staging/kea)

install(TARGETS ${PROJECT_NAME} RUNTIME
    DESTINATION bin)

set(qt_base_dir ${Qt5Core_DIR}/../../..)
install(DIRECTORY ${qt_base_dir}/lib ${qt_base_dir}/phrasebooks
    ${qt_base_dir}/plugins ${qt_base_dir}/qml ${qt_base_dir}/translations
    DESTINATION qt USE_SOURCE_PERMISSIONS)
