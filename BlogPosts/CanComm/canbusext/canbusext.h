// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QByteArray>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDebug>

Q_DECLARE_METATYPE(QCanBusFrame)
Q_DECLARE_METATYPE(QCanBusDevice::Filter)

namespace
{
inline QByteArray toByteArray(const QCanBusFrame &frame)
{
    return QByteArray::number(frame.frameId(), 16) + "#" + frame.payload().toHex();
}
}

inline bool operator==(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return frame1.frameId() == frame2.frameId() && frame1.payload() == frame2.payload();
}

inline bool operator!=(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return !(frame1 == frame2);
}

inline QDebug operator<<(QDebug debug, const QCanBusFrame &frame)
{
    QDebugStateSaver saver(debug);
    debug.nospace().noquote() << toByteArray(frame);
    return debug;
}

inline char *toString(const QCanBusFrame &frame)
{
    auto src = toByteArray(frame);
    char *dst = new char[src.size() + 1];
    return qstrcpy(dst, src.data());
}
