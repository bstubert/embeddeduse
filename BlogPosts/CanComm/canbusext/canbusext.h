// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>

inline bool operator==(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return frame1.frameId() == frame2.frameId() && frame1.payload() == frame2.payload();
}

inline bool operator!=(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return !(frame1 == frame2);
}
