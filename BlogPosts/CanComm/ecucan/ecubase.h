// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <tuple>

#include <QObject>
#include <QSet>

class QByteArray;
class QCanBusFrame;

class CanBusRouter;

class EcuBase : public QObject
{
    Q_OBJECT
public:
    explicit EcuBase(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    bool isLogging() const;
    void setLogging(bool enabled);

    virtual bool isReadParameter(const QCanBusFrame &frame) const;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(const QCanBusFrame &frame);
    virtual void receiveUnsolicitedFrame(const QCanBusFrame &frame);

signals:
    void logMessage(const QString &msg);

public slots:
    void onErrorOccurred();
    virtual void onFramesReceived(const QSet<int> &ecuIdColl);

protected:
    QByteArray encodedReadParameter(quint16 pid, quint32 value) const;
    std::tuple<quint16, quint32> decodedReadParameter(const QCanBusFrame &frame) const;
    int sourceEcuId(quint32 frameId) const;
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);
    void emitSendUnsolicitedMessage(int ecuId, const QString &direction, int value);

    CanBusRouter *m_router{nullptr};
    int m_ecuId{-1};
    bool m_logging{true};
};

