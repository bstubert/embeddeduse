// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <functional>

class ClimateModel
{
public:
    ClimateModel();
    void setInsideTemperature(int temperature);

    std::function<void(int)> temperatureChanged;

private:
    int m_insideTemperature{18};
};
