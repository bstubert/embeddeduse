#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QProcess>

class ApplicationManager : public QObject
{
    Q_OBJECT

public:
    explicit ApplicationManager(QObject *parent = nullptr);

public slots:
    void openApplication(int appId);

private:
    QProcess m_toolBarProcess;
};

#endif // APPLICATIONMANAGER_H
