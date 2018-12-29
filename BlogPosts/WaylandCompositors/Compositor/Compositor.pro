QT += gui qml quick remoteobjects

SOURCES += \
    main.cpp \
    ApplicationSourceModel.cpp \
    ApplicationManagerService.cpp

HEADERS += \
    ApplicationSourceModel.h \
    ApplicationManagerService.h

REPC_SOURCE = ../Common/ApplicationManagerService.rep

OTHER_FILES = \
    main.qml \
    ApplicationItem.qml

RESOURCES += qml.qrc

