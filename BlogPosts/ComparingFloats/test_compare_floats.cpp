#include <cmath>
#include <iostream>
#include <limits>

#include <QObject>
#include <QTest>
#include <QtGlobal>
#include <QtMath>

class TestCompareFloats : public QObject
{
    Q_OBJECT

private:
    float calculate(float start, float decrement, int count)
    {
        for (int i = 0; i < count; ++i)
            start -= decrement;
        return start;
    }

    bool equalWithOperator(float f1, float f2) const
    {
        return f1 == f2;
    }

    bool equalWithFixedEpsilon(float f1, float f2) const
    {
        return qAbs(f1 - f2) <= 1.0e-5f;
    }

    bool equalWithAdaptiveEpsilon(float f1, float f2) const
    {
        return qAbs(f1 - f2) <= 1.0e-5f * qMax(qAbs(f1), qAbs(f2));
    }

    bool floatCompare(float f1, float f2) const
    {
        static constexpr auto epsilon = 1.0e-05f;
        if (qAbs(f1 - f2) <= epsilon)
            return true;
        return qAbs(f1 - f2) <= epsilon * qMax(qAbs(f1), qAbs(f2));
    }

    bool qFloatCompare(float f1, float f2) const
    {
        if (qFuzzyIsNull(qAbs(f1 - f2)))
            return true;
        return qFuzzyCompare(f1, f2);
    }

private slots:
    void testEquality()
    {
        const auto total = 10000;
        auto count = 0;
        for (auto i = 0; i < total; ++i)
        {
            auto expected = (i / 10.0f);
            auto actual = calculate(9.0f + expected, 0.2f, 45);
            if (floatCompare(actual, expected))
            {
                ++count;
//                std::cout.precision(10);
//                std::cout << "expected = " << expected << ", actual = " << actual
//                          << ", error = " << (actual - expected) << std::endl;
            }
        }
        QCOMPARE(count, total);
    }

    void testIsZero()
    {
        auto actual = calculate(9.0f, 0.2f, 45);
        QVERIFY(floatCompare(actual, 0.0f));  // PASS
        QVERIFY(qFuzzyIsNull(actual));        // PASS
        QVERIFY(qFuzzyCompare(actual, 0.0f)); // FAIL
    }

private:
    void testIsNaN()
    {
        auto nan = 0.0f * std::numeric_limits<float>::infinity();
        QVERIFY(qIsNaN(nan));
        QVERIFY(std::numeric_limits<float>::has_quiet_NaN);
        QVERIFY(floatCompare(nan, std::numeric_limits<float>::quiet_NaN()));
    }

    void testIsInfinity()
    {
        auto plusInfinity = float(qPow(3.0, 800.0));
        QVERIFY(qIsInf(plusInfinity));
        QVERIFY(floatCompare(plusInfinity, std::numeric_limits<float>::infinity()));
        qDebug() << "plusInfinity = " << plusInfinity;

        auto minusInfinity = -float(qPow(3.0, 800.0));
        QVERIFY(qIsInf(minusInfinity));
        QVERIFY(floatCompare(minusInfinity, -std::numeric_limits<float>::infinity()));
        QVERIFY(minusInfinity == -std::numeric_limits<float>::infinity());
        qDebug() << "minusInfinity = " << minusInfinity;

        QVERIFY(floatCompare(plusInfinity, minusInfinity));
    }

private:
    void testSingleEquality()
    {
        auto expected = 0.0f;
        auto actual = -0.0f; //calculate(9.0f + expected, 0.2f, 45);
        auto ok = floatCompare(actual, expected);
        std::cout.precision(10);
        std::cout << "expected = " << expected << ", actual = " << actual
                  << ", error = " << (actual - expected) << std::endl;
        QVERIFY(ok);
    }
};


QTEST_GUILESS_MAIN(TestCompareFloats)

#include "test_compare_floats.moc"
