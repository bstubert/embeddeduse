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
    readonly property real statusBarHeight: 60
    readonly property real mainPageHeight: 450
    readonly property real appToolBarHeight: 90

    readonly property int textSizeNormal: 32
    readonly property int textSizeSmall: 24
    readonly property int textSizeVerySmall: 18

    readonly property real leftTabButtonWidth: 200
    readonly property real leftTabButtonHeight: 75
    readonly property real toolButtonWidth: 120
    readonly property real toolButtonHeight: 75

    readonly property real songInfoWidth: 600
    readonly property real songInfoHeight: 299
    readonly property real songInfoMargin: 30
    readonly property real songInfoTextFieldWidth: songInfoWidth - songInfoCoverSize - 3 * songInfoMargin
    readonly property int songInfoTextSpacing: 12
    readonly property real songInfoCoverSize: 180

    readonly property real songProgressBarWidth: 360
    readonly property real songProgressBarPositionHeight: 38
    readonly property real songProgressBarTimeHeight: songProgressBarPositionHeight - 1
    readonly property real songProgressBarMargin: 2
    readonly property real songProgressBarTextMargin: 8

    readonly property int musicToolBarButtonCount: 4
    readonly property real musicToolBarButtonHeight: toolButtonHeight + 1

    readonly property real dialogWidth: 0           // Not used yet
    readonly property real dialogHeight: 0          // Not used yet
    readonly property real dialogButtonHeight: 0    // Not used yet
}
