// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QString>
#include <QVariant>


class MockCanBackend : public QCanBusDevice
{
    Q_OBJECT
public:
    explicit MockCanBackend(const QString &name);
    ~MockCanBackend();

    void setConfigurationParameter(int key, const QVariant &value) override;

    bool writeFrame(const QCanBusFrame &newData) override;

    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

    static QList<QCanBusDeviceInfo> interfaces();

protected:
    bool open() override;
    void close() override;

private:
    void resetConfigurations();
};

