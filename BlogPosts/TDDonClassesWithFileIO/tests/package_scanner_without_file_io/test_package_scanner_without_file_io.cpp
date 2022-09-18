// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QString>
#include <QtTest>

#include "package_info.h"
#include "package_scanner.h"

class TestPackageScannerWithoutFileIO : public QObject
{
    Q_OBJECT

private slots:
    void testReadRecipeInfo();
    void testCannotOpenRecipeInfo();
};

void TestPackageScannerWithoutFileIO::testReadRecipeInfo()
{
    PackageScanner scanner;
    auto package = scanner.readRecipeInfo(u"libffi"_qs);
    QVERIFY(package.isValid());
    QCOMPARE(package.name(), u"libffi"_qs);
    QCOMPARE(package.licenseString(), u"MIT"_qs);
    QCOMPARE(package.version(), u"3.2.1"_qs);
    QCOMPARE(package.revision(), u"r0"_qs);
}

void TestPackageScannerWithoutFileIO::testCannotOpenRecipeInfo()
{
    PackageScanner scanner;
    auto package = scanner.readRecipeInfo(u"cannot-open"_qs);
    QVERIFY(!package.isValid());
}

QTEST_GUILESS_MAIN(TestPackageScannerWithoutFileIO)

#include "test_package_scanner_without_file_io.moc"
