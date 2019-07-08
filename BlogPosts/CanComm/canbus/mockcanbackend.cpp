// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>

#include "mockcanbackend.h"

MockCanBackend::MockCanBackend(const QString &name)
    : m_interface{name}
{
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
    const auto &interfaces = MockCanBackend::interfaces();
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

void MockCanBackend::close()
{
    setState(QCanBusDevice::UnconnectedState);
}

void MockCanBackend::setConfigurationParameter(int key, const QVariant &value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
}

bool MockCanBackend::writeFrame(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
    emit framesWritten(1);
    return true;
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

