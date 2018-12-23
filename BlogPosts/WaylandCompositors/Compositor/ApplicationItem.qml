import QtQuick 2.12
import QtQuick.Controls 2.5
import QtWayland.Compositor 1.3

ShellSurfaceItem {
    property int processId: 0
    anchors.fill: parent
    onSurfaceDestroyed: {
        console.log("@@@ Destroying surface of process ", processId)
        destroy()
    }
}
