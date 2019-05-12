// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>
#include <QByteArray>
#include <QCanBusDevice>
#include <QObject>
#include <QString>

class EcuProxy : public QObject
{
    Q_OBJECT
public:
    explicit EcuProxy(const QString &pluginName, const QString &canBusName,
                      QObject *parent = nullptr);
    virtual ~EcuProxy();
    bool isConnected() const;
    bool isReadParameterFrame(const QCanBusFrame &frame) const;
    bool isLogging() const;
    void setLogging(bool enabled);
    void displayCanConfiguration();

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();
    void sendReadParameter(quint16 pid);

signals:
    void logMessage(const QString &msg);

private:
    void receiveReadParameter(const QCanBusFrame &frame);

    std::unique_ptr<QCanBusDevice> m_canBusDevice;
    bool m_logging{true};
};
