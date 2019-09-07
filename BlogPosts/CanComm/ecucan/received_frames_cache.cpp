// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "received_frames_cache.h"

ReceivedFramesCache::ReceivedFramesCache()
{
}

QSet<int> ReceivedFramesCache::updateFrames(const QVector<QCanBusFrame> &frameColl)
{
    auto ecuIdColl = QSet<int>{};
    for (const auto &frame : frameColl)
    {
        auto id = sourceEcuId(frame);
        ecuIdColl.insert(id);
        m_cache[id].append(frame);
    }
    return ecuIdColl;
}

QVector<QCanBusFrame> ReceivedFramesCache::takeFrames(int ecuId)
{
    return m_cache.take(ecuId);
}

int ReceivedFramesCache::sourceEcuId(const QCanBusFrame &frame) const
{
    return static_cast<int>(frame.frameId() & 0x000000FF);
}
