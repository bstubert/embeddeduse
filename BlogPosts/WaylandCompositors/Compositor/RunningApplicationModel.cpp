#include "RunningApplicationModel.h"

RunningApplicationModel::RunningApplicationModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool RunningApplicationModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    auto isRunning = sourceModel()->data(sourceIndex, filterRole()).toBool();
    return isRunning;
}

