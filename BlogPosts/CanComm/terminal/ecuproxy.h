// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#ifndef ECUPROXY_H
#define ECUPROXY_H

#include <QObject>

class EcuProxy : public QObject
{
    Q_OBJECT
public:
    explicit EcuProxy(QObject *parent = nullptr);

signals:
    void parameterRead(quint16 pid, quint32 value);

public slots:
    void readParameter(quint16 pid);
};

#endif // ECUPROXY_H
