// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>

class QString;

class CanBusRouter;
class EcuProxy;

class TerminalModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isLoggingOn READ isLoggingOn WRITE setLoggingOn
               NOTIFY loggingOnChanged)
    Q_PROPERTY(bool isTxBufferOn READ isTxBufferOn WRITE setTxBufferOn
               NOTIFY txBufferOnChanged)

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();

    bool isLoggingOn() const;
    void setLoggingOn(bool isOn);

    bool isTxBufferOn() const;
    void setTxBufferOn(bool isOn);

public slots:
    void simulateTxBufferOverflow(int count);

signals:
    void logMessage(const QString &msg);
    void loggingOnChanged();
    void txBufferOnChanged();

private:
    EcuProxy *createEcuProxy(int ecuId);

    CanBusRouter *m_router;
    EcuProxy *m_a2Proxy;
    EcuProxy *m_a3Proxy;
};
