QT += gui qml quick

SOURCES += \
    main.cpp \
    ApplicationManager.cpp \
    ApplicationSourceModel.cpp \
    TopApplicationModel.cpp \
    RunningApplicationModel.cpp

OTHER_FILES = \
    main.qml \
    ApplicationItem.qml

RESOURCES += qml.qrc

HEADERS += \
    ApplicationManager.h \
    ApplicationSourceModel.h \
    TopApplicationModel.h \
    RunningApplicationModel.h


