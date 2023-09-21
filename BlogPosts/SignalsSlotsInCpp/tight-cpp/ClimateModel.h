// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <functional>

class ClimateEcuTwin;
class IoTClient;

class ClimateModel
{
public:
    ClimateModel();
    void setObservers(ClimateEcuTwin *twin, IoTClient *client);
    void setInsideTemperature(int temperature);
    void setOutsideTemperature(int temperature);

private:
    ClimateEcuTwin *m_twin;
    IoTClient *m_client;
    int m_insideTemperature{18};
    int m_outsideTemperature{12};
};
