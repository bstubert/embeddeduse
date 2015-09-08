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

Item
{
    id: root

    property bool playing: false
    property int elapsedTime: 0  // in seconds
    property int totalTime: 0    // in seconds

    width: childrenRect.width
    height: childrenRect.height

    Row
    {
        width: childrenRect.width
        height: childrenRect.height

        Button {
            id: shuffleButton
            iconSource: !pressed ? "qrc:/img/icShuffle.png" : "qrc:/img/icShufflePressed.png"
            style: ToolButtonStyle {
                backgroundNormal: BrandTheme.bgToolButtonNormalRTB
                backgroundSelected: BrandTheme.bgToolButtonSelected
            }
            width: SizeTheme.toolButtonWidth
            height: SizeTheme.toolButtonHeight
        }

        Column {
            BorderBackground {
                id: position
                backgroundColor: "#00008B"
                borderColor: "#FFEC8B"
                rightBorder: SizeTheme.dividerSize
                topBorder: SizeTheme.dividerSize
                bottomBorder: SizeTheme.dividerSize
                width: SizeTheme.songProgressBarWidth
                height: SizeTheme.songProgressBarPositionHeight

                Image {
                    source: "qrc:/img/bgProgressBar.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: SizeTheme.songProgressBarMargin
                    height: position.height - 2 * SizeTheme.songProgressBarMargin
                    width: root.totalTime != 0 ? ((SizeTheme.songProgressBarWidth - 2 * SizeTheme.songProgressBarMargin) * root.elapsedTime / root.totalTime) : 0
                    Behavior on width {
                        PropertyAnimation {
                            duration: 1000
                            easing.type: Easing.Linear
                        }
                    }
                }
            }

            BorderBackground {
                id: time
                backgroundColor: "#00008B"
                borderColor: "#FFEC8B"
                rightBorder: SizeTheme.dividerSize
                bottomBorder: SizeTheme.dividerSize
                width: SizeTheme.songProgressBarWidth
                height: SizeTheme.songProgressBarTimeHeight

                Text {
                    id: elapsedTimeText
                    anchors.left: parent.left
                    anchors.leftMargin: SizeTheme.songProgressBarTextMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: Qt.formatTime(new Date(root.elapsedTime * 1000), "m:ss")
                    font.pixelSize: SizeTheme.textSizeVerySmall
                    color: BrandTheme.textColorNormal
                }

                Text {
                    id: totalTimeText
                    anchors.right: parent.right
                    anchors.rightMargin: SizeTheme.songProgressBarTextMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: Qt.formatTime(new Date(root.totalTime * 1000), "m:ss")
                    font.pixelSize: SizeTheme.textSizeVerySmall
                    color: BrandTheme.textColorNormal
                }
            }
        }

        Button {
            id: repeatButton
            iconSource: !pressed ? "qrc:/img/icRepeat.png" : "qrc:/img/icRepeatPressed.png"
            style: ToolButtonStyle {
                backgroundNormal: BrandTheme.bgToolButtonNormalTB
                backgroundSelected: BrandTheme.bgToolButtonSelected
            }
            width: SizeTheme.toolButtonWidth
            height: SizeTheme.toolButtonHeight
        }
    }

    Timer {
        id: progressTimer
        interval: 1000
        running: root.playing
        repeat: true
        onTriggered: {
            if (root.elapsedTime < root.totalTime) {
                ++root.elapsedTime
            }
            else {
                root.elapsedTime = 0
            }
        }
    }
}
