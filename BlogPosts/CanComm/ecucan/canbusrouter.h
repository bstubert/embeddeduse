// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QString>
#include <QVector>

class QCanBusFrame;

class CanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit CanBusRouter(const QString &plugin, const QString &interface,
                          QObject *parent = nullptr);
    virtual ~CanBusRouter() override;

    QCanBusDevice::CanBusError error() const;
    QString errorString() const;
    QCanBusDevice::CanBusDeviceState state() const;

signals:
    void errorOccurred(QCanBusDevice::CanBusError error, const QString &errorStr);
    void framesWritten(qint64 framesCount);
    void framesReceived();

public slots:
    void writeFrame(const QCanBusFrame &frame);

protected:
    QCanBusDevice *m_device{nullptr};

private slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
//    void onFramesReceived();

private:
    QCanBusDevice *createDevice(const QString &plugin, const QString &interface);
    void connectToDevice();
    void disconnectFromDevice();

    QCanBusDevice::CanBusError m_error{QCanBusDevice::CanBusError::NoError};
    QString m_errorStr;
    QCanBusDevice::CanBusDeviceState m_state;
};

