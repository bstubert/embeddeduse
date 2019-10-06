// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecuproxy.h"

class BodyControllerProxy : public EcuProxy
{
public:
    BodyControllerProxy(CanBusRouter *router, QObject *parent = nullptr);
    virtual ~BodyControllerProxy() override;

    virtual void receiveProprietaryBroadcastFrame(const J1939Frame &frame) override;
};
