#ifndef APPLICATIONMANAGERCLIENT_H
#define APPLICATIONMANAGERCLIENT_H

#include <QObject>
#include <QRemoteObjectNode>
#include <QSharedPointer>

#include "rep_ApplicationManager_replica.h"

class ApplicationManagerClient : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationManagerClient(QObject *parent = nullptr);

public slots:
    void openApplication(int appId);

private:
    QRemoteObjectNode m_replicaNode;
    QSharedPointer<ApplicationManagerReplica> m_applicationManagerService;
};

#endif // APPLICATIONMANAGERCLIENT_H
