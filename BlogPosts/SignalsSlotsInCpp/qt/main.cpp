// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <QObject>

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"
#include "IoTClient.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    ClimateModel model;
    ClimateEcuTwin twin;
    IoTClient client;
    QObject::connect(&model, &ClimateModel::temperatureChanged,
                     &twin, &ClimateEcuTwin::setTemperature);
    QObject::connect(&model, &ClimateModel::temperatureChanged,
                     &client, &IoTClient::setTemperature);
    model.setTemperature(15);
}
