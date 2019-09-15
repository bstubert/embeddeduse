// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "can_frame_cache.h"

CanFrameCache::CanFrameCache()
{
}

QSet<int> CanFrameCache::enqueueIncomingFrames(const QVector<QCanBusFrame> &frameColl)
{
    auto ecuIdColl = QSet<int>{};
    for (const auto &frame : frameColl)
    {
        auto id = sourceEcuId(frame);
        ecuIdColl.insert(id);
        m_incomingCache[id].append(frame);
    }
    return ecuIdColl;
}

QVector<QCanBusFrame> CanFrameCache::takeIncomingFrames(int ecuId)
{
    return m_incomingCache.take(ecuId);
}

QCanBusFrame CanFrameCache::enqueueOutgoingFrame(const QCanBusFrame &frame)
{
    auto wasEmptyOnEntry = m_outgoingCache.isEmpty();
    // NOTE: If the frame was appended to the cache after writing it, the own frame could be
    // received before the frame is in the cache.
    m_outgoingCache.append(frame);
    if (wasEmptyOnEntry)
    {
        return frame;
    }
    return QCanBusFrame{QCanBusFrame::InvalidFrame};
}

QCanBusFrame CanFrameCache::dequeueOutgoingFrame()
{
    if (!m_outgoingCache.isEmpty())
    {
        m_outgoingCache.removeFirst();
    }
    if (!m_outgoingCache.isEmpty())
    {
        return m_outgoingCache.first();
    }
    return QCanBusFrame{QCanBusFrame::InvalidFrame};
}

int CanFrameCache::sourceEcuId(const QCanBusFrame &frame) const
{
    return static_cast<int>(frame.frameId() & 0x000000FF);
}
