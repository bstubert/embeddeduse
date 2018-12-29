#ifndef APPLICATIONMANAGERCLIENT_H
#define APPLICATIONMANAGERCLIENT_H

#include <QObject>
#include <QSharedPointer>

#include "rep_ApplicationService_replica.h"

class ApplicationManagerClient : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationManagerClient(QSharedPointer<ApplicationServiceReplica> replica,
                                      QObject *parent = nullptr);

public slots:
    void openApplication(int appId);

private:
    QSharedPointer<ApplicationServiceReplica> m_applicationManagerService;
};

#endif // APPLICATIONMANAGERCLIENT_H
