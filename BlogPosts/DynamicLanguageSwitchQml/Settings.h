#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QTranslator>
class QQmlEngine;
class QString;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QQmlEngine *engine, QObject *parent = nullptr);

public slots:
    void switchToLanguage(const QString &language);

private:
    QQmlEngine *m_engine;
    QTranslator m_translator;
};

#endif // SETTINGS_H
