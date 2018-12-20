#include <QProcess>
#include <QQuickItem>
#include <QtDebug>
#include <QVariant>

#include "ApplicationSourceModel.h"

namespace {
const QString c_home{"black"};
}

ApplicationSourceModel::ApplicationSourceModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_appInfoColl{
          {QString{"orange"}, nullptr, nullptr},
          {QString{"lightgreen"}, nullptr, nullptr},
          {c_home, nullptr, nullptr},
          {QString{"cyan"}, nullptr, nullptr},
          {QString{"magenta"}, nullptr, nullptr}
      }
{
}

QHash<int, QByteArray> ApplicationSourceModel::roleNames() const
{
    static const QHash<int, QByteArray> roleColl{
        { ROLE_COLOR, "color" },
        { ROLE_RUNNING, "running" },
        { ROLE_PROCESS_ID, "processId" },
        { ROLE_HOME, "home" },
        { ROLE_APPLICATION_ITEM, "applicationItem" },
    };
    return roleColl;
}

int ApplicationSourceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_appInfoColl.size();
}

QVariant ApplicationSourceModel::data(const QModelIndex &index, int role) const
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
    case ROLE_APPLICATION_ITEM: {
        QVariant v;
        v.setValue(static_cast<QObject *>(appInfo.m_item));
        return v;
    }
    default:
        return {};
    }
}

bool ApplicationSourceModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

bool ApplicationSourceModel::startApplication(int row)
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

void ApplicationSourceModel::insertApplicationItem(int processId, QQuickItem *item)
{
    auto index = indexOfProcess(processId);
    if (index != -1) {
        m_appInfoColl[index].m_item = item;
    }
}

int ApplicationSourceModel::indexOfProcess(int processId) const
{
    for (int i = 0; i < m_appInfoColl.size(); ++i) {
        if (m_appInfoColl[i].m_process != nullptr &&
                m_appInfoColl[i].m_process->processId() == processId) {
            return i;
        }
    }
    return -1;
}
