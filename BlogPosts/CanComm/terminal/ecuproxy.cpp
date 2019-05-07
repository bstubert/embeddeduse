// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QRandomGenerator>
#include <QtDebug>
#include "ecuproxy.h"

// sudo ip link set can0 up type can bitrate 250000
// sudo ip link set can0 txqueuelen 128

EcuProxy::EcuProxy(const QString &pluginName, const QString &canBusName, QObject *parent)
    : QObject{parent}
{
    m_canBusDevice.reset(QCanBus::instance()->createDevice(pluginName, canBusName));
    if (m_canBusDevice == nullptr || !m_canBusDevice->connectDevice()) {
        return;
    }
}

EcuProxy::~EcuProxy()
{
    if (isConnected()) {
        m_canBusDevice->disconnectDevice();
    }
}

bool EcuProxy::isConnected() const
{
    return m_canBusDevice != nullptr && m_canBusDevice->state() == QCanBusDevice::ConnectedState;
}

void EcuProxy::readParameter(quint16 pid)
{
    emit parameterRead(pid, QRandomGenerator::global()->generate());
}
