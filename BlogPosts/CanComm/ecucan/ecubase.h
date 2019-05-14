// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>

class EcuBase : public QObject
{
    Q_OBJECT
public:
    explicit EcuBase(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    QSharedPointer<QCanBusDevice> canBus() const;
    bool isLogging() const;
    void setLogging(bool enabled);
    void writeCanFrame(const QCanBusFrame &frame);
    virtual bool isReadParameter(const QCanBusFrame &frame) const;

signals:
    void logMessage(const QString &msg);

public slots:
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(quint16 pid, quint32 value = 0U);
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

protected:
    void encodeReadParameter(quint32 frameId, quint16 pid, quint32 value);
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);

private:
    int m_ecuId;
    QSharedPointer<QCanBusDevice> m_canBus;
    bool m_logging{true};
};

