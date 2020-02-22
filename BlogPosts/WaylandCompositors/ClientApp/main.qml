import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

ApplicationWindow {
    visible: true
    width: 1280
    height: 720

    Rectangle {
        id: background
        anchors.fill: parent
        color: backgroundColor

        Button {
            id: darkerButton
            anchors {
                left: parent.left
                leftMargin: 8
                bottom: parent.bottom
                bottomMargin: 8
            }
            width: 120
            height: 60
            text: "Darker"
            onReleased: {
                console.log("@ Darker button released")
                background.color = Qt.darker(background.color, 1.5)
            }
        }

        Button {
            id: lighterButton
            anchors {
                right: parent.right
                rightMargin: 8
                bottom: parent.bottom
                bottomMargin: 8
            }
            width: 120
            height: 60
            text: "Lighter"
            onReleased: {
                console.log("@ Lighter button released")
                background.color = Qt.lighter(background.color, 1.5)
            }
        }
    }
}
