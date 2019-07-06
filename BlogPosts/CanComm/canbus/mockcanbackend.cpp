// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "mockcanbackend.h"

MockCanBackend::MockCanBackend(const QString &name)
{
    Q_UNUSED(name)
    resetConfigurations();
}

MockCanBackend::~MockCanBackend()
{
    close();
}

void MockCanBackend::resetConfigurations()
{
    QCanBusDevice::setConfigurationParameter(
                QCanBusDevice::LoopbackKey, true);
    QCanBusDevice::setConfigurationParameter(
                QCanBusDevice::ReceiveOwnKey, false);
    QCanBusDevice::setConfigurationParameter(
                QCanBusDevice::ErrorFilterKey,
                QVariant::fromValue(QCanBusFrame::FrameErrors(QCanBusFrame::AnyError)));
    QCanBusDevice::setConfigurationParameter(
                QCanBusDevice::CanFdKey, false);
}

bool MockCanBackend::open()
{
    setState(QCanBusDevice::ConnectedState);
    return true;
}

void MockCanBackend::close()
{
    setState(QCanBusDevice::UnconnectedState);
}

void MockCanBackend::setConfigurationParameter(int key, const QVariant &value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
}

bool MockCanBackend::writeFrame(const QCanBusFrame &newData)
{
    Q_UNUSED(newData)
    return false;
}

QString MockCanBackend::interpretErrorFrame(const QCanBusFrame &errorFrame)
{
    Q_UNUSED(errorFrame)
    return {};
}

QList<QCanBusDeviceInfo> MockCanBackend::interfaces()
{
    QList<QCanBusDeviceInfo> result;
    result.append(createDeviceInfo("mcan0"));
    result.append(createDeviceInfo("mcan1"));
    return result;
}

