// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QList>
#include <QMetaType>
#include <QVariant>

Q_DECLARE_METATYPE(QCanBusFrame)

enum CanConfigurationKey {
    ActualCanIo = QCanBusDevice::UserKey,
    ExpectedCanIo
};

inline bool operator==(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return frame1.frameId() == frame2.frameId() && frame1.payload() == frame2.payload();
}

inline bool operator!=(const QCanBusFrame &frame1, const QCanBusFrame &frame2)
{
    return !(frame1 == frame2);
}

namespace CanUtils
{
inline QList<QCanBusFrame> actualCanIo(const QCanBusDevice *device)
{
    return device->configurationParameter(CanConfigurationKey::ActualCanIo)
            .value<QList<QCanBusFrame>>();
}

inline void setActualCanIo(QCanBusDevice *device, const QList<QCanBusFrame> &frames)
{
    device->setConfigurationParameter(CanConfigurationKey::ActualCanIo,
                                      QVariant::fromValue(frames));
}

inline void appendActualIoFrame(QCanBusDevice *device, const QCanBusFrame frame)
{
    auto frames = actualCanIo(device);
    frames.append(frame);
    setActualCanIo(device, frames);
}

inline QList<QCanBusFrame> expectedCanIo(const QCanBusDevice *device)
{
    return device->configurationParameter(CanConfigurationKey::ExpectedCanIo)
            .value<QList<QCanBusFrame>>();
}

inline void setExpectedCanIo(QCanBusDevice *device, const QList<QCanBusFrame> &frames)
{
    device->setConfigurationParameter(CanConfigurationKey::ExpectedCanIo,
                                      QVariant::fromValue(frames));
}

inline QCanBusFrame takeFirstExpectedCanIoFrame(QCanBusDevice *device)
{
    auto frames = expectedCanIo(device);
    auto firstFrame = frames.takeFirst();
    setExpectedCanIo(device, frames);
    return firstFrame;
}
}
