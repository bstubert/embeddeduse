// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QtGlobal>

class J1939Frame : public QCanBusFrame
{
public:
    explicit J1939Frame(quint8 pduFormat, quint8 pduSpecific);

    quint8 pduFormat() const;
    quint8 pduSpecific() const;

private:
    quint32 toJ1939FrameId(quint8 pduFormat, quint8 pduSpecific) const;
};
