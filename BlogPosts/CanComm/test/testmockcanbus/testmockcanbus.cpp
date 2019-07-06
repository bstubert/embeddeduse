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
    void testCreate();
};

void TestMockCanBus::initTestCase()
{
    QCoreApplication::addLibraryPath("../../");
}

void TestMockCanBus::testCreate()
{
    QString errorStr{"None"};
    auto device = QCanBus::instance()->createDevice("mockcan", "can0", &errorStr);
    qDebug() << "ERROR: " << errorStr;
    QVERIFY(device != nullptr);
}


QTEST_GUILESS_MAIN(TestMockCanBus)

#include "testmockcanbus.moc"
