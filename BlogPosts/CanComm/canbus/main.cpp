// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFactoryV2>
#include <QObject>

#include "mocksocketcandevice.h"

class MockCanBusPlugin : public QObject, public QCanBusFactoryV2
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactoryV2)

public:
    QList<QCanBusDeviceInfo> availableDevices(QString *errorMessage) const override
    {
        Q_UNUSED(errorMessage);
        return MockSocketCanDevice::interfaces();
    }

    QCanBusDevice *createDevice(const QString &interfaceName, QString *errorMessage) const override
    {
        Q_UNUSED(errorMessage);
        auto device = new MockSocketCanDevice(interfaceName);
        return device;
    }
};

#include "main.moc"
