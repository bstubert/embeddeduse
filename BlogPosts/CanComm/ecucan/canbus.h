// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

class QCanBusDevice;
class QString;

namespace CanBus
{
QCanBusDevice *setUp(const QString &plugin, const QString &interface, QString &errorStr);
void tearDown(QCanBusDevice *device);
}
