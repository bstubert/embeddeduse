// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QStringList>

#include "text_file.h"

struct TextFile::Impl
{
    Impl(QString filePath);
    ~Impl();
    bool m_isOpen{true};
    QStringList m_lines{
        "LICENSE: MIT",
        "PR: r0",
        "PV: 3.2.1"
    };
    int m_currentLine{0};
};

TextFile::Impl::Impl(QString filePath)
{
    if (!m_isOpen)
    {
        throw std::runtime_error(QString{"Cannot read file \'%1\'."}.arg(filePath).toStdString());
    }
}

TextFile::Impl::~Impl()
{
}

TextFile::TextFile(QString filePath)
    : m_impl{new Impl{filePath}}
{
}

TextFile::~TextFile()
{
}

bool TextFile::isAtEnd() const
{
    return m_impl->m_currentLine == m_impl->m_lines.count();
}

QString TextFile::readLine()
{
    auto line = m_impl->m_lines[m_impl->m_currentLine];
    ++m_impl->m_currentLine;
    return line;
}

