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

private:
    QByteArray encode(Payload payload) const;
};


//struct EEC1Payload
//{
//    static constexpr int c_parameterCount{8};

//    // Define QVector<QPair<quint8, quin8> with startBit and bitMask for every parameter
//    // in payload of EEC1.

//    // Define enum with parameter names as symbolic constants; the constant values run from 0
//    // to c_parameterCount - 1.

//    QByteArray toPayload(const QVector<quint64> &parameterValues) const
//    {
//        auto number{quint64{0U}};
//        for (int i = 0; i < qMin(c_parameterCount, parameterValues.size()); ++i)
//        {
////            number |= ((parameterValues[i] << startBit) & bitMask);
//        }
//        QByteArray payload{c_parameterCount, 0xff};
//        qToLittleEndian(number, payload.data());
//        return payload;
//    }

//    QVector<quint64> fromPayload(const QByteArray &payload);
//};
