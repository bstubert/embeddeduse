// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>

Q_DECLARE_METATYPE(QCanBusFrame)

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
    debug.nospace().noquote() << QByteArray::number(frame.frameId(), 16) << "#"
                              << frame.payload().toHex();
    return debug;
}
