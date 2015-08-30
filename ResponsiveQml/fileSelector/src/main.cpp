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

#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QtDebug>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlFileSelector>
#include <QtWidgets/QApplication>


namespace {

/*!
  Returns the name of the extra selector corresponding to the given \a screenSize. If \a screenSize
  is a value other than "sizeM" or "sizeXS", it returns the extra selector for the default screen size
  "sizeXL", which is the empty string "". Otherwise, it returns \a screenSize as the extra selector.
 */
QString screenSizeSelector(const QString screenSize)
{
    if (screenSize != "sizeM" && screenSize != "sizeXS") {
        return "";
    }
    else {
        return screenSize;
    }
}

}


/*!
  The user can specify the screen size through the command-line option "--screenSize=<screen-size>",
  where <screen-size> is one of "sizeXL" (1280x800), "sizeM" (800x600) or "sizeXS" (400x225). If this
  option is not present on the command line, the program will use "sizeXL" as the default screen size.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption screenSizeOption(
                "screenSize",
                "One of the string constants sizeXL (1280x800), sizeM (800x600) or sizeXS (400x225)."
                "screen-size", "sizeXL");
    screenSizeOption.setDefaultValue("sizeXL");
    parser.addOption(screenSizeOption);
    parser.process(app);
    QString screenSize = parser.value(screenSizeOption);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/qml");
    QQmlFileSelector *selector = new QQmlFileSelector(&engine);
    selector->setExtraSelectors(QStringList() << screenSizeSelector(screenSize));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
