// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateModel.h"

ClimateModel::ClimateModel()
{
}

void ClimateModel::setTemperature(int temperature)
{
    if (m_temperature == temperature)
        return;
    m_temperature = temperature;
    temperatureChanged(m_temperature);
}
