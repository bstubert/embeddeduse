#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "qmlenums.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WarningLevel warningLevel READ warningLevel
               WRITE setWarningLevel NOTIFY warningLevelChanged)
public:
    MainModel(QObject *parent = nullptr)
        : QObject(parent)
        , m_warningLevel(WarningLevel::Warning)
    {}
    WarningLevel warningLevel() const {
        return m_warningLevel;
    }
    void setWarningLevel(WarningLevel warningLevel) {
        if (m_warningLevel != warningLevel) {
            m_warningLevel = warningLevel;
            emit warningLevelChanged();
        }
    }
signals:
    void warningLevelChanged();
private:
    WarningLevel m_warningLevel;
};

#endif // MAINMODEL_H
