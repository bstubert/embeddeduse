// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#include <iostream>

#include "ClimateEcuTwin.h"
#include "ClimateModel.h"

ClimateEcuTwin::ClimateEcuTwin()
{
}

void ClimateEcuTwin::setObserver(ClimateModel *model)
{
    m_model = model;
}

void ClimateEcuTwin::setInsideTemperature(int temperature)
{
    std::cout << "With tightly coupled C++: Send outside temperature " << temperature << " to Climate ECU."
        << std::endl;
}

void ClimateEcuTwin::setOutsideTemperature(int temperature)
{
    m_model->setOutsideTemperature(temperature);
}
