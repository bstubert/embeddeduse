#include "riverstyle.h"

RiverStyle::RiverStyle(QObject *parent)
    : QObject(parent)
    , m_background("#f2f3ae")
    , m_foreground("#69140e")
    , m_accent("#3c1518")
{
}

RiverStyle *RiverStyle::qmlAttachedProperties(QObject *parent)
{
    return new RiverStyle(parent);
}

QColor RiverStyle::background() const
{
    return m_background;
}

void RiverStyle::setBackground(QColor color)
{
    if (m_background != color) {
        m_background = color;
        emit backgroundChanged();
    }
}

QColor RiverStyle::foreground() const
{
    return m_foreground;
}

void RiverStyle::setForeground(QColor color)
{
    if (m_foreground != color) {
        m_foreground = color;
        emit foregroundChanged();
    }
}

QColor RiverStyle::accent() const
{
    return m_accent;
}

void RiverStyle::setAccent(QColor color)
{
    if (m_accent != color) {
        m_accent = color;
        emit accentChanged();
    }
}
