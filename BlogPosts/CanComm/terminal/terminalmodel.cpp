// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include "terminalmodel.h"

TerminalModel::TerminalModel(QObject *parent)
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
    m_a2Proxy.reset(new EcuProxy{2, m_can0});
    m_a2Proxy->setLogging(true);
    connect(m_a2Proxy.get(), &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
}

TerminalModel::~TerminalModel()
{
    if (m_can0 != nullptr && m_can0->state() == QCanBusDevice::ConnectedState) {
        m_can0->disconnectDevice();
    }
}

void TerminalModel::simulateTxBufferOverflow(int count)
{
    for (quint16 i = 1; i <= count; ++i) {
        m_a2Proxy->sendReadParameter(i);
    }
}
