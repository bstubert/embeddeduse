// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QtGlobal>

class J1939Frame : public QCanBusFrame
{
public:
    explicit J1939Frame(quint8 priority, quint16 pduFormat, quint8 pduSpecific,
                        quint8 sourceAddress);

    quint8 priority() const;
    quint16 pduFormat() const;
    quint8 pduSpecific() const;
    quint8 sourceAddress() const;

private:
    bool isJ1939Compliant(quint16 pduFormat) const;
};
