#include <QCoreApplication>
#include <QQmlEngine>
#include <QString>
#include <QtDebug>
#include "Settings.h"

Settings::Settings(QQmlEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
{
    switchToLanguage("de_DE");
}

void Settings::switchToLanguage(const QString &language)
{
    if (!m_translator.isEmpty()) {
        if (!QCoreApplication::removeTranslator(&m_translator)) {
            qDebug() << "WARNING: Could not remove translator for " << language;
            return;
        }
    }
    if (!m_translator.load(QStringLiteral(":/language_") + language)) {
        qDebug() << "WARNING: Could not load language " << language;
        return;
    }
    if (!QCoreApplication::installTranslator(&m_translator)) {
        qDebug() << "WARNING: Could not install translator for " << language;
        return;
    }
    m_engine->retranslate();
}
