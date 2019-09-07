// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QMap>
#include <QSet>
#include <QVector>

class ReceivedFramesCache
{
public:
    ReceivedFramesCache();
    QSet<int> updateFrames(const QVector<QCanBusFrame> & frameColl);
    QVector<QCanBusFrame> takeFrames(int ecuId);

private:
    int sourceEcuId(const QCanBusFrame &frame) const;

    QMap<int, QVector<QCanBusFrame>> m_cache;
};
