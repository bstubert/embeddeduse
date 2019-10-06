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
    emitReadParameterMessage(QStringLiteral("Trm/Send"), pid, value);
    m_router->writeFrame(ReadParameterRequest(static_cast<quint8>(ecuId()), 0x01U, pid, value));
}

void EcuProxy::receiveProprietaryPeerToPeerFrame(const J1939Frame &frame)
{
    switch (quint8(frame.groupFunction()))
    {
    case 1U:
    {
        auto payload{frame.decode<ReadParameterResponse::Payload>()};
        emitReadParameterMessage(QStringLiteral("Trm/Recv"),  quint16(payload.parameterId),
                                 quint32(payload.parameterValue));
        break;
    }
    default:
        qWarning() << "WARNING: Unknown proprietary peer-to-peer J1939 frame: " << frame;
        break;
    }
}
