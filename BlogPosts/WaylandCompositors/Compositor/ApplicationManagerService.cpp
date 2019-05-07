#include <QMetaObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QQmlEngine>
#include <QtDebug>
#include "Application.h"
#include "ApplicationManagerService.h"

ApplicationManagerService::ApplicationManagerService(QObject *parent)
    : ApplicationManagerSimpleSource{parent}
    , m_sourceNode{QUrl{QStringLiteral("local:applicationService")}}
    // Platform "wayland-egl" must be specified for EGL backend. Apps don't work properly
    // otherwise (upside-down, no mouse forwarding).
    , m_appInfoColl{
          {ApplicationId::TOOLBAR_APP, {"../ToolBarApp/ToolBarApp -platform wayland-egl", nullptr}},
          {ApplicationId::ORANGE_APP, {"../ClientApp/ClientApp -platform wayland-egl orange", nullptr}},
          {ApplicationId::LIGHTGREEN_APP, {"../ClientApp/ClientApp -platform wayland-egl lightgreen", nullptr}},
          {ApplicationId::BLACK_APP, {"../ClientApp/ClientApp -platform wayland-egl black", nullptr}},
          {ApplicationId::CYAN_APP, {"../ClientApp/ClientApp -platform wayland-egl cyan", nullptr}},
          {ApplicationId::MAGENTA_APP, {"../ClientApp/ClientApp -platform wayland-egl magenta", nullptr}},
      }
{
    qmlRegisterUncreatableType<ApplicationId>("EmbeddedUse.Application", 1, 0, "ApplicationId",
                                              "Creating ApplicationId in QML not allowed");
    m_sourceNode.enableRemoting(this);
    QMetaObject::invokeMethod(this, [this]() { openApplication(ApplicationId::TOOLBAR_APP); },
                              Qt::QueuedConnection);
}

void ApplicationManagerService::openApplication(int appId)
{
    auto &appInfo = m_appInfoColl[appId];
    if (appInfo.m_command.isEmpty()) {
        qDebug() << "### No application found for ID " << appId;
        return;
    }
    if (appInfo.m_process == nullptr) {
        qDebug() << "@@@ ApplicationManagerService::openApplication/create: " << appId;
        appInfo.m_process = new QProcess{this};
        auto env = QProcessEnvironment::systemEnvironment();
        // QT_WAYLAND_CLIENT_BUFFER_INTEGRATION and QT_XCB_GL_INTEGRATION must be removed,
        // because they are only relevant for the compositor and confuse the other apps
        // (upside-down, no mouse forwarding).
        env.remove("QT_WAYLAND_CLIENT_BUFFER_INTEGRATION");
        env.remove("QT_XCB_GL_INTEGRATION");
        env.insert("QT_IVI_SURFACE_ID", QString::number(appId));
        env.insert("QT_WAYLAND_SHELL_INTEGRATION", "ivi-shell");
        appInfo.m_process->setProcessEnvironment(env);
        appInfo.m_process->start(appInfo.m_command);
    }
    else {
        qDebug() << "@@@ ApplicationManagerService::openApplication/raise: " << appId;
        emit raiseApplicationRequested(appId);
    }
}
