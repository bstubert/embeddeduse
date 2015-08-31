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

import EmbeddedAuto 1.0

BorderImage
{
    id: root
    source: "qrc:/img/bgMainPage.png"

    SongProgressBar {
        id: songProgressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        playing: musicToolBar.playing
        totalTime: 227
        elapsedTime: 215
    }

    SongInfo {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: songProgressBar.bottom
        anchors.bottom: musicToolBar.top
        anchors.margins: AppTheme.songInfoMargin
    }

    MusicToolBar {
        id: musicToolBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}

