// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QString>
#include <QtDebug>
#include <QtEndian>

#include "canbusext.h"
#include "canbusrouter.h"
#include "ecuproxy.h"
#include "j1939_broadcast_frames.h"
#include "j1939_frame.h"

EcuProxy::EcuProxy(int ecuId, CanBusRouter *router, QObject *parent)
    : EcuBase{ecuId, router, parent}
{
}

EcuProxy::~EcuProxy()
{
}

void EcuProxy::sendReadParameter(quint16 pid, quint32 value)
{
    emitLogMessage(QString("Trm/Send: Read(0x%2, 0x%3)")
                   .arg(pid, 4, 16, QLatin1Char('0'))
                   .arg(value, 8, 16, QLatin1Char('0')));
    m_router->writeFrame(ReadParameterRequest(static_cast<quint8>(ecuId()), 0x01U, pid, value));
}

void EcuProxy::receiveProprietaryPeerToPeerFrame(const J1939Frame &frame)
{
    switch (frame.groupFunction())
    {
    case 1U:
    {
        auto payload{frame.decode<ReadParameterResponse::Payload>()};
        emitLogMessage(QString("Trm/Recv: Read(0x%2, 0x%3)")
                       .arg(quint16(payload.parameterId), 4, 16, QLatin1Char('0'))
                       .arg(quint32(payload.parameterValue), 8, 16, QLatin1Char('0')));
        break;
    }
    default:
        qWarning() << "WARNING: Unknown proprietary peer-to-peer J1939 frame: " << frame;
        break;
    }
}
