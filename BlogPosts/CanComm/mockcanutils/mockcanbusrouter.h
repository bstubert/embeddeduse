// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QVector>

#include "canbusrouter.h"
#include "mockcanutils.h"

class MockCanBusRouter : public CanBusRouter
{
public:
    MockCanBusRouter(const QString &interface = QString{"mcan0"}, QObject *parent = nullptr);
    ~MockCanBusRouter() override;

    void setWriteErrorInterval(int interval);

    void expectWriteFrame(const QCanBusFrame &frame);
    void expectWriteFrames(const QVector<QCanBusFrame> &frames);
    void expectReadFrame(const QCanBusFrame &frame);
    void expectReadFrames(const QVector<QCanBusFrame> &frames);
    void expectError(QCanBusDevice::CanBusError deviceError, MockCanFrame::ErrorNo errorNo);

    MockCanFrameCollection actualCanFrames() const;
    MockCanFrameCollection expectedCanFrames() const;
};
