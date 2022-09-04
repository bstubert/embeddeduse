// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QString>
#include <QtTest>

#include "package_info.h"
#include "package_scanner.h"

class TestPackageScannerWithFileIO : public QObject
{
    Q_OBJECT

private slots:
    void testReadRecipeInfo();
};

void TestPackageScannerWithFileIO::testReadRecipeInfo()
{
    PackageScanner scanner;
    auto package = scanner.readRecipeInfo("libffi");
    QCOMPARE(package.name(), "libffi");
    QCOMPARE(package.licenseString(), "MIT");
    QCOMPARE(package.version(), "3.2.1");
    QCOMPARE(package.revision(), "r0");
}

QTEST_GUILESS_MAIN(TestPackageScannerWithFileIO)

#include "test_package_scanner_with_file_io.moc"
