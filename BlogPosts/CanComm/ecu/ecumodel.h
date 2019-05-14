// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "ecu.h"

class EcuModel : public QObject
{
    Q_OBJECT

public:
    explicit EcuModel(QObject *parent = nullptr);
    virtual ~EcuModel();

signals:
    void logMessage(const QString &msg);

private:
    QSharedPointer<QCanBusDevice> m_can0;
    QSharedPointer<Ecu> m_a2;
};
