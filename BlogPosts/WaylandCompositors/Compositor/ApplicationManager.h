#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include "ApplicationSourceModel.h"
#include "TopApplicationModel.h"
class QQuickItem;

class ApplicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ApplicationSourceModel *allApps READ allApps CONSTANT)
    Q_PROPERTY(TopApplicationModel *topApps READ topApps CONSTANT)

public:
    explicit ApplicationManager(QObject *parent = nullptr);
    ApplicationSourceModel *allApps() const;
    TopApplicationModel *topApps() const;

public slots:
    void insertApplicationItem(int processId, QQuickItem *item);

private:
    ApplicationSourceModel *m_sourceModel;
    TopApplicationModel *m_topAppsModel;
};

#endif // APPLICATIONMANAGER_H
