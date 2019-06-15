// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <tuple>
#include <QCanBusDevice>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QTimer>
class QByteArray;
class QCanBusFrame;

class EcuBase : public QObject
{
    Q_OBJECT
public:
    explicit EcuBase(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    QSharedPointer<QCanBusDevice> canBus() const;
    bool isLogging() const;
    void setLogging(bool enabled);
    bool isSkipResponseEnabled() const;
    void setSkipResponseEnabled(bool enabled);
    bool isMissingResponsesEnabled() const;
    void setMissingResponsesEnabled(bool enabled);

    qint64 receiptTimeOut() const;
    void setReceiptTimeOut(qint64 timeout);
    bool isReceiptMissing(qint64 stamp) const;
    bool isOwnFrame(const QCanBusFrame &frame) const;
    virtual bool isReadParameter(const QCanBusFrame &frame) const;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(const QCanBusFrame &frame);

signals:
    void logMessage(const QString &msg);
    void skipResponseEnabledChanged();
    void missingResponsesEnabledChanged();

public slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

protected:
    QByteArray encodedReadParameter(quint16 pid, quint32 value) const;
    std::tuple<quint16, quint32> decodedReadParameter(const QCanBusFrame &frame) const;
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);
    void enqueueOutgoingFrame(const QCanBusFrame &frame);
    void dequeueOutgoingFrame();
    virtual bool skipWrite(const QCanBusFrame &frame) const;

    int m_ecuId;
    QSharedPointer<QCanBusDevice> m_canBus;
    bool m_logging{true};
    bool m_skipResponseEnabled{true};
    bool m_missingResponsesEnabled{false};
    QList<QCanBusFrame> m_outgoingQueue;
    qint64 m_receiptTimeout{100};
    QTimer m_receiptTimer;
};

