#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include "ApplicationSourceModel.h"
class QQuickItem;

class ApplicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ApplicationSourceModel *allApps READ allApps CONSTANT)

public:
    explicit ApplicationManager(QObject *parent = nullptr);
    ApplicationSourceModel *allApps() const;

public slots:
    void insertApplicationItem(int processId, QQuickItem *item);

private:
    ApplicationSourceModel *m_sourceModel;
};

#endif // APPLICATIONMANAGER_H
