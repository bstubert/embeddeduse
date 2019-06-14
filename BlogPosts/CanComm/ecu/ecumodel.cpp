// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "canbus.h"
#include "ecumodel.h"

EcuModel::EcuModel(QObject *parent)
    : QObject{parent}
{
    auto errorStr = QString{};
    m_can0.reset(CanBus::setUp(QStringLiteral("socketcan"), QStringLiteral("can0"),
                                     errorStr));
    if (!errorStr.isEmpty()) {
        QMetaObject::invokeMethod(this,
                                  [this, errorStr]() { emit logMessage(errorStr); },
                                  Qt::QueuedConnection);
    }
    m_can0->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, true);

    m_a2.reset(new Ecu{2, m_can0});
    m_a2->setLogging(true);
    connect(m_a2.get(), &Ecu::logMessage,
            this, &EcuModel::logMessage);
}

EcuModel::~EcuModel()
{
    CanBus::tearDown(m_can0.get());
}
