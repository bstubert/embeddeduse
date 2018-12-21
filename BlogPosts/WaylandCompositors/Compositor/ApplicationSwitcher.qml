import QtQuick 2.12

Rectangle {
    property alias model: appView.model
    anchors.fill: parent
    color: "lightblue"

    ListView {
        id: appView
        property real itemHeight: height
        property real itemWidth: 1.777 * itemHeight
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        height: 0.6 * parent.height
        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5 * (width - itemWidth)
        preferredHighlightEnd: preferredHighlightBegin + itemWidth
        snapMode: ListView.SnapToItem
        delegate: Item {
            id: droot
            height: droot.ListView.view.itemHeight
            width: droot.ListView.view.itemWidth
            children: applicationItem
        }
    }
}
