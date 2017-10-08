#pragma once

#include <QHash>
#include <QObject>
#include <QtGlobal>
class QCanBusFrame;
class ReceiverProxy;

class Sender3 : public QObject
{
    Q_OBJECT
public:
    explicit Sender3(int messageCount, QObject *parent = nullptr);

    void connectReceiver(const QObject *receiver, const char *slot, quint8 deviceId);

    void sendMessages();

signals:
    void newMessage(const QCanBusFrame &frame);

private:
    void onFrameReceived(const QCanBusFrame &frame);

    // Number of times the signal newMessage() is emitted.
    const int c_messageCount;
    QHash<quint8, ReceiverProxy *> m_proxies;
};
