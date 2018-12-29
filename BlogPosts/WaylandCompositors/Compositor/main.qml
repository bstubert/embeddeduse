import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

import EmbeddedUse.Application 1.0

WaylandCompositor {
    WaylandOutput {
        sizeFollowsWindow: true

        window: Window {
            id: mainWindow
            visible: true
            width: 1280
            height: 800

            Rectangle {
                id: mainArea
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    bottom: toolBarArea.top
                }
                color: "pink"
                transform: Rotation {
                    origin.x: mainArea.width / 2
                    origin.y: mainArea.height / 2
                    axis { x: 1; y: 0; z: 0 }
                    angle: 180
                }
            }

            Rectangle {
                id: toolBarArea
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: 80
                color: "purple"
                transform: Rotation {
                    origin.x: toolBarArea.width / 2
                    origin.y: toolBarArea.height / 2
                    axis { x: 1; y: 0; z: 0 }
                    angle: 180
                }
            }
        }
    }

    IviApplication {
        onIviSurfaceCreated: {
            console.log("@@@ Created surface for app ", iviSurface.iviId)
            var area = iviSurface.iviId === ApplicationId.TOOLBAR_APP ? toolBarArea : mainArea
            var comp = Qt.createComponent("ApplicationItem.qml")
            var item = comp.createObject(area, {
                                             "shellSurface": iviSurface,
                                             "appId": iviSurface.iviId
                                         })
            item.doResize()
        }
    }

    Connections {
        target: gAppMgr
        onRaiseApplicationRequested: {
            for (var i = 0; i < mainArea.children.length; i++) {
                if (mainArea.children[i].appId === appId) {
                    console.log("@@@ Raising application ", appId)
                    mainArea.children[i].raise()
                    return
                }
            }
        }
    }
}
