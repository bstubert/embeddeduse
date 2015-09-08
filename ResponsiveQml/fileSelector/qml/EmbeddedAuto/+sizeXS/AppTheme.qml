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

/* This QML component defines the size properties for the screen size 400x225 ("sizeXS").
 */

pragma Singleton
import QtQuick 2.0

QtObject
{
    readonly property real screenWidth: 400
    readonly property real screenHeight: 225

    readonly property real screenLeftMargin: 5
    readonly property real screenRightMargin: screenLeftMargin
    readonly property real statusBarHeight: 0
    readonly property real mainPageHeight: screenHeight
    readonly property real appToolBarHeight: 0
    readonly property real dividerSize: 1

    readonly property int textSizeNormal: 24
    readonly property int textSizeSmall: 18
    readonly property int textSizeVerySmall: 14

    readonly property real leftTabButtonWidth: 0    // Not used
    readonly property real leftTabButtonHeight: 0   // Not used
    readonly property real toolButtonWidth: 80
    readonly property real toolButtonHeight: 60
    readonly property int buttonBorderWidth: 2

    readonly property real songInfoWidth: 320
    readonly property real songInfoHeight: 140
    readonly property real songInfoMargin: 15
    readonly property real songInfoTextFieldWidth: songInfoCoverSize !== 0 ? songInfoWidth - songInfoCoverSize - 3 * songInfoMargin
                                                                           : songInfoWidth - 2 * songInfoMargin
    readonly property int songInfoTextSpacing: 6
    readonly property real songInfoCoverSize: 0

    readonly property real songProgressBarWidth: 200
    readonly property real songProgressBarPositionHeight: 25
    readonly property real songProgressBarTimeHeight: 0
    readonly property real songProgressBarMargin: 1
    readonly property real songProgressBarTextWidth: 60 // Specific to sizeXS
    readonly property real songProgressBarTextMargin: 0

    readonly property int musicToolBarButtonCount: 3
    readonly property real musicToolBarButtonHeight: toolButtonHeight

    readonly property real dialogWidth: 320
    readonly property real dialogHeight: screenHeight
    readonly property real dialogButtonHeight: toolButtonHeight

    // Specific to sizeXS
    readonly property real musicCategorySwitcherButtonWidth: 160
    readonly property real musicCategorySwitcherButtonHeight: 55


    // Look-and-feel properties (e.g., for brand themes)
    readonly property color textColorNormal: "#ffec8b" // lightgoldenrod 1
    readonly property color textColorSmall: "#cdbe70" // lightgoldenrod 3
    readonly property color textColorSelected: "#7FFF00" // chartreuse

    property Component bgToolButtonNormalT: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        topBorder: dividerSize
    }

    property Component bgToolButtonNormalTB: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        topBorder: dividerSize
        bottomBorder: dividerSize
    }

    property Component bgToolButtonNormalRT: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        rightBorder: dividerSize
        topBorder: dividerSize
    }

    property Component bgToolButtonNormalRTB: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        rightBorder: dividerSize
        topBorder: dividerSize
        bottomBorder: dividerSize
    }

    property Component bgToolButtonSelected: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFB90F"
        leftBorder: buttonBorderWidth
        rightBorder: buttonBorderWidth
        topBorder: buttonBorderWidth
        bottomBorder: buttonBorderWidth
    }

    property Component bgTabButtonNormal: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
    }

    property Component bgTabButtonNormalT: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        topBorder: dividerSize
    }

    property Component bgTabButtonNormalR: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: dividerSize
    }

    property Component bgTabButtonNormalRT: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: dividerSize
        topBorder: dividerSize
    }

    property Component bgTabButtonChecked: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#7FFF00"
        leftBorder: buttonBorderWidth
        rightBorder: buttonBorderWidth
        topBorder: buttonBorderWidth
        bottomBorder: buttonBorderWidth
    }
}
