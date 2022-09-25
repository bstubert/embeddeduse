// Copyright (C) 2021, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QString>

class PackageInfo;
class AbstractTextFile;

class PackageScanner
{
public:
    PackageScanner();
    ~PackageScanner();

    PackageInfo readRecipeInfo(QString packageName, AbstractTextFile &recipeInfo);
};
