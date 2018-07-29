// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "Customer.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<Customer>("Customer.Models", 1, 0, "Customer");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
