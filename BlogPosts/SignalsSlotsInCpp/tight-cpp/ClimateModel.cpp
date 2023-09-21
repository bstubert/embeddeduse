// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateModel.h"
#include "ClimateEcuTwin.h"
#include "IoTClient.h"

ClimateModel::ClimateModel(ClimateEcuTwin &twin, IoTClient &client)
    : m_twin{twin}
    , m_client{client}
{
}

void ClimateModel::setInsideTemperature(int temperature)
{
    if (m_temperature == temperature)
        return;
    m_temperature = temperature;
    m_twin.setInsideTemperature(m_temperature);
    m_client.setInsideTemperature(m_temperature);
}

