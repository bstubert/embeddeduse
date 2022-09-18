// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#include <utility>

#include <QFile>
#include <QMap>
#include <QTextStream>

#include "package_info.h"

PackageInfo::PackageInfo()
{
}

PackageInfo::PackageInfo(QString name, QString licenseString,
                         QString version, QString revision)
    : m_isValid{true}
    , m_name{std::move(name)}
    , m_licenseString{std::move(licenseString)}
    , m_version{std::move(version)}
    , m_revision{std::move(revision)}
{
}

bool PackageInfo::isValid() const
{
    return m_isValid;
}

QString PackageInfo::name() const
{
    return m_name;
}

QString PackageInfo::licenseString() const
{
    return m_licenseString;
}

QString PackageInfo::version() const
{
    return m_version;
}

QString PackageInfo::revision() const
{
    return m_revision;
}
