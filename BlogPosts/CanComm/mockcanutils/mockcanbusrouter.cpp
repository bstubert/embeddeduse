// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "mockcanbusrouter.h"

MockCanBusRouter::MockCanBusRouter(const QString &interface, QObject *parent)
    : CanBusRouter{"mockcan", interface, parent}
{
}

MockCanBusRouter::~MockCanBusRouter()
{
}

MockCanFrameCollection MockCanBusRouter::actualCanFrames() const
{
    return m_device->configurationParameter(int(MockConfigurationKey::ActualCanIo))
            .value<MockCanFrameCollection>();
}

void MockCanBusRouter::setActualCanFrames(const MockCanFrameCollection &frames)
{
    m_device->setConfigurationParameter(int(MockConfigurationKey::ActualCanIo),
                                        QVariant::fromValue(frames));
}

MockCanFrameCollection MockCanBusRouter::expectedCanFrames() const
{
    return m_device->configurationParameter(int(MockConfigurationKey::ExpectedCanIo))
            .value<MockCanFrameCollection>();
}

void MockCanBusRouter::setExpectedCanFrames(const MockCanFrameCollection &frames)
{
    m_device->setConfigurationParameter(int(MockConfigurationKey::ExpectedCanIo),
                                        QVariant::fromValue(frames));
}
