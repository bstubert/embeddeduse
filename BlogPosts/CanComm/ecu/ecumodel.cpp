// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include "canbusrouter.h"
#include "ecu.h"
#include "ecumodel.h"

EcuModel::EcuModel(QObject *parent)
    : QObject{parent}
    , m_router{new CanBusRouter{"socketcan", "can0", this}}
    , m_a2{createEcu(2)}
    , m_a3{createEcu(3)}
{
}

EcuModel::~EcuModel()
{
}

void EcuModel::sendFramesFromTwoEcus()
{
    m_a2->sendUnsolicitedFrames();
    m_a3->sendUnsolicitedFrames();
}

Ecu *EcuModel::createEcu(int ecuId)
{
    auto ecu = new Ecu{ecuId, m_router};
    ecu->setLogging(true);
    connect(m_router, &CanBusRouter::errorOccurred,
            ecu, &Ecu::onErrorOccurred);
    connect(m_router, &CanBusRouter::framesReceived,
            ecu, &Ecu::onFramesReceived);
    connect(ecu, &Ecu::logMessage,
            this, &EcuModel::logMessage);
    return ecu;
}
