// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBusFrame>
#include <QString>
#include <QtDebug>
#include <QtEndian>
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
    if (isLogging()) {
        emit logMessage(QString("Trm/Send: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                        .arg(quint32(value), 0, 16));
    }
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    QCanBusFrame frame(0x18ef0201U, payload);
    writeCanFrame(frame);
}

void EcuProxy::receiveReadParameter(quint16 pid, quint32 value)
{
    if (isLogging()) {
        emit logMessage(QString("Trm/Recv: Read(0x%1, 0x%2)").arg(quint16(pid), 0, 16)
                        .arg(quint32(value), 0, 16));
    }
}
