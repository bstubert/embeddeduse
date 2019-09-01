// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "canbus.h"
#include "ecumodel.h"

EcuModel::EcuModel(QObject *parent)
    : QObject{parent}
{
    m_can0.reset(createCanBusDevice("can0"));

    m_a2.reset(createEcu(2));
    m_a3.reset(createEcu(3));
}

EcuModel::~EcuModel()
{
}

bool EcuModel::isSkipResponseEnabled() const
{
    return m_a2->isSkipResponseEnabled();
}

void EcuModel::setSkipResponseEnabled(bool enabled)
{
    m_a2->setSkipResponseEnabled(enabled);
}

bool EcuModel::isMissingResponsesEnabled() const
{
    return m_a2->isMissingResponsesEnabled();
}

void EcuModel::setMissingResponsesEnabled(bool enabled)
{
    m_a2->setMissingResponsesEnabled(enabled);
}

void EcuModel::sendFramesFromTwoEcus()
{
    m_a2->sendUnsolicitedFrames();
    m_a3->sendUnsolicitedFrames();
}

Ecu *EcuModel::createEcu(int ecuId)
{
    auto ecu = new Ecu{ecuId, m_can0.get()};
    ecu->setLogging(true);
    connect(m_can0.get(), &QCanBusDevice::errorOccurred,
            ecu, &Ecu::onErrorOccurred);
    connect(m_can0.get(), &QCanBusDevice::framesReceived,
            ecu, &Ecu::onFramesReceived);
//    connect(ecuProxy, &EcuProxy::frameToWrite,
//            m_can0.get(), &QCanBusDevice::writeFrame);
    connect(ecu, &Ecu::logMessage,
            this, &EcuModel::logMessage);
    connect(ecu, &Ecu::skipResponseEnabledChanged,
            this, &EcuModel::skipResponseEnabledChanged);
    connect(ecu, &Ecu::missingResponsesEnabledChanged,
            this, &EcuModel::missingResponsesEnabledChanged);
    return ecu;
}

QCanBusDevice *EcuModel::createCanBusDevice(const QString &interface)
{
    auto errorStr = QString{};
    auto device = CanBus::setUp(QStringLiteral("socketcan"), interface, errorStr);
    if (!errorStr.isEmpty()) {
        QMetaObject::invokeMethod(this,
                                  [this, errorStr]() { emit logMessage(errorStr); },
                                  Qt::QueuedConnection);
    }
    device->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, true);
    device->setConfigurationParameter(QCanBusDevice::LoopbackKey, false);
    return device;
}
