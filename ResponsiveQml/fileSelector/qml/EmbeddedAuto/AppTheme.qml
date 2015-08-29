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

pragma Singleton
import QtQuick 2.0

QtObject
{
    id: root

    readonly property real refScreenWidth: 1280
    readonly property real refScreenHeight: 800

    readonly property real screenWidth: 800
    readonly property real screenHeight: 600

    function hscale(size) {
        return Math.round(size * (screenWidth / refScreenWidth))
    }

    function vscale(size) {
        return Math.round(size * (screenHeight / refScreenHeight))
    }

    function tscale(size) {
        return Math.round((hscale(size) + vscale(size)) / 2)
    }

    readonly property real screenLeftMargin: hscale(16)
    readonly property real screenRightMargin: screenLeftMargin
    readonly property real statusBarHeight: vscale(79)
    readonly property real mainPageHeight: vscale(599)
    readonly property real appToolBarHeight: vscale(120)
    readonly property real dividerSize: 1

    readonly property int textSizeNormal: tscale(42)
    readonly property int textSizeSmall: tscale(32)
    readonly property int textSizeVerySmall: tscale(24)
    readonly property color textColorNormal: "#ffec8b" // lightgoldenrod 1
    readonly property color textColorSmall: "#cdbe70" // lightgoldenrod 3
    readonly property color textColorSelected: "#7FFF00" // chartreuse

    readonly property real leftTabButtonWidth: hscale(319)
    readonly property real leftTabButtonHeight: vscale(99)
    readonly property real toolButtonWidth: hscale(191)
    readonly property real toolButtonHeight: vscale(99)
    readonly property int buttonBorderWidth: 2

    readonly property real songInfoWidth: hscale(860)
    readonly property real songInfoHeight: vscale(300)
    readonly property real songInfoTextFieldWidth: hscale(510)
    readonly property int songInfoTextSpacing: vscale(16)
    readonly property real songInfoCoverSize: hscale(300)

    readonly property real songProgressBarWidth: hscale(576)
    readonly property real songProgressBarHeight: vscale(49)
    readonly property real songProgressBarMargin: hscale(3)
    readonly property real songProgressBarTextMargin: hscale(12)
}
