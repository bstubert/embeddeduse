#pragma once

#include <QObject>
#include <QtGlobal>
class QCanBusFrame;

class Receiver2 : public QObject
{
public:
    Receiver2(quint8 deviceId, QObject *parent = nullptr);

    int relevantMessageCount() const;

public slots:
    void onNewMessage(const QCanBusFrame &frame);

private:
    bool isRelevantMessage(const QCanBusFrame &frame) const;

    const quint8 c_deviceId;
    int m_relevantMessageCount;
};
