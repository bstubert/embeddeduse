TARGET = riverstyleplugin
TEMPLATE = lib
CONFIG += plugin
QT += qml

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    riverstyleplugin.cpp

QML_CONTROLS_PATH = imports/EmbeddedUse/Controls/River

OTHER_FILES += \
    $${QML_CONTROLS_PATH}/qmldir \
    $${QML_CONTROLS_PATH}/riverstyle.qmltypes

RUN_PATH = ../../run/$${QML_CONTROLS_PATH}
qml.files = $$OTHER_FILES
qml.path = $$RUN_PATH
target.path = $$RUN_PATH
INSTALLS += target qml
