#include <QtDebug>
#include <QCanBusFrame>
#include "Receiver1.h"

Receiver1::Receiver1(quint8 deviceId, QObject *parent)
    : QObject(parent)
    , c_deviceId(deviceId)
    , m_relevantMessageCount(0)
{
}

int Receiver1::relevantMessageCount() const
{
    return m_relevantMessageCount;
}

void Receiver1::onNewMessage(const QCanBusFrame &frame)
{
    if (static_cast<quint8>(frame.frameId() & 0x000000ff) != c_deviceId) {
//        qDebug() << "### " << QString::number(c_deviceId, 16) << ": Rejecting frame "
//                 << QString::number(frame.frameId(), 16);
        return;
    }
//    qDebug() << "@@@ " << QString::number(c_deviceId, 16) << ": Accepting frame "
//             << QString::number(frame.frameId(), 16);
    ++m_relevantMessageCount;
}
