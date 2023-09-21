// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "ClimateModel.h"
#include "ClimateEcuTwin.h"
#include "IoTClient.h"

ClimateModel::ClimateModel()
{
}

void ClimateModel::setObservers(ClimateEcuTwin *twin, IoTClient *client)
{
    m_twin = twin;
    m_client = client;
}

void ClimateModel::setInsideTemperature(int temperature)
{
    if (m_insideTemperature == temperature)
        return;
    m_insideTemperature = temperature;
    m_twin->setInsideTemperature(m_insideTemperature);
    m_client->setInsideTemperature(m_insideTemperature);
}

void ClimateModel::setOutsideTemperature(int temperature)
{
    if (m_outsideTemperature == temperature)
        return;
    m_outsideTemperature = temperature;
    std::cout << "With tightly coupled C++: Received outside temperature " << temperature << " from Climate ECU."
        << std::endl;
}

