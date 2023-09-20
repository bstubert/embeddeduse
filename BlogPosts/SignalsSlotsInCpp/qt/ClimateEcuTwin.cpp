// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "ClimateEcuTwin.h"

ClimateEcuTwin::ClimateEcuTwin(QObject *parent)
    : QObject{parent}
{
}

void ClimateEcuTwin::setTemperature(int temperature)
{
    std::cout << "With Qt: Send temperature " << temperature << " to Climate ECU." << std::endl;
}
