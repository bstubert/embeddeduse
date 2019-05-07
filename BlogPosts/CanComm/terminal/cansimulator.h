// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#ifndef CANSIMULATOR_H
#define CANSIMULATOR_H

#include <QObject>
#include <QString>
#include "ecuproxy.h"
class EcuProxy;

class CanSimulator : public QObject
{
    Q_OBJECT

public:
    explicit CanSimulator(QObject *parent = nullptr);

signals:
    void logMessage(const QString &msg);

public slots:
    void simulateTxBufferOverflow();
    void onParameterRead(quint16 pid, quint32 value);

private slots:
    void initLater();

private:
    EcuProxy *m_ecuProxy{nullptr};
};

#endif // CANSIMULATOR_H
