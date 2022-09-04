// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <memory>

#include <QString>

class TextFile
{
public:
    explicit TextFile(QString filePath);
    virtual ~TextFile();
    TextFile(const TextFile &file) = delete;
    TextFile &operator=(const TextFile &file) = delete;
    TextFile(TextFile &&file) = delete;
    TextFile &operator=(TextFile &&file) = delete;

    bool isAtEnd() const;
    QString readLine();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
