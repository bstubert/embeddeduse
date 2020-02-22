// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    id: topWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("EmbeddedUse")

    Rectangle {
        id: view
        property bool isCustomerInfoShown: false
        anchors.fill: parent
        color: "#EDFFAB"

        Loader {
            id: loader
            anchors.fill: parent
        }

        Button {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 0.25 * topWindow.width
            height: 0.10 * topWindow.height
            text: !view.isCustomerInfoShown ? qsTr("Open") : qsTr("Close")
            onClicked: {
                if (!view.isCustomerInfoShown) {
                    loader.setSource("CustomerInfo.qml",
                                     {"customer": g_customerMgr.randomCustomer })
                }
                else {
                    loader.setSource("", {})
                }
                view.isCustomerInfoShown = !view.isCustomerInfoShown
            }
        }
    }
}
