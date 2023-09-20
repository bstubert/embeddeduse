// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "IoTClient.h"

IoTClient::IoTClient()
{
}

void IoTClient::setTemperature(int temperature)
{
    std::cout << "With tightly coupled C++: Send temperature " << temperature << " to IoT cloud." << std::endl;
}
