// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("terminal");
    QGuiApplication app(argc, argv);

    auto engine = new QQmlApplicationEngine(&app);
    engine->load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
