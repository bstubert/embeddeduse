#ifndef RIVERSTYLE_H
#define RIVERSTYLE_H

#include <QColor>
#include <QObject>
#include <QtQml>

class RiverStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)
    Q_PROPERTY(QColor accent READ accent WRITE setAccent NOTIFY accentChanged)

public:
    explicit RiverStyle(QObject *parent = nullptr);

    static RiverStyle *qmlAttachedProperties(QObject *parent);

    QColor background() const;
    void setBackground(QColor color);
    QColor foreground() const;
    void setForeground(QColor color);
    QColor accent() const;
    void setAccent(QColor color);

signals:
    void backgroundChanged();
    void foregroundChanged();
    void accentChanged();

private:
    QColor m_background;
    QColor m_foreground;
    QColor m_accent;
};

QML_DECLARE_TYPEINFO(RiverStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // RIVERSTYLE_H
