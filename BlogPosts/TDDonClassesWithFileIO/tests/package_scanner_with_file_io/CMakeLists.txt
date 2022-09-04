# Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

cmake_minimum_required(VERSION 3.19)

project(package_scanner_with_file_io)

find_package(Qt6 REQUIRED COMPONENTS Test Core)

file(COPY files/ DESTINATION files)

add_executable(
    ${PROJECT_NAME}
    test_package_scanner_with_file_io.cpp
    ../../sources/package_scanner.cpp
    ../../sources/package_info.cpp
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../../sources)

target_link_libraries(
    ${PROJECT_NAME}
    Qt6::Test Qt6::Core
)

