import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

import EmbeddedUse.Models 1.0

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
                        model: appMgr

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
                                    appContainer.children = appItemForProcess(processId)
                                }
                                else {
                                    running = true
                                }
                            }
                        }
                    }
                }
            }

            ApplicationManager {
                id: appMgr
            }
        }
    }

    IviApplication {
        onIviSurfaceCreated: {
            var appComponent = Qt.createComponent("ApplicationItem.qml")
            var appItem = appComponent.createObject(appContainer, {
                                                        "shellSurface": iviSurface,
                                                        "processId": iviSurface.iviId
                                                    })
            appItemColl.push(appItem)
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }

    property var appItemColl: []
    function appItemForProcess(pid) {
        var ix = 0
        for (; ix < appItemColl.length; ix++) {
            if (appItemColl[ix].processId === pid) {
                return appItemColl[ix]
            }
        }
        return null
    }
}
