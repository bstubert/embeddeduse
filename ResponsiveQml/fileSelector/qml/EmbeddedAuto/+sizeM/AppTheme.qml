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

/* This QML component defines the size properties for the screen size 800x600 ("sizeM").
 */

pragma Singleton
import QtQuick 2.0

QtObject
{
    readonly property real screenWidth: 800
    readonly property real screenHeight: 600

    readonly property real screenLeftMargin: 10
    readonly property real screenRightMargin: screenLeftMargin
    readonly property real statusBarHeight: 59
    readonly property real mainPageHeight: 449
    readonly property real appToolBarHeight: 90
    readonly property real dividerSize: 1

    readonly property int textSizeNormal: 32
    readonly property int textSizeSmall: 24
    readonly property int textSizeVerySmall: 18
    readonly property color textColorNormal: "#ffec8b" // lightgoldenrod 1
    readonly property color textColorSmall: "#cdbe70" // lightgoldenrod 3
    readonly property color textColorSelected: "#7FFF00" // chartreuse

    readonly property real leftTabButtonWidth: 199
    readonly property real leftTabButtonHeight: 74
    readonly property real toolButtonWidth: 119
    readonly property real toolButtonHeight: 74
    readonly property int buttonBorderWidth: 2

    readonly property real songInfoWidth: 537
    readonly property real songInfoHeight: 225
    readonly property real songInfoTextFieldWidth: 318
    readonly property int songInfoTextSpacing: 12
    readonly property real songInfoCoverSize: 187

    readonly property real songProgressBarWidth: 360
    readonly property real songProgressBarPositionHeight: 37
    readonly property real songProgressBarTimeHeight: songProgressBarPositionHeight - 1
    readonly property real songProgressBarMargin: 2
    readonly property real songProgressBarTextMargin: 8
}
