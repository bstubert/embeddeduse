// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#ifndef CANSIMULATOR_H
#define CANSIMULATOR_H

#include <QObject>
#include <QString>

class CanSimulator : public QObject
{
    Q_OBJECT

public:
    explicit CanSimulator(QObject *parent = nullptr);

signals:
    void logMessage(const QString &msg);

public slots:
    void simulateTxBufferOverflow();
};

#endif // CANSIMULATOR_H
