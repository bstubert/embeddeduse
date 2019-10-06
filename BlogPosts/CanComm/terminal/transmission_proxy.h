// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecuproxy.h"

class TransmissionProxy : public EcuProxy
{
public:
    TransmissionProxy(CanBusRouter *router, QObject *parent = nullptr);
    virtual ~TransmissionProxy() override;

    virtual void receiveProprietaryBroadcastFrame(const J1939Frame &frame) override;
};
