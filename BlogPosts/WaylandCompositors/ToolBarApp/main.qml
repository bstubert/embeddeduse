import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

import EmbeddedUse.Application 1.0

Window {
    visible: true
    width: 1280
    height: 80

    ToolBar {
        id: toolBar
        anchors.fill: parent
//        property Item appSwitcher: null

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height
            spacing: 16

            Repeater {
                model: ListModel {
                    ListElement {
                        color: "orange"
                        isHome: false
                        appId: ApplicationId.ORANGE_APP
                    }
                    ListElement {
                        color: "lightgreen"
                        isHome: false
                        appId: ApplicationId.LIGHTGREEN_APP
                    }
                    ListElement {
                        color: "black"
                        isHome: true
                        appId: ApplicationId.BLACK_APP
                    }
                    ListElement {
                        color: "cyan"
                        isHome: false
                        appId: ApplicationId.CYAN_APP
                    }
                    ListElement {
                        color: "magenta"
                        isHome: false
                        appId: ApplicationId.MAGENTA_APP
                    }
                }

                RoundButton {
                    anchors.verticalCenter: parent.verticalCenter
                    height: isHome ? 75 : 60
                    width: height
                    radius: height / 2
                    palette.button: model.color
                    onReleased: gAppMgr.openApplication(appId)
//                    onReleased: {
//                        if (isHome) {
//                            return
//                        }
//                        if (isRunning) {
//                            appContainer.children = applicationItem
//                        }
//                        else {
//                            isRunning = true
//                        }
//                    }
//                    onPressAndHold: {
//                        if (!isHome) {
//                            return
//                        }
//                        if (toolBar.appSwitcher !== null) {
//                            toolBar.appSwitcher.destroy()
//                        }
//                        var comp = Qt.createComponent("ApplicationSwitcher.qml")
//                        toolBar.appSwitcher = comp.createObject(
//                                    appContainer, {"model": gAppMgr.runningApps})
//                        appContainer.children = toolBar.appSwitcher
//                    }
//                }
                }
            }
        }
    }
}
