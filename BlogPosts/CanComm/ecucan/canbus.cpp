// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QCanBusDevice>
#include <QString>
#include "canbus.h"

namespace CanBus
{
QCanBusDevice *setUp(const QString &plugin, const QString &interface, QString &errorStr)
{
    auto device = QCanBus::instance()->createDevice(plugin, interface, &errorStr);
    if (device != nullptr && !device->connectDevice()) {
        errorStr = device->errorString();
    }
    return device;
}

void tearDown(QCanBusDevice *device)
{
    if (device != nullptr && device->state() == QCanBusDevice::ConnectedState) {
        device->disconnectDevice();
    }
}
}
