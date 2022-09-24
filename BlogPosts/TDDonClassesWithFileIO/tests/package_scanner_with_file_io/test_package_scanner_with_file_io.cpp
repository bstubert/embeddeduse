// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QString>
#include <QtTest>

#include "package_info.h"
#include "package_scanner.h"
#include "text_file.h"

class TestPackageScannerWithFileIO : public QObject
{
    Q_OBJECT

private slots:
    void testReadRecipeInfo();
};

void TestPackageScannerWithFileIO::testReadRecipeInfo()
{
    PackageScanner scanner;
    TextFile recipeInfo{u"files/libffi/recipeinfo"_qs};
    auto package = scanner.readRecipeInfo(u"libffi"_qs, recipeInfo);
    QCOMPARE(package.name(), u"libffi"_qs);
    QCOMPARE(package.licenseString(), u"MIT"_qs);
    QCOMPARE(package.version(), u"3.2.1"_qs);
    QCOMPARE(package.revision(), u"r0"_qs);
}

QTEST_GUILESS_MAIN(TestPackageScannerWithFileIO)

#include "test_package_scanner_with_file_io.moc"
