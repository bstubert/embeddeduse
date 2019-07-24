// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QMetaType>
#include <QPair>
#include <QtGlobal>
#include <QVariant>
#include <QVector>

struct ExpectedCanFrame
{
    enum class Type : int {
        Invalid = 0,
        Outgoing = 1,
        Incoming = 2,
        DeviceError = 3
    };

    enum class ErrorNo : quint8 {
        NoBufferSpaceAvailable = 1,
        CannotFilterUnknownFrames = 2,
    };

    ExpectedCanFrame()
        : type{Type::Invalid}
    {}

    ExpectedCanFrame(Type type, const QCanBusFrame &frame)
        : type{type}
        , frame{frame}
    {}

    ExpectedCanFrame(Type type, quint32 frameId, const char *payload)
        : type{type}
        , frame{frameId, QByteArray::fromHex(payload)}
    {}

    ExpectedCanFrame(QCanBusDevice::CanBusError deviceError, ErrorNo errorNo)
        : type{Type::DeviceError}
        , frame{QCanBusFrame::FrameType::InvalidFrame}
    {
        QByteArray payload(8, 0x00);
        payload[0] = quint8(deviceError);
        payload[1] = quint8(errorNo);
        frame.setPayload(payload);
    }

    operator QCanBusFrame() const { return frame; }

    QCanBusDevice::CanBusError deviceError() const
    {
        return QCanBusDevice::CanBusError(quint8(frame.payload()[0]));
    }

    QString deviceErrorString() const
    {
        static const QMap<quint8, QString> errorStr{
            {quint8(ErrorNo::NoBufferSpaceAvailable),
                        QStringLiteral("No buffer space available")},
            {quint8(ErrorNo::CannotFilterUnknownFrames),
                        QStringLiteral("Cannot set filter for frame type: unknown")},
        };
        return errorStr[quint8(frame.payload()[1])];
    }

    Type type;
    QCanBusFrame frame;
};

using ExpectedCanFrameCollection = QVector<ExpectedCanFrame>;
Q_DECLARE_METATYPE(ExpectedCanFrame)

using CanBusFrameCollection = QVector<QCanBusFrame>;
Q_DECLARE_METATYPE(QCanBusFrame)

Q_DECLARE_METATYPE(ExpectedCanFrame::ErrorNo)
using CanBusErrorCollection = QVector<QCanBusDevice::CanBusError>;

namespace CanUtils
{
enum class ConfigurationKey : int {
    ActualCanIo = QCanBusDevice::UserKey,
    ExpectedCanIo
};

inline ExpectedCanFrameCollection actualCanIo(const QCanBusDevice *device)
{
    return device->configurationParameter(int(CanUtils::ConfigurationKey::ActualCanIo))
            .value<ExpectedCanFrameCollection>();
}

inline void setActualCanIo(QCanBusDevice *device, const ExpectedCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(CanUtils::ConfigurationKey::ActualCanIo),
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
    return device->configurationParameter(int(CanUtils::ConfigurationKey::ExpectedCanIo))
            .value<ExpectedCanFrameCollection>();
}

inline void setExpectedCanIo(QCanBusDevice *device, const ExpectedCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(CanUtils::ConfigurationKey::ExpectedCanIo),
                                      QVariant::fromValue(frames));
}
}
