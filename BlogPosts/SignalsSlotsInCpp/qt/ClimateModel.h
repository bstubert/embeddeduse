// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <QObject>

class ClimateModel : public QObject
{
    Q_OBJECT

public:
    ClimateModel(QObject *parent = nullptr);
    void setTemperature(int temperature);

signals:
    void temperatureChanged(int temperature);

private:
    int m_temperature{18};
};
