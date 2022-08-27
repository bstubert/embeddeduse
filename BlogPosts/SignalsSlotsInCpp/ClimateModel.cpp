// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateModel.h"

ClimateModel::ClimateModel(QObject *parent)
    : QObject{parent}
{
}

void ClimateModel::setTemperature(int temperature)
{
    m_temperature = temperature;
    emit temperatureChanged(m_temperature);
}
