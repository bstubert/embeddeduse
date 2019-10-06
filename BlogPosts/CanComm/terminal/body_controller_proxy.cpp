// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "j1939_broadcast_frames.h"
#include "body_controller_proxy.h"

BodyControllerProxy::BodyControllerProxy(CanBusRouter *router, QObject *parent)
    : EcuProxy(2, router, parent)
{
}

BodyControllerProxy::~BodyControllerProxy()
{
}

void BodyControllerProxy::receiveProprietaryBroadcastFrame(const J1939Frame &frame)
{
    if (frame.parameterGroupNumber() == 0xff10U)
    {
        auto payload{frame.decode<A02AxleTilt::Payload>()};
        emitLogMessage(QString{"Recv in Proxy %1: A02AxleTilt(%2, %3, %4)"}
                       .arg(ecuId()).arg(payload.tiltAxle1)
                       .arg(payload.tiltAxle2).arg(payload.tiltAxle2));
    }
}

