// Copyright (C) 2022 Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <QObject>

class ClimateEcuTwin : public QObject
{
    Q_OBJECT

public:
    ClimateEcuTwin(QObject *parent = nullptr);

public slots:
    void setInsideTemperature(int temperature);
};
