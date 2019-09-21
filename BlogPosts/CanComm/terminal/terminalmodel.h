// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>

class QString;

class CanBusRouter;
class EcuProxy;

class TerminalModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isFilterOn READ isFilterOn WRITE setFilterOn
               NOTIFY filterOnChanged)
    Q_PROPERTY(bool isTxBufferOn READ isTxBufferOn WRITE setTxBufferOn
               NOTIFY txBufferOnChanged)
    Q_PROPERTY(bool isLoggingOn READ isLoggingOn WRITE setLoggingOn
               NOTIFY loggingOnChanged)

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();

    bool isFilterOn() const;
    void setFilterOn(bool isOn);

    bool isTxBufferOn() const;
    void setTxBufferOn(bool isOn);

    bool isLoggingOn() const;
    void setLoggingOn(bool isOn);

public slots:
    void simulateTxBufferOverflow(int count);

signals:
    void logMessage(const QString &msg);
    void filterOnChanged();
    void txBufferOnChanged();
    void loggingOnChanged();

private:
    EcuProxy *createEcuProxy(int ecuId);

    CanBusRouter *m_router;
    EcuProxy *m_a2Proxy;
    EcuProxy *m_a3Proxy;
};
