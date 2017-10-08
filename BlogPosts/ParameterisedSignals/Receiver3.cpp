#include <QtDebug>
#include <QCanBusFrame>
#include "Receiver3.h"

Receiver3::Receiver3(quint8 deviceId, QObject *parent)
    : QObject(parent)
    , c_deviceId(deviceId)
    , m_relevantMessageCount(0)
{
}

int Receiver3::relevantMessageCount() const
{
    return m_relevantMessageCount;
}

void Receiver3::onNewMessage(const QCanBusFrame &frame)
{
//    qDebug() << "@@@ " << QString::number(c_deviceId, 16) << ": Accepting frame "
//             << QString::number(frame.frameId(), 16);
    ++m_relevantMessageCount;
}
