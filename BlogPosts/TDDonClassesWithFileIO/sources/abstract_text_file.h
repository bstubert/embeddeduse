// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QString>

class AbstractTextFile
{
public:
    virtual ~AbstractTextFile() = default;

    virtual bool isAtEnd() const = 0;
    virtual QString readLine() = 0;
};
