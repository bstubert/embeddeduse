#pragma once

#include <QHash>
#include <QStringList>

struct TextFileData
{
    bool m_isOpen{false};
    QStringList m_lines;
};

inline static QHash<QString, TextFileData> fileSystemDouble()
{
    return QHash<QString, TextFileData>{
        {u"files/libffi/recipeinfo"_qs,
            {true, {u"LICENSE: MIT"_qs,
                    u"PR: r0"_qs,
                    u"PV: 3.2.1"_qs}}},
        {u"files/cannot-open/recipeinfo"_qs,
            {false, {}}},
        {u"files/missing-license/recipeinfo"_qs,
            {true, {u"LICENSE: "_qs,
                    u"PR: r4"_qs,
                    u"PV: 6.3.2"_qs}}}
    };
}


