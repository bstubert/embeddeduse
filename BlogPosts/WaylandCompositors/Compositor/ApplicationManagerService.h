#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QHash>
#include <QObject>
#include <QRemoteObjectHost>
#include <QString>
class QProcess;

#include "rep_ApplicationManager_source.h"

class ApplicationManagerService : public ApplicationManagerSimpleSource
{
    Q_OBJECT

public:
    explicit ApplicationManagerService(QObject *parent = nullptr);

public slots:
    void openApplication(int appId) override;

private:
    QRemoteObjectHost m_sourceNode;

    struct AppInfo {
        QString m_command;
        QProcess *m_process;
    };
    QHash<int, AppInfo> m_appInfoColl;
};

#endif // APPLICATIONMANAGER_H
