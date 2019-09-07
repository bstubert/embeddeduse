// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>

class QString;

class CanBusRouter;
class EcuProxy;

class TerminalModel : public QObject
{
    Q_OBJECT

public:
    explicit TerminalModel(QObject *parent = nullptr);
    virtual ~TerminalModel();

public slots:
    void simulateTxBufferOverflow(int count);

signals:
    void logMessage(const QString &msg);

private:
    EcuProxy *createEcuProxy(int ecuId);

    CanBusRouter *m_router;
    EcuProxy *m_a2Proxy;
    EcuProxy *m_a3Proxy;
};
