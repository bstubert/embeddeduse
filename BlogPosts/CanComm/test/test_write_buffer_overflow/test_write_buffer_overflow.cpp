// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>
#include <memory>
#include <utility>

#include <QByteArray>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QRandomGenerator>
#include <QSignalSpy>
#include <QString>
#include <QStringList>
#include <QtDebug>
#include <QtTest>
#include <QVector>

#include "canbusext.h"
#include "mockcanbusrouter.h"
#include "mockcanutils.h"

class TestWriteBufferOverflow : public QObject
{
    Q_OBJECT

    MockCanBusRouter *m_router{nullptr};

    static const int c_writeErrorInterval{4};

    const QCanBusFrame c_out1{QCanBusFrame{0x18ef0201U, QByteArray::fromHex("018A010000000000")}};
    const QCanBusFrame c_in1{QCanBusFrame{0x18ef0102U, QByteArray::fromHex("018A0103A4000000")}};

    QByteArray encodedReadParameter(int pid, int value = 0) const
    {
        QByteArray payload(8, 0x00);
        qToLittleEndian(static_cast<quint8>(1), payload.data());
        qToLittleEndian(static_cast<quint16>(pid), payload.data() + 1);
        qToLittleEndian(static_cast<qint32>(value), payload.data() + 3);
        return payload;
    }

    std::pair<QVector<QCanBusFrame>, QVector<QCanBusFrame>>
    createReadParameterRequests(int count, int startPid)
    {
        auto requestColl = QVector<QCanBusFrame>{};
        auto responseColl = QVector<QCanBusFrame>{};
        for (int i = 0; i < count; ++i)
        {
            requestColl.append(QCanBusFrame{0x18ef0201U, encodedReadParameter(startPid + i)});
            auto value = static_cast<int>(QRandomGenerator::global()->generate());
            responseColl.append(QCanBusFrame{0x18ef0201U, encodedReadParameter(startPid + i, value)});
        }
        return std::make_pair(requestColl, responseColl);
    }

private slots:
    void initTestCase()
    {
        // The loader for the CAN bus plugins adds /canbus to each library path and looks for
        // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
        // is called "canbus".
        QCoreApplication::addLibraryPath("../../");
    }

    void init()
    {
        m_router = new MockCanBusRouter{};
        QVERIFY(!m_router->isReceiveOwnFrameEnabled());
        m_router->setReceiveOwnFrameEnabled(true);
        QVERIFY(m_router->isReceiveOwnFrameEnabled());
    }

    void cleanup()
    {
        delete m_router;
    }

    void testWriteBufferOverflow()
    {
        m_router->setWriteErrorInterval(c_writeErrorInterval);
        auto requestColl = QVector<QCanBusFrame>{};
        auto responseColl = QVector<QCanBusFrame>{};
        std::tie(requestColl, responseColl) = createReadParameterRequests(2 * c_writeErrorInterval, 32);
        m_router->expectWriteFrames(requestColl);

        for (const auto &request : requestColl)
        {
            m_router->writeFrame(request);
        }

        const auto &actualFrameColl = m_router->actualCanFrames();
        QCOMPARE(actualFrameColl[c_writeErrorInterval - 1].deviceError(),
                 QCanBusDevice::WriteError);
        QCOMPARE(actualFrameColl[2 * c_writeErrorInterval - 1].deviceError(),
                QCanBusDevice::WriteError);
    }

    void testOwnFrameAfterOutgoingFrame()
    {
        m_router->expectWriteFrame(c_out1);
        m_router->expectReadOwnFrame(c_out1);

        m_router->writeFrame(c_out1);

        auto actualFrames = m_router->actualCanFrames();
        QCOMPARE(actualFrames.count(), 2);
        QCOMPARE(QCanBusFrame{actualFrames[0]}, QCanBusFrame{actualFrames[1]});
        QVERIFY(actualFrames[1].isOwnIncoming());
    }

    void testIncomingFrameBetweenOutgoingAndOwnFrame()
    {
        m_router->expectWriteFrame(c_out1);
        m_router->expectReadFrame(c_in1);
        m_router->expectReadOwnFrame(c_out1);

        m_router->writeFrame(c_out1);

        auto actualFrames = m_router->actualCanFrames();
        QCOMPARE(actualFrames.count(), 3);
        QCOMPARE(QCanBusFrame{actualFrames[0]}, QCanBusFrame{actualFrames[2]});
        QVERIFY(actualFrames[2].isOwnIncoming());
    }

    void testReceivedOwnFrameAlthoughSwitchedOff()
    {
        m_router->setReceiveOwnFrameEnabled(false);
        m_router->expectWriteFrame(c_out1);
        m_router->expectReadOwnFrame(c_out1);

        m_router->writeFrame(c_out1);

        auto actualFrames = m_router->actualCanFrames();
        QCOMPARE(actualFrames.count(), 1);
        QVERIFY(actualFrames[0].isOutgoing());
    }

};

QTEST_GUILESS_MAIN(TestWriteBufferOverflow)

#include "test_write_buffer_overflow.moc"
