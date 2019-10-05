// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "j1939_broadcast_frames.h"
#include "transmission_proxy.h"

TransmissionProxy::TransmissionProxy(CanBusRouter *router, QObject *parent)
    : EcuProxy(3, router, parent)
{
}

TransmissionProxy::~TransmissionProxy()
{
}

void TransmissionProxy::receiveUnsolicitedFrame(const J1939Frame &frame)
{
    if (frame.parameterGroupNumber() == 0xff32U)
    {
        auto payload{frame.decode<A03VehicleSpeed::Payload>()};
        emitInfoUnsolicitedMessage(QString{"Recv in Proxy %1: A03VehicleSpeed(%2, %3)"}
                                   .arg(ecuId()).arg(payload.targetVehicleSpeed)
                                   .arg(payload.actualVehicleSpeed));
    }
}
