import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

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
            var area = iviSurface.iviId === 1 ? toolBarArea : mainArea
            var comp = Qt.createComponent("ApplicationItem.qml")
            var item = comp.createObject(area, {
                                             "shellSurface": iviSurface,
                                             "processId": iviSurface.iviId
                                         })
            iviSurface.sendConfigure(Qt.size(toolBarArea.width, toolBarArea.height))
        }
    }
}
