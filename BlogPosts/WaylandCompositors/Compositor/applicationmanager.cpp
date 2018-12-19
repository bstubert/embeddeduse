#include <QProcess>
#include <QtDebug>

#include "applicationmanager.h"

namespace {
const QString c_home{"black"};
}

ApplicationManager::ApplicationManager(QObject *parent)
    : QAbstractListModel{parent}
    , m_appInfoColl{
          {QString{"orange"}, nullptr},
          {QString{"lightgreen"}, nullptr},
          {c_home, nullptr},
          {QString{"cyan"}, nullptr},
          {QString{"magenta"}, nullptr}
      }
{
}

QHash<int, QByteArray> ApplicationManager::roleNames() const
{
    static const QHash<int, QByteArray> roleColl{
        { ROLE_COLOR, "color" },
        { ROLE_RUNNING, "running" },
        { ROLE_PROCESS_ID, "processId" },
        { ROLE_HOME, "home" },
    };
    return roleColl;
}

int ApplicationManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_appInfoColl.size();
}

QVariant ApplicationManager::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    if (row < 0 || row >= rowCount()) {
        return {};
    }
    auto &appInfo = m_appInfoColl[row];
    switch (role) {
    case ROLE_COLOR:
        return appInfo.m_color;
    case ROLE_RUNNING:
        return appInfo.m_process != nullptr && appInfo.m_process->state() == QProcess::Running;
    case ROLE_PROCESS_ID:
        return appInfo.m_process != nullptr ? appInfo.m_process->processId() : -1;
    case ROLE_HOME:
        return appInfo.m_color == c_home;
    default:
        return {};
    }
}

bool ApplicationManager::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role) {
    case ROLE_RUNNING:
        if (value.toBool()) {
            return startApplication(index.row());
        }
        // TODO: Stop application
        return false;
    default:
        return false;
    }
}

bool ApplicationManager::startApplication(int row)
{
    if (row < 0 || row >= rowCount()) {
        return false;
    }
    auto &appInfo = m_appInfoColl[row];
    if (appInfo.m_process != nullptr) {
        return true; // Already running
    }
    auto cmd = QString{"../ClientApp/ClientApp -platform wayland %1"}.arg(appInfo.m_color);
    appInfo.m_process = new QProcess{this};
    appInfo.m_process->start(cmd);
    qInfo() << QString{"INFO: Started application %1 with process ID %2."}.arg(appInfo.m_color)
               .arg(appInfo.m_process->processId());
    return true;
}

