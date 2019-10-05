// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QRandomGenerator>
#include <QString>

#include "canbusrouter.h"
#include "ecu.h"
#include "j1939_broadcast_frames.h"
#include "j1939_frame.h"

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

bool Ecu::isReadParameter(const J1939Frame &frame) const
{
    return frame.frameId() == 0x18ef0201U && frame.payload()[0] == char(1);
}

void Ecu::sendReadParameter(quint16 pid, quint32 value)
{
    emitReadParameterMessage(QStringLiteral("Ecu/Send"), pid, value);
    m_router->writeFrame(ReadParameterResponse(0x01U, static_cast<quint8>(ecuId()), pid, value));
}

void Ecu::receiveReadParameter(const J1939Frame &frame)
{
    auto payload{frame.decode<ReadParameterRequest::Payload>()};
    emitReadParameterMessage(QStringLiteral("Ecu/Recv"),  quint16(payload.parameterId),
                             quint32(payload.parameterValue));
    sendReadParameter(quint16(payload.parameterId), QRandomGenerator::global()->generate());
}

void Ecu::sendUnsolicitedFrames()
{
    if (ecuId() == 3) {
        emitInfoUnsolicitedMessage(QString{"Sent from ECU 3: A03VehicleSpeed(750, 344)"});
        m_router->writeFrame(A03VehicleSpeed{750, 344, 1340, 3499});

        emitInfoUnsolicitedMessage(QString{"Sent from ECU 3: A03VehicleSpeed(750, 407)"});
        m_router->writeFrame(A03VehicleSpeed{750, 407, 1340, 3499});

        emitInfoUnsolicitedMessage(QString{"Sent from ECU 3: A03VehicleSpeed(750, 489)"});
        m_router->writeFrame(A03VehicleSpeed{750, 489, 1340, 3499});
    }
    else if (ecuId() == 2) {
        emitInfoUnsolicitedMessage(QString{"Sent from ECU 2: A02AxleTilt(389, -813, 1034)"});
        m_router->writeFrame(A02AxleTilt{389, -813, 1034});

        emitInfoUnsolicitedMessage(QString{"Sent from ECU 2: A02AxleTilt(443, -978, 981)"});
        m_router->writeFrame(A02AxleTilt{443, -978, 981});

        emitInfoUnsolicitedMessage(QString{"Sent from ECU 2: A02AxleTilt(508, -1088, 855)"});
        m_router->writeFrame(A02AxleTilt{508, -1088, 855});
    }
}


