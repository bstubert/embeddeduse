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
}

TerminalModel::~TerminalModel()
{
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
    // NOTE: The write buffer overflow only happens, if logging is switched off. Logging introduces
    // a delay between two writeFrame() calls big enough to avoid the overflow.
    ecuProxy->setLogging(true);
    connect(m_router, &CanBusRouter::errorOccurred,
            ecuProxy, &EcuProxy::onErrorOccurred);
    connect(m_router, &CanBusRouter::framesReceived,
            ecuProxy, &EcuProxy::onFramesReceived);
    connect(ecuProxy, &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
    return ecuProxy;
}
