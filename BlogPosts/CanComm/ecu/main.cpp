// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ecumodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("ecu");
    QGuiApplication app(argc, argv);

    EcuModel model;

    auto engine = new QQmlApplicationEngine(&app);
    engine->rootContext()->setContextProperty("gEcu", &model);
    engine->load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
