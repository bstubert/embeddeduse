#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

class ApplicationId : public QObject
{
    Q_OBJECT

public:
    enum EnumType {
        TOOLBAR_APP = 1,
        ORANGE_APP,
        LIGHTGREEN_APP,
        BLACK_APP,
        CYAN_APP,
        MAGENTA_APP
    };
    Q_ENUM(EnumType)
};

#endif // APPLICATION_H
