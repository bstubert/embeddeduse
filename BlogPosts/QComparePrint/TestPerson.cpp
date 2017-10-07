#include <QString>
#include "Person.h"
#include "TestPerson.h"

char *toString(const Person &p)
{
    return QTest::toString("Person(" + p.firstName() + ", " +
                           QString::number(p.age()) + ")");
}

void TestPerson::testEquality()
{
    Person p1("Alice", 42);
    Person p2("Bob", 37);
    QCOMPARE(p1, p2);
}

QTEST_GUILESS_MAIN(TestPerson)

/*
*** QCOMPARE output without toString(const Person &p)

FAIL!  : TestPerson::testEquality() Compared values are not the same
   Loc: [../QComparePrint/TestPerson.cpp(8)]

*** QCOMPARE output with toString(const Person &p)

FAIL!  : TestPerson::testEquality() Compared values are not the same
   Actual   (p1): "Person(Alice, 42)"
   Expected (p2): "Person(Bob, 37)"
   Loc: [../QComparePrint/TestPerson.cpp(16)]
 */
