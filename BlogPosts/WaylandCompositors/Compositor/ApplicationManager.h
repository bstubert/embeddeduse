#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QProcess>

#include "rep_ApplicationService_source.h"

class ApplicationManager : public ApplicationServiceSimpleSource
{
    Q_OBJECT

public:
    explicit ApplicationManager(QObject *parent = nullptr);

public slots:
    void openApplication(int appId) override;

private:
    QProcess m_toolBarProcess;
};

#endif // APPLICATIONMANAGER_H
