QT += qml quick remoteobjects
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    ../Common/Application.h \
    ApplicationManagerClient.h

SOURCES += main.cpp \
    ApplicationManagerClient.cpp

REPC_REPLICA = ../Common/ApplicationManager.rep

RESOURCES += qml.qrc

