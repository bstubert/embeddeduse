// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "j1939_frame.h"

J1939Frame::J1939Frame(quint8 pduFormat)
    : QCanBusFrame{toJ1939FrameId(pduFormat), {}}
{
}

quint8 J1939Frame::pduFormat() const
{
    return static_cast<quint8>((frameId() & 0x00FF0000U) >> 16);
}


quint32 J1939Frame::toJ1939FrameId(quint8 pduFormat) const
{
    return quint32{pduFormat} << 16;
}
