// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "terminalmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("terminal");
    QGuiApplication app(argc, argv);

    TerminalModel model;

    auto engine = new QQmlApplicationEngine(&app);
    engine->rootContext()->setContextProperty("gTerminal", &model);
    engine->load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
