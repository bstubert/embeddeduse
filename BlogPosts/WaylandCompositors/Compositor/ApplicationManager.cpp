#include <QMetaObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtDebug>
#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject{parent}
{
    QMetaObject::invokeMethod(this, [this]() { openApplication(1); },  Qt::QueuedConnection);
}

void ApplicationManager::openApplication(int appId)
{
    qDebug() << "### openApplication: " << appId;
    auto env = QProcessEnvironment::systemEnvironment();
    env.insert("QT_IVI_SURFACE_ID", QString::number(appId));
    m_toolBarProcess.setProcessEnvironment(env);
    m_toolBarProcess.start("../ToolBarApp/ToolBarApp -platform wayland");
}
