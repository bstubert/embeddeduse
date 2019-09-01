// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>
#include <tuple>

#include <QCanBusDevice>
#include <QList>
#include <QObject>
#include <QTimer>

class QByteArray;
class QCanBusFrame;

class EcuBase : public QObject
{
    Q_OBJECT
public:
    explicit EcuBase(int ecuId, QCanBusDevice *canBus, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    QCanBusDevice *canBus() const;
    bool isLogging() const;
    void setLogging(bool enabled);

    qint64 receiptTimeOut() const;
    void setReceiptTimeOut(qint64 timeout);
    bool isReceiptMissing(qint64 stamp) const;
    bool isOwnFrame(const QCanBusFrame &frame) const;
    virtual bool isReadParameter(const QCanBusFrame &frame) const;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(const QCanBusFrame &frame);
    virtual void receiveUnsolicitedFrame(const QCanBusFrame &frame);

signals:
    void logMessage(const QString &msg);

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

protected:
    QByteArray encodedReadParameter(quint16 pid, quint32 value) const;
    std::tuple<quint16, quint32> decodedReadParameter(const QCanBusFrame &frame) const;
    int sourceEcuId(quint32 frameId) const;
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);
    void emitSendUnsolicitedMessage(int ecuId, const QString &direction, int value);
    void enqueueOutgoingFrame(const QCanBusFrame &frame);
    void dequeueOutgoingFrame();
    virtual bool skipWrite(const QCanBusFrame &frame) const;

    int m_ecuId;
    std::unique_ptr<QCanBusDevice> m_canBus;
    bool m_logging{true};
    QList<QCanBusFrame> m_outgoingQueue;
    qint64 m_receiptTimeout{100};
    QTimer m_receiptTimer;
};

