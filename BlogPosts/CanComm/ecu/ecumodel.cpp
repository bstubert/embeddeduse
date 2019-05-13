// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QMetaObject>
#include <QtDebug>
#include "ecumodel.h"

EcuModel::EcuModel(QObject *parent)
    : QObject{parent}
{
    QMetaObject::invokeMethod(this, &EcuModel::initLater, Qt::QueuedConnection);
}

void EcuModel::onParameterRead(quint16 pid, quint32 value)
{
    emit logMessage(QString("%1 -> %2").arg(pid).arg(value));
}

void EcuModel::initLater()
{
    m_ecu = new Ecu{QStringLiteral("socketcan"), QStringLiteral("can0"), this};
    m_ecu->setLogging(true);
    if (!m_ecu->isConnected()) {
        emit logMessage(QStringLiteral("ERROR: Could not connect to CAN bus device."));
        return;
    }
    connect(m_ecu, &Ecu::logMessage,
            this, &EcuModel::logMessage);
    connect(m_ecu, &Ecu::parameterRead,
            this, &EcuModel::onParameterRead);
}
