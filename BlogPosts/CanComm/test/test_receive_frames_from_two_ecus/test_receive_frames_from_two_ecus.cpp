// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCoreApplication>
#include <QSet>
#include <QSignalSpy>
#include <QtTest>

#include "mockcanbusrouter.h"

class TestReceiveFramesFromTwoEcus : public QObject
{
    Q_OBJECT

    MockCanBusRouter *m_router{nullptr};
    QSignalSpy *m_receivedSpy{nullptr};

    const QCanBusFrame c_ecu2_1{QCanBusFrame{0x18FF0602, QByteArray::fromHex("0A0000000A000000")}};
    const QCanBusFrame c_ecu2_2{QCanBusFrame{0x18FF0602, QByteArray::fromHex("0B0000000B000000")}};
    const QCanBusFrame c_ecu3_1{QCanBusFrame{0x18FF3503, QByteArray::fromHex("0100000001000000")}};
    const QCanBusFrame c_ecu3_2{QCanBusFrame{0x18FF3503, QByteArray::fromHex("0200000002000000")}};

    QSet<int> receivedEcuIds(int spyIndex) const
    {
        return qvariant_cast<QSet<int>>((*m_receivedSpy)[spyIndex][0]);
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
        m_receivedSpy = new QSignalSpy{m_router, &MockCanBusRouter::framesReceived};
    }

    void cleanup()
    {
        delete m_receivedSpy;
        delete m_router;
    }

    void testReceiveFramesOnce()
    {
        m_router->expectReadFrames({c_ecu2_1, c_ecu3_1, c_ecu2_2});
        QTRY_COMPARE_WITH_TIMEOUT(m_receivedSpy->count(), 1, 200);
        QCOMPARE(receivedEcuIds(0), (QSet<int>{2, 3}));

        auto fromEcu2 = m_router->takeReceivedFrames(2);
        QCOMPARE(fromEcu2, (QVector<QCanBusFrame>{c_ecu2_1, c_ecu2_2}));

        auto fromEcu3 = m_router->takeReceivedFrames(3);
        QCOMPARE(fromEcu3, (QVector<QCanBusFrame>{c_ecu3_1}));
    }

    void testDontRetrieveOldFramesAgain()
    {
        m_router->expectReadFrames({c_ecu2_1, c_ecu3_1});

        m_router->takeReceivedFrames(2);
        m_router->takeReceivedFrames(3);

        QVERIFY(m_router->takeReceivedFrames(2).isEmpty());
        QVERIFY(m_router->takeReceivedFrames(3).isEmpty());
    }

    void testReceiveFramesTwice()
    {
        m_router->expectReadFrames({c_ecu2_1, c_ecu3_1});
        QTRY_COMPARE_WITH_TIMEOUT(m_receivedSpy->count(), 1, 200);

        m_router->takeReceivedFrames(2);
        m_router->takeReceivedFrames(3);

        m_router->expectReadFrames({c_ecu2_2, c_ecu3_2, c_ecu3_1});
        QTRY_COMPARE_WITH_TIMEOUT(m_receivedSpy->count(), 2, 200);
        QCOMPARE(receivedEcuIds(1), (QSet<int>{2, 3}));

        auto fromEcu2 = m_router->takeReceivedFrames(2);
        QCOMPARE(fromEcu2, (QVector<QCanBusFrame>{c_ecu2_2}));

        auto fromEcu3 = m_router->takeReceivedFrames(3);
        QCOMPARE(fromEcu3, (QVector<QCanBusFrame>{c_ecu3_2, c_ecu3_1}));
    }
};




QTEST_GUILESS_MAIN(TestReceiveFramesFromTwoEcus)

#include "test_receive_frames_from_two_ecus.moc"
