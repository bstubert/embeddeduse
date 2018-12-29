QT += gui qml quick remoteobjects

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    ApplicationSourceModel.cpp \
    ApplicationManagerService.cpp

HEADERS += \
    ../Common/Application.h \
    ApplicationSourceModel.h \
    ApplicationManagerService.h

REPC_SOURCE = ../Common/ApplicationManager.rep

OTHER_FILES = \
    main.qml \
    ApplicationItem.qml

RESOURCES += qml.qrc

