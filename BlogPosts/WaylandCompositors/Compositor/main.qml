import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

WaylandCompositor {
    WaylandOutput {
        sizeFollowsWindow: true

        window: ApplicationWindow {
            id: mainWindow
            visible: true
            width: 1280
            height: 800

            Item {
                id: appContainer
                anchors.fill: parent
            }

            footer: ToolBar {
                height: 80

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height
                    spacing: 16

                    Repeater {
                        model: gAppMgr.allApps

                        RoundButton {
                            anchors.verticalCenter: parent.verticalCenter
                            height: home ? 75 : 60
                            width: height
                            radius: height / 2
                            palette.button: model.color
                            onClicked: {
                                if (home) {
                                    console.log("@@@ Clicked home button")
                                    return
                                }
                                if (running) {
                                    appContainer.children = applicationItem
                                }
                                else {
                                    running = true
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    IviApplication {
        onIviSurfaceCreated: {
            var appComponent = Qt.createComponent("ApplicationItem.qml")
            var appItem = appComponent.createObject(null, {
                                                        "shellSurface": iviSurface,
                                                        "processId": iviSurface.iviId
                                                    })
            appContainer.children = appItem
            gAppMgr.insertApplicationItem(iviSurface.iviId, appItem)
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }
}
