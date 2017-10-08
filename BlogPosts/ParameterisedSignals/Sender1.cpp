#include <QCanBusFrame>
#include "Sender1.h"

Sender1::Sender1(int messageCount, QObject *parent)
    : QObject(parent)
    , c_messageCount(messageCount)
{
}

void Sender1::sendMessages()
{
    QCanBusFrame frame1(0x18ff2213, QByteArray(8, '1'));
    QCanBusFrame frame2(0x18ff1021, QByteArray(8, '2'));
    QCanBusFrame frame3(0x18ff0803, QByteArray(8, '3'));
    for (int i = 0; i < c_messageCount; ++i) {
        emit newMessage(frame1);
        emit newMessage(frame2);
        emit newMessage(frame3);
    }
}
