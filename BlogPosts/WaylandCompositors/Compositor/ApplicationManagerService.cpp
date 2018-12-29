#include <QMetaObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtDebug>
#include "Application.h"
#include "ApplicationManagerService.h"

ApplicationManagerService::ApplicationManagerService(QObject *parent)
    : ApplicationManagerSimpleSource{parent}
    , m_sourceNode{QUrl{QStringLiteral("local:applicationService")}}
    , m_appInfoColl{
          {ApplicationId::TOOLBAR_APP, {"../ToolBarApp/ToolBarApp -platform wayland", nullptr}},
          {ApplicationId::ORANGE_APP, {"../ClientApp/ClientApp -platform wayland orange", nullptr}},
          {ApplicationId::LIGHTGREEN_APP, {"../ClientApp/ClientApp -platform wayland lightgreen", nullptr}},
          {ApplicationId::BLACK_APP, {"../ClientApp/ClientApp -platform wayland black", nullptr}},
          {ApplicationId::CYAN_APP, {"../ClientApp/ClientApp -platform wayland cyan", nullptr}},
          {ApplicationId::MAGENTA_APP, {"../ClientApp/ClientApp -platform wayland magenta", nullptr}},
      }
{
    m_sourceNode.enableRemoting(this);
    QMetaObject::invokeMethod(this, [this]() { openApplication(ApplicationId::TOOLBAR_APP); },
                              Qt::QueuedConnection);
}

void ApplicationManagerService::openApplication(int appId)
{
    auto &appInfo = m_appInfoColl[appId];
    if (appInfo.m_command.isEmpty()) {
        return;
    }
    if (appInfo.m_process == nullptr) {
        qDebug() << "@@@ ApplicationManagerService::openApplication/create: " << appId;
        appInfo.m_process = new QProcess{this};
        auto env = QProcessEnvironment::systemEnvironment();
        env.insert("QT_IVI_SURFACE_ID", QString::number(appId));
        appInfo.m_process->setProcessEnvironment(env);
        appInfo.m_process->start(appInfo.m_command);
    }
    else {
        qDebug() << "@@@ ApplicationManagerService::openApplication/raise: " << appId;
    }
}
