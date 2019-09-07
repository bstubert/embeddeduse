// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include <QObject>
#include <QString>

class CanBusRouter;
class Ecu;

class EcuModel : public QObject
{
    Q_OBJECT

public:
    explicit EcuModel(QObject *parent = nullptr);
    virtual ~EcuModel();

public slots:
    void sendFramesFromTwoEcus();

signals:
    void logMessage(const QString &msg);

private:
    Ecu *createEcu(int ecuId);

    CanBusRouter *m_router;
    Ecu *m_a2;
    Ecu *m_a3;
};
