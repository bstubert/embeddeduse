// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecubase.h"

class CanBusRouter;
class J1939Frame;

class Ecu : public EcuBase
{
    Q_OBJECT
public:
    explicit Ecu(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~Ecu() override;

    virtual void onFramesReceived(const QSet<int> &ecuIdColl) override;
    virtual bool isReadParameter(const J1939Frame &frame) const override;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(const J1939Frame &frame) override;

    void sendUnsolicitedFrames();

signals:
    void parameterRead(quint16 pid, quint32 value);
};
