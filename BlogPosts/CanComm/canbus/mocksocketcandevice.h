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
    explicit MockSocketCanDevice(const QString &name);
    ~MockSocketCanDevice();

    bool writeFrame(const QCanBusFrame &frame) override;

    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

    static QList<QCanBusDeviceInfo> interfaces();

protected:
    bool open() override;
    void close() override;

private:
    QString m_interface;
};

