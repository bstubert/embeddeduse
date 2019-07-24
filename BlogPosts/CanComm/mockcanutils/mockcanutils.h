// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QMetaType>
#include <QPair>
#include <QtGlobal>
#include <QVariant>
#include <QVector>

enum class CanErrorNo : quint8 {
    NoBufferSpaceAvailable = 1,
    CannotFilterUnknownFrames = 2,
};
Q_DECLARE_METATYPE(CanErrorNo)


struct ExpectedCanFrame
{
    enum class Type : int {
        Invalid = 0,
        Outgoing = 1,
        Incoming = 2,
        DeviceError = 3
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

    ExpectedCanFrame(QCanBusDevice::CanBusError deviceError, CanErrorNo errorNo)
        : type{Type::DeviceError}
        , frame{QCanBusFrame::FrameType::InvalidFrame}
    {
        QByteArray payload(8, 0x00);
        payload[0] = quint8(deviceError);
        payload[1] = quint8(errorNo);
        frame.setPayload(payload);
    }

    operator QCanBusFrame() const { return frame; }

    Type type;
    QCanBusFrame frame;
};

//using ExpectedCanFrame = QPair<ExpectedCanFrameType, QCanBusFrame>;
using ExpectedCanFrameCollection = QVector<ExpectedCanFrame>;
Q_DECLARE_METATYPE(ExpectedCanFrame)
Q_DECLARE_METATYPE(ExpectedCanFrameCollection)

using CanBusFrameCollection = QVector<QCanBusFrame>;
Q_DECLARE_METATYPE(QCanBusFrame)
Q_DECLARE_METATYPE(CanBusFrameCollection)

using CanBusErrorCollection = QVector<QCanBusDevice::CanBusError>;

namespace CanUtils
{
enum class ConfigurationKey : int {
    ActualCanIo = QCanBusDevice::UserKey,
    ExpectedCanIo
};

inline QPair<QString, QCanBusDevice::CanBusError> deviceError(const ExpectedCanFrame &frame)
{
    static const QMap<quint8, QString> errorStr{
        {quint8(CanErrorNo::NoBufferSpaceAvailable), QStringLiteral("No buffer space available")},
        {quint8(CanErrorNo::CannotFilterUnknownFrames), QStringLiteral("Cannot set filter for frame type: unknown")},
    };
    auto canFrame = QCanBusFrame{frame};
    return qMakePair(errorStr[quint8(canFrame.payload()[1])],
                     QCanBusDevice::CanBusError(quint8(canFrame.payload()[0])));
}

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
