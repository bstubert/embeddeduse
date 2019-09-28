// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QtDebug>
#include <QtTest>

#include "j1939_frame.h"


class TestJ1939Frames : public QObject
{
    Q_OBJECT


private slots:

    void testPduFormat_data()
    {
        QTest::addColumn<quint16>("pduFormat");
        QTest::addColumn<quint32>("frameId");

        QTest::newRow("pf = 73") << quint16{73U} << 0x00490000U;
        QTest::newRow("pf = 498") << quint16{498U} << 0x01f20000U;
        QTest::newRow("pf = 0") << quint16{0U} << 0x00000000U;
        QTest::newRow("pf = 511") << quint16{511U} << 0x01ff0000U;
        QTest::newRow("pf = 512") << quint16{512U} << 0x01ff0000U;
        QTest::newRow("pf = 65535") << quint16{65535U} << 0x01ff0000U;
    }

    void testPduFormat()
    {
        QFETCH(quint16, pduFormat);
        QFETCH(quint32, frameId);

        auto frame{J1939Frame{quint8{0U}, pduFormat, quint8{0U}, quint8{0U}}};
        QCOMPARE(frame.pduFormat(), qBound(quint16{0}, pduFormat, quint16{511}));
        QCOMPARE(frame.frameId(), frameId);
        QVERIFY(frame.isValid());
    }

    void testPduSpecific_data()
    {
        QTest::addColumn<quint8>("pduSpecific");
        QTest::addColumn<quint32>("frameId");

        QTest::newRow("ps = 73") << quint8{73U} << 0x00004900U;
        QTest::newRow("ps = 241") << quint8{241U} << 0x0000f100U;
        QTest::newRow("ps = 0") << quint8{0U} << 0x00000000U;
        QTest::newRow("ps = 255") << quint8{255U} << 0x0000ff00U;
    }

    void testPduSpecific()
    {
        QFETCH(quint8, pduSpecific);
        QFETCH(quint32, frameId);

        auto frame{J1939Frame{quint8{0U}, quint8{0U}, pduSpecific, quint8{0U}}};
        QCOMPARE(frame.pduSpecific(), pduSpecific);
        QCOMPARE(frame.frameId(), frameId);
        QVERIFY(frame.isValid());
    }

    void testSourceAddress_data()
    {
        QTest::addColumn<quint8>("sourceAddress");
        QTest::addColumn<quint32>("frameId");

        QTest::newRow("sa = 73") << quint8{73U} << 0x00000049U;
        QTest::newRow("sa = 241") << quint8{241U} << 0x000000f1U;
        QTest::newRow("sa = 0") << quint8{0U} << 0x00000000U;
        QTest::newRow("sa = 255") << quint8{255U} << 0x000000ffU;
    }

    void testSourceAddress()
    {
        QFETCH(quint8, sourceAddress);
        QFETCH(quint32, frameId);

        auto frame{J1939Frame{quint8{0U}, quint8{0U}, quint8{0U}, sourceAddress}};
        QCOMPARE(frame.sourceAddress(), sourceAddress);
        QCOMPARE(frame.frameId(), frameId);
        QVERIFY(frame.isValid());
    }

    void testPriority_data()
    {
        QTest::addColumn<quint8>("priority");
        QTest::addColumn<quint32>("frameId");

        QTest::newRow("prio = 3") << quint8{3U} << 0x0C000000U;
        QTest::newRow("prio = 6") << quint8{6U} << 0x18000000U;
        QTest::newRow("prio = 0") << quint8{0U} << 0x00000000U;
        QTest::newRow("prio = 7") << quint8{7U} << 0x1C000000U;
        QTest::newRow("prio = 8") << quint8{7U} << 0x1C000000U;
        QTest::newRow("prio = 255") << quint8{7U} << 0x1C000000U;
    }

    void testPriority()
    {
        QFETCH(quint8, priority);
        QFETCH(quint32, frameId);

        auto frame{J1939Frame{priority, quint8{0U}, quint8{0U}, quint8{0U}}};
        QCOMPARE(frame.priority(), priority);
        QCOMPARE(frame.frameId(), frameId);
        QVERIFY(frame.isValid());
    }
};

QTEST_GUILESS_MAIN(TestJ1939Frames)

#include "test_j1939_frames.moc"
