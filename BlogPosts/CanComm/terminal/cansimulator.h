// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>
#include <QString>
#include "ecuproxy.h"
class EcuProxy;

class TerminalModel : public QObject
{
    Q_OBJECT

public:
    explicit TerminalModel(QObject *parent = nullptr);

signals:
    void logMessage(const QString &msg);

public slots:
    void simulateTxBufferOverflow(int count);

private slots:
    void initLater();

private:
    EcuProxy *m_ecuProxy{nullptr};
};
