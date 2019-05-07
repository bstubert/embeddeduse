// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QMetaObject>
#include <QtDebug>
#include "cansimulator.h"

CanSimulator::CanSimulator(QObject *parent)
    : QObject{parent}
{
    QMetaObject::invokeMethod(this, &CanSimulator::initLater, Qt::QueuedConnection);
}

void CanSimulator::simulateTxBufferOverflow()
{
    if (m_ecuProxy == nullptr) {
        return;
    }
    for (quint16 i = 1; i <= 50; ++i) {
        m_ecuProxy->sendReadParameter(i);
    }
}

void CanSimulator::initLater()
{
    m_ecuProxy = new EcuProxy{QStringLiteral("socketcan"), QStringLiteral("can0"), this};
    if (!m_ecuProxy->isConnected()) {
        emit logMessage(QStringLiteral("ERROR: Could not connect to CAN bus device."));
        return;
    }
    connect(m_ecuProxy, &EcuProxy::logMessage,
            this, &CanSimulator::logMessage);
}
