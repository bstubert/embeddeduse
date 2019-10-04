// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QCanBusFrame>
#include <QString>
#include <QtEndian>

#include "canbusrouter.h"
#include "ecuproxy.h"
#include "j1939_broadcast_frames.h"

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

bool EcuProxy::isReadParameter(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

void EcuProxy::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Trm/Send"), pid, value);
    m_router->writeFrame(ReadParameterRequest(static_cast<quint8>(ecuId()), 0x01U, pid, value));
}

void EcuProxy::receiveReadParameter(const QCanBusFrame &frame)
{
    quint16 pid = 0U;
    quint32 value = 0U;
    std::tie(pid, value) = decodedReadParameter(frame);
    emitReadParameterMessage(QStringLiteral("Trm/Recv"), pid, value);
}

void EcuProxy::receiveUnsolicitedFrame(const QCanBusFrame &frame)
{
    auto sourceId = sourceEcuId(frame.frameId());
    auto value = qFromLittleEndian<qint32>(frame.payload().data());
    auto info = QString{"Recv in Proxy %1"}.arg(ecuId());
    emitSendUnsolicitedMessage(sourceId, info, value);
}
