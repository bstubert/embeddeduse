#include <QGuiApplication>
#include <QMetaType>
#include <QQmlApplicationEngine>
#include "mainmodel.h"
#include "qmlenums.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<MainModel>("com.embeddeduse.models", 1, 0, "MainModel");
//    qmlRegisterType<WarningLevel>("com.embeddeduse.models", 1, 0, "WarningLevel");
    qmlRegisterUncreatableType<WarningLevel>("com.embeddeduse.models", 1, 0, "WarningLevel",
                                             "Cannot create WarningLevel in QML");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}
