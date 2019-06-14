// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
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
    enqueueOutgoingFrame(QCanBusFrame(0x18ef0102U, encodedReadParameter(pid, value)));
}

void Ecu::receiveReadParameter(const QCanBusFrame &frame)
{
    quint16 pid = 0U;
    quint32 value = 0U;
    std::tie(pid, value) = decodedReadParameter(frame);
    // Uncomment the following code to make the ECU skip every 8th response.
//    if (pid % 8U == 0U) {
//        return;
//    }
    emitReadParameterMessage(QStringLiteral("Ecu/Recv"), pid, value);
    // Uncomment the next line, if you want to test request and response for ReceiveOwnKey.
//    sendReadParameter(pid, QRandomGenerator::global()->generate());
}
