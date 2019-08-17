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

class TestReadWriteOnMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void testWriteFrame_data();
    void testWriteFrame();

    void testWriteOneExpectedFrame();
    void testWriteOneUnexpectedFrame();
    void testWriteMoreFramesThanExpected();
    void testWriteLessFramesThanExpected();
    void testWriteTwoFramesInExpectedOrder();
    void testWriteTwoFramesInUnexpectedOrder();

    void testReadParameter_data();
    void testReadParameter();
    void testWriteFrameErrors_data();
    void testWriteFrameErrors();

private:    
    void expectWriteFrame(const QCanBusFrame &frame);

    const QCanBusFrame c_frame1{0x18ef0201U, QByteArray::fromHex("018A010000000000")};
    const QCanBusFrame c_frame2{0x18ef0301U, QByteArray::fromHex("01B5010000000000")};

    QCanBusDevice *m_device;
    QSignalSpy *m_writtenSpy;
    QSignalSpy *m_receivedSpy;
    QSignalSpy *m_errorSpy;
};

#define CHECK_FRAMES_EXPECTED_EQUAL \
    QCOMPARE(::actualCanFrames(m_device), ::expectedCanFrames(m_device)); \
    QCOMPARE(m_writtenSpy->size(), ::expectedCanFrameCount(m_device, MockCanFrame::Type::Outgoing))

#define CHECK_FRAMES_EXPECTED_NOT_EQUAL \
    QEXPECT_FAIL("", "Frames expected to differ!", Continue); \
    QCOMPARE(::actualCanFrames(m_device), ::expectedCanFrames(m_device)); \
    if (::actualCanFrames(m_device) == ::expectedCanFrames(m_device)) { \
        QCOMPARE(m_writtenSpy->size(), \
                 ::expectedCanFrameCount(m_device, MockCanFrame::Type::Outgoing)); \
    }


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
    m_device = QCanBus::instance()->createDevice("mockcan", "mcan0", &errorStr);
    m_device->connectDevice();

    m_writtenSpy = new QSignalSpy{m_device, &QCanBusDevice::framesWritten};
    m_receivedSpy = new QSignalSpy{m_device, &QCanBusDevice::framesReceived};
    m_errorSpy = new QSignalSpy{m_device, &QCanBusDevice::errorOccurred};

    QVERIFY(actualCanFrames(m_device).isEmpty());
    QVERIFY(expectedCanFrames(m_device).isEmpty());
}

void TestReadWriteOnMockCanBus::cleanup()
{
    delete m_device;
    delete m_writtenSpy;
    delete m_receivedSpy;
    delete m_errorSpy;
}

void TestReadWriteOnMockCanBus::testWriteFrame_data()
{
    QTest::addColumn<MockCanFrameCollection>("outgoingFrames");
    QTest::addColumn<MockCanFrameCollection>("expectedCanFrames");
    QTest::addColumn<bool>("isCanIoOk");
    auto frame1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U,
            "018A010000000000"};
    auto frame2 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0301U,
            "01B5010000000000"};

    QTest::newRow("1 written, same expected")
            << MockCanFrameCollection{frame1}
            << MockCanFrameCollection{frame1}
            << true;
    QTest::newRow("1 written, other expected")
            << MockCanFrameCollection{frame2}
            << MockCanFrameCollection{frame1}
            << false;
    QTest::newRow("2 written, 1 expected")
            << MockCanFrameCollection{frame1, frame2}
            << MockCanFrameCollection{frame1}
            << false;
    QTest::newRow("1 written, 2 expected")
            << MockCanFrameCollection{frame1}
            << MockCanFrameCollection{frame1, frame2}
            << false;
    QTest::newRow("2 written, 2 expected")
            << MockCanFrameCollection{frame1, frame2}
            << MockCanFrameCollection{frame1, frame2}
            << true;
    QTest::newRow("2 written, 2 expected but in different order")
            << MockCanFrameCollection{frame1, frame2}
            << MockCanFrameCollection{frame2, frame1}
            << false;
    QTest::newRow("0 written, 0 expected")      // Checked in init()
            << MockCanFrameCollection{}
            << MockCanFrameCollection{}
            << true;
    QTest::newRow("1 written, 0 expected")      // Duplicate of "2 written, 1 expected"
            << MockCanFrameCollection{frame1}
            << MockCanFrameCollection{}
            << false;
    QTest::newRow("0 written, 1 expected")      // Duplicate of "1 written, 2 expected"
            << MockCanFrameCollection{}
            << MockCanFrameCollection{frame1}
            << false;
}

void TestReadWriteOnMockCanBus::testWriteFrame()
{
    QFETCH(MockCanFrameCollection, outgoingFrames);
    QFETCH(MockCanFrameCollection, expectedCanFrames);
    QFETCH(bool, isCanIoOk);

    setExpectedCanFrames(m_device, expectedCanFrames);

    for (const auto &frame : outgoingFrames) {
        QVERIFY(m_device->writeFrame(frame));
    }
    QCOMPARE(actualCanFrames(m_device) == expectedCanFrames, isCanIoOk);
    QCOMPARE(m_writtenSpy->size(), outgoingFrames.size());
}

void TestReadWriteOnMockCanBus::testWriteOneExpectedFrame()
{
    expectWriteFrame(c_frame1);

    m_device->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteOneUnexpectedFrame()
{
    expectWriteFrame(c_frame1);

    m_device->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteMoreFramesThanExpected()
{
    expectWriteFrame(c_frame1);

    m_device->writeFrame(c_frame1);
    m_device->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteLessFramesThanExpected()
{
    expectWriteFrame(c_frame1);
    expectWriteFrame(c_frame2);

    m_device->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteTwoFramesInExpectedOrder()
{
    expectWriteFrame(c_frame1);
    expectWriteFrame(c_frame2);

    m_device->writeFrame(c_frame1);
    m_device->writeFrame(c_frame2);

    CHECK_FRAMES_EXPECTED_EQUAL;
}

void TestReadWriteOnMockCanBus::testWriteTwoFramesInUnexpectedOrder()
{
    expectWriteFrame(c_frame1);
    expectWriteFrame(c_frame2);

    m_device->writeFrame(c_frame2);
    m_device->writeFrame(c_frame1);

    CHECK_FRAMES_EXPECTED_NOT_EQUAL;
}



void TestReadWriteOnMockCanBus::testReadParameter_data()
{
    QTest::addColumn<MockCanFrameCollection>("expectedCanFrames");
    QTest::addColumn<CanBusFrameCollection>("outgoingFrames");
    QTest::addColumn<CanBusFrameCollection>("incomingFrames");
    QTest::addColumn<int>("receivedCount");
    auto req1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000000000"};
    auto rsp1 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "018A014433221100"};
    auto req2 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "0157000000000000"};
    auto rsp2 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "015700AABBCCDD00"};

    QTest::newRow("req1-rsp1")
            << MockCanFrameCollection{req1, rsp1}
            << CanBusFrameCollection{req1}
            << CanBusFrameCollection{rsp1}
            << 1;
    QTest::newRow("req1-rsp1-req2-rsp2")
            << MockCanFrameCollection{req1, rsp1, req2, rsp2}
            << CanBusFrameCollection{req1, req2}
            << CanBusFrameCollection{rsp1, rsp2}
            << 2;
    QTest::newRow("req1-req2-rsp1-rsp2")
            << MockCanFrameCollection{req1, req2, rsp1, rsp2}
            << CanBusFrameCollection{req1, req2}
            << CanBusFrameCollection{rsp1, rsp2}
            << 1;
    QTest::newRow("req1")
            << MockCanFrameCollection{req1}
            << CanBusFrameCollection{req1}
            << CanBusFrameCollection{}
            << 0;
    QTest::newRow("req1-req2-rsp2")
            << MockCanFrameCollection{req1, req2, rsp2}
            << CanBusFrameCollection{req1, req2}
            << CanBusFrameCollection{rsp2}
            << 1;
    QTest::newRow("rsp1-rsp2-req1-rsp1")
            << MockCanFrameCollection{rsp1, rsp2, req1, rsp1}
            << CanBusFrameCollection{req1}
            << CanBusFrameCollection{rsp1, rsp2, rsp1}
            << 2;
}

void TestReadWriteOnMockCanBus::testReadParameter()
{
    QFETCH(MockCanFrameCollection, expectedCanFrames);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(CanBusFrameCollection, incomingFrames);
    QFETCH(int, receivedCount);

    setExpectedCanFrames(m_device, expectedCanFrames);

    for (const auto &frame : outgoingFrames) {
        m_device->writeFrame(frame);
    }
    QCOMPARE(m_receivedSpy->size(), receivedCount);
    QCOMPARE(actualCanFrames(m_device), expectedCanFrames);
    QCOMPARE(m_device->readAllFrames(), incomingFrames);
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

void TestReadWriteOnMockCanBus::expectWriteFrame(const QCanBusFrame &frame)
{
    auto frames = expectedCanFrames(m_device);
    frames.append(MockCanFrame{MockCanFrame::Type::Outgoing, frame});
    setExpectedCanFrames(m_device, frames);
}

QTEST_GUILESS_MAIN(TestReadWriteOnMockCanBus)

#include "test_read_write_on_mock_can_bus.moc"
