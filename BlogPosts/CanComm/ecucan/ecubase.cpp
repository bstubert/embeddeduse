// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QByteArray>
#include <QCanBusDevice>
#include <QDateTime>
#include <QLatin1Char>
#include <QtDebug>
#include <QtEndian>

#include "canbusext.h"
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

void EcuBase::onFramesReceived(const QSet<int> &ecuIdColl)
{
    if (!ecuIdColl.contains(ecuId()))
    {
        return;
    }
    for (const auto &frame : m_router->takeReceivedFrames(ecuId()))
    {
        if (frame.isPeerToPeer())
        {
            if (frame.isProprietary())
            {
                receiveProprietaryPeerToPeerFrame(frame);
            }
            else
            {
                receiveStandardPeerToPeerFrame(frame);
            }
        }
        else {
            if (frame.isProprietary())
            {
                receiveProprietaryBroadcastFrame(frame);
            }
            else
            {
                receiveStandardBroadcastFrame(frame);
            }
        }
    }
}

void EcuBase::receiveProprietaryPeerToPeerFrame(const J1939Frame &frame)
{
    qWarning() << "WARNING: Proprietary J1939 peer-to-peer frames not yet supported: " << frame;
}

void EcuBase::receiveStandardPeerToPeerFrame(const J1939Frame &frame)
{
    qWarning() << "WARNING: Standard J1939 peer-to-peer frames not yet supported: " << frame;
}

void EcuBase::receiveProprietaryBroadcastFrame(const J1939Frame &frame)
{
    qWarning() << "WARNING: Proprietary J1939 broadcast frames not yet supported: " << frame;
}

void EcuBase::receiveStandardBroadcastFrame(const J1939Frame &frame)
{
    qWarning() << "WARNING: Standard J1939 broadcast frames not yet supported: " << frame;
}

void EcuBase::sendReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid)
    Q_UNUSED(value)
}

void EcuBase::onErrorOccurred()
{
    emit logMessage(QString("ERROR: %1.").arg(m_router->errorString()));
}

void EcuBase::emitLogMessage(const QString &info)
{
    if (isLogging())
    {
        emit logMessage(info);
    }
}
