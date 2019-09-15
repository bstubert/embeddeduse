// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QObject>
#include <QSet>
#include <QString>
#include <QVector>

#include "received_frames_cache.h"

class QCanBusFrame;

class CanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit CanBusRouter(int canId, const QString &plugin, const QString &interface,
                          QObject *parent = nullptr);
    virtual ~CanBusRouter() override;

    QCanBusDevice::CanBusError error() const;
    QString errorString() const;
    QCanBusDevice::CanBusDeviceState state() const;
    QVector<QCanBusFrame> takeReceivedFrames(int sourceEcuId);

    bool isReceiveOwnFrameEnabled() const;
    void setReceiveOwnFrameEnabled(bool enabled);

signals:
    void errorOccurred();
    void framesWritten(qint64 framesCount);
    void framesReceived(const QSet<int> &ecuIdColl);

public slots:
    void writeFrame(const QCanBusFrame &frame);

protected:
    QCanBusDevice *m_device{nullptr};

private slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

private:
    QCanBusDevice *createDevice(const QString &plugin, const QString &interface);
    void connectToDevice();
    void disconnectFromDevice();
    void enqueueOutoingFrame(const QCanBusFrame &frame);
    void dequeueOutgoingFrame();
    void processOwnFrames();

#if (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
    QVector<QCanBusFrame> readAllFrames();
#endif

    int m_canId{-1};
    QCanBusDevice::CanBusError m_error{QCanBusDevice::CanBusError::NoError};
    QString m_errorStr;
    QCanBusDevice::CanBusDeviceState m_state;
    ReceivedFramesCache m_receivedFrameCache;
    QVector<QCanBusFrame> m_writtenFrameCache;
};

