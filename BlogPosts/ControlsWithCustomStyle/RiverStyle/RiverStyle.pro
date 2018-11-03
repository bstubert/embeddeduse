TARGET = riverstyleplugin
TEMPLATE = lib
CONFIG += plugin
QT += qml

DESTDIR = imports/RiverStyle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    riverstyleplugin.cpp

#HEADERS += \

OTHER_FILES += \
    imports/RiverStyle/qmldir

qml.files = $$OTHER_FILES
qml.path = ../../run/imports/RiverStyle
target.path = ../../run/imports/RiverStyle
INSTALLS += target qml
