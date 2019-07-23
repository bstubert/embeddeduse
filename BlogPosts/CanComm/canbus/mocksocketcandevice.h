// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
#include <QString>
#include <QVariant>


class MockSocketCanDevice : public QCanBusDevice
{
    Q_OBJECT
public:
    explicit MockSocketCanDevice(const QString &name, QObject *parent = nullptr);
    ~MockSocketCanDevice();
    static QList<QCanBusDeviceInfo> interfaces();
    void setConfigurationParameter(int key, const QVariant &value) override;
    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;

private:
    void receiveIncomingFrames();

    QString m_interface;
    int m_frameIndex{0};
    int m_frameCount{0};
};

