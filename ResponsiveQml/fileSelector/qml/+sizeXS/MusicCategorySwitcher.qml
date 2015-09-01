/******************************************************************************

Copyright (C) 2015 Burkhard Stubert, Embedded Use (DBA), Germany
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Embedded Use (DBA) nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL BURKHARD STUBERT, EMBEDDED USE (DBA), BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import EmbeddedAuto 1.0

BorderImage
{
    id: root
    source: "qrc:/img/bgTabButton.png"
    width: childrenRect.width
    height: childrenRect.height

    // Prevent propagation of mouse events to parents and siblings of this item
    // (e.g., items lying below this item).
    MouseArea {
        anchors.fill: parent
        onPressed: mouse.accepted = true
    }

    Grid {
        id: categoryGrid

        columns: 2
        rows: 3
        width: childrenRect.width
        height: childrenRect.height

        ExclusiveGroup {
            id: tabButtonGroup
        }

        Repeater {
            id: repeater

            model: ListModel {
                ListElement {
                    buttonText: "Now Playing"
                    isPadding: false
                }
                ListElement {
                    buttonText: "Artists"
                    isPadding: false
                }
                ListElement {
                    buttonText: "Albums"
                    isPadding: false
                }
                ListElement {
                    buttonText: "Genres"
                    isPadding: false
                }
                ListElement {
                    buttonText: "Songs"
                    isPadding: false
                }
                ListElement {
                    buttonText: ""
                    isPadding: true
                }
            }

            Row {
                property bool __isLastRow: Math.floor(index / categoryGrid.columns) === categoryGrid.rows - 1
                property bool __isFirstColumn: index % categoryGrid.columns === 0

                width: childrenRect.width
                height: childrenRect.height

                Column {
                    width: childrenRect.width
                    height: childrenRect.height

                    Button {
                        id: gridButton
                        text: buttonText
                        exclusiveGroup: tabButtonGroup
                        checkable: enabled
                        checked: index === 0
                        enabled: !isPadding
                        style: ButtonStyle {
                            background: BorderImage {
                                source: !control.checked ? "qrc:/img/bgTabButton.png" : "qrc:/img/bgTabButtonChecked.png"
                                border.left: AppTheme.buttonBorderWidth
                                border.top: AppTheme.buttonBorderWidth
                                border.right: AppTheme.buttonBorderWidth
                                border.bottom: AppTheme.buttonBorderWidth
                            }
                            label: Text {
                                x: AppTheme.screenLeftMargin
                                text: control.text
                                font.pixelSize: AppTheme.textSizeNormal
                                color: control.checked ? AppTheme.textColorSelected : AppTheme.textColorNormal
                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        width: AppTheme.musicCategorySwitcherButtonWidth - (__isFirstColumn ? 0 : 1)
                        height: AppTheme.musicCategorySwitcherButtonHeight + (__isLastRow ? 1 : 0)
                    }

                    Divider {
                        height: AppTheme.dividerSize
                        width: AppTheme.musicCategorySwitcherButtonWidth
                        visible: !__isLastRow
                    }
                }

                Divider {
                    width: AppTheme.dividerSize
                    height: gridButton.height
                    visible: __isFirstColumn
                }
            }
        }
    }

    Divider {
        height: AppTheme.dividerSize
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: categoryGrid.bottom
    }

    Row {
        id: dialogButtonRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: childrenRect.width
        height: childrenRect.height

        property Component __toolButtonStyle: ButtonStyle {
            background: BorderImage {
                source: !control.pressed ? "qrc:/img/bgTabButton.png" : "qrc:/img/bgToolButtonPressed.png" // TODO: Introduce bgTabButtonPressed.png!
                border.left: AppTheme.buttonBorderWidth
                border.top: AppTheme.buttonBorderWidth
                border.right: AppTheme.buttonBorderWidth
                border.bottom: AppTheme.buttonBorderWidth
            }
            label: Image {
                source: control.iconSource
                fillMode: Image.PreserveAspectFit
            }
        }

        Divider {
            width: AppTheme.dividerSize
            height: AppTheme.toolButtonHeight
        }

        Button {
            id: cancelButton
            iconSource: !pressed ? "qrc:/img/icCancel.png" : "qrc:/img/icCancelPressed.png"
            style: dialogButtonRow.__toolButtonStyle
            width: AppTheme.toolButtonWidth
            height: AppTheme.toolButtonHeight
            onClicked: root.visible = false
        }

        Divider {
            width: AppTheme.dividerSize
            height: AppTheme.toolButtonHeight
        }

        Button {
            id: okButton
            iconSource: !pressed ? "qrc:/img/icOk.png" : "qrc:/img/icOkPressed.png"
            style: dialogButtonRow.__toolButtonStyle
            width: AppTheme.toolButtonWidth
            height: AppTheme.toolButtonHeight
            onClicked: root.visible = false
        }
    }


}
