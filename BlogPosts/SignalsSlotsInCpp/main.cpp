// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateEcuTwin twin;
    ClimateModel model{&twin};
    model.setTemperature(16);
}
