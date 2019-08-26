QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = compare_floats
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    test_compare_floats.cpp
