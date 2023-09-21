// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateModel.h"

ClimateModel::ClimateModel(QObject *parent)
    : QObject{parent}
{
}

void ClimateModel::setInsideTemperature(int temperature)
{
    if (m_insideTemperature == temperature)
        return;
    m_insideTemperature = temperature;
    emit temperatureChanged(m_insideTemperature);
}
