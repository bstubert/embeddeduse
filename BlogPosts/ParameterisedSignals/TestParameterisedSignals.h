#pragma once

#include <QObject>
#include <QTest>

class TestParameterisedSignals : public QObject
{
    Q_OBJECT

    void testSolution1();
private slots:
    void testSolution2();
};

