#ifndef QMLENUMS_H
#define QMLENUMS_H

#include <QObject>
#include <QtGlobal>

class WarningLevel : public QObject
{
    Q_OBJECT
public:
    enum class Enum : quint8 {
        Error,
        Warning,
        Info,
        Debug
    };
    Q_ENUM(Enum)
};

#endif // QMLENUMS_H
