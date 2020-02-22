// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

import QtQuick 2.9
import Customer.Models 1.0

Rectangle
{
    property Customer customer
    color: "#C8FFBE"

    Text {
        anchors.centerIn: parent
        text: customer.firstName + " " + customer.lastName
        font.pixelSize: 64
        color: "#623B5A"
    }
}
