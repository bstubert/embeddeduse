// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QByteArray>
#include <QtEndian>
#include <QtGlobal>
#include <QVector>

#include "j1939_frame.h"

class EEC1Frame : public J1939Frame
{
public:
    struct Payload
    {
        quint64 engineTorqueMode : 4;
        quint64 actualEnginePercenTorque : 4;
        quint64 driversDemandEnginePercentTorque : 8;
        quint64 actualEnginePercentTorque : 8;
        quint64 engineSpeed : 16;
        quint64 sourceAddressEngineController : 8;
        quint64 engineStarterMode : 4;
        quint64 dummy0 : 4;
        quint64 engineDemandPercentTorque : 8;
    };

    explicit EEC1Frame(Payload payload);
};


