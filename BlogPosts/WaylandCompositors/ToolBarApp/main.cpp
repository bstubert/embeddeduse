#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QSharedPointer>
#include <QString>
#include <QUrl>

#include "ApplicationManagerClient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QRemoteObjectNode replicaNode;
    replicaNode.connectToNode(QUrl{QStringLiteral("local:applicationService")});
    QSharedPointer<ApplicationServiceReplica> replica;
    replica.reset(replicaNode.acquire<ApplicationServiceReplica>());
    ApplicationManagerClient appMgr(replica);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gAppMgr", &appMgr);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}
