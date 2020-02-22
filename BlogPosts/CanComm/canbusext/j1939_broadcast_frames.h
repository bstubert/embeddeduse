// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QByteArray>
#include <QtEndian>
#include <QtGlobal>
#include <QVector>

#include "j1939_frame.h"

struct EEC1Frame : public J1939Frame
{
    static constexpr quint32 PGN{0xF004U};

    struct Payload
    {
        qint64 engineTorqueMode : 4;
        qint64 actualEnginePercenTorque : 4;
        qint64 driversDemandEnginePercentTorque : 8;
        qint64 actualEnginePercentTorque : 8;
        qint64 engineSpeed : 16;
        qint64 sourceAddressEngineController : 8;
        qint64 engineStarterMode : 4;
        qint64 dummy0 : 4;
        qint64 engineDemandPercentTorque : 8;
    };

    explicit EEC1Frame(quint8 engineTorqueMode, quint8 actualEnginePercenTorque,
                       quint8 driversDemandEnginePercentTorque, quint8 actualEnginePercentTorque,
                       quint16 engineSpeed, quint8 sourceAddressEngineController,
                       quint8 engineStarterMode, quint8 engineDemandPercentTorque)
        : J1939Frame{3U, 240U, 4U, 0U,
                     encode(Payload{engineTorqueMode, actualEnginePercenTorque,
                            driversDemandEnginePercentTorque, actualEnginePercentTorque,
                            engineSpeed, sourceAddressEngineController,
                            engineStarterMode, 0, engineDemandPercentTorque})}
    {}
};

struct A02AxleTilt : public J1939Frame
{
    static constexpr quint32 PGN{0xFF10U};

    struct Payload
    {
        qint64 tiltAxle1 : 16;
        qint64 tiltAxle2 : 16;
        qint64 tiltAxle3 : 16;
        qint64 dummy0 : 16;
    };

    explicit A02AxleTilt(qint16 tiltAxle1, qint16 tiltAxle2, qint16 tiltAxle3)
        : J1939Frame{6U, 255U, 16U, 2U,
                     encode(Payload{tiltAxle1, tiltAxle2, tiltAxle3, 0U})}
    {}
};

struct A03VehicleSpeed : public J1939Frame
{
    static constexpr quint32 PGN{0xFF32U};

    struct Payload
    {
        qint64 targetVehicleSpeed : 16;    // range: [-7000; 7000], 0.01 km/h
        qint64 actualVehicleSpeed : 16;    // range: [-7000; 7000], 0.01 km/h
        qint64 targetVehicleSpdRamp : 16;  // range: [-7000; 7000], 0.1 km/h
        qint64 engineSpeed_T2 : 16;        // range: [0; 8191], 0.125 rpm
    };

    explicit A03VehicleSpeed(qint16 targetVehicleSpeed, qint16 actualVehicleSpeed,
                             qint16 targetVehicleSpdRamp, quint16 engineSpeed_T2)
        : J1939Frame{6U, 255U, 50U, 3U,
                     encode(Payload{targetVehicleSpeed, actualVehicleSpeed,
                                    targetVehicleSpdRamp, engineSpeed_T2})}
    {}
};

struct ReadParameterRequest : public J1939Frame
{
    static constexpr quint32 PGN{0xEF00U};

    struct Payload
    {
        qint64 commandId : 8;
        qint64 parameterId : 16;
        qint64 parameterValue : 32;
        qint64 dummy0 : 8;
    };

    explicit ReadParameterRequest(quint8 destinationAddress, quint8 sourceAddress,
                                  quint16 parameterId, quint32 parameterValue)
        : J1939Frame{6U, 239U, destinationAddress, sourceAddress,
                     encode(Payload{1, parameterId, parameterValue, 0})}
    {}
};


struct ReadParameterResponse : public J1939Frame
{
    static constexpr quint32 PGN{0xEF00U};

    struct Payload
    {
        qint64 commandId : 8;
        qint64 parameterId : 16;
        qint64 parameterValue : 32;
        qint64 dummy0 : 8;
    };

    explicit ReadParameterResponse(quint8 destinationAddress, quint8 sourceAddress,
                                   quint16 parameterId, quint32 parameterValue)
        : J1939Frame{6U, 239U, destinationAddress, sourceAddress,
                     encode(Payload{1, parameterId, parameterValue, 0})}
    {}
};
