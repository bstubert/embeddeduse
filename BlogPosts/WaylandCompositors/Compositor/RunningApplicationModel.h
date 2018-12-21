#ifndef RUNNINGAPPLICATIONMODEL_H
#define RUNNINGAPPLICATIONMODEL_H

#include <QSortFilterProxyModel>

class RunningApplicationModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit RunningApplicationModel(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // RUNNINGAPPLICATIONMODEL_H
