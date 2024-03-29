// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QString>
#include <QtTest>

#include "package_info.h"
#include "package_scanner.h"
#include "fake_text_file.h"

class TestPackageScannerWithoutFileIO : public QObject
{
    Q_OBJECT

private slots:
    void testReadRecipeInfo();
    void testCannotOpenRecipeInfo();
    void testLicenseMissingInRecipeInfo();
};

void TestPackageScannerWithoutFileIO::testReadRecipeInfo()
{
    PackageScanner scanner;
    FakeTextFile recipeInfo{
        u"files/libffi/recipeinfo"_qs, true,
        {u"LICENSE: MIT"_qs,
         u"PR: r0"_qs,
         u"PV: 3.2.1"_qs}
    };
    auto package = scanner.readRecipeInfo(u"libffi"_qs, recipeInfo);
    QCOMPARE(package.name(), u"libffi"_qs);
    QCOMPARE(package.licenseString(), u"MIT"_qs);
    QCOMPARE(package.version(), u"3.2.1"_qs);
    QCOMPARE(package.revision(), u"r0"_qs);
}

void TestPackageScannerWithoutFileIO::testCannotOpenRecipeInfo()
{
    PackageScanner scanner;
    QVERIFY_EXCEPTION_THROWN(
        FakeTextFile recipeInfo(u"files/cannot-open/recipeinfo"_qs, false, {});
        auto package = scanner.readRecipeInfo(u"cannot-open"_qs, recipeInfo),
        std::runtime_error
    );
}

void TestPackageScannerWithoutFileIO::testLicenseMissingInRecipeInfo()
{
    PackageScanner scanner;
    FakeTextFile recipeInfo{
        u"files/missing-license/recipeinfo"_qs, true,
        {u"LICENSE: "_qs,
         u"PR: r4"_qs,
         u"PV: 6.3.2"_qs}
    };
    auto package = scanner.readRecipeInfo(u"missing-license"_qs, recipeInfo);
    QCOMPARE(package.name(), u"missing-license"_qs);
    QVERIFY(package.licenseString().isEmpty());
}

QTEST_GUILESS_MAIN(TestPackageScannerWithoutFileIO)

#include "test_package_scanner_without_file_io.moc"
