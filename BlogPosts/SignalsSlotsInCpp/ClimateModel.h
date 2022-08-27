// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#pragma once

class ClimateEcuTwin;

class ClimateModel
{
public:
    ClimateModel(ClimateEcuTwin *twin);
    void setTemperature(int temperature);

private:
    ClimateEcuTwin *m_twin{nullptr};
    int m_temperature{18};
};
