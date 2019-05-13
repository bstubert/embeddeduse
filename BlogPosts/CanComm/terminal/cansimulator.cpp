// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QMetaObject>
#include <QtDebug>
#include "cansimulator.h"

TerminalModel::TerminalModel(QObject *parent)
    : QObject{parent}
{
    QMetaObject::invokeMethod(this, &TerminalModel::initLater, Qt::QueuedConnection);
}

void TerminalModel::simulateTxBufferOverflow(int count)
{
    if (m_ecuProxy == nullptr) {
        return;
    }
    for (quint16 i = 1; i <= count; ++i) {
        m_ecuProxy->sendReadParameter(i);
    }
}

void TerminalModel::initLater()
{
    m_ecuProxy = new EcuProxy{QStringLiteral("socketcan"), QStringLiteral("can0"), this};
    m_ecuProxy->setLogging(false);
    if (!m_ecuProxy->isConnected()) {
        emit logMessage(QStringLiteral("ERROR: Could not connect to CAN bus device."));
        return;
    }
    connect(m_ecuProxy, &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
}
