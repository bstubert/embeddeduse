// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <tuple>
#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
class QByteArray;
class QCanBusFrame;

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
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(const QCanBusFrame &frame);

signals:
    void logMessage(const QString &msg);

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

protected:
    QByteArray encodeReadParameter(quint16 pid, quint32 value);
    std::tuple<quint16, quint32> decodeReadParameter(const QCanBusFrame &frame);
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);

private:
    int m_ecuId;
    QSharedPointer<QCanBusDevice> m_canBus;
    bool m_logging{true};
};

