#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QString>
#include <QVariant>
#include <QVector>
class QProcess;

class ApplicationManager : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        ROLE_COLOR = Qt::UserRole,
        ROLE_RUNNING,
        ROLE_PROCESS_ID
    };
    explicit ApplicationManager(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

public slots:
    bool startApplication(int row);

private:
    struct AppInfo {
        QString m_color;
        QProcess *m_process;
    };
    QVector<AppInfo> m_appInfoColl;
};

#endif // APPLICATIONMANAGER_H
