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

    void testReq1WriteError();
    void testReq1WriteErrorReq2Rsp2();
    void testTwoRequestsTwoWriteErrors();
    void testConfErrorReq2Rsp2();
    void testRsp2ConfErrorReq1();

private:    
    const QCanBusFrame c_frame1{0x18ef0201U, QByteArray::fromHex("018A010000000000")};
    const QCanBusFrame c_frame2{0x18ef0301U, QByteArray::fromHex("01B5010000000000")};

    const QCanBusFrame c_request1{0x18ef0201U, QByteArray::fromHex("018A010000000000")};
    const QCanBusFrame c_response1{0x18ef0102U, QByteArray::fromHex("018A014433221100")};
    const QCanBusFrame c_request2{0x18ef0201U, QByteArray::fromHex("0157000000000000")};
    const QCanBusFrame c_response2{0x18ef0102U, QByteArray::fromHex("015700AABBCCDD00")};

    MockCanBusRouter *m_router;
    QSignalSpy *m_writtenSpy;
    QSignalSpy *m_receivedSpy;
    QSignalSpy *m_errorSpy;
};

#define CHECK_FRAMES_EXPECTED_EQUAL(writeCount) \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames()); \
    QCOMPARE(m_writtenSpy->size(), writeCount)

#define CHECK_FRAMES_EXPECTED_NOT_EQUAL \
    QEXPECT_FAIL("", "Frames expected to differ!", Continue); \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames())

#define CHECK_REQUESTS_AND_RESPONSES(writeCount, readCount) \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames()); \
    QCOMPARE(m_writtenSpy->size(), writeCount); \
    QCOMPARE(m_receivedSpy->size(), readCount)


#define CHECK_ERROR_COUNT_AND_LAST_ERROR(errorCount, lastError) \
    QCOMPARE(m_errorSpy->size(), errorCount); \
    QCOMPARE(m_router->error(), lastError); \
    QCOMPARE(m_router->actualCanFrames(), m_router->expectedCanFrames())


void TestReadWriteOnMockCanBus::initTestCase()
{
    // The loader for the CAN bus plugins adds /canbus to each library path and looks for
    // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
    // is called "canbus".
    QCoreApplication::addLibraryPath("../../");
}

void TestReadWriteOnMockCanBus::init()
{
    m_router = new MockCanBusRouter{};
    m_writtenSpy = new QSignalSpy{m_router, &MockCanBusRouter::framesWritten};
    m_receivedSpy = new QSignalSpy{m_router, &MockCanBusRouter::framesReceived};
    m_errorSpy = new QSignalSpy{m_router, &MockCanBusRouter::errorOccurred};

    QVERIFY(m_router->actualCanFrames().isEmpty());
    QVERIFY(m_router->expectedCanFrames().isEmpty());
}

void TestReadWriteOnMockCanBus::cleanup()
{
    delete m_router;
    delete m_writtenSpy;
    delete m_receivedSpy;
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

void TestReadWriteOnMockCanBus::testReq1WriteError()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectError(QCanBusDevice::WriteError, MockCanFrame::ErrorNo::NoBufferSpaceAvailable);

    m_router->writeFrame(c_request1);

    CHECK_ERROR_COUNT_AND_LAST_ERROR(1, QCanBusDevice::WriteError);
}

void TestReadWriteOnMockCanBus::testReq1WriteErrorReq2Rsp2()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectError(QCanBusDevice::WriteError, MockCanFrame::ErrorNo::NoBufferSpaceAvailable);
    m_router->expectWriteFrame(c_request2);
    m_router->expectReadFrame(c_response2);

    m_router->writeFrame(c_request1);
    m_router->writeFrame(c_request2);

    CHECK_ERROR_COUNT_AND_LAST_ERROR(1, QCanBusDevice::WriteError);
}

void TestReadWriteOnMockCanBus::testTwoRequestsTwoWriteErrors()
{
    m_router->expectWriteFrame(c_request1);
    m_router->expectWriteFrame(c_request2);
    m_router->expectError(QCanBusDevice::WriteError, MockCanFrame::ErrorNo::NoBufferSpaceAvailable);
    m_router->expectError(QCanBusDevice::WriteError, MockCanFrame::ErrorNo::NoBufferSpaceAvailable);

    m_router->writeFrame(c_request1);
    m_router->writeFrame(c_request2);

    CHECK_ERROR_COUNT_AND_LAST_ERROR(2, QCanBusDevice::WriteError);
}

void TestReadWriteOnMockCanBus::testConfErrorReq2Rsp2()
{
    m_router->expectError(QCanBusDevice::ConfigurationError,
                          MockCanFrame::ErrorNo::CannotFilterUnknownFrames);
    m_router->expectWriteFrame(c_request2);
    m_router->expectReadFrame(c_response2);

    m_router->writeFrame(c_request2);

    CHECK_ERROR_COUNT_AND_LAST_ERROR(1, QCanBusDevice::ConfigurationError);
}

void TestReadWriteOnMockCanBus::testRsp2ConfErrorReq1()
{
    m_router->expectReadFrame(c_response2);
    m_router->expectError(QCanBusDevice::ConfigurationError,
                          MockCanFrame::ErrorNo::CannotFilterUnknownFrames);
    m_router->expectWriteFrame(c_request1);

    m_router->writeFrame(c_request1);

    CHECK_ERROR_COUNT_AND_LAST_ERROR(1, QCanBusDevice::ConfigurationError);
}

QTEST_GUILESS_MAIN(TestReadWriteOnMockCanBus)

#include "test_read_write_on_mock_can_bus.moc"
