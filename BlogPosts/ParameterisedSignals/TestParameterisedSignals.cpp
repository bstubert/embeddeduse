#include "Receiver1.h"
#include "Sender1.h"
#include "TestParameterisedSignals.h"

void TestParameterisedSignals::testSolution1()
{
    Sender1 sender1(5);
    Receiver1 receiver1(0x13);
    Receiver1 receiver2(0x21);
    Receiver1 receiver3(0x03);
    connect(&sender1, &Sender1::newMessage, &receiver1, &Receiver1::onNewMessage);
    connect(&sender1, &Sender1::newMessage, &receiver2, &Receiver1::onNewMessage);
    connect(&sender1, &Sender1::newMessage, &receiver3, &Receiver1::onNewMessage);
    sender1.sendMessages();
    QCOMPARE(receiver1.relevantMessageCount(), 5);
    QCOMPARE(receiver2.relevantMessageCount(), 5);
    QCOMPARE(receiver3.relevantMessageCount(), 5);
}

QTEST_GUILESS_MAIN(TestParameterisedSignals)
