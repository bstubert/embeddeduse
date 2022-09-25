// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QHash>
#include <QStringList>

#include "fake_text_file.h"

struct FakeTextFile::Impl
{
    bool m_isOpen{false};
    QStringList m_lines;
    int m_currentLine{0};
};

FakeTextFile::FakeTextFile(QString filePath, bool isOpen, QStringList lines)
    : m_impl{new Impl{isOpen, lines, 0}}
{
    if (!m_impl->m_isOpen)
    {
        throw std::runtime_error(QString{"Cannot read file \'%1\'."}.arg(filePath).toStdString());
    }
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

