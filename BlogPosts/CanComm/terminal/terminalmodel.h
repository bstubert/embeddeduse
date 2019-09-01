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

    Q_PROPERTY(bool directWriteEnabled READ isDirectWriteEnabled WRITE setDirectWriteEnabled
               NOTIFY directWriteEnabledChanged)

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();
    bool isSkipWriteEnabled() const;
    void setSkipWriteEnabled(bool enabled);
    bool isDirectWriteEnabled() const;
    void setDirectWriteEnabled(bool enabled);

signals:
    void logMessage(const QString &msg);
    void skipWriteEnabledChanged();
    void directWriteEnabledChanged();

public slots:
    void simulateTxBufferOverflow(int count);

private:
    EcuProxy *createEcuProxy(int ecuId);
    QCanBusDevice *createCanBusDevice(const QString &interface);

    QSharedPointer<EcuProxy> m_a2Proxy;
    QSharedPointer<EcuProxy> m_a3Proxy;
};
