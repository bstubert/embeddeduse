// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "j1939_frame.h"

namespace
{
constexpr quint32 INVALID_FRAME_ID{0xE0000000};

constexpr quint32 MASK_PRIORITY{0x1C000000U};
constexpr quint32 SHIFT_PRIORITY{26U};

constexpr quint32 MASK_PDU_FORMAT{0x01FF0000U};
constexpr quint32 SHIFT_PDU_FORMAT{16U};
constexpr quint16 MAX_PDU_FORMAT{511U};

constexpr quint32 MASK_PDU_SPECIFIC{0x0000FF00U};
constexpr quint32 SHIFT_PDU_SPECIFIC{8U};

constexpr quint32 MASK_SOURCE_ADDRESS{0x000000FFU};


quint32 toJ1939FrameId(quint8 priority, quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress)
{
    return (quint32{priority} << SHIFT_PRIORITY) |
            (quint32{pduFormat} << SHIFT_PDU_FORMAT) |
            (quint32{pduSpecific} << SHIFT_PDU_SPECIFIC) |
            (quint32{sourceAddress});
}

bool isJ1939Compliant(quint16 pduFormat)
{
    return pduFormat <= MAX_PDU_FORMAT;
}

} // end namespace

J1939Frame::J1939Frame(quint8 priority, quint16 pduFormat, quint8 pduSpecific, quint8 sourceAddress)
    : QCanBusFrame{toJ1939FrameId(priority, pduFormat, pduSpecific, sourceAddress), {}}
{
    if (!isJ1939Compliant(pduFormat))
    {
        setFrameId(INVALID_FRAME_ID);
    }
}

quint8 J1939Frame::priority() const
{
    return static_cast<quint8>((frameId() & MASK_PRIORITY) >> SHIFT_PRIORITY);
}

quint16 J1939Frame::pduFormat() const
{
    return static_cast<quint16>((frameId() & MASK_PDU_FORMAT) >> SHIFT_PDU_FORMAT);
}

quint8 J1939Frame::pduSpecific() const
{
    return static_cast<quint8>((frameId() & MASK_PDU_SPECIFIC) >> SHIFT_PDU_SPECIFIC);
}

quint8 J1939Frame::sourceAddress() const
{
    return static_cast<quint8>(frameId() & MASK_SOURCE_ADDRESS);
}

