// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <QRandomGenerator>
#include "ecuproxy.h"

EcuProxy::EcuProxy(QObject *parent)
    : QObject(parent)
{
}

void EcuProxy::readParameter(quint16 pid)
{
    emit parameterRead(pid, QRandomGenerator::global()->generate());
}
