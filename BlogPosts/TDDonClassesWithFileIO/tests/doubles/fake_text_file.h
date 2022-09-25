// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>

#include <QString>

#include "abstract_text_file.h"

class FakeTextFile : public AbstractTextFile
{
public:
    explicit FakeTextFile(QString filePath);
    ~FakeTextFile() override;
    FakeTextFile(const FakeTextFile &file) = delete;
    FakeTextFile &operator=(const FakeTextFile &file) = delete;
    FakeTextFile(FakeTextFile &&file) = delete;
    FakeTextFile &operator=(FakeTextFile &&file) = delete;

    bool isAtEnd() const override;
    QString readLine() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
