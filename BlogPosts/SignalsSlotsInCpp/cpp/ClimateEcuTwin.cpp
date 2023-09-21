// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "ClimateEcuTwin.h"

ClimateEcuTwin::ClimateEcuTwin()
{
}

void ClimateEcuTwin::setInsideTemperature(int temperature)
{
    std::cout << "With C++: Send temperature " << temperature << " to Climate ECU." << std::endl;
}
