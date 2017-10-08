#include "Receiver1.h"
#include "Receiver2.h"
#include "Receiver3.h"
#include "Sender1.h"
#include "Sender2.h"
#include "Sender3.h"
#include "TestParameterisedSignals.h"

void TestParameterisedSignals::testSolution1()
{
    const int messageCount(5000000);
    Sender1 sender(messageCount);
    Receiver1 receiver1(0x13);
    Receiver1 receiver2(0x21);
    Receiver1 receiver3(0x03);
    connect(&sender, &Sender1::newMessage, &receiver1, &Receiver1::onNewMessage);
    connect(&sender, &Sender1::newMessage, &receiver2, &Receiver1::onNewMessage);
    connect(&sender, &Sender1::newMessage, &receiver3, &Receiver1::onNewMessage);
    QBENCHMARK_ONCE {
        sender.sendMessages();
    }
    QCOMPARE(receiver1.relevantMessageCount(), messageCount);
    QCOMPARE(receiver2.relevantMessageCount(), messageCount);
    QCOMPARE(receiver3.relevantMessageCount(), messageCount);
}

void TestParameterisedSignals::testSolution2()
{
    const int messageCount(5000000);
    Sender2 sender(messageCount);
    Receiver2 receiver1(0x13);
    Receiver2 receiver2(0x21);
    Receiver2 receiver3(0x03);
    connect(&sender, &Sender2::newMessage1, &receiver1, &Receiver2::onNewMessage);
    connect(&sender, &Sender2::newMessage2, &receiver2, &Receiver2::onNewMessage);
    connect(&sender, &Sender2::newMessage3, &receiver3, &Receiver2::onNewMessage);
    QBENCHMARK_ONCE {
        sender.sendMessages();
    }
    QCOMPARE(receiver1.relevantMessageCount(), messageCount);
    QCOMPARE(receiver2.relevantMessageCount(), messageCount);
    QCOMPARE(receiver3.relevantMessageCount(), messageCount);
}

void TestParameterisedSignals::testSolution3()
{
    const int messageCount(5000000);
    Sender3 sender(messageCount);
    Receiver3 receiver1(0x13);
    Receiver3 receiver2(0x21);
    Receiver3 receiver3(0x03);
    sender.connectReceiver(&receiver1, "onNewMessage(QCanBusFrame)", 0x13);
    sender.connectReceiver(&receiver2, "onNewMessage(QCanBusFrame)", 0x21);
    sender.connectReceiver(&receiver3, "onNewMessage(QCanBusFrame)", 0x03);

    QBENCHMARK_ONCE {
        sender.sendMessages();
    }
    QCOMPARE(receiver1.relevantMessageCount(), messageCount);
    QCOMPARE(receiver2.relevantMessageCount(), messageCount);
    QCOMPARE(receiver3.relevantMessageCount(), messageCount);
}

QTEST_GUILESS_MAIN(TestParameterisedSignals)
