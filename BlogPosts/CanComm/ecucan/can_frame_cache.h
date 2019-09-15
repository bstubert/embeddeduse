// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QCanBusFrame>
#include <QMap>
#include <QSet>
#include <QVector>

class CanFrameCache
{
public:
    CanFrameCache();
    QSet<int> enqueueIncomingFrames(const QVector<QCanBusFrame> & frameColl);
    QVector<QCanBusFrame> takeIncomingFrames(int ecuId);

    QCanBusFrame enqueueOutgoingFrame(const QCanBusFrame &frame);
    QCanBusFrame dequeueOutgoingFrame();

private:
    int sourceEcuId(const QCanBusFrame &frame) const;

    QMap<int, QVector<QCanBusFrame>> m_incomingCache;
    QVector<QCanBusFrame> m_outgoingCache;
};
