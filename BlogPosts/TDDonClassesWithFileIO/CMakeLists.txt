# Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)
cmake_minimum_required(VERSION 3.19)

project(TDDonClassesWithFileIO LANGUAGES CXX)

include(CTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
