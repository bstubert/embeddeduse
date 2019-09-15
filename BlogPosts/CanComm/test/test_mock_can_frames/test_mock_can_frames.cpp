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

class TestMockCanFrames : public QObject
{
    Q_OBJECT

private slots:
    void testMockCanFrameEquality_data();
    void testMockCanFrameEquality();
    void testMockCanFrameCollectionEquality_data();
    void testMockCanFrameCollectionEquality();
    void testDeviceErrors_data();
    void testDeviceErrors();
};

void TestMockCanFrames::testMockCanFrameEquality_data()
{
    QTest::addColumn<MockCanFrame>("lhs");
    QTest::addColumn<MockCanFrame>("rhs");
    QTest::addColumn<bool>("same");

    auto out1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000000000"};
    auto out2 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0301U, "018A010000000000"};
    auto out3 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000050000"};
    auto in1 = MockCanFrame{MockCanFrame::Type::Incoming, out1.toCanFrame()};

    QTest::newRow("same type, same frame") << in1 << in1 << true;
    QTest::newRow("same type, different frame ID") << out1 << out2 << false;
    QTest::newRow("same type, different payload") << out1 << out3 << false;
    QTest::newRow("different type, same frame") << out1 << in1 << false;
}

void TestMockCanFrames::testMockCanFrameEquality()
{
    QFETCH(MockCanFrame, lhs);
    QFETCH(MockCanFrame, rhs);
    QFETCH(bool, same);

    QCOMPARE((lhs == rhs), same);
}

void TestMockCanFrames::testMockCanFrameCollectionEquality_data()
{
    QTest::addColumn<MockCanFrameCollection>("lhs");
    QTest::addColumn<MockCanFrameCollection>("rhs");
    QTest::addColumn<bool>("same");

    auto out1 = MockCanFrame{MockCanFrame::Type::Outgoing, 0x18ef0201U, "018A010000000000"};
    auto ownOut1 = MockCanFrame{MockCanFrame::Type::Incoming, 0x18ef0201U, "018A010000000000"};

    QTest::newRow("same types, same frames")
            << MockCanFrameCollection{out1, out1}
            << MockCanFrameCollection{out1, out1}
            << true;
    QTest::newRow("different types, same frames")
            << MockCanFrameCollection{out1, ownOut1}
            << MockCanFrameCollection{out1, out1}
            << false;
    QTest::newRow("different size")
            << MockCanFrameCollection{out1}
            << MockCanFrameCollection{out1, ownOut1}
            << false;
    QTest::newRow("both empty")
            << MockCanFrameCollection{}
            << MockCanFrameCollection{}
            << true;
}

void TestMockCanFrames::testMockCanFrameCollectionEquality()
{
    QFETCH(MockCanFrameCollection, lhs);
    QFETCH(MockCanFrameCollection, rhs);
    QFETCH(bool, same);

    QCOMPARE((lhs == rhs), same);
}

void TestMockCanFrames::testDeviceErrors_data()
{
    QTest::addColumn<QCanBusDevice::CanBusError>("canError");
    QTest::addColumn<MockCanFrame::ErrorNo>("errorNo");
    QTest::addColumn<QString>("errorString");

    QTest::newRow("WriteError - NoBufferSpaceAvailable")
            << QCanBusDevice::CanBusError::WriteError
            << MockCanFrame::ErrorNo::NoBufferSpaceAvailable
            << QStringLiteral("No buffer space available");
    QTest::newRow("ConfigurationError - CannotFilterUnknownFrames")
            << QCanBusDevice::CanBusError::ConfigurationError
            << MockCanFrame::ErrorNo::CannotFilterUnknownFrames
            << QStringLiteral("Cannot set filter for frame type: unknown");
}

void TestMockCanFrames::testDeviceErrors()
{
    QFETCH(QCanBusDevice::CanBusError, canError);
    QFETCH(MockCanFrame::ErrorNo, errorNo);
    QFETCH(QString, errorString);

    auto expectedError = MockCanFrame{canError, errorNo};
    QCOMPARE(expectedError.type, MockCanFrame::Type::DeviceError);
    QVERIFY(!expectedError.toCanFrame().isValid());
    QCOMPARE(expectedError.deviceErrorString(), errorString);
    QCOMPARE(expectedError.deviceError(), canError);
}

QTEST_GUILESS_MAIN(TestMockCanFrames)

#include "test_mock_can_frames.moc"
