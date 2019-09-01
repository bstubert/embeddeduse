// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "canbusrouter.h"
#include "mockcanutils.h"

class MockCanBusRouter : public CanBusRouter
{
public:
    MockCanBusRouter(const QString &interface = QString{"mcan0"}, QObject *parent = nullptr);
    ~MockCanBusRouter() override;

    MockCanFrameCollection actualCanFrames() const;
    void setActualCanFrames(const MockCanFrameCollection &frames);
    MockCanFrameCollection expectedCanFrames() const;
    void setExpectedCanFrames(const MockCanFrameCollection &frames);
};
