// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QCanBusDevice>
#include <QMetaObject>
#include <QVariant>
#include <QtDebug>

#include "canbusrouter.h"

CanBusRouter::CanBusRouter(const QString &plugin, const QString &interface, QObject *parent)
    : QObject(parent)
{
    m_device = createDevice(plugin, interface);
    if (m_device == nullptr)
    {
        return;
    }
    connectToDevice();
    m_device->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, false);
    m_device->setConfigurationParameter(QCanBusDevice::LoopbackKey, false);
    connect(m_device, &QCanBusDevice::errorOccurred,
            this, &CanBusRouter::onErrorOccurred);
    connect(m_device, &QCanBusDevice::framesReceived,
            this, &CanBusRouter::framesReceived);
    connect(m_device, &QCanBusDevice::framesWritten,
            this, &CanBusRouter::framesWritten);
}

CanBusRouter::~CanBusRouter()
{
    disconnectFromDevice();
    delete m_device;
}

QCanBusDevice::CanBusError CanBusRouter::error() const
{
    return m_error;
}

QString CanBusRouter::errorString() const
{
    return m_errorStr;
}

QCanBusDevice::CanBusDeviceState CanBusRouter::state() const
{
    return m_state;
}

void CanBusRouter::writeFrame(const QCanBusFrame &frame)
{
    if (m_device == nullptr)
    {
        return;
    }
    m_device->writeFrame(frame);
}

void CanBusRouter::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    emit errorOccurred(error, m_device->errorString());
}

//void CanBusRouter::onFramesReceived()
//{
//    emit framesReceived(m_device->readAllFrames());
//}

// QCanBus::createDevice() returns nullptr and an error message, if the plugin does not exist.
// It returns a non-null QCanBusDevice, if the plugin exists. Whether the CAN interface exists,
// does not matter.
QCanBusDevice *CanBusRouter::createDevice(const QString &plugin, const QString &interface)
{
    auto device = QCanBus::instance()->createDevice(plugin, interface, &m_errorStr);
    if (!m_errorStr.isEmpty())
    {
        m_error = QCanBusDevice::CanBusError::ConnectionError;
    }
    return device;
}

void CanBusRouter::connectToDevice()
{
    if (m_device == nullptr)
    {
        return;
    }
    if (!m_device->connectDevice())
    {
        m_error = m_device->error();
        m_errorStr = m_device->errorString();
    }
    m_state = m_device->state();
}

void CanBusRouter::disconnectFromDevice()
{
    if (m_device == nullptr)
    {
        return;
    }
    if (m_device->state() == QCanBusDevice::ConnectedState)
    {
        m_device->disconnectDevice();
    }
}
