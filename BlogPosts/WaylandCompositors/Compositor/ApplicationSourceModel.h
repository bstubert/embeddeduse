#ifndef APPLICATIONSOURCEMODEL_H
#define APPLICATIONSOURCEMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QString>
#include <QVector>
class QProcess;
class QQuickItem;
class QVariant;

class ApplicationSourceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        ROLE_COLOR = Qt::UserRole,
        ROLE_IS_RUNNING,
        ROLE_PROCESS_ID,
        ROLE_IS_HOME,
        ROLE_APPLICATION_ITEM,
        ROLE_IS_TOP
    };
    explicit ApplicationSourceModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

public slots:
    bool startApplication(int row);
    // The ownership of item stays with the QML engine.
    void insertApplicationItem(int processId, QQuickItem *item);

private:
    struct AppInfo {
        QString m_color;
        bool m_isTop;
        QProcess *m_process;
        QQuickItem *m_item;
    };
    int indexOfProcess(int processId) const;
    QVector<AppInfo> m_appInfoColl;
};

#endif // APPLICATIONSOURCEMODEL_H
