// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "mockcanbusrouter.h"

MockCanBusRouter::MockCanBusRouter(const QString &interface, QObject *parent)
    : CanBusRouter{"mockcan", interface, parent}
{
    setActualCanFrames({});
    setExpectedCanFrames({});
}

MockCanBusRouter::~MockCanBusRouter()
{
}

MockCanFrameCollection MockCanBusRouter::actualCanFrames() const
{
    return ::actualCanFrames(m_device);
}

void MockCanBusRouter::setActualCanFrames(const MockCanFrameCollection &frames)
{
    ::setActualCanFrames(m_device, frames);
}

MockCanFrameCollection MockCanBusRouter::expectedCanFrames() const
{
    return ::expectedCanFrames(m_device);
}

void MockCanBusRouter::setExpectedCanFrames(const MockCanFrameCollection &frames)
{
    ::setExpectedCanFrames(m_device, frames);
}

int MockCanBusRouter::expectedFrameCount(MockCanFrame::Type frameType)
{
    return ::expectedCanFrameCount(m_device, frameType);
}
