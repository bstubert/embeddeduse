// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QByteArray>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDateTime>
#include <QLatin1Char>
#include <QtDebug>
#include <QtEndian>

#include "canbusrouter.h"
#include "ecubase.h"

EcuBase::EcuBase(int ecuId, CanBusRouter *router, QObject *parent)
    : QObject(parent)
    , m_router{router}
    , m_ecuId{ecuId}
{
}

EcuBase::~EcuBase()
{
}

int EcuBase::ecuId() const
{
    return m_ecuId;
}

bool EcuBase::isLogging() const
{
    return m_logging;
}

void EcuBase::setLogging(bool enabled)
{
    m_logging = enabled;
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

void EcuBase::receiveReadParameter(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
}

void EcuBase::receiveUnsolicitedFrame(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
}

void EcuBase::onErrorOccurred()
{
    emit logMessage(QString("ERROR: %1.").arg(m_router->errorString()));
}

void EcuBase::onFramesReceived(const QSet<int> &ecuIdColl)
{
    Q_UNUSED(ecuIdColl)
}

QByteArray EcuBase::encodedReadParameter(quint16 pid, quint32 value) const
{
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    qToLittleEndian(value, payload.data() + 3);
    return payload;
}

std::tuple<quint16, quint32> EcuBase::decodedReadParameter(const QCanBusFrame &frame) const
{
    const auto &payload = frame.payload();
    quint16 pid = qFromLittleEndian<qint16>(payload.data() + 1);
    quint32 value = qFromLittleEndian<qint32>(payload.data() + 3);
    return std::make_tuple(pid, value);
}

int EcuBase::sourceEcuId(quint32 frameId) const
{
    return static_cast<int>(frameId & 0x000000FF);
}

void EcuBase::emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value)
{
    if (isLogging()) {
        emit logMessage(QString("%1: Read(0x%2, 0x%3)").arg(prefix)
                        .arg(quint16(pid), 4, 16, QLatin1Char('0'))
                        .arg(quint32(value), 8, 16, QLatin1Char('0')));
    }
}

void EcuBase::emitSendUnsolicitedMessage(int ecuId, const QString &direction, int value)
{
    if (isLogging()) {
        emit logMessage(QString("Ecu %1/%2: unsolicited %3").arg(ecuId).arg(direction).arg(value));
    }
}
