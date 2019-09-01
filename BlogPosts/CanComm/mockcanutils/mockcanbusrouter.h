// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "canbusrouter.h"
#include "mockcanutils.h"

class MockCanBusRouter : public CanBusRouter
{
public:
    MockCanBusRouter(const QString &interface = QString{"mcan0"}, QObject *parent = nullptr);
    ~MockCanBusRouter() override;

    void expectWriteFrame(const QCanBusFrame &frame);
    void expectReadFrame(const QCanBusFrame &frame);
    void expectError(QCanBusDevice::CanBusError deviceError, MockCanFrame::ErrorNo errorNo);

    MockCanFrameCollection actualCanFrames() const;
    MockCanFrameCollection expectedCanFrames() const;
};
