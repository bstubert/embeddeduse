// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecubase.h"
class QCanBusFrame;

class EcuProxy : public EcuBase
{
    Q_OBJECT
public:
    explicit EcuProxy(int ecuId, QCanBusDevice *canBus, QObject *parent = nullptr);
    virtual ~EcuProxy() override;

    virtual bool isReadParameter(const QCanBusFrame &frame) const override;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(const QCanBusFrame &frame) override;
    virtual void receiveUnsolicitedFrame(const QCanBusFrame &frame) override;

    bool isSkipWriteEnabled() const;
    void setSkipWriteEnabled(bool enabled);
    bool isDirectWriteEnabled() const;
    void setDirectWriteEnabled(bool enabled);

signals:
    void skipWriteEnabledChanged();
    void directWriteEnabledChanged();

protected:
    virtual bool skipWrite(const QCanBusFrame &frame) const override;

private:
    bool m_skipWriteEnabled{false};
    bool m_directWriteEnabled{false};
};
