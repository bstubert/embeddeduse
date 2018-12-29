import QtQuick 2.12
import QtQuick.Controls 2.5
import QtWayland.Compositor 1.3

ShellSurfaceItem {
    property int appId: 0
    anchors.fill: parent
    onWidthChanged: doResize()
    onHeightChanged: doResize()
    onSurfaceDestroyed: {
        console.log("@@@ Destroying surface of application ", appId)
        destroy()
    }

    function doResize()
    {
        if (width < 0 || height < 0) {
            return
        }
        shellSurface.sendConfigure(Qt.size(width, height))
    }
}
