// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <QObject>

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateModel model;
    ClimateEcuTwin twin;
    QObject::connect(&model, &ClimateModel::temperatureChanged,
                     &twin, &ClimateEcuTwin::setTemperature);
    model.setTemperature(15);
}
