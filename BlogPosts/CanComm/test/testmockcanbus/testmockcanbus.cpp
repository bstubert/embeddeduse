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

class TestMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testWriteFrame_data();
    void testWriteFrame();
    void testReadParameter_data();
    void testReadParameter();
    void testWriteFrameErrors_data();
    void testWriteFrameErrors();
    void testReceiveOwnConfigurationKey();
    void testReceiveOwnWrittenFrames_data();
    void testReceiveOwnWrittenFrames();
    void testWriteBufferOverflow_data();
    void testWriteBufferOverflow();

private:
    QCanBusDevice *createAndConnectDevice(const QString &interface);
};

void TestMockCanBus::initTestCase()
{
    // The loader for the CAN bus plugins adds /canbus to each library path and looks for
    // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
    // is called "canbus".
    QCoreApplication::addLibraryPath("../../");
}

void TestMockCanBus::testWriteFrame_data()
{
    QTest::addColumn<MockCanFrameCollection>("outgoingFrames");
    QTest::addColumn<MockCanFrameCollection>("expectedCanIo");
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
    QTest::newRow("0 written, 0 expected")
            << MockCanFrameCollection{}
            << MockCanFrameCollection{}
            << true;
    QTest::newRow("1 written, 0 expected")
            << MockCanFrameCollection{frame1}
            << MockCanFrameCollection{}
            << false;
    QTest::newRow("0 written, 1 expected")
            << MockCanFrameCollection{}
            << MockCanFrameCollection{frame1}
            << false;
}

void TestMockCanBus::testWriteFrame()
{
    QFETCH(MockCanFrameCollection, outgoingFrames);
    QFETCH(MockCanFrameCollection, expectedCanIo);
    QFETCH(bool, isCanIoOk);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    setExpectedCanIo(device.get(), expectedCanIo);
    QSignalSpy writtenSpy{device.get(), &QCanBusDevice::framesWritten};

    for (const auto &frame : outgoingFrames) {
        auto ok = device->writeFrame(frame);
        QVERIFY(ok);
    }
    QCOMPARE(actualCanIo(device.get()) == expectedCanIo, isCanIoOk);
    QCOMPARE(writtenSpy.size(), outgoingFrames.size());
}

void TestMockCanBus::testReadParameter_data()
{
    QTest::addColumn<MockCanFrameCollection>("expectedCanIo");
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

void TestMockCanBus::testReadParameter()
{
    QFETCH(MockCanFrameCollection, expectedCanIo);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(CanBusFrameCollection, incomingFrames);
    QFETCH(int, receivedCount);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QSignalSpy receivedSpy{device.get(), &QCanBusDevice::framesReceived};
    setExpectedCanIo(device.get(), expectedCanIo);
    for (const auto &frame : outgoingFrames) {
        device->writeFrame(frame);
    }
    QCOMPARE(receivedSpy.size(), receivedCount);
    QCOMPARE(actualCanIo(device.get()), expectedCanIo);
    QCOMPARE(device->readAllFrames(), incomingFrames);
}

void TestMockCanBus::testWriteFrameErrors_data()
{
    QTest::addColumn<MockCanFrameCollection>("expectedCanIo");
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

void TestMockCanBus::testWriteFrameErrors()
{
    QFETCH(MockCanFrameCollection, expectedCanIo);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(CanBusErrorCollection, canErrors);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QSignalSpy errorSpy{device.get(), &QCanBusDevice::errorOccurred};
    setExpectedCanIo(device.get(), expectedCanIo);

    for (const auto &frame : outgoingFrames) {
        device->writeFrame(frame);
    }
    QCOMPARE(errorSpy.size(), canErrors.size());
    for (int i = 0; i < canErrors.size(); ++i) {
        QCOMPARE(errorSpy[i][0].value<QCanBusDevice::CanBusError>(), canErrors[i]);
    }
    QCOMPARE(actualCanIo(device.get()), expectedCanIo);
}

void TestMockCanBus::testReceiveOwnConfigurationKey()
{
    const auto receiveOwnConfKey = QCanBusDevice::ConfigurationKey::ReceiveOwnKey;
    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QVERIFY(!device->configurationParameter(receiveOwnConfKey).toBool());
    device->setConfigurationParameter(receiveOwnConfKey, true);
    QVERIFY(device->configurationParameter(receiveOwnConfKey).toBool());
    device->setConfigurationParameter(receiveOwnConfKey, false);
    QVERIFY(!device->configurationParameter(receiveOwnConfKey).toBool());
}

void TestMockCanBus::testReceiveOwnWrittenFrames_data()
{
    QTest::addColumn<bool>("receiveOwn");
    QTest::addColumn<CanBusFrameCollection>("outgoingFrames");
    QTest::addColumn<MockCanFrameCollection>("expectedCanIo");

    auto out1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000000000"};
    auto ownOut1 = MockCanFrame{MockCanFrame::Type::OwnIncoming, out1};
    auto in1 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "018A0103A4000000"};

    QTest::newRow("own on: out1-ownOut1")
            << true
            << CanBusFrameCollection{out1}
            << MockCanFrameCollection{out1, ownOut1};
    QTest::newRow("own on: out1-ownOut1-in1")
            << true
            << CanBusFrameCollection{out1}
            << MockCanFrameCollection{out1, ownOut1, in1};
    QTest::newRow("own on: out1-in1-ownOut1")
            << true
            << CanBusFrameCollection{out1}
            << MockCanFrameCollection{out1, in1, ownOut1};
    QTest::newRow("own off, but own expected")
            << false
            << CanBusFrameCollection{out1}
            << MockCanFrameCollection{out1, ownOut1};
}

void TestMockCanBus::testReceiveOwnWrittenFrames()
{
    QFETCH(bool, receiveOwn);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(MockCanFrameCollection, expectedCanIo);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    device->setConfigurationParameter(QCanBusDevice::ConfigurationKey::ReceiveOwnKey,
                                      receiveOwn);
    setExpectedCanIo(device.get(), expectedCanIo);

    for (const auto &frame : outgoingFrames) {
        device->writeFrame(frame);
    }
    auto goldenCanIo = MockCanFrameCollection{};
    std::copy_if(expectedCanIo.cbegin(), expectedCanIo.cend(), std::back_inserter(goldenCanIo),
                 [receiveOwn](const MockCanFrame &f) {
                     return receiveOwn || !f.isOwnIncoming();
                 });
    QCOMPARE(actualCanIo(device.get()), goldenCanIo);
}

void TestMockCanBus::testWriteBufferOverflow_data()
{
    auto req1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "0101000000000000"};
    auto rsp1 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "0101001200000000"};
    auto req2 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "0102000000000000"};
    auto rsp2 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0102U, "0102002300000000"};

}

void TestMockCanBus::testWriteBufferOverflow()
{

}

QCanBusDevice *TestMockCanBus::createAndConnectDevice(const QString &interface)
{
    QString errorStr;
    auto device = QCanBus::instance()->createDevice("mockcan", interface, &errorStr);
    device->connectDevice();
    return device;
}

QTEST_GUILESS_MAIN(TestMockCanBus)

#include "testmockcanbus.moc"
