// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateModel model;
    ClimateEcuTwin twin;
    model.temperatureChanged = [&twin](int temperature)
    {
        twin.setTemperature(temperature);
    };
    model.setTemperature(14);
}
