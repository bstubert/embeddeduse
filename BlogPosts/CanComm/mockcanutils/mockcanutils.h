// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <algorithm>
#include <functional>

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QMetaType>
#include <QPair>
#include <QtGlobal>
#include <QVariant>
#include <QVector>

#include "canbusext.h"

struct MockCanFrame
{
    enum class Type : int {
        Invalid = 0,
        Outgoing = 1,
        Incoming = 2,
        OwnIncoming = 3,
        DeviceError = 4
    };

    enum class ErrorNo : quint8 {
        NoBufferSpaceAvailable = 1,
        CannotFilterUnknownFrames = 2,
    };

    MockCanFrame()
        : type{Type::Invalid}
    {}

    MockCanFrame(Type type, const QCanBusFrame &frame)
        : type{type}
        , frame{frame}
    {}

    MockCanFrame(Type type, quint32 frameId, const char *payload)
        : type{type}
        , frame{frameId, QByteArray::fromHex(payload)}
    {}

    MockCanFrame(QCanBusDevice::CanBusError deviceError, ErrorNo errorNo)
        : type{Type::DeviceError}
        , frame{QCanBusFrame::FrameType::InvalidFrame}
    {
        QByteArray payload(8, 0x00);
        payload[0] = static_cast<qint8>(deviceError);
        payload[1] = static_cast<qint8>(errorNo);
        frame.setPayload(payload);
    }

    QCanBusFrame toCanFrame() const { return frame; }

    QByteArray typeString() const
    {
        switch (type)
        {
        case Type::Invalid:
            return QByteArray{"Invalid"};
        case Type::Outgoing:
            return QByteArray{"Outgoing"};
        case Type::Incoming:
            return QByteArray{"Incoming"};
        case Type::OwnIncoming:
            return QByteArray{"OwnIncoming"};
        case Type::DeviceError:
            return QByteArray{"DeviceError"};
        }
    }

    QByteArray toByteArray() const
    {
        return typeString() + "::" + QByteArray::number(frame.frameId(), 16) + "#" +
                frame.payload().toHex();
    }

    bool isOutgoing() const { return type == Type::Outgoing; }

    bool isIncoming() const { return type == Type::Incoming; }

    bool isOwnIncoming() const { return type == Type::OwnIncoming; }

    bool isDeviceError() const { return type == Type::DeviceError; }

    QCanBusDevice::CanBusError deviceError() const
    {
        if (isDeviceError())
        {
            return QCanBusDevice::CanBusError(quint8(frame.payload()[0]));
        }
        return QCanBusDevice::NoError;
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

using MockCanFrameCollection = QVector<MockCanFrame>;

inline bool operator==(const MockCanFrame &lhs, const MockCanFrame &rhs)
{
    return lhs.type == rhs.type && lhs.frame == rhs.frame;
}

inline bool operator!=(const MockCanFrame &lhs, const MockCanFrame &rhs)
{
    return !(lhs == rhs);
}

inline QDebug operator<<(QDebug debug, const MockCanFrame &mockFrame)
{
    QDebugStateSaver saver(debug);
    debug.nospace().noquote() << mockFrame.typeString() << ": " << mockFrame.toCanFrame();
    return debug;
}

inline char *toString(const MockCanFrame &mockFrame)
{
    auto src = mockFrame.toByteArray();
    char *dst = new char[src.size() + 1];
    return qstrcpy(dst, src.data());
}


inline char *toString(const MockCanFrameCollection &coll)
{
    auto src = QByteArray{"[ "};
    for (const auto &frame : coll)
    {
        src += frame.toByteArray();
        src += ", ";
    }
    src += " ]";
    char *dst = new char[src.size() + 1];
    return qstrcpy(dst, src.data());
}


enum class MockConfigurationKey : int {
    ActualCanIo = QCanBusDevice::UserKey,
    ExpectedCanIo,
    WriteErrorInterval
};


inline MockCanFrameCollection actualCanFrames(const QCanBusDevice *device)
{
    return device->configurationParameter(int(MockConfigurationKey::ActualCanIo))
            .value<MockCanFrameCollection>();
}

inline void setActualCanFrames(QCanBusDevice *device, const MockCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(MockConfigurationKey::ActualCanIo),
                                      QVariant::fromValue(frames));
}

inline void appendActualCanFrame(QCanBusDevice *device, const MockCanFrame &frame)
{
    auto frames = actualCanFrames(device);
    frames.append(frame);
    setActualCanFrames(device, frames);
}

inline MockCanFrameCollection expectedCanFrames(const QCanBusDevice *device)
{
    return device->configurationParameter(int(MockConfigurationKey::ExpectedCanIo))
            .value<MockCanFrameCollection>();
}

inline int expectedCanFrameCount(const QCanBusDevice *device, MockCanFrame::Type frameType)
{
    const auto &coll = expectedCanFrames(device);
    return std::count_if(coll.cbegin(), coll.cend(), [frameType](const MockCanFrame &frame) {
        return frame.type == frameType;
    });
}

inline void setExpectedCanFrames(QCanBusDevice *device, const MockCanFrameCollection &frames)
{
    device->setConfigurationParameter(int(MockConfigurationKey::ExpectedCanIo),
                                      QVariant::fromValue(frames));
}

Q_DECLARE_METATYPE(MockCanFrame)
Q_DECLARE_METATYPE(MockCanFrame::ErrorNo)

using CanBusFrameCollection = QVector<QCanBusFrame>;

using CanBusErrorCollection = QVector<QCanBusDevice::CanBusError>;
