// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "j1939_frame.h"

J1939Frame::J1939Frame(quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress)
    : QCanBusFrame{toJ1939FrameId(pduFormat, pduSpecific, sourceAddress), {}}
{
    if (!isJ1939Compliant(pduFormat))
    {
        setFrameId(0U);
        setFrameType(QCanBusFrame::InvalidFrame);
    }
}

quint16 J1939Frame::pduFormat() const
{
    return static_cast<quint16>((frameId() & 0x01FF0000U) >> 16);
}

quint8 J1939Frame::pduSpecific() const
{
    return static_cast<quint8>((frameId() & 0x0000FF00U) >> 8);
}

quint8 J1939Frame::sourceAddress() const
{
    return static_cast<quint8>(frameId() & 0x000000FFU);
}


quint32 J1939Frame::toJ1939FrameId(
        quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress
        ) const
{
    return (quint32{pduFormat} << 16) | (quint32{pduSpecific} << 8) | (quint32{sourceAddress});
}

bool J1939Frame::isJ1939Compliant(quint16 pduFormat) const
{
    return pduFormat == this->pduFormat();
}
