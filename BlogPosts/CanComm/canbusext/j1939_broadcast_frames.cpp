// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <utility>

#include <QtEndian>

#include "j1939_broadcast_frames.h"

EEC1Frame::EEC1Frame(Payload payload)
    : J1939Frame{3U, 240U, 4U, 0U, encode(std::move(payload))}
{
}

QByteArray EEC1Frame::encode(Payload payload) const
{
    QByteArray result(8, 0x00);
    qToLittleEndian(payload, result.data());
    return result;
}
