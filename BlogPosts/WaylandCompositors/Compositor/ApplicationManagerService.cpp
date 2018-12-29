#include <QMetaObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtDebug>
#include "Application.h"
#include "ApplicationManagerService.h"

ApplicationManagerService::ApplicationManagerService(QObject *parent)
    : ApplicationManagerSimpleSource{parent}
    , m_sourceNode{QUrl{QStringLiteral("local:applicationService")}}
{
    m_sourceNode.enableRemoting(this);
    QMetaObject::invokeMethod(this, [this]() { openApplication(ApplicationId::TOOLBAR_APP); },
                              Qt::QueuedConnection);
}

void ApplicationManagerService::openApplication(int appId)
{
    qDebug() << "### openApplication: " << appId;
    if (appId != ApplicationId::TOOLBAR_APP) {
        return;
    }
    auto env = QProcessEnvironment::systemEnvironment();
    env.insert("QT_IVI_SURFACE_ID", QString::number(appId));
    m_toolBarProcess.setProcessEnvironment(env);
    m_toolBarProcess.start("../ToolBarApp/ToolBarApp -platform wayland");
}
