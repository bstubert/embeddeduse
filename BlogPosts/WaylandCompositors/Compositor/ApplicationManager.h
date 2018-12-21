#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include "ApplicationSourceModel.h"
#include "TopApplicationModel.h"
#include "RunningApplicationModel.h"
class QQuickItem;

class ApplicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ApplicationSourceModel *allApps READ allApps CONSTANT)
    Q_PROPERTY(TopApplicationModel *topApps READ topApps CONSTANT)
    Q_PROPERTY(RunningApplicationModel *runningApps READ runningApps CONSTANT)

public:
    explicit ApplicationManager(QObject *parent = nullptr);
    ApplicationSourceModel *allApps() const;
    TopApplicationModel *topApps() const;
    RunningApplicationModel *runningApps() const;

public slots:
    void insertApplicationItem(int processId, QQuickItem *item);

private:
    ApplicationSourceModel *m_sourceModel;
    TopApplicationModel *m_topAppsModel;
    RunningApplicationModel *m_runningAppsModel;
};

#endif // APPLICATIONMANAGER_H
