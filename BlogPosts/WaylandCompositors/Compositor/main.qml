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

            StackView {
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
            console.log("@@@ appId = ", iviSurface.iviId)
            var appItem = appComponent.createObject(appContainer, {
                                                        "shellSurface": iviSurface,
                                                        "processId": iviSurface.iviId
                                                    })
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }
}
