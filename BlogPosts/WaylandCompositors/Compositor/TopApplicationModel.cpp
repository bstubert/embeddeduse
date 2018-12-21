#include "TopApplicationModel.h"

TopApplicationModel::TopApplicationModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool TopApplicationModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    auto isTop = sourceModel()->data(sourceIndex, filterRole()).toBool();
    return isTop;
}
