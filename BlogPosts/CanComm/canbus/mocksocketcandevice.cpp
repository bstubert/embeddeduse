// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>

#include <QMetaType>
#include <QtDebug>

#include "canbusext.h"
#include "mockcanutils.h"
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
    if (key == int(CanUtils::ConfigurationKey::ExpectedCanIo)) {
        m_frameIndex = 0;
        m_frameCount = CanUtils::expectedCanIo(this).size();
        checkForResponses();
    }
}

bool MockSocketCanDevice::writeFrame(const QCanBusFrame &frame)
{
    if (m_frameIndex >= m_frameCount) {
        qWarning() << "Expected no frame, but got " << frame.toString();
    }
    else {
        auto expectedFrame = QCanBusFrame{CanUtils::expectedCanIo(this)[m_frameIndex]};
        ++m_frameIndex;
        if (expectedFrame != frame) {
            qWarning() << "Expected " << expectedFrame.toString()
                       << ", but got " << frame.toString();
        }
    }
    CanUtils::appendActualIoFrame(this, CanUtils::makeOutgoingFrame(frame));
    emit framesWritten(1);
    checkForResponses();
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

void MockSocketCanDevice::checkForResponses()
{
    auto expectedFrameColl = CanUtils::expectedCanIo(this);
    auto incomingFrameColl = CanBusFrameCollection{};
    while (m_frameIndex < m_frameCount &&
           expectedFrameColl[m_frameIndex].type != ExpectedCanFrameType::OutgoingCanFrame) {
        CanUtils::appendActualIoFrame(this, expectedFrameColl[m_frameIndex]);
        if (expectedFrameColl[m_frameIndex].type == ExpectedCanFrameType::DeviceError) {
            auto deviceError = CanUtils::deviceError(expectedFrameColl[m_frameIndex]);
            setError(deviceError.first, deviceError.second);
        }
        else if (expectedFrameColl[m_frameIndex].type == ExpectedCanFrameType::IncomingCanFrame) {
            incomingFrameColl.append(expectedFrameColl[m_frameIndex]);
        }
        ++m_frameIndex;
    }
    enqueueReceivedFrames(incomingFrameColl);
}
