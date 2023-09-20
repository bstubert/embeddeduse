// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"
#include "IoTClient.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateEcuTwin twin;
    IoTClient client;
    ClimateModel model{twin, client};
    model.setTemperature(23);
}
