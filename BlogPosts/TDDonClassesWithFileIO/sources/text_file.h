// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>

#include <QString>

#include "abstract_text_file.h"

class TextFile : public AbstractTextFile
{
public:
    explicit TextFile(QString filePath);
    ~TextFile() override;
    TextFile(const TextFile &file) = delete;
    TextFile &operator=(const TextFile &file) = delete;
    TextFile(TextFile &&file) = delete;
    TextFile &operator=(TextFile &&file) = delete;

    bool isAtEnd() const override;
    QString readLine() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
