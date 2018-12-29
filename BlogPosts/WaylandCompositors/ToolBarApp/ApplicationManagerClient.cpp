#include <QtDebug>
#include "ApplicationManagerClient.h"

ApplicationManagerClient::ApplicationManagerClient(
        QSharedPointer<ApplicationServiceReplica> replica, QObject *parent)
    : QObject{parent}
    , m_applicationManagerService{replica}
{
}

void ApplicationManagerClient::openApplication(int appId)
{
    qDebug() << "### ApplicationManagerClient::openApplication: " << appId;
    m_applicationManagerService->openApplication(appId);
}
