// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QCanBusFrame>
#include <QString>
#include <QtEndian>

#include "canbusrouter.h"
#include "ecuproxy.h"

EcuProxy::EcuProxy(int ecuId, CanBusRouter *router, QObject *parent)
    : EcuBase{ecuId, router, parent}
{
}

EcuProxy::~EcuProxy()
{
}

bool EcuProxy::areReceivedFramesRelevant(const QSet<int> &ecuIdColl) const
{
    return ecuIdColl.contains(ecuId());
}

bool EcuProxy::isReadParameter(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

void EcuProxy::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Trm/Send"), pid, value);
    m_router->writeFrame(QCanBusFrame(0x18ef0201U, encodedReadParameter(pid, value)));
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
