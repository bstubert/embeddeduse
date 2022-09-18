// Copyright (C) 2022, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QString>

class PackageInfo
{
public:
    PackageInfo();
    PackageInfo(QString name, QString licenseString = QString{},
                QString version = QString{}, QString revision = QString{});
    bool isValid() const;
    QString name() const;
    QString licenseString() const;
    QString version() const;
    QString revision() const;

private:
    bool m_isValid{false};
    QString m_name;
    QString m_licenseString;
    QString m_version;
    QString m_revision;
};
