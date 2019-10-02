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

    explicit EEC1Frame(Payload payload)
        : J1939Frame{3U, 240U, 4U, 0U, encode(std::move(payload))}
    {}
};

class A03VehicleSpeed : public J1939Frame
{
    struct Payload
    {
        quint64 targetVehicleSpeed : 16;    // range: [-7000; 7000], 0.01 km/h
        quint64 actualVehicleSpeed : 16;    // range: [-7000; 7000], 0.01 km/h
        quint64 targetVehicleSpdRamp : 16;  // range: [-7000; 7000], 0.1 km/h
        quint64 engineSpeed_T2 : 16;        // range: [0; 8191], 0.125 rpm
    };

public:
    explicit A03VehicleSpeed(qint16 targetVehicleSpeed, qint16 actualVehicleSpeed,
                             qint16 targetVehicleSpdRamp, quint16 engineSpeed_T2)
        : J1939Frame{6U, 255U, 50U, 3U,
                     encode(Payload{quint16(targetVehicleSpeed), quint16(actualVehicleSpeed),
                                    quint16(targetVehicleSpdRamp), engineSpeed_T2})}
    {}
};


