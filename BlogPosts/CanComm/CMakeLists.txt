# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.5)

project(CanComm)

#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

set(CMAKE_VERBOSE_MAKEFILE true)

add_subdirectory(ecucan)
add_subdirectory(ecu)
add_subdirectory(terminal)

