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
#include "canbusrouter.h"
#include "mockcanbusrouter.h"
#include "mockcanutils.h"

class TestConnectToMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testAvailableDevicesOfExistingPlugin();
    void testAvailableDevicesOfNonExistingPlugin();
    void testCreateExistingPlugin();
    void testCreateNonExistingPlugin();
    void testConnectToExistingDevice();
    void testConnectToNonExistingDevice();
    void testActualCanIoConfiguration();
    void testExpectedCanIoConfiguration();
};

void TestConnectToMockCanBus::initTestCase()
{
    // The loader for the CAN bus plugins adds /canbus to each library path and looks for
    // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
    // is called "canbus".
    QCoreApplication::addLibraryPath("../../");
}

void TestConnectToMockCanBus::testAvailableDevicesOfExistingPlugin()
{
    auto currentDevices = QCanBus::instance()->availableDevices("mockcan");
    QStringList currentInterfaces;
    for (const auto &device : currentDevices)
    {
        currentInterfaces.append(device.name());
    }
    QCOMPARE(currentInterfaces, (QStringList{"mcan0", "mcan1"}));
}

void TestConnectToMockCanBus::testAvailableDevicesOfNonExistingPlugin()
{
    auto currentDevices = QCanBus::instance()->availableDevices("muppetcan");
    QVERIFY(currentDevices.isEmpty());
}

void TestConnectToMockCanBus::testCreateExistingPlugin()
{
    CanBusRouter router{"mockcan", "mcan0"};
    QCOMPARE(router.error(), QCanBusDevice::NoError);
    QVERIFY(router.errorString().isEmpty());
}

void TestConnectToMockCanBus::testCreateNonExistingPlugin()
{
    CanBusRouter router{"muppetcan", "mcan1"};
    QCOMPARE(router.error(), QCanBusDevice::ConnectionError);
    QCOMPARE(router.errorString(), QString{"No such plugin: \'muppetcan\'"});
}

void TestConnectToMockCanBus::testConnectToExistingDevice()
{
    CanBusRouter router{"mockcan", "mcan0"};
    QCOMPARE(router.error(), QCanBusDevice::NoError);
    QCOMPARE(router.state(), QCanBusDevice::ConnectedState);
}

void TestConnectToMockCanBus::testConnectToNonExistingDevice()
{
    CanBusRouter router{"mockcan", "sky7"};
    QCOMPARE(router.error(), QCanBusDevice::CanBusError::ConnectionError);
    QCOMPARE(router.state(), QCanBusDevice::UnconnectedState);
}

void TestConnectToMockCanBus::testActualCanIoConfiguration()
{
    auto frames = MockCanFrameCollection{
        MockCanFrame{MockCanFrame::Type::Outgoing, 0x185f0901U, "018A010102300405"},
        MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ed0301U, "018A0105a2f0b405"}
    };

    MockCanBusRouter router;
    router.setActualCanFrames(frames);
    QCOMPARE(router.actualCanFrames(), frames);
}

void TestConnectToMockCanBus::testExpectedCanIoConfiguration()
{
    auto frames = MockCanFrameCollection{
        MockCanFrame{MockCanFrame::Type::Outgoing, 0x185f0901U, "018A010102300405"},
        MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ed0301U, "018A0105a2f0b405"}
    };

    MockCanBusRouter router;
    router.setExpectedCanFrames(frames);
    QCOMPARE(router.expectedCanFrames(), frames);
}

QTEST_GUILESS_MAIN(TestConnectToMockCanBus)

#include "test_connect_to_mock_can_bus.moc"
