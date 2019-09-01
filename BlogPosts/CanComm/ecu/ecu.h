// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecubase.h"
class QCanBusFrame;

class Ecu : public EcuBase
{
    Q_OBJECT
public:
    explicit Ecu(int ecuId, QCanBusDevice *canBus, QObject *parent = nullptr);
    virtual ~Ecu();
    virtual bool isReadParameter(const QCanBusFrame &frame) const override;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(const QCanBusFrame &frame) override;

    bool isSkipResponseEnabled() const;
    void setSkipResponseEnabled(bool enabled);
    bool isMissingResponsesEnabled() const;
    void setMissingResponsesEnabled(bool enabled);

    void sendUnsolicitedFrames();

signals:
    void parameterRead(quint16 pid, quint32 value);
    void skipResponseEnabledChanged();
    void missingResponsesEnabledChanged();

private:
    bool m_skipResponseEnabled{true};
    bool m_missingResponsesEnabled{false};
};
