// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "IoTClient.h"

IoTClient::IoTClient(QObject *parent)
    : QObject(parent)
{

}

void IoTClient::setInsideTemperature(int temperature)
{
    std::cout << "With Qt: Send temperature " << temperature << " to IoT cloud." << std::endl;
}
