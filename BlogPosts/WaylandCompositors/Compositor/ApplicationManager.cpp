#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject{parent}
    , m_sourceModel{new ApplicationSourceModel{this}}
{
}

ApplicationSourceModel *ApplicationManager::allApps() const
{
    return m_sourceModel;
}

void ApplicationManager::insertApplicationItem(int processId, QQuickItem *item)
{
    m_sourceModel->insertApplicationItem(processId, item);
}
