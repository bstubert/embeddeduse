#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<MainModel>("com.embeddeduse.models", 1, 0, "MainModel");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}
