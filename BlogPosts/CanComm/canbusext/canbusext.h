// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QList>
#include <QMetaType>
#include <QPair>
#include <QVariant>

enum class CanConfigurationKey : int {
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

enum class CanFrameType : int {
    OutgoingCanFrame = 0,
    IncomingCanFrame
};

using ExpectedCanFrame = QPair<CanFrameType, QCanBusFrame>;
using ExpectedCanFrameCollection = QVector<ExpectedCanFrame>;
Q_DECLARE_METATYPE(ExpectedCanFrame)
Q_DECLARE_METATYPE(ExpectedCanFrameCollection)

using CanBusFrameCollection = QVector<QCanBusFrame>;
Q_DECLARE_METATYPE(QCanBusFrame)
Q_DECLARE_METATYPE(CanBusFrameCollection)

namespace CanUtils
{
inline ExpectedCanFrame makeOutgoingFrame(const QCanBusFrame &frame)
{
    return qMakePair(CanFrameType::OutgoingCanFrame, frame);
}

inline ExpectedCanFrame makeOutgoingFrame(quint32 frameId, const char *payload)
{
    return makeOutgoingFrame(QCanBusFrame{frameId, QByteArray::fromHex(payload)});
}

inline ExpectedCanFrame makeIncomingFrame(quint32 frameId, const char *payload)
{
    return qMakePair(CanFrameType::IncomingCanFrame,
                     QCanBusFrame{frameId, QByteArray::fromHex(payload)});
}

inline ExpectedCanFrameCollection actualCanIo(const QCanBusDevice *device)
{
    return device->configurationParameter(int(CanConfigurationKey::ActualCanIo))
            .value<ExpectedCanFrameCollection>();
}

inline void setActualCanIo(QCanBusDevice *device, const ExpectedCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(CanConfigurationKey::ActualCanIo),
                                      QVariant::fromValue(frames));
}

inline void appendActualIoFrame(QCanBusDevice *device, const ExpectedCanFrame &frame)
{
    auto frames = actualCanIo(device);
    frames.append(frame);
    setActualCanIo(device, frames);
}

inline ExpectedCanFrameCollection expectedCanIo(const QCanBusDevice *device)
{
    return device->configurationParameter(int(CanConfigurationKey::ExpectedCanIo))
            .value<ExpectedCanFrameCollection>();
}

inline void setExpectedCanIo(QCanBusDevice *device, const ExpectedCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(CanConfigurationKey::ExpectedCanIo),
                                      QVariant::fromValue(frames));
}
}
