// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>

#include <QMetaType>
#include <QtDebug>

#include "canbusext.h"
#include "mocksocketcandevice.h"

MockSocketCanDevice::MockSocketCanDevice(const QString &name, QObject *parent)
    : QCanBusDevice{parent}
    , m_interface{name}
{
    // Required to use QCanBusDevice::CanBusError in asynchronous signal-slot connections and
    // in QSignalSpys.
    qRegisterMetaType<QCanBusDevice::CanBusError>();
}

MockSocketCanDevice::~MockSocketCanDevice()
{
    close();
}

QList<QCanBusDeviceInfo> MockSocketCanDevice::interfaces()
{
    QList<QCanBusDeviceInfo> result;
    result.append(createDeviceInfo("mcan0"));
    result.append(createDeviceInfo("mcan1"));
    return result;
}

void MockSocketCanDevice::setConfigurationParameter(int key, const QVariant &value)
{
    QCanBusDevice::setConfigurationParameter(key, value);
    if (key == int(CanConfigurationKey::ExpectedCanIo)) {
        m_frameIndex = 0;
        m_frameCount = CanUtils::expectedCanIo(this).size();
        receiveIncomingFrames();
    }
}

bool MockSocketCanDevice::writeFrame(const QCanBusFrame &frame)
{
    if (m_frameIndex >= m_frameCount) {
        qWarning() << "Expected no frame, but got " << frame.toString();
    }
    else {
        auto expectedFrame = CanUtils::expectedCanIo(this)[m_frameIndex];
        ++m_frameIndex;
        if (expectedFrame.second != frame) {
            qWarning() << "Expected " << expectedFrame.second.toString()
                       << ", but got " << frame.toString();
        }
    }
    CanUtils::appendActualIoFrame(this, CanUtils::makeOutgoingFrame(frame));
    emit framesWritten(1);
    checkForDeviceErrors();
    receiveIncomingFrames();
    return true;
}

QString MockSocketCanDevice::interpretErrorFrame(const QCanBusFrame &errorFrame)
{
    Q_UNUSED(errorFrame)
    return {};
}

bool MockSocketCanDevice::open()
{
    const auto &interfaces = MockSocketCanDevice::interfaces();
    auto pos = std::find_if(interfaces.cbegin(), interfaces.cend(),
                            [this](const QCanBusDeviceInfo &info) {
                                return info.name() == m_interface;
                            });
    if (pos == interfaces.cend()) {
        close();
        return false;
    }
    setState(QCanBusDevice::ConnectedState);
    return true;
}

void MockSocketCanDevice::close()
{
    setState(QCanBusDevice::UnconnectedState);
}

void MockSocketCanDevice::checkForDeviceErrors()
{
    auto expectedFrames = CanUtils::expectedCanIo(this);
    while (m_frameIndex < m_frameCount &&
           expectedFrames[m_frameIndex].first == CanFrameType::DeviceError) {
        CanUtils::appendActualIoFrame(this, expectedFrames[m_frameIndex]);
        auto deviceError = CanUtils::deviceError(expectedFrames[m_frameIndex]);
        setError(deviceError.first, deviceError.second);
        ++m_frameIndex;
    }
}

void MockSocketCanDevice::receiveIncomingFrames()
{
    auto expectedFrames = CanUtils::expectedCanIo(this);
    auto incomingFrames = CanBusFrameCollection{};
    while (m_frameIndex < m_frameCount &&
           expectedFrames[m_frameIndex].first == CanFrameType::IncomingCanFrame) {
        incomingFrames.append(expectedFrames[m_frameIndex].second);
        CanUtils::appendActualIoFrame(this, expectedFrames[m_frameIndex]);
        ++m_frameIndex;
    }
    enqueueReceivedFrames(incomingFrames);
}
