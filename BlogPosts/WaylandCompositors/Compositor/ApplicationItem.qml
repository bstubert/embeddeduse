import QtQuick 2.12
import QtWayland.Compositor 1.3

ShellSurfaceItem {
    property int processId: 0
    anchors.fill: parent
    onSurfaceDestroyed: destroy()
}
