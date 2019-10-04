// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QByteArray>
#include <QtEndian>
#include <QtGlobal>
#include <QVector>

#include "j1939_frame.h"

class EEC1Frame : public J1939Frame
{
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

public:
    explicit EEC1Frame(quint8 engineTorqueMode, quint8 actualEnginePercenTorque,
                       quint8 driversDemandEnginePercentTorque, quint8 actualEnginePercentTorque,
                       quint16 engineSpeed, quint8 sourceAddressEngineController,
                       quint8 engineStarterMode, quint8 engineDemandPercentTorque)
        : J1939Frame{3U, 240U, 4U, 0U,
                     encode(Payload{engineTorqueMode, actualEnginePercenTorque,
                            driversDemandEnginePercentTorque, actualEnginePercentTorque,
                            engineSpeed, sourceAddressEngineController,
                            engineStarterMode, quint8{0U}, engineDemandPercentTorque})}
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

class ReadParameterRequest : public J1939Frame
{
    struct Payload
    {
        quint64 commandId : 8;
        quint64 parameterId : 16;
        quint64 parameterValue : 32;
        quint64 dummy0 : 8;
    };

public:
    explicit ReadParameterRequest(quint8 destinationAddress, quint8 sourceAddress,
                                  quint16 parameterId, quint32 parameterValue)
        : J1939Frame{6U, 239U, destinationAddress, sourceAddress,
                     encode(Payload{quint8{1U}, parameterId, parameterValue, quint8{0U}})}
    {}
};


class ReadParameterResponse : public J1939Frame
{
    struct Payload
    {
        quint64 commandId : 8;
        quint64 parameterId : 16;
        quint64 parameterValue : 32;
        quint64 dummy0 : 8;
    };

public:
    explicit ReadParameterResponse(quint8 destinationAddress, quint8 sourceAddress,
                                   quint16 parameterId, quint32 parameterValue)
        : J1939Frame{6U, 239U, destinationAddress, sourceAddress,
                     encode(Payload{quint8{1U}, parameterId, parameterValue, quint8{0U}})}
    {}
};
