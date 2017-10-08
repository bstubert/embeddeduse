#include <QMetaMethod>
#include <QMetaObject>
#include <QtDebug>
#include <QCanBusFrame>
#include "Sender3.h"

class ReceiverProxy : public QObject
{
    Q_OBJECT

public:
    explicit ReceiverProxy(const QObject *receiver, const char *slot, quint8 devicedId,
                           QObject *parent = nullptr);
    void emitNewMessage(const QCanBusFrame &frame);

    quint8 m_deviceId;

signals:
    void newMessage(const QCanBusFrame &frame);
};

ReceiverProxy::ReceiverProxy(const QObject *receiver, const char *slot, quint8 devicedId, QObject *parent)
    : QObject(parent)
    , m_deviceId(devicedId)
{
    auto signalIndex = metaObject()->indexOfSignal("newMessage(QCanBusFrame)");
    auto slotIndex = receiver->metaObject()->indexOfSlot(slot);
    connect(this, metaObject()->method(signalIndex),
            receiver, receiver->metaObject()->method(slotIndex));
}

void ReceiverProxy::emitNewMessage(const QCanBusFrame &frame)
{
    emit newMessage(frame);
}


Sender3::Sender3(int messageCount, QObject *parent)
    : QObject(parent)
    , c_messageCount(messageCount)
{
}

void Sender3::connectReceiver(const QObject *receiver, const char *slot, quint8 deviceId)
{
    auto proxy = new ReceiverProxy(receiver, slot, deviceId, this);
    m_proxies.insert(deviceId, proxy);
}

void Sender3::sendMessages()
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

void Sender3::onFrameReceived(const QCanBusFrame &frame)
{
    auto deviceId = static_cast<quint8>(frame.frameId() & 0x000000ff);
    auto proxy = m_proxies[deviceId];
    if (proxy != nullptr && proxy->m_deviceId == deviceId) {
        proxy->emitNewMessage(frame);
    }
}

#include "Sender3.moc"
