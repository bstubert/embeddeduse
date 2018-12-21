import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtWayland.Compositor 1.3

WaylandCompositor {
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
                id: toolBar
                property Item appSwitcher: null
                height: 80

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height
                    spacing: 16

                    Repeater {
                        model: gAppMgr.topApps

                        RoundButton {
                            anchors.verticalCenter: parent.verticalCenter
                            height: isHome ? 75 : 60
                            width: height
                            radius: height / 2
                            palette.button: model.color
                            onReleased: {
                                if (isHome) {
                                    return
                                }
                                if (isRunning) {
                                    appContainer.children = applicationItem
                                }
                                else {
                                    isRunning = true
                                }
                            }
                            onPressAndHold: {
                                if (!isHome) {
                                    return
                                }
                                if (toolBar.appSwitcher !== null) {
                                    toolBar.appSwitcher.destroy()
                                }
                                var comp = Qt.createComponent("ApplicationSwitcher.qml")
                                toolBar.appSwitcher = comp.createObject(
                                            appContainer, {"model": gAppMgr.runningApps})
                                appContainer.children = toolBar.appSwitcher
                            }
                        }
                    }
                }
            }
        }
    }

    IviApplication {
        onIviSurfaceCreated: {
            var comp = Qt.createComponent("ApplicationItem.qml")
            var item = comp.createObject(appContainer, {
                                             "shellSurface": iviSurface,
                                             "processId": iviSurface.iviId
                                         })
            appContainer.children = item
            gAppMgr.insertApplicationItem(iviSurface.iviId, item)
            iviSurface.sendConfigure(Qt.size(appContainer.width, appContainer.height))
        }
    }
}
