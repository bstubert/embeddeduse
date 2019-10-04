// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QObject>
#include <QSet>
#include <QString>
#include <QVector>

#include "can_frame_cache.h"

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
    QVector<J1939Frame> takeReceivedFrames(int sourceEcuId);

    bool isReceiveOwnFrameEnabled() const;
    void setReceiveOwnFrameEnabled(bool enabled);

    QList<QCanBusDevice::Filter> rawFilters() const;
    void setRawFilters(const QList<QCanBusDevice::Filter> &filters);

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
    void onOwnFrameLost(const QCanBusFrame &lostFrame, const QCanBusFrame &nextFrame);

private:
    QCanBusDevice *createDevice(const QString &plugin, const QString &interface);
    void connectToDevice();
    void disconnectFromDevice();
    void writeQueuedFrame(const QCanBusFrame &frame);
    void processOwnFrames();

    QVector<QCanBusFrame> readAllFrames();

    int m_canId{-1};
    QCanBusDevice::CanBusError m_error{QCanBusDevice::CanBusError::NoError};
    QString m_errorStr;
    QCanBusDevice::CanBusDeviceState m_state;
    CanFrameCache m_frameCache;
};

