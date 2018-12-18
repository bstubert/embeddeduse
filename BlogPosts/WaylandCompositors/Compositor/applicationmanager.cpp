#include <QProcess>
#include <QtDebug>

#include "applicationmanager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QAbstractListModel{parent}
    , m_appInfoColl{
          {QString{"orange"}, nullptr},
          {QString{"lightgreen"}, nullptr},
          {QString{"cyan"}, nullptr},
          {QString{"magenta"}, nullptr}
      }
{
}

QHash<int, QByteArray> ApplicationManager::roleNames() const
{
    static const QHash<int, QByteArray> roleColl{
        { ROLE_COLOR, "color" },
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
    if (row < 0 || row >= rowCount() || role != ROLE_COLOR) {
        return {};
    }
    return m_appInfoColl[row].m_color;
}

void ApplicationManager::startApplication(int row)
{
    if (row < 0 || row >= rowCount()) {
        return;
    }
    if (m_appInfoColl[row].m_process != nullptr) { // TODO: Raise app to top of stack
        return;
    }
    auto cmd = QString{"../ClientApp/ClientApp -platform wayland %1"}
            .arg(m_appInfoColl[row].m_color);
    qInfo() << "INFO: Starting application " << cmd;
    m_appInfoColl[row].m_process = new QProcess{this};
    m_appInfoColl[row].m_process->start(cmd);
    qInfo() << "INFO: Process ID = " << m_appInfoColl[row].m_process->processId();
}

