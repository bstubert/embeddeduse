// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QByteArray>
#include <QtDebug>
#include <QtTest>

#include "j1939_broadcast_frames.h"
#include "j1939_frame.h"


class TestJ1939Frames : public QObject
{
    Q_OBJECT


private slots:

    void testPduFormat_data()
    {
        QTest::addColumn<quint16>("pduFormat");
        QTest::addColumn<bool>("isValid");
        QTest::addColumn<quint32>("frameId");

        QTest::newRow("pf = 73") << quint16{73U} << true << 0x00490000U;
        QTest::newRow("pf = 498") << quint16{498U} << true << 0x01f20000U;
        QTest::newRow("pf = 0") << quint16{0U} << true << 0U;
        QTest::newRow("pf = 511") << quint16{511U} << true << 0x01ff0000U;
        QTest::newRow("pf = 512") << quint16{512U} << false << 0U;
        QTest::newRow("pf = 65535") << quint16{65535U} << false << 0U;
    }

    void testPduFormat()
    {
        QFETCH(quint16, pduFormat);
        QFETCH(bool, isValid);
        QFETCH(quint32, frameId);

        auto frame{J1939Frame{quint8{0U}, pduFormat, quint8{0U}, quint8{0U}, {}}};
        QCOMPARE(frame.isValid(), isValid);
        if (isValid)
        {
            QCOMPARE(frame.pduFormat(), pduFormat);
            QCOMPARE(frame.frameId(), frameId);
        }
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

        auto frame{J1939Frame{quint8{0U}, quint8{0U}, pduSpecific, quint8{0U}, {}}};
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

        auto frame{J1939Frame{quint8{0U}, quint8{0U}, quint8{0U}, sourceAddress, {}}};
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

        auto frame{J1939Frame{priority, quint8{0U}, quint8{0U}, quint8{0U}, {}}};
        QCOMPARE(frame.priority(), priority);
        QCOMPARE(frame.frameId(), frameId);
        QVERIFY(frame.isValid());
    }

    void testPeerToPeer_data()
    {
        QTest::addColumn<quint16>("pduFormat");
        QTest::addColumn<bool>("isPeerToPeer");

        QTest::newRow("pf = 0") << quint16{0x00U} << true;
        QTest::newRow("pf = 239") << quint16{0xefU} << true;
        QTest::newRow("pf = 240") << quint16{0xf0U} << false;
        QTest::newRow("pf = 255") << quint16{0xffU} << false;
        QTest::newRow("pf = 256") << quint16{0x100U} << true;
        QTest::newRow("pf = 495") << quint16{0x1efU} << true;
        QTest::newRow("pf = 496") << quint16{0x1f0U} << false;
        QTest::newRow("pf = 511") << quint16{0x1ffU} << false;
    }

    void testPeerToPeer()
    {
        QFETCH(quint16, pduFormat);
        QFETCH(bool, isPeerToPeer);

        auto frame{J1939Frame{6U, pduFormat, 0x28U, 0x02U, {}}};
        QCOMPARE(frame.isPeerToPeer(), isPeerToPeer);
    }

    void testSimplePayload()
    {
        auto payload{QByteArray{8, 1}};
        auto frame{J1939Frame{6U, 0xE0U, 0x28U, 0x02U, payload}};
        QCOMPARE(frame.payload(), payload);
    }

    // TODO:
    // * Try negative numbers for fields.
    void testEncodePayload()
    {
        auto eec1{EEC1Frame{{4U, 10U, 80U, 56U, 5489U, 13U, 3U, 0U, 30U}}};
        QCOMPARE(eec1.frameId(), 0x0cf00400U);
        QCOMPARE(eec1.payload().toHex(), QByteArray("a4503871150d031e"));
    }

    // The second payload argument 0x33 (51) cannot be represented by 4 bits. It is truncated to
    // 4 bits, which yields 0x03. Similarly, the last argument 0x15d (349) is to big for 8 bits.
    // It is truncated to 0x5d.
    void testEncodePayloadWithOutOfRangeValues()
    {
        auto eec1{EEC1Frame{{4U, 51U, 80U, 56U, 5489U, 13U, 3U, 0U, 349U}}};
        QCOMPARE(eec1.frameId(), 0x0cf00400U);
        QCOMPARE(eec1.payload().toHex(), QByteArray("34503871150d035d"));
    }
};

QTEST_GUILESS_MAIN(TestJ1939Frames)

#include "test_j1939_frames.moc"
