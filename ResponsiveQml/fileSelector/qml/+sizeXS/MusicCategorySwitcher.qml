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
                }
                ListElement {
                    buttonText: "Artists"
                }
                ListElement {
                    buttonText: "Albums"
                }
                ListElement {
                    buttonText: "Genres"
                }
                ListElement {
                    buttonText: "Songs"
                }
                ListElement {
                    buttonText: ""
                }
            }

            Button {
                id: gridButton

                property bool __isFirstRow: Math.floor(index / categoryGrid.columns) === 0
                property bool __isFirstColumn: index % categoryGrid.columns === 0

                text: buttonText
                exclusiveGroup: tabButtonGroup
                checkable: enabled
                checked: index === 0
                enabled: !gridButton.Positioner.isLastItem
                style: TabButtonStyle {
                    backgroundNormal: __isFirstRow ? (__isFirstColumn ? BrandTheme.bgTabButtonNormalR : BrandTheme.bgTabButtonNormal)
                                                   : (__isFirstColumn ? BrandTheme.bgTabButtonNormalRT : BrandTheme.bgTabButtonNormalT)
                    backgroundChecked: BrandTheme.bgTabButtonChecked
                    textSize: SizeTheme.textSizeNormal
                    textColorNormal: BrandTheme.textColorNormal
                    textColorChecked: BrandTheme.textColorSelected
                    leftMargin: SizeTheme.screenLeftMargin
                }
                width: SizeTheme.musicCategorySwitcherButtonWidth
                height: SizeTheme.musicCategorySwitcherButtonHeight
            }
        }
    }

    Row {
        id: dialogButtonRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: childrenRect.width
        height: childrenRect.height

        BorderBackground {
            backgroundColor: BrandTheme.backgroundColorDark
            borderColor: BrandTheme.textColorNormal
            rightBorder: BrandTheme.borderSizeNormal
            topBorder: BrandTheme.borderSizeNormal
            width: SizeTheme.musicCategorySwitcherButtonWidth
            height: SizeTheme.toolButtonHeight
        }

        Button {
            id: cancelButton
            iconSource: !pressed ? "qrc:/img/icCancel.png" : "qrc:/img/icCancelPressed.png"
            style: ToolButtonStyle {
                backgroundNormal: BrandTheme.bgTabButtonNormalRT
                backgroundSelected: BrandTheme.bgToolButtonSelected
            }
            width: SizeTheme.toolButtonWidth
            height: SizeTheme.toolButtonHeight
            onClicked: root.visible = false
        }

        Button {
            id: okButton
            iconSource: !pressed ? "qrc:/img/icOk.png" : "qrc:/img/icOkPressed.png"
            style: ToolButtonStyle {
                backgroundNormal: BrandTheme.bgTabButtonNormalT
                backgroundSelected: BrandTheme.bgToolButtonSelected
            }
            width: SizeTheme.toolButtonWidth
            height: SizeTheme.toolButtonHeight
            onClicked: root.visible = false
        }
    }


}
