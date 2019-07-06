// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QCoreApplication>
#include <QObject>
#include <QtDebug>
#include <QtTest>

#include <QCanBus>

class TestMockCanBus : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateDevice_data();
    void testCreateDevice();
};

void TestMockCanBus::initTestCase()
{
    // The loader for the CAN bus plugins adds /canbus to each library path and looks for
    // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
    // is called "canbus".
    QCoreApplication::addLibraryPath("../../");
}

void TestMockCanBus::testCreateDevice_data()
{
    QTest::addColumn<QString>("plugin");
    QTest::addColumn<QString>("interface");
    QTest::addColumn<bool>("isNull");
    QTest::addColumn<QString>("errorStr");

    QTest::newRow("mockcan/can0") << QString{"mockcan"} << QString{"can0"} << false
                                  << QString{};
    QTest::newRow("muppetcan/can0") << QString{"muppetcan"} << QString{"can0"} << true
                                  << QString{"No such plugin: \'muppetcan\'"};
    QTest::newRow("mockcan/sky9") << QString{"mockcan"} << QString{"sky9"} << false
                                  << QString{};
    QTest::newRow("muppetcan/sky9") << QString{"muppetcan"} << QString{"sky9"} << true
                                  << QString{"No such plugin: \'muppetcan\'"};
}

// QCanBus::createDevice() returns nullptr and an error message, if the plugin does not exist.
// It returns a non-null QCanBusDevice, if the plugin exists. Whether the CAN interface exists,
// does not matter. This is counterintuitive, but it is exactly how QCanBus::createDevice is
// implemented.
void TestMockCanBus::testCreateDevice()
{
    QFETCH(QString, plugin);
    QFETCH(QString, interface);
    QFETCH(bool, isNull);
    QFETCH(QString, errorStr);

    QString lastErrorStr;
    auto device = QCanBus::instance()->createDevice(plugin, interface, &lastErrorStr);
    QCOMPARE(device == nullptr, isNull);
    QCOMPARE(lastErrorStr, errorStr);
}


QTEST_GUILESS_MAIN(TestMockCanBus)

#include "testmockcanbus.moc"
