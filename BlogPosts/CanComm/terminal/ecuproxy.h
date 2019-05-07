// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#ifndef ECUPROXY_H
#define ECUPROXY_H

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

public slots:
    void readParameter(quint16 pid);

signals:
    void errorMessage(const QString &msg);
    void parameterRead(quint16 pid, quint32 value);

private slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);

private:
    std::unique_ptr<QCanBusDevice> m_canBusDevice;
};

#endif // ECUPROXY_H
