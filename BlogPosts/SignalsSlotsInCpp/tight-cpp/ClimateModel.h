// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <functional>

class ClimateEcuTwin;
class IoTClient;

class ClimateModel
{
public:
    ClimateModel(ClimateEcuTwin &twin, IoTClient &client);
    void setInsideTemperature(int temperature);

    std::function<void(int)> temperatureChanged;

private:
    ClimateEcuTwin &m_twin;
    IoTClient &m_client;
    int m_temperature{18};
};
