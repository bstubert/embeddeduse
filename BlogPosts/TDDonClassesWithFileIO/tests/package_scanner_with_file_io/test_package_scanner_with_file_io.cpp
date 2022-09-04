// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QCoreApplication>
#include <QtTest>

class TestPackageScannerWithFileIO : public QObject
{
    Q_OBJECT

private slots:
    void testReadRecipeInfo();
};

void TestPackageScannerWithFileIO::testReadRecipeInfo()
{
    QVERIFY(true);
}

QTEST_GUILESS_MAIN(TestPackageScannerWithFileIO)

#include "test_package_scanner_with_file_io.moc"
