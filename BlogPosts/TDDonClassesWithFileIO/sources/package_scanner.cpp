// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <QFile>
#include <QtDebug>
#include <QTextStream>

#include "package_info.h"
#include "package_scanner.h"

PackageScanner::PackageScanner()
{
}

PackageScanner::~PackageScanner()
{
}

PackageInfo PackageScanner::readRecipeInfo(QString packageName)
{
    QFile recipeInfo{QString{"files/%1/recipeinfo"}.arg(packageName)};
    if (!recipeInfo.open(QFile::ReadOnly))
    {
        qWarning().noquote().nospace()
                << "Cannot read file \'" << recipeInfo.fileName() << "\'.";
        return {};
    }
    QString licStr;
    QString version;
    QString revision;
    QTextStream is{&recipeInfo};
    while (!is.atEnd())
    {
        auto line = is.readLine();
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
