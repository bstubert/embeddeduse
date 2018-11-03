import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Window 2.10
import RiverStyle 1.0

Window {
    id: mainWindow
    visible: true
    width: 400
    height: 600
    title: qsTr("QML with Style")
//    Component.onCompleted: switchToLightTheme()

//    function switchToLightTheme() {
//        Universal.theme = Universal.Light
//        Universal.background = "#f2f3ae"
//        Universal.foreground = "#69140e"
//        Universal.accent = "#3c1518"
//    }

//    function switchToDarkTheme() {
//        Universal.theme = Universal.Light
//        Universal.background = "#3c1518"
//        Universal.foreground = "#f2f3ae"
//        Universal.accent = "#d58936"
//    }

    Pane {
        id: mainPane
        anchors.fill: parent
        readonly property real buttonHeight: 64

        Label {
            id: pinDisplay
            anchors {
                left: keypad.left
                right: keypad.right
                top: parent.top
            }
            height: 64
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            function appendDigit(digit) {
                if (text.length < 6) {
                    text += digit
                }
            }

            function removeLastDigit() {
                if (text.length > 0) {
                    text = text.slice(0, -1)
                }
            }
        }

        Grid {
            id: keypad
            anchors {
                top: pinDisplay.bottom
            }
            columns: 3
            rows: 4
            spacing: 4

            Repeater {
                model: parent.columns * parent.rows

                Button {
                    width: mainPane.buttonHeight
                    height: width
                    enabled: !isUnusedKey

                    readonly property bool isUnusedKey: index == 9
                    readonly property bool isDigitKeyFrom1To9: index >=0 && index <= 8
                    readonly property bool isDigitKey0: index == 10
                    readonly property bool isBackspaceKey: index == 11

                    text: {
                        if (isDigitKeyFrom1To9) {
                            (index + 1).toString()
                        }
                        else if (isDigitKey0) {
                            "0"
                        }
                        else {
                            ""
                        }
                    }

                    icon {
                        source: isBackspaceKey ? "/backspace.png" : ""
                        width: 48
                        height: width
                    }

                    onReleased: {
                        if (isBackspaceKey) {
                            pinDisplay.removeLastDigit()
                        }
                        else {
                            pinDisplay.appendDigit(text)
                        }
                    }
                }
            }
        }

//        ButtonGroup {
//            buttons: themeButtons.children
//        }

//        Column {
//            id: themeButtons
//            anchors {
//                left: keypad.right
//                leftMargin: 16
//                right: parent.right
//                top: keypad.top
//            }

//            RadioButton {
//                checked: true
//                text: qsTr("Light")
//                width: parent.width
//                height: mainPane.buttonHeight
//                onReleased: mainWindow.switchToLightTheme()
//            }

//            RadioButton {
//                text: qsTr("Dark")
//                width: parent.width
//                height: mainPane.buttonHeight
//                onReleased: mainWindow.switchToDarkTheme()
//            }
//        }
    }
}
