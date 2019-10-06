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
    J1939Frame();
    J1939Frame(quint8 priority, quint16 pduFormat, quint8 pduSpecific,
                        quint8 sourceAddress, const QByteArray &payload);
    J1939Frame(const J1939Frame &frame) = default;
    J1939Frame &operator=(const J1939Frame &frame) = default;

    explicit J1939Frame(const QCanBusFrame &frame);
    J1939Frame &operator=(const QCanBusFrame &frame);

    quint8 priority() const;
    quint32 parameterGroupNumber() const;
    quint16 pduFormat() const;
    quint8 pduSpecific() const;
    quint8 sourceAddress() const;
    bool isPeerToPeer() const;
    bool isProprietary() const;
    quint8 destinationAddress() const;

    template <class Payload>
    Payload decode() const
    {
        auto decoded{Payload{}};
        qFromLittleEndian<qint64>(payload().data(), 1, &decoded);
        return decoded;
    }

protected:
    template <class Payload>
    static QByteArray encode(Payload payload)
    {
        QByteArray result(8, 0x00);
        qToLittleEndian(payload, result.data());
        return result;
    }
};
