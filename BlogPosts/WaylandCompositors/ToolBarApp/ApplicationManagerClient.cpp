#include <QQmlEngine>
#include <QtDebug>
#include "Application.h"
#include "ApplicationManagerClient.h"

ApplicationManagerClient::ApplicationManagerClient(QObject *parent)
    : QObject{parent}
{
    qmlRegisterUncreatableType<ApplicationId>("EmbeddedUse.Application", 1, 0, "ApplicationId",
                                              "Creating ApplicationId in QML not allowed");
    m_replicaNode.connectToNode(QUrl{QStringLiteral("local:applicationService")});
    m_applicationManagerService.reset(m_replicaNode.acquire<ApplicationManagerReplica>());

}

void ApplicationManagerClient::openApplication(int appId)
{
    qDebug() << "### ApplicationManagerClient::openApplication: " << appId;
    m_applicationManagerService->openApplication(appId);
}
