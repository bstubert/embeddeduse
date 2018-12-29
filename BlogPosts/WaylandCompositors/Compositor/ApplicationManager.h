#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QProcess>
#include <QRemoteObjectHost>

#include "rep_ApplicationService_source.h"

class ApplicationManager : public ApplicationServiceSimpleSource
{
    Q_OBJECT

public:
    explicit ApplicationManager(QObject *parent = nullptr);

public slots:
    void openApplication(int appId) override;

private:
    QRemoteObjectHost m_sourceNode;
    QProcess m_toolBarProcess;
};

#endif // APPLICATIONMANAGER_H
