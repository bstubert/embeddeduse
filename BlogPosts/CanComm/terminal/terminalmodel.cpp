// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBusDevice>
#include <QString>
#include <QtDebug>

#include "canbusrouter.h"
#include "ecuproxy.h"
#include "terminalmodel.h"
#include "transmission_proxy.h"

namespace
{
QCanBusDevice::Filter createEcuFilter(int ecuId)
{
    auto filter{QCanBusDevice::Filter{}};
    filter.frameId = static_cast<quint32>(ecuId);
    filter.frameIdMask = 0xFFU;
    filter.type = QCanBusFrame::DataFrame;
    filter.format = QCanBusDevice::Filter::MatchExtendedFormat;
    return filter;
}

// TODO: Find out why blocking filter produces this error:
// ERROR: FrameId 536870914 larger than 29 bit..
//QCanBusDevice::Filter createEcuBlocker(int ecuId)
//{
//    auto filter{QCanBusDevice::Filter{}};
//    filter.frameId = static_cast<quint32>(ecuId) | 0x20000000U;
//    filter.frameIdMask = 0xFFU;
//    filter.type = QCanBusFrame::DataFrame;
//    filter.format = QCanBusDevice::Filter::MatchExtendedFormat;
//    return filter;
//}
}


TerminalModel::TerminalModel(QObject *parent)
    : QObject{parent}
    , m_router{new CanBusRouter{1, "socketcan", "can0", this}}
    , m_a2Proxy{new EcuProxy{2, m_router, this}}
    , m_a3Proxy{new TransmissionProxy{m_router, this}}
{
    connectProxy(m_a2Proxy);
    connectProxy(m_a3Proxy);

    setLoggingOn(true);
    setTxBufferOn(false);
}

TerminalModel::~TerminalModel()
{
}

bool TerminalModel::isFilterOn() const
{
    return false;
}

void TerminalModel::setFilterOn(bool isOn)
{
    if (isOn)
    {
        m_router->setRawFilters({createEcuFilter(2)});
    }
    else
    {
        m_router->setRawFilters({QCanBusDevice::Filter{}});
    }
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

void TerminalModel::connectProxy(EcuProxy *proxy)
{
    connect(m_router, &CanBusRouter::errorOccurred,
            proxy, &EcuProxy::onErrorOccurred);
    connect(m_router, &CanBusRouter::framesReceived,
            proxy, &EcuProxy::onFramesReceived);
    connect(proxy, &EcuProxy::logMessage,
            this, &TerminalModel::logMessage);
}
