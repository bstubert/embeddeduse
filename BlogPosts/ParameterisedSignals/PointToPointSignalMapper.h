#pragma once

#include <functional>
#include <QObject>

class PointToPointSignalMapper : public QObject
{
    Q_OBJECT
public:
    explicit PointToPointSignalMapper(QObject *parent = nullptr)
        : QObject(parent)
    {}

//    template <typename T>
//    void connect(const QObject *sender, std::function<void(T)> signal,
//                 std::function<bool(T)> condition,
//                 const QObject *receiver, std::function<void(T)> slot)
//    {

//    }

signals:

public slots:

private:

};
