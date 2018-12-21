#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject{parent}
    , m_sourceModel{new ApplicationSourceModel{this}}
    , m_topAppsModel{new TopApplicationModel{this}}
{
    m_topAppsModel->setSourceModel(m_sourceModel);
    m_topAppsModel->setFilterRole(ApplicationSourceModel::ROLE_IS_TOP);
}

ApplicationSourceModel *ApplicationManager::allApps() const
{
    return m_sourceModel;
}

TopApplicationModel *ApplicationManager::topApps() const
{
    return m_topAppsModel;
}

void ApplicationManager::insertApplicationItem(int processId, QQuickItem *item)
{
    m_sourceModel->insertApplicationItem(processId, item);
}
