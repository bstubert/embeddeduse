import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

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
                    }
                    ListElement {
                        color: "lightgreen"
                        isHome: false
                    }
                    ListElement {
                        color: "black"
                        isHome: true
                    }
                    ListElement {
                        color: "cyan"
                        isHome: false
                    }
                    ListElement {
                        color: "magenta"
                        isHome: false
                    }
                }

                RoundButton {
                    anchors.verticalCenter: parent.verticalCenter
                    height: isHome ? 75 : 60
                    width: height
                    radius: height / 2
                    palette.button: model.color
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
