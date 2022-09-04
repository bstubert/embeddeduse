# Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

cmake_minimum_required(VERSION 3.19)

project(package_scanner_with_file_io)

find_package(Qt6 REQUIRED COMPONENTS Test Core)

#file(COPY projects/ DESTINATION projects)

add_executable(
    ${PROJECT_NAME}
    test_package_scanner_with_file_io.cpp
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

#target_include_directories(${PROJECT_NAME} PRIVATE )

target_link_libraries(
    ${PROJECT_NAME}
    Qt::Test Qt::Core
)

