// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "canbus.h"
#include "terminalmodel.h"

TerminalModel::TerminalModel(QObject *parent)
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

    m_a2Proxy.reset(new EcuProxy{2, m_can0});
    m_a2Proxy->setLogging(true);
    connect(m_a2Proxy.get(), &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
    connect(m_a2Proxy.get(), &EcuProxy::skipWriteEnabledChanged,
            this, &TerminalModel::skipWriteEnabledChanged);
    connect(m_a2Proxy.get(), &EcuProxy::directWriteEnabledChanged,
            this, &TerminalModel::directWriteEnabledChanged);
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
