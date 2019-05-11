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
            id: tx100
            anchors {
                left: parent.left
                top: parent.top
            }
            text: "Tx 100"
            font.pixelSize: 24
            onReleased: gSimulator.simulateTxBufferOverflow(100)
        }

        Button {
            id: tx200
            anchors {
                left: tx100.right
                leftMargin: 16
                top: parent.top
            }
            text: "Tx 200"
            font.pixelSize: 24
            onReleased: gSimulator.simulateTxBufferOverflow(200)
        }

        Button {
            id: tx500
            anchors {
                left: tx200.right
                leftMargin: 16
                top: parent.top
            }
            text: "Tx 800"
            font.pixelSize: 24
            onReleased: gSimulator.simulateTxBufferOverflow(800)
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
                        target: gSimulator
                        onLogMessage: output.append(msg)
                    }
                }
            }
        }
    }
}
