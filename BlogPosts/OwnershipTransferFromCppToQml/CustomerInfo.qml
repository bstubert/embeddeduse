// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

import QtQuick 2.9

Rectangle
{
    id: root
    color: "#C8FFBE"

    Component.onDestruction: console.log("@@@ Destroying CustomerInfo.qml")

    Text {
        anchors.centerIn: parent
        text: g_customerMgr.currentCustomer.firstName + " " +
              g_customerMgr.currentCustomer.lastName
        font.pixelSize: 64
        color: "#623B5A"
    }
}
