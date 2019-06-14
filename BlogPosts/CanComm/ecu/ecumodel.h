// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "ecu.h"

class EcuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool skipResponseEnabled READ isSkipResponseEnabled WRITE setSkipResponseEnabled
               NOTIFY skipResponseEnabledChanged)

public:
    explicit EcuModel(QObject *parent = nullptr);
    virtual ~EcuModel();
    bool isSkipResponseEnabled() const;
    void setSkipResponseEnabled(bool enabled);

signals:
    void logMessage(const QString &msg);
    void skipResponseEnabledChanged();

private:
    QSharedPointer<QCanBusDevice> m_can0;
    QSharedPointer<Ecu> m_a2;
};
