// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecubase.h"

class QCanBusFrame;

class CanBusRouter;

class EcuProxy : public EcuBase
{
    Q_OBJECT
public:
    explicit EcuProxy(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~EcuProxy() override;

    virtual bool areReceivedFramesRelevant(const QSet<int> &ecuIdColl) const override;
    virtual bool isReadParameter(const QCanBusFrame &frame) const override;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(const QCanBusFrame &frame) override;
    virtual void receiveUnsolicitedFrame(const QCanBusFrame &frame) override;
};
