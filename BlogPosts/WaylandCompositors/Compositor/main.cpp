#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectHost>
#include <QUrl>

#include "ApplicationManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApplicationManager appMgr;
    QRemoteObjectHost sourceNode{QUrl{QStringLiteral("local:applicationService")}};
    sourceNode.enableRemoting(&appMgr);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gAppMgr", &appMgr);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}
