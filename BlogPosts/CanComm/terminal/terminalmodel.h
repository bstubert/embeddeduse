// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "ecuproxy.h"

class TerminalModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool skipWriteEnabled READ isSkipWriteEnabled WRITE setSkipWriteEnabled
               NOTIFY skipWriteEnabledChanged)

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();
    bool isSkipWriteEnabled() const;
    void setSkipWriteEnabled(bool enabled);

signals:
    void logMessage(const QString &msg);
    void skipWriteEnabledChanged();

public slots:
    void simulateTxBufferOverflow(int count);

private:
    QSharedPointer<QCanBusDevice> m_can0;
    QSharedPointer<EcuProxy> m_a2Proxy;
};
