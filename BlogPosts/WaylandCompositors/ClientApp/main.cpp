#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QUrl>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto color = QString{"magenta"};
    auto args = QGuiApplication::arguments();
    if (args.size() >= 2) {
        color = args[1];
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backgroundColor", color);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}
