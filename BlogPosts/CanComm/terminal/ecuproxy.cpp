// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QString>
#include <QtEndian>

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

void EcuProxy::onFramesReceived(const QSet<int> &ecuIdColl)
{
    if (!ecuIdColl.contains(ecuId()))
    {
        return;
    }
    for (const auto &frame : m_router->takeReceivedFrames(ecuId()))
    {
        if (isReadParameter(frame)) {
            receiveReadParameter(frame);
        }
        else {
            receiveUnsolicitedFrame(frame);
        }
    }
}

bool EcuProxy::isReadParameter(const J1939Frame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

void EcuProxy::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Trm/Send"), pid, value);
    m_router->writeFrame(ReadParameterRequest(static_cast<quint8>(ecuId()), 0x01U, pid, value));
}

void EcuProxy::receiveReadParameter(const J1939Frame &frame)
{
    auto payload{frame.decode<ReadParameterResponse::Payload>()};
    emitReadParameterMessage(QStringLiteral("Trm/Recv"),  quint16(payload.parameterId),
                             quint32(payload.parameterValue));
}

void EcuProxy::receiveUnsolicitedFrame(const J1939Frame &frame)
{
    if (frame.parameterGroupNumber() == 0xff32U)
    {
        auto payload{frame.decode<A03VehicleSpeed::Payload>()};
        emitInfoUnsolicitedMessage(QString{"Recv in Proxy %1: A03VehicleSpeed(%2, %3)"}
                                   .arg(ecuId()).arg(payload.targetVehicleSpeed)
                                   .arg(payload.actualVehicleSpeed));
    }
    else if (frame.parameterGroupNumber() == 0xff10U)
    {
        auto payload{frame.decode<A02AxleTilt::Payload>()};
        emitInfoUnsolicitedMessage(QString{"Recv in Proxy %1: A02AxleTilt(%2, %3, %4)"}
                                   .arg(ecuId()).arg(payload.tiltAxle1)
                                   .arg(payload.tiltAxle2).arg(payload.tiltAxle2));
    }
}
