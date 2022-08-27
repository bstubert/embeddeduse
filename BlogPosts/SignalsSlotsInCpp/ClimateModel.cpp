// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"

ClimateModel::ClimateModel(ClimateEcuTwin *twin)
    : m_twin{twin}
{
}

void ClimateModel::setTemperature(int temperature)
{
    m_temperature = temperature;
    m_twin->setTemperature(m_temperature);
}
