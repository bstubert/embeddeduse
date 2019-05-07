// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QtDebug>
#include <QtEndian>
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
    connect(m_canBusDevice.get(), &QCanBusDevice::errorOccurred,
            this, &EcuProxy::onErrorOccurred);
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
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    QCanBusFrame frame(0x18ef0201U, payload);
    m_canBusDevice->writeFrame(frame);

//    auto value = QRandomGenerator::global()->generate();
//    emit parameterRead(pid, value);
}

void EcuProxy::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    emit errorMessage(QString("ERROR: %1 (%2).").arg(m_canBusDevice->errorString()).arg(error));
}
