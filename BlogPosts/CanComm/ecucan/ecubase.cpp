// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QtEndian>
#include "ecubase.h"

EcuBase::EcuBase(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : QObject(parent)
    , m_ecuId{ecuId}
    , m_canBus{canBus}
{
    if (m_canBus == nullptr) {
        return;
    }
    connect(m_canBus.get(), &QCanBusDevice::errorOccurred,
            this, &EcuBase::onErrorOccurred);
    connect(m_canBus.get(), &QCanBusDevice::framesReceived,
            this, &EcuBase::onFramesReceived);
}

EcuBase::~EcuBase()
{
}

int EcuBase::ecuId() const
{
    return m_ecuId;
}

QSharedPointer<QCanBusDevice> EcuBase::canBus() const
{
    return m_canBus;
}

bool EcuBase::isLogging() const
{
    return m_logging;
}

void EcuBase::setLogging(bool enabled)
{
    m_logging = enabled;
}

void EcuBase::writeCanFrame(const QCanBusFrame &frame)
{
    if (canBus() == nullptr) {
        return;
    }
    canBus()->writeFrame(frame);
}

bool EcuBase::isReadParameter(const QCanBusFrame &frame) const
{
    Q_UNUSED(frame)
    return false;
}

void EcuBase::sendReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid)
    Q_UNUSED(value)
}

void EcuBase::receiveReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid)
    Q_UNUSED(value)
}

void EcuBase::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    emit logMessage(QString("ERROR: %1 (%2).").arg(canBus()->errorString()).arg(error));
}

void EcuBase::onFramesReceived()
{
    if (canBus() == nullptr) {
        return;
    }
    auto count = canBus()->framesAvailable();
    for (qint64 i = count; i > 0; --i) {
        auto frame = canBus()->readFrame();
        if (isReadParameter(frame)) {
            const auto &payload = frame.payload();
            auto pid = qFromLittleEndian<qint16>(payload.data() + 1);
            auto value = qFromLittleEndian<qint32>(payload.data() + 3);
            receiveReadParameter(pid, value);
        }
    }
}
