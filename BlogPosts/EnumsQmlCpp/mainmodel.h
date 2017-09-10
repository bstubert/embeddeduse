#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QtDebug>
#include "qmlenums.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WarningLevel::Enum warningLevel READ warningLevel
               WRITE setWarningLevel NOTIFY warningLevelChanged)
public:
    MainModel(QObject *parent = nullptr)
        : QObject(parent)
        , m_warningLevel(WarningLevel::Enum::Warning)
    {}
    WarningLevel::Enum warningLevel() const {
        return m_warningLevel;
    }
    void setWarningLevel(WarningLevel::Enum warningLevel) {
        if (m_warningLevel != warningLevel) {
            m_warningLevel = warningLevel;
            emit warningLevelChanged();
        }
    }
signals:
    void warningLevelChanged();
private:
    WarningLevel::Enum m_warningLevel;
};

#endif // MAINMODEL_H
