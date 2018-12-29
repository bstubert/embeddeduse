QT += gui qml quick remoteobjects

SOURCES += \
    main.cpp \
    ApplicationManager.cpp \
    ApplicationSourceModel.cpp

HEADERS += \
    ApplicationManager.h \
    ApplicationSourceModel.h

REPC_SOURCE = ../Common/ApplicationService.rep

OTHER_FILES = \
    main.qml \
    ApplicationItem.qml

RESOURCES += qml.qrc

