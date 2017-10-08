#pragma once

#include <QObject>
#include <QTest>

class TestParameterisedSignals : public QObject
{
    Q_OBJECT

    void testSolution1();
    void testSolution2();

private slots:
    void testSolution3();
};

