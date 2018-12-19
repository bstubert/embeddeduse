import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

import EmbeddedUse.Models 1.0

WaylandCompositor {
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
                    anchors.centerIn: parent
                    spacing: 8
                    Repeater {
                        model: appMgr
                        RoundButton {
                            height: 60
                            width: height
                            radius: height / 2
                            palette.button: model.color
                            onClicked: {
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

    Component {
        id: appComponent
        ShellSurfaceItem {
            property int processId: 0
            anchors.fill: parent
            onSurfaceDestroyed: destroy()
        }
    }

    IviApplication {
        onIviSurfaceCreated: {
            var appItem = appComponent.createObject(appContainer, {
                                                        "shellSurface": iviSurface,
                                                        "processId": iviSurface.iviId
                                                    })
            appItemColl.push(appItem)
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }
}
