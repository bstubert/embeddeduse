QT += qml quick remoteobjects
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    ApplicationManagerClient.cpp

REPC_REPLICA = ../Common/ApplicationService.rep

RESOURCES += qml.qrc

HEADERS += \
    ApplicationManagerClient.h

