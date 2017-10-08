#pragma once

#include <QObject>
class QCanBusFrame;

class Sender2 : public QObject
{
    Q_OBJECT
public:
    explicit Sender2(int messageCount, QObject *parent = nullptr);

    void sendMessages();

signals:
    void newMessage1(const QCanBusFrame &frame);
    void newMessage2(const QCanBusFrame &frame);
    void newMessage3(const QCanBusFrame &frame);

private:
    void onFrameReceived(const QCanBusFrame &frame);

    // Number of times the signal newMessage() is emitted.
    const int c_messageCount;
};
