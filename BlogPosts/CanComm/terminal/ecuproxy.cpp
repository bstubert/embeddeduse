// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QtDebug>
#include <QtEndian>
#include "ecuproxy.h"

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
//    m_canBusDevice->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, true);
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

bool EcuProxy::isOwnFrame(const QCanBusFrame &frame) const
{
    return frame.frameId() == m_outgoingQueue.first().frameId() &&
            frame.payload() == m_outgoingQueue.first().payload();
}

bool EcuProxy::isLogging() const
{
    return m_logging;
}

void EcuProxy::setLogging(bool enabled)
{
    m_logging = enabled;
}

// Default values:
// ReceiveOwnKey = 0 (false)
void EcuProxy::displayCanConfiguration()
{
    auto receiveOwnKey = m_canBusDevice->configurationParameter(QCanBusDevice::ReceiveOwnKey).toBool();
    emit logMessage(QString("ReceiveOwnKey = %1").arg(receiveOwnKey));
}

void EcuProxy::sendReadParameter(quint16 pid)
{
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    QCanBusFrame frame(0x18ef0201U, payload);
    writeCanFrame(frame);
//    enqueueOutgoingFrame(frame);
}

void EcuProxy::enqueueOutgoingFrame(const QCanBusFrame &frame)
{
    auto empty = m_outgoingQueue.isEmpty();
    m_outgoingQueue.append(frame);
    if (empty) {
        writeCanFrame(frame);
    }
}

void EcuProxy::dequeueOutgoingFrame()
{
    m_outgoingQueue.removeFirst();
    if (!m_outgoingQueue.isEmpty()) {
        writeCanFrame(m_outgoingQueue.first());
    }
}

void EcuProxy::writeCanFrame(const QCanBusFrame &frame)
{
    if (isLogging()) {
        emit logMessage(QString("T-Send: %1").arg(m_outgoingQueue.first().toString()));
    }
    m_canBusDevice->writeFrame(frame);
}

void EcuProxy::receiveReadParameter(const QCanBusFrame &frame)
{
    const auto &payload = frame.payload();
    auto pid = qFromLittleEndian<qint16>(payload.data() + 1);
    auto value = qFromLittleEndian<qint32>(payload.data() + 3);
    if (isLogging()) {
        emit logMessage(QString("T-Recv: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                        .arg(quint32(value), 0, 16));
    }
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
//        if (isOwnFrame(frame)) {
//            dequeueOutgoingFrame();
//        }
//        else
        if (isReadParameterFrame(frame)) {
            receiveReadParameter(frame);
        }
    }
}
