// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QHash>
#include <QStringList>

#include "file_system_double.h"
#include "text_file.h"

struct TextFile::Impl
{
    Impl(QString filePath);
    ~Impl();
    QHash<QString, TextFileData> m_fileSystem = fileSystemDouble();

    bool m_isOpen{false};
    QStringList m_lines;
    int m_currentLine{0};
};

TextFile::Impl::Impl(QString filePath)
{
    auto textFileData = m_fileSystem.value(filePath);
    m_isOpen = textFileData.m_isOpen;
    m_lines = textFileData.m_lines;
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

