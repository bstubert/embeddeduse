#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include <QtDebug>

#include "riverstyle.h"

class RiverStylePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    RiverStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;
};

RiverStylePlugin::RiverStylePlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
}

void RiverStylePlugin::registerTypes(const char *uri)
{
    qDebug() << "### Registering plugin: " << uri;
    qmlRegisterModule(uri, 1, 0);
    qmlRegisterUncreatableType<RiverStyle>(uri, 1, 0, "River", "Attached property River");
// qmlRegisterType(resolvedUrl(QStringLiteral("Button.qml")), uri, 1, 0, "Button");
}

#include "riverstyleplugin.moc"
