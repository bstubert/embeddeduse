// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "IoTClient.h"

IoTClient::IoTClient()
{
}

void IoTClient::setInsideTemperature(int temperature)
{
    std::cout << "With tightly coupled C++: Send outside temperature " << temperature << " to IoT cloud."
        << std::endl;
}
