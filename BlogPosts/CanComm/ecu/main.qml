// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

import QtQuick 2.10
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
            id: twoEcus
            anchors {
                left: parent.left
                top: parent.top
            }
            text: "2 ECUs"
            font.pixelSize: 24
            onReleased: gEcu.sendFramesFromTwoEcus()
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

        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                top: clear.bottom
                topMargin: 32
                bottom: parent.bottom
            }
            color: "#e2f9b8"

            Flickable {
                id: scrollView
                anchors.fill: parent
                clip: true
                contentWidth: output.paintedWidth
                contentHeight: output.paintedHeight

                TextEdit {
                    id: output
                    readOnly: true
                    font.pixelSize: 16
                    onCursorRectangleChanged: scrollView.contentY = output.cursorRectangle.y

                    Connections {
                        target: gEcu
                        onLogMessage: output.append(msg)
                    }
                }
            }
        }
    }
}
