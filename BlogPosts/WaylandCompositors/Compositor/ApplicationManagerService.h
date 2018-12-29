#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QProcess>
#include <QRemoteObjectHost>

#include "rep_ApplicationManagerService_source.h"

class ApplicationManagerService : public ApplicationManagerSimpleSource
{
    Q_OBJECT

public:
    explicit ApplicationManagerService(QObject *parent = nullptr);

public slots:
    void openApplication(int appId) override;

private:
    QRemoteObjectHost m_sourceNode;
    QProcess m_toolBarProcess;
};

#endif // APPLICATIONMANAGER_H
