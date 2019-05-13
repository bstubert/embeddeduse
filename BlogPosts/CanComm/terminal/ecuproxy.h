// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>
#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
class QCanBusFrame;
class QString;

class EcuProxy : public QObject
{
    Q_OBJECT
public:
    explicit EcuProxy(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent = nullptr);
    virtual ~EcuProxy();
    bool isReadParameterFrame(const QCanBusFrame &frame) const;
    bool isLogging() const;
    void setLogging(bool enabled);

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();
    void sendReadParameter(quint16 pid);

signals:
    void logMessage(const QString &msg);

private:
    void receiveReadParameter(const QCanBusFrame &frame);
    void writeCanFrame(const QCanBusFrame &frame);

    int m_ecuId;
    QSharedPointer<QCanBusDevice> m_canBus;
    bool m_logging{true};
};
