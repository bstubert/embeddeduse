// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecubase.h"
class QCanBusFrame;

class Ecu : public EcuBase
{
    Q_OBJECT
public:
    explicit Ecu(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent = nullptr);
    virtual ~Ecu();
    virtual bool isReadParameter(const QCanBusFrame &frame) const override;

public slots:
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(quint16 pid, quint32 value = 0U) override;

signals:
    void parameterRead(quint16 pid, quint32 value);
};
