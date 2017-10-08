#pragma once

#include <QObject>
class QCanBusFrame;

class Sender1 : public QObject
{
    Q_OBJECT
public:
    explicit Sender1(int messageCount, QObject *parent = nullptr);

    void sendMessages();

signals:
    void newMessage(const QCanBusFrame &frame);

private:
    // Number of times the signal newMessage() is emitted.
    const int c_messageCount;
};
