// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>
#include <QByteArray>
#include <QCanBusDevice>
#include <QObject>
#include <QString>
class QCanBusFrame;

class Ecu : public QObject
{
    Q_OBJECT
public:
    explicit Ecu(const QString &pluginName, const QString &canBusName,
                      QObject *parent = nullptr);
    virtual ~Ecu();
    bool isConnected() const;
    bool isReadParameterFrame(const QCanBusFrame &frame) const;

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();
    void readParameter(quint16 pid);

signals:
    void logMessage(const QString &msg);
    void parameterRead(quint16 pid, quint32 value);

private:
    std::unique_ptr<QCanBusDevice> m_canBusDevice;
};
