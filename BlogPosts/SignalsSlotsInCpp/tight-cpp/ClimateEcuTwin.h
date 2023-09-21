// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#pragma once

class ClimateModel;

class ClimateEcuTwin
{
public:
    ClimateEcuTwin();
    void setObserver(ClimateModel *model);
    void setInsideTemperature(int temperature);
    void setOutsideTemperature(int temperature);

private:
    ClimateModel *m_model;
};
