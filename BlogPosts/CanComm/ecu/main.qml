// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

import QtQuick 2.12
import QtQuick.Controls 2.3


ApplicationWindow {
    id: gApp

    visible: true
    width: 1280
    height: 800


    Pane {
        id: mainItem
        anchors.fill: parent
        padding: 16
        background: Rectangle {
            color: "#effbd8"
        }

        Button {
            id: clear
            anchors {
                right: parent.right
                top: parent.top
            }
            text: "Clear"
            font.pixelSize: 24
            onReleased: output.clear()
        }

        ScrollView {
            anchors {
                left: parent.left
                right: parent.right
                top: clear.bottom
                topMargin: 32
                bottom: parent.bottom
            }
            background: Rectangle {
                color: "#e2f9b8"
            }
            clip: true
            contentWidth: output.paintedWidth
            contentHeight: output.paintedHeight

            TextEdit {
                id: output
                readOnly: true
                font.pixelSize: 16

                Connections {
                    target: gSimulator
                    onLogMessage: output.append(msg)
                }
            }
        }
   }
}
