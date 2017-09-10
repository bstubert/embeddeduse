#ifndef QMLENUMS_H
#define QMLENUMS_H

#include <QObject>

class WarningLevel : public QObject
{
    Q_OBJECT
public:
    enum Enum {
        Error,
        Warning,
        Info,
        Debug
    };
    Q_ENUM(Enum)
};

#endif // QMLENUMS_H
