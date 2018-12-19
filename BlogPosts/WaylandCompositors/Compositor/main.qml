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

            Container {
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
                        Button {
                            height: 60
                            width: height
                            background: Rectangle {
                                radius: parent.height / 2
                                color: model.color
                            }
                            onClicked: appMgr.startApplication(index)
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
            appContainer.addItem(appItem)
            appContainer.contentItem = appItem
            console.log("@@@ appId = ", iviSurface.iviId, ", #items = ", appContainer.count)
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }
}
