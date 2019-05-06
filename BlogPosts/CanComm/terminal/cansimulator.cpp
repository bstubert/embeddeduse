// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QtDebug>
#include "cansimulator.h"

CanSimulator::CanSimulator(QObject *parent)
    : QObject(parent)
{
}

void CanSimulator::simulateTxBufferOverflow()
{
    for (int i = 0; i < 50; ++i) {
        emit logMessage(QString("Line %1").arg(i));
    }
}
