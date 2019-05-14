// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBusFrame>
#include <QRandomGenerator>
#include <QString>
#include "ecu.h"

Ecu::Ecu(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : EcuBase{ecuId, canBus, parent}
{
}

Ecu::~Ecu()
{
}

bool Ecu::isReadParameter(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0201U && frame.payload()[0] == char(1);
}

void Ecu::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Ecu/Send"), pid, value);
    canBus()->writeFrame(QCanBusFrame(0x18ef0102U, encodeReadParameter(pid, value)));
}

void Ecu::receiveReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Ecu/Recv"), pid, value);
    sendReadParameter(pid, QRandomGenerator::global()->generate());
}
