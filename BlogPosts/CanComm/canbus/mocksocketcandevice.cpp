// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>

#include "mocksocketcandevice.h"

MockSocketCanDevice::MockSocketCanDevice(const QString &name)
    : m_interface{name}
{
}

MockSocketCanDevice::~MockSocketCanDevice()
{
    close();
}

bool MockSocketCanDevice::open()
{
    const auto &interfaces = MockSocketCanDevice::interfaces();
    auto pos = std::find_if(interfaces.cbegin(), interfaces.cend(),
                            [this](const QCanBusDeviceInfo &info) {
                                return info.name() == m_interface;
                            });
    if (pos == interfaces.cend()) {
        close();
        return false;
    }
    setState(QCanBusDevice::ConnectedState);
    return true;
}

void MockSocketCanDevice::close()
{
    setState(QCanBusDevice::UnconnectedState);
}

void MockSocketCanDevice::setConfigurationParameter(int key, const QVariant &value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
}

bool MockSocketCanDevice::writeFrame(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
    emit framesWritten(1);
    return true;
}

QString MockSocketCanDevice::interpretErrorFrame(const QCanBusFrame &errorFrame)
{
    Q_UNUSED(errorFrame)
    return {};
}

QList<QCanBusDeviceInfo> MockSocketCanDevice::interfaces()
{
    QList<QCanBusDeviceInfo> result;
    result.append(createDeviceInfo("mcan0"));
    result.append(createDeviceInfo("mcan1"));
    return result;
}

