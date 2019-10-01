// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QByteArray>
#include <QCanBusFrame>
#include <QtEndian>
#include <QtGlobal>
#include <QVector>

class QByteArray;

class J1939Frame : public QCanBusFrame
{
public:
    explicit J1939Frame(quint8 priority, quint16 pduFormat, quint8 pduSpecific,
                        quint8 sourceAddress, const QByteArray &payload);

    quint8 priority() const;
    quint16 pduFormat() const;
    quint8 pduSpecific() const;
    quint8 sourceAddress() const;
    bool isPeerToPeer() const;
    quint8 destinationAddress() const;

protected:
    template <class Payload>
    static QByteArray encode(Payload payload)
    {
        QByteArray result(8, 0x00);
        qToLittleEndian(payload, result.data());
        return result;
    }
};
