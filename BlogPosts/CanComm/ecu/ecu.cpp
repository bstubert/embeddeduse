// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QCanBusFrame>
#include <QRandomGenerator>
#include <QString>

#include "canbusrouter.h"
#include "ecu.h"

Ecu::Ecu(int ecuId, CanBusRouter *router, QObject *parent)
    : EcuBase{ecuId, router, parent}
{
}

Ecu::~Ecu()
{
}

void Ecu::onFramesReceived(const QSet<int> &ecuIdColl)
{
    if (!ecuIdColl.contains(1))
    {
        return;
    }
    for (const auto &frame : m_router->takeReceivedFrames(1))
    {
        if (isReadParameter(frame)) {
            receiveReadParameter(frame);
        }
    }
}

bool Ecu::isReadParameter(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0201U && frame.payload()[0] == char(1);
}

void Ecu::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Ecu/Send"), pid, value);
    m_router->writeFrame(QCanBusFrame(0x18ef0102U, encodedReadParameter(pid, value)));
}

void Ecu::receiveReadParameter(const QCanBusFrame &frame)
{
    quint16 pid = 0U;
    quint32 value = 0U;
    std::tie(pid, value) = decodedReadParameter(frame);
    emitReadParameterMessage(QStringLiteral("Ecu/Recv"), pid, value);
    sendReadParameter(pid, QRandomGenerator::global()->generate());
}

void Ecu::sendUnsolicitedFrames()
{
    if (ecuId() == 3) {
        emitSendUnsolicitedMessage(3, "Send", 1);
        m_router->writeFrame(QCanBusFrame{0x18FF3503, QByteArray::fromHex("0100000001000000")});

        emitSendUnsolicitedMessage(3, "Send", 2);
        m_router->writeFrame(QCanBusFrame{0x18FF3503, QByteArray::fromHex("0200000002000000")});

        emitSendUnsolicitedMessage(3, "Send", 3);
        m_router->writeFrame(QCanBusFrame{0x18FF3503, QByteArray::fromHex("030000000C000000")});
    }
    else if (ecuId() == 2) {
        emitSendUnsolicitedMessage(2, "Send", 10);
        m_router->writeFrame(QCanBusFrame{0x18FF0602, QByteArray::fromHex("0A0000000A000000")});

        emitSendUnsolicitedMessage(2, "Send", 11);
        m_router->writeFrame(QCanBusFrame{0x18FF0602, QByteArray::fromHex("0B0000000B000000")});

        emitSendUnsolicitedMessage(2, "Send", 12);
        m_router->writeFrame(QCanBusFrame{0x18FF0602, QByteArray::fromHex("0C0000000C000000")});
    }
}


