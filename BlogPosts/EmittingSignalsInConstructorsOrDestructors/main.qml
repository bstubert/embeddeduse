// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    id: topWindow
    visible: true
    width: 320
    height: 240
    title: qsTr("EmbeddedUse")

    Rectangle {
        id: view
        property bool isSecondScreenShown: false
        anchors.fill: parent
        color: "#EDFFAB"

        Label {
            anchors.fill: parent
            text: "Main Screen"
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        Loader {
            id: loader
            anchors.fill: parent
        }

        Button {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 0.25 * topWindow.width
            height: 0.10 * topWindow.height
            text: !view.isSecondScreenShown ? qsTr("Open") : qsTr("Close")
            onClicked: {
                if (!view.isSecondScreenShown) {
                    loader.setSource("SecondScreen.qml")
                }
                else {
                    loader.setSource("")
                }
                view.isSecondScreenShown = !view.isSecondScreenShown
            }
        }
    }
}
