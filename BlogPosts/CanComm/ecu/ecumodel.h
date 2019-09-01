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

    Q_PROPERTY(bool missingResponsesEnabled READ isMissingResponsesEnabled
               WRITE setMissingResponsesEnabled NOTIFY missingResponsesEnabledChanged)

public:
    explicit EcuModel(QObject *parent = nullptr);
    virtual ~EcuModel();
    bool isSkipResponseEnabled() const;
    void setSkipResponseEnabled(bool enabled);
    bool isMissingResponsesEnabled() const;
    void setMissingResponsesEnabled(bool enabled);

public slots:
    void sendFramesFromTwoEcus();

signals:
    void logMessage(const QString &msg);
    void skipResponseEnabledChanged();
    void missingResponsesEnabledChanged();

private:
    Ecu *createEcu(int ecuId);
    QCanBusDevice *createCanBusDevice(const QString &interface);

    QSharedPointer<Ecu> m_a2;
    QSharedPointer<Ecu> m_a3;
};
