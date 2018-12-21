#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject{parent}
    , m_sourceModel{new ApplicationSourceModel{this}}
    , m_topAppsModel{new TopApplicationModel{this}}
    , m_runningAppsModel{new RunningApplicationModel{this}}
{
    m_topAppsModel->setSourceModel(m_sourceModel);
    m_topAppsModel->setFilterRole(ApplicationSourceModel::ROLE_IS_TOP);

    m_runningAppsModel->setSourceModel(m_sourceModel);
    m_runningAppsModel->setFilterRole(ApplicationSourceModel::ROLE_IS_RUNNING);
}

ApplicationSourceModel *ApplicationManager::allApps() const
{
    return m_sourceModel;
}

TopApplicationModel *ApplicationManager::topApps() const
{
    return m_topAppsModel;
}

RunningApplicationModel *ApplicationManager::runningApps() const
{
    return m_runningAppsModel;
}

void ApplicationManager::insertApplicationItem(int processId, QQuickItem *item)
{
    m_sourceModel->insertApplicationItem(processId, item);
}
