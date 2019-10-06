// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>

class CanBusRouter;
class J1939Frame;

class Ecu : public QObject
{
    Q_OBJECT

public:
    explicit Ecu(int ecuId, CanBusRouter *router, QObject *parent = nullptr);
    virtual ~Ecu() override;

    int ecuId() const;
    bool isLogging() const;
    void setLogging(bool enabled);

    bool isReadParameter(const J1939Frame &frame) const;
    void sendReadParameter(quint16 pid, quint32 value = 0U);
    void receiveReadParameter(const J1939Frame &frame);

    void sendUnsolicitedFrames();

public slots:
    void onFramesReceived(const QSet<int> &ecuIdColl);
    void onErrorOccurred();

signals:
    void logMessage(const QString &msg);

private:
    void emitLogMessage(const QString &info);

    CanBusRouter *m_router{nullptr};
    int m_ecuId{-1};
    bool m_logging{true};
};
