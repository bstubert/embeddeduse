// Copyright (C) 2018 Burkhard Stubert

#include <QByteArray>
#include <QString>
#include <QtGlobal>
#include <QtTest>

class TestByteArrayToUint32 : public QObject
{
    Q_OBJECT

public:
    quint32 byteArrayToUint32(const QByteArray &bytes) const
    {
        auto count = bytes.size();
        if (count == 0 || count > 4) {
            return 0;
        }
        quint32 number = 0U;
        for (int i = 0; i < count; ++i) {
            auto b = static_cast<quint32>(bytes[count - 1 - i]);
            // Correct: auto b = static_cast<quint32>(bytes[count - 1 - i]);
            number += static_cast<quint32>(b << (8 * i));
        }
        return number;
    }

    quint32 castToUint32(const QByteArray &bytes) const
    {
        auto number = reinterpret_cast<const quint32 *>(bytes.data());
        return *number;
    }

private Q_SLOTS:
    void testByteArrayToUint32();
    void testCastToUint32();
};


void TestByteArrayToUint32::testByteArrayToUint32()
{
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("9020562f")), 0x9020562fU);
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("314922")), 0x314922U);
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("1540")), 0x1540U);
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("38")), 0x38U);
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("")), 0x0U);
    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("559020562f")), 0x0U);
    // The next two checks show the bug.
//    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("0180")), 0x180U);
//    QCOMPARE(byteArrayToUint32(QByteArray::fromHex("95")), 0x95U);
}

void TestByteArrayToUint32::testCastToUint32()
{
    QCOMPARE(castToUint32(QByteArray::fromHex("8001")), 0x180U);
    QCOMPARE(castToUint32(QByteArray::fromHex("0180")), 0x8001U);
    QCOMPARE(castToUint32(QByteArray::fromHex("224931")), 0x314922U);
}

QTEST_APPLESS_MAIN(TestByteArrayToUint32)

#include "TestByteArrayToUint32.moc"
