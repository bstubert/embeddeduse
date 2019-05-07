// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>
#include <QString>
#include "ecu.h"
class Ecu;

class CanSimulator : public QObject
{
    Q_OBJECT

public:
    explicit CanSimulator(QObject *parent = nullptr);

signals:
    void logMessage(const QString &msg);

public slots:
    void onParameterRead(quint16 pid, quint32 value);

private slots:
    void initLater();

private:
    Ecu *m_ecuProxy{nullptr};
};
