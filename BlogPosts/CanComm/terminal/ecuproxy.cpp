// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBusFrame>
#include <QString>
#include <QtDebug>
#include <QtEndian>
#include "ecuproxy.h"

EcuProxy::EcuProxy(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : QObject{parent}
    , m_ecuId{ecuId}
    , m_canBus{canBus}
{
    if (m_canBus == nullptr) {
        return;
    }
    connect(m_canBus.get(), &QCanBusDevice::errorOccurred,
            this, &EcuProxy::onErrorOccurred);
    connect(m_canBus.get(), &QCanBusDevice::framesReceived,
            this, &EcuProxy::onFramesReceived);
}

EcuProxy::~EcuProxy()
{
}

bool EcuProxy::isReadParameterFrame(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

bool EcuProxy::isLogging() const
{
    return m_logging;
}

void EcuProxy::setLogging(bool enabled)
{
    m_logging = enabled;
}

void EcuProxy::sendReadParameter(quint16 pid)
{
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    QCanBusFrame frame(0x18ef0201U, payload);
    writeCanFrame(frame);
}

void EcuProxy::writeCanFrame(const QCanBusFrame &frame)
{
    if (m_canBus == nullptr) {
        return;
    }
    if (isLogging()) {
        emit logMessage(QString("T-Send: %1").arg(frame.toString()));
    }
    m_canBus->writeFrame(frame);
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
    emit logMessage(QString("ERROR: %1 (%2).").arg(m_canBus->errorString()).arg(error));
}

void EcuProxy::onFramesReceived()
{
    if (m_canBus == nullptr) {
        return;
    }
    auto count = m_canBus->framesAvailable();
    for (qint64 i = count; i > 0; --i) {
        auto frame = m_canBus->readFrame();
        if (isReadParameterFrame(frame)) {
            receiveReadParameter(frame);
        }
    }
}
