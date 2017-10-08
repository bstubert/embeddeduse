#include <QCanBusFrame>
#include "Sender2.h"

Sender2::Sender2(int messageCount, QObject *parent)
    : QObject(parent)
    , c_messageCount(messageCount)
{
}

void Sender2::sendMessages()
{
    QCanBusFrame frame1(0x18ff2213, QByteArray(8, '1'));
    QCanBusFrame frame2(0x18ff1021, QByteArray(8, '2'));
    QCanBusFrame frame3(0x18ff0803, QByteArray(8, '3'));
    for (int i = 0; i < c_messageCount; ++i) {
        onFrameReceived(frame1);
        onFrameReceived(frame2);
        onFrameReceived(frame3);
    }
}

void Sender2::onFrameReceived(const QCanBusFrame &frame)
{
    auto deviceId = static_cast<quint8>(frame.frameId() & 0x000000ff);
    switch (deviceId) {
    case 0x13:
        emit newMessage1(frame);
        break;
    case 0x21:
        emit newMessage2(frame);
        break;
    case 0x03:
        emit newMessage3(frame);
        break;
    default:
        break;
    }
}

