import QtQuick 2.6
import QtQuick.Window 2.2
import com.embeddeduse.models 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Passing Enums between QML and C++")

    property MainModel mainModel : MainModel {}

    Rectangle {
        width: parent.width
        height: 0.5 * parent.height
        color: toColor(mainModel.warningLevel)
    }

    Row {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 0.5 * parent.height
        Repeater {
            model: [WarningLevel.Error, WarningLevel.Warning, WarningLevel.Info,
                WarningLevel.Debug]
            Rectangle {
                width: 0.25 * parent.width
                height: parent.height
                color: toColor(modelData)
                MouseArea {
                    anchors.fill: parent
                    onReleased: mainModel.warningLevel = modelData
                }
            }
        }
    }

    function toColor(level) {
        switch (level) {
        case WarningLevel.Error:
            return "red"
        case WarningLevel.Warning:
            return "orange"
        case WarningLevel.Info:
            return "green"
        case WarningLevel.Debug:
            return "purple"
        default:
            return "magenta"
        }
    }
}
