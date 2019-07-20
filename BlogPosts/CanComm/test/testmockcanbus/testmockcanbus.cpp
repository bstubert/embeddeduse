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
    void testWriteFrame();

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
    QTest::addColumn<QList<QCanBusFrame>>("frames");

    QTest::newRow("0 frames") << QList<QCanBusFrame>{};
    QTest::newRow("1 frame") << QList<QCanBusFrame>{
        QCanBusFrame{0x18ef0201U, QByteArray::fromHex("018A010000000000")}
    };
    QTest::newRow("2 frames") << QList<QCanBusFrame>{
        QCanBusFrame{0x185f0901U, QByteArray::fromHex("018A010102300405")},
        QCanBusFrame{0x18ed0301U, QByteArray::fromHex("018A0105a2f0b405")}
    };
}

void TestMockCanBus::testActualCanIoConfiguration()
{
    QFETCH(QList<QCanBusFrame>, frames);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QVERIFY(CanUtils::actualCanIo(device.get()).isEmpty());

    CanUtils::setActualCanIo(device.get(), frames);
    QCOMPARE(CanUtils::actualCanIo(device.get()), frames);
}

void TestMockCanBus::testExpectedCanIoConfiguration_data()
{
    QTest::addColumn<QList<QCanBusFrame>>("frames");

    QTest::newRow("0 frames") << QList<QCanBusFrame>{};
    QTest::newRow("1 frame") << QList<QCanBusFrame>{
        QCanBusFrame{0x18ef0201U, QByteArray::fromHex("018A010000000000")}
    };
    QTest::newRow("2 frames") << QList<QCanBusFrame>{
        QCanBusFrame{0x185f0901U, QByteArray::fromHex("018A010102300405")},
        QCanBusFrame{0x18ed0301U, QByteArray::fromHex("018A0105a2f0b405")}
    };
}

void TestMockCanBus::testExpectedCanIoConfiguration()
{
    QFETCH(QList<QCanBusFrame>, frames);

    QString currentErrorStr;
    std::unique_ptr<QCanBusDevice> device{
        QCanBus::instance()->createDevice("mockcan", "mcan1", &currentErrorStr)};

    QVERIFY(CanUtils::expectedCanIo(device.get()).isEmpty());

    CanUtils::setExpectedCanIo(device.get(), frames);
    QCOMPARE(CanUtils::expectedCanIo(device.get()), frames);
}
void TestMockCanBus::testWriteFrame()
{
    std::unique_ptr<QCanBusDevice> device{createAndConnectDevice("mcan0")};
    QSignalSpy spy{device.get(), &QCanBusDevice::framesWritten};
    auto frames = QList<QCanBusFrame>{
            QCanBusFrame{0x18ef0201U, QByteArray::fromHex("018A010000000000")},
            QCanBusFrame{0x18ef0301U, QByteArray::fromHex("0195020000000000")},
    };
    for (const auto &frame : frames) {
        auto ok = device->writeFrame(frame);
        QVERIFY(ok);
    }
    QCOMPARE(spy.count(), frames.size());
    QCOMPARE(CanUtils::actualCanIo(device.get()), frames);
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
