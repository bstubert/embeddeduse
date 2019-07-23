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

class TestMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testAvailableDevices_data();
    void testAvailableDevices();
    void testCreateDevice_data();
    void testCreateDevice();
    void testConnectDevice_data();
    void testConnectDevice();
    void testConnectConnectedDevice();
    void testDisconnectDevice();
    void testDisconnectUnconnectedDevice();
    void testActualCanIoConfiguration_data();
    void testActualCanIoConfiguration();
    void testExpectedCanIoConfiguration_data();
    void testExpectedCanIoConfiguration();
    void testWriteFrame_data();
    void testWriteFrame();
    void testReadParameter_data();
    void testReadParameter();
    void testDeviceErrors_data();
    void testDeviceErrors();
    void testWriteFrameErrors();

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

void TestMockCanBus::testAvailableDevices_data()
{
    QTest::addColumn<QString>("plugin");
    QTest::addColumn<QStringList>("interfaces");

    QTest::newRow("mockcan: mcan0, mcan1") << QString{"mockcan"} << QStringList{"mcan0", "mcan1"};
    QTest::newRow("muppetcan: none") << QString{"muppetcan"} << QStringList{};
}

void TestMockCanBus::testAvailableDevices()
{
    QFETCH(QString, plugin);
    QFETCH(QStringList, interfaces);

    QString currentErrorStr;
    auto currentDevices = QCanBus::instance()->availableDevices(plugin, &currentErrorStr);
    QStringList currentInterfaces;
    std::transform(currentDevices.cbegin(), currentDevices.cend(),
                   std::back_inserter(currentInterfaces),
                   [](const QCanBusDeviceInfo &info) { return info.name(); });
    QCOMPARE(currentInterfaces, interfaces);
}

void TestMockCanBus::testCreateDevice_data()
{
    QTest::addColumn<QString>("plugin");
    QTest::addColumn<QString>("interface");
    QTest::addColumn<bool>("isNull");
    QTest::addColumn<QString>("errorStr");

    QTest::newRow("mockcan/mcan0") << QString{"mockcan"} << QString{"mcan0"} << false
                                  << QString{};
    QTest::newRow("muppetcan/mcan0") << QString{"muppetcan"} << QString{"mcan0"} << true
                                  << QString{"No such plugin: \'muppetcan\'"};
    QTest::newRow("mockcan/sky9") << QString{"mockcan"} << QString{"sky9"} << false
                                  << QString{};
    QTest::newRow("muppetcan/sky9") << QString{"muppetcan"} << QString{"sky9"} << true
                                  << QString{"No such plugin: \'muppetcan\'"};
}

// QCanBus::createDevice() returns nullptr and an error message, if the plugin does not exist.
// It returns a non-null QCanBusDevice, if the plugin exists. Whether the CAN interface exists,
// does not matter.
void TestMockCanBus::testCreateDevice()
{
    QFETCH(QString, plugin);
    QFETCH(QString, interface);
    QFETCH(bool, isNull);
    QFETCH(QString, errorStr);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice(plugin, interface, &currentErrorStr)};
    QCOMPARE(device == nullptr, isNull);
    QCOMPARE(currentErrorStr, errorStr);
}

void TestMockCanBus::testConnectDevice_data()
{
    QTest::addColumn<QString>("interface");
    QTest::addColumn<bool>("connected");

    QTest::newRow("mcan0") << QString{"mcan0"} << true;
    QTest::newRow("sky7") << QString{"sky7"} << false;
}

void TestMockCanBus::testConnectDevice()
{
    QFETCH(QString, interface);
    QFETCH(bool, connected);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", interface, &currentErrorStr)};

    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);
    auto ok = device->connectDevice();
    QCOMPARE(ok, connected);
    QCOMPARE(device->state(), connected ? QCanBusDevice::ConnectedState
                                        : QCanBusDevice::UnconnectedState);
}

void TestMockCanBus::testConnectConnectedDevice()
{
    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan0", &currentErrorStr)};

    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);
    auto ok = device->connectDevice();
    QVERIFY(ok);
    QCOMPARE(device->state(), QCanBusDevice::ConnectedState);

    ok = device->connectDevice();
    QVERIFY(!ok);
    QCOMPARE(device->state(), QCanBusDevice::ConnectedState);
    QCOMPARE(device->error(), QCanBusDevice::ConnectionError);
}

void TestMockCanBus::testDisconnectDevice()
{
    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);

    auto ok = device->connectDevice();
    QVERIFY(ok);
    QCOMPARE(device->state(), QCanBusDevice::ConnectedState);
    device->disconnectDevice();
    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);
}

void TestMockCanBus::testDisconnectUnconnectedDevice()
{
    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);
    device->disconnectDevice();
    QCOMPARE(device->state(), QCanBusDevice::UnconnectedState);
}

void TestMockCanBus::testActualCanIoConfiguration_data()
{
    QTest::addColumn<ExpectedCanFrameCollection>("frames");

    QTest::newRow("0 frames") << ExpectedCanFrameCollection{};
    QTest::newRow("1 frame") << ExpectedCanFrameCollection{
        CanUtils::makeOutgoingFrame(0x18ef0201U, "018A010000000000")
    };
    QTest::newRow("2 frames") << ExpectedCanFrameCollection{
        CanUtils::makeOutgoingFrame(0x185f0901U, "018A010102300405"),
        CanUtils::makeOutgoingFrame(0x18ed0301U, "018A0105a2f0b405")
    };
}

void TestMockCanBus::testActualCanIoConfiguration()
{
    QFETCH(ExpectedCanFrameCollection, frames);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QVERIFY(CanUtils::actualCanIo(device.get()).isEmpty());

    CanUtils::setActualCanIo(device.get(), frames);
    QCOMPARE(CanUtils::actualCanIo(device.get()), frames);
}

void TestMockCanBus::testExpectedCanIoConfiguration_data()
{
    QTest::addColumn<ExpectedCanFrameCollection>("frames");

    QTest::newRow("0 frames") << ExpectedCanFrameCollection{};
    QTest::newRow("1 frame") << ExpectedCanFrameCollection{
        CanUtils::makeOutgoingFrame(0x18ef0201U, "018A010000000000")
    };
    QTest::newRow("2 frames") << ExpectedCanFrameCollection{
        CanUtils::makeOutgoingFrame(0x185f0901U, "018A010102300405"),
        CanUtils::makeOutgoingFrame(0x18ed0301U, "018A0105a2f0b405")
    };
}

void TestMockCanBus::testExpectedCanIoConfiguration()
{
    QFETCH(ExpectedCanFrameCollection, frames);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QVERIFY(CanUtils::expectedCanIo(device.get()).isEmpty());

    CanUtils::setExpectedCanIo(device.get(), frames);
    QCOMPARE(CanUtils::expectedCanIo(device.get()), frames);
}

void TestMockCanBus::testWriteFrame_data()
{
    QTest::addColumn<ExpectedCanFrameCollection>("outgoingFrames");
    QTest::addColumn<ExpectedCanFrameCollection>("expectedCanIo");
    QTest::addColumn<bool>("isCanIoOk");
    auto frame1 = CanUtils::makeOutgoingFrame(0x18ef0201U, "018A010000000000");
    auto frame2 = CanUtils::makeOutgoingFrame(0x18ef0301U, "01B5010000000000");

    QTest::newRow("1 written, same expected")
            << ExpectedCanFrameCollection{frame1}
            << ExpectedCanFrameCollection{frame1}
            << true;
    QTest::newRow("1 written, other expected")
            << ExpectedCanFrameCollection{frame2}
            << ExpectedCanFrameCollection{frame1}
            << false;
    QTest::newRow("2 written, 1 expected")
            << ExpectedCanFrameCollection{frame1, frame2}
            << ExpectedCanFrameCollection{frame1}
            << false;
    QTest::newRow("1 written, 2 expected")
            << ExpectedCanFrameCollection{frame1}
            << ExpectedCanFrameCollection{frame1, frame2}
            << false;
    QTest::newRow("2 written, 2 expected")
            << ExpectedCanFrameCollection{frame1, frame2}
            << ExpectedCanFrameCollection{frame1, frame2}
            << true;
    QTest::newRow("2 written, 2 expected but in different order")
            << ExpectedCanFrameCollection{frame1, frame2}
            << ExpectedCanFrameCollection{frame2, frame1}
            << false;
    QTest::newRow("0 written, 0 expected")
            << ExpectedCanFrameCollection{}
            << ExpectedCanFrameCollection{}
            << true;
    QTest::newRow("1 written, 0 expected")
            << ExpectedCanFrameCollection{frame1}
            << ExpectedCanFrameCollection{}
            << false;
    QTest::newRow("0 written, 1 expected")
            << ExpectedCanFrameCollection{}
            << ExpectedCanFrameCollection{frame1}
            << false;
}

void TestMockCanBus::testWriteFrame()
{
    QFETCH(ExpectedCanFrameCollection, outgoingFrames);
    QFETCH(ExpectedCanFrameCollection, expectedCanIo);
    QFETCH(bool, isCanIoOk);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    CanUtils::setExpectedCanIo(device.get(), expectedCanIo);
    QSignalSpy writtenSpy{device.get(), &QCanBusDevice::framesWritten};

    for (const auto &frame : outgoingFrames) {
        auto ok = device->writeFrame(frame.second);
        QVERIFY(ok);
    }
    QCOMPARE(CanUtils::actualCanIo(device.get()) == expectedCanIo, isCanIoOk);
    QCOMPARE(writtenSpy.size(), outgoingFrames.size());
}

void TestMockCanBus::testReadParameter_data()
{
    QTest::addColumn<ExpectedCanFrameCollection>("expectedCanIo");
    QTest::addColumn<CanBusFrameCollection>("outgoingFrames");
    QTest::addColumn<CanBusFrameCollection>("incomingFrames");
    QTest::addColumn<int>("receivedCount");
    auto req1 = CanUtils::makeOutgoingFrame(0x18ef0201U, "018A010000000000");
    auto rsp1 = CanUtils::makeIncomingFrame(0x18ef0102U, "018A014433221100");
    auto req2 = CanUtils::makeOutgoingFrame(0x18ef0201U, "0157000000000000");
    auto rsp2 = CanUtils::makeIncomingFrame(0x18ef0102U, "015700AABBCCDD00");

    QTest::newRow("req1-rsp1")
            << ExpectedCanFrameCollection{req1, rsp1}
            << CanBusFrameCollection{req1.second}
            << CanBusFrameCollection{rsp1.second}
            << 1;
    QTest::newRow("req1-rsp1-req2-rsp2")
            << ExpectedCanFrameCollection{req1, rsp1, req2, rsp2}
            << CanBusFrameCollection{req1.second, req2.second}
            << CanBusFrameCollection{rsp1.second, rsp2.second}
            << 2;
    QTest::newRow("req1-req2-rsp1-rsp2")
            << ExpectedCanFrameCollection{req1, req2, rsp1, rsp2}
            << CanBusFrameCollection{req1.second, req2.second}
            << CanBusFrameCollection{rsp1.second, rsp2.second}
            << 1;
    QTest::newRow("req1")
            << ExpectedCanFrameCollection{req1}
            << CanBusFrameCollection{req1.second}
            << CanBusFrameCollection{}
            << 0;
    QTest::newRow("req1-req2-rsp2")
            << ExpectedCanFrameCollection{req1, req2, rsp2}
            << CanBusFrameCollection{req1.second, req2.second}
            << CanBusFrameCollection{rsp2.second}
            << 1;
    QTest::newRow("rsp1-rsp2-req1-rsp1")
            << ExpectedCanFrameCollection{rsp1, rsp2, req1, rsp1}
            << CanBusFrameCollection{req1.second}
            << CanBusFrameCollection{rsp1.second, rsp2.second, rsp1.second}
            << 2;
}

void TestMockCanBus::testReadParameter()
{
    QFETCH(ExpectedCanFrameCollection, expectedCanIo);
    QFETCH(CanBusFrameCollection, outgoingFrames);
    QFETCH(CanBusFrameCollection, incomingFrames);
    QFETCH(int, receivedCount);

    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QSignalSpy receivedSpy{device.get(), &QCanBusDevice::framesReceived};
    CanUtils::setExpectedCanIo(device.get(), expectedCanIo);
    for (const auto &frame : outgoingFrames) {
        device->writeFrame(frame);
    }
    QCOMPARE(receivedSpy.size(), receivedCount);
    QCOMPARE(CanUtils::actualCanIo(device.get()), expectedCanIo);
    QCOMPARE(device->readAllFrames(), incomingFrames);
}

void TestMockCanBus::testDeviceErrors_data()
{
    QTest::addColumn<QCanBusDevice::CanBusError>("canError");
    QTest::addColumn<CanErrorNo>("errorNo");
    QTest::addColumn<QString>("errorString");

    QTest::newRow("WriteError - NoBufferSpaceAvailable")
            << QCanBusDevice::CanBusError::WriteError
            << CanErrorNo::NoBufferSpaceAvailable
            << QStringLiteral("No buffer space available");
    QTest::newRow("ConfigurationError - CannotFilterUnknownFrames")
            << QCanBusDevice::CanBusError::ConfigurationError
            << CanErrorNo::CannotFilterUnknownFrames
            << QStringLiteral("Cannot set filter for frame type: unknown");
}

void TestMockCanBus::testDeviceErrors()
{
    QFETCH(QCanBusDevice::CanBusError, canError);
    QFETCH(CanErrorNo, errorNo);
    QFETCH(QString, errorString);

    auto expectedError = CanUtils::makeDeviceError(canError, errorNo);
    QCOMPARE(expectedError.first, CanFrameType::DeviceError);
    QVERIFY(!expectedError.second.isValid());

    auto deviceError = CanUtils::deviceError(expectedError);
    QCOMPARE(deviceError.first, errorString);
    QCOMPARE(deviceError.second, canError);
}

void TestMockCanBus::testWriteFrameErrors()
{
    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QSignalSpy errorSpy{device.get(), &QCanBusDevice::errorOccurred};
    auto req1 = CanUtils::makeOutgoingFrame(0x18ef0201U, "018A010000000000");
    auto err1 = CanUtils::makeDeviceError(QCanBusDevice::CanBusError::WriteError,
                                          CanErrorNo::NoBufferSpaceAvailable);
    CanUtils::setExpectedCanIo(device.get(), ExpectedCanFrameCollection{req1, err1});
    device->writeFrame(req1.second);
    QCOMPARE(errorSpy.size(), 1);
    QCOMPARE(errorSpy[0][0].value<QCanBusDevice::CanBusError>(),
            CanUtils::deviceError(err1).second);
    QCOMPARE(device->error(), CanUtils::deviceError(err1).second);
    QCOMPARE(device->errorString(), CanUtils::deviceError(err1).first);
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
