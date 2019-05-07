// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCanBus>
#include <QCanBusFrame>
#include <QRandomGenerator>
#include <QtDebug>
#include <QtEndian>
#include "ecu.h"

// sudo ip link set can0 up type can bitrate 250000
// sudo ip link set can0 txqueuelen 128

Ecu::Ecu(const QString &pluginName, const QString &canBusName, QObject *parent)
    : QObject{parent}
{
    m_canBusDevice.reset(QCanBus::instance()->createDevice(pluginName, canBusName));
    if (m_canBusDevice == nullptr || !m_canBusDevice->connectDevice()) {
        return;
    }
    connect(m_canBusDevice.get(), &QCanBusDevice::errorOccurred,
            this, &Ecu::onErrorOccurred);
    connect(m_canBusDevice.get(), &QCanBusDevice::framesReceived,
            this, &Ecu::onFramesReceived);
}

Ecu::~Ecu()
{
    if (isConnected()) {
        m_canBusDevice->disconnectDevice();
    }
}

bool Ecu::isConnected() const
{
    return m_canBusDevice != nullptr && m_canBusDevice->state() == QCanBusDevice::ConnectedState;
}

bool Ecu::isReadParameterFrame(const QCanBusFrame &frame) const
{
    return frame.frameId() == 0x18ef0201U && frame.payload()[0] == char(1);
}

void Ecu::readParameter(quint16 pid)
{
    qDebug() << "### Ecu::readParameter: " << pid;
    auto value = QRandomGenerator::global()->generate();
    QByteArray payload(8, 0x00);
    qToLittleEndian(quint8(1), payload.data());
    qToLittleEndian(pid, payload.data() + 1);
    qToLittleEndian(value, payload.data() + 3);
    QCanBusFrame frame(0x18ef0102U, payload);
    emit logMessage(QString("ECU - Sending: ") + frame.toString());
    m_canBusDevice->writeFrame(frame);

//    emit parameterRead(pid, value);
}

void Ecu::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    // TODO: Print m_canBusDevice->state(), too.
    emit logMessage(QString("ERROR: %1 (%2).").arg(m_canBusDevice->errorString()).arg(error));
}

void Ecu::onFramesReceived()
{
    auto count = m_canBusDevice->framesAvailable();
    for (qint64 i = count; i > 0; --i) {
        auto frame = m_canBusDevice->readFrame();
        emit logMessage(QString("ECU - Received: ") + frame.toString());
        if (isReadParameterFrame(frame)) {
            auto pid = qFromLittleEndian<qint16>(frame.payload().data() + 1);
            readParameter(static_cast<quint16>(pid));
        }
    }
}
