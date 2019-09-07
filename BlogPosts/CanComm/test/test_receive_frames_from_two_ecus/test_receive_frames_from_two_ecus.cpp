// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCoreApplication>
#include <QSignalSpy>
#include <QtTest>

#include "mockcanbusrouter.h"

class TestReceiveFramesFromTwoEcus : public QObject
{
    Q_OBJECT

    MockCanBusRouter *m_router{nullptr};
    QSignalSpy *m_receivedSpy{nullptr};

    const QCanBusFrame c_ecu2_1{QCanBusFrame{0x18FF0602, QByteArray::fromHex("0A0000000A000000")}};
    const QCanBusFrame c_ecu3_1{QCanBusFrame{0x18FF3503, QByteArray::fromHex("0100000001000000")}};


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

    }

    void testReceiveFramesFromTwoEcusAtSameTime()
    {
        m_router->expectReadFrame(c_ecu2_1);
        m_router->expectReadFrame(c_ecu3_1);

        QCOMPARE(m_receivedSpy->count(), 2);
        QCOMPARE(m_router->allReceivedFrames(2).count(), 1);
    }

};




QTEST_GUILESS_MAIN(TestReceiveFramesFromTwoEcus)

#include "test_receive_frames_from_two_ecus.moc"
