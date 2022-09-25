// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QHash>
#include <QStringList>

#include "file_system_double.h"
#include "fake_text_file.h"

struct FakeTextFile::Impl
{
    Impl(QString filePath);
    ~Impl();
    QHash<QString, TextFileData> m_fileSystem = fileSystemDouble();

    bool m_isOpen{false};
    QStringList m_lines;
    int m_currentLine{0};
};

FakeTextFile::Impl::Impl(QString filePath)
{
    auto textFileData = m_fileSystem.value(filePath);
    m_isOpen = textFileData.m_isOpen;
    m_lines = textFileData.m_lines;
    if (!m_isOpen)
    {
        throw std::runtime_error(QString{"Cannot read file \'%1\'."}.arg(filePath).toStdString());
    }
}

FakeTextFile::Impl::~Impl()
{
}

FakeTextFile::FakeTextFile(QString filePath)
    : m_impl{new Impl{filePath}}
{
}

FakeTextFile::~FakeTextFile()
{
}

bool FakeTextFile::isAtEnd() const
{
    return m_impl->m_currentLine == m_impl->m_lines.count();
}

QString FakeTextFile::readLine()
{
    auto line = m_impl->m_lines[m_impl->m_currentLine];
    ++m_impl->m_currentLine;
    return line;
}

