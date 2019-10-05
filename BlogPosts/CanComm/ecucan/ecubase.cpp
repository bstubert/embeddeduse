// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QByteArray>
#include <QCanBusDevice>
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

bool EcuBase::isReadParameter(const J1939Frame &frame) const
{
    Q_UNUSED(frame)
    return false;
}

void EcuBase::sendReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid)
    Q_UNUSED(value)
}

void EcuBase::receiveReadParameter(const J1939Frame &frame)
{
    Q_UNUSED(frame)
}

void EcuBase::receiveUnsolicitedFrame(const J1939Frame &frame)
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

void EcuBase::emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value)
{
    if (isLogging()) {
        emit logMessage(QString("%1: Read(0x%2, 0x%3)").arg(prefix)
                        .arg(quint16(pid), 4, 16, QLatin1Char('0'))
                        .arg(quint32(value), 8, 16, QLatin1Char('0')));
    }
}

void EcuBase::emitInfoUnsolicitedMessage(const QString &info)
{
    if (isLogging()) {
        emit logMessage(info);
    }
}
