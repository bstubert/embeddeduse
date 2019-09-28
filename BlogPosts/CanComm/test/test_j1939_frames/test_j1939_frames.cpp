// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QtDebug>
#include <QtTest>


class TestJ1939Frames : public QObject
{
    Q_OBJECT


private slots:

    void testBroadcastFrame()
    {
        QVERIFY(false);
    }

};

QTEST_GUILESS_MAIN(TestJ1939Frames)

#include "test_j1939_frames.moc"
