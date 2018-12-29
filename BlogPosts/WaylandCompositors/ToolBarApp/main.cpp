#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QUrl>

#include "ApplicationManagerClient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    ApplicationManagerClient appMgr;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gAppMgr", &appMgr);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}
