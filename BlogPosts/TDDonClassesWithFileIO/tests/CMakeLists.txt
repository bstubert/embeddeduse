# Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.19)

project(tests)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(package_scanner_with_file_io)
endif()
