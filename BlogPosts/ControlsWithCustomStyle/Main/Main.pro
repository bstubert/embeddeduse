QT += qml quick quickcontrols2
CONFIG += c++11
#CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

#osx {
#    riverstyle.files = $$OUT_PWD/run/import/RiverStyle
#    riverstyle.path = Contents/PlugIns
#    QMAKE_BUNDLE_DATA += riverstyle
#}

SOURCES += \
        main.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH = ../RiverStyle/imports

target.path = ../../run
INSTALLS += target
