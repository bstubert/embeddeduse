// Copyright (C) Burkhard Stubert (DBA EmbeddedUse)

#pragma once

#include <QObject>

class IoTClient : public QObject
{
    Q_OBJECT

public:
    IoTClient(QObject *parent = nullptr);

public slots:
    void setTemperature(int temperature);
};
