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

Column
{
    id: root

    property bool playing: false

    property Component __toolButtonStyle: ButtonStyle {
        background: BorderImage {
            source: !control.pressed ? "qrc:/img/bgToolButton.png" : "qrc:/img/bgToolButtonPressed.png"
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

    width: childrenRect.width
    height: childrenRect.height

    Divider {
        width: buttonRow.width + 1
        height: AppTheme.dividerSize
    }

    Row
    {
        id: buttonRow

        width: childrenRect.width
        height: childrenRect.height

        Repeater
        {
            id: repeater

            model: ListModel {
                id: musicBarModel

                function doAction(index) {
                    switch (index) {
                    case 1: // play/pause
                        if (root.playing) {
                            musicBarModel.setProperty(index, "buttonIcon", "qrc:/img/icPlay.png")
                            musicBarModel.setProperty(index, "buttonIconPressed", "qrc:/img/icPlayPressed.png")
                        }
                        else {
                            musicBarModel.setProperty(index, "buttonIcon", "qrc:/img/icPause.png")
                            musicBarModel.setProperty(index, "buttonIconPressed", "qrc:/img/icPausePressed.png")
                        }
                        root.playing = !root.playing
                        break;
                    default:
                        console.log("@ Action not supported")
                    }
                }

                ListElement {
                    buttonIcon: "qrc:/img/icPreviousTrack.png"
                    buttonIconPressed: "qrc:/img/icPreviousTrackPressed.png"
                }
                ListElement {
                    buttonIcon: "qrc:/img/icPlay.png"
                    buttonIconPressed: "qrc:/img/icPlayPressed.png"
                }
                ListElement {
                    buttonIcon: "qrc:/img/icNextTrack.png"
                    buttonIconPressed: "qrc:/img/icNextTrackPressed.png"
                }
                ListElement {
                    buttonIcon: "qrc:/img/icTracks.png"
                    buttonIconPressed: "qrc:/img/icTracksPressed.png"
                }
            }

            Row {
                width: childrenRect.width
                height: childrenRect.height

                Button {
                    id: toolButton
                    iconSource: !pressed ? buttonIcon : buttonIconPressed
                    style: root.__toolButtonStyle
                    width: visible ? AppTheme.toolButtonWidth : 0
                    height: visible ? AppTheme.toolButtonHeight : 0
                    visible: index < AppTheme.musicToolBarButtonCount

                    onClicked: musicBarModel.doAction(index)
                }

                Divider {
                    width: visible ? AppTheme.dividerSize : 0
                    height: visible ? AppTheme.toolButtonHeight : 0
                    visible: toolButton.visible
                }
            }
        }

        Button {
            iconSource: !pressed ? "qrc:/img/icMore.png" : "qrc:/img/icMorePressed.png"
            style: root.__toolButtonStyle
            width: AppTheme.toolButtonWidth
            height: AppTheme.toolButtonHeight
        }
    }
}
