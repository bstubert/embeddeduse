// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QCanBusFrame>
#include <QString>
#include "ecuproxy.h"

EcuProxy::EcuProxy(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : EcuBase{ecuId, canBus, parent}
{
}

EcuProxy::~EcuProxy()
{
}

bool EcuProxy::isReadParameter(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0102U && frame.payload()[0] == char(1);
}

void EcuProxy::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Trm/Send"), pid, value);
    canBus()->writeFrame(QCanBusFrame(0x18ef0201U, encodeReadParameter(pid, value)));

}

void EcuProxy::receiveReadParameter(const QCanBusFrame &frame)
{
    quint16 pid = 0U;
    quint32 value = 0U;
    std::tie(pid, value) = decodeReadParameter(frame);
    emitReadParameterMessage(QStringLiteral("Trm/Recv"), pid, value);
}
