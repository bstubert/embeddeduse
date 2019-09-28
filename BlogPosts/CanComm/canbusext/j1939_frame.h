// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QtGlobal>

class J1939Frame : public QCanBusFrame
{
public:
    explicit J1939Frame(quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress);

    quint16 pduFormat() const;
    quint8 pduSpecific() const;
    quint8 sourceAddress() const;

private:
    quint32 toJ1939FrameId(quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress) const;
    bool isJ1939Compliant(quint16 pduFormat) const;
};
