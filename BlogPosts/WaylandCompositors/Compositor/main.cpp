#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "applicationmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<ApplicationManager>("EmbeddedUse.Models", 1, 0, "ApplicationManager");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}
