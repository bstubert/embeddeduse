# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(CanComm)

set(CMAKE_VERBOSE_MAKEFILE true)

add_subdirectory(mockcanutils)
add_subdirectory(canbus)
add_subdirectory(canbusext)
add_subdirectory(ecucan)
add_subdirectory(ecu)
add_subdirectory(terminal)
add_subdirectory(test)

