// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>
#include <memory>

#include <QByteArray>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QSignalSpy>
#include <QString>
#include <QStringList>
#include <QtDebug>
#include <QtTest>

#include "canbusext.h"
#include "mockcanutils.h"
#include "mockcanbusrouter.h"

class TestReadWriteOnMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void testWriteOneExpectedFrame();
    void testWriteOneUnexpectedFrame();
    void testWriteMoreFramesThanExpected();
    void testWriteLessFramesThanExpected();
    void testWriteTwoFramesInExpectedOrder();
    void testWriteTwoFramesInUnexpectedOrder();

    void testReq1Rsp1();
    void testReq1Rsp1Req2Rsp2();
    void testReq1Req2Rsp1Rsp2();
    void testReq1Req2Rsp2();
    void testRsp1Rsp2Req1Rsp1();

private:
    void testWriteFrameErrors_data();
    void testWriteFrameErrors();

private:    
    const QCanBusFrame c_frame1{0x18ef0201U, QByteArray::fromHex("018A010000000000")};
    const QCanBusFrame c_frame2{0x18ef0301U, QByteArray::fromHex("01B5010000000000")};

    const QCanBusFrame c_request1{0x18ef0201U, QByteArray::fromHex("018A010000000000")};
    const QCanBusFrame c_response1{0x18ef0102U, QByteArray::fromHex("018A014433221100")};
    const QCanBusFrame c_request2{0x18ef0201U, QByteArray::fromHex("0157000000000000")};
    const QCanBusFrame c_response2{0x18ef0102U, QByteArray::fromHex("015700AABBCCDD00")};

    MockCanBusRouter *m_router;
    QCanBusDevice *m_device;
    QSignalSpy *m_writtenSpy;
    QSignalSpy *m_receivedSpy;
    QSignalSpy *m_errorSpy;
};

#define CHECK_FRAMES_EXPECTED_EQUAL(writeCount) \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames()); \
    QCOMPARE(m_writtenSpy->size(), writeCount)

#define CHECK_FRAMES_EXPECTED_NOT_EQUAL \
    QEXPECT_FAIL("", "Frames expected to differ!", Continue); \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames());

#define CHECK_REQUESTS_AND_RESPONSES(writeCount, readCount) \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames()); \
    QCOMPARE(m_writtenSpy->size(), writeCount); \
    QCOMPARE(m_receivedSpy->size(), readCount)


void TestReadWriteOnMockCanBus::initTestCase()
{
    // The loader for the CAN bus plugins adds /canbus to each library path and looks for
    // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
    // is called "canbus".
    QCoreApplication::addLibraryPath("../../");
}

void TestReadWriteOnMockCanBus::init()
{
    QString errorStr;
    m_router = new MockCanBusRouter{};
    m_writtenSpy = new QSignalSpy{m_router, &MockCanBusRouter::framesWritten};
    m_receivedSpy = new QSignalSpy{m_router, &MockCanBusRouter::framesReceived};

    m_device = QCanBus::instance()->createDevice("mockcan", "mcan1", &errorStr);
    m_device->connectDevice();
    m_errorSpy = new QSignalSpy{m_device, &QCanBusDevice::errorOccurred};

    QVERIFY(actualCanFrames(m_device).isEmpty());
    QVERIFY(expectedCanFrames(m_device).isEmpty());
}

void TestReadWriteOnMockCanBus::cleanup()
{
    delete m_router;
    delete m_device;
    delete m_writtenSpy;
    delete m_receivedSpy;
    delete m_errorSpy;
}

void TestReadWriteOnMockCanBus::testWriteOneExpectedFrame()
{
    m_router->expectWriteFrame(c_frame1);

    m_router->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_EQUAL(1);
}

void TestReadWriteOnMockCanBus::testWriteOneUnexpectedFrame()
{
    m_router->expectWriteFrame(c_frame1);

    m_router->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteMoreFramesThanExpected()
{
    m_router->expectWriteFrame(c_frame1);

    m_router->writeFrame(c_frame1);
    m_router->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteLessFramesThanExpected()
{
    m_router->expectWriteFrame(c_frame1);
    m_router->expectWriteFrame(c_frame2);

    m_router->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteTwoFramesInExpectedOrder()
{
    m_router->expectWriteFrame(c_frame1);
    m_router->expectWriteFrame(c_frame2);

    m_router->writeFrame(c_frame1);
    m_router->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_EQUAL(2);
}

void TestReadWriteOnMockCanBus::testWriteTwoFramesInUnexpectedOrder()
{
    m_router->expectWriteFrame(c_frame1);
    m_router->expectWriteFrame(c_frame2);

    m_router->writeFrame(c_frame2);
    m_router->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testReq1Rsp1()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectReadFrame(c_response1);

    m_router->writeFrame(c_request1);

    CHECK_REQUESTS_AND_RESPONSES(1, 1);
}

void TestReadWriteOnMockCanBus::testReq1Rsp1Req2Rsp2()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectReadFrame(c_response1);
    m_router->expectWriteFrame(c_request2);
    m_router->expectReadFrame(c_response2);

    m_router->writeFrame(c_request1);
    m_router->writeFrame(c_request2);

    CHECK_REQUESTS_AND_RESPONSES(2, 2);
}

void TestReadWriteOnMockCanBus::testReq1Req2Rsp1Rsp2()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectWriteFrame(c_request2);
    m_router->expectReadFrame(c_response1);
    m_router->expectReadFrame(c_response2);

    m_router->writeFrame(c_request1);
    m_router->writeFrame(c_request2);

    CHECK_REQUESTS_AND_RESPONSES(2, 1);
}

void TestReadWriteOnMockCanBus::testReq1Req2Rsp2()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectWriteFrame(c_request2);
    m_router->expectReadFrame(c_response2);

    m_router->writeFrame(c_request1);
    m_router->writeFrame(c_request2);

    CHECK_REQUESTS_AND_RESPONSES(2, 1);
}

void TestReadWriteOnMockCanBus::testRsp1Rsp2Req1Rsp1()
{
    m_router->expectReadFrame(c_response1);
    m_router->expectReadFrame(c_response2);
    m_router->expectWriteFrame(c_request1);
    m_router->expectReadFrame(c_response1);

    m_router->writeFrame(c_request1);

    CHECK_REQUESTS_AND_RESPONSES(1, 3);
}

void TestReadWriteOnMockCanBus::testWriteFrameErrors_data()
{
    QTest::addColumn<MockCanFrameCollection>("expectedCanFrames");
    QTest::addColumn<CanBusFrameCollection>("outgoingFrames");
    QTest::addColumn<CanBusErrorCollection>("canErrors");

    auto req1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000000000"};
    auto req2 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "0157000000000000"};
    auto rsp2 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "015700AABBCCDD00"};
    auto err1 = MockCanFrame{QCanBusDevice::CanBusError::WriteError,
            MockCanFrame::ErrorNo::NoBufferSpaceAvailable};
    auto err2 = MockCanFrame{QCanBusDevice::CanBusError::ConfigurationError,
            MockCanFrame::ErrorNo::CannotFilterUnknownFrames};

    QTest::newRow("req1-WriteError")
            << MockCanFrameCollection{req1, err1}
            << CanBusFrameCollection{req1}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::WriteError};
    QTest::newRow("req1-WriteError-req2-rsp2")
            << MockCanFrameCollection{req1, err1, req2, rsp2}
            << CanBusFrameCollection{req1, req2}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::WriteError};
    QTest::newRow("req1-req2-WriteError-WriteError")
            << MockCanFrameCollection{req1, req2, err1, err1}
            << CanBusFrameCollection{req1, req2}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::WriteError,
                                     QCanBusDevice::CanBusError::WriteError};
    QTest::newRow("ConfError-req2-rsp2")
            << MockCanFrameCollection{err2, req2, rsp2}
            << CanBusFrameCollection{req2}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::ConfigurationError};
    QTest::newRow("req1-req2-WriteError-rsp2")
            << MockCanFrameCollection{req1, req2, err1, rsp2}
            << CanBusFrameCollection{req1, req2}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::WriteError};
    QTest::newRow("req2-req1-rsp2-WriteError")
            << MockCanFrameCollection{req2, req1, rsp2, err1}
            << CanBusFrameCollection{req2, req1}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::WriteError};
    QTest::newRow("rsp2-ConfError-req1")
            << MockCanFrameCollection{rsp2, err2, req1}
            << CanBusFrameCollection{req1}
            << CanBusErrorCollection{QCanBusDevice::CanBusError::ConfigurationError};
}

void TestReadWriteOnMockCanBus::testWriteFrameErrors()
{
    QFETCH(MockCanFrameCollection, expectedCanFrames);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(CanBusErrorCollection, canErrors);

    setExpectedCanFrames(m_device, expectedCanFrames);

    for (const auto &frame : outgoingFrames) {
        m_device->writeFrame(frame);
    }
    QCOMPARE(m_errorSpy->size(), canErrors.size());
    for (int i = 0; i < canErrors.size(); ++i) {
        QCOMPARE((*m_errorSpy)[i][0].value<QCanBusDevice::CanBusError>(), canErrors[i]);
    }
    QCOMPARE(actualCanFrames(m_device), expectedCanFrames);
}

QTEST_GUILESS_MAIN(TestReadWriteOnMockCanBus)

#include "test_read_write_on_mock_can_bus.moc"
