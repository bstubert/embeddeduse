// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

import QtQuick 2.9
import QtQuick.Controls 2.2
import MyModels 1.0

Rectangle
{
    property Model model: Model {}
    color: "#C8FFBE"

    Component.onDestruction: console.log("@@@@@@ Destroyig SecondScreen!")

    Label {
        anchors.fill: parent
        text: model.infoText
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
    }
}
