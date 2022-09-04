// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QStringList>

#include "package_info.h"
#include "package_scanner.h"
#include "text_file.h"

PackageScanner::PackageScanner()
{
}

PackageScanner::~PackageScanner()
{
}

PackageInfo PackageScanner::readRecipeInfo(QString packageName)
{
    TextFile recipeInfo{QString{"files/%1/recipeinfo"}.arg(packageName)};
    QString licStr;
    QString version;
    QString revision;
    while (!recipeInfo.isAtEnd())
    {
        auto line = recipeInfo.readLine();
        if (line.startsWith("LICENSE"))
        {
            licStr = line.split(':')[1].trimmed();
        }
        else if (line.startsWith("PV"))
        {
            version = line.split(':')[1].trimmed();
        }
        else if (line.startsWith("PR"))
        {
            revision = line.split(':')[1].trimmed();
        }
    }
    return PackageInfo{packageName, licStr, version, revision};
}
