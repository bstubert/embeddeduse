// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "Model.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<Model>("MyModels", 1, 0, "Model");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
