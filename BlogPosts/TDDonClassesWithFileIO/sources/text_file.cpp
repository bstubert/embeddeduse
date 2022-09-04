// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <stdexcept>

#include <QFile>
#include <QTextStream>

#include "text_file.h"

struct TextFile::Impl
{
    Impl(QString filePath);
    ~Impl();
    QFile m_file;
    QTextStream m_inStream;
};

TextFile::Impl::Impl(QString filePath)
    : m_file{filePath}
{
    if (!m_file.open(QFile::ReadOnly))
    {
        throw std::runtime_error(QString{"Cannot read file \'%1\'."}.arg(filePath).toStdString());
    }
    m_inStream.setDevice(&m_file);
}

TextFile::Impl::~Impl()
{
    m_file.close();
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
    return m_impl->m_inStream.atEnd();
}

QString TextFile::readLine()
{
    return m_impl->m_inStream.readLine();
}

