// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QSharedPointer>
#include <QObject>
#include <QString>
#include "ecuproxy.h"
class QCanBusDevice;
class EcuProxy;

class TerminalModel : public QObject
{
    Q_OBJECT

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();

signals:
    void logMessage(const QString &msg);

public slots:
    void simulateTxBufferOverflow(int count);

private:
    QSharedPointer<QCanBusDevice> m_can0;
    QSharedPointer<EcuProxy> m_a2Proxy;
};
