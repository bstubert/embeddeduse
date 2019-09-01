// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "canbus.h"
#include "terminalmodel.h"

TerminalModel::TerminalModel(QObject *parent)
    : QObject{parent}
{
    m_can0.reset(createCanBusDevice("can0"));

    m_a2Proxy.reset(createEcuProxy(2));
    m_a3Proxy.reset(createEcuProxy(3));
}

TerminalModel::~TerminalModel()
{
    CanBus::tearDown(m_can0.get());
}

bool TerminalModel::isSkipWriteEnabled() const
{
    return m_a2Proxy->isSkipWriteEnabled();
}

void TerminalModel::setSkipWriteEnabled(bool enabled)
{
    m_a2Proxy->setSkipWriteEnabled(enabled);
}

bool TerminalModel::isDirectWriteEnabled() const
{
    return m_a2Proxy->isDirectWriteEnabled();
}

void TerminalModel::setDirectWriteEnabled(bool enabled)
{
    m_a2Proxy->setDirectWriteEnabled(enabled);
}

void TerminalModel::simulateTxBufferOverflow(int count)
{
    for (quint16 i = 1; i <= count; ++i) {
        m_a2Proxy->sendReadParameter(i);
    }
}

EcuProxy *TerminalModel::createEcuProxy(int ecuId)
{
    auto ecuProxy = new EcuProxy{ecuId, m_can0.get()};
    ecuProxy->setLogging(true);
    connect(m_can0.get(), &QCanBusDevice::errorOccurred,
            ecuProxy, &EcuProxy::onErrorOccurred);
    connect(m_can0.get(), &QCanBusDevice::framesReceived,
            ecuProxy, &EcuProxy::onFramesReceived);
//    connect(ecuProxy, &EcuProxy::frameToWrite,
//            m_can0.get(), &QCanBusDevice::writeFrame);
    connect(ecuProxy, &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
    connect(ecuProxy, &EcuProxy::skipWriteEnabledChanged,
            this, &TerminalModel::skipWriteEnabledChanged);
    connect(ecuProxy, &EcuProxy::directWriteEnabledChanged,
            this, &TerminalModel::directWriteEnabledChanged);
    return ecuProxy;
}

QCanBusDevice *TerminalModel::createCanBusDevice(const QString &interface)
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
