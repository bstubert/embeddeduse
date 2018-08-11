// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef MODEL_H
#define MODEL_H

#include <QMetaMethod>
#include <QObject>
#include <QScopedPointer>
#include <QString>

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString infoText READ infoText WRITE setInfoText NOTIFY infoTextChanged)

public:
    Model(QObject *parent = nullptr);
    virtual ~Model();
    QString infoText() const;
    void setInfoText(const QString &text);

signals:
    void infoTextChanged();

private:
    class Impl;
    QScopedPointer<Impl> m_impl;
};

#endif // MODEL_H
