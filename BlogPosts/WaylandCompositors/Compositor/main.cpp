#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>

#include "ApplicationManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    ApplicationManager appMgr;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gAppMgr", &appMgr);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}
