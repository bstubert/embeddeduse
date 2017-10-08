#include <QtDebug>
#include <QCanBusFrame>
#include "Receiver2.h"

Receiver2::Receiver2(quint8 deviceId, QObject *parent)
    : QObject(parent)
    , c_deviceId(deviceId)
    , m_relevantMessageCount(0)
{
}

int Receiver2::relevantMessageCount() const
{
    return m_relevantMessageCount;
}

void Receiver2::onNewMessage(const QCanBusFrame &frame)
{
//    qDebug() << "@@@ " << QString::number(c_deviceId, 16) << ": Accepting frame "
//             << QString::number(frame.frameId(), 16);
    ++m_relevantMessageCount;
}

bool Receiver2::isRelevantMessage(const QCanBusFrame &frame) const
{
    return static_cast<quint8>(frame.frameId() & 0x000000ff) == c_deviceId;
}
