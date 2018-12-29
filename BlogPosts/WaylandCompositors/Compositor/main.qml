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
