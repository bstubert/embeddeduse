#include <QtDebug>
#include "ApplicationManagerClient.h"

ApplicationManagerClient::ApplicationManagerClient(QObject *parent)
    : QObject{parent}
{
    m_replicaNode.connectToNode(QUrl{QStringLiteral("local:applicationService")});
    m_applicationManagerService.reset(m_replicaNode.acquire<ApplicationManagerReplica>());

}

void ApplicationManagerClient::openApplication(int appId)
{
    qDebug() << "### ApplicationManagerClient::openApplication: " << appId;
    m_applicationManagerService->openApplication(appId);
}
