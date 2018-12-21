import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    Rectangle {
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
                console.log("@ Lighter button released")
                parent.color = Qt.darker(parent.color, 1.5)
            }
        }

        Button {
            id: lighterButton
            anchors {
                right: parent.left
                rightMargin: 8
                bottom: parent.bottom
                bottomMargin: 8
            }
            width: 120
            height: 60
            text: "Lighter"
            onReleased: {
                console.log("@ Lighter button released")
                parent.color = Qt.lighter(parent.color, 1.5)
            }
        }
    }
}
