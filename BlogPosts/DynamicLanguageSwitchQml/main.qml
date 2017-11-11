import QtQuick 2.8
import QtQuick.Controls 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 320
    height: 240
    title: qsTr("Dynamic Language Switching")

    Rectangle {
        anchors.fill: parent
        color: "#F87060"

        Column {
            anchors {
                margins: 8
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            width: 0.4 * parent.width
            spacing: 8

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: 40
                radius: 8
                color: "transparent"
                border.color: "#102542"
                border.width: 2

                Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Sun")
                    font.pixelSize: 32
                    color: "#102542"
                }
            }

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: 40
                radius: 8
                color: "transparent"
                border.color: "#102542"
                border.width: 2

                Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Beach")
                    font.pixelSize: 32
                    color: "#102542"
                }
            }

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: 40
                radius: 8
                color: "transparent"
                border.color: "#102542"
                border.width: 2

                Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Sea")
                    font.pixelSize: 32
                    color: "#102542"
                }
            }
        }

        Column {
            anchors {
                margins: 8
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            width: 0.4 * parent.width
            spacing: 8

            Button {
                id: buttonGerman
                anchors {
                    right: parent.right
                    rightMargin: 8
                }
                width: 100
                height: 60

                background: Item {}

                icon {
                    source: "flagGermany.png"
                    width: parent.width
                    height: parent.height
                    color: "transparent"
                }

                onReleased: settings.switchToLanguage("de_DE")
            }

            Button {
                id: buttonEnglish
                anchors {
                    right: parent.right
                    rightMargin: 8
                }
                width: 100
                height: 60

                background: Item {}

                icon {
                    source: "flagUK.png"
                    width: parent.width
                    height: parent.height
                    color: "transparent"
                }

                onReleased: settings.switchToLanguage("en_UK")
            }
        }
    }
}
