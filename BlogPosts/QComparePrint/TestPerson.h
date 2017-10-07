#pragma once

#include <QObject>
#include <QTest>

class TestPerson : public QObject
{
    Q_OBJECT

private slots:
    void testEquality();
};
