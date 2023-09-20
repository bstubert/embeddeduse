// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "ClimateEcuTwin.h"

ClimateEcuTwin::ClimateEcuTwin()
{
}

void ClimateEcuTwin::setTemperature(int temperature)
{
    std::cout << "With tightly coupled C++: Send temperature " << temperature << " to Climate ECU." << std::endl;
}
