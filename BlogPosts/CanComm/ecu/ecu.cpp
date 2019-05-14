// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QCanBusFrame>
#include <QRandomGenerator>
#include <QtDebug>
#include <QtEndian>
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
    if (isLogging()) {
        emit logMessage(QString("Ecu/Send: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                        .arg(quint32(value), 0, 16));
    }
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    qToLittleEndian(value, payload.data() + 3);
    QCanBusFrame frame(0x18ef0102U, payload);
    canBus()->writeFrame(frame);
}

void Ecu::receiveReadParameter(quint16 pid, quint32 value)
{
    if (isLogging()) {
        emit logMessage(QString("Ecu/Recv: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                        .arg(quint32(value), 0, 16));
    }
    sendReadParameter(pid, QRandomGenerator::global()->generate());
}
