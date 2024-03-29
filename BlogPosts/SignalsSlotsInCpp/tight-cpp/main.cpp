// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"
#include "IoTClient.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateEcuTwin twin;
    IoTClient client;
    ClimateModel model;

    model.setObservers(&twin, &client);
    twin.setObserver(&model);

    model.setInsideTemperature(16);

    twin.setOutsideTemperature(27);
}
