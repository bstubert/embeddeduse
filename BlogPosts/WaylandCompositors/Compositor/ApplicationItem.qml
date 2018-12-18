import QtQuick 2.12
import QtWayland.Compositor 1.3

ShellSurfaceItem {
    onSurfaceDestroyed: destroy()
    onWidthChanged: resizeSurface()
    onHeightChanged: resizeSurface()
    function resizeSurface() {
        shellSurface.sendConfigure(Qt.size(width, height));
    }
}
