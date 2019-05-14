// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include "ecumodel.h"

EcuModel::EcuModel(QObject *parent)
    : QObject{parent}
{
    auto errorMsg = QString{};
    m_can0.reset(QCanBus::instance()->createDevice(QStringLiteral("socketcan"),
                                                   QStringLiteral("can0"),
                                                   &errorMsg));
    if (m_can0 == nullptr) {
        QMetaObject::invokeMethod(this,
                                  [this, errorMsg]() { emit logMessage(errorMsg); },
                                  Qt::QueuedConnection);
    }
    if (m_can0 != nullptr && !m_can0->connectDevice()) {
        QMetaObject::invokeMethod(this,
                                  [this]() { emit logMessage(m_can0->errorString()); },
                                  Qt::QueuedConnection);
    }

    m_a2.reset(new Ecu{2, m_can0});
    m_a2->setLogging(true);
    connect(m_a2.get(), &Ecu::logMessage,
            this, &EcuModel::logMessage);
}

EcuModel::~EcuModel()
{
    if (m_can0 != nullptr && m_can0->state() == QCanBusDevice::ConnectedState) {
        m_can0->disconnectDevice();
    }
}
