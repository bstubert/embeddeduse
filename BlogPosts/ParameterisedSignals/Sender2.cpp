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
        emit newMessage1(frame1);
        emit newMessage2(frame2);
        emit newMessage3(frame3);
    }
}
