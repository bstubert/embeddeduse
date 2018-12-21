#ifndef TOPAPPLICATIONMODEL_H
#define TOPAPPLICATIONMODEL_H

#include <QSortFilterProxyModel>

class TopApplicationModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit TopApplicationModel(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // TOPAPPLICATIONMODEL_H
