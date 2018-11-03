TARGET = riverstyleplugin
TEMPLATE = lib
CONFIG += plugin
QT += qml

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    riverstyleplugin.cpp

#HEADERS += \

OTHER_FILES += \
    imports/RiverStyle/qmldir \
    imports/RiverStyle/riverstyle.qmltypes

RUN_PATH = ../../run/imports/RiverStyle
qml.files = $$OTHER_FILES
qml.path = $$RUN_PATH
target.path = $$RUN_PATH
INSTALLS += target qml
