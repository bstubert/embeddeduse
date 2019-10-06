// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <tuple>

#include <QObject>
#include <QSet>

class QByteArray;
class J1939Frame;

class CanBusRouter;

class EcuBase : public QObject
{
    Q_OBJECT

signals:
    void logMessage(const QString &msg);

public slots:
    void onErrorOccurred();
    virtual void onFramesReceived(const QSet<int> &ecuIdColl);

public:
    explicit EcuBase(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    bool isLogging() const;
    void setLogging(bool enabled);

    virtual void receiveProprietaryPeerToPeerFrame(const J1939Frame &frame);
    virtual void receiveStandardPeerToPeerFrame(const J1939Frame &frame);
    virtual void receiveProprietaryBroadcastFrame(const J1939Frame &frame);
    virtual void receiveStandardBroadcastFrame(const J1939Frame &frame);

    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);

protected:
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);
    void emitInfoUnsolicitedMessage(const QString &info);

    CanBusRouter *m_router{nullptr};
    int m_ecuId{-1};
    bool m_logging{true};
};

