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

import EmbeddedAuto 1.0

QtObject
{
    readonly property color textColorNormal: "#ffec8b" // lightgoldenrod 1
    readonly property color textColorSmall: "#cdbe70" // lightgoldenrod 3
    readonly property color textColorSelected: "#7FFF00" // chartreuse

    property Component bgToolButtonNormalT: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        topBorder: AppTheme.dividerSize
    }

    property Component bgToolButtonNormalTB: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        topBorder: AppTheme.dividerSize
        bottomBorder: AppTheme.dividerSize
    }

    property Component bgToolButtonNormalRT: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
        topBorder: AppTheme.dividerSize
    }

    property Component bgToolButtonNormalRTB: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
        topBorder: AppTheme.dividerSize
        bottomBorder: AppTheme.dividerSize
    }

    property Component bgToolButtonSelected: BorderBackground {
        backgroundColor: "#00008B"
        borderColor: "#FFB90F"
        leftBorder: AppTheme.buttonBorderWidth
        rightBorder: AppTheme.buttonBorderWidth
        topBorder: AppTheme.buttonBorderWidth
        bottomBorder: AppTheme.buttonBorderWidth
    }

    property Component bgTabButtonNormal: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
    }

    property Component bgTabButtonNormalT: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        topBorder: AppTheme.dividerSize
    }

    property Component bgTabButtonNormalR: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
    }

    property Component bgTabButtonNormalRT: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
        topBorder: AppTheme.dividerSize
    }

    property Component bgTabButtonNormalRB: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
        bottomBorder: AppTheme.dividerSize
    }

    property Component bgTabButtonNormalRTB: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#FFEC8B"
        rightBorder: AppTheme.dividerSize
        topBorder: AppTheme.dividerSize
        bottomBorder: AppTheme.dividerSize
    }

    property Component bgTabButtonChecked: BorderBackground {
        backgroundColor: "#191970"
        borderColor: "#7FFF00"
        leftBorder: AppTheme.buttonBorderWidth
        rightBorder: AppTheme.buttonBorderWidth
        topBorder: AppTheme.buttonBorderWidth
        bottomBorder: AppTheme.buttonBorderWidth
    }
}
