// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QStringList>

#include "package_info.h"
#include "package_scanner.h"
#include "abstract_text_file.h"

PackageScanner::PackageScanner()
{
}

PackageScanner::~PackageScanner()
{
}

PackageInfo PackageScanner::readRecipeInfo(QString packageName, AbstractTextFile &recipeInfo)
{
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
    return {packageName, licStr, version, revision};
}
