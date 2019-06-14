// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QByteArray>
#include <QCanBusFrame>
#include <QDateTime>
#include <QLatin1Char>
#include <QtDebug>
#include <QtEndian>
#include "ecubase.h"

namespace
{
QCanBusFrame::TimeStamp currentTimeStampSinceEpoch()
{
    return QCanBusFrame::TimeStamp::fromMicroSeconds(1000 * QDateTime::currentMSecsSinceEpoch());
}

qint64 toMs(const QCanBusFrame &frame)
{
    auto stamp = frame.timeStamp();
    return (stamp.seconds() * 1000) + (stamp.microSeconds() / 1000);
}
}

EcuBase::EcuBase(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : QObject(parent)
    , m_ecuId{ecuId}
    , m_canBus{canBus}
{
    if (m_canBus == nullptr) {
        return;
    }
    connect(m_canBus.get(), &QCanBusDevice::errorOccurred,
            this, &EcuBase::onErrorOccurred);
    connect(m_canBus.get(), &QCanBusDevice::framesReceived,
            this, &EcuBase::onFramesReceived);
    connect(&m_receiptTimer, &QTimer::timeout, [this]() {
        if (!m_outgoingQueue.isEmpty() &&
                isReceiptMissing(toMs(m_outgoingQueue.first()))) {
            emit logMessage(QString("ERROR: No response for request %1.")
                            .arg(m_outgoingQueue.first().toString()));
            dequeueOutgoingFrame();
        }
    });
    m_receiptTimer.start(receiptTimeOut() / 2);
}

EcuBase::~EcuBase()
{
}

int EcuBase::ecuId() const
{
    return m_ecuId;
}

QSharedPointer<QCanBusDevice> EcuBase::canBus() const
{
    return m_canBus;
}

bool EcuBase::isLogging() const
{
    return m_logging;
}

void EcuBase::setLogging(bool enabled)
{
    m_logging = enabled;
}

qint64 EcuBase::receiptTimeOut() const
{
    return m_receiptTimeout;
}

void EcuBase::setReceiptTimeOut(qint64 timeout)
{
    m_receiptTimeout = timeout;
}

bool EcuBase::isReceiptMissing(qint64 stamp) const
{
    return QDateTime::currentMSecsSinceEpoch() - stamp > receiptTimeOut();
}

bool EcuBase::isReadParameter(const QCanBusFrame &frame) const
{
    Q_UNUSED(frame)
    return false;
}

void EcuBase::sendReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid)
    Q_UNUSED(value)
}

void EcuBase::receiveReadParameter(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
}

void EcuBase::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    emit logMessage(QString("ERROR: %1 (%2).").arg(canBus()->errorString()).arg(error));
}

void EcuBase::onFramesReceived()
{
    if (canBus() == nullptr) {
        return;
    }
    auto count = canBus()->framesAvailable();
    for (qint64 i = count; i > 0; --i) {
        auto frame = canBus()->readFrame();
        if (isReadParameter(frame)) {
            receiveReadParameter(frame);
            dequeueOutgoingFrame();
        }
    }
}

QByteArray EcuBase::encodeReadParameter(quint16 pid, quint32 value)
{
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    qToLittleEndian(value, payload.data() + 3);
    return payload;
}

std::tuple<quint16, quint32> EcuBase::decodeReadParameter(const QCanBusFrame &frame)
{
    const auto &payload = frame.payload();
    quint16 pid = qFromLittleEndian<qint16>(payload.data() + 1);
    quint32 value = qFromLittleEndian<qint32>(payload.data() + 3);
    return std::make_tuple(pid, value);
}

void EcuBase::emitReadParameterMessage(const QString &prefix, quint16 pid, quint32 value)
{
    if (isLogging()) {
        emit logMessage(QString("%1: Read(0x%2, 0x%3)").arg(prefix)
                        .arg(quint16(pid), 4, 16, QLatin1Char('0'))
                        .arg(quint32(value), 8, 16, QLatin1Char('0')));
    }
}

void EcuBase::enqueueOutgoingFrame(const QCanBusFrame &frame)
{
    auto empty = m_outgoingQueue.isEmpty();
    m_outgoingQueue.append(frame);
    if (empty) {
        m_outgoingQueue.first().setTimeStamp(currentTimeStampSinceEpoch());
        canBus()->writeFrame(m_outgoingQueue.first());
    }
}

void EcuBase::dequeueOutgoingFrame()
{
    if (!m_outgoingQueue.isEmpty()) {
        m_outgoingQueue.removeFirst();
    }
    if (!m_outgoingQueue.isEmpty()) {
        m_outgoingQueue.first().setTimeStamp(currentTimeStampSinceEpoch());
        canBus()->writeFrame(m_outgoingQueue.first());
    }
}
