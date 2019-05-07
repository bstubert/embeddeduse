// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QtDebug>
#include "cansimulator.h"

CanSimulator::CanSimulator(QObject *parent)
    : QObject(parent)
{
    connect(&m_ecuProxy, &EcuProxy::parameterRead,
            this, &CanSimulator::onParameterRead);
}

void CanSimulator::simulateTxBufferOverflow()
{
    for (quint16 i = 0; i < 50; ++i) {
        m_ecuProxy.readParameter(i);
    }
}

void CanSimulator::onParameterRead(quint16 pid, quint32 value)
{
    emit logMessage(QString("%1 -> %2").arg(pid).arg(value));
}
