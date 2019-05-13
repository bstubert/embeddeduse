// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cansimulator.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("ecu");
    QGuiApplication app(argc, argv);

    CanSimulator simulator;

    auto engine = new QQmlApplicationEngine(&app);
    engine->rootContext()->setContextProperty("gSimulator", &simulator);
    engine->load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
