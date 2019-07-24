// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QMetaType>
#include <QPair>
#include <QtGlobal>
#include <QVariant>
#include <QVector>

enum class CanConfigurationKey : int {
    ActualCanIo = QCanBusDevice::UserKey,
    ExpectedCanIo
};


enum class CanFrameType : int {
    OutgoingCanFrame = 0,
    IncomingCanFrame = 1,
    DeviceError = 2
};

enum class CanErrorNo : quint8 {
    NoBufferSpaceAvailable = 1,
    CannotFilterUnknownFrames = 2,
};
Q_DECLARE_METATYPE(CanErrorNo)


using ExpectedCanFrame = QPair<CanFrameType, QCanBusFrame>;
using ExpectedCanFrameCollection = QVector<ExpectedCanFrame>;
Q_DECLARE_METATYPE(ExpectedCanFrame)
Q_DECLARE_METATYPE(ExpectedCanFrameCollection)

using CanBusFrameCollection = QVector<QCanBusFrame>;
Q_DECLARE_METATYPE(QCanBusFrame)
Q_DECLARE_METATYPE(CanBusFrameCollection)

using CanBusErrorCollection = QVector<QCanBusDevice::CanBusError>;

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

inline ExpectedCanFrame makeDeviceError(QCanBusDevice::CanBusError deviceError,
                                        CanErrorNo errorNo)
{
    auto frame = QCanBusFrame{QCanBusFrame::FrameType::InvalidFrame};
    QByteArray payload(8, 0x00);
    payload[0] = quint8(deviceError);
    payload[1] = quint8(errorNo);
    frame.setPayload(payload);
    return qMakePair(CanFrameType::DeviceError, frame);
}

inline QPair<QString, QCanBusDevice::CanBusError> deviceError(const ExpectedCanFrame &frame)
{
    static const QMap<quint8, QString> errorStr{
        {quint8(CanErrorNo::NoBufferSpaceAvailable), QStringLiteral("No buffer space available")},
        {quint8(CanErrorNo::CannotFilterUnknownFrames), QStringLiteral("Cannot set filter for frame type: unknown")},
    };
    return qMakePair(errorStr[quint8(frame.second.payload()[1])],
                     QCanBusDevice::CanBusError(quint8(frame.second.payload()[0])));
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
