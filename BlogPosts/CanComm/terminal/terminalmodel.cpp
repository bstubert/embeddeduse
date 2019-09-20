// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QString>

#include "canbusrouter.h"
#include "ecuproxy.h"
#include "terminalmodel.h"

TerminalModel::TerminalModel(QObject *parent)
    : QObject{parent}
    , m_router{new CanBusRouter{1, "socketcan", "can0", this}}
    , m_a2Proxy{createEcuProxy(2)}
    , m_a3Proxy{createEcuProxy(3)}
{
    setLoggingOn(true);
    setTxBufferOn(false);
}

TerminalModel::~TerminalModel()
{
}

bool TerminalModel::isLoggingOn() const
{
    return m_a2Proxy->isLogging();
}

void TerminalModel::setLoggingOn(bool isOn)
{
    m_a2Proxy->setLogging(isOn);
    m_a3Proxy->setLogging(isOn);
    emit loggingOnChanged();
}

bool TerminalModel::isTxBufferOn() const
{
    return m_router->isReceiveOwnFrameEnabled();
}

// NOTE: The write buffer overflow only happens, if logging is switched off. Logging introduces
// a delay between two writeFrame() calls big enough to avoid the overflow.
void TerminalModel::setTxBufferOn(bool isOn)
{
    m_router->setReceiveOwnFrameEnabled(isOn);
    emit txBufferOnChanged();
}

void TerminalModel::simulateTxBufferOverflow(int count)
{
    for (quint16 i = 1; i <= count; ++i) {
        m_a2Proxy->sendReadParameter(i);
    }
}

EcuProxy *TerminalModel::createEcuProxy(int ecuId)
{
    auto ecuProxy = new EcuProxy{ecuId, m_router, this};
    connect(m_router, &CanBusRouter::errorOccurred,
            ecuProxy, &EcuProxy::onErrorOccurred);
    connect(m_router, &CanBusRouter::framesReceived,
            ecuProxy, &EcuProxy::onFramesReceived);
    connect(ecuProxy, &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
    return ecuProxy;
}
