// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QMetaObject>
#include <QtDebug>
#include "cansimulator.h"

CanSimulator::CanSimulator(QObject *parent)
    : QObject{parent}
{
    QMetaObject::invokeMethod(this, &CanSimulator::initLater, Qt::QueuedConnection);
}

void CanSimulator::onParameterRead(quint16 pid, quint32 value)
{
    emit logMessage(QString("%1 -> %2").arg(pid).arg(value));
}

void CanSimulator::initLater()
{
    m_ecuProxy = new Ecu{QStringLiteral("socketcan"), QStringLiteral("can0"), this};
    if (!m_ecuProxy->isConnected()) {
        emit logMessage(QStringLiteral("ERROR: Could not connect to CAN bus device."));
        return;
    }
    connect(m_ecuProxy, &Ecu::logMessage,
            this, &CanSimulator::logMessage);
    connect(m_ecuProxy, &Ecu::parameterRead,
            this, &CanSimulator::onParameterRead);
}
