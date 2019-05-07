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
    connect(m_canBusDevice.get(), &QCanBusDevice::framesReceived,
            this, &EcuProxy::onFramesReceived);
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

bool EcuProxy::isReadParameterFrame(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

void EcuProxy::sendReadParameter(quint16 pid)
{
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    QCanBusFrame frame(0x18ef0201U, payload);
    emit logMessage(QString("T-Send: Read(%1)").arg(pid, 0, 16));
    m_canBusDevice->writeFrame(frame);
}

void EcuProxy::receiveReadParameter(const QCanBusFrame &frame)
{
    const auto &payload = frame.payload();
    auto pid = qFromLittleEndian<qint16>(payload.data() + 1);
    auto value = qFromLittleEndian<qint32>(payload.data() + 3);
    emit logMessage(QString("T-Recv: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                    .arg(quint32(value), 0, 16));
}

void EcuProxy::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    emit logMessage(QString("ERROR: %1 (%2).").arg(m_canBusDevice->errorString()).arg(error));
}

void EcuProxy::onFramesReceived()
{
    auto count = m_canBusDevice->framesAvailable();
    for (qint64 i = count; i > 0; --i) {
        auto frame = m_canBusDevice->readFrame();
        if (isReadParameterFrame(frame)) {
            receiveReadParameter(frame);
        }
    }
}
