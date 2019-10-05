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
public:
    explicit EcuBase(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~EcuBase();
    int ecuId() const;
    bool isLogging() const;
    void setLogging(bool enabled);

    virtual bool isReadParameter(const J1939Frame &frame) const;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U);
    virtual void receiveReadParameter(const J1939Frame &frame);
    virtual void receiveUnsolicitedFrame(const J1939Frame &frame);

signals:
    void logMessage(const QString &msg);

public slots:
    void onErrorOccurred();
    virtual void onFramesReceived(const QSet<int> &ecuIdColl);

protected:
    std::tuple<quint16, quint32> decodedReadParameter(const J1939Frame &frame) const;
    int sourceEcuId(quint32 frameId) const;
    void emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value);
    void emitInfoUnsolicitedMessage(const QString &info);

    CanBusRouter *m_router{nullptr};
    int m_ecuId{-1};
    bool m_logging{true};
};

